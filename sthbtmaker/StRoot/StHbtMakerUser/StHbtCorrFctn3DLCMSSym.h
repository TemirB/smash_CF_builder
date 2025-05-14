/**
 * \class StHbtCorrFctn3DLCMSSym
 * \brief 3D correlation function in Bertsch-Pratt coordinate system
 *
 * Three-dimensional correlation function of identical particles
 * in Bertsch-Pratt coordinate system (out-side-long)
 */

#ifndef StHbtCorrFctn3DLCMSSym_h
#define StHbtCorrFctn3DLCMSSym_h

// Forward declarations
class TH3F;
class StHbtPairCut;

// StHbtMaker headers
#include "StHbtMaker/StHbtBaseCorrFctn.h"

//_________________
class StHbtCorrFctn3DLCMSSym : public StHbtBaseCorrFctn {

 public:

  /// Build the correlation function with parameters.
  ///
  /// \param title The title with which to give the output
  /// \param nbins The number of bins in each direction of , and q
  StHbtCorrFctn3DLCMSSym(const char* title, const int nbins, const float QHi);
  /// Copy Constructor
  StHbtCorrFctn3DLCMSSym(const StHbtCorrFctn3DLCMSSym& aCorrFctn);
  /// Assignment operator
  StHbtCorrFctn3DLCMSSym& operator=(const StHbtCorrFctn3DLCMSSym& aCorrFctn);
  /// Destructor
  virtual ~StHbtCorrFctn3DLCMSSym();

  /// Make report
  virtual StHbtString report();
  /// Add real pair (from the same event)
  virtual void addRealPair(StHbtPair* aPair);
  /// Add mixed pair (from event mixing)
  virtual void addMixedPair(StHbtPair* aPair);

  /// Finish
  virtual void finish();

  /// Return numerator
  TH3F* numerator()     { return (mNumerator) ? mNumerator : nullptr; }
  /// Return denominator
  TH3F* denominator()   { return (mDenominator) ? mDenominator : nullptr; }
  /// Return numerator weighted by qinv
  TH3F* numeratorW()    { return (mNumeratorW) ? mNumeratorW : nullptr; }
  /// Return denominator weighted by qinv
  TH3F* denominatorW()  { return (mDenominatorW) ? mDenominatorW : nullptr; }

  /// Write all histograms
  void writeOutHistos();
  /// Retrieve list of histograms
  virtual TList* getOutputList();

  /// Set which system to use:
  /// \param true LCMS (default)
  /// \param false PRF
  void setUseLCMS(bool useLCMS)        { mUseLCMS = useLCMS; }
  /// Retrieve which system is used for calculations
  bool  isUseLCMS()                    { return mUseLCMS; }

  /// Clone correlation function
  virtual StHbtBaseCorrFctn* clone() const
  { return new StHbtCorrFctn3DLCMSSym( *this ); }

 private:

  /// Numerator
  TH3F* mNumerator;
  /// Denominator
  TH3F* mDenominator;
  /// Qinv-weighted numerator
  TH3F* mNumeratorW;
  /// Qinv-weighted denominator
  TH3F* mDenominatorW;

  /// False - use PRF, True - use LCMS
  bool mUseLCMS;

#ifdef __ROOT__
  ClassDef(StHbtCorrFctn3DLCMSSym, 1);
#endif
};

#endif // StHbtCorrFctn3DLCMSSym_h
