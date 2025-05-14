
#ifndef StHbtFemtoDstReader_h
#define StHbtFemtoDstReader_h

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

// StFemtoDst headers
#include "StFemtoEvent/StFemtoDst.h"
#include "StFemtoEvent/StFemtoDstReader.h"
#include "StFemtoEvent/StFemtoEvent.h"
#include "StFemtoEvent/StFemtoTrack.h"
#include "StFemtoEvent/StFemtoArrays.h"

// ROOT haders
#include "TSystem.h"
#include "TChain.h"
#include "TTree.h"
#include "TMatrixTLazy.h"

//_________________
class StHbtFemtoDstReader : public StHbtBaseEventReader {

 public:
  /// Default constructor
  StHbtFemtoDstReader();
  /// Constructor
  StHbtFemtoDstReader(StFemtoDstReader *femtoDstReader, int debug=1);
  /// Copy constructor
  StHbtFemtoDstReader(const StHbtFemtoDstReader& copy);
  /// Assignment operator
  StHbtFemtoDstReader& operator=(const StHbtFemtoDstReader& copy);
  /// Destructor
  virtual ~StHbtFemtoDstReader();

  /// Return StHbtEvent (back to the analysis)
  virtual StHbtEvent *returnHbtEvent();
  /// Make report
  virtual StHbtString report();

  /// Set femtoDst reader
  void setFemtoDstReader(StFemtoDstReader *femtoDstReader) { mFemtoDstReader = femtoDstReader; }

 private:

  /// Pointer to the StFemtoDstReader
  StFemtoDstReader *mFemtoDstReader;
  /// Pointer to StHbtEvent
  StHbtEvent *mHbtEvent;

  /// Sphericity esitmated by tracks with  |eta|<0.5, pT>0.15, DCA<3 and nHits>10
  float mSphericity;
  /// Sphericity esitmated by tracks with  |eta|<1, pT>0.15, DCA<3 and nHits>10
  float mSphericity2;

  /// Number of events passed
  long int mEventsPassed;

  /// Matrix for sphericity estimation (pT>0.15 && |eta|<0.5)
  TMatrixTSym<double> *mMatrix;
  /// Matrix for sphericity2 estimation (pT>0.15 && |eta|<1.0)
  TMatrixTSym<double> *mMatrix2;

#ifdef __ROOT__
  ClassDef(StHbtFemtoDstReader, 3)
#endif
};

#endif // #define StHbtFemtoDstReader_h
