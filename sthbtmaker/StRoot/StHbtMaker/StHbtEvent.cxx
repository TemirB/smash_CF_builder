//
// StHbtEvent holds the event information specific and particle collections
//

// StHbtMaker headers
// Infrastructure
#include "StHbtEvent.h"
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "StHbtXi.h"
#include "StHbtKink.h"
#include "PhysicalConstants.h"
#include "SystemOfUnits.h"
// Base
#include "StHbtBaseTrackCut.h"
#include "StHbtBaseV0Cut.h"
#include "StHbtBaseXiCut.h"
#include "StHbtBaseKinkCut.h"
#ifdef __ROOT__
ClassImp(StHbtEvent)
#endif

//_________________
StHbtEvent::StHbtEvent() :
  mEventNumber(0), mRunNumber(0), mMagneticField(0),
  mRefMult(0), mRefMultPos(0), mRefMultCorr(0),
  mRefMultCorrWeight(0), mRefMult2(0), mRefMult2Pos(0),
  mGRefMult(0), mGRefMultPos(0), mBTofTrayMultiplicity(0),
  mNBTOFMatch(0), mNBEMCMatch(0), mNumberOfPrimaryTracks(0),
  mNumberOfGlobalTracks(0), mZdcSumAdcEast(0), mZdcSumAdcWest(0),
  mZdcCoincidenceRate(0), mBbcCoincidenceRate(0), mSphericity(-1), mSphericity2(-1),
  mEventPlaneAngle( 0 ), mEventPlaneResolution( 0 ), mCent16(-1),
  mPrimaryVertexPositionX(-999), mPrimaryVertexPositionY(-999), mPrimaryVertexPositionZ(-999),
  mVpdVz(0), mRanking(-1e5), mImpactPar(0) {

  if( !mTriggerIds.empty() ) mTriggerIds.clear();

  // Default constuctor
  mTrackCollection = new StHbtTrackCollection;
  mV0Collection = new StHbtV0Collection;
  mXiCollection = new StHbtXiCollection;
  mKinkCollection = new StHbtKinkCollection;
}

//___________________
StHbtEvent::StHbtEvent(const StHbtEvent& ev, StHbtBaseTrackCut* tCut,
                       StHbtBaseV0Cut* vCut, StHbtBaseXiCut* xCut,
                       StHbtBaseKinkCut* kCut) {

  // Copy constructor with track and v0 cuts
  mEventNumber = ev.mEventNumber;
  mRunNumber = ev.mRunNumber;
  mMagneticField = ev.mMagneticField;

  mRefMult = ev.mRefMult;
  mRefMultPos = ev.mRefMultPos;
  mRefMultCorr = ev.mRefMultCorr;
  mRefMultCorrWeight = ev.mRefMultCorrWeight;
  mRefMult2 = ev.mRefMult2;
  mRefMult2Pos = ev.mRefMult2Pos;
  mGRefMult = ev.mGRefMult;
  mGRefMultPos = ev.mGRefMultPos;
  mBTofTrayMultiplicity = ev.mBTofTrayMultiplicity;
  mNBTOFMatch = ev.mNBTOFMatch;
  mNBEMCMatch = ev.mNBEMCMatch;
  mNumberOfPrimaryTracks = ev.mNumberOfPrimaryTracks;
  mNumberOfGlobalTracks = ev.mNumberOfGlobalTracks;
  mZdcSumAdcEast = ev.mZdcSumAdcEast;
  mZdcSumAdcWest = ev.mZdcSumAdcWest;
  mZdcCoincidenceRate = ev.mZdcCoincidenceRate;
  mBbcCoincidenceRate = ev.mBbcCoincidenceRate;

  mSphericity = ev.mSphericity;
  mSphericity2 = ev.mSphericity2;
  mEventPlaneAngle = ev.mEventPlaneAngle;
  mEventPlaneResolution = ev.mEventPlaneResolution;
  mCent16 = ev.mCent16;

  mPrimaryVertexPositionX = ev.mPrimaryVertexPositionX;
  mPrimaryVertexPositionY = ev.mPrimaryVertexPositionY;
  mPrimaryVertexPositionZ = ev.mPrimaryVertexPositionZ;
  mVpdVz = ev.mVpdVz;
  mRanking = ev.mRanking;
  mImpactPar = ev.mImpactPar;
  mTriggerIds = ev.mTriggerIds;

  // Create empty collections
  mTrackCollection = new StHbtTrackCollection;
  mV0Collection = new StHbtV0Collection;
  mXiCollection = new StHbtXiCollection;
  mKinkCollection = new StHbtKinkCollection;

  // Copy tracks from one collection to the another one
  for ( StHbtTrackIterator tIter=ev.mTrackCollection->begin();
	tIter!=ev.mTrackCollection->end(); tIter++) {
    if ( !tCut || tCut->pass(*tIter) ) {
      StHbtTrack* trackCopy = new StHbtTrack(**tIter);
      mTrackCollection->push_back(trackCopy);
    }
  }

  // Copy V0s from one collection to the another one
  for ( StHbtV0Iterator vIter=ev.mV0Collection->begin();
	vIter!=ev.mV0Collection->end(); vIter++) {
    if ( !vCut || vCut->pass(*vIter) ) {
      StHbtV0* v0Copy = new StHbtV0(**vIter);
      mV0Collection->push_back(v0Copy);
    }
  }

  // Copy Xis from one collection to the another one
  for ( StHbtXiIterator xIter=ev.mXiCollection->begin();
	xIter!=ev.mXiCollection->end(); xIter++) {
    if ( !xCut || xCut->pass(*xIter) ) {
      StHbtXi* xiCopy = new StHbtXi(**xIter);
      mXiCollection->push_back(xiCopy);
    }
  }

  // Copy kinks from one collection to the another one
  for ( StHbtKinkIterator kIter=ev.mKinkCollection->begin();
	kIter!=ev.mKinkCollection->end(); kIter++) {
    if ( !kCut || kCut->pass(*kIter) ) {
      StHbtKink* kinkCopy = new StHbtKink(**kIter);
      mKinkCollection->push_back(kinkCopy);
    }
  }
}

//_________________
StHbtEvent& StHbtEvent::operator=(const StHbtEvent& ev) {

  // Assignment operator
  if ( this != &ev ) {
    mEventNumber = ev.mEventNumber;
    mRunNumber = ev.mRunNumber;
    mMagneticField = ev.mMagneticField;

    mRefMult = ev.mRefMult;
    mRefMultPos = ev.mRefMultPos;
    mRefMultCorr = ev.mRefMultCorr;
    mRefMultCorrWeight = ev.mRefMultCorrWeight;
    mRefMult2 = ev.mRefMult2;
    mRefMult2Pos = ev.mRefMult2Pos;
    mGRefMult = ev.mGRefMult;
    mGRefMultPos = ev.mGRefMultPos;
    mBTofTrayMultiplicity = ev.mBTofTrayMultiplicity;
    mNBTOFMatch = ev.mNBTOFMatch;
    mNBEMCMatch = ev.mNBEMCMatch;
    mNumberOfPrimaryTracks = ev.mNumberOfPrimaryTracks;
    mNumberOfGlobalTracks = ev.mNumberOfGlobalTracks;
    mZdcSumAdcEast = ev.mZdcSumAdcEast;
    mZdcSumAdcWest = ev.mZdcSumAdcWest;
    mZdcCoincidenceRate = ev.mZdcCoincidenceRate;
    mBbcCoincidenceRate = ev.mBbcCoincidenceRate;
    mSphericity = ev.mSphericity;
    mSphericity2 = ev.mSphericity2;
    mEventPlaneAngle = ev.mEventPlaneAngle;
    mEventPlaneResolution = ev.mEventPlaneResolution;
    mCent16 = ev.mCent16;
    mPrimaryVertexPositionX = ev.mPrimaryVertexPositionX;
    mPrimaryVertexPositionY = ev.mPrimaryVertexPositionY;
    mPrimaryVertexPositionZ = ev.mPrimaryVertexPositionZ;
    mRanking = ev.mRanking;
    mImpactPar = ev.mImpactPar;

    for(unsigned int iIter=0; iIter<ev.mTriggerIds.size(); iIter++) {
      mTriggerIds.push_back( ev.mTriggerIds.at(iIter) );
    }

    // Clear collections if exist
    if( mTrackCollection ) {
      for( StHbtTrackIterator iter=mTrackCollection->begin();
	         iter!=mTrackCollection->end(); iter++ ) {
	            delete *iter;
      }
      mTrackCollection->clear();
    }
    else {
      mTrackCollection = new StHbtTrackCollection;
    }

    if( mV0Collection ) {
      for( StHbtV0Iterator iter=mV0Collection->begin();
	         iter!=mV0Collection->end(); iter++ ) {
	            delete *iter;
      }
      mV0Collection->clear();
    }
    else {
      mV0Collection = new StHbtV0Collection;
    }

    if( mKinkCollection ) {
      for( StHbtKinkIterator iter=mKinkCollection->begin();
	         iter!=mKinkCollection->end(); iter++ ) {
	            delete *iter;
      }
      mKinkCollection->clear();
    }
    else {
      mKinkCollection = new StHbtKinkCollection;
    }

    if( mXiCollection ) {
      for( StHbtXiIterator iter=mXiCollection->begin();
	         iter!=mXiCollection->end(); iter++ ) {
	            delete *iter;
      }
      mXiCollection->clear();
    }
    else {
      mXiCollection = new StHbtXiCollection;
    }

    // Copy collections
    for (StHbtTrackIterator iIter=ev.mTrackCollection->begin();
	       iIter!=ev.mTrackCollection->end(); iIter++) {
      StHbtTrack *trackCopy = new StHbtTrack( **iIter );
      mTrackCollection->push_back( trackCopy );
    }

    for (StHbtV0Iterator iIter=ev.mV0Collection->begin();
	       iIter!=ev.mV0Collection->end(); iIter++) {
      StHbtV0 *v0Copy = new StHbtV0( **iIter );
      mV0Collection->push_back( v0Copy );
    }

    for (StHbtKinkIterator iIter=ev.mKinkCollection->begin();
	       iIter!=ev.mKinkCollection->end(); iIter++) {
      StHbtKink *kinkCopy = new StHbtKink( **iIter );
      mKinkCollection->push_back( kinkCopy );
    }

    for (StHbtXiIterator iIter=ev.mXiCollection->begin();
	       iIter!=ev.mXiCollection->end(); iIter++) {
      StHbtXi *xiCopy = new StHbtXi( **iIter );
      mXiCollection->push_back( xiCopy );
    }
  } //if ( this != &ev )

  return *this;
}

//___________________
StHbtEvent::~StHbtEvent() {

  // Remove track collection
  for (StHbtTrackIterator iter=mTrackCollection->begin();
       iter!=mTrackCollection->end();iter++){
    delete *iter;
  }
  mTrackCollection->clear();
  delete mTrackCollection;

  // Remove V0 collection
  for (StHbtV0Iterator V0iter=mV0Collection->begin();
       V0iter!=mV0Collection->end();V0iter++){
    delete *V0iter;
  }
  mV0Collection->clear();
  delete mV0Collection;

  // Remove Xi collection
  for (StHbtXiIterator XiIter=mXiCollection->begin();
       XiIter!=mXiCollection->end();XiIter++){
    delete *XiIter;
  }
  mXiCollection->clear();
  delete mXiCollection;

  // Remove Kink collection
  for (StHbtKinkIterator kinkIter=mKinkCollection->begin();
       kinkIter!=mKinkCollection->end();kinkIter++){
    delete *kinkIter;
  }
  mKinkCollection->clear();
  delete mKinkCollection;
}

//___________________
void StHbtEvent::rotateZ(const double& angle) {

  StHbtTrackIterator iter;
  StHbtV0Iterator V0iter;

  StHbtPhysicalHelix helix;
  TVector3 p;
  TVector3 o;

  mEventPlaneAngle += angle;
  std::cout << " StHbtEvent::rotateZ(const double angle) - angle="
	          << angle << " rad    ";
  std::cout << angle / degree << " deg " << std::endl;
  for ( iter=mTrackCollection->begin(); iter!=mTrackCollection->end(); iter++ ) {

    p = (*iter)->p();
    p.RotateZ( angle );
    (*iter)->setP(p);
  }
  for ( V0iter=mV0Collection->begin(); V0iter!=mV0Collection->end(); V0iter++ ) {

    p = (*V0iter)->decayPoint();
    p.RotateX(angle);
    (*V0iter)->setDecayPoint( p );

    p = (*V0iter)->momV0();
    p.RotateX( angle );
    (*V0iter)->setV0Mom( p );

    p = (*V0iter)->momPos();
    p.RotateX( angle );
    (*V0iter)->setMomPos( p );

    p = (*V0iter)->momNeg();
    p.RotateX( angle );
    (*V0iter)->setMomNeg( p );
  }
}

//_________________
bool StHbtEvent::isTrigger(const unsigned int& id) const {
  return std::find(mTriggerIds.begin(), mTriggerIds.end(), id) != mTriggerIds.end();
}

//_________________
short StHbtEvent::cent9() const {
  if(mCent16 == 15) {
    return 8;  //0-5%
  }
  else if(mCent16 == 14) {
    return 7;  //5-10%
  }
  else if( (mCent16 == 13) || (mCent16 == 12) ) {
    return 6;  //10-20%
  }
  else if( (mCent16 == 11) || (mCent16 == 10) ) {
    return 5;  //20-30%
  }
  else if( (mCent16 == 9) || (mCent16 == 8) ) {
    return 4;  //30-40%
  }
  else if( (mCent16 == 7) || (mCent16 == 6) ) {
    return 3;  //40-50%
  }
  else if( (mCent16 == 5) || (mCent16 == 4) ) {
    return 2;  //50-60%
  }
  else if( (mCent16 == 3) || (mCent16 == 2) ) {
    return 1;  //60-70%
  }
  else if( (mCent16 == 1) || (mCent16 == 0) ) {
    return 0;  //70-80%
  }
  else {
    return -1; //not defined
  }
}

//_________________
void StHbtEvent::addTriggerId(const unsigned int& id) {
  // Check if the trigger id is not in the mTriggerIds vector
  if ( std::find(mTriggerIds.begin(),
                 mTriggerIds.end(),
                 id) == mTriggerIds.end() ) {
    mTriggerIds.push_back(id);
  }
}

//_________________
void StHbtEvent::setSphericity(const float& sph) {
  // Set sphericity value for |eta|<0.5, nHits>10, pT>0.15 and DCA<3
  if ( sph<0 ) {
    mSphericity = -1;
  }
  else {
    mSphericity = ( (sph * 100.) > 100. ? -1. : (char)(sph * 100.) );
  }
}

//_________________
void StHbtEvent::setSphericity2(const float& sph) {
  // Set sphericity value for |eta|<0.5, nHits>10, pT>0.15 and DCA<3
  if ( sph<0 ) {
    mSphericity2 = -1;
  }
  else {
    mSphericity2 = ( (sph * 100.) > 100. ? -1. : (char)(sph * 100.) );
  }
}
