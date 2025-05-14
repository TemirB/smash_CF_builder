//
// Perform femtoscopic analysis using z- and impact binnings
//

// C++ headers
#include <iostream>

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseTrackCut.h"
#include "StHbtMaker/StHbtBaseV0Cut.h"
#include "StHbtMaker/StHbtBaseKinkCut.h"
#include "StHbtMaker/StHbtBaseXiCut.h"
// Infrastructure
#include "StHbtMakerUser/StHbtModelVertexImpactAnalysis.h"
#include "StHbtMaker/StHbtParticleCollection.h"
#include "StHbtMaker/StHbtPicoEventCollectionVector.h"
#include "StHbtMaker/StHbtPicoEventCollectionVectorHideAway.h"

// ROOT headers
#include "TString.h"

#ifdef __ROOT__
ClassImp(StHbtModelVertexImpactAnalysis)
#endif

//_________________
StHbtModelVertexImpactAnalysis::StHbtModelVertexImpactAnalysis(unsigned int binsVertex,
						 double minVertex,
						 double maxVertex,
						 unsigned int binsImpact,
						 double minImpact,
						 double maxImpact) :
  StHbtAnalysis(),
  mVertexZBins( binsVertex ),
  mOverFlowVertexZ( 0 ),
  mUnderFlowVertexZ( 0 ),
  mImpactBins( binsImpact ),
  mOverFlowImpact( 0 ),
  mUnderFlowImpact( 0 ) {

	// Constructor
  mVertexZ[0] = minVertex;
  mVertexZ[1] = maxVertex;
  mImpact[0] = minImpact;
  mImpact[1] = maxImpact;

  // Print out warnings, will help user to fix these bugs
  if ( minVertex >= maxVertex ) {
    std::cout << "[WARNING] StHbtModelVertexImpactAnalysis - wrong z-vertex positions ("
	      << minVertex << " >= " << maxVertex << "). No events are expected to pass."
	      << std::endl;
  }

  if ( minImpact >= maxImpact ) {
    std::cout << "[WARNING] StHbtModelVertexImpactAnalysis - wrong impact intervals ("
	      << minImpact << " >= " << maxImpact << "). No events are expected to pass."
	      << std::endl;
  }

  if ( !mCorrFctnCollection ) {
    mCorrFctnCollection = new StHbtCorrFctnCollection;
  }

  // If the event collection was already create (it should NOT be) delete
  // before we allocate a new one
  if (mMixingBuffer) {
    delete mMixingBuffer;
    mMixingBuffer = nullptr;
  }

  mPicoEventCollectionVectorHideAway =
    new StHbtPicoEventCollectionVectorHideAway( mVertexZBins, mVertexZ[0], mVertexZ[1],
						mImpactBins, mImpact[0], mImpact[1] );
}

//_________________
StHbtModelVertexImpactAnalysis::StHbtModelVertexImpactAnalysis(const StHbtModelVertexImpactAnalysis& a) :
  StHbtAnalysis( a ),
  mVertexZBins( a.mVertexZBins ),
  mOverFlowVertexZ( 0 ),
  mUnderFlowVertexZ( 0 ),
  mImpactBins( a.mImpactBins ),
  mOverFlowImpact( 0 ),
  mUnderFlowImpact( 0 ) {

	// Copy constructor
  mVertexZ[0] = a.mVertexZ[0];
  mVertexZ[1] = a.mVertexZ[1];
  mImpact[0] = a.mImpact[0];
  mImpact[1] = a.mImpact[1];

  if (mMixingBuffer) {
    delete mMixingBuffer;
    mMixingBuffer = nullptr;
  }

  if( mPicoEventCollectionVectorHideAway ) {
    delete mPicoEventCollectionVectorHideAway;
  }

  mPicoEventCollectionVectorHideAway =
    new StHbtPicoEventCollectionVectorHideAway( mVertexZBins, mVertexZ[0], mVertexZ[1],
						mImpactBins, mImpact[0], mImpact[1] );

  if (mVerbose) {
    std::cout << "StHbtModelVertexImpactAnalysis::StHbtModelVertexImpactAnalysis(const StHbtModelVertexImpactAnalysis& a) - "
	      << "analysis copied" << std::endl;
  } // if (mVerbose)
}

//_________________
StHbtModelVertexImpactAnalysis& StHbtModelVertexImpactAnalysis::operator=(const StHbtModelVertexImpactAnalysis& a) {

	// Assignement operator
  if ( this != &a) {

    // Allow parent class to copy the cuts and correlation functions
    StHbtAnalysis::operator=(a);

    mVertexZBins = a.mVertexZBins;
    mImpactBins = a.mImpactBins;

    mVertexZ[0] = a.mVertexZ[0];
    mVertexZ[1] = a.mVertexZ[1];
    mUnderFlowVertexZ = 0;
    mOverFlowVertexZ = 0;

    mImpact[0] = a.mImpact[0];
    mImpact[1] = a.mImpact[1];
    mUnderFlowImpact = 0;
    mOverFlowImpact = 0;

    if (mMixingBuffer) {
      delete mMixingBuffer;
      mMixingBuffer = nullptr;
    }

    delete mPicoEventCollectionVectorHideAway;

    mPicoEventCollectionVectorHideAway =
      new StHbtPicoEventCollectionVectorHideAway( mVertexZBins, mVertexZ[0], mVertexZ[1],
						  mImpactBins, mImpact[0], mImpact[1] );
  } // if ( this != &a)

  return *this;
}

//_________________
StHbtModelVertexImpactAnalysis::~StHbtModelVertexImpactAnalysis() {
	// Destructor

  // Now delete every PicoEvent in the EventMixingBuffer and
	// then the Buffer itself
  delete mPicoEventCollectionVectorHideAway;
}

//_________________
StHbtString StHbtModelVertexImpactAnalysis::report() {

  // Prepare a report of the execution
  if ( mVerbose ) {
    std::cout << "StHbtModelVertexImpactAnalysis - constructing report..." << std::endl;
  }

  TString report("-----------\nHbt   StHbtModelVertexImpactAnalysis Report:\n");

  report += TString::Format("Events are mixed in %d VertexZ bins in the range %E cm to %E cm.\n",
			    mVertexZBins, mVertexZ[0], mVertexZ[1])
    + TString::Format("Events underflowing: %d\n", mUnderFlowVertexZ)
    + TString::Format("Events overflowing: %d\n", mOverFlowVertexZ)
    + TString::Format("Events are mixed in %d Impact bins in the range %E cm to %E cm.\n",
		      mImpactBins, mImpact[0], mImpact[1])
    + TString::Format("Events underflowing: %d\n", mUnderFlowImpact)
    + TString::Format("Events overflowing: %d\n", mOverFlowImpact)
    + TString::Format("Now adding StHbtAnalysis(base) report\n")
    + StHbtAnalysis::report();

  return StHbtString((const char *)report);
}

//_________________
TList* StHbtModelVertexImpactAnalysis::listSettings() {

  TList *settings = StHbtAnalysis::listSettings();

  settings->AddVector( new TObjString( TString::Format("StHbtModelVertexImpactAnalysis.vertex_z.bins=%d", mVertexZBins) ),
		       new TObjString( TString::Format("StHbtModelVertexImpactAnalysis.vertex_z.min=%f", mVertexZ[0]) ),
		       new TObjString( TString::Format("StHbtModelVertexImpactAnalysis.vertex_z.max=%f", mVertexZ[1]) ),
		       new TObjString( TString::Format("StHbtModelVertexImpactAnalysis.impact.bins=%d", mImpactBins) ),
		       new TObjString( TString::Format("StHbtModelVertexImpactAnalysis.impact.min=%f", mImpact[0]) ),
		       new TObjString( TString::Format("StHbtModelVertexImpactAnalysis.impact.max=%f", mImpact[1]) ),
		       NULL);
  return settings;
}

//_________________________
TList* StHbtModelVertexImpactAnalysis::getOutputList() {

  // Collect the list of output objects to be written
  TList *tOutputList = new TList();

  TList *p1Cut = mFirstParticleCut->getOutputList();
  TListIter nextp1(p1Cut);
  while (TObject *obj = nextp1.Next()) {
    tOutputList->Add(obj);
  }
  delete p1Cut;

  if (mSecondParticleCut != mFirstParticleCut) {
    TList *p2Cut = mSecondParticleCut->getOutputList();

    TIter nextp2(p2Cut);
    while (TObject *obj = nextp2()) {
      tOutputList->Add(obj);
    }
    delete p2Cut;
  } //if (fSecondParticleCut != fFirstParticleCut)

  TList *pairCut = mPairCut->getOutputList();
  TIter nextpair(pairCut);
  while (TObject *obj = nextpair()) {
    tOutputList->Add(obj);
  }
  delete pairCut;

  TList *eventCut = mEventCut->getOutputList();
  TIter nextevent(eventCut);
  while (TObject *obj = nextevent()) {
    tOutputList->Add(obj);
  }
  delete eventCut;

  for (auto &cf : *mCorrFctnCollection) {
    TList *tListCf = cf->getOutputList();

    TIter nextListCf(tListCf);
    while (TObject *obj = nextListCf()) {
      tOutputList->Add(obj);
    }
    delete tListCf;
  }

  return tOutputList;
}

//_________________
void StHbtModelVertexImpactAnalysis::processEvent(const StHbtEvent* hbtEvent) {

  // Perform event processing in bins of z vertex and impact

  // Find the correct mixing buffer
  double vertexZ = hbtEvent->primaryVertex().Z();
  double impact = hbtEvent->impactParameter();
  mMixingBuffer = mPicoEventCollectionVectorHideAway->picoEventCollection( vertexZ, impact );
  if (!mMixingBuffer) {
    if ( vertexZ < mVertexZ[0] ) mUnderFlowVertexZ++;
    if ( vertexZ > mVertexZ[1] ) mOverFlowVertexZ++;
    if ( impact < mImpact[0] ) mUnderFlowImpact++;
    if ( impact > mImpact[1] ) mOverFlowImpact++;
    return;
  }

  // Call ProcessEvent() from StHbtAnalysis-base
  StHbtAnalysis::processEvent(hbtEvent);

  // NULL out the mixing buffer after event processed
  mMixingBuffer = nullptr;
}
