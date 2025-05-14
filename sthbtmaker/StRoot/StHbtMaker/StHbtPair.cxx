//
// Holds information about pair of particles
//

// StHbtMaker headers
#include "StHbtPair.h"

// ROOT headers
#include "TMath.h"

// C++ headers
#include <iostream>

float StHbtPair::mMaxDuInner = 0.8f;
float StHbtPair::mMaxDzInner = 3.0f;
float StHbtPair::mMaxDuOuter = 1.4f;
float StHbtPair::mMaxDzOuter = 3.2f;
float StHbtPair::mTpcRadiusMin = 60.f;   //[cm]
float StHbtPair::mTpcRadiusMax = 190.f;  //[cm]

//_________________
StHbtPair::StHbtPair() :
  mTrack1( nullptr ),
  mTrack2( nullptr ),
  mNonIdParNotCalculated(0),
  mDKSide(0),
  mDKOut(0),
  mDKLong(0),
  mCVK(0),
  mKStarCalc(0),
  mNonIdParNotCalculatedGlobal(0),
  mDKSideGlobal(0),
  mDKOutGlobal(0),
  mDKLongGlobal(0),
  mKStarCalcGlobal(0),
  mCVKGlobal(0),
  mMergingParNotCalculated(0),
  mWeightedAvSep(0),
  mFracOfMergedRow(0),
  mClosestRowAtDCA(0),
  mMergingParNotCalculatedTrkV0Pos(0),
  mFracOfMergedRowTrkV0Pos(0),
  mClosestRowAtDCATrkV0Pos(0),
  mMergingParNotCalculatedTrkV0Neg(0),
  mFracOfMergedRowTrkV0Neg(0),
  mClosestRowAtDCATrkV0Neg(0),
  mMergingParNotCalculatedV0PosV0Neg(0),
  mFracOfMergedRowV0PosV0Neg(0),
  mClosestRowAtDCAV0PosV0Neg(0),
  mMergingParNotCalculatedV0NegV0Pos(0),
  mFracOfMergedRowV0NegV0Pos(0),
  mClosestRowAtDCAV0NegV0Pos(0),
  mMergingParNotCalculatedV0PosV0Pos(0),
  mFracOfMergedRowV0PosV0Pos(0),
  mClosestRowAtDCAV0PosV0Pos(0),
  mMergingParNotCalculatedV0NegV0Neg(0),
  mFracOfMergedRowV0NegV0Neg(0),
  mClosestRowAtDCAV0NegV0Neg(0) {

  // Default constructor
  setDefaultHalfFieldMergingPar();
}

//_________________
StHbtPair::StHbtPair(StHbtParticle* a, StHbtParticle* b) :
  mTrack1(a),
  mTrack2(b),
  mNonIdParNotCalculated(0),
  mDKSide(0),
  mDKOut(0),
  mDKLong(0),
  mCVK(0),
  mKStarCalc(0),
  mNonIdParNotCalculatedGlobal(0),
  mDKSideGlobal(0),
  mDKOutGlobal(0),
  mDKLongGlobal(0),
  mKStarCalcGlobal(0),
  mCVKGlobal(0),
  mMergingParNotCalculated(0),
  mWeightedAvSep(0),
  mFracOfMergedRow(0),
  mClosestRowAtDCA(0),
  mMergingParNotCalculatedTrkV0Pos(0),
  mFracOfMergedRowTrkV0Pos(0),
  mClosestRowAtDCATrkV0Pos(0),
  mMergingParNotCalculatedTrkV0Neg(0),
  mFracOfMergedRowTrkV0Neg(0),
  mClosestRowAtDCATrkV0Neg(0),
  mMergingParNotCalculatedV0PosV0Neg(0),
  mFracOfMergedRowV0PosV0Neg(0),
  mClosestRowAtDCAV0PosV0Neg(0),
  mMergingParNotCalculatedV0NegV0Pos(0),
  mFracOfMergedRowV0NegV0Pos(0),
  mClosestRowAtDCAV0NegV0Pos(0),
  mMergingParNotCalculatedV0PosV0Pos(0),
  mFracOfMergedRowV0PosV0Pos(0),
  mClosestRowAtDCAV0PosV0Pos(0),
  mMergingParNotCalculatedV0NegV0Neg(0),
  mFracOfMergedRowV0NegV0Neg(0),
  mClosestRowAtDCAV0NegV0Neg(0) {

  // Construct pair from two particles
  setDefaultHalfFieldMergingPar();
}

//_________________
StHbtPair::StHbtPair(const StHbtPair& pair) :
  mTrack1(pair.mTrack1),
  mTrack2(pair.mTrack2),
  mNonIdParNotCalculated(pair.mNonIdParNotCalculated),
  mDKSide(pair.mDKSide),
  mDKOut(pair.mDKOut),
  mDKLong(pair.mDKLong),
  mCVK(pair.mCVK),
  mKStarCalc(pair.mKStarCalc),
  mNonIdParNotCalculatedGlobal(pair.mNonIdParNotCalculatedGlobal),
  mDKSideGlobal(pair.mDKSideGlobal),
  mDKOutGlobal(pair.mDKOutGlobal),
  mDKLongGlobal(pair.mDKLongGlobal),
  mKStarCalcGlobal(pair.mKStarCalcGlobal),
  mCVKGlobal(pair.mCVKGlobal),
  mMergingParNotCalculated(pair.mMergingParNotCalculated),
  mWeightedAvSep(pair.mWeightedAvSep),
  mFracOfMergedRow(pair.mFracOfMergedRow),
  mClosestRowAtDCA(pair.mClosestRowAtDCA),
  mMergingParNotCalculatedTrkV0Pos(pair.mMergingParNotCalculatedTrkV0Pos),
  mFracOfMergedRowTrkV0Pos(pair.mFracOfMergedRowTrkV0Pos),
  mClosestRowAtDCATrkV0Pos(pair.mClosestRowAtDCATrkV0Pos),
  mMergingParNotCalculatedTrkV0Neg(pair.mMergingParNotCalculatedTrkV0Neg),
  mFracOfMergedRowTrkV0Neg(pair.mFracOfMergedRowTrkV0Neg),
  mClosestRowAtDCATrkV0Neg(pair.mClosestRowAtDCATrkV0Neg),
  mMergingParNotCalculatedV0PosV0Neg(pair.mMergingParNotCalculatedV0PosV0Neg),
  mFracOfMergedRowV0PosV0Neg(pair.mFracOfMergedRowV0PosV0Neg),
  mClosestRowAtDCAV0PosV0Neg(pair.mClosestRowAtDCAV0PosV0Neg),
  mMergingParNotCalculatedV0NegV0Pos(pair.mMergingParNotCalculatedV0NegV0Pos),
  mFracOfMergedRowV0NegV0Pos(pair.mFracOfMergedRowV0NegV0Pos),
  mClosestRowAtDCAV0NegV0Pos(pair.mClosestRowAtDCAV0NegV0Pos),
  mMergingParNotCalculatedV0PosV0Pos(pair.mMergingParNotCalculatedV0PosV0Pos),
  mFracOfMergedRowV0PosV0Pos(pair.mFracOfMergedRowV0PosV0Pos),
  mClosestRowAtDCAV0PosV0Pos(pair.mClosestRowAtDCAV0PosV0Pos),
  mMergingParNotCalculatedV0NegV0Neg(pair.mMergingParNotCalculatedV0NegV0Neg),
  mFracOfMergedRowV0NegV0Neg(pair.mFracOfMergedRowV0NegV0Neg),
  mClosestRowAtDCAV0NegV0Neg(pair.mClosestRowAtDCAV0NegV0Neg) {
  /* empty */
}

//_________________
StHbtPair& StHbtPair::operator=(const StHbtPair& pair) {

  // Assignment operator
  if ( this != &pair ) {
    mTrack1 = pair.mTrack1;
    mTrack2 = pair.mTrack2;

    mNonIdParNotCalculated = pair.mNonIdParNotCalculated;
    mDKSide = pair.mDKSide;
    mDKOut = pair.mDKOut;
    mDKLong = pair.mDKLong;
    mCVK = pair.mCVK;
    mKStarCalc = pair.mKStarCalc;

    mNonIdParNotCalculatedGlobal = pair.mNonIdParNotCalculatedGlobal;
    mDKSideGlobal = pair.mDKSideGlobal;
    mDKOutGlobal = pair.mDKOutGlobal;
    mDKLongGlobal = pair.mDKLongGlobal;
    mKStarCalcGlobal = pair.mKStarCalcGlobal;
    mCVKGlobal = pair.mCVKGlobal;

    mMergingParNotCalculated = pair.mMergingParNotCalculated;
    mWeightedAvSep = pair.mWeightedAvSep;
    mFracOfMergedRow = pair.mFracOfMergedRow;
    mClosestRowAtDCA = pair.mClosestRowAtDCA;

    mMergingParNotCalculatedTrkV0Pos = pair.mMergingParNotCalculatedTrkV0Pos;
    mFracOfMergedRowTrkV0Pos = pair.mFracOfMergedRowTrkV0Pos;
    mClosestRowAtDCATrkV0Pos = pair.mClosestRowAtDCATrkV0Pos;

    mMergingParNotCalculatedTrkV0Neg = pair.mMergingParNotCalculatedTrkV0Neg;
    mFracOfMergedRowTrkV0Neg = pair.mFracOfMergedRowTrkV0Neg;
    mClosestRowAtDCATrkV0Neg = pair.mClosestRowAtDCATrkV0Neg;

    mMergingParNotCalculatedV0PosV0Neg = pair.mMergingParNotCalculatedV0PosV0Neg;
    mFracOfMergedRowV0PosV0Neg = pair.mFracOfMergedRowV0PosV0Neg;
    mClosestRowAtDCAV0PosV0Neg = pair.mClosestRowAtDCAV0PosV0Neg;

    mMergingParNotCalculatedV0NegV0Pos = pair.mMergingParNotCalculatedV0NegV0Pos;
    mFracOfMergedRowV0NegV0Pos = pair.mFracOfMergedRowV0NegV0Pos;
    mClosestRowAtDCAV0NegV0Pos = pair.mClosestRowAtDCAV0NegV0Pos;

    mMergingParNotCalculatedV0PosV0Pos = pair.mMergingParNotCalculatedV0PosV0Pos;
    mFracOfMergedRowV0PosV0Pos = pair.mFracOfMergedRowV0PosV0Pos;
    mClosestRowAtDCAV0PosV0Pos = pair.mClosestRowAtDCAV0PosV0Pos;

    mMergingParNotCalculatedV0NegV0Neg = pair.mMergingParNotCalculatedV0NegV0Neg;
    mFracOfMergedRowV0NegV0Neg = pair.mFracOfMergedRowV0NegV0Neg;
    mClosestRowAtDCAV0NegV0Neg = pair.mClosestRowAtDCAV0NegV0Neg;
  }

  return *this;
}

//_________________
StHbtPair::~StHbtPair() {
  /* empty */
}

//_________________
void StHbtPair::setDefaultHalfFieldMergingPar() {
  // Cluster sizes, described in the dimension of TPC sector local coordinates
  mMaxDuInner = 3;
  mMaxDzInner = 4.;
  mMaxDuOuter = 4.;
  mMaxDzOuter = 6.;
}

//_________________
void StHbtPair::setDefaultFullFieldMergingPar() {
  // Cluster sizes, described in the dimension of TPC sector local coordinates
  mMaxDuInner = 0.8;
  mMaxDzInner = 3.;
  mMaxDuOuter = 1.4;
  mMaxDzOuter = 3.2;
}

//_________________
void StHbtPair::setMergingPar(float aMaxDuInner, float aMaxDzInner,
			                        float aMaxDuOuter, float aMaxDzOuter) {
  // Cluster sizes, described in the dimension of TPC sector local coordinates
  mMaxDuInner = aMaxDuInner;
  mMaxDzInner = aMaxDzInner;
  mMaxDuOuter = aMaxDuOuter;
  mMaxDzOuter = aMaxDzOuter;
};

//_________________
double StHbtPair::emissionAngle() const {
  double angle = TMath::ATan2( py(), px() ) * TMath::RadToDeg();
  if ( angle < 0 ) {
    angle += 360.0;
  }
  return angle;
}

//_________________
void StHbtPair::qYKPCMS(double& qP, double& qT, double& q0) const {

  // Yano-Koonin-Podgoretskii Parametrisation in CMS
  // Calculate momentum difference in source rest frame (= lab frame)

  // Random ordering of the particles
  TLorentzVector l = ( ( rand() / (double)RAND_MAX ) > 0.50 ?
		       ( mTrack1->fourMomentum() - mTrack2->fourMomentum() ) :
		       ( mTrack2->fourMomentum() - mTrack1->fourMomentum() ) );
  // Fill momentum differences into return variables
  qP = l.Pz() ;
  qT = l.Vect().Perp() ;
  q0 = l.Energy() ;
}

//_________________
void StHbtPair::qYKPLCMS(double& qP, double& qT, double& q0) const {

  // Yano-Koonin-Podgoretskii Parametrisation in LCMS
  // Calculate momentum difference in LCMS : frame where pz1 + pz2 = 0
  TLorentzVector l1 = mTrack1->fourMomentum();
  TLorentzVector l2 = mTrack2->fourMomentum();

  // Determine beta to LCMS
  double betaZ = fourMomentumSum().Pz() / fourMomentumSum().Energy() ;

  // Boost in the correct direction
  if ( betaZ > 0 ) { betaZ = -betaZ; }

  // Boost particles along the beam into a frame with velocity beta
  l1.Boost( 0., 0., betaZ );
  l2.Boost( 0., 0., betaZ );

  // Caculate the momentum difference with random ordering of the particle
  TLorentzVector l = ( ( rand() / (double)RAND_MAX ) > 0.5 ?
		       ( l1 - l2 ) : ( l2 - l1 ) );

  // Fill momentum differences into return variables
  qP = l.Z() ;
  qT = l.Vect().Perp() ;
  q0 = l.Energy() ;
}

//_________________
void StHbtPair::qYKPPF(double& qP, double& qT, double& q0) const {

  // Yano-Koonin-Podgoretskii Parametrisation in pair rest fram
  // Calculate momentum difference in pair rest frame :
  // frame where (pz1 + pz2, py1 + py2, px1 + px2) = (0,0,0)
  TLorentzVector l1 = mTrack1->fourMomentum() ;
  TLorentzVector l2 = mTrack2->fourMomentum() ;

  // Calculate beta in each direction
  double betaX = -fourMomentumSum().Px() / fourMomentumSum().Energy();
  double betaY = -fourMomentumSum().Py() / fourMomentumSum().Energy();
  double betaZ = -fourMomentumSum().Pz() / fourMomentumSum().Energy();

  // Boost particles
  l1.Boost( betaX, betaY, betaZ ) ;
  l2.Boost( betaX, betaY, betaZ ) ;

  // Caculate the momentum difference with random ordering of the particle
  TLorentzVector l = ( ( rand() / (double)RAND_MAX ) > 0.50 ?
		       ( l1 - l2 ) : ( l2 - l1 ) );

  // Fill momentum differences into return variables
  qP = l.Z();
  qT = l.Vect().Perp();
  q0 = l.Energy();
}

//_________________
double StHbtPair::qOutCMS() const {
  // Relative momentum out component in the lab frame
  double dx = mTrack1->px() - mTrack2->px();
  double xt = mTrack1->px() + mTrack2->px();

  double dy = mTrack1->py() - mTrack2->py();
  double yt = mTrack1->py() + mTrack2->py();

  double k1 = TMath::Sqrt(xt*xt+yt*yt);
  double k2 = dx*xt + dy*yt;
  return (k1!=0) ? (k2 / k1) : 0.;
}

//_________________
double StHbtPair::qSideCMS() const {
  // Relative momentum side component in the lab frame
  double x1 = mTrack1->px();  double y1 = mTrack1->py();
  double x2 = mTrack2->px();  double y2 = mTrack2->py();

  double xt = x1+x2;  double yt = y1+y2;
  double k1 = TMath::Sqrt( xt*xt + yt*yt );

  return ( (k1!=0) ? ( 2.0 * ( x2*y1 - x1*y2 ) / k1 ) : 0. );
}

//_________________
double StHbtPair::qLongCMS() const {
  // Relative momentum long component in the lab frame
  double dz = mTrack1->pz() - mTrack2->pz();
  double zz = mTrack1->pz() + mTrack2->pz();

  double dt = mTrack1->t() - mTrack2->t();
  double tt = mTrack1->t() + mTrack2->t();

  double beta = zz / tt;
  double gamma = 1.0 / TMath::Sqrt( 1.0 - beta*beta );

  return ( gamma * ( dz - beta*dt ) );
}

//_________________
double StHbtPair::qOutPf() const {
  // Relative momentum out component in the pair frame
  double dt = mTrack1->t() - mTrack2->t();
  double tt = mTrack1->t() + mTrack2->t();

  double xt = mTrack1->px() + mTrack2->px();
  double yt = mTrack1->py() + mTrack2->py();

  double k1 = TMath::Sqrt( xt*xt + yt*yt );
  double bOut = k1 / tt;
  double gOut = 1.0 / TMath::Sqrt(1.0 - bOut*bOut );

  return ( gOut * ( this->qOutCMS() - bOut*dt ) );
}

//_________________
double StHbtPair::qSidePf() const {
  // Relative momentum side component in the pair frame
  return ( this->qSideCMS() );
}

//_________________
double StHbtPair::qLongPf() const {
  // Relative momentum long component in the pair frame
 return ( this->qLongCMS() );
}

//_________________
double StHbtPair::qOutBf(double /* beta */) const {
  // Relative momentum long component in the boosted frame
  return ( this->qOutCMS() );
}

//_________________
double StHbtPair::qSideBf(double /* beta */) const {
  // Relative momentum long component in the boosted frame
  return ( this->qSideCMS() );
}

//_________________
double StHbtPair::qLongBf(double beta) const {
  // Relative momentum long component in the boosted frame
  double dz = mTrack1->pz() -  mTrack2->pz();
  double dt = mTrack1->t() +  mTrack2->t();

  double gamma = 1.0/TMath::Sqrt( 1.0 - beta*beta );

  return ( gamma * ( dz - beta*dt ) );
}

//_________________
double StHbtPair::quality() const {
  // Estimation of track splitting
  unsigned long mapMask0 = 0xFFFFFF00;
  unsigned long mapMask1 = 0x1FFFFF;
  unsigned long padRow1To24Track1 = mTrack1->topologyMap(0) & mapMask0;
  unsigned long padRow25To45Track1 = mTrack1->topologyMap(1) & mapMask1;
  unsigned long padRow1To24Track2 = mTrack2->topologyMap(0) & mapMask0;
  unsigned long padRow25To45Track2 = mTrack2->topologyMap(1) & mapMask1;
  // AND logic
  unsigned long bothPads1To24 = padRow1To24Track1 & padRow1To24Track2;
  unsigned long bothPads25To45 = padRow25To45Track1 & padRow25To45Track2;
  // XOR logic
  unsigned long onePad1To24 = padRow1To24Track1 ^ padRow1To24Track2;
  unsigned long onePad25To45 = padRow25To45Track1 ^ padRow25To45Track2;
  unsigned long bitI;
  int ibits;
  int Quality = 0;
  for ( ibits=8; ibits<=31; ibits++ ) {
    bitI = 0;
    bitI |= 1UL<<(ibits);
    if ( onePad1To24 & bitI ) {
      Quality++;
      continue;
    } // if ( onePad1To24 & bitI )
    else {
      if ( bothPads1To24 & bitI ) Quality--;
    } //else {
  } //for (ibits=8;ibits<=31;ibits++)
  for ( ibits=0; ibits<=20; ibits++ ) {
    bitI = 0;
    bitI |= 1UL<<(ibits);
    if ( onePad25To45 & bitI ) {
      Quality++;
      continue;
    } //if ( onePad25To45 & bitI )
    else {
      if ( bothPads25To45 & bitI ) {
	      Quality--;
      } //if ( bothPads25To45 & bitI )
    } //else {
  } //for (ibits=0;ibits<=20;ibits++)
  return ( (double)Quality / ( (double) ( mTrack1->nHits() + mTrack2->nHits() ) ) );
}

//_________________
double StHbtPair::quality2() const {

  unsigned long mapMask0 = 0xFFFFFF00;
  unsigned long mapMask1 = 0x1FFFFF;
  unsigned long padRow1To24Track1 = mTrack1->topologyMap(0) & mapMask0;
  unsigned long padRow25To45Track1 = mTrack1->topologyMap(1) & mapMask1;
  unsigned long padRow1To24Track2 = mTrack2->topologyMap(0) & mapMask0;
  unsigned long padRow25To45Track2 = mTrack2->topologyMap(1) & mapMask1;

  // AND logic
  //unsigned long bothPads1To24 = padRow1To24Track1 & padRow1To24Track2;
  //unsigned long bothPads25To45 = padRow25To45Track1 & padRow25To45Track2;

  // XOR logic
  unsigned long onePad1To24 = padRow1To24Track1 ^ padRow1To24Track2;
  unsigned long onePad25To45 = padRow25To45Track1 ^ padRow25To45Track2;
  unsigned long bitI;
  int ibits;
  int Quality = 0;
  for (ibits=8;ibits<=31;ibits++) {
    bitI = 0;
    bitI |= 1UL<<(ibits);
    if ( onePad1To24 & bitI ) {
      Quality++;
      continue;
    }
    //else{
    //if ( bothPads1To24 & bitI ) Quality--;
    //}
  }
  for (ibits=0;ibits<=20;ibits++) {
    bitI = 0;
    bitI |= 1UL<<(ibits);
    if ( onePad25To45 & bitI ) {
      Quality++;
      continue;
    }
    //else{
    //if ( bothPads25To45 & bitI ) Quality--;
    //}
  }
  return ( (double)Quality / ( (double) ( mTrack1->nHits() + mTrack2->nHits() ) ) );
}

//_________________
double StHbtPair::nominalTpcExitSeparation() const {
  /// Distance between tracks at nominal exit point
  return ( mTrack1->nominalTpcExitPoint() -
	   mTrack2->nominalTpcExitPoint() ).Mag();
}

//_________________
double StHbtPair::nominalTpcEntranceSeparation() const {
  /// Distance between tracks at nominal entrance point
  return ( mTrack1->nominalTpcEntrancePoint() -
	   mTrack2->nominalTpcEntrancePoint() ).Mag();
}

//_________________
double StHbtPair::nominalTpcAverageSeparation() const {

  double AveSep = 0.0;
  int ipt = 0;
  if (mTrack1->nominalPosSampleX() && mTrack2->nominalPosSampleX() &&
      mTrack1->nominalPosSampleY() && mTrack2->nominalPosSampleY() &&
      mTrack1->nominalPosSampleZ() && mTrack2->nominalPosSampleZ() ) {

    while ( ipt < mTrack1->mNumberOfPoints &&
 	    TMath::Abs( mTrack1->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleZ()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleZ()[ipt] ) < 9999. ) {

      AveSep += ( mTrack1->nominalPosSample(ipt) - mTrack2->nominalPosSample(ipt) ).Mag();
      ipt++;
    }
    AveSep = AveSep / (ipt+1.);
  }
  else {
    AveSep = -1.;
  }
  return AveSep;
}

//_________________
double StHbtPair::kStarFlipped() const {
  /// Estimation of kStar with the flipped sign
  TLorentzVector tP1 = mTrack1->fourMomentum();

  /// Flip the sign
  TVector3 qwe = mTrack1->p();
  qwe *= -1.; // flip it
  tP1.SetVect(qwe);

  TLorentzVector tSum = ( tP1 + mTrack2->fourMomentum() );
  TVector3 tGammaBeta = ( 1. / tSum.M() ) * tSum.Vect();
  double   tGamma = tSum.E() / tSum.M();
  TVector3 tLongMom  = ( ( tP1.Vect() * tGammaBeta ) /
			 ( tGammaBeta * tGammaBeta ) ) * tGammaBeta;
  /// Constructor TLorentzVector( TVector3, double )
  TLorentzVector tK( ( tP1.Vect() + (tGamma - 1.) * tLongMom - tP1.E() * tGammaBeta ),
		     ( tGamma * tP1.E() - tP1.Vect() * tGammaBeta ) );

  return tK.Vect().Mag();
}

//_________________
double StHbtPair::cvkFlipped() const {
  /// CVK with sign flipped
  TLorentzVector tP1 = mTrack1->fourMomentum();
  TVector3 qwe = tP1.Vect();
  qwe *= -1.; // flip it
  tP1.SetVect(qwe);

  TLorentzVector tSum = ( tP1 + mTrack2->fourMomentum() );
  TVector3 tGammaBeta = ( 1. / tSum.M() ) * tSum.Vect();
  double   tGamma = tSum.E() / tSum.M();
  TVector3 tLongMom  = ( ( tP1.Vect() * tGammaBeta ) /
			 ( tGammaBeta * tGammaBeta ) ) * tGammaBeta;
  TLorentzVector tK( ( tP1.Vect() + ( tGamma-1. ) * tLongMom - tP1.E() * tGammaBeta ),
		     ( tGamma * tP1.E() - tP1.Vect() * tGammaBeta ) );
  return ( tGammaBeta * (1. / tGamma) * tK.Vect() );
}

//_________________
double StHbtPair::pInv() const {
  // Invariant total momentum
  TLorentzVector tP1 = mTrack1->fourMomentum();
  TLorentzVector tP2 = mTrack2->fourMomentum();
  double tP = ( tP1.Px() + tP2.Px() ) * ( tP1.Px() + tP2.Px() )+
              ( tP1.Py() + tP2.Py() ) * ( tP1.Py() + tP2.Py() )+
              ( tP1.Pz() + tP2.Pz() ) * ( tP1.Pz() + tP2.Pz() )-
              ( tP1.E()  - tP2.E()  ) * ( tP1.E()  - tP2.E()  ); 
  return TMath::Sqrt( TMath::Abs( tP ) );
}

//_________________
double StHbtPair::qInvFlippedXY() const {
  // qInv with X and Y flipped of one of the track from pair
  TLorentzVector tP1 = mTrack1->fourMomentum();
  tP1.SetX(-1. * tP1.X() );
  tP1.SetY(-1. * tP1.Y() );
  return ( -1. * ( tP1 - mTrack2->fourMomentum() ).M() );
}

//_________________
double StHbtPair::qInvRandomFlippedXY() const {
  // qInv with X and Y flipped of one of the track from pair.
  // The track is randomly selected.
  TLorentzVector tP1 = mTrack1->fourMomentum();
  TLorentzVector tP2 = mTrack1->fourMomentum();

  if ( rand()/(double)RAND_MAX > 0.50 ) {
    tP1.SetX(-1. * tP1.X() );
    tP1.SetY(-1. * tP1.Y() );
  }
  else {
    tP2.SetX( -1. * tP2.X() );
    tP2.SetY( -1. * tP2.Y() );
  }
  return ( -1. * ( tP1 - tP2 ).M() );
}

//_________________
double StHbtPair::qInvFlippedXYZ() const {
  // qInv with X, Y and Z flipped of one of the track from pair
  TLorentzVector tP1 = mTrack1->fourMomentum();
  tP1.SetX( -1.* tP1.X() );
  tP1.SetY( -1.* tP1.Y() );
  tP1.SetZ( -1.* tP1.Z() );
  return ( -1. * (tP1 - mTrack2->fourMomentum()).M() );
}

//_________________
double StHbtPair::qInvRandomFlippedXYZ() const {
  // qInv with X, Y and Z flipped of one of the track from pair.
  // The track is randomly selected.
  TLorentzVector tP1 = mTrack1->fourMomentum();
  TLorentzVector tP2 = mTrack2->fourMomentum();

  if ( rand()/(double)RAND_MAX > 0.50 ) {
    tP1.SetX( -1.* tP1.X() );
    tP1.SetY( -1.* tP1.Y() );
    tP1.SetZ( -1.* tP1.Z() );
  }
  else {
    tP2.SetX( -1.*tP2.X() );
    tP2.SetY( -1.*tP2.Y() );
    tP2.SetZ( -1.*tP2.Z() );
  }
  return ( -1. * (tP1-tP2).M() );
}

//_________________
void StHbtPair::calcNonIdPar() const {
  // Calculate generalized relative mometum
  // Use this instead of qXYZ() function when calculating
  // anything for non-identical particles
  mNonIdParNotCalculated=0;

  double px1 = mTrack1->px();
  double py1 = mTrack1->py();
  double pz1 = mTrack1->pz();
  double pE1  = mTrack1->e();
  double Particle1Mass = 0;
  if( ( pE1 * pE1 - px1 * px1 - py1 * py1 - pz1 * pz1 ) >0 ) {
    Particle1Mass = TMath::Sqrt( pE1 * pE1 - px1 * px1 - py1 * py1 - pz1 * pz1 );
  }

  double px2 = mTrack2->px();
  double py2 = mTrack2->py();
  double pz2 = mTrack2->pz();
  double pE2  = mTrack2->e();
  double Particle2Mass = 0;
  if( ( pE1 * pE1 - px1 * px1 - py1 * py1 - pz1 * pz1 ) >0 ) {
    Particle2Mass = TMath::Sqrt( pE2 * pE2 - px2 * px2 - py2 * py2 - pz2 * pz2 );
  }

  double Px = px1 + px2;
  double Py = py1 + py2;
  double Pz = pz1 + pz2;
  double PE = pE1 + pE2;

  double Ptrans = Px*Px + Py*Py;
  double Mtrans = PE*PE - Pz*Pz;
  double Pinv = TMath::Sqrt( Mtrans - Ptrans );
  Mtrans = TMath::Sqrt( Mtrans );
  Ptrans = TMath::Sqrt( Ptrans );

  double QinvL = ( (pE1 - pE2) * ( pE1 - pE2 ) - ( px1 - px2 ) * ( px1 - px2 ) -
		   (py1 - py2) * ( py1 - py2 ) - ( pz1 - pz2 ) * ( pz1 - pz2 ) );

  double Q = ( Particle1Mass * Particle1Mass -
	       Particle2Mass * Particle2Mass ) / Pinv;
  Q = sqrt ( Q * Q - QinvL );
  mKStarCalc = Q / 2;

  /// ad 1) go to LCMS
  double beta = Pz / PE;
  double gamma = PE / Mtrans;

  double pz1L = gamma * ( pz1 - beta * pE1 );
  double pE1L = gamma * ( pE1 - beta * pz1 );

  // fill histogram for beam projection ( z - axis )
  mDKLong = pz1L;

  // ad 2) rotation px -> Pt
  double px1R = ( px1 * Px + py1 * Py ) / Ptrans;
  double py1R = ( -px1 * Py + py1 * Px ) / Ptrans;

  // fill histograms for side projection ( y - axis )
  mDKSide = py1R;

  // ad 3) go from LCMS to CMS
  beta = Ptrans / Mtrans;
  gamma = Mtrans / Pinv;

  double px1C = gamma * ( px1R - beta * pE1L );

  // fill histogram for out projection ( x - axis )
  mDKOut  = px1C;

  mCVK = ( ( mDKOut * Ptrans + mDKLong * Pz ) /
	   mKStarCalc / TMath::Sqrt( Ptrans * Ptrans + Pz * Pz ) );
}

//_________________
void StHbtPair::calcNonIdParGlobal() const{
  // Calculate generalized relative mometum
  // Use this instead of qXYZ() function when calculating
  // anything for non-identical particles
  mNonIdParNotCalculatedGlobal = 0;

  double px1 = mTrack1->track()->gMom().X();
  double py1 = mTrack1->track()->gMom().Y();
  double pz1 = mTrack1->track()->gMom().Z();
  double Particle1Mass =  mTrack1->fourMomentum().M2();
  double pE1  = TMath::Sqrt( Particle1Mass + px1 * px1 + py1 * py1 + pz1 * pz1 );
  Particle1Mass = TMath::Sqrt( Particle1Mass );

  double px2 = mTrack2->track()->gMom().X();
  double py2 = mTrack2->track()->gMom().Y();
  double pz2 = mTrack2->track()->gMom().Z();
  double Particle2Mass =  mTrack2->fourMomentum().M2();
  double pE2  = TMath::Sqrt( Particle2Mass + px2 * px2 + py2 * py2 + pz2 * pz2 );
  Particle2Mass = TMath::Sqrt( Particle2Mass );

  double Px = px1 + px2;
  double Py = py1 + py2;
  double Pz = pz1 + pz2;
  double PE = pE1 + pE2;

  double Ptrans = Px * Px + Py * Py;
  double Mtrans = PE * PE - Pz * Pz;
  double Pinv = TMath::Sqrt( Mtrans - Ptrans );
  Mtrans = TMath::Sqrt( Mtrans );
  Ptrans = TMath::Sqrt( Ptrans );

  double QinvL = ( ( pE1 - pE2 ) * ( pE1 - pE2 ) - ( px1 - px2 ) * ( px1 - px2 ) -
		   ( py1 - py2 ) * ( py1 - py2 ) - ( pz1 - pz2 ) * ( pz1 - pz2 ) );

  double Q = ( Particle1Mass * Particle1Mass - Particle2Mass * Particle2Mass ) / Pinv;
  Q = TMath::Sqrt( Q*Q - QinvL );
  mKStarCalcGlobal = Q/2;

  /// ad 1) go to LCMS
  double beta = Pz / PE;
  double gamma = PE / Mtrans;

  double pz1L = gamma * ( pz1 - beta * pE1 );
  double pE1L = gamma * ( pE1 - beta * pz1 );

  // fill histogram for beam projection ( z - axis )
  mDKLongGlobal = pz1L;

  // ad 2) rotation px -> Pt
  double px1R = ( px1 * Px + py1 * Py ) / Ptrans;
  double py1R = ( -px1 * Py + py1 * Px ) / Ptrans;

  // fill histograms for side projection ( y - axis )
  mDKSideGlobal = py1R;

  // ad 3) go from LCMS to CMS
  beta = Ptrans / Mtrans;
  gamma = Mtrans / Pinv;

  double px1C = gamma * ( px1R - beta * pE1L );

  // fill histogram for out projection ( x - axis )
  mDKOutGlobal  = px1C;

  mCVKGlobal = ( ( mDKOutGlobal * Ptrans + mDKLongGlobal * Pz ) /
		 mKStarCalcGlobal / TMath::Sqrt( Ptrans * Ptrans + Pz * Pz ) );
}

//_________________
double StHbtPair::dcaInsideTpc() const {
  // DCA inside TPC
  double tMinDist = nominalTpcEntranceSeparation();
  double tExit = nominalTpcExitSeparation();
  tMinDist = ( tExit > tMinDist ) ? tMinDist : tExit;
  double tInsideDist;
  //tMinDist = 999.;

  double rMin = 60.;
  double rMax = 190.;
  StHbtPhysicalHelix tHelix1 = mTrack1->helix();
  StHbtPhysicalHelix tHelix2 = mTrack2->helix();
  // --- One is a line and other one a helix
  //if (tHelix1.mSingularity != tHelix2.mSingularity) return -999.;
  // --- 2 lines : don't care right now
  //if (tHelix1.mSingularity)  return -999.;
  // --- 2 helix
  double dx = tHelix2.xcenter() - tHelix1.xcenter();
  double dy = tHelix2.ycenter() - tHelix1.ycenter();
  double dd = TMath::Sqrt( dx * dx + dy * dy );
  double r1 = 1 / tHelix1.curvature();
  double r2 = 1 / tHelix2.curvature();
  double cosAlpha = ( r1 * r1 + dd * dd - r2 * r2 ) / ( 2 * r1 * dd );

  double x, y, r;
  double s;
  if ( TMath::Abs( cosAlpha ) < 1. ) {
    // Two solutions
    double sinAlpha = TMath::Sin( TMath::ACos( cosAlpha ) );
    x = tHelix1.xcenter() + r1 * ( cosAlpha * dx - sinAlpha * dy ) / dd;
    y = tHelix1.ycenter() + r1 * ( sinAlpha * dx + cosAlpha * dy) / dd;
    r = TMath::Sqrt( x * x + y * y );
    if( ( r > rMin ) && ( r < rMax ) &&
      TMath::Abs( TMath::ATan2( y, x) -
	    mTrack1->nominalTpcEntrancePoint().Phi() ) < 0.5 ) {
        // first solution inside
        s = tHelix1.pathLength(x, y);
        tInsideDist = tHelix2.distance( tHelix1.at(s) );
        if ( tInsideDist < tMinDist ) {
  	       tMinDist = tInsideDist;
        }
      }
      else {
        x = tHelix1.xcenter() + r1 * ( cosAlpha * dx + sinAlpha * dy) / dd;
        y = tHelix1.ycenter() + r1 * ( cosAlpha * dy - sinAlpha * dx) / dd;
        r = TMath::Sqrt( x * x + y * y );
        if( ( r > rMin ) && ( r < rMax ) &&
  	        TMath::Abs( TMath::ATan2( y, x ) -
            mTrack1->nominalTpcEntrancePoint().Phi() ) < 0.5 ) {
  	          // second solution inside
              s = tHelix1.pathLength( x, y );
              tInsideDist = tHelix2.distance( tHelix1.at(s) );
              if ( tInsideDist < tMinDist ) {
  	             tMinDist = tInsideDist;
  	          }
        }
    } //else
  } //if ( TMath::Abs( cosAlpha ) < 1. )
  return tMinDist;
}

//_________________
void StHbtPair::calcMergingPar() const {
  // Calculate merging factor for the pair in STAR TPC
  mMergingParNotCalculated=0;

  double tDu, tDz;
  int tN = 0;
  mFracOfMergedRow = 0.;
  mWeightedAvSep =0.;
  double tDist;
  double tDistMax = 200.;
  for ( int ti=0; ti < mTrack1->mNumberOfPadrows ; ti++ ) {

    if ( ( mTrack1->sect()[ti] == mTrack2->sect()[ti] ) &&
	       mTrack1->sect()[ti] != -1 ) {
      tDu = TMath::Abs( mTrack1->u()[ti] - mTrack2->u()[ti] );
      tDz = TMath::Abs( mTrack1->z()[ti] - mTrack2->z()[ti] );
      tN++;

      if ( ti<13 ) {
      	mFracOfMergedRow += ( tDu<mMaxDuInner && tDz<mMaxDzInner );
      	tDist = TMath::Sqrt( tDu * tDu / mMaxDuInner / mMaxDuInner +
      		tDz * tDz / mMaxDzInner / mMaxDzInner );
	      //mFracOfMergedRow += (tDu<mMaxDuInner && tDz<mMaxDzInner);
      }
      else {
      	mFracOfMergedRow += ( tDu<mMaxDuOuter && tDz<mMaxDzOuter );
      	tDist = TMath::Sqrt( tDu * tDu / mMaxDuOuter / mMaxDuOuter +
			    tDz * tDz / mMaxDzOuter / mMaxDzOuter );
	      //mFracOfMergedRow += (tDu<mMaxDuOuter && tDz<mMaxDzOuter);
      }

      if ( tDist<tDistMax ) {
	      mClosestRowAtDCA = ti+1;
	      tDistMax = tDist;
      }
      mWeightedAvSep += tDist;
    }
  } // for ( int ti=0; ti < mTrack1->mNumberOfPadrows ; ti++ )

  if ( tN>0 ) {
    mWeightedAvSep /= tN;
    mFracOfMergedRow /= tN;
  }
  else {
    mClosestRowAtDCA = -1;
    mFracOfMergedRow = -1.;
    mWeightedAvSep = -1.;
  }
}

//________________V0 daughters exit/entrance/average separation calc.
//_______1st part is a track 2nd is a V0 considering Pos daughter
double StHbtPair::tpcAverageSeparationTrackV0Pos() const {

  double AveSep = 0.0;
  int ipt = 0;
  if ( mTrack1->nominalPosSampleX() && mTrack2->nominalPosSampleX() &&
       mTrack1->nominalPosSampleY() && mTrack2->nominalPosSampleY() &&
       mTrack1->nominalPosSampleZ() && mTrack2->nominalPosSampleZ() ) {

    while ( ipt < mTrack1->mNumberOfPoints &&
 	    TMath::Abs( mTrack1->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleZ()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleZ()[ipt] ) < 9999. ) {

      AveSep += ( mTrack1->nominalPosSample( ipt ) - mTrack2->nominalPosSample( ipt ) ).Mag();
      ipt++;
    }
    AveSep = AveSep / ( ipt+1. );
  }
  else {
    AveSep = -1.;
  }
  return AveSep;
}

//_________________
double StHbtPair::tpcAverageSeparationTrackV0Neg() const {

  double AveSep = 0.0;
  int ipt = 0;
  if ( mTrack1->nominalPosSampleX() && mTrack2->tpcV0NegPosSampleX() &&
       mTrack1->nominalPosSampleY() && mTrack2->tpcV0NegPosSampleY() &&
       mTrack1->nominalPosSampleZ() && mTrack2->tpcV0NegPosSampleZ() ) {

    while ( ipt < mTrack1->mNumberOfPoints &&
 	    TMath::Abs( mTrack1->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleZ()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleZ()[ipt] ) < 9999. ) {
      AveSep = ( mTrack1->nominalPosSample( ipt ) - mTrack2->tpcV0NegPosSample( ipt ) ).Mag();
      ipt++;
    }
    AveSep = AveSep / (ipt + 1.);
  }
  else {
    AveSep = -1;
  }
  return AveSep;
}

//_________________
double StHbtPair::tpcAverageSeparationV0PosV0Pos() const {

  double AveSep = 0.0;
  int ipt=0;
  if( mTrack1->nominalPosSampleX() && mTrack2->nominalPosSampleX() &&
      mTrack1->nominalPosSampleY() && mTrack2->nominalPosSampleY() &&
      mTrack1->nominalPosSampleZ() && mTrack2->nominalPosSampleZ() ) {

    while ( ipt < mTrack1->mNumberOfPoints &&
 	    TMath::Abs( mTrack1->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleZ()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleZ()[ipt] ) < 9999. ) {
      AveSep += ( mTrack1->nominalPosSample( ipt ) - mTrack2->nominalPosSample( ipt ) ).Mag();
      ipt++;
    }
    AveSep = AveSep / ( ipt+1 );
  }
  else {
    AveSep = -1;
  }
  return AveSep;
}

//_________________
double StHbtPair::tpcAverageSeparationV0PosV0Neg() const {
  double AveSep = 0.0;
  int ipt = 0;
  if ( mTrack1->nominalPosSampleX() && mTrack2->tpcV0NegPosSampleX() &&
       mTrack1->nominalPosSampleY() && mTrack2->tpcV0NegPosSampleY() &&
       mTrack1->nominalPosSampleZ() && mTrack2->tpcV0NegPosSampleZ() ) {

    while ( ipt < mTrack1->mNumberOfPoints &&
 	    TMath::Abs( mTrack1->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->nominalPosSampleZ()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->tpcV0NegPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->tpcV0NegPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->tpcV0NegPosSampleZ()[ipt] ) < 9999. ) {
      AveSep += ( mTrack1->nominalPosSample( ipt ) - mTrack2->tpcV0NegPosSample( ipt ) ).Mag();
      ipt++;
    }
    AveSep = AveSep / (ipt+1.);
  }
  else {
    AveSep = -1;
  }
  return AveSep;
}

//_________________
double StHbtPair::tpcAverageSeparationV0NegV0Pos() const {
  double AveSep = 0.0;
  int ipt = 0;
  if ( mTrack1->tpcV0NegPosSampleX() &&  mTrack2->nominalPosSampleX() &&
       mTrack1->tpcV0NegPosSampleY() &&  mTrack2->nominalPosSampleY() &&
       mTrack1->tpcV0NegPosSampleZ() &&  mTrack2->nominalPosSampleZ() ) {

    while ( ipt < mTrack1->mNumberOfPoints &&
 	    TMath::Abs( mTrack1->tpcV0NegPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->tpcV0NegPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->tpcV0NegPosSampleZ()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->nominalPosSampleZ()[ipt] ) < 9999. ) {
      AveSep += ( mTrack1->tpcV0NegPosSample( ipt ) - mTrack2->nominalPosSample( ipt ) ).Mag();
      ipt++;
    }
    AveSep = AveSep / ( ipt+1 );
  }
  else {
    AveSep = -1;
  }
  return AveSep;
}

//_________________
double StHbtPair::tpcAverageSeparationV0NegV0Neg() const {
  double AveSep = 0.0;
  int ipt=0;
  if ( mTrack1->tpcV0NegPosSampleX() && mTrack2->tpcV0NegPosSampleX() &&
       mTrack1->tpcV0NegPosSampleY() && mTrack2->tpcV0NegPosSampleY() &&
       mTrack1->tpcV0NegPosSampleZ() && mTrack2->tpcV0NegPosSampleZ() ) {

    while ( ipt < mTrack1->mNumberOfPoints &&
 	    TMath::Abs( mTrack1->tpcV0NegPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->tpcV0NegPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack1->tpcV0NegPosSampleZ()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->tpcV0NegPosSampleX()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->tpcV0NegPosSampleY()[ipt] ) < 9999. &&
	    TMath::Abs( mTrack2->tpcV0NegPosSampleZ()[ipt] ) < 9999. ) {
      AveSep += ( mTrack1->tpcV0NegPosSample(ipt) - mTrack2->tpcV0NegPosSample(ipt) ).Mag();
      ipt++;
    }
    AveSep = AveSep / ( ipt+1 );
  }
  else {
    AveSep = -1;
  }
  return AveSep;
}

//_________________ End V0 daughters exit/entrance/average separation calc.
void StHbtPair::calcMergingParFctn( short* tmpMergingParNotCalculatedFctn,
                        				    float* tmpZ1, float* tmpU1,
                        				    float* tmpZ2, float* tmpU2,
                        				    int *tmpSect1, int *tmpSect2,
                        				    float* tmpFracOfMergedRow,
                        				    float* tmpClosestRowAtDCA ) const {

  tmpMergingParNotCalculatedFctn=0;
  double tDu, tDz;
  int tN = 0;
  *tmpFracOfMergedRow = 0.;
  *tmpClosestRowAtDCA = 0.;
  double tDist;
  double tDistMax = 100000000.;

  /// Loop over padrows
  for(int ti=0 ; ti<mTrack1->mNumberOfPadrows ; ti++) {

    if( tmpSect1[ti]==tmpSect2[ti] && tmpSect1[ti]!=-1 ) {
      tDu = fabs(tmpU1[ti]-tmpU2[ti]);
      tDz = fabs(tmpZ1[ti]-tmpZ2[ti]);
      tN++;

      if ( ti < 13 ) {
	      *tmpFracOfMergedRow += ( tDu<mMaxDuInner && tDz<mMaxDzInner );
	      tDist = TMath::Sqrt( tDu * tDu / mMaxDuInner / mMaxDuInner +
			    tDz * tDz / mMaxDzInner / mMaxDzInner );
      }
      else {
      	*tmpFracOfMergedRow += ( tDu < mMaxDuOuter && tDz < mMaxDzOuter );
      	tDist = TMath::Sqrt( tDu * tDu / mMaxDuOuter / mMaxDuOuter +
			    tDz * tDz / mMaxDzOuter / mMaxDzOuter );
      }

      if ( tDist < tDistMax ) {
      	mClosestRowAtDCA = ti+1;
      	tDistMax = tDist;
      }
      //mWeightedAvSep += tDist; // now, wrong but not used
    }
  } // for(int ti=0 ; ti<mTrack1->mNumberOfPadrows ; ti++)

  if ( tN > 0 ) {
    //mWeightedAvSep /= tN;
    *tmpFracOfMergedRow /= tN;
  }
  else {
    *tmpClosestRowAtDCA = -1;
    *tmpFracOfMergedRow = -1.;
    //mWeightedAvSep = -1.;
  }
}

//_________________
double StHbtPair::calculateDPhiStarMin(const TVector3& p_a,
                                       const short& charge_a,
                                       const TVector3& p_b,
                                       const short& charge_b,
                                       const double& rad_step_in_meters,
                                       const double& rad_min_in_meters,
                                       const double& rad_max_in_meters,
                                       const double& magnetic_field) {
  // Estimate minimal value of azimuthal angle disctance between two tracks
  // over a set of radial positions from rad_min to rad_max with_rad_step
  if (rad_min_in_meters > rad_max_in_meters) {
    std::cout << "[WARNING] double StHbtDPhiStarDEtaEstimator::calculateDPhiStarMin - "
              << "Mimal radial distance is larger then maximal one" << std::endl;
    return 0;
  }

  // Estimate DPhiStar at all requested radial distances
  std::vector<double> dPhiStarValues = calculateDPhiStarValues( p_a, charge_a,
                                                                p_b, charge_b,
                                                                rad_step_in_meters,
                                                                rad_min_in_meters,
                                                                rad_max_in_meters,
                                                                magnetic_field );
  // Check that vector is not empty
  if ( dPhiStarValues.empty() ) {
    return 0;
  }

  // STL vector that stores DPhiStar values estimated for requested radial positions
  double minValue = 99999.;
  double currentValue = 0.;

  // Loop over radial positions
  for ( unsigned short iDist=0; iDist<dPhiStarValues.size(); iDist++ ) {
    currentValue = dPhiStarValues.at( iDist );
    if ( currentValue<minValue ) {
      minValue = currentValue;
    }
  } //for ( unsigned short iDist=0; iDist<nSteps; iDist++ )

  return minValue;
}

//_________________
std::vector<double> StHbtPair::calculateDPhiStarValues(const TVector3& p_a,
                                                       const short& charge_a,
                                                       const TVector3& p_b,
                                                       const short& charge_b,
                                                       const double& rad_step_in_meters,
                                                       const double& rad_min_in_meters,
                                                       const double& rad_max_in_meters,
                                                       const double& magnetic_field) {
  // Estimate minimal value of azimuthal angle disctance between two tracks
  // over a set of radial positions from rad_min to rad_max with_rad_step

  // STL vector that stores DPhiStar values estimated for requested radial positions
  std::vector<double> dPhiStar;

  if (rad_min_in_meters > rad_max_in_meters) {
    std::cout << "[WARNING] double StHbtDPhiStarDEtaEstimator::calculateDPhiStarMin - "
              << "Mimal radial distance is larger then maximal one" << std::endl;
    return dPhiStar;
  }

  // Estimate number of calculations
  unsigned short nSteps = (rad_max_in_meters - rad_min_in_meters) / rad_step_in_meters;

  // Loop over radial positions
  for ( unsigned short iStep=0; iStep<=nSteps; iStep++ ) {
    dPhiStar.push_back( calculateDPhiStar( p_a, charge_a,
                                           p_b, charge_b,
                                           (rad_min_in_meters + iStep * rad_step_in_meters),
                                           magnetic_field ) );
  } //for ( unsigned short iStep=0; iStep<nSteps; iStep++ )

  return dPhiStar;
}

//_________________
double StHbtPair::calculateDPhi(const TVector3& p_a, const TVector3& p_b) {
  // Calculate dPhi between two tracks
  return ( p_a.Phi() - p_b.Phi() );
}

//_________________
double StHbtPair::calculateDPhiStar(const TVector3& p_a,
                                    const short& charge_a,
                                    const TVector3& p_b,
                                    const short& charge_b,
                                    const double& radius_in_meters,
                                    const double& magnetic_field) {
  // phi shift at radius R in magnetic field B, with charge and momentum q & p_T is:
  //    φ = arcsin( q * B * R / 2 p_T )
  //
  // Unit analysis:
  //   q * B * R : [Coulomb][Tesla][Meter] = 1.60218e-19 [e][Tesla][Meter]
  //   p_T : [Joule][Second]/[Meter] = 1.60218e-10 [GeV][Second]/[Meter] = 1.60218e-10 / c [GeV/c]
  //
  //  q * B * R / p_T = (1.60218e-19 * c / 1.60218e-10) [e] [Tesla] [Meters] / [GeV/c]
  //                 ~ 0.3 [e] [Tesla] [Meters] / [GeV/c]
  //

  // The difference in phi is calculated by examining the tracks' azimuthal angle
  // at a particular radius of all tracks.
  //
  // \Delta \phi* = \phi_1 - \phi_2
  //        + arcsin \left( \frac{ charge_1 \cdot B_z \cdot R}{2 p_{T1}} \right)
  //        - arcsin \left( \frac{ charge_2 \cdot B_z \cdot R}{2 p_{T2}} \right)

  double UNIT_FACTOR = 0.299792458;
  double prefix = -0.5 * UNIT_FACTOR * magnetic_field * radius_in_meters;
  double shift_a = TMath::ASin( prefix * charge_a / p_a.Perp() );
  double shift_b = TMath::ASin( prefix * charge_b / p_b.Perp() );

  return ( ( p_b.Phi() + shift_b ) - ( p_a.Phi() + shift_a ) );
}

//_________________
double StHbtPair::calculateDEta(const TVector3& a, const TVector3& b) {
  // Calculate dEta between two tracks
  return ( a.Eta() - b.Eta() );
}

//_________________
double StHbtPair::calculateDEtaStar(const TVector3& a, const TVector3& b,
                                    const double& radius_in_meters) {
  // Calculate dEta* (dEta at a given radius)
  double RADIUS_CM = radius_in_meters * 100.0;
  double thetas1 = TMath::Pi() /2.0 - TMath::ATan(a.Z() / RADIUS_CM);
  double thetas2 = TMath::Pi() /2.0 - TMath::ATan(b.Z() / RADIUS_CM);
  double etas1 = -TMath::Log( TMath::Tan(thetas1 / 2.0) );
  double etas2 = -TMath::Log( TMath::Tan(thetas2 / 2.0) );

  return TMath::Abs(etas1 - etas2);
}
