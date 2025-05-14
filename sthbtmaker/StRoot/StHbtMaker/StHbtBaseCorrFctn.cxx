//
// The pure-virtual base class for correlation functions
//

#include "StHbtBaseCorrFctn.h"

#ifdef __ROOT__
ClassImp(StHbtBaseCorrFctn)
#endif

//_________________
StHbtBaseCorrFctn::StHbtBaseCorrFctn() :
  mBaseAnalysis(nullptr),
  mPairCut(nullptr) {
  /* no-op */
}

//_________________
StHbtBaseCorrFctn::StHbtBaseCorrFctn(const StHbtBaseCorrFctn& c) :
  mBaseAnalysis( c.mBaseAnalysis ),
  mPairCut( c.mPairCut ) {
  /* no-op */
}

//_________________
StHbtBaseCorrFctn& StHbtBaseCorrFctn::operator=(const StHbtBaseCorrFctn& c) {
  if (this != &c) {
    mBaseAnalysis = c.mBaseAnalysis;
    mPairCut = c.mPairCut;
  }
  return *this;
}

//________________
void StHbtBaseCorrFctn::addRealPair(StHbtPair* /* pair */) {
  std::cout << " StHbtBaseCorrFctn::addRealPair - Not implemented" << std::endl;
}

//_________________
void StHbtBaseCorrFctn::addMixedPair(StHbtPair* /* pair */) {
  std::cout << "StHbtBaseCorrFctn::addMixedPair - Not implemented" << std::endl;
}

//_________________
void StHbtBaseCorrFctn::addRealTriplet(const StHbtTriplet* /* triplet */) {
  std::cout << "StHbtBaseCorrFctn::addRealTriplet - Not implemented" << std::endl;
}

//_________________
void StHbtBaseCorrFctn::addMixedTriplet(const StHbtTriplet* /* triplet */) {
  std::cout << "StHbtBaseCorrFctn::addMixedTriplet - Not implemented" << std::endl;
}

//_________________
void StHbtBaseCorrFctn::addFirstParticle(StHbtParticle* /* part */, bool /* isMixing*/) {
  std::cout << "StHbtBaseCorrFctn::addFirstParticle -- Not implemented" << std::endl;
}

//_________________
void StHbtBaseCorrFctn::addSecondParticle(StHbtParticle* /* part */) {
  std::cout << "StHbtBaseCorrFctn::addSecondParticle -- Not implemented" << std::endl;
}
