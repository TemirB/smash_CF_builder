/**
 * \class StHbtCutMonitorHandler
 * \brief A handler for cut monitors
 *
 * You add cut monitors to the collection which are stored in two separate
 * collections - one which stores characteristics of the entities (tracks,
 * particles, pairs, events) that pass the respective cuts and the other for
 * the ones that fail the cut.
 */

#ifndef StHbtCutMonitorHandler_h
#define StHbtCutMonitorHandler_h

// StHbtMaker headers
// Base
#include "StHbtBaseCutMonitor.h"

// Infrastructure
#include "StHbtTypes.h"
#include "StHbtEvent.h"
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "StHbtKink.h"
#include "StHbtXi.h"
#include "StHbtPair.h"
#include "StHbtParticleCollection.h"
#include "StHbtCutMonitorCollection.h"

// ROOT headers
#include "Rtypes.h"
#include "TList.h"

//_________________
class StHbtCutMonitorHandler {

 public:
  /// Default constructor
  StHbtCutMonitorHandler();
  /// Copy constructor
  StHbtCutMonitorHandler(const StHbtCutMonitorHandler& copy);
  /// Assignment operator
  StHbtCutMonitorHandler& operator=(const StHbtCutMonitorHandler& copy);
  /// Destructor
  virtual ~StHbtCutMonitorHandler();

  /// Return monitor collection that passed cuts
  StHbtCutMonitorCollection* passMonitorColl()    { return mPassColl; }
  /// Return monitor collection that failed to pass cuts
  StHbtCutMonitorCollection* failMonitorColl()    { return mFailColl; }
  /// Return n-th monitor that passed cut
  StHbtBaseCutMonitor* passMonitor(int n);
  /// Return n-th monitor that failed to pass cut
  StHbtBaseCutMonitor* failMonitor(int n);

  /// Add cut monitor
  void addCutMonitor(StHbtBaseCutMonitor* cutMoni1, StHbtBaseCutMonitor* cutMoni2);
  /// Add cut monitor
  void addCutMonitor(StHbtBaseCutMonitor* cutMoni);
  /// Add cut monitor that will be written in case the cut will be passed
  void addCutMonitorPass(StHbtBaseCutMonitor* cutMoni);
  /// Add cut monitor that will be written in case the cut will not be passed
  void addCutMonitorFail(StHbtBaseCutMonitor* cutMoni);

  /// Fill cut monitor for the event
  void fillCutMonitor(const StHbtEvent* event, bool pass);
  /// Fill cut monitor for the track
  void fillCutMonitor(const StHbtTrack* track, bool pass);
  /// Fill cut monitor for the v0
  void fillCutMonitor(const StHbtV0* v0, bool pass);
  /// Fill cut monitor for the kink
  void fillCutMonitor(const StHbtKink* kink, bool pass);
  /// Fill cut monitor for the xi
  void fillCutMonitor(const StHbtXi* xi, bool pass);
  /// Fill cut monitor for the pair
  void fillCutMonitor(const StHbtPair* pair, bool pass);
  /// Fill cut monitor for the pair
  void fillCutMonitor(const StHbtParticleCollection* partColl);
  /// Fill cut monitor for the event and collection
  void fillCutMonitor(const StHbtEvent* event, const StHbtParticleCollection* partColl);
  /// Fill cut monitor for two collections
  void fillCutMonitor(const StHbtParticleCollection* partColl1, const StHbtParticleCollection* partColl2);

  /// Call finish
  void finish();

  /// Obtain list of objects to be written as an output
  virtual TList *getOutputList();

  /// Event begin
  virtual void eventBegin(const StHbtEvent* event);
  /// Event end
  virtual void eventEnd(const StHbtEvent* event);

 private:

  /// Are the collections empty?
  bool mCollectionsEmpty;
  /// Collection of cut monitors for passed entities
  StHbtCutMonitorCollection* mPassColl;
  /// Collection of cut monitors for failed entities
  StHbtCutMonitorCollection* mFailColl;

#ifdef __ROOT__
  ClassDef(StHbtCutMonitorHandler, 0)
#endif
};

#endif // #define StHbtCutMonitorHandler_h
