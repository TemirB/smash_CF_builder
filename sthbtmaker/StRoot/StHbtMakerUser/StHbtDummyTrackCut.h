///
/// \file StHbtDummyTrackCut.h
///
/// \class StHbtDummyTrackCut
/// \brief The basic cut for tracks.
///
/// Cuts on particle identification, transverse momentum, rapidity, distance
/// of closest approach to primary vertex and charge.
///
/// ## Default cut values
///
/// |  value   |  min | max |
/// |----------|------|-----|
/// | pt (GeV) |    0 | 100 |
/// | σ-pion   | -100 | 100 |
/// | σ-kaon   | -100 | 100 |
/// | σ-proton | -100 | 100 |
/// | \# Hits  |   10 | 180 |
/// | rapidity |   -2 |   2 |
/// | DCA (cm) |   -1 |  20 |
///
/// Charge defaults to 1 (positive)
///

#ifndef StHbtDummyTrackCut_h
#define StHbtDummyTrackCut_h

#include "StHbtMaker/StHbtBaseTrackCut.h"

class StHbtDummyTrackCut : public StHbtBaseTrackCut {

 public:

  StHbtDummyTrackCut();

  /// Test the particle and return true if it meets all criteria. false otherwise.
  virtual bool pass(const StHbtTrack* tr);

  virtual StHbtString report();
  virtual TList *listSettings();

  void setNSigmaPion(const float& lo, const float& hi) { fNSigmaPion[0] = lo; fNSigmaPion[1] = hi; }
  void setNSigmaKaon(const float& lo, const float& hi) { fNSigmaKaon[0] = lo; fNSigmaKaon[1] = hi; }
  void setNSigmaProton(const float& lo, const float& hi) { fNSigmaProton[0] = lo; fNSigmaProton[1] = hi; }

  void setNHits(const int& lo, const int& hi) { fNHits[0] = lo; fNHits[1] = hi; }
  void setPt(const float& lo, const float& hi) { fPt[0] = lo; fPt[1] = hi; }
  void setRapidity(const float& lo, const float& hi) { fRapidity[0] = lo; fRapidity[1] = hi; }
  void setDCA(const float& lo, const float& hi) { fDCA[0] = lo; fDCA[1] = hi; }
  void setCharge(const int& ch) { fCharge = ch; }

 protected:

  int     fCharge;          ///< charge of the track - if 0 the charge is not checked
  float   fNSigmaPion[2];   ///< bounds for nsigma dEdx from pion band
  float   fNSigmaKaon[2];   ///< bounds for nsigma dEdx from kaon band
  float   fNSigmaProton[2]; ///< bounds for nsigma dEdx from proton band
  int     fNHits[2];        ///< bounds for number of hits
  float   fPt[2];           ///< bounds for transverse momentum
  float   fRapidity[2];     ///< bounds for rapidity
  float   fDCA[2];          ///< bounds for DCA to primary vertex

  long    fNTracksPassed;   ///< passed tracks counter
  long    fNTracksFailed;   ///< falied tracks counter

#ifdef __ROOT__
  ClassDef(StHbtDummyTrackCut, 2);
#endif
};

#endif
