/**
 * \class StHbtBaseCutMonitor
 * \brief The base class for cut monitors
 *
 * A cut monitor saves attributes of the entities that have passed or failed
 * the given cut. This class is the base class which is present to
 * provide a common interface for storing data.
 *
 * Cut monitors are to be used in conjunction with cut monitor handlers
 * (StHbtCutMonitorHandler) - of which all standard cuts (e.g.
 * StHbtEventCut) inherit from. Your cut monitor objects get added to the
 * monitorhandlers via their addCutMonitor methods, and the Fill commands get
 * called by the handler upon their fillCutMonitor method, with the particular
 * entity type.
 *
 * The default behavior of this base class is to do nothing with the
 * incoming data, as no data members are provided. It is up to the user to use
 * (or write) a subclass with relevant histograms.
 *
 * To implement a custom cut monitor, subclass this class and overload the
 * Fill method(s) corresponding to the entity type(s) you wish to monitor.
 * All other 'fill' methods should be implemented to avoid 'member hiding'
 * compiler warnings.
 *
 * All methods of this class are empty except report which returns an empty
 * string and getOutputList which returns a pointer to an empty list.
 */

#ifndef StHbtBaseCutMonitor_h
#define StHbtBaseCutMonitor_h

// Forward declarations
class StHbtEvent;
class StHbtTrack;
class StHbtV0;
class StHbtXi;
class StHbtKink;
class StHbtPair;

// C++ headers
#include <iostream>

// StHbtMaker headers
#include "StHbtString.h"
#include "StHbtParticleCollection.h"

// ROOT headers
#include "TList.h"

//_________________
class StHbtBaseCutMonitor {

 public:
  /// Default constructor
  StHbtBaseCutMonitor()            { /* no-op */ };
  /// Default destructor
  virtual ~StHbtBaseCutMonitor()   { /* no-op */ };

  /// Report details
  virtual StHbtString report();

  /// Start event processing
  virtual void eventBegin(const StHbtEvent*) { /* no-op */ }
  /// Finish event processing
  virtual void eventEnd(const StHbtEvent*) { /* no-op */ }

  /// Returns pointer to empty list
  virtual TList* getOutputList();

  /// Fill method for event
  virtual void fill(const StHbtEvent*);
  /// Fill method for track
  virtual void fill(const StHbtTrack*);
  /// Fill method for v0
  virtual void fill(const StHbtV0*);
  /// Fill method for xi
  virtual void fill(const StHbtXi*);
  /// Fill method for kink
  virtual void fill(const StHbtKink*);
  /// Fill method for pair
  virtual void fill(const StHbtPair*);
  /// Fill method for particle collection
  virtual void fill(const StHbtParticleCollection*);
  /// Fill method for event and particle collection
  virtual void fill(const StHbtEvent*,const StHbtParticleCollection*);
  /// Fill method for two particle collections
  virtual void fill(const StHbtParticleCollection*, const StHbtParticleCollection*);

  /// Finish
  virtual void finish();
  /// Initialize cut monitor
  virtual void init();

#ifdef __ROOT__
  ClassDef(StHbtBaseCutMonitor, 0)
#endif
};

//_________________
inline TList* StHbtBaseCutMonitor::getOutputList() {
  TList *mOutputList = new TList();
  return mOutputList;
}

//_________________
inline StHbtString StHbtBaseCutMonitor::report() {
  StHbtString defReport("*** no user defined fill(const StHbtEvent*), take from base class");
  return defReport;
}

#endif //#define StHbtBaseCutMonitor_h
