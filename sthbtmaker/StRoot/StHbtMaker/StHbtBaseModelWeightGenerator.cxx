//
// Base class fo the femtoscopic weight generators
//

// StHbtMaker headers
// Base
#include "StHbtBaseModelWeightGenerator.h"
// Infrastructure
#include "StHbtPair.h"
#include "StHbtModelHiddenInfo.h"

#ifdef __ROOT__
ClassImp(StHbtBaseModelWeightGenerator);
#endif

// Constants
const int StHbtBaseModelWeightGenerator::fgkPairTypeNone = 0;
const int StHbtBaseModelWeightGenerator::fgkPionPlusPionPlus = 1;
const int StHbtBaseModelWeightGenerator::fgkPionPlusPionMinus = 2;
const int StHbtBaseModelWeightGenerator::fgkKaonPlusKaonPlus = 3;
const int StHbtBaseModelWeightGenerator::fgkKaonPlusKaonMinus = 4;
const int StHbtBaseModelWeightGenerator::fgkProtonProton = 5;
const int StHbtBaseModelWeightGenerator::fgkProtonAntiproton = 6;
const int StHbtBaseModelWeightGenerator::fgkPionPlusKaonPlus = 7;
const int StHbtBaseModelWeightGenerator::fgkPionPlusKaonMinus = 8;
const int StHbtBaseModelWeightGenerator::fgkPionPlusProton = 9;
const int StHbtBaseModelWeightGenerator::fgkPionPlusAntiproton = 10;
const int StHbtBaseModelWeightGenerator::fgkKaonPlusProton = 11;
const int StHbtBaseModelWeightGenerator::fgkKaonPlusAntiproton = 12;
const int StHbtBaseModelWeightGenerator::fgkLambdaLambda = 13;
const int StHbtBaseModelWeightGenerator::fgkAntilambdaAntilambda = 14;
const int StHbtBaseModelWeightGenerator::fgkLambdaAntilambda = 15;

//_________________
StHbtBaseModelWeightGenerator::StHbtBaseModelWeightGenerator() :
  mPairType(0),
  mKStarOut(0), mKStarSide(0), mKStarLong(0), mKStar(0),
  mRStarOut(0), mRStarSide(0), mRStarLong(0), mRStar(0) {
  /* empty */
}

//_________________
StHbtBaseModelWeightGenerator::StHbtBaseModelWeightGenerator(const StHbtBaseModelWeightGenerator &aModel) :
  mPairType(0),
  mKStarOut(0), mKStarSide(0), mKStarLong(0), mKStar(0),
  mRStarOut(0), mRStarSide(0), mRStarLong(0), mRStar(0) {
  // Copy constructor
  mPairType = aModel.mPairType;
}

//_________________
StHbtBaseModelWeightGenerator& StHbtBaseModelWeightGenerator::operator=(const StHbtBaseModelWeightGenerator &aModel) {
  // Assignment operator
  if (this != &aModel) {
    mPairType = aModel.mPairType;
  }
  return *this;
}

//_____________________________________________
StHbtBaseModelWeightGenerator::~StHbtBaseModelWeightGenerator() {
  /* empty */
}

//_________________
int StHbtBaseModelWeightGenerator::pairTypeFromPair(StHbtPair *aPair) {
  // Get the type of pair from PID of particles in the pair
  StHbtModelHiddenInfo *inf1 = (StHbtModelHiddenInfo*)aPair->track1()->hiddenInfo();
  StHbtModelHiddenInfo *inf2 = (StHbtModelHiddenInfo*)aPair->track2()->hiddenInfo();

  int tPairType = fgkPairTypeNone;

  const int ktPid1 = inf1->pdgPid();
  const int ktPid2 = inf2->pdgPid();

  if ( ( ( ktPid1 ==  211 ) && ( ktPid2 == 211 ) ) ||
       ( ( ktPid1 == -211 ) && (ktPid2 == -211 ) ) ) {
    tPairType = fgkPionPlusPionPlus;
  }
  else if ( ( ( ktPid1 == -211 ) && ( ktPid2 ==  211 ) ) ||
	    ( ( ktPid1 ==  211 ) && ( ktPid2 == -211 ) ) ) {
    tPairType = fgkPionPlusPionMinus;
  }
  else if ( ( ( ktPid1 ==  321 ) && ( ktPid2 ==  321 ) ) ||
	    ( ( ktPid1 == -321 ) && ( ktPid2 == -321 ) ) ) {
    tPairType = fgkKaonPlusKaonPlus;
  }
  else if ( ( ( ktPid1 == -321 ) && ( ktPid2 ==  321 ) ) ||
	    ( ( ktPid1 ==  321 ) && ( ktPid2 == -321 ) ) ) {
    tPairType = fgkKaonPlusKaonMinus;
  }
  else if ( ( ( ktPid1 ==  2212 ) && ( ktPid2 ==  2212 ) ) ||
	    ( ( ktPid1 == -2212 ) && ( ktPid2 == -2212 ) ) ) {
    tPairType = fgkProtonProton;
  }
  else if ( ( ( ktPid1 == -2212 ) && ( ktPid2 ==  2212 ) ) ||
	    ( ( ktPid1 ==  2212 ) && ( ktPid2 == -2212 ) ) ) {
    tPairType = fgkProtonAntiproton;
  }
  else if ( ( ( ktPid1 ==  211 ) && ( ktPid2 ==  321 ) ) ||
            ( ( ktPid1 == -211 ) && ( ktPid2 == -321 ) ) ) {
    tPairType = fgkPionPlusKaonPlus;
  }
  else if ( ( ( ktPid1 == -211 ) && ( ktPid2 ==  321 ) ) ||
	    ( ( ktPid1 ==  211 ) && ( ktPid2 == -321 ) ) ) {
    tPairType = fgkPionPlusKaonMinus;
  }
  else if ( ( ( ktPid1 ==  211 ) && ( ktPid2 ==  2212 ) ) ||
	    ( ( ktPid1 == -211 ) && ( ktPid2 == -2212 ) ) ) {
    tPairType = fgkPionPlusProton;
  }
  else if ( ( ( ktPid1 == -211 ) && ( ktPid2 ==  2212 ) ) ||
	    ( ( ktPid1 ==  211 ) && ( ktPid2 == -2212 ) ) ) {
    tPairType = fgkPionPlusAntiproton;
  }
  else if ( ( ( ktPid1 ==  321 ) && ( ktPid2 ==  2212 ) ) ||
	    ( ( ktPid1 == -321 ) && ( ktPid2 == -2212 ) ) ) {
    tPairType = fgkKaonPlusProton;
  }
  else if ( ( ( ktPid1 == -321 ) && ( ktPid2 ==  2212 ) ) ||
	    ( ( ktPid1 ==  321 ) && ( ktPid2 == -2212 ) ) ) {
    tPairType = fgkKaonPlusAntiproton;
  }
  else if ( ( ( ktPid1 == 3122 ) && ( ktPid2 == 3122 ) ) ) {
    tPairType = fgkLambdaLambda;
  }
  else if ( ( ( ktPid1 == -3122 ) && ( ktPid2 == -3122 ) ) ) {
    tPairType = fgkAntilambdaAntilambda;
  }
  else if ( ( ( ktPid1 ==  3122 ) && ( ktPid2 == -3122 ) ) ||
	    ( ( ktPid1 == -3122 ) && ( ktPid2 ==  3122 ) ) ) {
    tPairType = fgkLambdaAntilambda;
  }

  return tPairType;
}
