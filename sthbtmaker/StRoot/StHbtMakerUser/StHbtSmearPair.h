/**
 * \class StHbtSmearPair
 * \brief Class that returns a StHbtPair with smeared momentum
 *
 * Given a StHbtPair, this class provides a corresponding
 * StHbtPair whose constituent StHbtParticles' momenta have been
 * smeared according to a parameterization of the STAR momentum
 * resolution.
 */

#ifndef StHbtSmearPair_h
#define StHbtSmearPair_h

// StHbtMaker headers
#include "StHbtMaker/StHbtPair.h"

// ROOT headers
#include "TLorentzVector.h"
#include "TRandom3.h"

//_________________
class StHbtSmearPair {

 public:
  /// Default constructor
  StHbtSmearPair();
  /// Constructor that takes unsmeared pair
  StHbtSmearPair(const StHbtPair* unSmearedPair);
  /// Destructor
  virtual ~StHbtSmearPair()             { /* empty */ }

  /// Essentially same as c'tor
  void setUnsmearedPair(const StHbtPair* unSmearedPair);

  /// Access to the smeared pair
  StHbtPair& smearedPair()              { return mSmearedPair; }

  //========= Resolution parameters ==========

  /// pT resolution parameterized by d(pT) = Frac*pT
  void setFractionalPtRes(double val)   { mFracPtRes = val; }
  /// phi resolution parameterized d(phi)= by a+b*P^alpha
  void setPhiRes_a(double val)          { mPhi_a = val; }
  /// phi resolution parameterized d(phi)= by a+b*P^alpha
  void setPhiRes_b(double val)          { mPhi_b = val; }
  /// phi resolution parameterized d(phi)= by a+b*P^alpha
  void setPhiRes_alpha(double val)      { mPhi_alpha = val; }
  /// phi resolution parameterized by d(theta) = a+b*P^alpha
  void setThetaRes_a(double val)        { mTheta_a = val; }
  /// phi resolution parameterized by d(theta) = a+b*P^alpha
  void setThetaRes_b(double val)        { mTheta_b = val; }
  /// phi resolution parameterized by d(theta) = a+b*P^alpha
  void setThetaRes_alpha(double val)    { mTheta_alpha = val; }

  /// Return smeared four-momentum of the pair
  TLorentzVector smearedMomentum(TLorentzVector input);

 private:

  /// Pair with smeared parameters
  StHbtPair mSmearedPair;
  /// The first particle
  StHbtParticle mParticle1;
  /// The second particle
  StHbtParticle mParticle2;

  /// Pair resolution parameters
  double mFracPtRes;
  /// Parameter phi_a
  double mPhi_a;
  /// Parameter phi_b
  double mPhi_b;
  /// Parameter phi_alpha
  double mPhi_alpha;
  /// Parameter theta_a
  double mTheta_a;
  /// Parameter theta_b
  double mTheta_b;
  /// Parameter theta_alpha
  double mTheta_alpha;

  /// Random value
  TRandom3* mHbtRandom;

  /// Setup
  void setup();

#ifdef __ROOT__
  ClassDef(StHbtSmearPair, 0)
#endif
};

#endif // #define StHbtSmearPair_h
