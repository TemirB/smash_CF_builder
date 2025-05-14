//
// Stores collection of particles for processing
//

// StHbtMaker headers
#include "StHbtPicoEvent.h"

//_________________
StHbtPicoEvent::StHbtPicoEvent() {
  mFirstParticleCollection = new StHbtParticleCollection();
  mSecondParticleCollection = new StHbtParticleCollection();
  mThirdParticleCollection = new StHbtParticleCollection();
}

//_________________
StHbtPicoEvent::~StHbtPicoEvent(){

  StHbtParticleIterator iter;

  if (mFirstParticleCollection){
    for (iter=mFirstParticleCollection->begin();iter!=mFirstParticleCollection->end();iter++){
      delete *iter;
    }
    mFirstParticleCollection->clear();
    delete mFirstParticleCollection;
    mFirstParticleCollection = nullptr;
  }

  if (mSecondParticleCollection){
    for (iter=mSecondParticleCollection->begin();iter!=mSecondParticleCollection->end();iter++){
      delete *iter;
    }
    mSecondParticleCollection->clear();
    delete mSecondParticleCollection;
    mSecondParticleCollection = nullptr;
  }

  if (mThirdParticleCollection){
    if (mThirdParticleCollection->size() != 0 ) {
      for (iter=mThirdParticleCollection->begin();iter!=mThirdParticleCollection->end();iter++){
	       delete *iter;
      }
    }
    mThirdParticleCollection->clear();
    delete mThirdParticleCollection;
    mThirdParticleCollection = nullptr;
  }
}

//_________________
StHbtPicoEvent::StHbtPicoEvent(const StHbtPicoEvent& pico) :
  mFirstParticleCollection(nullptr),
  mSecondParticleCollection(nullptr),
  mThirdParticleCollection(nullptr) {

  StHbtParticleIterator iter;

  mFirstParticleCollection = new StHbtParticleCollection;
  if (pico.mFirstParticleCollection) {
    for( iter=pico.mFirstParticleCollection->begin();
	       iter!=pico.mFirstParticleCollection->end(); iter++) {
      mFirstParticleCollection->push_back( *iter );
    }
  }

  mSecondParticleCollection = new StHbtParticleCollection;
  if (pico.mSecondParticleCollection) {
    for( iter=pico.mSecondParticleCollection->begin();
	       iter!=pico.mSecondParticleCollection->end(); iter++) {
      mSecondParticleCollection->push_back( *iter );
    }
  }

  mThirdParticleCollection = new StHbtParticleCollection;
  if (pico.mThirdParticleCollection) {
    for( iter=pico.mThirdParticleCollection->begin();
	       iter!=pico.mThirdParticleCollection->end(); iter++) {
      mThirdParticleCollection->push_back( *iter );
    }
  }
}

//_________________
StHbtPicoEvent& StHbtPicoEvent::operator=(const StHbtPicoEvent& pico) {

  if( this != &pico) {

    StHbtParticleIterator iter;

    /// Clean collections
    if (mFirstParticleCollection) {
      for( iter=mFirstParticleCollection->begin();
	         iter!=mFirstParticleCollection->end(); iter++ ) {
	      delete *iter;
      }
      mFirstParticleCollection->clear();
      delete mFirstParticleCollection;
      mFirstParticleCollection = nullptr;
    } //if (mFirstParticleCollection)

    if (mSecondParticleCollection) {
      for( iter=mSecondParticleCollection->begin();
	         iter!=mSecondParticleCollection->end(); iter++ ) {
	      delete *iter;
      }
      mSecondParticleCollection->clear();
      delete mSecondParticleCollection;
      mSecondParticleCollection = nullptr;
    } //if (mSecondParticleCollection)

    if (mThirdParticleCollection) {
      for( iter = mThirdParticleCollection->begin();
	         iter != mThirdParticleCollection->end(); iter++ ) {
	      delete *iter;
      }
      mThirdParticleCollection->clear();
      delete mThirdParticleCollection;
      mThirdParticleCollection = nullptr;
    } //if (mThirdParticleCollection)

    /// Copy collections
    mFirstParticleCollection = new StHbtParticleCollection;
    if ( pico.mFirstParticleCollection ) {
      for ( iter = pico.mFirstParticleCollection->begin();
	          iter != pico.mFirstParticleCollection->end(); iter++ ) {
	      mFirstParticleCollection->push_back( *iter );
      }
    } //if (pico.mFirstParticleCollection)

    mSecondParticleCollection = new StHbtParticleCollection;
    if (pico.mSecondParticleCollection) {
      for ( iter = pico.mSecondParticleCollection->begin();
	          iter != pico.mSecondParticleCollection->end(); iter++ ) {
	      mSecondParticleCollection->push_back( *iter );
      }
    } //if (pico.mSecondParticleCollection)

    mThirdParticleCollection = new StHbtParticleCollection;
    if (pico.mThirdParticleCollection) {
      for ( iter = pico.mThirdParticleCollection->begin();
	          iter != pico.mThirdParticleCollection->end(); iter++ ) {
	      mThirdParticleCollection->push_back( *iter );
      }
    } //if (pico.mThirdParticleCollection)

  } //if( this != &pico)

  return *this;
}
