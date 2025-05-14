/**
 * \class StHbtPicoEventCollectionVectorHideAway
 * \brief A helper class for managing many mixing buffers
 *
 * A helper class for managing many mixing buffers with up to
 * three variables used for binning.
 */

#ifndef StHbtPicoEventCollectionVectorHideAway_h
#define StHbtPicoEventCollectionVectorHideAway_h

// C++ headers
#include <cmath>
#include <limits>
#include <float.h>

// StHbtMaker headers
// Infrastructure
#include "StHbtPicoEvent.h"
#include "StHbtPicoEventCollection.h"
#include "StHbtPicoEventCollectionVector.h"

//_________________
class StHbtPicoEventCollectionVectorHideAway {

 public:
  /// Constructor
  StHbtPicoEventCollectionVectorHideAway(int bx=1, double lx=-FLT_MAX, double ux=FLT_MAX,
                              					 int by=1, double ly=-FLT_MAX, double uy=FLT_MAX,
                              					 int bz=1, double lz=-FLT_MAX, double uz=FLT_MAX);
  /// Copy constructor
  StHbtPicoEventCollectionVectorHideAway(const StHbtPicoEventCollectionVectorHideAway &copy);
  /// Copy constructor
  StHbtPicoEventCollectionVectorHideAway& operator=(const StHbtPicoEventCollectionVectorHideAway& copy);
  /// Default destructor
  ~StHbtPicoEventCollectionVectorHideAway();

  /// Return pico event collection
  StHbtPicoEventCollection* picoEventCollection(int, int, int);
  /// Return pico event collection
  StHbtPicoEventCollection* picoEventCollection(double x, double y=0, double z=0);

  /// Return bin number on the x axis
  unsigned int binXNumber(double x) const { return (int)floor( (x - mMinX) / mStepX ); }
  /// Return bin number on the y axis
  unsigned int binYNumber(double y) const { return (int)floor( (y - mMinY) / mStepY ); }
  /// Return bin number on the z axis
  unsigned int binZNumber(double z) const { return (int)floor( (z - mMinZ) / mStepZ ); }

 private:

  /// Total number of bins
  int mBinsTot;
  /// Number of bins on x axis
  int mBinsX;
  /// Number of bins on y axis
  int mBinsY;
  /// Number of bins on z axis
  int mBinsZ;
  /// Minimal value on x axis
  double mMinX;
  /// Minimal value on y axis
  double mMinY;
  /// Minimal value on z axis
  double mMinZ;
  /// Maximal value on x axis
  double mMaxX;
  /// Maximal value on y axis
  double mMaxY;
  /// Maximal value on z axis
  double mMaxZ;
  /// Steps on x axis
  double mStepX;
  /// Steps on y axis
  double mStepY;
  /// Steps on z axis
  double mStepZ;
  /// Pico event collection
  StHbtPicoEventCollection* mCollection;
  /// Collection vector
  StHbtPicoEventCollectionVector mCollectionVector;
};

#endif // #define StHbtPicoEventCollectionVectorHideAway_h
