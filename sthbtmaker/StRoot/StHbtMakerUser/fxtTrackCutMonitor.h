/**
 * \class fxtTrackCutMonitor
 * \brief Track cut monitor for basic analysis
 *
 * The class provides histograms for monitoring track cuts
 */

#ifndef fxtTrackCutMonitor_h
#define fxtTrackCutMonitor_h

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseCutMonitor.h"

// ROOT headers
#include "TH1F.h"
#include "TH2F.h"

// Forward declaration
class StHbtTrack;

//_________________
class fxtTrackCutMonitor : public StHbtBaseCutMonitor {

 public:
  /// Constructor with mass
  fxtTrackCutMonitor(const char*, const double);
  /// Copy constructor
  fxtTrackCutMonitor(const fxtTrackCutMonitor& cutMoni);
  /// Assignment operator
  fxtTrackCutMonitor operator=(const fxtTrackCutMonitor& c);
  /// Destructor
  virtual ~fxtTrackCutMonitor();

  /// Fill histograms with track information
  virtual void fill(const StHbtTrack* track);

  /// Write all histograms
  void writeOutHistos();

  /// Ouput list with histograms
  virtual TList* getOutputList();

  // These dummy Fill() functions were introduced to remove a compiler
  // warning related to overloaded base-class Fill() functions being
  // hidden by a single version of Fill() in this derived class
  void fill(const StHbtEvent* /* d */) {;}
  void fill(const StHbtV0* /* d */)    {;}
  void fill(const StHbtXi* /* xi */)   {;}
  void fill(const StHbtKink* /* d */)  {;}
  void fill(const StHbtPair* /* d */)  {;}
  void fill(const StHbtParticleCollection* /* d */) {;}
  void fill(const StHbtEvent* /* d1 */, const StHbtParticleCollection* /* d2 */) {;}
  void fill(const StHbtParticleCollection* /* d1 */, const StHbtParticleCollection* /* d2 */) {;}

  /// DCA of the track
  TH1F* dcaGlobal() { return (mDCAGlobal) ? mDCAGlobal : nullptr; }
  /// DCA of the track
  TH1F* DCAGlobal() { return dcaGlobal(); }
  /// Number of hits
  TH1F* nHits() { return (mNhits) ? mNhits : nullptr; }
  /// Number of hits
  TH1F* NHits() { return nHits(); }
  /// Track momentum
  TH1F* p() { return (mP) ? mP : nullptr; }
  /// Track momentum
  TH1F* P() { return p(); }
  /// Track transverse momentum
  TH1F* pt() { return (mPt) ? mPt : nullptr; }
  /// Track transverse momentum
  TH1F* Pt() { return pt(); }
  /// nSigma(pion) vs p
  TH2F* nSigmaPionVsP() { return (mPVsNsigmaPion) ? mPVsNsigmaPion : nullptr; }
  /// nSigma(pion) vs p
  TH2F* NSigmaPionVsP() { return nSigmaPionVsP(); }
  /// nSigma(pion) vs p
  TH2F* PVsNsigmaPion() { return nSigmaPionVsP(); }
  /// nSigma(kaon) vs p
  TH2F* nSigmaKaonVsP() { return (mPVsNsigmaKaon) ? mPVsNsigmaKaon : nullptr; }
  /// nSigma(kaon) vs p
  TH2F* NSigmaKaonVsP() { return nSigmaKaonVsP(); }
  /// nSigma(kaon) vs p
  TH2F* PVsNsigmaKaon() { return nSigmaKaonVsP(); }
  /// nSigma(proton) vs p
  TH2F* nSigmaProtonVsP() { return (mPVsNsigmaProton) ? mPVsNsigmaProton : nullptr; }
  /// nSigma(proton) vs p
  TH2F* NSigmaProtonVsP() { return nSigmaProtonVsP(); }
  /// nSigma(proton) vs p
  TH2F* PVsNsigmaProton() { return nSigmaProtonVsP(); }
  /// nSigma(electron) vs p
  TH2F* nSigmaElectronVsP() { return (mPVsNsigmaElectron) ? mPVsNsigmaElectron : nullptr; }
  /// nSigma(electron) vs p
  TH2F* NSigmaElectronVsP() { return nSigmaElectronVsP(); }
  /// nSigma(electron) vs p
  TH2F* PVsNsigmaElectron() { return nSigmaElectronVsP(); }
  /// dE/dx vs momentum
  TH2F* dEdxVsP()          { return (mPvsDedx) ? mPvsDedx : nullptr; }
  /// dE/dx vs momentum
  TH2F* DedxVsP()          { return dEdxVsP(); }
  /// dE/dx vs momentum
  TH2F* PvsDedx()          { return dEdxVsP(); }
  /// Pseudorapidity
  TH1F* eta()              { return (mPseudoRapidity) ? mPseudoRapidity : nullptr; }
  /// Pseudorapidity
  TH1F* Eta()              { return eta(); }
  /// Pseudorapidity
  TH1F* PseudoRapidity()   { return eta(); }
  /// Square of mass vs. momentum
  TH2F* massSqrVsP()       { return (mPvsMassSqr) ? mPvsMassSqr : nullptr; }
  /// Square of mass vs. momentum
  TH2F* MassSqrVsP()       { return massSqrVsP(); }
  /// Square of mass vs. momentum
  TH2F* PvsMassSqr()       { return massSqrVsP(); }
  /// Inversed beta vs. momentum
  TH2F* inversedBetaVsP()  { return (mPvsInvBeta) ? mPvsInvBeta : nullptr; }
  /// Inversed beta vs. momentum
  TH2F* InversedBetaVsP()  { return inversedBetaVsP(); }
  /// Inversed beta vs. momentum
  TH2F* PvsInvBeta()       { return inversedBetaVsP(); }
  /// Transverse momenum vs. pseudorapidity
  TH2F* ptVsEta()          { return (mPtVsEta) ? mPtVsEta : nullptr; }
  /// Transverse momenum vs. pseudorapidity
  TH2F* PtVsEta()          { return ptVsEta(); }
  /// Inveresed beta minus inversed beta for pion hypothesis vs. momentum
  TH2F* inversedBetaDiffPionVsP() { return (mInvBetaDiffPionVsP) ? mInvBetaDiffPionVsP : nullptr; }
  /// Inveresed beta minus inversed beta for pion hypothesis vs. momentum
  TH2F* InversedBetaDiffPionVsP() { return inversedBetaDiffPionVsP(); }
  /// Inveresed beta minus inversed beta for kaon hypothesis vs. momentum
  TH2F* inversedBetaDiffKaonVsP() { return (mInvBetaDiffKaonVsP) ? mInvBetaDiffKaonVsP : nullptr; }
  /// Inveresed beta minus inversed beta for kaon hypothesis vs. momentum
  TH2F* InversedBetaDiffKaonVsP() { return inversedBetaDiffKaonVsP(); }
  /// Inveresed beta minus inversed beta for proton hypothesis vs. momentum
  TH2F* inversedBetaDiffProtonVsP() { return (mInvBetaDiffProtonVsP) ? mInvBetaDiffProtonVsP : nullptr; }
  /// Inveresed beta minus inversed beta for proton hypothesis vs. momentum
  TH2F* InversedBetaDiffProtonVsP() { return inversedBetaDiffProtonVsP(); }
  /// Inveresed beta minus inversed beta for proton hypothesis vs. momentum
  TH2F* inversedBetaDiffElectronVsP() { return (mInvBetaDiffElectronVsP) ? mInvBetaDiffElectronVsP : nullptr; }
  /// Inveresed beta minus inversed beta for proton hypothesis vs. momentum
  TH2F* InversedBetaDiffElectronVsP() { return inversedBetaDiffElectronVsP(); }

 private:

  /// DCA of the track to primary vertex
  TH1F* mDCAGlobal;
  /// Number of hits
  TH1F* mNhits;
  /// Momentum
  TH1F* mP;
  /// Transverse momentum
  TH1F* mPt;
  /// nSigma(pi) vs. momentum
  TH2F* mPVsNsigmaPion;
  /// nSigma(K) vs. momentum
  TH2F* mPVsNsigmaKaon;
  /// nSigma(p) vs. momentum
  TH2F* mPVsNsigmaProton;
  /// nSigma(e) vs. momentum
  TH2F* mPVsNsigmaElectron;
  /// dE/dx vs. momentum
  TH2F* mPvsDedx;
  /// Rapidity
  TH1F* mRapidity;
  /// Pseudorapidity
  TH1F* mPseudoRapidity;
  /// Squared mass vs. momentum
  TH2F* mPvsMassSqr;
  /// Inversed beta vs. momentum
  TH2F* mPvsInvBeta;
  /// Pseudorapidity vs. transverse momentum
  TH2F* mPtVsEta;
  /// Inversed beta minus inversed beta for pion hypothesis vs. momentum
  TH2F* mInvBetaDiffPionVsP;
  /// Inversed beta minus inversed beta for kaon hypothesis vs. momentum
  TH2F* mInvBetaDiffKaonVsP;
  /// Inversed beta minus inversed beta for proton hypothesis vs. momentum
  TH2F* mInvBetaDiffProtonVsP;
  /// Inversed beta minus inversed beta for electron hypothesis vs. momentum
  TH2F* mInvBetaDiffElectronVsP;
  /// Particle mass
  double monMass;

#ifdef __ROOT__
  ClassDef(fxtTrackCutMonitor, 3)
#endif
};

#endif // #define fxtTrackCutMonitor_h
