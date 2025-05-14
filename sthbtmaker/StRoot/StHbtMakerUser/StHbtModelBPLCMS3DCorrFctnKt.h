/**
 * \class StHbtModelBPLCMS3DCorrFctnKt
 * \brief Three-dimensional Bertsch-Pratt correlation function in LCMS for the model estimations
 *
 * Three-dimensional Bertsch-Pratt correlation function which will store
 * numerators (from same event) and denominatros (from mixed events) with
 * and without femtoscopic weights
 */

#ifndef StHbtModelBPLCMS3DCorrFctnKt_h
#define StHbtModelBPLCMS3DCorrFctnKt_h

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseCorrFctn.h"

// ROOT headers
#include "TH3.h"

// C++ headers
#include <vector>

// Forward declarations
class StHbtPair;
class StHbtModelManager;

//_________________
class StHbtModelBPLCMS3DCorrFctnKt: public StHbtBaseCorrFctn {

 public:
  /// Parametrized constructor
  ///
  /// \param title  Name of the histogram
  /// \param nBins  Number of bins (will be used for out, side and long projections)
  /// \param qLo    Minimum value of the q
  /// \param qHi    Maximum value of the q
  /// \param ktBins Number of kT bins used in the analysis
  /// \param ktLo   Minimum value of kT
  /// \param ktHi   Maximum value of kT
  /// \param isFillDenominators Fill/Not fill denominators
  ///
  StHbtModelBPLCMS3DCorrFctnKt(const char* title="hBPLCMSCorrFctn",
                               const int& nBins=80, const double& qLo=-0.4, const double& qHi=0.4,
                               const int& ktBins=10, const double& ktLo=0.05, const double& ktHi=1.05,
                               const bool& isFillDenominators=false);
  /// Copy constructor
  StHbtModelBPLCMS3DCorrFctnKt(const StHbtModelBPLCMS3DCorrFctnKt& corrFctn);
  /// Assignment operator
  StHbtModelBPLCMS3DCorrFctnKt& operator=(const StHbtModelBPLCMS3DCorrFctnKt& corrFctn);
  /// Destructor
  virtual ~StHbtModelBPLCMS3DCorrFctnKt();

  /// Method that allows front-loading model manager
  virtual void connectToManager(StHbtModelManager *manager);

  /// Set kT range (nbins, ktLow, ktHi)
  void setKtRange(const int& nKtBins=10, const double& kTLow = 0.05, const double& kTHi=1.05);

  /// Make report
  virtual StHbtString report();
  /// Add real pair
  virtual void addRealPair(StHbtPair* pair);
  /// Add mixed pair
  virtual void addMixedPair(StHbtPair* pair);
  /// Fill event-mixed distributions (default: false)
  void setFillMixedDistributions(const bool& isFill = false)  { mFillMixedDistributions = isFill; }

  /// Begin event
  virtual void eventBegin(const StHbtEvent* event);
  /// Event end
  virtual void eventEnd(const StHbtEvent* event);
  /// Finish
  virtual void finish();

  /// Write histograms
  virtual void writeOutHistos();

  /// Return i-th histogram for numerator
  TH3F* numerator(int i)           { return ( mNumerator.at(i) ) ? mNumerator.at(i) : nullptr; }
  /// Return i-th weighted numerator
  TH3F* numeratorWeighted(int i)   { return ( mNumeratorWeighted.at(i) ) ? mNumeratorWeighted.at(i) : nullptr; }
  /// Return i-th histogram for denominator
  TH3F* denominator(int i)         { return ( mDenominator.at(i) ) ? mDenominator.at(i) : nullptr; }
  /// Return i-th weighted denominator
  TH3F* denominatorWeighted(int i) { return ( mDenominatorWeighted.at(i) ) ? mDenominatorWeighted.at(i) : nullptr; }

  /// Return output list
  virtual TList* getOutputList();
  /// Clone correlation function
  virtual StHbtModelBPLCMS3DCorrFctnKt* clone() const { return new StHbtModelBPLCMS3DCorrFctnKt(*this); }

 protected:

  /// Pointer to the model manager that performs femtoscopic
  /// weight calculation
  StHbtModelManager *mManager;

  /// Numerator made with pairs from the same event with femtoscopic weight
  std::vector< TH3F* > mNumeratorWeighted;
  /// Numerator made with pairs from the same event without weights
  std::vector< TH3F* > mNumerator;
  /// Denominator made with mixed pairs with femtoscopic weight
  std::vector< TH3F* > mDenominatorWeighted;
  /// Denominator made with mixed pairs without weights
  std::vector< TH3F* > mDenominator;

  /// Number of the kT bins
  int mNKtBins;
  /// kT step
  float mKtStep;
  /// kT range
  float mKtRange[2];

  /// Fill denominators (default: falase)
  bool mFillMixedDistributions;

#ifdef __ROOT__
  ClassDef(StHbtModelBPLCMS3DCorrFctnKt, 2);
#endif
};

#endif // StHbtModelBPLCMS3DCorrFctnKt_h
