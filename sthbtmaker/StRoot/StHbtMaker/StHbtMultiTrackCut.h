/**
 * \class StHbtMultiTrackCut
 * \brief Allows to add several cuts to the list
 *
 * The StHbtMultiTrackCut class allows to add many track cuts
 * into the list
 */

#ifndef StHbtMultiTrackCut_h
#define StHbtMultiTrackCut_h

// StHbtMaker headers
// Base
#include "StHbtBaseTrackCut.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "StHbtTrackCutCollection.h"

//_________________
class StHbtMultiTrackCut : public StHbtBaseTrackCut {

 public:
  /// Default constructor
  StHbtMultiTrackCut();
  /// Copy constructor
  StHbtMultiTrackCut(const StHbtMultiTrackCut& copy);
  /// Assignment operator
  StHbtMultiTrackCut& operator=(const StHbtMultiTrackCut& copy);
  /// Destructor
  virtual ~StHbtMultiTrackCut();

  /// User-written method to return string describing cuts
  virtual StHbtString report();
  /// True if passes, false if not
  virtual bool pass(const StHbtTrack* track);

  /// Add track cut
  virtual void addTrackCut(StHbtBaseTrackCut*);
  /// Start event
  virtual void eventBegin(const StHbtEvent*);
  /// Finish event
  virtual void eventEnd(const StHbtEvent*);

  /// Return track type
  StHbtParticleType type() { return hbtTrack; }

  /// Clone cut
  virtual StHbtMultiTrackCut* clone();

 private:
  /// Pointer to a track cut collection
  StHbtTrackCutCollection* mCutCollection;

#ifdef __ROOT__
  ClassDef(StHbtMultiTrackCut, 0)
#endif
};

#endif // #define StHbtMultiTrackCut_h
