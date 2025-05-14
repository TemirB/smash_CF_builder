/**
 * \class StHbtBaseXiCut
 * \brief Base class for Xi cuts
 *
 * The pure virtual base class for the Xi cut. All Xi cuts must
 * inherit from this one.
 */

#ifndef StHbtBaseXiCut_h
#define StHbtBaseXiCut_h

// StHbtMaker headers
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtXi.h"
// Base
#include "StHbtBaseParticleCut.h"

//_________________
class StHbtBaseXiCut : public StHbtBaseParticleCut {

 public:
  /// Default constructor
  StHbtBaseXiCut() { /* empty */}
  /// Copy constructor
  StHbtBaseXiCut(const StHbtBaseXiCut& copy);
  /// Assignment operator
  StHbtBaseXiCut& operator=(const StHbtBaseXiCut& copy);
  /// Default destructor
  virtual ~StHbtBaseXiCut() { /* empty */ }

  /// Returns true if cut has been passed and false if not
  virtual bool pass(const StHbtXi* ) = 0;

  /// Return Xi type
  virtual StHbtParticleType type() { return hbtXi; }

  /// Clone Xi cut
  virtual StHbtBaseXiCut* clone() { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtBaseXiCut, 0)
#endif
};

//_________________
inline StHbtBaseXiCut::StHbtBaseXiCut(const StHbtBaseXiCut& c) : StHbtBaseParticleCut(c) { /* no-op */ }

//_________________
inline StHbtBaseXiCut& StHbtBaseXiCut::operator=(const StHbtBaseXiCut& c) {
  if (this != &c ) {
    StHbtBaseParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtXiCut_h
