/**
 * StHbtModelGausLCMSFreezeOutGenerator - freeze-out
 * coordinates generator, generating a 3D gaussian ellipsoid in LCMS
 */

/// C++ headers
#include <math.h>
#include <iostream>

/// StHbtMaker headers
#include "StHbtModelGausLCMSFreezeOutGenerator.h"
#include "StHbtModelHiddenInfo.h"

/// ROOT headers
#include "TMath.h"
#include "TLorentzVector.h"

#ifdef __ROOT__
ClassImp(StHbtModelGausLCMSFreezeOutGenerator);
#endif

//_________________
StHbtModelGausLCMSFreezeOutGenerator::StHbtModelGausLCMSFreezeOutGenerator() :
  mSizeOut(0), mSizeSide(0), mSizeLong(0) {
  // Default constructor
  mRandom = new TRandom3();
}

//_________________
StHbtModelGausLCMSFreezeOutGenerator::StHbtModelGausLCMSFreezeOutGenerator(const StHbtModelGausLCMSFreezeOutGenerator &aModel):
  StHbtBaseModelFreezeOutGenerator(aModel),
  mSizeOut(0), mSizeSide(0), mSizeLong(0) {
  // Copy constructor
  mRandom = new TRandom3();
  setSizeOut( aModel.sizeOut() );
  setSizeSide( aModel.sizeSide() );
  setSizeLong( aModel.sizeLong() );
}

//_________________
StHbtModelGausLCMSFreezeOutGenerator& StHbtModelGausLCMSFreezeOutGenerator::operator=(const StHbtModelGausLCMSFreezeOutGenerator &aModel) {
  // Assignment operator
  if (this != &aModel) {
    mRandom = new TRandom3();
    setSizeOut( aModel.sizeOut() );
    setSizeSide( aModel.sizeSide() );
    setSizeLong( aModel.sizeLong() );
  }

  return *this;
}

//_________________
StHbtModelGausLCMSFreezeOutGenerator::~StHbtModelGausLCMSFreezeOutGenerator() {
  if (mRandom) delete mRandom;
}

//_________________
void StHbtModelGausLCMSFreezeOutGenerator::generateFreezeOut(StHbtPair *aPair) {
  // Generate two-particle emission points with respect
  // to their pair momentum
  // The source is the 3D Gaussian ellipsoid in the LCMS frame

  //StHbtModelHiddenInfo *inf1 = (StHbtModelHiddenInfo *) aPair->Track1()->HiddenInfo();
  //StHbtModelHiddenInfo *inf2 = (StHbtModelHiddenInfo *) aPair->Track2()->HiddenInfo();

  // Mike Lisa
  StHbtTrack *inf1 = (StHbtTrack *) aPair->track1()->track();
  StHbtTrack *inf2 = (StHbtTrack *) aPair->track2()->track();

  if ( (!inf1) || (!inf2) ) {
    std::cout << "Hidden info not created! "  << std::endl; exit(kFALSE);
  }

  //std::cout<<" we are in Freeze-out Generator inf1 inf2  "<<inf1<<"  "<<inf2<<std::endl;
  //std::cout<<" inf1 GetMass "<<((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetPDGPid()<<std::endl;
  //std::cout<<" true mom    " <<((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetTrueMomentum()->x()<<std::endl;

  double tPx = ( ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().X() +
		 ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->trueMomentum().X() );
  double tPy = ( ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().Y() +
		 ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->trueMomentum().Y() );
  double tPz = ( ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().Z() +
		 ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->trueMomentum().Z() );

  // double tPy = inf1->GetTrueMomentum()->y() + inf2->GetTrueMomentum()->y();
  // double tPz = inf1->GetTrueMomentum()->z() + inf2->GetTrueMomentum()->z();

  //std::cout<<" tPx tPy tPz"<<tPx<<" "<<tPy<<" "<<tPz<<std::endl;
  if ( !(tPx==0 && tPy==0 && tPz==0 ) ) {

    double tM1 = ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->mass();
    double tM2 = ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->mass();
    double tE1 = TMath::Sqrt( tM1 * tM1 +
			      ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().Mag2() );
    double tE2 = TMath::Sqrt( tM2 * tM2 +
			      ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->trueMomentum().Mag2() );
    double tEs = tE1 + tE2;

    //std::cout<<" tM1 tM2 tE1 tE2"<<tM1<<" "<<tM2<<" "<<tE2<<std::endl;
    double tPt = TMath::Sqrt(tPx*tPx + tPy*tPy);

    double tRout = mRandom->Gaus(0.0, mSizeOut);
    double tRside = mRandom->Gaus(0.0, mSizeSide);
    double tRlong = mRandom->Gaus(0.0, mSizeLong);

    double tXout = (tPx * tRout + tPy * tRside) / tPt;
    double tXside = (tPy * tRout - tPx * tRside) / tPt;

    double tBetaz = tPz / tEs;
    double tGammaz = 1.0/TMath::Sqrt(1-tBetaz * tBetaz);

    double tXlong = tGammaz * (tRlong + tBetaz * 0);
    double tXtime = tGammaz * (0 + tBetaz * tRlong);

    //std::cout<<" tXout tXside before hidden infor "<<tXout<<" "<<tXside<<std::endl;

    inf1->hiddenInfo()->setEmissionPoint(0.,0.,0.,0.);
    inf2->hiddenInfo()->setEmissionPoint(tXout, tXside, tXlong, tXtime);
    //std::cout<<" after all tXout tXside "<<tXout<<" "<<tXside<<std::endl;

  } // if ( !(tPx==0 && tPy==0 && tPz==0 ) ) {
}
