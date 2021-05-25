import FWCore.ParameterSet.Config as cms

# TODO: should I copy it and change some parameters? No need
from RecoPPS.Configuration.recoCTPPS_cff import ctppsLocalTrackLiteProducer
from CalibPPS.AlignmentGlobal.ppsAlignmentWorker_cfi import ppsAlignmentWorker

MEtoEDMConvertPPSAlignment = cms.EDProducer('MEtoEDMConverter',
    Name=cms.untracked.string('MEtoEDMConverter'),
    Verbosity=cms.untracked.int32(0),
    Frequency=cms.untracked.int32(50),
    MEPathToSave=cms.untracked.string('AlCaReco/PPSAlignment'),  # TODO: check naming
    deleteAfterCopy=cms.untracked.bool(True)
)

taskALCARECOPPSAlignment = cms.Task(
    ctppsLocalTrackLiteProducer,
    ppsAlignmentWorker,
    MEtoEDMConvertPPSAlignment
)
