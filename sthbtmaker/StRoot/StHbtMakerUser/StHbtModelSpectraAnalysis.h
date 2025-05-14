#ifndef StHbtModelSpectraAnalysis_h
#define StHbtModelSpectraAnalysis_h


// C++ headers
#include <iostream>

// McDst headers
#include "McDst/McDstReader.h"
#include "McDst/McDst.h"
#include "McDst/McEvent.h"
#include "McDst/McParticle.h"
#include "McDst/McRun.h"

// StHbtMaker headers
#include "StHbtMaker/StHbtModelWeightGeneratorLednicky.h"

// ROOT headers
#include "TObject.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TProfile.h"

const int nCh = 2; // positive, negative
const int nCent = 4; // number of centrality classes
//________________
class StHbtModelSpectraAnalysis {

 public:
  /// Constructor
  /// \param oFileName Name of the output file where the histograms will
  ///                  be stored
  StHbtModelSpectraAnalysis(const char* oFileName = "oTest.root");
  /// Destructor
  virtual ~StHbtModelSpectraAnalysis();

  /// Init method inherited from StMaker
  virtual Int_t Init(const char* inFile);
  /// Make method inherited from StMaker
  virtual Int_t Make(Long64_t iEvent);
  /// Finish method inherited from StMaker
  virtual Int_t Finish();
  /// Looper
  void Loop();

  //
  // Setters
  //

  /// Set debug status
  void setDebugStatus(bool status)                      { mDebug = status; }
  /// Set event verbose status
  void setEventVerboseStatus(bool status)               { mEventVerbose = status; }
  /// Set output file name
  void setOutputFileName(const char* name)              { mOutFileName = name; }

  /// Set cut on track pT
  void setPt(const float& lo, const float& hi)          { mPt[0] = lo; mPt[1] = hi; }
  /// Set cut on track pseudorapidity
  void setEta(const float& lo, const float& hi)         { mEta[0] = lo; mEta[1] = hi; }
  /// Set residual charge
  void setZResCh(const double& value)                   { mZResCh = value; }

 private:
  /// Create histograms
  void CreateHistograms();
  /// Create event histograms
  void CreateEventHistograms();
  /// Create track histograms
  void CreateTrackHistograms();
  /// Event cut
  Bool_t EventCut(McEvent *event);
  /// Track cut
  Bool_t TrackCut(McParticle *const&  particle);

  /// Debug mode
  Bool_t mDebug;

  /// Event verbose mode
  Bool_t mEventVerbose;

  /// Transverse momentum [min,max]
  Float_t mPt[2];
  /// PseudoRapidity [min,max]
  Float_t mEta[2];
  /// Center-of-mass rapidity
  Float_t mYcm;
  /// Residual charge
  Float_t mZResCh;

  /// Output file name
  const char* mOutFileName;
  /// Output file
  TFile* mOutFile;
  /// Impact parameter
  TH1F *hImpParam;
  /// Number of event for each centrality class (used for normalization)
  TH1D *hCent;
  /// Original total momentum distritbution
  TH1D *hPtOrigin[nCent][nCh];
  /// Original transverse momentum distritbution
  TH1D *hPOrigin[nCent][nCh];
  /// total momentum distritbution distorted by third-body Coulomb (weighted by p-N weights)
  TH1D *hPtDistorted[nCent][nCh];
  /// transverse momentum distritbution distorted by third-body Coulomb (weighted by p-N weights)
  TH1D *hPDistorted[nCent][nCh];
  /// Third-body Coulomb (p-N) weight
  TH1D *hWeif[nCent][nCh];
  /// Third-body Coulomb (p-N) weight versus total momentum
  TH2F *hWeifVsP[nCent][nCh];
  /// Third-body Coulomb (p-N) weight versus total momentum (profile)
  TProfile *pWeifVsP[nCent][nCh];

  McDstReader* mReader;
  McParticle *mParticle;
  McDst *mDst;
  McEvent *mEvent;

  StHbtModelWeightGeneratorLednicky* mLedWei;

#ifdef __ROOT__
  ClassDef(StHbtModelSpectraAnalysis, 0);
#endif // #ifdef __ROOT__
};

#endif // StHbtModelSpectraAnalysis_h
