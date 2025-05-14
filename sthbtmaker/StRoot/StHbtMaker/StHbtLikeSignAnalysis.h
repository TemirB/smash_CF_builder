/**
 * \class StHbtLikeSignAnalysis
 * \brief The class is a base class for like-sign analysis with z-binning
 *
 * The class provides posibility to perform femtoscopic analysis
 * using vertex binning
 */

#ifndef StHbtLikeSignAnalysis_h
#define StHbtLikeSignAnalysis_h

// StHbtMaker headers
// Base
#include "StHbtBaseAnalysis.h"
#include "StHbtBaseEventCut.h"
#include "StHbtBaseParticleCut.h"
#include "StHbtBasePairCut.h"
#include "StHbtBaseLikeSignCorrFctn.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtAnalysis.h"
#include "StHbtCorrFctnCollection.h"

//_________________
class StHbtLikeSignAnalysis : public StHbtAnalysis {

 public:
  /// Constructor
  StHbtLikeSignAnalysis(const unsigned int& bins=20, const double& min=-100., const double& max=100.);
  /// Copy constructor
  StHbtLikeSignAnalysis(const StHbtLikeSignAnalysis& copy);
  /// Copy constructor
  StHbtLikeSignAnalysis& operator=(const StHbtLikeSignAnalysis& copy);
  /// Default destructor
  virtual ~StHbtLikeSignAnalysis();

  /// Function that calls processing
  virtual void processEvent(const StHbtEvent*);
  /// Make report
  virtual StHbtString report();
  /// Make report
  virtual StHbtString Report() { return report(); }
  /// Return number of events were lower than min z
  virtual unsigned int overflow() { return mOverFlow; }
  /// Return number of events were lower than min z
  virtual unsigned int Overflow() { return overflow(); }
  /// Return number of events were higher than max z
  virtual unsigned int underflow() { return mUnderFlow; }
  /// Return number of events were higher than max z
  virtual unsigned int Underflow() { return mUnderFlow; }

 protected:
  /// Min/Max z-vertex position allowed to be processed
  double mVertexZ[2];
  /// Number of mixing bins in z-vertex in EventMixing Buffer
  unsigned int mVertexBins;
  /// Number of events encountered which had too large z-vertex
  unsigned int mOverFlow;
  /// Number of events encountered which had too small z-vertex
  unsigned int mUnderFlow;

#ifdef __ROOT__
  ClassDef(StHbtLikeSignAnalysis, 0)
#endif
};

#endif // #define StHbtLikeSignAnalysis_h
