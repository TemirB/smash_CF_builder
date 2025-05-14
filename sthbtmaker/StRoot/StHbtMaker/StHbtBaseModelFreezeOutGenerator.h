/**
 * \class StHbtModelFreezeOutGenerator
 * \brief A base class for freeze-out coordinate generator
 *
 * An abstract base class for freeze-out coordinates generator
 */

#ifndef StHbtBaseModelFreezeOutGenerator_h
#define StHbtBaseModelFreezeOutGenerator_h

// ROOT headers
#include "TRandom3.h"

// StHbtMaker headers
#include "StHbtPair.h"

//_________________
class StHbtBaseModelFreezeOutGenerator {

 public:
  /// Default constructor
  StHbtBaseModelFreezeOutGenerator();
  /// Copy constructor
  StHbtBaseModelFreezeOutGenerator(const StHbtBaseModelFreezeOutGenerator &aModel);
  /// Assignment operator
  StHbtBaseModelFreezeOutGenerator& operator=(const StHbtBaseModelFreezeOutGenerator& aGen);
  /// Destructor
  virtual ~StHbtBaseModelFreezeOutGenerator();

  /// Generate freeze-out parameters (x,y,z,t)
  virtual void generateFreezeOut(StHbtPair *aPair) = 0;
  /// Clone freeze-out generator
  virtual StHbtBaseModelFreezeOutGenerator* clone() const;

 protected:
  // Randomizer
  TRandom3 *mRandom; //!<!

 private:

#ifdef __ROOT__
  ClassDef(StHbtBaseModelFreezeOutGenerator, 1);
#endif
};

#endif // #define StHbtBaseModelFreezeOutGenerator_h
