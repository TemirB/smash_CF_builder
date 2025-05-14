/**
 * \class StHbtBaseTrackCut
 * \brief Base class for track cuts
 *
 * The pure virtual base class for track cuts. All track cuts must
 * inherit from this one.
 */

#ifndef StHbtBaseTrackCut_h
#define StHbtBaseTrackCut_h

// StHbtMaker headers
// Base
#include "StHbtBaseParticleCut.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtTrack.h"

//_________________
class StHbtBaseTrackCut : public StHbtBaseParticleCut {

 public:
  /// Default constructor
  StHbtBaseTrackCut();
  /// Copy constructor
  StHbtBaseTrackCut(const StHbtBaseTrackCut& copy);
  /// Assignment operator
  StHbtBaseTrackCut& operator=(const StHbtBaseTrackCut& copy);
  /// Default destructor
  virtual ~StHbtBaseTrackCut()             {/* no-op */}

  /// Returns true if passed the track cut and false if not
  virtual bool pass(const StHbtTrack* track) = 0;
  /// Return track type
  virtual StHbtParticleType type() { return hbtTrack; }
  /// Clone track cut
  virtual StHbtBaseTrackCut* clone() { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtBaseTrackCut, 0)
#endif
};

//_________________
inline StHbtBaseTrackCut::StHbtBaseTrackCut() : StHbtBaseParticleCut() { /* empty */ }

//_________________
inline StHbtBaseTrackCut::StHbtBaseTrackCut(const StHbtBaseTrackCut& c) : StHbtBaseParticleCut(c) { /* empty */ }

//_________________
inline StHbtBaseTrackCut& StHbtBaseTrackCut::operator=(const StHbtBaseTrackCut& c) {
  if (this != &c ) {
    StHbtBaseParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtTrackCut_h
