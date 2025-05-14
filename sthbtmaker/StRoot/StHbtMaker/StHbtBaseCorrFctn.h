/**
 * \class StHbtBaseCorrFctn
 * \brief The pure-virtual base class for correlation functions
 *
 * All correlation function classes must inherit from this one.
 * This class has a optional pointers to the "parent" analysis and
 * a pair cut
 */

#ifndef StHbtBaseCorrFctn_h
#define StHbtBaseCorrFctn_h

// C++ headers
#include <iostream>

// StHbtMaker headers
// Base
#include "StHbtBaseAnalysis.h"
#include "StHbtBasePairCut.h"
// Real
#include "StHbtEvent.h"
#include "StHbtPair.h"
#include "StHbtTriplet.h"

// ROOT headers
#include "TList.h"

//_________________
class StHbtBaseCorrFctn {

 public:
  /// Default constuctor
  StHbtBaseCorrFctn();
  /// Copy constructor
  StHbtBaseCorrFctn(const StHbtBaseCorrFctn& copy);
  /// Assignment operator
  StHbtBaseCorrFctn& operator=(const StHbtBaseCorrFctn& copy);
  /// Default destructor
  virtual ~StHbtBaseCorrFctn() {/* no-op */}

  /// Report
  virtual StHbtString report() = 0;

  /// Add real pair
  virtual void addRealPair(StHbtPair*);
  /// Add mixed pair
  virtual void addMixedPair(StHbtPair*);

  /// Add real triplet
  virtual void addRealTriplet(const StHbtTriplet*);
  /// Add mixed triplet
  virtual void addMixedTriplet(const StHbtTriplet*);

  /// Not Implemented - Add particle with options
  virtual void addFirstParticle(StHbtParticle *particle, bool mixing);
  /// Not Implemented - Add particle
  virtual void addSecondParticle(StHbtParticle *particle);

  /// Event start
  virtual void eventBegin(const StHbtEvent*)    { /* no-op */ }
  /// Event end
  virtual void eventEnd(const StHbtEvent*)      { /* no-op */ }
  /// Finish method
  virtual void finish() = 0;

  /// Return output list
  virtual TList* getOutputList() = 0;

  /// Return correlation function clone
  virtual StHbtBaseCorrFctn* clone() const = 0;
  /// Return pointer to the pair cut
  virtual StHbtBasePairCut* getPairCut() { return mPairCut; }

  // The following allows "back-pointing" from the CorrFctn to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  /// Return a pointer to the analysis
  StHbtBaseAnalysis* hbtAnalysis() { return mBaseAnalysis; }
  /// Set analysis
  void setAnalysis(StHbtBaseAnalysis* ana) { mBaseAnalysis = ana; }
  /// Set pair cut
  void setPairSelectionCut(StHbtBasePairCut *cut) { mPairCut = cut; }

 protected:
  /// Pointer to the base analysis
  StHbtBaseAnalysis* mBaseAnalysis; //!
  /// Pointer to the base pair cut
  StHbtBasePairCut* mPairCut;       //!

 private:

#ifdef __ROOT__
  ClassDef(StHbtBaseCorrFctn, 0)
#endif
};

#endif // #define StHbtBaseCorrFctn_h
