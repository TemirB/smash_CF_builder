/**
 * \class StHbtQinvCorrFctnKt
 * \brief One-dimensional correlation function with kT-binning
 *
 * One-dimensional correlation function with correlation functions binned
 * according to the user request
 */

#ifndef StHbtQinvCorrFctnKt_h
#define StHbtQinvCorrFctnKt_h

// StHbtMaker headers
#include "StHbtMaker/StHbtBaseCorrFctn.h"
#include "StHbtMaker/StHbtBasePairCut.h"

// ROOT headers
#include "TH1D.h"

// C++ headers
#include <vector>

//_________________
class StHbtQinvCorrFctnKt : public StHbtBaseCorrFctn {

 public:

  /// Constructor
  StHbtQinvCorrFctnKt(const char* title = "hQinv",
		      const int& nbins=100, const double& QinvLo=0., const double& QinvHi=1.,
		      const int& nCFs=10, const double& KtLo=0.05, const double& KtHi=1.05);
  /// Copy constructor
  StHbtQinvCorrFctnKt(const StHbtQinvCorrFctnKt& copy);
  /// Assignment operator
  StHbtQinvCorrFctnKt& operator=(const StHbtQinvCorrFctnKt& copy);
  /// Destructor
  virtual ~StHbtQinvCorrFctnKt();

  /// Make report
  virtual StHbtString report();
  /// Add real pair
  virtual void addRealPair(StHbtPair* pair);
  /// Add mixed pair
  virtual void addMixedPair(StHbtPair* pair);

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
  TH1D *numerator(unsigned int i) { return ( mNumerator.at(i) ) ? mNumerator.at(i) : nullptr; }
  /// Return i-th denominator
  TH1D *denominator(unsigned int i) { return ( mDenominator.at(i) ) ? mDenominator.at(i) : nullptr; }

  /// Clone correlation function
  virtual StHbtQinvCorrFctnKt* clone() const { return new StHbtQinvCorrFctnKt(*this); }

 private:

  /// Numerators
  std::vector< TH1D* > mNumerator;
  /// Denominators
  std::vector< TH1D* > mDenominator;

  /// Number of kT bins to study
  int mNKtBins;
  /// Range of kT to plot [min,max]
  double mKtRange[2];
  /// kT bin width
  double mKtStep;

#ifdef __ROOT__
  ClassDef(StHbtQinvCorrFctnKt, 3)
#endif
};

#endif // #define StHbtQinvCorrFctnKt_h
