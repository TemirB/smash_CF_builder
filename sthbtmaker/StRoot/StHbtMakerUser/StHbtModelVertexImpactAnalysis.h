/**
 * \class StHbtModelVertexImpactAnalysis
 * \brief Perform femtoscopic analysis using z- and impact binnings
 *
 * Femtoscopic analysis which mixes events with respect to the logitudinal (z)
 * position of the primary vertex and event total impact. These
 * parameters are only set via the constructor.
 *
 * Binning is done by using the mPicoEventCollectionVectorHideAway member
 * provided by the superclass AliFemtoSimpleAnalysis. It should be noted that
 * this member is not created or deleted by the superclass, so this class
 * deletes the member in its destructor.
 */

#ifndef StHbtModelVertexImpactAnalysis_h
#define StHbtModelVertexImpactAnalysis_h

// StHbtMaker headers
#include "StHbtMaker/StHbtAnalysis.h"

// ROOT headers
#include "TList.h"

//_________________
class StHbtModelVertexImpactAnalysis : public StHbtAnalysis {

 public:

  /// Constructor with parameters for event-mixing bins
  ///
  /// If the min/max values are backwards or equal, this class prints a warning
  /// but continues onward, potentially ignoring all events.
  StHbtModelVertexImpactAnalysis( unsigned int zVertexBins = 10,
                  			   double zMin = -100.,
                  			   double zMax = +100.,
                  			   unsigned int impactBins = 10,
                  			   double impactMin = -0.1,
                  			   double impactMax = +100.1 );

  /// Copy constructor
  ///
  /// Copies the event-mixing binning parameters, creates a new event
  /// collection and resets the overflow & underflow members to 0.
  StHbtModelVertexImpactAnalysis(const StHbtModelVertexImpactAnalysis& copy);
  /// Assignment operator
  StHbtModelVertexImpactAnalysis& operator=(const StHbtModelVertexImpactAnalysis& copy);
  /// Destructor
  virtual ~StHbtModelVertexImpactAnalysis();

  /// Passes the event to StHbtAnalysis::processEvent after
  /// determining which (if any) mixing buffer to use.
  virtual void processEvent(const StHbtEvent* thisEvent);
  /// Returns reports of all cuts applied and correlation functions being done
  virtual StHbtString report();

  /// Return a TList of analysis settings.
  ///
  /// The TList comprises TObjStrings describing the settings provided by the
  /// StHbtAnalysis::ListSettings class followed by all event-mixing
  /// binning parameters.
  virtual TList* listSettings();
  /// Return a TList of objects to be written as output
  virtual TList* getOutputList();    ;

  /// Return number of events that overflow max vertex z
  virtual unsigned int overflowVertexZ()  { return mOverFlowVertexZ; }
  /// Return number of events that underflow min vertex z
  virtual unsigned int underflowVertexZ() { return mUnderFlowVertexZ; }
  /// Return number events that overflow max impact
  virtual unsigned int overflowImpact()     { return mOverFlowImpact; }
  /// Return number events that underflow min impact
  virtual unsigned int underflowImpact()    { return mUnderFlowImpact; }

 protected:
  /// Min/max z-vertex position allowed to be processed
  double mVertexZ[2];
  /// Number of VERTEX mixing bins in z-vertex in EventMixing Buffer
  unsigned int mVertexZBins;
  /// Number of events encountered which had too large z-vertex
  unsigned int mOverFlowVertexZ;
  /// Number of events encountered which had too small z-vertex
  unsigned int mUnderFlowVertexZ;

  /// Min/max impact allowed for event to be processed
  double mImpact[2];
  /// Number of impact mixing bins in z-vertex in EventMixing Buffer
  unsigned int mImpactBins;
  /// Number of events encountered which had too large impact
  unsigned int mOverFlowImpact;
  /// Number of events encountered which had too small impact
  unsigned int mUnderFlowImpact;

#ifdef __ROOT__
  ClassDef(StHbtModelVertexImpactAnalysis, 0)
#endif
};

#endif // #define StHbtModelVertexImpactAnalysis_h
