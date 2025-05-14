//
// Allows to add several cuts to the list
//

// StHbtMaker headers
// Infrastructure
#include "StHbtMultiTrackCut.h"
#include "StHbtTrackCutCollection.h"

#ifdef __ROOT__
ClassImp(StHbtMultiTrackCut)
#endif

//_________________
StHbtMultiTrackCut::StHbtMultiTrackCut() {
  mCutCollection = new StHbtTrackCutCollection;
}

//_________________
StHbtMultiTrackCut::StHbtMultiTrackCut(const StHbtMultiTrackCut& copy) : StHbtBaseTrackCut() {
  StHbtMultiTrackCut();
  StHbtTrackCutIterator iter;
  StHbtBaseTrackCut *t;
  for (iter=copy.mCutCollection->begin(); iter!=copy.mCutCollection->end(); iter++) {
    t = (*iter)->clone();
    if (t) {
      mCutCollection->push_back(t);
    }
  } //for (iter=copy.mCutCollection->begin(); iter!=copy.mCutCollection->end(); iter++)
}

//_________________
StHbtMultiTrackCut& StHbtMultiTrackCut::operator=(const StHbtMultiTrackCut& copy) {
  if ( !mCutCollection ) {
    StHbtMultiTrackCut();
  }

  if ( this != &copy ) {
    StHbtTrackCutIterator iter;
    StHbtBaseTrackCut *t;
    for (iter=copy.mCutCollection->begin(); iter!=copy.mCutCollection->end(); iter++) {
      t = (*iter)->clone();
      if (t) {
	       mCutCollection->push_back(t);
      } //if (t)
    } // for (iter=copy.mCutCollection->begin(); iter!=copy.mCutCollection->end(); iter++)
  } //if ( this != &copy )

  return *this;
}

//_________________
StHbtMultiTrackCut::~StHbtMultiTrackCut() {
  if( mCutCollection ) {
    StHbtTrackCutIterator iter;
    for (iter=mCutCollection->begin(); iter!=mCutCollection->end(); iter++) {
      delete *iter;
    }
  }
  delete mCutCollection;
}

//_________________
StHbtString StHbtMultiTrackCut::report() {
  StHbtString temp;
  temp = "\n StHbtMultiTrackCut::report() reporting ";
  temp += (int)mCutCollection->size();
  temp += " track cuts \n";
  StHbtTrackCutIterator iter;
  for (iter=mCutCollection->begin(); iter!=mCutCollection->end(); iter++) {
    temp += (*iter)->report();
  }
  return temp;
}

//_________________
bool StHbtMultiTrackCut::pass(const StHbtTrack* track) {
  bool temp=0;
  StHbtTrackCutIterator iter;
  for (iter=mCutCollection->begin(); iter!=mCutCollection->end(); iter++) {
    temp = temp || (*iter)->pass(track);
  }
  return temp;
}

//_________________
void StHbtMultiTrackCut::eventBegin(const StHbtEvent* ev) {
  StHbtTrackCutIterator iter;
  for (iter=mCutCollection->begin(); iter!=mCutCollection->end(); iter++) {
    (*iter)->eventBegin(ev);
  }
}

//_________________
void StHbtMultiTrackCut::eventEnd(const StHbtEvent* ev) {
  StHbtTrackCutIterator iter;
  for (iter=mCutCollection->begin(); iter!=mCutCollection->end(); iter++) {
    (*iter)->eventEnd(ev);
  }
}

//_________________
void StHbtMultiTrackCut::addTrackCut(StHbtBaseTrackCut* cut) {
  mCutCollection->push_back(cut);
}

//_________________
StHbtMultiTrackCut* StHbtMultiTrackCut::clone() {
  StHbtMultiTrackCut* cut = this->clone();
  return cut;
}
