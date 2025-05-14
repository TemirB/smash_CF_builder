//
// The class allows to perform three-particle analysis
//

// StHbtMaker headers
#include "StHbtTriplet.h"

// ROOT headers
#include "TMath.h"

//_________________
double Triplet_Quality_Calc(StHbtParticle* Track1, StHbtParticle* Track2) {

  unsigned long mapMask0 = 0xFFFFFF00;
  unsigned long mapMask1 = 0x1FFFFF;
  unsigned long padRow1To24Track1 = Track1->topologyMap(0) & mapMask0;
  unsigned long padRow25To45Track1 = Track1->topologyMap(1) & mapMask1;
  unsigned long padRow1To24Track2 = Track2->topologyMap(0) & mapMask0;
  unsigned long padRow25To45Track2 = Track2->topologyMap(1) & mapMask1;
  // AND logic
  unsigned long bothPads1To24 = padRow1To24Track1 & padRow1To24Track2;
  unsigned long bothPads25To45 = padRow25To45Track1 & padRow25To45Track2;
  // XOR logic
  unsigned long onePad1To24 = padRow1To24Track1 ^ padRow1To24Track2;
  unsigned long onePad25To45 = padRow25To45Track1 ^ padRow25To45Track2;
  unsigned long bitI;
  int ibits;
  int Quality = 0;
  double normQual = 0.0;
  for (ibits=8;ibits<=31;ibits++) {
    bitI = 0;
    bitI |= 1UL<<(ibits);
    if ( onePad1To24 & bitI ) {
      Quality++;
      continue;
    }
    else{
      if ( bothPads1To24 & bitI ) Quality--;
    }
  }
  for (ibits=0;ibits<=20;ibits++) {
    bitI = 0;
    bitI |= 1UL<<(ibits);
    if ( onePad25To45 & bitI ) {
      Quality++;
      continue;
    }
    else{
      if ( bothPads25To45 & bitI ) Quality--;
    }
  }
  normQual = (double)Quality / ( (double) (Track1->nHits() + Track2->nHits()) );
  return ( normQual );

}

//_________________
StHbtTriplet::StHbtTriplet() :
  mTrack1( nullptr ),
  mTrack2( nullptr ),
  mTrack3( nullptr ) {
  /* empty */
}

//_________________
StHbtTriplet::StHbtTriplet(StHbtParticle* a, StHbtParticle* b, StHbtParticle* c) :
  mTrack1(a),
  mTrack2(b),
  mTrack3(c) {
  /* empty */
}

//_________________
StHbtTriplet::StHbtTriplet(const StHbtTriplet& trio) :
  mTrack1( trio.mTrack1 ),
  mTrack2( trio.mTrack2 ),
  mTrack3( trio.mTrack3 ) {
  /* emtpy */
}

//_________________
StHbtTriplet::~StHbtTriplet() {
  if(mTrack1) delete mTrack1;
  if(mTrack2) delete mTrack2;
  if(mTrack3) delete mTrack3;
}

//_________________
double StHbtTriplet::qInv() const {
  double dq = TMath::Sqrt( TMath::Abs( (mTrack1->fourMomentum() - mTrack2->fourMomentum() ).M2() ) +
			   TMath::Abs( (mTrack2->fourMomentum() - mTrack3->fourMomentum() ).M2() ) +
			   TMath::Abs( (mTrack3->fourMomentum() - mTrack1->fourMomentum() ).M2() ) );
  return dq;
}

//_________________
double StHbtTriplet::qInv12() const {
  return TMath::Sqrt( TMath::Abs( (mTrack1->fourMomentum() - mTrack2->fourMomentum()).M2() ) );
}

//_________________
double StHbtTriplet::qInv23() const {
  return TMath ::Sqrt( TMath::Abs( (mTrack2->fourMomentum() - mTrack3->fourMomentum()).M2() ) );
}

//_________________
double StHbtTriplet::qInv31() const {
  return TMath::Sqrt( TMath::Abs( (mTrack3->fourMomentum() - mTrack1->fourMomentum()).M2() ) );
}

//_________________
double StHbtTriplet::mInv() const {
  return ( mTrack1->fourMomentum() + mTrack2->fourMomentum() + mTrack3->fourMomentum() ).Mag();
}

//_________________
double StHbtTriplet::kT() const {
  return (mTrack1->fourMomentum() + mTrack2->fourMomentum() + mTrack3->fourMomentum()).Perp() / 3.0f;
}

//_________________
TLorentzVector StHbtTriplet::fourMomentum() const {
  TLorentzVector temp( mTrack1->fourMomentum() + mTrack2->fourMomentum() + mTrack3->fourMomentum() );
  return temp;
}

//_________________
double StHbtTriplet::quality() const {

  double Q1 = Triplet_Quality_Calc(mTrack1, mTrack2);
  double Q2 = Triplet_Quality_Calc(mTrack2, mTrack3);
  double Q3 = Triplet_Quality_Calc(mTrack3, mTrack1);

  if (Q1>Q2) {
    if (Q1>Q3) return Q1;
    else return Q3;
  }
  else
    if (Q2>Q3) return Q2;
    else return Q3;

}

//_________________
double StHbtTriplet::nominalTpcExitSeparation() const {
  TVector3 diff1 = mTrack1->nominalTpcExitPoint() - mTrack2->nominalTpcExitPoint();
  TVector3 diff2 = mTrack2->nominalTpcExitPoint() - mTrack3->nominalTpcExitPoint();
  TVector3 diff3 = mTrack3->nominalTpcExitPoint() - mTrack1->nominalTpcExitPoint();
  if (diff1.Mag() < diff2.Mag()) {
    if (diff1.Mag() < diff3.Mag()) return (diff1.Mag());
    else return (diff3.Mag());
  }
  else if (diff2.Mag() < diff3.Mag()) return (diff2.Mag());
  else return (diff3.Mag());
}

//_________________
double StHbtTriplet::nominalTpcEntranceSeparation() const {
  TVector3 diff1 = mTrack1->nominalTpcEntrancePoint() - mTrack2->nominalTpcEntrancePoint();
  TVector3 diff2 = mTrack2->nominalTpcEntrancePoint() - mTrack3->nominalTpcEntrancePoint();
  TVector3 diff3 = mTrack3->nominalTpcEntrancePoint() - mTrack1->nominalTpcEntrancePoint();
  if (diff1.Mag() < diff2.Mag()) {
    if (diff1.Mag() < diff3.Mag()) return (diff1.Mag());
    else return (diff3.Mag());
  }
  else if (diff2.Mag() < diff3.Mag()) return (diff2.Mag());
  else return (diff3.Mag());
}

//_________________
double StHbtTriplet::nominalTpcAverageSeparation() const {
  TVector3 diff1,diff2,diff3;
  double AveSep1 = 0.0;
  double AveSep2 = 0.0;
  double AveSep3 = 0.0;
  int ipt=0;
  for (ipt=0; ipt < (mTrack1->mNumberOfPoints); ipt++){
    diff1 = mTrack1->nominalPosSample(ipt) - mTrack2->nominalPosSample(ipt);
    AveSep1 += diff1.Mag();
    diff2 = mTrack2->nominalPosSample(ipt) - mTrack3->nominalPosSample(ipt);
    AveSep2 += diff2.Mag();
    diff3 = mTrack3->nominalPosSample(ipt) - mTrack1->nominalPosSample(ipt);
    AveSep3 += diff3.Mag();
  }
  AveSep1 = AveSep1 / (mTrack1->mNumberOfPoints);
  AveSep2 = AveSep1 / (mTrack1->mNumberOfPoints);
  AveSep3 = AveSep1 / (mTrack1->mNumberOfPoints);
  if (AveSep1<AveSep2) {
    if (AveSep1<AveSep3) return (AveSep1);
    else return (AveSep3);
  }
  else if (AveSep2<AveSep3) return (AveSep2);
  else return (AveSep3);
}
