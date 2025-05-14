/**
 * \class StHbtVertexAnalysis
 * \brief Femtoscopic analysis which mixes events with vertex z-binning
 *
 * Femtoscopic analysis which mixes events with respect to the z-position
 * of the primary vertex
 */

#ifndef StHbtVertexAnalysis_h
#define StHbtVertexAnalysis_h

// StHbtMaker headers
#include "StHbtMaker/StHbtAnalysis.h"

//_________________
class StHbtVertexAnalysis : public StHbtAnalysis {

 public:
  /// Standard constructor
  StHbtVertexAnalysis(unsigned int bins=10, float zMin=-100., float zMax = +100.);
  /// Copy constructor
  StHbtVertexAnalysis(const StHbtVertexAnalysis& copy);
  /// Assignment constructor
  StHbtVertexAnalysis& operator=(const StHbtVertexAnalysis& copy);
  /// Destructor
  virtual ~StHbtVertexAnalysis();

  /// Main processor
  virtual void processEvent(const StHbtEvent* thisEvent);
  /// Returns reports of all cuts applied and correlation functions being done
  virtual StHbtString report();
  /// Returns number of events that have z greater than the zMax
  virtual unsigned int overflow()   { return mOverFlow; }
  /// Returns number of events that have z smaller than the zMin
  virtual unsigned int underflow()  { return mUnderFlow; }

  /// Return list of cut settings for the analysis
  virtual TList* listSettings();
  /// Return a TList of objects to be written as output
  virtual TList* getOutputList();

 protected:

  /// min/max z-vertex position allowed to be processed
  float mVertexZ[2];
  /// Number of mixing bins in z-vertex in EventMixing Buffer
  unsigned int mVertexBins;
  /// Number of events encountered which had too large z-vertex
  unsigned int mOverFlow;
  /// Number of events encountered which had too small z-vertex
  unsigned int mUnderFlow;

#ifdef __ROOT__
  ClassDef(StHbtVertexAnalysis, 0)
#endif
};

#endif
