//
// StHbtManager: main class managing femtoscopic analysis
//

// C/C++ headers
#include <cstdio>

// StHbtMaker headers
#include "StHbtManager.h"

#ifdef __ROOT__
ClassImp(StHbtManager)
#endif

//_________________
StHbtManager::StHbtManager() :
  mAnalysisCollection(nullptr),
  mEventReader(nullptr),
  mEventWriterCollection(nullptr) {

  // Constructor
  mAnalysisCollection = new StHbtAnalysisCollection;
  mEventWriterCollection = new StHbtEventWriterCollection;
}

//_________________
StHbtManager::StHbtManager(const StHbtManager &copy) :
  mAnalysisCollection( new StHbtAnalysisCollection ),
  mEventReader( copy.mEventReader ),
  mEventWriterCollection( new StHbtEventWriterCollection ) {

  // Copy constructor
  StHbtAnalysisIterator AnalysisIter;
  for(AnalysisIter = copy.mAnalysisCollection->begin();
      AnalysisIter != copy.mAnalysisCollection->end();
      AnalysisIter++ ) {
    mAnalysisCollection->push_back( *AnalysisIter );
  }

  StHbtEventWriterIterator EventWriterIter;
  for(EventWriterIter = copy.mEventWriterCollection->begin();
      EventWriterIter != copy.mEventWriterCollection->end();
      EventWriterIter++) {
    mEventWriterCollection->push_back( *EventWriterIter );
  }
}

//_________________
StHbtManager& StHbtManager::operator=(const StHbtManager& man) {

  // Assignment operator
  if ( this != &man ) {

    mEventReader = man.mEventReader;

    // Clean collections
    StHbtAnalysisIterator analysisIter;
    if (mAnalysisCollection) {
      for( analysisIter = mAnalysisCollection->begin();
	         analysisIter != mAnalysisCollection->end(); analysisIter++) {
	      delete *analysisIter;
	      *analysisIter = nullptr;
      }
    } //if (mAnalysisCollection)
    delete mAnalysisCollection;

    StHbtEventWriterIterator writerIter;
    if(mEventWriterCollection) {
      for( writerIter = mEventWriterCollection->begin();
	         writerIter != mEventWriterCollection->end(); writerIter++ ) {
	      delete *writerIter;
	      *writerIter = nullptr;
      }
    } //if(mEventWriterCollection)
    delete mEventWriterCollection;

    // Copy collections
    mAnalysisCollection = new StHbtAnalysisCollection;
    for( analysisIter = man.mAnalysisCollection->begin();
	       analysisIter != man.mAnalysisCollection->end(); analysisIter++ ) {
      mAnalysisCollection->push_back( *analysisIter );
    }

    mEventWriterCollection = new StHbtEventWriterCollection;
    for( writerIter = man.mEventWriterCollection->begin();
	       writerIter != man.mEventWriterCollection->end(); writerIter++ ) {
      mEventWriterCollection->push_back( *writerIter );
    }

  } //if ( this != &man )

  return *this;
}

//_________________
StHbtManager::~StHbtManager() {

  // Destructor
  delete mEventReader;

  // Delete each Analysis in the Collection
  // and then the Collection itself
  StHbtAnalysisIterator AnalysisIter;
  for (AnalysisIter = mAnalysisCollection->begin();
       AnalysisIter != mAnalysisCollection->end();
       AnalysisIter++) {
    delete *AnalysisIter;
    *AnalysisIter = nullptr;
  }
  delete mAnalysisCollection;

  // Delete each EventWriter in the Collection,
  // and then the Collection itself
  StHbtEventWriterIterator EventWriterIter;
  for (EventWriterIter = mEventWriterCollection->begin();
       EventWriterIter != mEventWriterCollection->end();
       EventWriterIter++) {
    delete *EventWriterIter;
    *EventWriterIter = nullptr;
  }
  delete mEventWriterCollection;
}

//_________________
int StHbtManager::init() {

  StHbtString readerMessage;
  readerMessage += "*** *** *** *** *** *** *** *** *** *** *** *** \n";
  // EventReader
  if (mEventReader) {
    if ( mEventReader->init("r",readerMessage) ) {
      std::cout << " StHbtManager::init() - Reader initialization failed " << std::endl;
      return 1;
    }
    readerMessage += mEventReader->report();
  }

  // EventWriters
  StHbtEventWriterIterator EventWriterIter;
  for ( EventWriterIter = mEventWriterCollection->begin();
      	EventWriterIter != mEventWriterCollection->end();
      	EventWriterIter++ ) {
    // The message (StHbtString) passed into Init will be at the file header.
    // for that reason take the readerReport, add my own report and pass as message
    StHbtString writerMessage = readerMessage;
    writerMessage += "*** *** *** *** *** *** *** *** *** *** *** *** \n";
    writerMessage += (*EventWriterIter)->report();
    if (*EventWriterIter) {
      if ( (*EventWriterIter)->init("w",writerMessage) ) {
      	// yes, the message from the reader is passed into the writer
      	std::cout << " StHbtManager::Init() - Writer initialization failed " << std::endl;
      	return 1;
      } //if ( (*EventWriterIter)->Init("w",writerMessage) )
    } //if (*EventWriterIter)
  }
  return 0;
}

//_________________
void StHbtManager::finish() {

  // EventReader
  if (mEventReader) {
    mEventReader->finish();
  }

  // EventWriters
  StHbtEventWriterIterator EventWriterIter;
  StHbtBaseEventWriter* currentEventWriter;
  for (EventWriterIter = mEventWriterCollection->begin();
       EventWriterIter != mEventWriterCollection->end();
       EventWriterIter++) {
    currentEventWriter = *EventWriterIter;
    currentEventWriter->finish();
  }

  // Analyses
  StHbtAnalysisIterator AnalysisIter;
  StHbtBaseAnalysis* currentAnalysis;
  for (AnalysisIter = mAnalysisCollection->begin();
       AnalysisIter != mAnalysisCollection->end();
       AnalysisIter++) {
    currentAnalysis = *AnalysisIter;
    currentAnalysis->finish();
  }
}

//_________________
StHbtString StHbtManager::report() {
  // Report construction
  string stemp;
  char ctemp[100];

  // EventReader
  stemp = mEventReader->report();

  // EventWriters
  sprintf( ctemp, "\nStHbtManager Reporting %u EventWriters\n", (unsigned int)mEventWriterCollection->size() );
  stemp += ctemp;
  StHbtEventWriterIterator EventWriterIter;
  StHbtBaseEventWriter* currentEventWriter;
  for (EventWriterIter = mEventWriterCollection->begin();
       EventWriterIter != mEventWriterCollection->end();
       EventWriterIter++) {
    std::cout << "StHbtManager - asking for EventWriter Report" << std::endl;
    currentEventWriter = *EventWriterIter;
    stemp+=currentEventWriter->report();
  }

  // Analyses
  sprintf( ctemp, "\nStHbtManager Reporting %u Analyses\n", (unsigned int)mAnalysisCollection->size() );
  stemp += ctemp;
  StHbtAnalysisIterator AnalysisIter;
  StHbtBaseAnalysis* currentAnalysis;
  for (AnalysisIter = mAnalysisCollection->begin();
       AnalysisIter != mAnalysisCollection->end();
       AnalysisIter++) {
    std::cout << "StHbtManager - asking for Analysis Report" << std::endl;
    currentAnalysis = *AnalysisIter;
    stemp+=currentAnalysis->report();
  }

  StHbtString returnThis = stemp;
  return returnThis;
}

//_________________
StHbtBaseAnalysis* StHbtManager::analysis( int n ){
  // Return pointer to n-th analysis
  if ( n<0 || n > (int) mAnalysisCollection->size() ) {
    return nullptr;
  }
  StHbtAnalysisIterator iter = mAnalysisCollection->begin();
  for (int i=0; i<n ;i++) {
    iter++;
  }
  return *iter;
}

//_________________
StHbtBaseEventWriter* StHbtManager::eventWriter( int n ) {
  // Return pointer to n-th analysis
  if ( n<0 || n > (int) mEventWriterCollection->size() ) {
    return nullptr;
  }
  StHbtEventWriterIterator iter = mEventWriterCollection->begin();
  for (int i=0; i<n ;i++) {
    iter++;
  }
  return *iter;
}

//_________________
int StHbtManager::processEvent() {

  // Process a single event by reading it and passing it to each
  // analysis and event writer
  // NOTE - this ReturnHbtEvent makes a *new* StHbtEvent - delete it when done!
  StHbtEvent* currentHbtEvent = mEventReader->returnHbtEvent();

  // Uncomment next line for debug only!
  //  std::cout << "Event reader has returned control to manager" << std::endl;

  // If no HbtEvent is returned, then we abort processing.
  // the question is now: do we try again next time (i.e. there may be an HbtEvent next time)
  // or are we at EOF or something?  If Reader says Status=0, then that means try again later.
  // so, we just return the Reader's Status.

  if ( !currentHbtEvent ) {
    // Reader may return NULL pointer in case it doesn't receive file
    // or current event doesn't pass triggerId cut
    // So, in order not to flood output next line is commented

    // Uncomment for debug only!
    //  std::cout << "StHbtManager::processEvent() - Reader::ReturnHbtEvent() has returned null pointer\n";

    return mEventReader->status();
  }

  // Loop over all the EventWriters
  StHbtEventWriterIterator EventWriterIter;
  for (EventWriterIter = mEventWriterCollection->begin();
       EventWriterIter != mEventWriterCollection->end();
       EventWriterIter++) {

    // Uncomment next line for debug only
    //  std::cout << " *EventWriterIter " <<  *EventWriterIter << std::endl;

    (*EventWriterIter)->writeHbtEvent(currentHbtEvent);
  }

  // Loop over all the Analysis
  StHbtAnalysisIterator AnalysisIter;
  for (AnalysisIter = mAnalysisCollection->begin();
       AnalysisIter != mAnalysisCollection->end();
       AnalysisIter++) {

    // Uncomment next line for debug only
    // std::cout << "StHbtManager::processEvent() - Calling processEvent for analysis " << std::endl;
    (*AnalysisIter)->processEvent(currentHbtEvent);
  }

  if ( currentHbtEvent ) {
    // Uncomment next line for debug only
    // std::cout << "StHbtManager::processEvent() - Removing event";
    delete currentHbtEvent;
    currentHbtEvent = nullptr;
    // Uncomment for debug only
    //std::cout << "\t[DONE]" << std::endl;
  }

  // Uncomment for debug only
  // std::cout << "StHbtManager::processEvent() - return to caller ... " << std::endl;

  return 0;    // 0 = "good return"
}
