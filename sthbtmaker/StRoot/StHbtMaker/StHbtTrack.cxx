//
// Main class holding track information
//

// StHbtMaker headers
#include "StHbtTrack.h"
#include "phys_constants.h"

//________________
StHbtTrack::StHbtTrack() :
  mId(0), mFlag(0), mNHits(0), mNHitsPoss(0), mNHitsDedx(0), mChi2(0), mDedx(0),
  mNSigmaElectron(-30), mNSigmaPion(-30), mNSigmaKaon(-30), mNSigmaProton(-30),
  mPidProbElectron(0), mPidProbPion(0), mPidProbKaon(0), mPidProbProton(0),
  mMap{}, mTofBeta(0),
  mPrimaryPx(0), mPrimaryPy(0), mPrimaryPz(0), mGlobalPx(0), mGlobalPy(0), mGlobalPz(0),
  mDcaX(-999), mDcaY(-999), mDcaZ(-999),
  mPrimaryVertexX(0), mPrimaryVertexY(0), mPrimaryVertexZ(0), mBField(0),
  /* mXfr(0), mYfr(0), mZfr(0), mTfr(0), mPdgId(0), */
  mHiddenInfo(nullptr) {
  // Default constructor
}

//________________
StHbtTrack::StHbtTrack(const StHbtTrack& t) {

  // Copy constructor
  mId = t.mId;
  mFlag = t.mFlag;
  mNHits = t.mNHits;
  mNHitsPoss = t.mNHitsPoss;
  mNHitsDedx = t.mNHitsDedx;
  mChi2 = t.mChi2;
  mDedx = t.mDedx;
  mNSigmaElectron = t.mNSigmaElectron;
  mNSigmaPion = t.mNSigmaPion;
  mNSigmaKaon = t.mNSigmaKaon;
  mNSigmaProton = t.mNSigmaProton;
  mPidProbElectron = t.mPidProbElectron;
  mPidProbPion = t.mPidProbPion;
  mPidProbKaon = t.mPidProbKaon;
  mPidProbProton = t.mPidProbProton;
  mDcaX = t.mDcaX; 
  mDcaY = t.mDcaY; 
  mDcaZ = t.mDcaZ;
  mMap[0] = t.mMap[0]; 
  mMap[1] = t.mMap[1];
  mTofBeta = t.mTofBeta;
  mPrimaryPx = t.mPrimaryPx;
  mPrimaryPy = t.mPrimaryPy;
  mPrimaryPz = t.mPrimaryPz;
  mGlobalPx = t.mGlobalPx;
  mGlobalPy = t.mGlobalPy;
  mGlobalPz = t.mGlobalPz;
  mPrimaryVertexX = t.mPrimaryVertexX;
  mPrimaryVertexY = t.mPrimaryVertexY;
  mPrimaryVertexZ = t.mPrimaryVertexZ;
  mBField = t.mBField;
  /*
  mXfr = t.mXfr;
  mYfr = t.mYfr;
  mZfr = t.mZfr;
  mTfr = t.mTfr;
  mPdgId = t.mPdgId;
  */

  if ( t.validHiddenInfo() ) {
    mHiddenInfo = t.getHiddenInfo()->clone();
  }
  else {
    mHiddenInfo = nullptr;
  }
}

//_________________
StHbtTrack& StHbtTrack::operator=(const StHbtTrack& trk) {

  // Assignment operator
  if( this != &trk ) {
    mId = trk.mId;
    mFlag = trk.mFlag;
    mNHits = trk.mNHits;
    mNHitsPoss = trk.mNHitsPoss;
    mNHitsDedx = trk.mNHitsDedx;
    mChi2 = trk.mChi2;
    mDedx = trk.mDedx;
    mNSigmaElectron = trk.mNSigmaElectron;
    mNSigmaPion = trk.mNSigmaPion;
    mNSigmaKaon = trk.mNSigmaKaon;
    mNSigmaProton = trk.mNSigmaProton;
    mPidProbElectron = trk.mPidProbElectron;
    mPidProbPion = trk.mPidProbPion;
    mPidProbKaon = trk.mPidProbKaon;
    mPidProbProton = trk.mPidProbProton;
    mMap[0] = trk.mMap[0];
    mMap[1] = trk.mMap[1];
    mTofBeta = trk.mTofBeta;
    mPrimaryPx = trk.mPrimaryPx;
    mPrimaryPy = trk.mPrimaryPy;
    mPrimaryPz = trk.mPrimaryPz;
    mGlobalPx = trk.mGlobalPx;
    mGlobalPy = trk.mGlobalPy;
    mGlobalPz = trk.mGlobalPz;
    mDcaX = trk.mDcaX;
    mDcaY = trk.mDcaY;
    mDcaZ = trk.mDcaZ;
    mPrimaryVertexX = trk.mPrimaryVertexX;
    mPrimaryVertexY = trk.mPrimaryVertexY;
    mPrimaryVertexZ = trk.mPrimaryVertexZ;
    mBField = trk.mBField;

    /*
    mXfr = trk.mXfr;
    mYfr = trk.mYfr;
    mZfr = trk.mZfr;
    mTfr = trk.mTfr;
    mPdgId = trk.mPdgId;
    */

    if(mHiddenInfo) delete mHiddenInfo;
    mHiddenInfo = trk.validHiddenInfo() ? trk.getHiddenInfo()->clone() : nullptr;
  }

  return *this;
}

//_________________
StHbtTrack::~StHbtTrack() {
  if (mHiddenInfo) delete mHiddenInfo;
}

//_________________
float StHbtTrack::massSqr() const {
  // Set squared mass
  float massSqr = -999.;
  if( isPrimary() && isTofTrack() ) {
    massSqr = ptot2() * ( invBeta2() - 1.);
  }
  return massSqr;
}

//_________________
void StHbtTrack::setNSigmaElectron(const float& ns) {
  // Set nSigma(e)
  mNSigmaElectron = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
                     ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
                     (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setNSigmaPion(const float& ns) {
  // Set nSigma(pi)
  mNSigmaPion = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
                 ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
                 (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setNSigmaKaon(const float& ns) {
  // Set nSigma(K)
  mNSigmaKaon = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
                 ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
                 (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setNSigmaProton(const float& ns) {
  // Set nSigma(p)
  mNSigmaProton = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
                   ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
                   (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setChi2(const float& x) {
  // Set chi2
  if ( x < 0 ) {
    mChi2 = 0;
  }
  else {
    mChi2 = ( ( x * 1000.) > std::numeric_limits<unsigned short>::max() ?
	      std::numeric_limits<unsigned short>::max() :
	      (unsigned short)( x * 1000.) );
  }
}

//_________________
void StHbtTrack::setPidProbElectron(const float& prob) {
  // Set probability(e)
  if ( prob<0 ) {
    mPidProbElectron = 0;
  }
  else {
    mPidProbElectron = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
			 std::numeric_limits<unsigned short>::max() :
			 (unsigned short)(prob * 10000.) );
  }
}

//_________________
void StHbtTrack::setPidProbPion(const float& prob) {
  // Set probability(pi)
  if( prob < 0 ) {
    mPidProbPion = 0;
  }
  else {
    mPidProbPion = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
		     std::numeric_limits<unsigned short>::max() :
		     (unsigned short)(prob * 10000.) );
  }
}

//_________________
void StHbtTrack::setPidProbKaon(const float& prob) {
  // Set probability(K)
  if( prob < 0 ) {
    mPidProbKaon = 0;
  }
  else {
    mPidProbKaon = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
		     std::numeric_limits<unsigned short>::max() :
		     (unsigned short)(prob * 10000.) );
  }
}

//_________________
void StHbtTrack::setPidProbProton(const float& prob) {
  // Set probability(p)
  if( prob < 0 ) {
    mPidProbProton = 0;
  }
  else {
    mPidProbProton = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
		       std::numeric_limits<unsigned short>::max() :
		       (unsigned short)(prob * 10000.) );
  }
}

//_________________
void StHbtTrack::setDedx(const double& dEdx) {
  // Set dE/dx (from GeV/cm)
  if( dEdx < 0 ) {
    mDedx = 0;
  }
  else {
    mDedx = ( (dEdx * 1e9) > std::numeric_limits<unsigned short>::max() ?
             std::numeric_limits<unsigned short>::max() :
             (unsigned short)(dEdx * 1e9) );
  }
}

//_________________
void StHbtTrack::setDedxFromKeV(const double& dEdx) {
  // Set dE/dx (from keV/cm)
  if( dEdx < 0 ) {
    mDedx = 0;
  }
  else {
    mDedx = ( (dEdx * 1e3) > std::numeric_limits<unsigned short>::max() ?
             std::numeric_limits<unsigned short>::max() :
             (unsigned short)(dEdx * 1e3) );
  }
}

//_________________
void StHbtTrack::setBeta(const float& beta) {
  // Set relativistik velocity (from TOF)
  // Zero means there is no signal in TOF (track did not match TOF)
  if( beta <= 0 ) {
    mTofBeta = 0;
  }
  else {
    mTofBeta = ( (beta * 20000.) > std::numeric_limits<unsigned short>::max() ?
                std::numeric_limits<unsigned short>::max() :
                (unsigned short)(beta * 20000.) );
  }
}

//_________________
StHbtPhysicalHelix StHbtTrack::helix() const {
  // Return helix of the primary track
  return StHbtPhysicalHelix( pMom(), primaryVertex(),
                            mBField * kilogauss,
                            static_cast<float>( charge() ) );
}

//_________________
StHbtPhysicalHelix StHbtTrack::gHelix() const {
  // Return helix of the global track
  return StHbtPhysicalHelix( gMom(), origin(),
                            mBField * kilogauss,
                            static_cast<float>( charge() ) );
}

//_________________
float StHbtTrack::invBetaDiffElectron() const {
  // Calculate 1/beta-1/beta(electron) for TOF-matched primary track
  if ( isPrimary() && isTofTrack() ) {
    return ( invBeta() - TMath::Sqrt( M_ELECTRON*M_ELECTRON + pMom().Mag2() ) / pMom().Mag() );
  }
  else {
    return -999.;
  }
}

//_________________
float StHbtTrack::invBetaDiffPion() const {
  // Calculate 1/beta-1/beta(pion) for TOF-matched primary track
  if ( isPrimary() && isTofTrack() ) {
    return ( invBeta() - TMath::Sqrt( M_PION_PLUS*M_PION_PLUS + pMom().Mag2() ) / pMom().Mag() );
  }
  else {
    return -999.;
  }
}

//_________________
float StHbtTrack::invBetaDiffKaon() const {
  // Calculate 1/beta-1/beta(kaon) for TOF-matched primary track
  if ( isPrimary() && isTofTrack() ) {
    return ( invBeta() - TMath::Sqrt( M_KAON_PLUS*M_KAON_PLUS + pMom().Mag2() ) / pMom().Mag() );
  }
  else {
    return -999.;
  }
}

//_________________
float StHbtTrack::invBetaDiffProton() const {
  // Calculate 1/beta-1/beta(proton) for TOF-matched primary track
  if ( isPrimary() && isTofTrack() ) {
    return ( invBeta() - TMath::Sqrt( M_PROTON*M_PROTON + pMom().Mag2() ) / pMom().Mag() );
  }
  else {
    return -999.;
  }
}
