//
// Femtoscopic analysis which mixes events with vertex z-binning
//

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseTrackCut.h"
#include "StHbtMaker/StHbtBaseV0Cut.h"
#include "StHbtMaker/StHbtBaseKinkCut.h"
// Infrastructure
#include "StHbtMakerUser/StHbtVertexAnalysis.h"
#include "StHbtMaker/StHbtParticleCollection.h"
#include "StHbtMaker/StHbtPicoEventCollectionVector.h"
#include "StHbtMaker/StHbtPicoEventCollectionVectorHideAway.h"

#ifdef __ROOT__
ClassImp(StHbtVertexAnalysis)
#endif

//_________________
StHbtVertexAnalysis::StHbtVertexAnalysis(unsigned int bins, float zMin, float zMax) :
  StHbtAnalysis(),
  mVertexBins( bins ),
  mOverFlow( 0 ),
  mUnderFlow( 0 ) {

  mVertexZ[0] = zMin;
  mVertexZ[1] = zMax;

  if (mMixingBuffer) {
    delete mMixingBuffer;
    mMixingBuffer = nullptr;
  }
  mPicoEventCollectionVectorHideAway =
    new StHbtPicoEventCollectionVectorHideAway( mVertexBins, mVertexZ[0], mVertexZ[1] );
}

//_________________
StHbtVertexAnalysis::StHbtVertexAnalysis(const StHbtVertexAnalysis& a) :
  StHbtAnalysis( a ),
  mVertexBins( a.mVertexBins ),
  mOverFlow( 0 ),
  mUnderFlow( 0 ) {

  mVertexZ[0] = a.mVertexZ[0];
  mVertexZ[1] = a.mVertexZ[1];

  if (mMixingBuffer) {
    delete mMixingBuffer;
    mMixingBuffer = nullptr;
  } // if (mMixingBuffer)

  mPicoEventCollectionVectorHideAway =
    new StHbtPicoEventCollectionVectorHideAway( mVertexBins, mVertexZ[0], mVertexZ[1] );

  if (mVerbose) {
    std::cout << " StHbtVertexAnalysis::StHbtVertexAnalysis(const StHbtVertexAnalysis& a) - analysis copied "
	      << std::endl;
  } // if (mVerbose)
}

//_________________
StHbtVertexAnalysis& StHbtVertexAnalysis::operator=(const StHbtVertexAnalysis& a) {

  if ( this != &a ) {
    StHbtAnalysis::operator=( a );

    mVertexBins = a.mVertexBins;
    mVertexZ[0] = a.mVertexZ[0];
    mVertexZ[1] = a.mVertexZ[1];
    mUnderFlow = 0;
    mOverFlow = 0;

    if (mMixingBuffer) {
      delete mMixingBuffer;
      mMixingBuffer = nullptr;
    }
    mPicoEventCollectionVectorHideAway =
      new StHbtPicoEventCollectionVectorHideAway( mVertexBins, mVertexZ[0], mVertexZ[1] );
  } // if ( this != &a )

  return *this;
}

//_________________
StHbtVertexAnalysis::~StHbtVertexAnalysis(){
  // Now delete every PicoEvent in the EventMixingBuffer and then the Buffer itself
  delete mPicoEventCollectionVectorHideAway;
}

//_________________
StHbtString StHbtVertexAnalysis::report() {

  // Prepare report fromt the execution
  if (mVerbose) {
    std::cout << "StHbtVertexAnalysis - constructing report..." << std::endl;
  }

  TString report("-----------\nStHbtVertexAnalysis report:\n");
  report += TString::Format( "Events are mixed in %d bins in the range %E cm to %E cm.\n",
			     mVertexBins, mVertexZ[0], mVertexZ[1] )
    + TString::Format("Events underflowing: %d\n", mUnderFlow)
    + TString::Format("Events overflowing: %d\n",mOverFlow)
    + TString::Format("Now adding StHbtAnalysis(base) report\n");

  report += StHbtAnalysis::report();

  return StHbtString( (const char *)report );
}

//_________________
void StHbtVertexAnalysis::processEvent(const StHbtEvent* hbtEvent) {

  if ( mVerbose ) {
    std::cout << " StHbtVertexAnalysis::processEvent(const StHbtEvent* hbtEvent) " << std::endl;
  }

  // Get right mixing buffer
  double vertexZ = hbtEvent->primaryVertex().Z();
  mMixingBuffer = mPicoEventCollectionVectorHideAway->picoEventCollection( vertexZ );

  if (!mMixingBuffer) {
    if ( vertexZ < mVertexZ[0] ) mUnderFlow++;
    if ( vertexZ > mVertexZ[1] ) mOverFlow++;
    return;
  }

  // Call processEvent() from StHbtAnalysis-base
  StHbtAnalysis::processEvent( hbtEvent );

  // NULL out the mixing buffer after event processed
  mMixingBuffer = nullptr;
}

//_________________
TList* StHbtVertexAnalysis::listSettings() {

  TList *settings = StHbtAnalysis::listSettings();
  settings->AddVector( new TObjString( TString::Format("StHbtVertexAnalysis.vertex_z.bins=%d", mVertexBins) ),
		       new TObjString( TString::Format("StHbtVertexAnalysis.vertex_z.min=%f", mVertexZ[0]) ),
		       new TObjString( TString::Format("StHbtVertexAnalysis.vertex_z.max=%f", mVertexZ[1]) ),
		       NULL );
  return settings;
}

//_________________________
TList* StHbtVertexAnalysis::getOutputList() {

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
