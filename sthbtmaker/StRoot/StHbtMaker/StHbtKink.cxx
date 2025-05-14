//
// Main class holding kink information
//

// StHbtMaker headers
#include "StHbtKink.h"
#include "StHbtTrack.h"

#ifdef __ROOT__
ClassImp(StHbtKink)
#endif

//_________________
StHbtKink::StHbtKink() :
  mDcaParentDaughter(999),
  mHitDistanceParentDaughter(999),
  mHitDistanceParentVertex(999),
  mDeltaEnergy{},
  mDecayAngle(0),
  mDecayAngleCM(0),
  mDaughter(),
  mParent(),
  mPositionX(999),
  mPositionY(999),
  mPositionZ(999) {

  /* empty */
}

//_________________
StHbtKink::StHbtKink(const StHbtKink& k) :
  mDcaParentDaughter(k.mDcaParentDaughter),
  mHitDistanceParentDaughter(k.mHitDistanceParentDaughter),
  mHitDistanceParentVertex(k.mHitDistanceParentVertex),
  mDecayAngle(k.mDecayAngle),
  mDecayAngleCM(k.mDecayAngleCM),
  mDaughter(k.mDaughter),
  mParent(k.mParent),
  mPositionX(k.mPositionX),
  mPositionY(k.mPositionY),
  mPositionZ(k.mPositionZ) {

  memcpy( mDeltaEnergy, k.mDeltaEnergy, sizeof(mDeltaEnergy) );
}

//_________________
StHbtKink& StHbtKink::operator=(const StHbtKink &k) {

  if( this != &k ) {

    mDcaParentDaughter         = k.mDcaParentDaughter;
    mHitDistanceParentDaughter = k.mHitDistanceParentDaughter;
    mHitDistanceParentVertex   = k.mHitDistanceParentVertex;
    mDeltaEnergy[0]            = k.mDeltaEnergy[0];
    mDeltaEnergy[1]            = k.mDeltaEnergy[1];
    mDeltaEnergy[2]            = k.mDeltaEnergy[2];
    mDecayAngle                = k.mDecayAngle;
    mDecayAngleCM              = k.mDecayAngleCM;
    mDaughter                  = k.mDaughter;
    mParent                    = k.mParent;
    mPositionX                 = k.mPositionX;
    mPositionY                 = k.mPositionY;
    mPositionZ                 = k.mPositionZ;
  }

  return *this;
}

//_________________
StHbtKink::~StHbtKink() {
  /* empty */
}

//_________________
void StHbtKink::setDaugherHbtTrack(const StHbtTrack& trk) {
  mDaughter = trk;
}

//_________________
void StHbtKink::setParetntHbtTrack(const StHbtTrack& trk) {
  mParent = trk;
}
