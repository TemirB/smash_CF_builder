/**
 * \class StHbtPicoDstReader
 * \brief Reader for the StPicoDst format
 *
 * The reader class for StPicoDst format. It reads McDst and
 * converts data to the internal StHbtMaker structure (StHbtEvent,
 * StHbtTrack, etc).
 */

#ifndef StHbtPicoDstReader_h
#define StHbtPicoDstReader_h

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseEventReader.h"
// Infrastructure
#include "StHbtMaker/StHbtEvent.h"
#include "StHbtMaker/StHbtTrack.h"
#include "StHbtMaker/StHbtV0.h"
#include "StHbtMaker/StHbtKink.h"
#include "StHbtMaker/StHbtXi.h"
#include "StHbtMaker/StHbtEnumeration.h"
#include "StHbtMaker/StHbtString.h"

// StPicoDst headers
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoDstReader.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"

// ROOT haders
#include "TSystem.h"
#include "TChain.h"
#include "TTree.h"

#ifndef _VANILLA_ROOT_
// Forward declarations
class StRefMultCorr;
#endif

//_________________
class StHbtPicoDstReader : public StHbtBaseEventReader {

 public:
  /// Default constructor
  StHbtPicoDstReader();
  /// Constructor
  StHbtPicoDstReader(StPicoDstReader *picoDstReader, int debug=1);
  /// Copy constructor
  StHbtPicoDstReader(const StHbtPicoDstReader& copy);
  /// Assignment operator
  StHbtPicoDstReader& operator=(const StHbtPicoDstReader& copy);
  /// Destructor
  virtual ~StHbtPicoDstReader();

  /// Return StHbtEvent (back to the analysis)
  virtual StHbtEvent *returnHbtEvent();
  /// Make report
  virtual StHbtString report();

  /// Set picoDst reader
  void setPicoDstReader(StPicoDstReader *picoDstReader) { mPicoDstReader = picoDstReader; }
#ifndef _VANILLA_ROOT_
  /// Set StRefMultCorr
  void setRefMultCorrUtil(StRefMultCorr *refMultCorr)   { mRefMultCorrUtil = refMultCorr; }
#endif
  /// Set use StRefMultCorr package
  void setUseRefMultCorr(const bool& useRefMultCorr)    { mUseRefMultCorr = useRefMultCorr; }
  /// Set use ZDC correction for StRefMultCorr package
  void setUseZdcCorrection(const bool& useZdcCorrection){ mUseZdcCorrection = useZdcCorrection; }

 private:

  /// Sphericity calculation for tracks within |eta|<0.5 (or |eta|<1.),
  /// pT>0.15, DCA<3 and nHits>10
  void sphericityCalculation();

  /// Pointer to the StPicoDstReader
  StPicoDstReader *mPicoDstReader;
  /// Pointer to StHbtEvent
  StHbtEvent *mHbtEvent;

  /// Use StRefMultCorr
  bool mUseRefMultCorr;
  /// Use ZDC correction for StRefMultCorr
  bool mUseZdcCorrection;

  /// Sphericity esitmated by tracks with  |eta|<0.5, pT>0.15, DCA<3 and nHits>10
  float mSphericity;
  /// Sphericity esitmated by tracks with  |eta|<1, pT>0.15, DCA<3 and nHits>10
  float mSphericity2;

  /// Number of events passed
  long int mEventsPassed;

#ifndef _VANILLA_ROOT_
  /// Pointer to the StRefMultCorr instance
  StRefMultCorr *mRefMultCorrUtil;
#endif

#ifdef __ROOT__
  ClassDef(StHbtPicoDstReader, 1)
#endif
};

#endif // #define StHbtPicoDstReader_h
