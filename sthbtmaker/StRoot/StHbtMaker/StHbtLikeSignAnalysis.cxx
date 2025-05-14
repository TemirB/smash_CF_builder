//
// The class is a base class for like-sign analysis with z-binning
//

// StHbtMaker headers
// Base
#include "StHbtBaseTrackCut.h"
#include "StHbtBaseV0Cut.h"
// Infrastructure
#include "StHbtLikeSignAnalysis.h"
#include "StHbtParticleCollection.h"
#include "StHbtPicoEventCollectionVector.h"
#include "StHbtPicoEventCollectionVectorHideAway.h"

#ifdef __ROOT__
ClassImp(StHbtLikeSignAnalysis)
#endif

/// This little function used to apply ParticleCuts (TrackCuts or V0Cuts)
/// and fill ParticleCollections of picoEvent it is called
/// from StHbtAnalysis::ProcessEvent()
extern void fillHbtParticleCollection(StHbtBaseParticleCut* partCut,
				      StHbtEvent* hbtEvent,
				      StHbtParticleCollection* partCollection, char doReshuffle);

//_________________
StHbtLikeSignAnalysis::StHbtLikeSignAnalysis(const unsigned int& bins, const double& min,
					     const double& max) : StHbtAnalysis() {
  // Constructor
  mVertexBins = bins;
  mVertexZ[0] = min;
  mVertexZ[1] = max;
  mUnderFlow = 0;
  mOverFlow = 0;
  if (mMixingBuffer) delete mMixingBuffer;
  mPicoEventCollectionVectorHideAway =
    new StHbtPicoEventCollectionVectorHideAway(mVertexBins, mVertexZ[0], mVertexZ[1]);
}

//_________________
StHbtLikeSignAnalysis::StHbtLikeSignAnalysis(const StHbtLikeSignAnalysis& a) : StHbtAnalysis(a) {
  // Copy constructor
  mVertexBins = a.mVertexBins;
  mVertexZ[0] = a.mVertexZ[0];
  mVertexZ[1] = a.mVertexZ[1];
  mUnderFlow = 0;
  mOverFlow = 0;
  if (mMixingBuffer) delete mMixingBuffer;
  mPicoEventCollectionVectorHideAway =
    new StHbtPicoEventCollectionVectorHideAway(mVertexBins, mVertexZ[0], mVertexZ[1]);
}

//_________________
StHbtLikeSignAnalysis& StHbtLikeSignAnalysis::operator=(const StHbtLikeSignAnalysis& a) {
  // Assignement operator
  if( this != &a ) {
    mVertexBins = a.mVertexBins;
    mVertexZ[0] = a.mVertexZ[0];
    mVertexZ[1] = a.mVertexZ[1];
    mUnderFlow = 0;
    mOverFlow = 0;
    if(mMixingBuffer) delete mMixingBuffer;
    if(mPicoEventCollectionVectorHideAway) delete mPicoEventCollectionVectorHideAway;
    mPicoEventCollectionVectorHideAway =
      new StHbtPicoEventCollectionVectorHideAway( mVertexBins, mVertexZ[0], mVertexZ[1] );
  }

  return *this;
}

//_________________
StHbtLikeSignAnalysis::~StHbtLikeSignAnalysis() {
  delete mPicoEventCollectionVectorHideAway;
  mPicoEventCollectionVectorHideAway = nullptr;
}

//_________________
StHbtString StHbtLikeSignAnalysis::report() {
  char Ctemp[200];
  std::cout << "StHbtLikeSignAnalysis - constructing Report..." << std::endl;
  StHbtString temp = "-----------\nHbt Analysis Report:\n";
  sprintf(Ctemp,"Events are mixed in %d bins in the range %E cm to %E cm.\n",mVertexBins,mVertexZ[0],mVertexZ[1]);
  temp += Ctemp;
  sprintf(Ctemp,"Events underflowing: %d\n",mUnderFlow);
  temp += Ctemp;
  sprintf(Ctemp,"Events overflowing: %d\n",mOverFlow);
  temp += Ctemp;
  sprintf(Ctemp,"Now adding StHbtAnalysis(base) Report\n");
  temp += Ctemp;
  temp += "Adding StHbtAnalysis(base) Report now:\n";
  temp += StHbtAnalysis::report();
  temp += "-------------\n";
  StHbtString returnThis=temp;
  return returnThis;
}

//_________________________
void StHbtLikeSignAnalysis::processEvent(const StHbtEvent* hbtEvent) {

  // Perform all the analysis tasks for a single event
  // get right mixing buffer
  double vertexZ = hbtEvent->primaryVertex().Z();
  mMixingBuffer = mPicoEventCollectionVectorHideAway->picoEventCollection(vertexZ);
  if (!mMixingBuffer) {
    if ( vertexZ < mVertexZ[0] ) mUnderFlow++;
    if ( vertexZ > mVertexZ[1] ) mOverFlow++;
    return;
  }

  // Startup for EbyE
  eventBegin( hbtEvent );

  // Event cut and event cut monitor
  bool tmpPassEvent = mEventCut->pass(hbtEvent);
  mEventCut->fillCutMonitor(hbtEvent, tmpPassEvent);
  if (tmpPassEvent) {
    mNeventsProcessed++;
    std::cout << "StHbtLikeSignAnalysis::processEvent() - " << hbtEvent->trackCollection()->size();
    std::cout << " #track=" << hbtEvent->trackCollection()->size();
    // OK, analysis likes the event-- build a pico event from it,
    // using tracks the analysis likes...
    // This is what we will make pairs from and put in Mixing Buffer
    StHbtPicoEvent* picoEvent = new StHbtPicoEvent;

    fillHbtParticleCollection( mFirstParticleCut, (StHbtEvent*)hbtEvent, picoEvent->firstParticleCollection(), mReshuffle );
    if ( !(analyzeIdenticalParticles()) ) {
      fillHbtParticleCollection( mSecondParticleCut, (StHbtEvent*)hbtEvent, picoEvent->secondParticleCollection(), mReshuffle );
    }

    std::cout << "   #particles in First, Second Collections: "
	      << picoEvent->firstParticleCollection()->size() << " "
	      << picoEvent->secondParticleCollection()->size() << std::endl;

    if ( picoEvent->secondParticleCollection()->size() *
	 picoEvent->firstParticleCollection()->size()==0 ) {
      delete picoEvent;
      std::cout << "StHbtLikeSignAnalysis - picoEvent deleted due to empty collection " << std::endl;
      return;
    }
    // OK, pico event is built
    // make real pairs...

    // Fabrice points out that we do not need to keep creating/deleting pairs all the time
    // We only ever need ONE pair, and we can just keep changing internal pointers
    // this should help speed things up
    StHbtPair* ThePair = new StHbtPair;

    StHbtParticleIterator PartIter1;
    StHbtParticleIterator PartIter2;
    StHbtCorrFctnIterator CorrFctnIter;
    // Always
    StHbtParticleIterator StartOuterLoop = picoEvent->firstParticleCollection()->begin();
    // Will be one less if identical
    StHbtParticleIterator EndOuterLoop   = picoEvent->firstParticleCollection()->end();
    StHbtParticleIterator StartInnerLoop;
    StHbtParticleIterator EndInnerLoop;
    // Only use First collection
    if ( analyzeIdenticalParticles() ) {
      // Iuter loop goes to next-to-last particle in First collection
      EndOuterLoop--;
      // Inner loop goes to last particle in First collection
      EndInnerLoop = picoEvent->firstParticleCollection()->end() ;
    }
    else {
      // Non-identical - loop over First and Second collections
      // Inner loop starts at first particle in Second collection
      StartInnerLoop = picoEvent->secondParticleCollection()->begin();
      // Inner loop goes to last particle in Second collection
      EndInnerLoop   = picoEvent->secondParticleCollection()->end() ;
    }
    // real pairs
    for ( PartIter1=StartOuterLoop; PartIter1!=EndOuterLoop; PartIter1++ ) {
      if ( analyzeIdenticalParticles() ) {
	StartInnerLoop = PartIter1;
	StartInnerLoop++;
      }
      ThePair->setTrack1(*PartIter1);
      for (PartIter2 = StartInnerLoop; PartIter2!=EndInnerLoop; PartIter2++) {
				ThePair->setTrack2(*PartIter2);
				// The following lines have to be uncommented if you want pairCutMonitors
				// they are not in for speed reasons
				// bool tmpPassPair = mPairCut->Pass(ThePair);
				// mPairCut->FillCutMonitor(ThePair, tmpPassPair);
				// if ( tmpPassPair ) {
				if ( mPairCut->pass(ThePair) ) {
				  for ( CorrFctnIter=mCorrFctnCollection->begin();
								CorrFctnIter!=mCorrFctnCollection->end(); CorrFctnIter++) {
				    StHbtBaseLikeSignCorrFctn* CorrFctn = dynamic_cast<StHbtBaseLikeSignCorrFctn*>(*CorrFctnIter);
				    if (CorrFctn) {
				      CorrFctn->addRealPair(ThePair);
				    }
				  }
				} //if ( mPairCut->pass(ThePair) )
      } //for (PartIter2 = StartInnerLoop; PartIter2!=EndInnerLoop; PartIter2++)
    }  //for ( PartIter1=StartOuterLoop; PartIter1!=EndOuterLoop; PartIter1++ )

#ifdef STHBTDEBUG
    std::cout << "StHbtLikeSignAnalysis::ProcessEvent() - reals done" << std::endl;
#endif

    StHbtParticleIterator nextIter;
    StHbtParticleIterator prevIter;

    // Like-sign first partilce collection pairs
    prevIter = EndOuterLoop;
    prevIter--;
    for ( PartIter1=StartOuterLoop; PartIter1!=prevIter; PartIter1++) {
      ThePair->setTrack1(*PartIter1);
      nextIter = PartIter1;
      nextIter++;
      for ( PartIter2 = nextIter; PartIter2!=EndOuterLoop; PartIter2++) {
				ThePair->setTrack2(*PartIter2);
				// The following lines have to be uncommented if you want pairCutMonitors
				// they are not in for speed reasons
				// bool tmpPassPair = mPairCut->Pass(ThePair);
				// mPairCut->FillCutMonitor(ThePair, tmpPassPair);
				// if ( tmpPassPair ) {
				if ( mPairCut->pass(ThePair) ) {
				  for ( CorrFctnIter=mCorrFctnCollection->begin();
								CorrFctnIter!=mCorrFctnCollection->end(); CorrFctnIter++) {
				    StHbtBaseLikeSignCorrFctn* CorrFctn = dynamic_cast<StHbtBaseLikeSignCorrFctn*>(*CorrFctnIter);
				    if (CorrFctn) {
				      CorrFctn->addLikeSignPositivePair(ThePair);
				    }
				  }
				} //if ( mPairCut->pass(ThePair) )
      } //for ( PartIter2 = nextIter; PartIter2!=EndOuterLoop; PartIter2++)
    } //for ( PartIter1=StartOuterLoop; PartIter1!=prevIter; PartIter1++)

#ifdef STHBTDEBUG
    std::cout << "StHbtLikeSignAnalysis::processEvent() - like sign first collection done" << std::endl;
#endif

    // Like-sign second partilce collection pairs
    prevIter = EndInnerLoop;
    prevIter--;
    for ( PartIter1=StartInnerLoop; PartIter1!=prevIter; PartIter1++) {
      ThePair->setTrack1(*PartIter1);
      nextIter = PartIter1;
      nextIter++;
      for (PartIter2 = nextIter; PartIter2!=EndInnerLoop; PartIter2++) {
				ThePair->setTrack2(*PartIter2);
				// The following lines have to be uncommented if you want pairCutMonitors
				// they are not in for speed reasons
				// bool tmpPassPair = mPairCut->Pass(ThePair);
				// mPairCut->FillCutMonitor(ThePair, tmpPassPair);
				// if ( tmpPassPair ) {
				if ( mPairCut->pass(ThePair) ) {
				  for ( CorrFctnIter=mCorrFctnCollection->begin();
					CorrFctnIter!=mCorrFctnCollection->end(); CorrFctnIter++) {
				    StHbtBaseLikeSignCorrFctn* CorrFctn = dynamic_cast<StHbtBaseLikeSignCorrFctn*>(*CorrFctnIter);
				    if (CorrFctn) {
				      CorrFctn->addLikeSignNegativePair(ThePair);
				    }
				  }
				} //if ( mPairCut->pass(ThePair) )
      } //for (PartIter2 = nextIter; PartIter2!=EndInnerLoop; PartIter2++)

      //for ( PartIter1=StartInnerLoop; PartIter1!=prevIter; PartIter1++)
#ifdef STHBTDEBUG
      std::cout << "StHbtLikeSignAnalysis::processEvent() - like sign second collection done" << std::endl;
#endif

      if ( mixingBufferFull() ) {
#ifdef STHBTDEBUG
	std::cout << "Mixing Buffer is full - lets rock and roll" << std::endl;
#endif
      }
      else {
	std::cout << "Mixing Buffer not full -gotta wait " << mixingBuffer()->size() << std::endl;
      }

      if ( mixingBufferFull() ) {
	StartOuterLoop = picoEvent->firstParticleCollection()->begin();
	EndOuterLoop   = picoEvent->firstParticleCollection()->end();
	StHbtPicoEvent* storedEvent;
	StHbtPicoEventIterator picoEventIter;
	for ( picoEventIter=mixingBuffer()->begin();
	      picoEventIter!=mixingBuffer()->end(); picoEventIter++) {
	  storedEvent = *picoEventIter;
	  if ( analyzeIdenticalParticles() ) {
	    StartInnerLoop = storedEvent->firstParticleCollection()->begin();
	    EndInnerLoop = storedEvent->firstParticleCollection()->end();
	  }
	  else {
	    StartInnerLoop = storedEvent->secondParticleCollection()->begin();
	    EndInnerLoop = storedEvent->secondParticleCollection()->end();
	  }
	  for ( PartIter1=StartOuterLoop; PartIter1!=EndOuterLoop; PartIter1++) {
	    ThePair->setTrack1(*PartIter1);
	    for (PartIter2=StartInnerLoop; PartIter2!=EndInnerLoop; PartIter2++) {
	      ThePair->setTrack2(*PartIter2);
	      // testing...	      cout << "ThePair defined... going to pair cut... ";
	      if ( mPairCut->pass(ThePair) ) {
					// testing...		cout << " ThePair passed PairCut... ";
					for ( CorrFctnIter=mCorrFctnCollection->begin();
					      CorrFctnIter!=mCorrFctnCollection->end(); CorrFctnIter++) {
					  StHbtBaseLikeSignCorrFctn* CorrFctn = dynamic_cast<StHbtBaseLikeSignCorrFctn*>(*CorrFctnIter);
					  if (CorrFctn) {
					    CorrFctn->addMixedPair(ThePair);
					    //cout << " ThePair has been added to MixedPair method " << endl;
					  } //if (CorrFctn)
					} // for ( CorrFctnIter=mCorrFctnCollection->begin();
	      } //if ( mPairCut->pass(ThePair) )
	    } //for (PartIter2=StartInnerLoop; PartIter2!=EndInnerLoop; PartIter2++)
	  } //for ( PartIter1=StartOuterLoop; PartIter1!=EndOuterLoop; PartIter1++)
	} //for ( picoEventIter=mixingBuffer()->begin(); picoEventIter!=mixingBuffer()->end(); picoEventIter++)

	// Now get rid of oldest stored pico-event in buffer.
	// This means (1) delete the event from memory, (2) "pop" the pointer to it from the MixingBuffer
	delete mixingBuffer()->back();
	mixingBuffer()->pop_back();
      } //if ( mixingBufferFull() )

      delete ThePair;
      // Store the current pico-event in buffer
      mixingBuffer()->push_front(picoEvent);
    } //if (tmpPassEvent)

    // Cleanup for EbyE
    eventEnd(hbtEvent);
    // cout << "StHbtLikeSignAnalysis::ProcessEvent() - return to caller ... " << endl;
  }
}
