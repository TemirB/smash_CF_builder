/**
 * \class StHbtBasicTrackCut
 * \brief The basic track cut
 *
 * Cuts on particle identification, transverse momentum, rapidity, distance
 * of closest approach to primary vertex and charge. Charge defaults to 1 (positive)
 */

#ifndef StHbtBasicTrackCut_h
#define StHbtBasicTrackCut_h

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseParticleCut.h"
#include "StHbtMaker/StHbtBaseTrackCut.h"

// ROOT headers
#include "TLorentzVector.h"

// C++ headers
#include <limits>

//_________________
class StHbtBasicTrackCut : public StHbtBaseTrackCut {

 public:
  /// Default constructor
  StHbtBasicTrackCut();
  /// Copy constructor
  StHbtBasicTrackCut(const StHbtBasicTrackCut& copy);
  /// Assignment operator
  StHbtBasicTrackCut& operator=(const StHbtBasicTrackCut& copy);
  /// Destructor
  virtual ~StHbtBasicTrackCut();

  /// Test the particle and return true if it meets all criteria. false otherwise.
  virtual bool pass(const StHbtTrack* tr);

  /// Prepare report
  virtual StHbtString report();
  /// Prepare list of settings
  virtual TList *listSettings();

  /// Enumeration of PID
  enum HbtPID { Electron=1, Pion, Kaon, Proton };

  /// Select track type: false (0) - global, true (1) - primary
  void selectPrimary(const bool& type)                       { setType( type ); }
  void setType(const bool& type)                             { mType = type; }
  /// Set charge of the track to select
  void setCharge(const short& charge);
  /// Set min and max range of nhits
  void setNHits(const short& lo, const short& hi);
  /// Set min and max range of nHitsFit/nHitsPossible
  void setNHitsFitOverNHitsPoss(const float& lo)             { mNHitsRat = lo; }
  void setAntiSplit(const float& lo)                         { setNHitsFitOverNHitsPoss( lo ); }
  /// Set min and max ranges of transverse momentum
  void setPt(const float& lo, const float& hi)               { mPt[0] = lo; mPt[1] = hi; }
  void setP(const float& lo, const float& hi)                { mP[0] = lo; mP[1] = hi; }
  void setTranverseMomentum(const float& lo, const float& hi){ setPt( lo , hi ); }
  /// Set min and max ranges of rapidity
  void setRapidity(const float& lo, const float& hi)         { mRapidity[0] = lo; mRapidity[1] = hi; }
  /// Set min and max ranges of pseudorapidity
  void setEta(const float& lo, const float& hi)              { mEta[0] = lo; mEta[1] = hi; }
  void setPseudoRapidity(const float& lo, const float& hi)   { setEta( lo , hi ); }
  /// Set min and max range of DCA
  void setDCA(const float& lo, const float& hi)              { mDCA[0] = lo; mDCA[1] = hi; }

  /// Set type of detector selection:
  /// \param 0 TPC
  /// \param 1 TOF
  /// \param 2 TPC+TOF
  /// \param 3 if(TOF){TPC+TOF} else{TPC}
  /// \param 4 if(TOF&&p>pthresh){TPC+TOF} else if (p<pthresh){TPC}
  void setDetectorSelection(const int& selection) {
    if ( selection<0 || selection>4 ) {
      std::cout << "[WARNING] StHbtBasicTrackCut: wrong detector selection: " << selection
		<< " reset to TPC (0)" << std::endl;
      mDetSelection = 0;
    }
    else {
      mDetSelection = (unsigned char)selection;
    }
  }

  /// Set min and max range of electron nSigma to select
  void setNSigmaElectron(const float& lo, const float& hi)   { mNSigmaElectron[0]=lo; mNSigmaElectron[1]=hi; }
  /// Set min and max range of pion nSigma to select
  void setNSigmaPion(const float& lo, const float& hi)       { mNSigmaPion[0] = lo; mNSigmaPion[1] = hi; }
  /// Set min and max range of kaon nSigma to select
  void setNSigmaKaon(const float& lo, const float& hi)       { mNSigmaKaon[0] = lo; mNSigmaKaon[1] = hi; }
  /// Set min and max range of proton nSigma to select
  void setNSigmaProton(const float& lo, const float& hi)     { mNSigmaProton[0] = lo; mNSigmaProton[1] = hi; }
  /// Set low and hight values for the exclusion cut
  void setNSigmaOther(const float& lo, const float& hi)      { mNSigmaOther[0] = lo; mNSigmaOther[1] = hi; }
  /// Set min and max momentum of the track for TPC identification
  void setTpcP(const float& lo, const float& hi)             { mTpcMom[0] = lo; mTpcMom[1] = hi; }
  void setTpcMomentum(const float& lo, const float& hi)      { setTpcP( lo , hi ); }
  void setTpcMom(const float& lo, const float& hi)           { setTpcP( lo, hi ); }

  /// Set min and max mass square estimated using TOF
  void setMassSqr(const float& lo, const float& hi)          { mTofMassSqr[0] = lo; mTofMassSqr[1] = hi; }
  /// Set min and max momentum for TOF or TPC+TOF identification
  void setTofP(const float& lo, const float& hi)             { mTofMom[0] = lo; mTofMom[1] = hi; }
  void setTofMomentum(const float& lo, const float& hi)      { setTofP( lo , hi ); }
  void setTofMom(const float& lo, const float& hi)           { setTofP( lo , hi ); }

  /// Set min and max values of electron nSigma for TPC+TOF identification
  void setTnTNSigmaElectron(const float& lo, const float& hi){ mTnTNSigmaElectron[0] = lo; mTnTNSigmaElectron[1] = hi; }
  /// Set min and max values of pion nSigma for TPC+TOF identification
  void setTnTNSigmaPion(const float& lo, const float& hi){ mTnTNSigmaPion[0] = lo; mTnTNSigmaPion[1] = hi; }
  /// Set min and max values of kaon nSigma for TPC+TOF identification
  void setTnTNSigmaKaon(const float& lo, const float& hi){ mTnTNSigmaKaon[0] = lo; mTnTNSigmaKaon[1] = hi; }
  /// Set min and max values of proton nSigma for TPC+TOF identification
  void setTnTNSigmaProton(const float& lo, const float& hi)  { mTnTNSigmaProton[0] = lo; mTnTNSigmaProton[1] = hi; }

  /// Set PID to select: 1-electron, 2-pion, 3-kaon, 4-proton
  void setHbtPid(const HbtPID& pid)                          { mPidSelection = pid; }

  /// Is theoretical work
  void setIsTheory(const bool& isTheory)                     { mIsTheory = isTheory; }
  /// Set PDD ID to select (will be checked if IsTheory set to true)
  void setPdgId(const int& pdgId)                            { mPdgId = pdgId; }
  /// Set min and max 1/beta-1/beta_expected values
  void setInvBetaDiff(const float& lo, const float& hi)      { mInvBetaDiff[0]=lo; mInvBetaDiff[1]=hi; }
  /// Set threshold for detector selection =4
  void setPthresh(const float& mom)                          { mPthresh = mom; }
  /// Set verbose mode
  /// \param true print information for each track
  /// \param false do not print (default)
  void setVerboseMode(const bool& isVerbose)                 { mVerbose = isVerbose; }

 protected:

  /// Track type: 0 - global, 1 - primary
  bool mType;
  /// Charge of the track - if 0 the charge is not checked
  char mCharge;
  /// Bounds for number of hits
  unsigned char mNHits[2];
  /// nHitsFit/nHitsPossible
  float mNHitsRat;
  /// Bounds for transverse momentum
  float mPt[2];
  /// Bounds for full momentum
  float mP[2];
  /// Bounds for rapidity
  float mRapidity[2];
  /// Bounds for pseudorapidity
  float mEta[2];
  /// Bounds for DCA to primary vertex
  float mDCA[2];

  /// Type of detector selection:
  /// \param 0 TPC
  /// \param 1 TOF
  /// \param 2 TPC+TOF
  /// \param 3 if(TOF){TPC+TOF} else{TPC}
  /// \param 4 if(TOF&&p>pthresh){TPC+TOF} else if (p<pthresh){TPC}
  unsigned char mDetSelection;

  // TPC identification

  /// Bounds for nsigma dEdx from electron band
  float mNSigmaElectron[2];
  /// Bounds for nsigma dEdx from pion band
  float mNSigmaPion[2];
  /// Bounds for nsigma dEdx from kaon band
  float mNSigmaKaon[2];
  /// Bounds for nsigma dEdx from proton band
  float mNSigmaProton[2];
  /// Bounds for exclusion cuts
  float mNSigmaOther[2];
  /// Momentum of the track for pure TPC identification
  float mTpcMom[2];


  // TOF identification

  /// TOF mass square
  float mTofMassSqr[2];
  /// Momentum of the track for the pure TOF identification
  float mTofMom[2];


  // TPC && TOF identification

  /// Bounds for nsigma dEdx from pion band
  float mTnTNSigmaElectron[2];
  /// Bounds for nsigma dEdx from pion band
  float mTnTNSigmaPion[2];
  /// Bounds for nsigma dEdx from kaon band
  float mTnTNSigmaKaon[2];
  /// Bounds for nsigma dEdx from proton band
  float mTnTNSigmaProton[2];

  /// PID selection
  /// \param 1 electron
  /// \param 2 pion
  /// \param 3 kaon
  /// \param 4 proton
  HbtPID mPidSelection;

  /// Passed tracks counter
  unsigned int mNTracksPassed;
  /// Falied tracks counter
  unsigned int mNTracksFailed;

  /// If work with theory
  bool mIsTheory;
  /// PDG pid
  int mPdgId;
  /// Bounds for 1/beta-1/beta(expected)
  float mInvBetaDiff[2];
  /// Momentum threshold for (detector) selection type == 4 
  float mPthresh;
  /// Print information for each pair (default is false)
  bool mVerbose;


  //
  // Functions for PID
  //

  /// Is good clean TPC identification
  bool isGoodCleanTpcPid(const StHbtTrack *t, TLorentzVector mom);
  /// Is good clean electron identification in TPC
  bool isTpcCleanElectron(const StHbtTrack *t, TLorentzVector mom);
  /// Is good clean pion identification in TPC
  bool isTpcCleanPion(const StHbtTrack *t, TLorentzVector mom);
  /// Is good clean kaon identification in TPC
  bool isTpcCleanKaon(const StHbtTrack *t, TLorentzVector mom);
  /// Is good clean proton identification in TPC
  bool isTpcCleanProton(const StHbtTrack *t, TLorentzVector mom);

  /// Is good particle identification by TOF
  bool isGoodTofPid(const StHbtTrack *t);

  /// Is TPC electron by nSigma(electron) only (uses TnT sigma cut values)
  bool isTpcElectron(const StHbtTrack *t);
  /// Is TPC electron by nSigma(pion) only (uses TnT sigma cut values)
  bool isTpcPion(const StHbtTrack *t);
  /// Is TPC electron by nSigma(kaon) only (uses TnT sigma cut values)
  bool isTpcKaon(const StHbtTrack *t);
  /// Is TPC electron by nSigma(proton) only (uses TnT sigma cut values)
  bool isTpcProton(const StHbtTrack *t);

  /// Check that passes TOF and TPC identification (TnT = TPC && TOF)
  bool isGoodTnT(const StHbtTrack *t);
  /// Check that passes TPC+TOF identification in case of TOF signal,
  /// and clean TPC in the other case
  bool isGoodToT(const StHbtTrack *t, TLorentzVector vec);
  /// Check that passes TPC+TOF identification in case of TOF signal and
  /// momentum greater or equal to threshold, and clean TPC in the other case
  bool isGoodToTThresh(const StHbtTrack *t, TLorentzVector vec);

  /// Check kinematics
  bool isGoodKine(const StHbtTrack *t, TLorentzVector vec);

#ifdef __ROOT__
  ClassDef(StHbtBasicTrackCut, 3);
#endif
};

#endif // StHbtBasicTrackCut_h
