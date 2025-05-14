//
// Keeps the pointer to all internal members such as event or track
//

// FemtoDst headers
#include "StFemtoMessMgr.h"
#include "StFemtoEvent.h"
#include "StFemtoTrack.h"
#include "StFemtoV0.h"
#include "StFemtoXi.h"
#include "StFemtoKFP.h"
#include "StFemtoDst.h"          // MUST be the last one

TClonesArray** StFemtoDst::femtoArrays = 0;

//_________________
void StFemtoDst::unset() {
  // Unset pointers
  femtoArrays = 0;
}

//_________________
void StFemtoDst::set(TClonesArray** theFemtoArrays) {
  // Set pointers
  femtoArrays = theFemtoArrays;
}

//_________________
void StFemtoDst::print() const {
  // Print event information
  LOG_INFO << "\n=========== Event header =============\n\n";
  event()->print();
  LOG_INFO << "=====================================\n\n";
}

//_________________
void StFemtoDst::printTracks() {
  // Print track information
  if(numberOfTracks() == 0) {
    LOG_INFO << "No tracks found!" << endm;
    return;
  }

  LOG_INFO << "\n+++++++++ track list ( " << numberOfTracks() << " entries )\n\n";
  for(UInt_t iTrk=0; iTrk<numberOfTracks(); iTrk++) {
    LOG_INFO << "+++ track " << iTrk << "\n";
    track(iTrk)->print();
    LOG_INFO << "\n";
  }

  LOG_INFO << endm;
}

//_________________
void StFemtoDst::printV0s() {
  // Print track information
  if(numberOfV0s() == 0) {
    LOG_INFO << "No V0s found!" << endm;
    return;
  }

  LOG_INFO << "\n+++++++++ V0 list ( " << numberOfV0s() << " entries )\n\n";
  for(UInt_t iV0=0; iV0<numberOfV0s(); iV0++) {
    LOG_INFO << "+++ v0 " << iV0 << "\n";
    v0(iV0)->print();
    LOG_INFO << "\n";
  }

  LOG_INFO << endm;
}

//_________________
void StFemtoDst::printXis() {
  // Print track information
  if(numberOfXis() == 0) {
    LOG_INFO << "No Xis found!" << endm;
    return;
  }

  LOG_INFO << "\n+++++++++ Xi list ( " << numberOfXis() << " entries )\n\n";
  for(UInt_t iXi=0; iXi<numberOfXis(); iXi++) {
    LOG_INFO << "+++ xi " << iXi << "\n";
    xi(iXi)->print();
    LOG_INFO << "\n";
  }

  LOG_INFO << endm;
}

//_________________
void StFemtoDst::printKFPs() {
  // Print track information
  if(numberOfKFPs() == 0) {
    LOG_INFO << "No KFParticles found!" << endm;
    return;
  }

  LOG_INFO << "\n+++++++++ KFParticle list ( " << numberOfKFPs() << " entries )\n\n";
  for(UInt_t iKFP=0; iKFP<numberOfKFPs(); iKFP++) {
    LOG_INFO << "+++ KFParticle " << iKFP << "\n";
    kfparticle(iKFP)->print();
    LOG_INFO << "\n";
  }

  LOG_INFO << endm;
}
