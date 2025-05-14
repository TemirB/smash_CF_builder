/**
 * \class StHbtTriplet
 * \brief The class allows to perform three-particle analysis
 *
 * The StHbtTriplet class allows to perform three-particle
 * analysis and calculate quantities like: qInv, mInv, etc...
 */

#ifndef StHbtTriplet_h
#define StHbtTriplet_h

// C++ headers
#include <utility>

// StHbtMaker headers
#include "StHbtParticle.h"
#include "StHbtTypes.h"

// ROOT headers
#include "TLorentzVector.h"

//_________________
class StHbtTriplet {

 public:
  /// Default constructor
  StHbtTriplet();
  /// Constructor with three particles
  StHbtTriplet(StHbtParticle*, StHbtParticle*, StHbtParticle*);
  /// Copy constructor
  StHbtTriplet(const StHbtTriplet&);
  // Default destructor
  virtual ~StHbtTriplet();

  /// Retrieve the first track
  StHbtParticle* track1() const { return mTrack1; }
  /// Retrieve the second track
  StHbtParticle* track2() const { return mTrack2; }
  /// Retrieve the third track
  StHbtParticle* track3() const { return mTrack3; }
  /// Set first track
  void setTrack1(const StHbtParticle* trkPtr)   { mTrack1 = (StHbtParticle*)trkPtr; }
  /// Set second track
  void setTrack2(const StHbtParticle* trkPtr)   { mTrack2=(StHbtParticle*)trkPtr; }
  /// Set third track
  void setTrack3(const StHbtParticle* trkPtr)   { mTrack3=(StHbtParticle*)trkPtr; }

  /// Four-momentum of three particles
  TLorentzVector fourMomentum() const;
  /// Relative momentum of three particles
  double qInv() const;
  /// Relative momentum the first and second particles
  double qInv12() const;
  /// Relative momentum the third and second particles
  double qInv23() const;
  /// Relative momentum the first and third particles
  double qInv31() const;
  /// Half of transverse momentum of three particles
  double kT()   const;
  /// Invariant mass of three particles
  double mInv() const;

  /// Track-splitting quantity of three particles
  double quality() const;
  /// Track-splitting quantity of three particles
  double splittinLevel() const { return quality(); }

  // the following two methods calculate the "nominal" separation of the tracks
  // at the inner field cage (EntranceSeparation) and when they exit the TPC,
  // which may be at the outer field cage, or at the endcaps.
  // "nominal" means that the tracks are assumed to start at (0,0,0).  Making this
  // assumption is important for the Event Mixing-- it is not a mistake

  /// Nominal TPC exit separation
  double nominalTpcExitSeparation() const;
  /// Nominal TPC entrance separation
  double nominalTpcEntranceSeparation() const;
  /// Nominal TPC average separation
  double nominalTpcAverageSeparation() const;

 private:

  /// The first particle from triplet
  StHbtParticle* mTrack1;
  /// The second particle from triplet
  StHbtParticle* mTrack2;
  /// The third particle from triplet
  StHbtParticle* mTrack3;
};

#endif // StHbtTriplet_h
