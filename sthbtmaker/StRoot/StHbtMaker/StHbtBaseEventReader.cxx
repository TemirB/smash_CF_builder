//
// The pure virtual base class for femto event readers
//

// StHbtMaker headers
// Base
#include "StHbtBaseEventCut.h"
#include "StHbtBaseTrackCut.h"
#include "StHbtBaseV0Cut.h"
#include "StHbtBaseXiCut.h"
#include "StHbtBaseKinkCut.h"
#include "StHbtBaseEventReader.h"
// Infrastructure
#include "StHbtEvent.h"

#ifdef __ROOT__
ClassImp(StHbtBaseEventReader)
#endif

//_________________
StHbtBaseEventReader::StHbtBaseEventReader() :
  mEventCut(nullptr),
  mTrackCut(nullptr),
  mV0Cut(nullptr),
  mXiCut(nullptr),
  mKinkCut(nullptr),
  mReaderStatus(0),
  mDebug(1) {
  /* empty */
}

//_________________
StHbtBaseEventReader::StHbtBaseEventReader(const StHbtBaseEventReader &copy) :
  mEventCut( copy.mEventCut ),
  mTrackCut( copy.mTrackCut ),
  mV0Cut( copy.mV0Cut ),
  mXiCut( copy.mXiCut ),
  mKinkCut( copy.mKinkCut ),
  mReaderStatus( copy.mReaderStatus ),
  mDebug( copy.mDebug ) {
  /* empty */
}

//_________________
StHbtBaseEventReader& StHbtBaseEventReader::operator=(const StHbtBaseEventReader& aReader) {

  if ( this != &aReader) {
    mEventCut = aReader.mEventCut;
    mTrackCut = aReader.mTrackCut;
    mV0Cut    = aReader.mV0Cut;
    mXiCut    = aReader.mXiCut;
    mKinkCut  = aReader.mKinkCut;
    mReaderStatus = aReader.mReaderStatus;
    mDebug = aReader.mDebug;
  }

  return *this;
}

//_________________
StHbtString StHbtBaseEventReader::report() {

  StHbtString temp = "\n This is the base class StHbtBaseEventReader reporting";
  temp += "\n---> EventCuts in Reader: ";
  if (mEventCut) {
    temp += mEventCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> TrackCuts in Reader: ";
  if (mTrackCut) {
    temp += mTrackCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> V0Cuts in Reader: ";
  if (mV0Cut) {
    temp += mV0Cut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> XiCuts in Reader: ";
  if (mXiCut) {
    temp += mXiCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> KinkCuts in Reader: ";
  if (mKinkCut) {
    temp += mKinkCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n";
  return temp;
}

//_________________
int StHbtBaseEventReader::init(const char* /* ReadWrite */, StHbtString& /* Message */) {
  std::cout << "do-nothing StHbtBaseEventReader::Init()" << std::endl; return 0;
}
