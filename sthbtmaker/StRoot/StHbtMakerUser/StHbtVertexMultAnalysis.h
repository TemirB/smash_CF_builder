/**
 * \class StHbtVertexMultAnalysis
 * \brief Perform femtoscopic analysis using z- and multiplicity binnings
 *
 * Femtoscopic analysis which mixes events with respect to the logitudinal (z)
 * position of the primary vertex and event total multiplicity. These
 * parameters are only set via the constructor.
 *
 * Binning is done by using the mPicoEventCollectionVectorHideAway member
 * provided by the superclass AliFemtoSimpleAnalysis. It should be noted that
 * this member is not created or deleted by the superclass, so this class
 * deletes the member in its destructor.
 */

#ifndef StHbtVertexMultAnalysis_h
#define StHbtVertexMultAnalysis_h

// StHbtMaker headers
#include "StHbtMaker/StHbtAnalysis.h"

// ROOT headers
#include "TList.h"

//_________________
class StHbtVertexMultAnalysis : public StHbtAnalysis {

 public:

  /// Constructor with parameters for event-mixing bins
  ///
  /// If the min/max values are backwards or equal, this class prints a warning
  /// but continues onward, potentially ignoring all events.
  StHbtVertexMultAnalysis( unsigned int zVertexBins = 10,
                  			   double zMin = -100.,
                  			   double zMax = +100.,
                  			   unsigned int multBins = 10,
                  			   double multMin = -1.e9,
                  			   double multMax = +1.e9 );

  /// Copy constructor
  ///
  /// Copies the event-mixing binning parameters, creates a new event
  /// collection and resets the overflow & underflow members to 0.
  StHbtVertexMultAnalysis(const StHbtVertexMultAnalysis& copy);
  /// Assignment operator
  StHbtVertexMultAnalysis& operator=(const StHbtVertexMultAnalysis& copy);
  /// Destructor
  virtual ~StHbtVertexMultAnalysis();

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
  /// Return number events that overflow max multiplicity
  virtual unsigned int overflowMult()     { return mOverFlowMult; }
  /// Return number events that underflow min multiplicity
  virtual unsigned int underflowMult()    { return mUnderFlowMult; }

 protected:
  /// Min/max z-vertex position allowed to be processed
  double mVertexZ[2];
  /// Number of VERTEX mixing bins in z-vertex in EventMixing Buffer
  unsigned int mVertexZBins;
  /// Number of events encountered which had too large z-vertex
  unsigned int mOverFlowVertexZ;
  /// Number of events encountered which had too small z-vertex
  unsigned int mUnderFlowVertexZ;

  /// Min/max multiplicity allowed for event to be processed
  double mMult[2];
  /// Number of multiplicity mixing bins in z-vertex in EventMixing Buffer
  unsigned int mMultBins;
  /// Number of events encountered which had too large multiplicity
  unsigned int mOverFlowMult;
  /// Number of events encountered which had too small multiplicity
  unsigned int mUnderFlowMult;

#ifdef __ROOT__
  ClassDef(StHbtVertexMultAnalysis, 0)
#endif
};

#endif // #define StHbtVertexMultAnalysis_h
