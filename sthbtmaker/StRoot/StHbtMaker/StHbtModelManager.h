/**
 * \class StHbtModelManager
 * \brief Manager for model studies
 *
 * The StHbtModelManager class is a main helper class for femtoscopy
 * calculations. It manages weight generation, freeze-out coordinates
 * generation
 */

#ifndef StHbtModelManager_h
#define StHbtModelManager_h

// StHbtMaker headers
// Base
#include "StHbtBaseModelWeightGenerator.h"
#include "StHbtBaseModelFreezeOutGenerator.h"
// Infrastructure
#include "StHbtEnumeration.h"

//_________________
class StHbtModelManager {

 public:
  /// Default constructor
  StHbtModelManager();
  /// Copy constructor
  StHbtModelManager(const StHbtModelManager& manager);
  /// Assignment operator
  StHbtModelManager& operator=(const StHbtModelManager& manager);
  /// Destructor
  virtual ~StHbtModelManager();

  /// Set pointer to the freeze-out coordinate generator
  void setFreezeOutGenerator(StHbtBaseModelFreezeOutGenerator *foGen) { mFreezeOutGenerator = foGen; }
  /// Set pointer to the freeze-out coordinate generator
  void SetFreezeOutGenerator(StHbtBaseModelFreezeOutGenerator *foGen) { setFreezeOutGenerator(foGen); }
  /// Set pointer to the femtoscopic weight generator
  void setWeightGenerator(StHbtBaseModelWeightGenerator *weightGen)   { mWeightGenerator = weightGen; }
  /// Set pointer to the femtoscopic weight generator
  void SetWeightGenerator(StHbtBaseModelWeightGenerator *weightGen)   { setWeightGenerator(weightGen); }
  /// Set status of the copy hidden info
  void createCopyHiddenInfo(bool aCopy=true);
  /// Set status of the copy hidden info
  void CreateCopyHiddenInfo(bool aCopy) { createCopyHiddenInfo(aCopy); }

  /// Return pointer to the freeze-out coordinate generator
  StHbtBaseModelFreezeOutGenerator* freezeOutGenerator() { return mFreezeOutGenerator; }
  /// Return pointer to the freeze-out coordinate generator
  StHbtBaseModelFreezeOutGenerator* FreezeOutGenerator() { return freezeOutGenerator(); }
  /// Return pointer to the pair-weight generator
  StHbtBaseModelWeightGenerator* weightGenerator()       { return mWeightGenerator; }
  /// Return pointer to the pair-weight generator
  StHbtBaseModelWeightGenerator* WeightGenerator()       { return weightGenerator(); }
  /// Return femtoscopic weight
  virtual double weight(StHbtPair *aPair);
  /// Return femtoscopic weight
  virtual double Weight(StHbtPair *aPair)  { return weight(aPair); }

 protected:

  /// Pointer to freeze-out coordinate generator
  StHbtBaseModelFreezeOutGenerator *mFreezeOutGenerator;
  /// Femtoscopic weight generator
  StHbtBaseModelWeightGenerator    *mWeightGenerator;
  /// Switch to turn on hidden-info generation
  bool                             mCreateCopyHiddenInfo;

 private:

#ifdef __ROOT__
  ClassDef(StHbtModelManager, 1);
#endif

};

#endif // #define StHbtModelManager_h
