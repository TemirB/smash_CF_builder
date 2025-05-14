/**
 * \class StHbtModelGausLCMSFreezeOutGenerator
 * \brief Generates freeze-out coordinates using Gaussian profile
 *
 * Freeze-out coordinates generator, generating a 3D gaussian ellipsoid in LCMS
 */

#ifndef StHbtModelGausLCMSFreezeOutGenerator_h
#define StHbtModelGausLCMSFreezeOutGenerator_h

// StHbtMaker headers
#include "StHbtBaseModelFreezeOutGenerator.h"

// ROOT headers
#include "TRandom3.h"

//_________________
class StHbtModelGausLCMSFreezeOutGenerator : public StHbtBaseModelFreezeOutGenerator {

 public:
  /// Default constructor
  StHbtModelGausLCMSFreezeOutGenerator();
  /// Copy construcotr
  StHbtModelGausLCMSFreezeOutGenerator(const StHbtModelGausLCMSFreezeOutGenerator &aModel);
  /// Assignment operator
  StHbtModelGausLCMSFreezeOutGenerator& operator=(const StHbtModelGausLCMSFreezeOutGenerator &aModel);
  /// Default destructor
  virtual ~StHbtModelGausLCMSFreezeOutGenerator();

  /// Generate freeze-out coordinate (x,y,z,t)
  virtual void generateFreezeOut(StHbtPair *aPair);
  /// Generate freeze-out coordinate (x,y,z,t)
  virtual void GenerateFreezeOut(StHbtPair *aPair) { generateFreezeOut(aPair); }

  /// Set outward component
  void setSizeOut(const double& aSizeOut)   { mSizeOut = aSizeOut; }
  /// Set sideward component
  void setSizeSide(const double& aSizeSide) { mSizeSide = aSizeSide; }
  /// Set longitudinal component
  void setSizeLong(const double& aSizeLong) { mSizeLong = aSizeLong; }

  /// Return outward component
  double sizeOut() const   { return mSizeOut; }
  /// Return sideward component
  double sizeSide() const  { return mSizeSide; }
  /// Return longitudinal component
  double sizeLong() const  { return mSizeLong; }

  /// Clone generator
  virtual StHbtBaseModelFreezeOutGenerator* clone() const { return generator(); }

 protected:
  /// Size of the source in the out direction
  double mSizeOut;
  /// Size of the source in the side direction
  double mSizeSide;
  /// Size of the source in the long direction
  double mSizeLong;

 private:
  StHbtBaseModelFreezeOutGenerator* generator() const
  { StHbtBaseModelFreezeOutGenerator* tModel = new StHbtModelGausLCMSFreezeOutGenerator(*this); return tModel; }

#ifdef __ROOT__
  ClassDef(StHbtModelGausLCMSFreezeOutGenerator, 1);
#endif
};

#endif // StHbtModelGausLCMSFreezeOutGenerator_h
