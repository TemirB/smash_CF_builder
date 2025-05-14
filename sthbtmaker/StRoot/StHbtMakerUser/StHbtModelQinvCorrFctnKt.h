/**
 * \class StHbtModelQinvCorrFctnKt
 * \brief One-dimensional correlation function with kT-binning for the model estimations
 *
 * One-dimensional correlation function with correlation functions kT-binned
 * according to the user request for model estimations
 */

#ifndef StHbtModelQinvCorrFctnKt_h
#define StHbtModelQinvCorrFctnKt_h

// StHbtMaker headers
#include "StHbtMaker/StHbtBaseCorrFctn.h"
#include "StHbtMaker/StHbtBasePairCut.h"

// C++ headers
#include <vector>

// Forward declarations
class StHbtPair;
class StHbtModelManager;
class TH1D;

//_________________
class StHbtModelQinvCorrFctnKt : public StHbtBaseCorrFctn {

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
  StHbtModelQinvCorrFctnKt(const char* title = "hQinv",
			   const int& nBins=100, const double& qLo=0., const double& qHi=1.,
			   const int& ktBins=10, const double& ktLo=0.05, const double& ktHi=1.05,
			   const bool& isFillDenominators=false);
  /// Copy constructor
  StHbtModelQinvCorrFctnKt(const StHbtModelQinvCorrFctnKt& copy);
  /// Assignment operator
  StHbtModelQinvCorrFctnKt& operator=(const StHbtModelQinvCorrFctnKt& copy);
  /// Destructor
  virtual ~StHbtModelQinvCorrFctnKt();

  /// Method that allows front-loading model manager
  virtual void connectToManager(StHbtModelManager *manager);

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
  void writeOutHistos();

  /// Return output list
  virtual TList* getOutputList();

  /// Set kT bins
  void setKtRange(const int& nbins=10, const double& ktLo=0.05, const double& ktHi=1.05);

  /// Return i-th numerator
  TH1D *numerator(unsigned int i)  { return ( mNumerator.at(i) ) ? mNumerator.at(i) : nullptr; }
  /// Return i-th weighted numerator
  TH1D* numeratorWeighted(int i)   { return ( mNumeratorWeighted.at(i) ) ? mNumeratorWeighted.at(i) : nullptr; }
  /// Return i-th denominator
  TH1D *denominator(unsigned int i) { return ( mDenominator.at(i) ) ? mDenominator.at(i) : nullptr; }
  /// Return i-th weighted denominator
  TH1D* denominatorWeighted(int i) { return ( mDenominatorWeighted.at(i) ) ? mDenominatorWeighted.at(i) : nullptr; }

  /// Clone correlation function
  virtual StHbtModelQinvCorrFctnKt* clone() const { return new StHbtModelQinvCorrFctnKt(*this); }

 private:

  /// Pointer to the model manager that performs femtoscopic
  /// weight calculation
  StHbtModelManager *mManager;

  /// Numerator made with pairs from the same event with femtoscopic weight
  std::vector< TH1D* > mNumeratorWeighted;
  /// Numerator made with pairs from the same event without weights
  std::vector< TH1D* > mNumerator;
  /// Denominator made with mixed pairs with femtoscopic weight
  std::vector< TH1D* > mDenominatorWeighted;
  /// Denominator made with mixed pairs without weights
  std::vector< TH1D* > mDenominator;

  /// Number of kT bins to study
  int mNKtBins;
  /// Range of kT to plot [min,max]
  double mKtRange[2];
  /// kT bin width
  double mKtStep;

  /// Fill denominators (default: falase)
  bool mFillMixedDistributions;

#ifdef __ROOT__
  ClassDef(StHbtModelQinvCorrFctnKt, 1)
#endif
};

#endif // #define StHbtModelQinvCorrFctnKt_h
