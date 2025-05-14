/**
 * \class StHbtModelQinvCorrFctn
 * \brief One-dimensional correlation function for the model estimations
 *
 * One-dimensional correlation function which will store numerators (from real events)
 * and denominatros (from mixed events) with and without femtoscopic weights
 */

#ifndef StHbtModelQinvCorrFctn_h
#define StHbtModelQinvCorrFctn_h

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseCorrFctn.h"

// Forward declarations
class StHbtPair;
class StHbtModelManager;
class TH1D;

//_________________
class StHbtModelQinvCorrFctn: public StHbtBaseCorrFctn {

 public:
  /// Default constructor
  StHbtModelQinvCorrFctn();
  /// Parametrized constructor
  StHbtModelQinvCorrFctn(const char *title, const int& nbins,
                         const double& qInvLow, const double& qInvHi);
  /// Copy constructor
  StHbtModelQinvCorrFctn(const StHbtModelQinvCorrFctn& corrFctn);
  /// Assignment operator
  StHbtModelQinvCorrFctn& operator=(const StHbtModelQinvCorrFctn& corrFctn);
  /// Destructor
  virtual ~StHbtModelQinvCorrFctn();

  /// Method that allows front-loading model manager
  virtual void connectToManager(StHbtModelManager *manager);

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
  virtual void writeOutHistos();

  /// Return output list
  virtual TList* getOutputList();
  /// Clone correlation function
  virtual StHbtModelQinvCorrFctn* clone() const { return new StHbtModelQinvCorrFctn(*this); }

 protected:

  /// Pointer to the model manager that performs femtoscopic
  /// weight calculation
  StHbtModelManager *mManager;

  /// Numerator made with pairs from the same event with femtoscopic weight
  TH1D *mNumeratorWeighted;
  /// Numerator made with pairs from the same event without weights
  TH1D *mNumerator;
  /// Denominator made with mixed pairs with femtoscopic weight
  TH1D *mDenominatorWeighted;
  /// Denominator made with mixed pairs without weights
  TH1D *mDenominator;

#ifdef __ROOT__
  ClassDef(StHbtModelQinvCorrFctn, 1);
#endif
};

#endif // StHbtModelQinvCorrFctn_h
