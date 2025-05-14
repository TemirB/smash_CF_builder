/**
 * \class StHbtBaseKinkCut
 * \brief Base class for kink cuts
 *
 * The the pure virtual base class for the kink cut. All kink cuts
 * must inherit from this one
 */

#ifndef StHbtBaseKinkCut_h
#define StHbtBaseKinkCut_h

// StHbtMaker headers
// Base
#include "StHbtBaseParticleCut.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtKink.h"

//_________________
class StHbtBaseKinkCut : public StHbtBaseParticleCut {

 public:
  /// Default constructor
  StHbtBaseKinkCut() { /* empty */ }
  /// Copy constructor
  StHbtBaseKinkCut(const StHbtBaseKinkCut& copy);
  /// Assignment operator
  StHbtBaseKinkCut& operator=(const StHbtBaseKinkCut& copy);
  /// Default destructor
  virtual ~StHbtBaseKinkCut() { /* empty */ }

  /// Returns true is cut has been passed, and false if not
  virtual bool pass(const StHbtKink* ) = 0;
  /// Return kink type
  virtual StHbtParticleType type() { return hbtKink; }
  /// Clone kink cut
  virtual StHbtBaseKinkCut* clone() { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtBaseKinkCut, 0)
#endif
};

//_________________
inline StHbtBaseKinkCut::StHbtBaseKinkCut(const StHbtBaseKinkCut& c) : StHbtBaseParticleCut(c) { /* empty */ }

//_________________
inline StHbtBaseKinkCut& StHbtBaseKinkCut::operator=(const StHbtBaseKinkCut& c) {
  if( this != &c ) {
    StHbtBaseParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtKinkCut_h
