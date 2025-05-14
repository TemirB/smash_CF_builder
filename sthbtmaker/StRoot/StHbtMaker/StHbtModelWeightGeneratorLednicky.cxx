/**
 * \class StHbtModelWeightGenerator
 * \brief Femtoscopic weight generator that called Richard Lednicky's code
 *
 * The most advanced weight generator available. Supports a large
 * number of different pair types and interaction types. Can calculate
 * pair weights coming from quantum statistics, Coulomb and strong interactions
 * or any combination of the three, as applicable.
 * This class is a wrapper for the fortran code provided by Richard
 * Lednicky.
 */

// C++ headers
//#include <strstream.h>
//#include <iomanip.h>
//#include <stream>
//#include <iomanip>
#include <sstream>
#include <iostream>

// StHbtMaker headers
#include "StHbtModelWeightGeneratorLednicky.h"
#include "StHbtModelHiddenInfo.h"
#include "StHbtPair.h"

// ROOT headers
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#ifdef SOLARIS
# ifndef false
typedef int bool;
#define false 0
#define true 1
# endif
#endif

#ifdef WIN32
# ifdef CERNLIB_MSSTDCALL
#  define F77_UCASE
#  define type_of_call _stdcall
#  ifndef CERNLIB_QXCAPT
#    define CERNLIB_QXCAPT
#  endif
# else
#  define F77_LCASE
#  ifndef CERNLIB_QXNO_SC
#    define CERNLIB_QXNO_SC
#  endif
# endif
# define type_of_call  _stdcall
# define DEFCHARD   const char* , const int
# define DEFCHARL
# define PASSCHARD(string) string, strlen(string)
# define PASSCHARL(string)
#else
# define DEFCHARD     const char*
# define DEFCHARL   , const int
# define PASSCHARD(string) string
# define PASSCHARL(string) , strlen(string)
#endif
#ifdef CERNLIB_QXCAPT
#  define F77_NAME(name,NAME) NAME
#else
#  if defined(CERNLIB_QXNO_SC)
#    define F77_NAME(name,NAME) name
#  else
#    define F77_NAME(name,NAME) name##_
#  endif
#endif
#ifndef type_of_call
# define type_of_call
#endif

// --- Prototype of the function used in the weight calculator
//     (in StHbtFsiWeightLedinicky.F)
#define fsiin F77_NAME(fsiin,FSIIN)
extern "C" {void type_of_call F77_NAME(fsiin,FSIIN)(const int &itest,const int &ich, const int &iqs, const int &isi,const int &i3c);}
#define llini F77_NAME(llini,LLINI)
extern "C" {void type_of_call F77_NAME(llini,LLINI)(const int &lll,const int &ns, const int &itest);}

#define fsinucl F77_NAME(fsinucl,FSINUCL)
extern "C" {void type_of_call  F77_NAME(fsinucl,FSINUCL)(const double &mn,const double &cn);}
#define fsimomentum F77_NAME(fsimomentum,FSIMOMENTUM)
extern "C" {void type_of_call F77_NAME(fsimomentum,FSIMOMENTUM)(double &p1,double &p2);}
#define fsiposition F77_NAME(fsiposition,FSIPOSITION)
extern "C" {void type_of_call F77_NAME(fsiposition,FSIPOSITION)(double &x1,double &x2);}
#define fsiw F77_NAME(fsiw,FSIW)
extern "C" {void type_of_call F77_NAME(fsiw,FSIW)(const int &i,double &weif,
						  double &wei,double &wein);}
#define ltran12 F77_NAME(ltran12,LTRAN12)
extern "C" {void type_of_call ltran12_();}

//K+K- model type
#define setkpkmmodel F77_NAME(setkpkmmodel,SETKPKMMODEL)
extern "C" {void type_of_call F77_NAME(setkpkmmodel,SETKPKMMODEL)(const int &i_model,const int &i_PhiOffOn);}

// Test function for Lambda potential
//#define printlam F77_NAME(printlam,PRINTLAM)
//extern "C" {void type_of_call printlam_();}
//there is not PRINTLAM in *.F file

// --- Additional prototyping of some CERN functions (in FsiTool.F)
typedef float   REAL;
typedef struct { REAL re; REAL im; } COMPLEX;
#define cgamma F77_NAME(cgamma,CGAMMA)
extern "C" {COMPLEX type_of_call cgamma_(COMPLEX*);}

#ifdef __ROOT__
ClassImp(StHbtModelWeightGeneratorLednicky);
#endif

//_________________
StHbtModelWeightGeneratorLednicky::StHbtModelWeightGeneratorLednicky() :
  StHbtBaseModelWeightGenerator(),
  mWei(0), mWein(0), mWeif(0), mWeightDen(0),
  mItest(0), mIch(1), mIqs(1), mIsi(1), mI3c(0),
  mNuclMass(1.), mNuclCharge(0.),
  mSphereApp(false), mT0App(false),
  mLL(0), mNuclChargeSign(1), mSwap(0), mLLMax(30), mLLName(0),
  mNumProcessPair(0), mNumbNonId(0),
  mKpKmModel(14), mPhi_OffOn(1) {

  // Default constructor
  mLLName=new char*[mLLMax+1];
  mNumProcessPair=new int[mLLMax+1];
  int i;
  for (i=1;i<=mLLMax;i++) { mLLName[i]=new char[40]; mNumProcessPair[i]=0; }
  strncpy( mLLName[1], "neutron neutron", 40 );
  strncpy( mLLName[2], "proton proton", 40 );
  strncpy( mLLName[3], "neutron proton", 40 );
  strncpy( mLLName[4], "alpha alpha", 40 );
  strncpy( mLLName[5], "pi+ pi-", 40 );
  strncpy( mLLName[6], "pi0 pi0", 40 );
  strncpy( mLLName[7], "pi+ pi+", 40 );
  strncpy( mLLName[8], "neutron deuteron", 40 );
  strncpy( mLLName[9], "proton deuteron", 40 );
  strncpy( mLLName[10], "pi+ K-", 40 );
  strncpy( mLLName[11], "pi+ K+", 40 );
  strncpy( mLLName[12], "pi+ proton", 40 );
  strncpy( mLLName[13], "pi- proton", 40 );
  strncpy( mLLName[14], "K+ K-", 40 );
  strncpy( mLLName[15], "K+ K+", 40 );
  strncpy( mLLName[16], "K+ proton", 40 );
  strncpy( mLLName[17], "K- proton", 40 );
  strncpy( mLLName[18], "deuteron deuteron", 40 );
  strncpy( mLLName[19], "deuton alpha", 40 );
  strncpy( mLLName[20], "triton triton", 40 );
  strncpy( mLLName[21], "triton alpha", 40 );
  strncpy( mLLName[22], "K0 K0", 40 );
  strncpy( mLLName[23], "K0 K0b", 40 );
  strncpy( mLLName[24], "deuteron triton", 40 );
  strncpy( mLLName[25], "proton triton", 40 );
  strncpy( mLLName[26], "proton alpha", 40 );
  strncpy( mLLName[27], "proton lambda", 40 );
  strncpy( mLLName[28], "neutron lambda", 40 );
  strncpy( mLLName[29], "Lambda lambda", 40 );
  strncpy( mLLName[30], "Proton Anti-proton", 40 );
  fsiInit();
  fsiNucl();
}

//_________________
StHbtModelWeightGeneratorLednicky::StHbtModelWeightGeneratorLednicky(const StHbtModelWeightGeneratorLednicky &aWeight):
  StHbtBaseModelWeightGenerator(),
  mWei(0), mWein(0), mWeif(0), mWeightDen(0),
  mItest(0), mIch(1), mIqs(1), mIsi(1), mI3c(0),
  mNuclMass(1.), mNuclCharge(0.),
  mSphereApp(false), mT0App(false) ,
  mLL(0), mNuclChargeSign(1), mSwap(0), mLLMax(30), mLLName(0),
  mNumProcessPair(0), mNumbNonId(0),
  mKpKmModel(14), mPhi_OffOn(1) {
  // Copy constructor
  mWei = aWeight.mWei;
  mWein = aWeight.  mWein;
  mWeif = aWeight. mWeif;
  mWeightDen = aWeight.mWeightDen;

  mItest = aWeight.mItest;
  mIch = aWeight.mIch;
  mIqs = aWeight.mIqs;
  mIsi = aWeight.mIsi;
  mI3c = aWeight.mI3c;
  mNuclMass = aWeight.mNuclMass;
  mNuclCharge = aWeight.mNuclCharge;
  mSphereApp = aWeight.mSphereApp;
  mT0App = aWeight.mT0App;
  mLL = aWeight.mLL;
  mNuclChargeSign = aWeight.mNuclChargeSign;
  mSwap = aWeight.mSwap;
  mLLName = aWeight.mLLName;
  mNumProcessPair = aWeight.mNumProcessPair;
  mNumbNonId = aWeight.mNumbNonId;
  mLLName=new char*[mLLMax+1];
  mNumProcessPair=new int[mLLMax+1];
  mKpKmModel = aWeight.mKpKmModel;
  mPhi_OffOn = aWeight.mPhi_OffOn;
  int i;
  for (i=1;i<=mLLMax;i++) {mLLName[i]=new char[40];mNumProcessPair[i]=0;}
  strncpy( mLLName[1],"neutron neutron",40);
  strncpy( mLLName[2],"proton proton",40);
  strncpy( mLLName[3],"neutron proton",40);
  strncpy( mLLName[4],"alpha alpha",40);
  strncpy( mLLName[5],"pi+ pi-",40);
  strncpy( mLLName[6],"pi0 pi0",40);
  strncpy( mLLName[7],"pi+ pi+",40);
  strncpy( mLLName[8],"neutron deuteron",40);
  strncpy( mLLName[9],"proton deuteron",40);
  strncpy( mLLName[10],"pi+ K-",40);
  strncpy( mLLName[11],"pi+ K+",40);
  strncpy( mLLName[12],"pi+ proton",40);
  strncpy( mLLName[13],"pi- proton",40);
  strncpy( mLLName[14],"K+ K-",40);
  strncpy( mLLName[15],"K+ K+",40);
  strncpy( mLLName[16],"K+ proton",40);
  strncpy( mLLName[17],"K- proton",40);
  strncpy( mLLName[18],"deuteron deuteron",40);
  strncpy( mLLName[19],"deuton alpha",40);
  strncpy( mLLName[20],"triton triton",40);
  strncpy( mLLName[21],"triton alpha",40);
  strncpy( mLLName[22],"K0 K0",40);
  strncpy( mLLName[23],"K0 K0b",40);
  strncpy( mLLName[24],"deuteron triton",40);
  strncpy( mLLName[25],"proton triton",40);
  strncpy( mLLName[26],"proton alpha",40);
  strncpy( mLLName[27],"proton lambda",40);
  strncpy( mLLName[28],"neutron lambda",40);
  strncpy( mLLName[29],"Lambda lambda",40);
  strncpy( mLLName[30],"Proton Anti-proton",40);
  fsiInit();
  fsiNucl();
}

//_________________
StHbtModelWeightGeneratorLednicky& StHbtModelWeightGeneratorLednicky::operator=(const StHbtModelWeightGeneratorLednicky& aWeight) {

  // Assignment operator
  if (this != &aWeight) {

    mWei = aWeight.mWei;
    mWein = aWeight.  mWein;
    mWeif = aWeight. mWeif;
    mWeightDen = aWeight.mWeightDen;

    mItest = aWeight.mItest;
    mIch = aWeight.mIch;
    mIqs = aWeight.mIqs;
    mIsi = aWeight.mIsi;
    mI3c = aWeight.mI3c;
    mNuclMass = aWeight.mNuclMass;
    mNuclCharge = aWeight.mNuclCharge;
    mSphereApp = aWeight.mSphereApp;
    mT0App = aWeight.mT0App;
    mLL = aWeight.mLL;
    mNuclChargeSign = aWeight.mNuclChargeSign;
    mSwap = aWeight.mSwap;
    //  mLLName = aWeight.mLLName;
    mNumProcessPair = aWeight.mNumProcessPair;
    mNumbNonId = aWeight.mNumbNonId;
    if (mLLName) free(mLLName);
    mLLName=new char*[mLLMax+1];
    if (mNumProcessPair) free(mNumProcessPair);
    mNumProcessPair=new int[mLLMax+1];
    mKpKmModel = aWeight.mKpKmModel;
    mPhi_OffOn = aWeight.mPhi_OffOn;
    int i;
    for (i=1;i<=mLLMax;i++) {mLLName[i]=new char[40];mNumProcessPair[i]=0;}
    strncpy( mLLName[1],"neutron neutron",40);
    strncpy( mLLName[2],"proton proton",40);
    strncpy( mLLName[3],"neutron proton",40);
    strncpy( mLLName[4],"alpha alpha",40);
    strncpy( mLLName[5],"pi+ pi-",40);
    strncpy( mLLName[6],"pi0 pi0",40);
    strncpy( mLLName[7],"pi+ pi+",40);
    strncpy( mLLName[8],"neutron deuteron",40);
    strncpy( mLLName[9],"proton deuteron",40);
    strncpy( mLLName[10],"pi+ K-",40);
    strncpy( mLLName[11],"pi+ K+",40);
    strncpy( mLLName[12],"pi+ proton",40);
    strncpy( mLLName[13],"pi- proton",40);
    strncpy( mLLName[14],"K+ K-",40);
    strncpy( mLLName[15],"K+ K+",40);
    strncpy( mLLName[16],"K+ proton",40);
    strncpy( mLLName[17],"K- proton",40);
    strncpy( mLLName[18],"deuteron deuteron",40);
    strncpy( mLLName[19],"deuton alpha",40);
    strncpy( mLLName[20],"triton triton",40);
    strncpy( mLLName[21],"triton alpha",40);
    strncpy( mLLName[22],"K0 K0",40);
    strncpy( mLLName[23],"K0 K0b",40);
    strncpy( mLLName[24],"deuteron triton",40);
    strncpy( mLLName[25],"proton triton",40);
    strncpy( mLLName[26],"proton alpha",40);
    strncpy( mLLName[27],"proton lambda",40);
    strncpy( mLLName[28],"neutron lambda",40);
    strncpy( mLLName[29],"Lambda lambda",40);
    strncpy( mLLName[30],"Proton Anti-proton",40);
    fsiInit();
    fsiNucl();
  }

  return *this;
}

//_________________
	double StHbtModelWeightGeneratorLednicky::generateWeight(StHbtPair* aPair) {

  // Get hidden information pointers
  StHbtTrack *inf1 = (StHbtTrack*)aPair->track1()->track();
  StHbtTrack *inf2 = (StHbtTrack*)aPair->track2()->track();

  // Calculate pair variables
  double tPx = ( ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().X()  +
		 						 ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->trueMomentum().X() );
  double tPy = ( ( (StHbtModelHiddenInfo*)inf1->hiddenInfo())->trueMomentum().Y() +
		 						 ( (StHbtModelHiddenInfo*)inf2->hiddenInfo())->trueMomentum().Y() );
  double tPz = ( ( (StHbtModelHiddenInfo*)inf1->hiddenInfo())->trueMomentum().Z() +
		 						 ( (StHbtModelHiddenInfo*)inf2->hiddenInfo())->trueMomentum().Z() );

  double tM1 = ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->mass();
  double tM2 = ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->mass();

  double tE1 = TMath::Sqrt( tM1*tM1 +
			    ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().Mag2() );
  double tE2 = TMath::Sqrt( tM2*tM2 +
			    ( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->trueMomentum().Mag2() );

  double tE  = tE1 + tE2;
  double tPt = tPx*tPx + tPy*tPy;
  double tMt = tE*tE - tPz*tPz;     //mCVK;
  double tM  = TMath::Sqrt(tMt - tPt);
  tMt = TMath::Sqrt( tMt );
  tPt = TMath::Sqrt( tPt );

  if (tMt==0 || tE==0 || tM==0 || tPt==0 ) {
    std::cout<<" weight generator zero tPt || tMt || tM || tPt"<<tM1<<" "<<tM2<< std::endl;
    return 0;
  }

  //double tBetat = tPt/tMt;

  // Boost to LCMS
  double tBeta = tPz/tE;
  double tGamma = tE/tMt;

  double pX = ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().X();
  double pY = ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().Y();
  double pZ = ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum().Z();

  mKStarLong = tGamma * (pZ - tBeta * tE1);
  double tE1L = tGamma * (tE1  - tBeta * pZ);

  // Rotate in transverse plane
  mKStarOut  = ( pX*tPx + pY*tPy)/tPt;
  mKStarSide = (-pX*tPy + pY*tPx)/tPt;

  // Boost to pair cms
  mKStarOut = tMt/tM * (mKStarOut - tPt/tMt * tE1L);

  //tBetat = tPt/tMt;

  double tDX = inf1->hiddenInfo()->emissionPoint().X() - inf2->hiddenInfo()->emissionPoint().X();
  double tDY = inf1->hiddenInfo()->emissionPoint().Y() - inf2->hiddenInfo()->emissionPoint().Y();
  double tRLong = inf1->hiddenInfo()->emissionPoint().Z() - inf2->hiddenInfo()->emissionPoint().Z();
  double tDTime = inf1->hiddenInfo()->emissionPoint().T() - inf2->hiddenInfo()->emissionPoint().T();

  double tROut = (tDX*tPx + tDY*tPy)/tPt;
  double tRSide = (-tDX*tPy + tDY*tPx)/tPt;


  //std::cout<<"Weight generator"<<" tDX "<<tDX<<" tDY "<<tDY<<"tRLong "<<tRLong<<endl;

 /*
   std::cout << "Got points 1 " << inf1->GetEmissionPoint()->x()
   << "  " <<  inf1->GetEmissionPoint()->y() << " "  <<
    inf1->GetEmissionPoint()->z()
     << "  " << inf1->GetEmissionPoint()->t()<< endl;

 	 std::cout << "Got points 2 " << inf2->GetEmissionPoint()->x()
   << "  " <<  inf2->GetEmissionPoint()->y() << " "  <<
    inf2->GetEmissionPoint()->z()
     << "  " << inf2->GetEmissionPoint()->t()<< endl;
	*/

  mRStarSide = tRSide;
  mRStarLong = tGamma*(tRLong - tBeta* tDTime);

  double tDTimePairLCMS = tGamma * (tDTime - tBeta * tRLong);

  tBeta = tPt/tMt;
  tGamma = tMt/tM;

  mRStarOut = tGamma*(tROut - tBeta* tDTimePairLCMS);
  mRStar = TMath::Sqrt( mRStarOut * mRStarOut + mRStarSide * mRStarSide + mRStarLong * mRStarLong );
  mKStar = TMath::Sqrt( mKStarOut * mKStarOut + mKStarSide * mKStarSide + mKStarLong * mKStarLong );

  //std::cout << "-- weights generator : Got out side " << mRStarOut << " " << mRStarSide << endl;

  if ( !setPid( ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->pdgPid(),
								( (StHbtModelHiddenInfo*)inf2->hiddenInfo() )->pdgPid() ) ) {

    mWeightDen=1.;
    //  std::cout<<" bad PID weight generator pdg1 "<<((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetPDGPid()<<" pdg2 "<<((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetPDGPid() << std::endl;
    return 1; //non-correlated
  }
  else { // Good Pid

    // std::cout<<" good PID weight generator pdg1 "<<((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetPDGPid()<<" pdg2 "<<((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetPDGPid() << std::endl;

    TVector3 p;
    p = ( (StHbtModelHiddenInfo*)inf1->hiddenInfo() )->trueMomentum();
    double p1[] = { p.X(), p.Y(), p.Z() };
    p= ( (StHbtModelHiddenInfo*)inf2->hiddenInfo())->trueMomentum();
    double p2[] = { p.X(), p.Y(), p.Z() };

    if ( (p1[0] == p2[0] ) && ( p1[1] == p2[1] ) && ( p1[2] == p2[2] ) ) {
      mWeightDen=0.;
      return 0;
    }

    if (mSwap) {
      fsimomentum(*p2,*p1);
    }
    else {
      fsimomentum(*p1,*p2);
    }

    TLorentzVector tPoint;
    //    tPoint=((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetEmissionPoint();
    tPoint = inf1->hiddenInfo()->emissionPoint();

    //int pdg1 = ( (StHbtModelHiddenInfo*)inf1->hiddenInfo())->pdgPid();
    //int pdg2 = ( (StHbtModelHiddenInfo*)inf2->hiddenInfo())->pdgPid();

    // if(pdg1==!211||pdg2!=211)std::cout << "Weight pdg1 pdg2 = " << pdg1<<" "<<pdg2<< endl;
    // std::cout << "LL:in GetWeight = " << mLL << std::endl;

    double x1[] = { tPoint.X(), tPoint.Y(), tPoint.Z(), tPoint.T() };
    //    tPoint=((StHbtModelHiddenInfo*)inf1->GetHiddenInfo())->GetEmissionPoint();
    tPoint = inf2->hiddenInfo()->emissionPoint();
    double x2[] = { tPoint.X(), tPoint.Y(), tPoint.Z(), tPoint.T() };
    if ( ( x1[0] == x2[0] ) && ( x1[1] == x2[1] ) && ( x1[2] == x2[2] ) && ( x1[3] == x2[3] ) ) {
      mWeightDen=0.;
      return 0;
    }

    if (mSwap) {
      fsiposition(*x2,*x1);
    }
    else {
      fsiposition(*x1,*x2);
    }

    fsiSetLL();
    ltran12();
    fsiw(1, mWeif, mWei, mWein);

    // std::cout<<" mWeif "<<mWeif<<" mWei "<<mWei<<" mWein "<<mWein << std::endl;
    if (mI3c==0) return mWein;
    mWeightDen=mWeif;
    return mWei;
  }
}

//_________________
double StHbtModelWeightGeneratorLednicky::generateSingleParticleThirdBodyWeight(const TLorentzVector &freezeOutCoordinate, const TLorentzVector &fourMom, const int &pid) {
  // Use the same particle to calculate p-N weight using Richard's code
  // Final p-N weight is sqrt(WEIF)
  // "It's not a bug, it's a feature!"

  if ( !setPid( pid, pid) ) {
    mWeightDen=1.;
    return 1.; // non-correlated
  }
  else { // Good Pid

    TVector3 p;
    p = fourMom.Vect();
    double p1[] = { p.X(), p.Y(), p.Z() };
    p = fourMom.Vect();
    double p2[] = { p.X(), p.Y(), p.Z() };

    if (mSwap) {
      fsimomentum(*p2,*p1);
    }
    else {
      fsimomentum(*p1,*p2);
    }

    TLorentzVector tPoint;
    tPoint = freezeOutCoordinate;

    double x1[] = { tPoint.X(), tPoint.Y(), tPoint.Z(), tPoint.T() };
    tPoint = freezeOutCoordinate;
    double x2[] = { tPoint.X(), tPoint.Y(), tPoint.Z(), tPoint.T() };

    if (mSwap) {
      fsiposition(*x2,*x1);
    }
    else {
      fsiposition(*x1,*x2);
    }

    fsiSetLL();
    ltran12();
    fsiw(1, mWeif, mWei, mWein);

    // std::cout<<" mWeif "<<mWeif<<" mWei "<<mWei<<" mWein "<<mWein << std::endl;
    if (mI3c==0) return 1.;
    mWeightDen=mWeif;
    return TMath::Sqrt(mWeif);
  }
}

//_________________
StHbtString StHbtModelWeightGeneratorLednicky::report() {
  // Create report
  std::ostringstream tStr;
  tStr << "Lednicky afterburner calculation for  Correlation -  Report" << std::endl;
  tStr << "    Setting : Quantum : " << ((mIqs) ? "On" : "Off");
  tStr << " - Coulbomb : " << ((mIch) ? "On" : "Off") ;
  tStr << " - Strong : " << ((mIsi) ? "On" : "Off");
  tStr << std::endl;
  tStr << "              3-Body : " << ((mI3c) ? "On"  : "Off") ;
  if (mI3c) tStr << " Mass=" <<  mNuclMass << " - Charge= " << mNuclCharge ;
  tStr << std::endl;
  tStr << "    " << mNumProcessPair[0] << " Pairs have been Processed :" << std::endl;
  int i;
  for(i=1;i<=mLLMax;i++) {
    if (mNumProcessPair[i])
      tStr << "         " << mNumProcessPair[i] << " " << mLLName[i] << std::endl;
  }
  if (mNumbNonId)
    tStr << "         "<< mNumbNonId << " Non Identified" << std::endl;
  StHbtString returnThis = tStr.str();
  return returnThis;
}

//_________________
void StHbtModelWeightGeneratorLednicky::fsiInit(){
  // Initialize weight generation module
  std::cout << "***** StHbtModelWeightGeneratorLednicky check fsiInit *****" << std::endl;
  std::cout <<"mItest dans FsiInit() = " << mItest << std::endl;
  std::cout <<"mIch dans FsiInit() = " << mIch << std::endl;
  std::cout <<"mIqs dans FsiInit() = " << mIqs << std::endl;
  std::cout <<"mIsi dans FsiInit() = " << mIsi << std::endl;
  std::cout <<"mI3c dans FsiInit() = " << mI3c << std::endl;

  fsiin(mItest,mIch,mIqs,mIsi,mI3c);
}

//_________________
void StHbtModelWeightGeneratorLednicky::fsiSetKpKmModelType() {
  // Initialize K+K- model type
  std::cout<<"***** StHbtModelWeightGeneratorLednicky check fsiInit initialize K+K- model"
    << "type with FsiSetKpKmModelType(), type= " << mKpKmModel << " PhiOffON= " << mPhi_OffOn
	   <<" *****" << std::endl;
  setkpkmmodel(mKpKmModel,mPhi_OffOn);
  std::cout << "-----------------END fsiSetKpKmModelType-------" << std::endl;
}

//_________________
void StHbtModelWeightGeneratorLednicky::fsiNucl() {
  // initialize weight generation taking into account the residual charge

  //   std::cout << "*******************StHbtModelWeightGeneratorLednicky check FsiNucl ************" << std::endl;
  //   std::cout <<"mNuclMass dans FsiNucl() = " << mNuclMass << std::endl;
  //   std::cout <<"mNuclCharge dans FsiNucl() = " << mNuclCharge << std::endl;
  //   std::cout <<"mNuclChargeSign dans FsiNucl() = " << mNuclChargeSign << std::endl;
  fsinucl(mNuclMass,mNuclCharge*mNuclChargeSign);
}

//_________________
void StHbtModelWeightGeneratorLednicky::fsiSetLL() {
  // Set internal pair type for the module
  int tNS;
  if ( mSphereApp || (mLL>5) ) {
    if (mT0App) {
      tNS=4;
    }
    else {
      tNS=2;
    }
  }
  else {
    tNS=1;
  }

  //std::cout<<"*********************** StHbtModelWeightGeneratorLednicky::FsiSetLL() *********************"<<std::endl;
  if ( mNS_4 == 4 ) tNS=4; //K+K- analisys

  //std::cout <<"mLL dans FsiSetLL() = "<< mLL << std::endl;
  //std::cout <<"tNS dans FsiSetLL() = "<< tNS << std::endl;
  //std::cout <<"mItest dans FsiSetLL() = "<< mItest << std::endl;

  //std::cout <<"mLL dans FsiSetLL() = "<< mLL << std::endl;
   //std::cout <<"tNS dans FsiSetLL() = "<< tNS << std::endl;
  // std::cout <<"mItest dans FsiSetLL() = "<< mItest << std::endl;

  llini(mLL, tNS, mItest);
 // std::cout<<" end of FsiSetLL"<<std::endl;
}

//_________________
bool StHbtModelWeightGeneratorLednicky::setPid(const int& aPid1, const int& aPid2) {
  // Set calculated system for basing on particles' pids
  static const int ksPi0Pid = 111;
  static const int ksPionPid = 211;
  static const int ksK0Pid = 311;
  static const int ksKPid = 321;
  static const int ksNeutPid = 2112;
  static const int ksProtPid = 2212;
  static const int ksLamPid = 3122;

  // std::cout << "in SetPiD Setting PID to " << aPid1 << " " << aPid2 << std::endl;

  int tPidl,tPidh;
  int tChargeFactor=1;

  if ( TMath::Abs( aPid1 ) < TMath::Abs( aPid2 ) ) {
    if (aPid1<0) tChargeFactor=-1;
    tPidl=aPid1*tChargeFactor;
    tPidh=aPid2*tChargeFactor;
    mSwap=false;
  }
  else {
    if (aPid2<0) tChargeFactor=-1;
    tPidl=aPid2*tChargeFactor;
    tPidh=aPid1*tChargeFactor;
    mSwap=true;
  }
  switch (tPidl) {
  case ksPionPid:
    switch (tPidh) {
    case -ksPionPid:   mLL=5; tChargeFactor*=1 ;break;
    case ksPionPid:    mLL=7; tChargeFactor*=1 ;break;
    case -ksKPid:      mLL=10;tChargeFactor*=1 ;break;
    case ksKPid:       mLL=11;tChargeFactor*=1 ;break;
    case ksProtPid:    mLL=12;tChargeFactor*=1 ;break;
    case -ksProtPid:   mLL=13;tChargeFactor*=-1;break;
    default: mLL=0;
    }
    break;
  case ksProtPid:
    switch (tPidh) {
    case ksProtPid:    mLL=2; tChargeFactor*=1 ;break;
    case ksLamPid:     mLL=27;tChargeFactor*=1 ;break;
    case -ksProtPid:   mLL=30;tChargeFactor*=1 ;break;
    default: mLL=0;
    }
    break;
  case ksKPid:
    switch (tPidh) {
    case -ksKPid:      mLL=14;tChargeFactor*=1 ;break;
    case ksKPid:       mLL=15;tChargeFactor*=1 ;break;
    case ksProtPid:    mLL=16;tChargeFactor*=1 ;break;
    case -ksProtPid:   mLL=17;tChargeFactor*=-1 ;break;
    default: mLL=0;
    }
    break;
  case ksK0Pid:
    switch (tPidh) {
    case ksK0Pid:         mLL=22;tChargeFactor*=1 ;break;
    case -ksK0Pid:        mLL=23;tChargeFactor*=1 ;break;
    default: mLL=0;
    }
    break;
  case ksPi0Pid:
    switch (tPidh) {
    case ksPi0Pid:        mLL=6; tChargeFactor*=1 ;break;
    default: mLL=0;
    }
    break;
  case ksNeutPid:
    switch (tPidh) {
    case ksNeutPid:      mLL=1; tChargeFactor*=1 ;break;
    case ksProtPid:      mLL=3; tChargeFactor*=1 ;break;
    case ksLamPid:       mLL=28;tChargeFactor*=1 ;break;
    default: mLL=0;
    }
    break;                                             //Gael 21May02
  case ksLamPid:                                        //Gael 21May02
    switch (tPidh) {                                   //Gael 21May02
    case ksLamPid:       mLL=29;tChargeFactor*=1 ;break;//Gael 21May02
    default: mLL=0;                                    //Gael 21May02
    }                                                 //Gael 21May02
    break;                                             //Gael 21May02
  default: mLL=0;
  }
  if (tChargeFactor!=mNuclChargeSign) {
    mNuclChargeSign=tChargeFactor;
    FsiNucl();
  }
  (mNumProcessPair[0])++;
  if (mLL) {
    (mNumProcessPair[mLL])++;
    return true;
  }
  else {
    mNumbNonId++;
    return false;
  }

  //   std::cout << "*******************StHbtModelWeightGeneratorLednicky check SetPid ************" << std::endl;
  //  std::cout << "mLL=="<< mLL << std::endl;
  //  std::cout << "mNuclCharge=="<< mNuclCharge << std::endl;
}

//_________________
StHbtModelWeightGeneratorLednicky::~StHbtModelWeightGeneratorLednicky() {
  // Destructor
  if (mLLName) delete [] mLLName;
  if (mNumProcessPair) delete [] mNumProcessPair;
  /* empty */
}

//_________________
void StHbtModelWeightGeneratorLednicky::setPairType(const int& aPairType) {
  // Set calculated system basing on the pair type
  mPairType = aPairType;
  if (mPairType == fgkPionPlusPionPlus)    setPid(211,211);
  if (mPairType == fgkPionPlusPionMinus )  setPid(211, -211);
  if (mPairType == fgkKaonPlusKaonPlus )   setPid(321, 321);
  if (mPairType == fgkKaonPlusKaonMinus )  setPid(321, -321);
  if (mPairType == fgkProtonProton )       setPid(2212, 2212);
  if (mPairType == fgkProtonAntiproton )   setPid(2212, -2212);
  if (mPairType == fgkPionPlusKaonPlus )   setPid(211, 321);
  if (mPairType == fgkPionPlusKaonMinus )  setPid(211, -321);
  if (mPairType == fgkPionPlusProton )     setPid(211, 2212);
  if (mPairType == fgkPionPlusAntiproton ) setPid(211, -2212);
  if (mPairType == fgkKaonPlusProton )     setPid(321, 2212);
  if (mPairType == fgkKaonPlusAntiproton ) setPid(321, -2212);
}

//_________________
void StHbtModelWeightGeneratorLednicky::setPairTypeFromPair(StHbtPair *aPair) {
  // Set calculated system based on the hidden info in the pair
  StHbtModelHiddenInfo *inf1 = ( StHbtModelHiddenInfo *) aPair->track1()->hiddenInfo();
  StHbtModelHiddenInfo *inf2 = ( StHbtModelHiddenInfo *) aPair->track2()->hiddenInfo();

  const int ktPid1 = inf1->pdgPid();
  const int ktPid2 = inf2->pdgPid();

  if      (((ktPid1 ==   211) && (ktPid2 ==   211)) ||
           ((ktPid1 ==  -211) && (ktPid2 ==  -211)))
    mPairType = fgkPionPlusPionPlus;
  else if (((ktPid1 ==  -211) && (ktPid2 ==   211)) ||
           ((ktPid1 ==   211) && (ktPid2 ==  -211)))
    mPairType = fgkPionPlusPionMinus;
  else if (((ktPid1 ==   321) && (ktPid2 ==   321)) ||
           ((ktPid1 ==  -321) && (ktPid2 ==  -321)))
    mPairType = fgkKaonPlusKaonPlus;
  else if (((ktPid1 ==  -321) && (ktPid2 ==   321)) ||
           ((ktPid1 ==   321) && (ktPid2 ==  -321)))
    mPairType = fgkKaonPlusKaonMinus;
  else if (((ktPid1 ==  2212) && (ktPid2 ==  2212)) ||
           ((ktPid1 == -2212) && (ktPid2 == -2212)))
    mPairType = fgkProtonProton;
  else if (((ktPid1 == -2212) && (ktPid2 ==  2212)) ||
           ((ktPid1 ==  2212) && (ktPid2 == -2212)))
    mPairType = fgkProtonAntiproton;
  else if (((ktPid1 ==   211) && (ktPid2 ==   321)) ||
           ((ktPid1 ==  -211) && (ktPid2 ==  -321)))
    mPairType = fgkPionPlusKaonPlus;
  else if (((ktPid1 ==  -211) && (ktPid2 ==   321)) ||
           ((ktPid1 ==   211) && (ktPid2 ==  -321)))
    mPairType = fgkPionPlusKaonMinus;
  else if (((ktPid1 ==   211) && (ktPid2 ==  2212)) ||
           ((ktPid1 ==  -211) && (ktPid2 == -2212)))
    mPairType = fgkPionPlusProton;
  else if (((ktPid1 ==  -211) && (ktPid2 ==  2212)) ||
           ((ktPid1 ==   211) && (ktPid2 == -2212)))
    mPairType = fgkPionPlusAntiproton;
  else if (((ktPid1 ==   321) && (ktPid2 ==  2212)) ||
           ((ktPid1 ==  -321) && (ktPid2 == -2212)))
    mPairType = fgkKaonPlusProton;
  else if (((ktPid1 ==  -321) && (ktPid2 ==  2212)) ||
           ((ktPid1 ==   321) && (ktPid2 == -2212)))
    mPairType = fgkKaonPlusAntiproton;

  setPid(ktPid1, ktPid2);
}
