#ifndef FWCore_Framework_EDLooperHelper_h
#define FWCore_Framework_EDLooperHelper_h
// -*- C++ -*-
//
// Package:     <package>
// Module:      EDLooperHelper
// 
/**\class EDLooperHelper EDLooperHelper.h package/EDLooperHelper.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Valentin Kuznetsov
// Created:     Wed Jul 12 11:26:26 EDT 2006
// $Id: EDLooperHelper.h,v 1.5 2007/07/13 20:08:18 chrjones Exp $
//
// Revision history
//
// $Log: EDLooperHelper.h,v $
// Revision 1.5  2007/07/13 20:08:18  chrjones
// Have the code used by the looper properly handle run and luminosity blocks
//
// Revision 1.4  2007/06/22 23:26:32  wmtan
// Add Run and Lumi loops to the EventProcessor
//
// Revision 1.3  2007/06/14 17:52:15  wmtan
// Remove unnecessary includes
//
// Revision 1.2  2006/10/13 01:47:34  wmtan
// Remove unnecessary argument from runOnce()
//
// Revision 1.1  2006/07/23 01:24:33  valya
// Add looper support into framework. The base class is EDLooper. All the work done in EventProcessor and EventHelperLooper
//

// system include files
#include "boost/shared_ptr.hpp"

// user include files
#include "FWCore/Framework/interface/EventHelperDescription.h"
#include "FWCore/Framework/interface/EventSetupProvider.h"

// forward declarations

namespace edm {
class EventProcessor;
class LuminosityBlockPrincipal;
class RunPrincipal;

namespace eventsetup {
class EventSetupRecordKey;
}

class EDLooperHelper
{
      // ---------- friend classes and functions ---------------
      friend class edm::EventProcessor;

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      virtual ~EDLooperHelper();

      // ---------- member functions ---------------------------
      EventHelperDescription runOnce(boost::shared_ptr<edm::RunPrincipal>& rp,
                                     boost::shared_ptr<edm::LuminosityBlockPrincipal>& lbp);
      void rewind(const std::set<edm::eventsetup::EventSetupRecordKey>& keys);

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      EDLooperHelper(EventProcessor* p) : eventProcessor_(p) {}
      EDLooperHelper( const EDLooperHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const EDLooperHelper& operator=( const EDLooperHelper& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      EventProcessor* eventProcessor_;

      // ---------- static data members ------------------------

};

// inline function definitions

} // end of namespace

#endif /* FWCORE_FRAMEWORK_EDLOOPERHELPER_H */
