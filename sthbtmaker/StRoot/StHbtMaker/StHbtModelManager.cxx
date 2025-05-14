//
// Manager for model studies
//

// StHbtMaker headers
#include "StHbtModelManager.h"
#include "StHbtModelHiddenInfo.h"

// C++ headers
#include <iostream>

#ifdef __ROOT__
ClassImp(StHbtModelManager);
#endif

//_____________________________________________
StHbtModelManager::StHbtModelManager():
	mFreezeOutGenerator(nullptr),
	mWeightGenerator(nullptr),
	mCreateCopyHiddenInfo(false) {
  /* empty */
}

//_________________
StHbtModelManager::StHbtModelManager(const StHbtModelManager& copy):
  mFreezeOutGenerator(nullptr),
  mWeightGenerator(nullptr),
  mCreateCopyHiddenInfo(copy.mCreateCopyHiddenInfo) {

  // Copy freeze-out coordinate generator if exists
  if (copy.mFreezeOutGenerator) {
    mFreezeOutGenerator = copy.mFreezeOutGenerator->clone();
  }

  // Copy femtoscopic weight generator if exists
  if (copy.mWeightGenerator) {
    mWeightGenerator = copy.mWeightGenerator->clone();
  }
}

//_________________
StHbtModelManager::~StHbtModelManager() {
  if (mFreezeOutGenerator) delete mFreezeOutGenerator;
  if (mWeightGenerator)    delete mWeightGenerator;
}

//_________________
StHbtModelManager& StHbtModelManager::operator=(const StHbtModelManager& copy) {

  // Check if the instance is not a copy of the object.
  // If not then copy it.
  if (this != &copy) {

    // Copy freeze-out coordinate generator if exists
    if (copy.mFreezeOutGenerator) {
      mFreezeOutGenerator = copy.mFreezeOutGenerator->clone();
    }
    else {
      mFreezeOutGenerator = nullptr;
    }

    // Copy femtoscopic weight generator if exists
    if (copy.mWeightGenerator) {
      mWeightGenerator = copy.mWeightGenerator->clone();
    }
    else {
      mWeightGenerator = nullptr;
    }

    // Copy hidden info copy status
    mCreateCopyHiddenInfo = copy.mCreateCopyHiddenInfo;
  }

  return *this;
}

//_____________________________________________
double StHbtModelManager::weight(StHbtPair *aPair) {
  if (!mWeightGenerator) {
    std::cout << "No weight generator set! Cannot calculate weight" << std::endl;
    return 1.0;
    // exit(0);
  }

  // Return femtoscopic weight for a given pair
  if (mCreateCopyHiddenInfo) {

    // Try to guess particle masses and pid from the weight generator
    int tPid1=0, tPid2=0;

    // pi+pi+
    if ( mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::pionPlusPionPlus() ) {
      tPid1 = 211;
      tPid2 = 211;
    }

    // pi+pi-
    if ( mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::pionPlusPionMinus()) {
      tPid1 = 211;
      tPid2 = -211;
    }

    // K+K+
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::kaonPlusKaonPlus()) {
      tPid1 = 321;
      tPid2 = 321;
    }

    // K+K-
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::kaonPlusKaonMinus()) {
      tPid1 = 321;
      tPid2 = -321;
    }

    // pp
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::protonProton()) {
      tPid1 = 2212;
      tPid2 = 2212;
    }

    // p antip
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::protonAntiproton()) {
      tPid1 = 2212;
      tPid2 = -2212;
    }

    // pi+K+
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::pionPlusKaonPlus()) {
      tPid1 = 211;
      tPid2 = 321;
    }

    // pi+K-
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::pionPlusKaonMinus()) {
      tPid1 = 211;
      tPid2 = -321;
    }

    // pi+p
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::pionPlusProton()) {
      tPid1 = 211;
      tPid2 = 2212;
    }

    // pi+antip
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::pionPlusAntiproton()) {
      tPid1 = 211;
      tPid2 = -2212;
    }

    // K+p
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::kaonPlusProton()) {
      tPid1 = 321;
      tPid2 = 2212;
    }

    // K+antip
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::kaonPlusAntiproton()) {
      tPid1 = 321;
      tPid2 = -2212;
    }

    // LambdaLambda
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::lambdaLambda()) {
      tPid1 = 3122;
      tPid2 = 3122;
    }

    // AntiLambdaAntiLambda
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::antilambdaAntilambda()) {
      tPid1 = -3122;
      tPid2 = -3122;
    }

    // LambdaAntiLambda
    if (mWeightGenerator->pairType() == StHbtBaseModelWeightGenerator::lambdaAntilambda()) {
      tPid1 = 3122;
      tPid2 = -3122;
    }

    // If hiddenInfo of the first particle from the pair is not set, then set it
    if ( !( aPair->track1()->hiddenInfo() ) ) {
      StHbtModelHiddenInfo *inf1 = new StHbtModelHiddenInfo();
      inf1->setTrueMomentum( aPair->track1()->track()->p() );
      inf1->setPDGPid( tPid1 );
      aPair->track1()->setHiddenInfo( inf1 );
      delete inf1;
    }

    // If hiddenInfo of the second particle from the pair is not set, then set it
    if ( !( aPair->track2()->hiddenInfo() ) ) {
      StHbtModelHiddenInfo *inf2 = new StHbtModelHiddenInfo();
      inf2->setTrueMomentum( aPair->track2()->track()->p() );
      inf2->setPDGPid( tPid2 );
      aPair->track2()->setHiddenInfo( inf2 );
      delete inf2;
    }
  }

  // If freeze-out coordinate generator exists, then perform generation
  if (mFreezeOutGenerator) {
    mFreezeOutGenerator->generateFreezeOut( aPair );
  }

  return mWeightGenerator->generateWeight( aPair );
}

//_________________
void StHbtModelManager::createCopyHiddenInfo(bool aCopy) {
  mCreateCopyHiddenInfo = aCopy;
}
