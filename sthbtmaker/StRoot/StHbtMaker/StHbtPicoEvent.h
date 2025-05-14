/**
 * \class StHbtPicoEvent
 * \brief Stores collection of particles for processing
 *
 * StHbtPicoEvent stores collections of particles for the further processing
 */

#ifndef StHbtPicoEvent_h
#define StHbtPicoEvent_h

// StHbtMaker headers
#include "StHbtParticleCollection.h"

//_________________
class StHbtPicoEvent {

 public:
  /// Default constructor
  StHbtPicoEvent();
  /// Copy constructor
  StHbtPicoEvent(const StHbtPicoEvent& copy);
  /// Copy constructor
  StHbtPicoEvent& operator=(const StHbtPicoEvent& copy);
  /// Default destructor
  ~StHbtPicoEvent();

  //
  // Getters
  //

  /// First particle collection
  StHbtParticleCollection* firstParticleCollection()   { return mFirstParticleCollection; }
  /// Second particle collection
  StHbtParticleCollection* secondParticleCollection()  { return mSecondParticleCollection; }
  /// Third particle collection
  StHbtParticleCollection* thirdParticleCollection()   { return mThirdParticleCollection; }

 private:

  /// First particle collection
  StHbtParticleCollection* mFirstParticleCollection;
  /// First particle collection
  StHbtParticleCollection* mSecondParticleCollection;
  /// First particle collection
  StHbtParticleCollection* mThirdParticleCollection;
};

#endif // #define StHbtPicoEvent_h
