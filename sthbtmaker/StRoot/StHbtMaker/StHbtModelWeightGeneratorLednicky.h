//
// Femtoscopic weight generator that called Richard Lednicky's code
//

#ifndef StHbtModelWeightGeneratorLednicky_h
#define StHbtModelWeightGeneratorLednicky_h

// StHbtMaker headers
// Base
#include "StHbtBaseModelWeightGenerator.h"
// Infrastructure
#include "StHbtTypes.h"
#include "TLorentzVector.h"

//_________________
class StHbtModelWeightGeneratorLednicky : public StHbtBaseModelWeightGenerator {

 public:
  /// Default constructor
  StHbtModelWeightGeneratorLednicky();
  /// Copy constructor
  StHbtModelWeightGeneratorLednicky(const StHbtModelWeightGeneratorLednicky &aWeight);
  /// Assignment operator
  StHbtModelWeightGeneratorLednicky& operator=(const StHbtModelWeightGeneratorLednicky& aWeight);
  /// Destructor
  ~StHbtModelWeightGeneratorLednicky();

  /// Generate femtoscopic weight
  virtual double generateWeight(StHbtPair *aPair);
  /// Generate single particle-residual nucleus (p-N) weight
  double generateSingleParticleThirdBodyWeight(const TLorentzVector &freezeOutCoordinate, const TLorentzVector &fourMom, const int &pid);

  /// Set pair type
  virtual void setPairType(const int& aPairType);
  /// Set pair type from the given pair
  virtual void setPairTypeFromPair(StHbtPair *aPair);
  /// Return pair type
  virtual int pairType() const     { return mPairType; }

  /// Return kStar
  virtual double kStar() const      { return StHbtBaseModelWeightGenerator::kStar(); }
  /// Return kStarOut
  virtual double kStarOut() const   { return StHbtBaseModelWeightGenerator::kStarOut(); }
  /// Return kStarSide
  virtual double kStarSide() const  { return StHbtBaseModelWeightGenerator::kStarSide(); }
  /// Return kStarLong
  virtual double kStarLong() const  { return StHbtBaseModelWeightGenerator::kStarLong(); }
  /// Return rStar
  virtual double rStar() const      { return StHbtBaseModelWeightGenerator::rStar(); }
  /// Return rStarOut
  virtual double rStarOut() const   { return StHbtBaseModelWeightGenerator::rStarOut(); }
  /// Return rStarSide
  virtual double rStarSide() const  { return StHbtBaseModelWeightGenerator::rStarSide(); }
  /// Return rStarLong
  virtual double rStarLong() const  { return StHbtBaseModelWeightGenerator::rStarLong(); }

  /// Clone generator
  virtual StHbtBaseModelWeightGenerator* clone() const
  { StHbtBaseModelWeightGenerator* tmp = new StHbtModelWeightGeneratorLednicky(*this); return tmp; }

  // Calculation mode
  // Default is CoulOn, QuantumOn, StrongOn, 3BodyOff, Square, T0ApproxOff

  /// Set default parameters
  void setDefaultCalcPar()
  { mItest = 1; mIqs = 1; mIsi = 1; mI3c = 0; mIch = 1; fsiInit(); mSphereApp = false; mT0App = false; }

  /// Set to calculate Coulomb
  void setCoulOn()               { mItest=1; mIch=1; fsiInit(); }
  /// Set not to calculate Coulomb
  void setCoulOff()              { mItest=1; mIch=0; fsiInit(); }

  /// Set turn Quantum Statistics ON
  void setQuantumOn()            { mItest=1; mIqs=1; fsiInit(); }
  /// Set turn Quantum Statistics OFF
  void setQuantumOff()           { mItest=1; mIqs=0; fsiInit(); }
  /// Set turn Strong Interaction ON
  void setStrongOn()             { mItest=1; mIsi=1; fsiInit(); }
  /// Set turn Strong Interaction OFF
  void setStrongOff()            { mItest=1; mIsi=0; fsiInit(); }
  /// Set three-body interaction ON
  void set3BodyOn()              { mItest=1; mI3c=1; fsiInit(); fsiNucl(); }
  /// Set three-body interaction OFF
  void set3BodyOff()             { mItest=1; mI3c=0; fsiInit(); mWeightDen=1.; fsiNucl(); }
  /// Use Spherical wave approximation
  void setSphere()               { mSphereApp = true; }
  /// Use use Square potential (only for p-p and pi+Pi-) otherwise, use spherical wave approx
  void setSquare()               { mSphereApp = false; }
  /// Only with  Spherical wave Approximation - this is default mode
  void setT0ApproxOff()          { mT0App = false; }
  /// Only with  Spherical wave Approximation - turned ON
  void setT0ApproxOn()           { mT0App = true; }

  /// Test Lambda parameters
  void printLambdas(){;}

  /// Set nuclear charge (for 3-body calculation)
  void setNuclCharge(const double& aNuclCharge)    { mNuclCharge = aNuclCharge; fsiNucl(); }
  /// Set nuclear mass (for 3-body calculation)
  void setNuclMass(const double& aNuclMass)        { mNuclMass = aNuclMass; fsiNucl(); }

  /// K+K- model type, Phi off/on
  void setKpKmModelType(const int& aModelType, const int& aPhi_OffOn)
  { mKpKmModel = aModelType; mPhi_OffOn = aPhi_OffOn; mNS_4 = 4; fsiSetKpKmModelType(); }

  /// Make a report
  virtual StHbtString report();

  /// Return weight for denominator: weight due to particle - (effective) residual nucleus FSI (p-N)
  double getWeif() const { return mWeightDen; }
  /// Return weight due to p-p-N FSI
  double getWei()  const { return mWei; }
  /// Return weight due to weight due to p-p FSI
  double getWein() const { return mWein; }

 protected:

  // FSI weight output
  /// normal weight
  double mWei;
  /// weight with nuclear influence
  double mWein;
  /// weight
  double mWeif;
  /// weight for the denominator
  double mWeightDen;

  // Setting parameters
  /// if set to 1 default parameters will be used
  int mItest;

  //int mNs;
  /// switch coulomb interaction on/off
  int mIch;
  /// switch quantum statistics on/off
  int mIqs;
  /// switch strong interaction on/off
  int mIsi;
  /// switch 3rd body influence on/off
  int mI3c;
  /// mass of the third body
  double mNuclMass;
  /// charge of the third body
  double mNuclCharge;

  /// use spherical approximation
  bool mSphereApp;
  /// use square well approximation
  bool mT0App;

  // Pair identification
  /// internal pair type code
  int mLL;
  /// sign of the 3rd body charge
  short mNuclChargeSign;
  /// are particle in right order ?
  bool mSwap;
  /// number of supported pairs
  int const mLLMax;
  /// name of the system
  char** mLLName;
  /// number of process pairs of each type
  int* mNumProcessPair;
  /// Number of unidentified pairs
  int mNumbNonId;

  // K+K- model type
  /// ij (i=1..4, j=1..4; see StHbtFsiWeightLednicky.F)
  int mKpKmModel;
  /// 0->Phi Off,1->Phi On
  int mPhi_OffOn;
  /// Set NS is equal to 4
  int mNS_4;

  // Interface to the fortran functions
  // initialize K+K- model type
  void fsiSetKpKmModelType();
  void FsiSetKpKmModelType() { fsiSetKpKmModelType(); }
  void fsiInit();
  void FsiInit()             { fsiInit(); }
  void fsiSetLL();
  void FsiSetLL()            { fsiSetLL(); }
  void fsiNucl();
  void FsiNucl()             { fsiNucl(); }
  bool setPid(const int& aPid1, const int& aPid2);
  bool SetPid(const int& aPid1, const int& aPid2) { return setPid(aPid1, aPid2); }

#ifdef __ROOT__
  ClassDef(StHbtModelWeightGeneratorLednicky,2)
#endif
};

#endif // StHbtModelWeightGeneratorLednicky_h
