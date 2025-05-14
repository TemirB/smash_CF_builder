//
// Base class for cut monitors
//

// StHbtMaker headers
#include "StHbtBaseCutMonitor.h"

#ifdef __ROOT__
ClassImp(StHbtBaseCutMonitor)
#endif

//_________________
void StHbtBaseCutMonitor::fill(const StHbtEvent* /* event */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtTrack* /* track */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtV0* /* v0 */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtXi* /* xi */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtKink* /* kink*/) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtPair* /* pair */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtParticleCollection* /* collection */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtParticleCollection* /* coll1 */,
			   											 const StHbtParticleCollection* /* coll2 */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::fill(const StHbtEvent* /* event */,
													 		 const StHbtParticleCollection* /* coll */) {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::finish() {
  /* empty */
}

//_________________
void StHbtBaseCutMonitor::init() {
  /* empty */
}
