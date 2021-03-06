#ifndef IsolationAlgos_IsoDepositExtractorFactory_H
#define IsolationAlgos_IsoDepositExtractorFactory_H

namespace edm {
  class ParameterSet;
  class ConsumesCollector;
}  // namespace edm
namespace reco {
  namespace isodeposit {
    class IsoDepositExtractor;
  }
}  // namespace reco
#include "FWCore/PluginManager/interface/PluginFactory.h"

typedef edmplugin::PluginFactory<reco::isodeposit::IsoDepositExtractor*(const edm::ParameterSet&,
                                                                        edm::ConsumesCollector&&)>
    IsoDepositExtractorFactory;
typedef edmplugin::PluginFactory<reco::isodeposit::IsoDepositExtractor*(const edm::ParameterSet&,
                                                                        edm::ConsumesCollector&)>
    IsoDepositExtractorFactoryFromHelper;
#endif
