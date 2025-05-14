/**
 * \class StHbtBaseV0Cut
 * \brief Base class for V0 cuts
 *
 * The pure virtual base class for the V0 cut. All V0 cuts
 * must inherit from this one.
 */

#ifndef StHbtBaseV0Cut_h
#define StHbtBaseV0Cut_h

// StHbtMaker headers
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtV0.h"
// Base
#include "StHbtBaseParticleCut.h"

//_________________
class StHbtBaseV0Cut : public StHbtBaseParticleCut {

 public:
  /// Default constructor
  StHbtBaseV0Cut() { /* empty */ }
  /// Copy constructor
  StHbtBaseV0Cut(const StHbtBaseV0Cut& copy);
  /// Assignment operator
  StHbtBaseV0Cut& operator=(const StHbtBaseV0Cut& c);
  /// Default destructor
  virtual ~StHbtBaseV0Cut() {/* empty */}

  /// Returns true if cut has been passed and false if not
  virtual bool pass(const StHbtV0* ) = 0;

  /// Return V0 type
  virtual StHbtParticleType type() { return hbtV0; }
  /// Clone V0 cut
  virtual StHbtBaseV0Cut* clone() { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtBaseV0Cut, 0)
#endif
};

//_________________
inline StHbtBaseV0Cut::StHbtBaseV0Cut(const StHbtBaseV0Cut& c) : StHbtBaseParticleCut(c) { /* empty */ }

//_________________
inline StHbtBaseV0Cut& StHbtBaseV0Cut::operator=(const StHbtBaseV0Cut& c) {
  if( this != &c ) {
    StHbtBaseParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtV0Cut_h
