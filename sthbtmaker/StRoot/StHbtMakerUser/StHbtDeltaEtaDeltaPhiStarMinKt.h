/**
 * \class StHbtDeltaEtaDeltaPhiStarMinKt
 * \brief Two-dimensional plot of $\Delta\eta$ vs. $\Delta\phi^{*}_{min}$
 *
 * Two-dimensional distribution of $\Deta\eta$ vs. $\Delta\phi^{*}_{min}$
 * of pairs constructed for real and mixed events 
 */

#ifndef StHbtDeltaEtaDeltaPhiStarMinKt_h
#define StHbtDeltaEtaDeltaPhiStarMinKt_h

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseCorrFctn.h"

// ROOT headers
#include "TH2.h"
#include "TVector3.h"

// C++ headers
#include <vector>

// Forward declarations
class StHbtPair;

//_________________
class StHbtDeltaEtaDeltaPhiStarMinKt: public StHbtBaseCorrFctn {

 public:
 
  /// Parametrized constructor
  ///
  /// \param title     Name of the histogram
  /// \param nBinsEta  Number of eta bins
  /// \param mEtaLo    Minimum value of eta
  /// \param mEtaHi    Maximum value of eta
  /// \param nBinsPhi  Number of eta bins
  /// \param mPhiLo    Minimum value of eta
  /// \param mPhiHi    Maximum value of eta
  /// \param ktBins 	 Number of kT bins used in the analysis
  /// \param ktLo   	 Minimum value of kT
  /// \param ktHi   	 Maximum value of kT
  ///
  StHbtDeltaEtaDeltaPhiStarMinKt(const char* title="hDeltaEtaDeltaPhiStarMin",
																 const int& nBinsEta=200, const double& etaLo=-0.5, const double& etaHi=0.5,
																 const int& nBinsPhi=200, const double& phiLo=-0.5, const double& phiHi=0.5,
																 const int& ktBins=10,    const double& ktLo=0.05, const double& ktHi=1.05);
  /// Copy constructor
  StHbtDeltaEtaDeltaPhiStarMinKt(const StHbtDeltaEtaDeltaPhiStarMinKt& corrFctn);
  /// Assignment operator
  StHbtDeltaEtaDeltaPhiStarMinKt& operator=(const StHbtDeltaEtaDeltaPhiStarMinKt& corrFctn);
  /// Destructor
  virtual ~StHbtDeltaEtaDeltaPhiStarMinKt();

  /// Set histogram parameters (nBinsEta, etaLow, etaHi, nBinsPhi, phiLow, phiHi)
  void setHistoParameters(const int& nBinsEta=200, const double& etaLo=-0.1, const double& etaHi=0.1,
													const int& nBinsPhi=200, const double& phiLo=-0.1, const double& phiHi=0.1);
  /// Set kT range (nbins, ktLow, ktHi)
  void setKtRange(const int& nKtBins=10, const double& kTLow = 0.05, const double& kTHi=1.05);
  
  /// Set number of points, inner and outer radii (in meters)
  void setRadiiParameters(const int& npoints=4, const double& radiusLo=0.5, const double& radiusHi=2.);
  
  /// Set charges of the first and the second particles
  void setCharges(const int& charge1 = 1, const int& charge2 = 1);
  
  /// Set magnetic field (Tesla)
  void setBField(const double& bfield = -0.5);

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

  /// Return i-th histogram for numerator
  TH2F* numerator(unsigned int i)   { return ( mNumerator.at(i) ) ? mNumerator.at(i) : nullptr; }
  /// Return i-th histogram for denominator
  TH2F* denominator(unsigned int i) { return ( mDenominator.at(i) ) ? mDenominator.at(i) : nullptr; }

  /// Write histograms
  virtual void writeOutHistos();

  /// Return output list
  virtual TList* getOutputList();
  /// Clone correlation function
  virtual StHbtDeltaEtaDeltaPhiStarMinKt* clone() const { return new StHbtDeltaEtaDeltaPhiStarMinKt(*this); }

 protected:

  /// Numerator made with pairs from the same event
  std::vector< TH2F* > mNumerator;
  /// Denominator made with mixed pairs
  std::vector< TH2F* > mDenominator;

  /// Number of eta bins
  int mEtaBins;
  /// Eta range
  double mEtaRange[2];  
  /// Number of phi* bins
  int mPhiBins;
  /// Phi* range
  double mPhiRange[2];
  
  /// Charge of the first particle
  int mQ1;
  /// Charge of the second particle
  int mQ2;
  /// Step in radius (cm)
  double mRadiusStep;
  /// Inner and outer radii values
  double mRadii[2];
  /// Magnetic field
  double mBField;
  /// Momentum of the first particle
  TVector3 mMomentum1;
  /// Momentum of the second particle
  TVector3 mMomentum2;

  /// Number of the kT bins
  int mNKtBins;
  /// kT step
  double mKtStep;
  /// kT range
  double mKtRange[2];

#ifdef __ROOT__
  ClassDef(StHbtDeltaEtaDeltaPhiStarMinKt, 1);
#endif
};

#endif // StHbtDeltaEtaDeltaPhiStarMinKt_h
