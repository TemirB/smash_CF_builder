//
// A helper class for managing many mixing buffers
//

// StHbtMaker headers
#include "StHbtPicoEventCollectionVectorHideAway.h"

//_________________
StHbtPicoEventCollectionVectorHideAway::StHbtPicoEventCollectionVectorHideAway(int bx, double lx, double ux,
																																				       int by, double ly, double uy,
																																				       int bz, double lz, double uz) :
  mBinsTot(0),
  mBinsX(bx), mBinsY(by), mBinsZ(bz),
  mMinX(lx), mMinY(ly), mMinZ(lz),
  mMaxX(ux), mMaxY(uy), mMaxZ(uz),
  mCollection(nullptr),
  mCollectionVector(0) {

  // Constructor
  mBinsTot = mBinsX * mBinsY * mBinsZ;
  mStepX=0;  mStepX = (mMaxX-mMinX) / mBinsX;
  mStepY=0;  mStepY = (mMaxY-mMinY) / mBinsY;
  mStepZ=0;  mStepZ = (mMaxZ-mMinZ) / mBinsZ;

  for ( int i=0; i<mBinsTot; i++) {
    mCollection = new StHbtPicoEventCollection();
    mCollectionVector.push_back(mCollection);
  } //for ( int i=0; i<mBinsTot; i++)
}

//_________________
StHbtPicoEventCollectionVectorHideAway::StHbtPicoEventCollectionVectorHideAway(const StHbtPicoEventCollectionVectorHideAway &coll) :
  mBinsTot(coll.mBinsTot),
  mBinsX(coll.mBinsX),
  mBinsY(coll.mBinsY),
  mBinsZ(coll.mBinsZ),
  mMinX(coll.mMinX),
  mMinY(coll.mMinY),
  mMinZ(coll.mMinZ),
  mMaxX(coll.mMaxX),
  mMaxY(coll.mMaxY),
  mMaxZ(coll.mMaxZ),
  mStepX(coll.mStepX),
  mStepY(coll.mStepY),
  mStepZ(coll.mStepZ) {

  mCollectionVector.clear();
  for (int iter=0; coll.mCollectionVector.size(); iter++) {
    mCollectionVector.push_back(coll.mCollectionVector[iter]);
  } //for (int iter=0; coll.mCollectionVector.size(); iter++)
}

//_________________
StHbtPicoEventCollectionVectorHideAway& StHbtPicoEventCollectionVectorHideAway::operator=(const StHbtPicoEventCollectionVectorHideAway& coll) {

  if ( this != &coll ) {
    mBinsTot = coll.mBinsTot;
    mBinsX = coll.mBinsX;
    mBinsY = coll.mBinsY;
    mBinsZ = coll.mBinsZ;
    mMinX = coll.mMinX;
    mMinY = coll.mMinY;
    mMinZ = coll.mMinZ;
    mMaxX = coll.mMaxX;
    mMaxY = coll.mMaxY;
    mMaxZ = coll.mMaxZ;
    mStepX = coll.mStepX;
    mStepY = coll.mStepY;
    mStepZ = coll.mStepZ;

    mCollectionVector.clear();
    for (int iter=0; coll.mCollectionVector.size(); iter++) {
      mCollectionVector.push_back(coll.mCollectionVector[iter]);
    } //for (int iter=0; coll.mCollectionVector.size(); iter++)
  }

  return *this;
}

//_________________
StHbtPicoEventCollectionVectorHideAway::~StHbtPicoEventCollectionVectorHideAway() {
  mCollectionVector.clear();
}

//_________________
StHbtPicoEventCollection* StHbtPicoEventCollectionVectorHideAway::picoEventCollection(int ix, int iy, int iz) {

  // Return mixing event collection from a given bin
  if ( ix<0 || ix >= mBinsX) return 0;
  if ( iy<0 || iy >= mBinsY) return 0;
  if ( iz<0 || iz >= mBinsZ) return 0;
  return ( ix + iy*mBinsX + iz*mBinsY*mBinsX ) < mCollectionVector.size() ?
           mCollectionVector[( ix + iy*mBinsX + iz*mBinsY*mBinsX )] : NULL;
}

//_________________
StHbtPicoEventCollection* StHbtPicoEventCollectionVectorHideAway::picoEventCollection(double x, double y, double z) {
  // Return mixing event collection for given values on x, y, z axes
  int ix,iy,iz;
  ix=0;iy=0;iz=0;
  if( mStepX!=0 && mStepY!=0 && mStepZ!=0 ) {
    ix =  (int)floor( (x-mMinX) / mStepX );
    iy =  (int)floor( (y-mMinY) / mStepY );
    iz =  (int)floor( (z-mMinZ) / mStepZ );
  }
  return picoEventCollection( ix, iy, iz );
}
