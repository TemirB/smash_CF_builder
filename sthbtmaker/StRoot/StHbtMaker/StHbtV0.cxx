//
// A special type of particle dealing with the V0
//

// C++ headers
#include <utility>

// StHbtMaker headers
#include "StHbtV0.h"

// ROOT headers
#include "TLorentzVector.h"

#ifdef __ROOT__
ClassImp(StHbtV0)
#endif

//_________________
StHbtV0::StHbtV0() :
  mPrimaryVertexX(0), mPrimaryVertexY(0), mPrimaryVertexZ(0),
  mV0DecayPointX(0), mV0DecayPointY(0), mV0DecayPointZ(0),
  mV0MomX(0), mV0MomY(0), mV0MomZ(0), mV0PtotPos(0), mV0PtotNeg(0), mV0DcaDaughters(0),
  mV0DcaToPrimVertex(0), mChi2V0(0), mClV0(0), mAlphaV0(0), mPtArmV0(0),
  mPosId(0), mPosMomX(0), mPosMomY(0), mPosMomZ(0),
  mPosDca2PrimVertexX(0), mPosDca2PrimVertexY(0), mPosDca2PrimVertexZ(0),
  mPosNHits(0), mPosNHitsPoss(0), mPosNHitsDedx(0), mPosTopologyMap{},
  mPosChi2(0), mPosDedx(0), mPosNSigmaElectron(0), mPosNSigmaPion(0),
  mPosNSigmaKaon(0), mPosNSigmaProton(0), mPosTofBeta(0),
  mNegId(0), mNegMomX(0), mNegMomY(0), mNegMomZ(0),
  mNegDca2PrimVertexX(0), mNegDca2PrimVertexY(0), mNegDca2PrimVertexZ(0),
  mNegNHits(0), mNegNHitsPoss(0), mNegNHitsDedx(0), mNegTopologyMap{},
  mNegChi2(0), mNegDedx(0), mNegNSigmaElectron(0), mNegNSigmaPion(0),
  mNegNSigmaKaon(0), mNegNSigmaProton(0), mNegTofBeta(0), mHiddenInfo(nullptr) {
  /* no-op */
}

//_________________
StHbtV0::StHbtV0(const StHbtV0& v) {
  // Copy constructor

  // Copy V0 information
  mPrimaryVertexX = v.mPrimaryVertexX;
  mPrimaryVertexY = v.mPrimaryVertexY;
  mPrimaryVertexZ = v.mPrimaryVertexZ;
  mV0DecayPointX = v.mV0DecayPointX;
  mV0DecayPointY = v.mV0DecayPointY;
  mV0DecayPointZ = v.mV0DecayPointZ;
  mV0PtotPos = v.mV0PtotPos;
  mV0PtotNeg = v.mV0PtotNeg;
  mV0DcaDaughters = v.mV0DcaDaughters;
  mV0DcaToPrimVertex = v.mV0DcaToPrimVertex;
  mChi2V0 = v.mChi2V0;
  mClV0 = v.mClV0;
  mAlphaV0 = v.mAlphaV0;
  mPtArmV0 = v.mPtArmV0;

  // Copy positive daughter information
  mPosId = v.mPosId;
  mPosMomX = v.mPosMomX;
  mPosMomY = v.mPosMomY;
  mPosMomZ = v.mPosMomZ;
  mPosDca2PrimVertexX = v.mPosDca2PrimVertexX;
  mPosDca2PrimVertexY = v.mPosDca2PrimVertexY;
  mPosDca2PrimVertexZ = v.mPosDca2PrimVertexZ;
  mPosNHits = v.mPosNHits;
  mPosNHitsPoss = v.mPosNHitsPoss;
  mPosNHitsDedx = v.mPosNHitsDedx;
  mPosTopologyMap[0] = v.mPosTopologyMap[0];
  mPosTopologyMap[1] = v.mPosTopologyMap[1];
  mPosChi2 = v.mPosChi2;
  mPosDedx = v.mPosDedx;
  mPosNSigmaElectron = v.mPosNSigmaElectron;
  mPosNSigmaPion = v.mPosNSigmaPion;
  mPosNSigmaKaon = v.mPosNSigmaKaon;
  mPosNSigmaProton = v.mPosNSigmaProton;
  mPosTofBeta = v.mPosTofBeta;

  // Copy negative daughter information
  mNegId = v.mNegId;
  mNegMomX = v.mNegMomX;
  mNegMomY = v.mNegMomY;
  mNegMomZ = v.mNegMomZ;
  mNegDca2PrimVertexX = v.mNegDca2PrimVertexX;
  mNegDca2PrimVertexY = v.mNegDca2PrimVertexY;
  mNegDca2PrimVertexZ = v.mNegDca2PrimVertexZ;
  mNegNHits = v.mNegNHits;
  mNegNHitsPoss = v.mNegNHitsPoss;
  mNegNHitsDedx = v.mNegNHitsDedx;
  mNegTopologyMap[0] = v.mNegTopologyMap[0];
  mNegTopologyMap[1] = v.mNegTopologyMap[1];
  mNegChi2 = v.mNegChi2;
  mNegDedx = v.mNegDedx;
  mNegNSigmaElectron = v.mNegNSigmaElectron;
  mNegNSigmaPion = v.mNegNSigmaPion;
  mNegNSigmaKaon = v.mNegNSigmaKaon;
  mNegNSigmaProton = v.mNegNSigmaProton;
  mNegTofBeta = v.mNegTofBeta;

  // Copy theoretical part
  if( mHiddenInfo ) delete mHiddenInfo;
  mHiddenInfo = v.mHiddenInfo ? v.mHiddenInfo->clone() : nullptr;

  updateV0();
}

//_________________
StHbtV0& StHbtV0::operator=(const StHbtV0& v0) {
  // Assignment operator
  if ( this != &v0 ) {
    // V0 information
    mPrimaryVertexX = v0.mPrimaryVertexX;
    mPrimaryVertexY = v0.mPrimaryVertexY;
    mPrimaryVertexZ = v0.mPrimaryVertexZ;
    mBField = v0.mBField;
    mV0DecayPointX = v0.mV0DecayPointX;
    mV0DecayPointY = v0.mV0DecayPointY;
    mV0DecayPointZ = v0.mV0DecayPointZ;
    mV0MomX = v0.mV0MomX;
    mV0MomY = v0.mV0MomY;
    mV0MomZ = v0.mV0MomZ;
    mV0PtotPos = v0.mV0PtotPos;
    mV0PtotNeg = v0.mV0PtotNeg;
    mV0DcaDaughters = v0.mV0DcaDaughters;
    mV0DcaToPrimVertex = v0.mV0DcaToPrimVertex;
    mChi2V0 = v0.mChi2V0;
    mClV0 = v0.mClV0;
    mAlphaV0 = v0.mAlphaV0;
    mPtArmV0 = mPtArmV0;

    // Positive daughter
    mPosId = v0.mPosId;
    mPosMomX = v0.mPosMomX;
    mPosMomY = v0.mPosMomY;
    mPosMomZ = v0.mPosMomZ;
    mPosDca2PrimVertexX = v0.mPosDca2PrimVertexX;
    mPosDca2PrimVertexY = v0.mPosDca2PrimVertexY;
    mPosDca2PrimVertexZ = v0.mPosDca2PrimVertexZ;
    mPosNHits = v0.mPosNHits;
    mPosNHitsPoss = v0.mPosNHitsPoss;
    mPosNHitsDedx = v0.mPosNHitsDedx;
    mPosTopologyMap[0] = v0.mPosTopologyMap[0];
    mPosTopologyMap[1] = v0.mPosTopologyMap[1];
    mPosChi2 = v0.mPosChi2;
    mPosDedx = v0.mPosDedx;
    mPosNSigmaElectron = v0.mPosNSigmaElectron;
    mPosNSigmaPion = v0.mPosNSigmaPion;
    mPosNSigmaKaon = v0.mPosNSigmaKaon;
    mPosNSigmaProton = v0.mPosNSigmaProton;
    mPosTofBeta = v0.mPosTofBeta;

    // Negative daughter
    mNegId = v0.mNegId;
    mNegMomX = v0.mNegMomX;
    mNegMomY = v0.mNegMomY;
    mNegMomZ = v0.mNegMomZ;
    mNegDca2PrimVertexX = v0.mNegDca2PrimVertexX;
    mNegDca2PrimVertexY = v0.mNegDca2PrimVertexY;
    mNegDca2PrimVertexZ = v0.mNegDca2PrimVertexZ;
    mNegNHits = v0.mNegNHits;
    mNegNHitsPoss = v0.mNegNHitsPoss;
    mNegNHitsDedx = v0.mNegNHitsDedx;
    mNegTopologyMap[0] = v0.mNegTopologyMap[0];
    mNegTopologyMap[1] = v0.mNegTopologyMap[1];
    mNegChi2 = v0.mNegChi2;
    mNegDedx = v0.mNegDedx;
    mNegNSigmaElectron = v0.mNegNSigmaElectron;
    mNegNSigmaPion = v0.mNegNSigmaPion;
    mNegNSigmaKaon = v0.mNegNSigmaKaon;
    mNegNSigmaProton = v0.mNegNSigmaProton;
    mNegTofBeta = v0.mNegTofBeta;

    if( mHiddenInfo ) delete mHiddenInfo;
    mHiddenInfo = (v0.mHiddenInfo) ? v0.mHiddenInfo->clone() : nullptr;

    updateV0();
  }

  return *this;
}

//_________________
StHbtV0::~StHbtV0() {
  // Destructor
  if(mHiddenInfo) {
    delete mHiddenInfo;
  }
}

//_________________
void StHbtV0::updateV0() {

  // Retrieve positive and negative particle helices
  StHbtPhysicalHelix posHelix = helixPos();
  StHbtPhysicalHelix negHelix = helixNeg();
  // Find DCA between two helices
  std::pair<double, double> length = posHelix.pathLength( negHelix );

  // Search for the decay point
  TVector3 positionAtDCAPos = posHelix.at( length.first );
  TVector3 positionAtDCANeg = negHelix.at( length.second );
  TVector3 vectorAtDCA = positionAtDCAPos - positionAtDCANeg;
  // DCA between positive and negative tracks at decay point
  mV0DcaDaughters = vectorAtDCA.Mag();

  // Obtain V0 decay point coordinates
  TVector3 v0DecayPoint = (positionAtDCAPos + positionAtDCANeg) * 0.5;
  mV0DecayPointX = v0DecayPoint.X();
  mV0DecayPointY = v0DecayPoint.Y();
  mV0DecayPointZ = v0DecayPoint.Z();

  // Momentum of daughters at DCA to V0 decay point
  TVector3 momAtDecayPointPos = posHelix.momentumAt( length.first, mBField*kilogauss );
  TVector3 momAtDecayPointNeg = negHelix.momentumAt( length.second, mBField*kilogauss );
  mV0PtotPos = momAtDecayPointPos.Mag();
  mV0PtotNeg = momAtDecayPointNeg.Mag();

  // Momentum of V0 at decay point
  mV0MomX = momAtDecayPointPos.X() + momAtDecayPointNeg.X();
  mV0MomY = momAtDecayPointPos.Y() + momAtDecayPointNeg.Y();
  mV0MomZ = momAtDecayPointPos.Z() + momAtDecayPointNeg.Z();

  // Obtain DCA of V0 to primary vertex
  float angle = v0DecayVector().Angle( momV0() );
  mV0DcaToPrimVertex = v0DecayLength() * TMath::Sin( angle );

  // Calculating Podolianski-Armenteros parameters
  float momPosAlongV0 = momAtDecayPointPos * momV0() / ptotV0();
  float momNegAlongV0 = momAtDecayPointNeg * momV0() / ptotV0();
  mAlphaV0 = ( momPosAlongV0 - momNegAlongV0) / ( momPosAlongV0 + momNegAlongV0 );
  mPtArmV0 = TMath::Sqrt( mV0PtotPos*mV0PtotPos - momPosAlongV0*momPosAlongV0 );
}

//_________________
float StHbtV0::rapidityPhi() const {
  TLorentzVector fourVector( momV0X(), momV0Y(), momV0Z(), ePhi() );
  return fourVector.Rapidity();
}

//_________________
float StHbtV0::rapidityLambda() const {
  TLorentzVector fourVector( momV0X(), momV0Y(), momV0Z(), eLambda() );
  return fourVector.Rapidity();
}

//_________________
float StHbtV0::rapidityK0Short() const {
  TLorentzVector fourVector( momV0X(), momV0Y(), momV0Z(), eK0Short() );
  return fourVector.Rapidity();
}

//_________________
StHbtPhysicalHelix StHbtV0::helixPos() const {
  return StHbtPhysicalHelix( momPos(), originPos(),
			     bField() * kilogauss,
			     static_cast<float>( 1 ) );
}

//_________________
void StHbtV0::setNSigmaElectronPos(const float& ns) {
  mPosNSigmaElectron = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
			 std::numeric_limits<short>::max() :
			 (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setNSigmaPionPos(const float& ns) {
  mPosNSigmaPion = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
		     std::numeric_limits<short>::max() :
		     (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setNSigmaKaonPos(const float& ns) {
  mPosNSigmaKaon = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
		     std::numeric_limits<short>::max() :
		     (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setNSigmaProtonPos(const float& ns) {
  mPosNSigmaProton = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
		       std::numeric_limits<short>::max() :
		       (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setTofBetaPos(const float& beta) {
  if( beta < 0 ) {
    mPosTofBeta = 0;
  }
  else {
    mPosTofBeta = ( ( beta * 20000. ) > std::numeric_limits<unsigned short>::max() ?
		    std::numeric_limits<unsigned short>::max() :
		    (unsigned short)( beta * 20000.f ) );
  }
}

//_________________
StHbtPhysicalHelix StHbtV0::helixNeg() const {
  return StHbtPhysicalHelix( momPos(), originNeg(),
			     bField() * kilogauss,
			     static_cast<float>( -1 ) );
}

//_________________
void StHbtV0::setNSigmaElectronNeg(const float& ns) {
  mNegNSigmaElectron = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
			 std::numeric_limits<short>::max() :
			 (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setNSigmaPionNeg(const float& ns) {
  mNegNSigmaPion = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
		     std::numeric_limits<short>::max() :
		     (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setNSigmaKaonNeg(const float& ns) {
  mNegNSigmaKaon = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
		     std::numeric_limits<short>::max() :
		     (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setNSigmaProtonNeg(const float& ns) {
  mNegNSigmaProton = ( TMath::Abs(ns * 1000.f) > std::numeric_limits<short>::max() ?
		       std::numeric_limits<short>::max() :
		       (short)(ns * 1000.f) );
}

//_________________
void StHbtV0::setTofBetaNeg(const float& beta) {
  if( beta < 0 ) {
    mNegTofBeta = 0;
  }
  else {
    mNegTofBeta = ( (beta * 20000.f) > std::numeric_limits<unsigned short>::max() ?
		    std::numeric_limits<unsigned short>::max() :
		    (unsigned short)( beta * 20000.f ) );
  }
}

//_________________
void StHbtV0::setChi2V0(const float& chi2) {
  if( chi2 < 0 ) {
    mChi2V0 = chi2;
  }
  else {
    mChi2V0 = ( (chi2 * 10.f) > std::numeric_limits<unsigned char>::max() ?
		std::numeric_limits<unsigned char>::max() :
		(unsigned char)(chi2 * 10.f) );
  }
}
