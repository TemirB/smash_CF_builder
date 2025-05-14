//
// Class that returns a StHbtPair with smeared momentum
//

// StHbtMaker headers
#include "StHbtSmearPair.h"

// ROOT headers
#include "TMath.h"

#ifdef __ROOT__
ClassImp(StHbtSmearPair)
#endif


//_________________
StHbtSmearPair::StHbtSmearPair() :
  mSmearedPair(),
  mParticle1(),
  mParticle2(),
  mFracPtRes(0),
  mPhi_a(0),
  mPhi_b(0),
  mPhi_alpha(0),
  mTheta_a(0),
  mTheta_b(0),
  mTheta_alpha(0),
  mHbtRandom(nullptr) {

  setup();
  if ( mHbtRandom ) {
    delete mHbtRandom;
    mHbtRandom = nullptr;
  }
  mHbtRandom = new TRandom3(0);
}

//_________________
StHbtSmearPair::StHbtSmearPair(const StHbtPair* unSmearedPair) {
  setup();
  setUnsmearedPair( unSmearedPair );
}

//_________________
void StHbtSmearPair::setup() {
  mSmearedPair.setTrack1( &mParticle1 );
  mSmearedPair.setTrack2( &mParticle2 );
  if ( !mHbtRandom ) {
    mHbtRandom = new TRandom3(0);
  }
}

//_________________
void StHbtSmearPair::setUnsmearedPair(const StHbtPair* unSmearedPair) {
  mParticle1.resetFourMomentum( smearedMomentum( unSmearedPair->track1()->fourMomentum() ) );
  mParticle2.resetFourMomentum( smearedMomentum( unSmearedPair->track2()->fourMomentum() ) );
}

/**
 * philosophy behind this smearing is as follows:
 * what we *measure* is pT (via curvature), and the angles phi and theta
 * momentum is related to this via
 * px = pT*cos(phi)   --> Dpx = DpT*cos(phi) - pT*sin(phi)*Dphi = px*DpT/pT - py*Dphi
 * py = pT*sin(phi)   --> Dpy = DpT*sin(phi) + pT*cos(phi)*Dphi = py*DpT/pT + px*Dphi
 * pz = pT/tan(theta) --> Dpz = DpT/tan(theta) - pT*Dtheta/(sin(theta))^2
 *                            = pT*(DpT/pT)/tan(theta) - pT*Dtheta/(sin(theta))^2
 *                            = pz*DpT/pT - pT*Dtheta/(sin(theta))^2
 */

//_________________
TLorentzVector StHbtSmearPair::smearedMomentum(TLorentzVector fourmom) {
  double pT = fourmom.Perp();
  double mass2 = fourmom.M2();
  double px = fourmom.X();
  double py = fourmom.Y();
  double pz = fourmom.Z();
  double sin2theta = TMath::Sin( fourmom.Theta() );
  sin2theta = sin2theta * sin2theta;

  double DpT_div_pT = mHbtRandom->Gaus( 0., mFracPtRes );
  double Dphi = mHbtRandom->Gaus( 0., ( mPhi_a + mPhi_b * TMath::Power( pT, mPhi_alpha ) ) );
  double Dtheta = mHbtRandom->Gaus(0. , ( mTheta_a + mTheta_b * TMath::Power( pT, mTheta_alpha ) ) );

  fourmom.SetX( px * ( 1.0 + DpT_div_pT ) - py * Dphi );
  fourmom.SetY( py * ( 1.0 + DpT_div_pT ) + px * Dphi );
  fourmom.SetZ( pz * ( 1.0 + DpT_div_pT ) - pT * Dtheta / sin2theta );
  fourmom.SetE( TMath::Sqrt( mass2 + fourmom.X()*fourmom.X() +
			     fourmom.Y() * fourmom.Y() + fourmom.Z() * fourmom.Z() ) );
  return fourmom;
}
