#include "DQM/SiStripCommissioningClients/interface/DaqScopeModeHistograms.h"
#include "CondFormats/SiStripObjects/interface/DaqScopeModeAnalysis.h"
#include "DataFormats/SiStripCommon/interface/SiStripConstants.h"
#include "DataFormats/SiStripCommon/interface/SiStripEnumsAndStrings.h"
#include "DQM/SiStripCommissioningSummary/interface/DaqScopeModeSummaryFactory.h"
#include "DQM/SiStripCommissioningAnalysis/interface/DaqScopeModeAlgorithm.h"
#include "DQM/SiStripCommissioningSummary/interface/SummaryGenerator.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace sistrip;

// -----------------------------------------------------------------------------
/** */
DaqScopeModeHistograms::DaqScopeModeHistograms(const edm::ParameterSet& pset, DQMStore* bei)
    : CommissioningHistograms(
          pset.getParameter<edm::ParameterSet>("DaqScopeModeParameters"), bei, sistrip::DAQ_SCOPE_MODE) {
  factory_ = unique_ptr<DaqScopeModeSummaryFactory>(new DaqScopeModeSummaryFactory);
  LogTrace(mlDqmClient_) << "[DaqScopeModeHistograms::" << __func__ << "]"
                         << " Constructing object...";
}

// -----------------------------------------------------------------------------
/** */
DaqScopeModeHistograms::~DaqScopeModeHistograms() {
  LogTrace(mlDqmClient_) << "[DaqScopeModeHistograms::" << __func__ << "]"
                         << " Destructing object...";
}

// -----------------------------------------------------------------------------
/** */
void DaqScopeModeHistograms::histoAnalysis(bool debug) {
  LogTrace(mlDqmClient_) << "[DaqScopeModeHistograms::" << __func__ << "]";

  // Some initialisation
  uint16_t valid = 0;
  HistosMap::const_iterator iter;
  Analyses::iterator ianal;
  std::map<std::string, uint16_t> errors;

  // Clear map holding analysis objects
  for (ianal = data().begin(); ianal != data().end(); ianal++) {
    if (ianal->second) {
      delete ianal->second;
    }
  }
  data().clear();

  // Iterate through map containing histograms
  for (iter = histos().begin(); iter != histos().end(); iter++) {
    // Check vector of histos is not empty
    if (iter->second.empty()) {
      edm::LogWarning(mlDqmClient_) << "[DaqScopeModeHistograms::" << __func__ << "]"
                                    << " Zero histograms found!";
      continue;
    }

    // Retrieve pointers to profile histos
    std::vector<TH1*> profs;
    Histos::const_iterator ihis = iter->second.begin();
    for (; ihis != iter->second.end(); ihis++) {
      TProfile* prof = ExtractTObject<TProfile>().extract((*ihis)->me_);
      if (prof) {
        profs.push_back(prof);
      }
      if (!prof) {
        TH1F* prof = ExtractTObject<TH1F>().extract((*ihis)->me_);
        profs.push_back(prof);
      }
    }

    // Perform histo analysis
    DaqScopeModeAnalysis* anal = new DaqScopeModeAnalysis(iter->first);
    DaqScopeModeAlgorithm algo(this->pset(), anal);
    algo.analysis(profs);
    data()[iter->first] = anal;

    if (anal->isValid()) {
      valid++;
    }
    if (!anal->getErrorCodes().empty()) {
      errors[anal->getErrorCodes()[0]]++;
    }
  }

  if (!histos().empty()) {
    edm::LogVerbatim(mlDqmClient_) << "[DaqScopeModeHistograms::" << __func__ << "]"
                                   << " Analyzed histograms for " << histos().size() << " FED channels, of which "
                                   << valid << " (" << 100 * valid / histos().size() << "%) are valid.";
    if (!errors.empty()) {
      uint16_t count = 0;
      std::stringstream ss;
      ss << std::endl;
      std::map<std::string, uint16_t>::const_iterator ii;
      for (ii = errors.begin(); ii != errors.end(); ++ii) {
        ss << " " << ii->first << ": " << ii->second << std::endl;
        count += ii->second;
      }
      edm::LogWarning(mlDqmClient_) << "[DaqScopeModeHistograms::" << __func__ << "]"
                                    << " Found " << count << " errors (" << 100 * count / histos().size()
                                    << "%): " << ss.str();
    }
  } else {
    edm::LogWarning(mlDqmClient_) << "[DaqScopeModeHistograms::" << __func__ << "]"
                                  << " No histograms to analyze!";
  }
}

// -----------------------------------------------------------------------------
void DaqScopeModeHistograms::printAnalyses() {
  Analyses::iterator ianal = data().begin();
  Analyses::iterator janal = data().end();
  for (; ianal != janal; ++ianal) {
    if (ianal->second) {
      std::stringstream ss;
      ianal->second->print(ss, 1);
      ianal->second->print(ss, 2);
      if (ianal->second->isValid()) {
        LogTrace(mlDqmClient_) << ss.str();
      } else {
        edm::LogWarning(mlDqmClient_) << ss.str();
      }
    }
  }
}
