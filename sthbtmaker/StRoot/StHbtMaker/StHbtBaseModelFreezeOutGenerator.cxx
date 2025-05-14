//
// A base class for freeze-out coordinate generator
//

// StHbtMaker headers
#include "StHbtBaseModelFreezeOutGenerator.h"

#ifdef __ROOT__
ClassImp(StHbtBaseModelFreezeOutGenerator);
#endif

//_________________
StHbtBaseModelFreezeOutGenerator::StHbtBaseModelFreezeOutGenerator(): mRandom(0) {
  /* emtpy */
}

//_________________
StHbtBaseModelFreezeOutGenerator::StHbtBaseModelFreezeOutGenerator(const StHbtBaseModelFreezeOutGenerator &/* aModel */):
  mRandom(0) {
  /* empty */
}

//_________________
StHbtBaseModelFreezeOutGenerator& StHbtBaseModelFreezeOutGenerator::operator=(const StHbtBaseModelFreezeOutGenerator& aGen) {
  // Assignment operator
  if (this != &aGen) {
    if ( aGen.mRandom ) {
      mRandom = new TRandom3( *aGen.mRandom );
    }
    else {
      mRandom=0;
    }
  }

  return *this;
}

//_________________
StHbtBaseModelFreezeOutGenerator::~StHbtBaseModelFreezeOutGenerator() {
  if (mRandom) delete mRandom;
}

//_________________
StHbtBaseModelFreezeOutGenerator* StHbtBaseModelFreezeOutGenerator::clone() const {
  return nullptr;
}
