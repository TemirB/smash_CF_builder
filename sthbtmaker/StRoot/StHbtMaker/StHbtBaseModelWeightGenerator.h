/**
 * \class StHbtBaseModelWeightGenerator
 * \brief Base class fo the femtoscopic weight generators
 *
 * Abstract base class for femtoscopic weight generator
 */

#ifndef StHbtBaseModelWeightGenerator_h
#define StHbtBaseModelWeightGenerator_h

// ROOT headers
#include "TRandom3.h"

// Forward declaration
class StHbtPair;

//_________________
class StHbtBaseModelWeightGenerator {

 public:
  /// Default constructor
  StHbtBaseModelWeightGenerator();
  /// Copy constructor
  StHbtBaseModelWeightGenerator(const StHbtBaseModelWeightGenerator &aModel);
  /// Assignment operator
  StHbtBaseModelWeightGenerator& operator=(const StHbtBaseModelWeightGenerator &aModel);
  /// Destructor
  virtual ~StHbtBaseModelWeightGenerator();

  /// Generate femtoscopic weight
  virtual double generateWeight(StHbtPair *aPair) = 0;

  /// Set pair type
  virtual void setPairType(const int& aPairType)  { mPairType = aPairType; }
  /// Set pair type from pair
  virtual void setPairTypeFromPair(StHbtPair *aPair) { mPairType = pairTypeFromPair( aPair ); }
  /// Return pair type
  virtual int pairType() const            { return mPairType; }
  /// Return pair type from a pair
  virtual int pairTypeFromPair(StHbtPair *aPair);

  /// Return KStar
  virtual double kStar() const        { return mKStar; }
  /// Return KStarOut
  virtual double kStarOut() const     { return mKStarOut; }
  /// Return KStarSide
  virtual double kStarSide() const    { return mKStarSide; }
  /// Return kStarLong
  virtual double kStarLong() const    { return mKStarLong; }
  /// Return RStar
  virtual double rStar() const        { return mRStar; }
  /// Return RStarOut
  virtual double rStarOut() const     { return mRStarOut; }
  /// Return RStarSide
  virtual double rStarSide() const    { return mRStarSide; }
  /// Return RStarLong
  virtual double rStarLong() const    { return mRStarLong; }

  /// Clone model weight generator
  virtual StHbtBaseModelWeightGenerator* clone() const { return nullptr; }

  /// Identical pion pair type
  static int pionPlusPionPlus()       { return fgkPionPlusPionPlus; }
  /// Identical pion pair type
  static int PionPlusPionPlus()       { return pionPlusPionPlus(); }
  /// Non-identcial pion pair type
  static int pionPlusPionMinus()      { return fgkPionPlusPionMinus; }
  /// Non-identcial pion pair type
  static int PionPlusPionMinus()      { return pionPlusPionMinus(); }
  /// Identical kaon pair type
  static int kaonPlusKaonPlus()       { return fgkKaonPlusKaonPlus; }
  /// Identical kaon pair type
  static int KaonPlusKaonPlus()       { return kaonPlusKaonPlus(); }
  /// Non-identical kaon pair type
  static int kaonPlusKaonMinus()      { return fgkKaonPlusKaonMinus; }
  /// Non-identical kaon pair type
  static int KaonPlusKaonMinus()      { return kaonPlusKaonMinus(); }
  /// Identical proton pair type
  static int protonProton()           { return fgkProtonProton; }
  /// Identical proton pair type
  static int ProtonProton()           { return protonProton(); }
  /// Proton-Antiproton pair type
  static int protonAntiproton()       { return fgkProtonAntiproton; }
  /// Proton-Antiproton pair type
  static int ProtonAntiproton()       { return protonAntiproton(); }
  /// pi+K+ pair type
  static int pionPlusKaonPlus()       { return fgkPionPlusKaonPlus; }
  /// pi+K+ pair type
  static int PionPlusKaonPlus()       { return pionPlusKaonPlus(); }
  /// pi+K- pair type
  static int pionPlusKaonMinus()      { return fgkPionPlusKaonMinus; }
  /// pi+K- pair type
  static int PionPlusKaonMinus()      { return pionPlusKaonMinus(); }
  /// pi+p pair type
  static int pionPlusProton()         { return fgkPionPlusProton; }
  /// pi+p pair type
  static int PionPlusProton()         { return pionPlusProton(); }
  /// pi+antiproton pair type
  static int pionPlusAntiproton()     { return fgkPionPlusAntiproton; }
  /// pi+antiproton pair type
  static int PionPlusAntiproton()     { return pionPlusAntiproton(); }
  /// K+p pair type
  static int kaonPlusProton()         { return fgkKaonPlusProton; }
  /// K+p pair type
  static int KaonPlusProton()         { return kaonPlusProton(); }
  /// K+antiproton pair type
  static int kaonPlusAntiproton()     { return fgkKaonPlusAntiproton; }
  /// K+antiproton pair type
  static int KaonPlusAntiproton()     { return kaonPlusAntiproton(); }
  /// None pair type
  static int pairTypeNone()           { return fgkPairTypeNone; }
  /// None pair type
  static int PairTypeNone()           { return pairTypeNone(); }
  /// LambdaLambda pair type
  static int lambdaLambda()           { return fgkLambdaLambda; }
  /// LambdaLambda pair type
  static int LambdaLambda()           { return lambdaLambda(); }
  /// AntilambdaAntilambda pair type
  static int antilambdaAntilambda()   { return fgkAntilambdaAntilambda; }
  /// AntilambdaAntilambda pair type
  static int AntilambdaAntilambda()   { return antilambdaAntilambda(); }
  /// LambdaAntilambda pair type
  static int lambdaAntilambda()       { return fgkLambdaAntilambda; }
  /// LambdaAntilambda pair type
  static int LambdaAntilambda()       { return lambdaAntilambda(); }

 protected:

  /// no pair type set - read from model
  static const int fgkPairTypeNone;
  /// identical pion pair
  static const int fgkPionPlusPionPlus;
  /// non-identical pion pair
  static const int fgkPionPlusPionMinus;
  /// identical kaon pair
  static const int fgkKaonPlusKaonPlus;
  /// non-identical kaon pair
  static const int fgkKaonPlusKaonMinus;
  /// identical proton pair
  static const int fgkProtonProton;
  /// non-identical proton pair
  static const int fgkProtonAntiproton;
  /// same-charge pion kaon pair
  static const int fgkPionPlusKaonPlus;
  /// opposite-charge pion kaon pair
  static const int fgkPionPlusKaonMinus;
  /// same-charge pion proton pair
  static const int fgkPionPlusProton;
  /// opposite-chare pion proton pair
  static const int fgkPionPlusAntiproton;
  /// same-charge kaon proton pair
  static const int fgkKaonPlusProton;
  /// opposite-charge kaon proton pair
  static const int fgkKaonPlusAntiproton;
  /// same-type lambdas
  static const int fgkLambdaLambda;
  /// same-type antilambdas
  static const int fgkAntilambdaAntilambda;
  /// non-same-type lambdas
  static const int fgkLambdaAntilambda;

  /// Type of the pair for which the calculation is done
  int mPairType;

  /// Relative momentum out component in PRF
  float mKStarOut;
  /// Relative momentum side component in PRF
  float mKStarSide;
  /// Relative momentum long component in PRF
  float mKStarLong;
  /// Relative momentum magnitude
  float mKStar;

  /// Relative separation out component in PRF
  float mRStarOut;
  /// Relative separation side component in PRF
  float mRStarSide;
  /// Relative separation long component in PRF
  float mRStarLong;
  /// Relative separation magnitude
  float mRStar;

 private:

#ifdef __ROOT__
  ClassDef(StHbtBaseModelWeightGenerator, 1);
#endif
};

#endif // StHbtBaseModelWeightGenerator_h
