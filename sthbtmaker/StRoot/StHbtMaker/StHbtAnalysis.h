/**
 * \class StHbtAnalsysis
 * \brief An example of the most basic (concrete) analysis.
 *
 * Most other analyses (e.g. StHbtVertexAnalysis) inherit from this one.
 * Provides basic functionality for the analysis. To properly set up the
 * analysis the following steps should be taken:
 *
 * - create particle cuts and add them via setFirstParticleCut and
 *  setSecondParticleCut. If one analyzes identical particle
 *  correlations, the first particle cut must be also the second
 *  particle cut.
 *
 * - create pair cuts and add them via setPairCut
 *
 * - create one or many correlation functions and add them via
 *  addCorrFctn method.
 *
 * - specify how many events are to be strored in the mixing buffer for
 *  background construction
 *
 * Then, when the analysis is run, for each event, the eventBegin is
 * called before any processing is done, then the ProcessEvent is called
 * which takes care of creating real and mixed pairs and sending them
 * to all the registered correlation functions. At the end of each event,
 * after all pairs are processed, eventEnd is called. After the whole
 * analysis finishes (there is no more events to process) finish() is
 * called.
 */

#ifndef StHbtAnalysis_h
#define StHbtAnalysis_h

// StHbtMaker headers
// Base classes
#include "StHbtBaseAnalysis.h"
#include "StHbtBasePairCut.h"
#include "StHbtBaseEventCut.h"
#include "StHbtBaseParticleCut.h"
#include "StHbtBaseCorrFctn.h"

// Infrustructure classes
#include "StHbtCorrFctnCollection.h"
#include "StHbtPicoEventCollection.h"
#include "StHbtParticleCollection.h"
#include "StHbtPicoEvent.h"

// ROOT headers
#include "TList.h"

// Forward declaration
class StHbtPicoEventCollectionVectorHideAway;

//_________________
class StHbtAnalysis : public StHbtBaseAnalysis {

 public:
  /// Construct with default parameters
  ///
  /// All pointer members are initialized to NULL except for the correlation
  /// function collection (mCorrFctnCollection) and the mixing buffer
  /// (mMixingBuffer) which are created with default parameters.
  StHbtAnalysis();

  /// Copy parameters from another analysis.
  ///
  /// All parameters are copied and cuts & correlation functions are cloned.
  /// A new (empty) mixing buffer is created and the number of events processed
  /// (mNeventsProcessed) is set to 0. The EventCollectionHideAway is NOT
  /// copied, and it's up to the subclass to clone if neccessary.
  StHbtAnalysis(const StHbtAnalysis&);
  /// Copy constructor
  StHbtAnalysis& operator=(const StHbtAnalysis&);
  /// Default destructor
  virtual ~StHbtAnalysis();

  //
  // Setters and getters
  //

  /// Return pointer to a pair cut
  virtual StHbtBasePairCut* pairCut();
  /// Return pointer to an event cut
  virtual StHbtBaseEventCut* eventCut();
  /// Return pointer to a first particle cut
  virtual StHbtBaseParticleCut* firstParticleCut();
  /// Return pointer to a first particle cut
  virtual StHbtBaseParticleCut* secondParticleCut();

  /// Return pointer to the correlation function collection
  StHbtCorrFctnCollection* corrFctnCollection();
  /// Access to CFs within the collection
  virtual StHbtBaseCorrFctn* corrFctn(int n);
  /// Add correlation function to the analysis
  void addCorrFctn(StHbtBaseCorrFctn* cf)
  { mCorrFctnCollection->push_back(cf); cf->setAnalysis( (StHbtBaseAnalysis*)this ); }

  /// Set pair cut
  void setPairCut(StHbtBasePairCut* x)
  { mPairCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }
  /// Set event cut
  void setEventCut(StHbtBaseEventCut* x)
  { mEventCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }
  /// Set first particle cut
  void setFirstParticleCut(StHbtBaseParticleCut* x)
  { mFirstParticleCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }
  /// Set second particle cut
  void setSecondParticleCut(StHbtBaseParticleCut* x)
  { mSecondParticleCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }

  /// Set minimal size of the particle collection
  void setMinSizePartCollection(unsigned int& minSize) { mMinSizePartCollection = minSize; }
  /// Set Reshuffling mode for particles
  /// \par 0  as is (do not swap of reshuffle particles)
  /// \par 1  swap particles from pair
  /// \par 2  reshuffle using Fisher Yates algorythm
  void setReshuffle(unsigned int type = 1);
  /// Set verbose mode
  void setVerboseMode(const bool& isVerbose) { mVerbose = isVerbose; }


  /// Return size of the event buffer to mix
  unsigned int numEventsToMix() { return mNumEventsToMix; }
  /// Set number of events to mix
  void setNumEventsToMix(const unsigned int& nmix) { mNumEventsToMix = nmix; }
  /// Return pointer ot the current event
  StHbtPicoEvent* currentPicoEvent() { return mPicoEvent; }
  /// Return pointer to the current mixing buffer (particle collection)
  StHbtPicoEventCollection* mixingBuffer() { return mMixingBuffer; }
  /// If mixing buffer is full
  bool mixingBufferFull()
  { return ( mMixingBuffer->size() >= mNumEventsToMix ); }
  /// If first and second particle are identical
  bool analyzeIdenticalParticles()
  { return (mFirstParticleCut == mSecondParticleCut); }
  ///Returns particles reshuffling type
  char reshuffle() 				  { return mReshuffle; }
  /// Returns report of reshuffle settings
  StHbtString reshReport();
  /// Returns reports of all cuts applied and correlation functions being done
  virtual StHbtString report();
  /// Return list of cut settings for the analysis
  virtual TList* listSettings();
  /// Return a TList of objects to be written as output
  virtual TList* getOutputList();

  /// Initialization code run at the beginning of processing an event
  ///
  /// This is implemented by calling EventBegin for each member cut
  /// and correlation function
  virtual void eventBegin(const StHbtEvent*);

  /// Bulk of analysis code
  ///
  /// This functions begins by calling EventBegin. If the event passes the
  /// event cut, pairs are made from the particles passing their respective
  /// cuts. The pairs are passed to each correlation function's AddRealPair
  /// method. Pairs made between particles in this event and events in the
  /// mixing buffer, are passed to the correlation functions' AddMixedPair
  /// method. The event is then added to the mixing buffer. The EventEnd() is
  /// called exactly once upon exiting this function.
  virtual void processEvent(const StHbtEvent*);

  /// Cleanup code after processing each event
  ///
  /// Calls EventEnd for each member cut and correlation function.
  virtual void eventEnd(const StHbtEvent*);

  /// Returns number of events which have been passed to processEvent.
  int nEventsProcessed()                          { return mNeventsProcessed; }

  /// Finish the analysis
  virtual void finish(); 

  friend class StHbtLikeSignAnalysis;

 protected:

  /// Increment fNeventsProcessed - is this method neccessary?
  void addEventProcessed();

  /// Build pairs, check pair cuts, and call CFs' AddRealPair() or
  /// AddMixedPair() methods. If no second particle collection is
  /// specfied, make pairs within first particle collection.
  ///
  /// \param type Either the string "real" or "mixed", specifying which method
  ///             to call (AddRealPair or AddMixedPair)
  void makePairs(const char* type, StHbtParticleCollection*, StHbtParticleCollection* p2=0);

  /// Mixing Buffer used for Analyses which wrap this one
  StHbtPicoEventCollectionVectorHideAway* mPicoEventCollectionVectorHideAway; //!

  /// Pair cut
  StHbtBasePairCut* mPairCut;
  /// Correlation function collection
  StHbtCorrFctnCollection*  mCorrFctnCollection;
  /// Event cut
  StHbtBaseEventCut* mEventCut;
  /// The first particle cut
  StHbtBaseParticleCut* mFirstParticleCut;
  /// The second particle cut
  StHbtBaseParticleCut* mSecondParticleCut;
  /// Event collection (mixing buffer)
  StHbtPicoEventCollection* mMixingBuffer;
  /// Pointer to the event
  StHbtPicoEvent* mPicoEvent;  //!

  /// How many "previous" events get mixed with this one, to make background
  unsigned int mNumEventsToMix;
  /// Don't use event if it has fewer than this many particles passing ParticleCuts default 0
  unsigned int mNeventsProcessed;
  /// Minimum # particles in ParticleCollection
  unsigned int mMinSizePartCollection;
  /// Particles Reshuffling
  ///0 - no reshuffling
  ///1 - swapping particles in pairs
  ///2 - Fisher–Yates shuffling algorithm for particle collection

  /// default: mReshuffle=1 
  char mReshuffle;
  /// Print info
  bool mVerbose;

#ifdef __ROOT__
  ClassDef(StHbtAnalysis, 0)
#endif
};

//_________________
inline StHbtBasePairCut* StHbtAnalysis::pairCut() { return mPairCut; }

//_________________
inline StHbtBaseEventCut* StHbtAnalysis::eventCut() { return mEventCut; }

//_________________
inline StHbtBaseParticleCut* StHbtAnalysis::firstParticleCut() { return mFirstParticleCut; }

//_________________
inline StHbtBaseParticleCut* StHbtAnalysis::secondParticleCut() { return mSecondParticleCut; }

//_________________
inline StHbtCorrFctnCollection* StHbtAnalysis::corrFctnCollection() { return mCorrFctnCollection; }

#endif // #define StHbtAnalysis_h
