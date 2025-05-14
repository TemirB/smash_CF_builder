//
// Keeps information about V0/Kinks reconstructed via KFParticle 
//

// C++ headers
#include <iostream>
#include <limits>

// FemtoDst headers
#include "StFemtoKFP.h"

ClassImp(StFemtoKFP)

//________________
StFemtoKFP::StFemtoKFP() : TObject(),
 mMomX{0}, mMomY{0}, mMomZ{0}, mPdgCode{0},
 mMass{0}, mDaughterIds{}, mChi2{0}, mDecPointX{0},
 mDecPointY{0}, mDecPointZ{0}, mDcaKFParticle2Vertex{0},
 mDcaBetweenDaughters{0} {
  /* empty */
}

//________________
StFemtoKFP::StFemtoKFP(const StFemtoKFP &p) : TObject(), 
  mMomX{p.mMomX}, mMomY{p.mMomY}, mMomZ{p.mMomZ}, mPdgCode{p.mPdgCode},
  mMass{p.mMass}, mDaughterIds{p.mDaughterIds}, mChi2{p.mChi2},
  mDecPointX{p.mDecPointX}, mDecPointY{p.mDecPointY}, mDecPointZ{p.mDecPointZ},
  mDcaKFParticle2Vertex{p.mDcaKFParticle2Vertex}, 
  mDcaBetweenDaughters{p.mDcaBetweenDaughters}  {
  /* empty */
}

//________________
void StFemtoKFP::print() {
  std::cout << Form("px/py/pz (GeV/c): %4.2f/%4.2f/%4.2f\n", mMomX, mMomY, mMomZ) 
            << "Mass: " << mMass << " pdgId: " << mPdgCode
            << " chi2: " << chi2()
            << Form("Decay point x/y/z (cm): %5.2f/%5.2f/%5.2f\n", mDecPointX, mDecPointY, mDecPointZ)
            << "dca2vertex: " << mDcaKFParticle2Vertex 
            << " dca daughters: " << mDcaBetweenDaughters
            << " nDaughters: " << mDaughterIds.size() << std::endl;
}

//________________
void StFemtoKFP::setChi2NDF(Float_t chi2) {
  if (chi2<0) mChi2 = std::numeric_limits<unsigned short>::max();
  else
  mChi2 = (chi2 * 100) < std::numeric_limits<unsigned short>::max() ?
    (UShort_t)(chi2 * 100) : std::numeric_limits<unsigned short>::max();
}

//________________
void StFemtoKFP::armenterosPodolanski(TVector3 pMomPos, TVector3 pMomNeg, Float_t arm[2]) {
  Float_t alpha{0}, qt{0};
  Float_t spx = pMomPos.X() + pMomNeg.X();
  Float_t spy = pMomPos.Y() + pMomNeg.Y();
  Float_t spz = pMomPos.Z() + pMomNeg.Z();
  Float_t sp  = TMath::Sqrt(spx*spx + spy*spy + spz*spz);
  if ( sp == 0.0 ) return;
  Float_t pn{0}, pln{0}, plp{0};

  pn = pMomNeg.Mag();
  
  pln  = (pMomNeg.X()*spx + pMomNeg.Y()*spy + pMomNeg.Z()*spz) / sp;
  plp  = (pMomPos.X()*spx + pMomPos.Y()*spy + pMomPos.Z()*spz) / sp;

  if( pn == 0.0) return;
  Float_t ptm  = (1. - ( (pln/pn) * (pln/pn) ) );
  qt = ( ptm >= 0. ) ?  pn * TMath::Sqrt(ptm) : 0;
  alpha = (plp - pln) / (plp + pln);  

  arm[0] = qt;
  arm[1] = alpha;
}
