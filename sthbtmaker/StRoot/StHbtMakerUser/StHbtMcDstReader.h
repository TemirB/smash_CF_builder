/**
 * \class StHbtMcDstReader
 * \brief Reader for the McDst format that takes McDstReader
 *
 * The reader class for the McDst format. It reads McDst and
 * converts data to the internal StHbtMaker structure (StHbtEvent,
 * StHbtTrack, etc).
 */

#ifndef StHbtMcDstReader_h
#define StHbtMcDstReader_h

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

// ROOT headers
#include "TSystem.h"
#include "TTree.h"
#include "TChain.h"
#include "TRandom3.h"
#include "TMatrixTLazy.h"

// McDst headers
#include "McDst/McDst.h"
#include "McDst/McEvent.h"
#include "McDst/McParticle.h"
#include "McDst/McArrays.h"
#include "McDst/McDstReader.h"

//_________________
class StHbtMcDstReader : public StHbtBaseEventReader {

 public:
  /// Default constructor
  StHbtMcDstReader();
  /// Parametrized constructor
  /// \param mcDstReader Takes pointer to McDstReader
  /// \param debug Set debut value (see the StHbtBaseEventReader class)
  StHbtMcDstReader(McDstReader* mcDstReader, int debug=1);
  /// Copy constructor
  StHbtMcDstReader(const StHbtMcDstReader& copy);
  /// Assignment operator
  StHbtMcDstReader& operator=(const StHbtMcDstReader& copy);
  /// Destructor
  virtual ~StHbtMcDstReader();

  /// Prepare report
  virtual StHbtString report();
  /// Return instance of StHbtEvent with filled information
  virtual StHbtEvent* returnHbtEvent();

  /// Set McDstReader
  void setMcDstReader(McDstReader* reader) { mMcDstReader = reader; }
  /// Set magnetic field value in kilogauss (default is 0.5T)
  void setMagneticField(const float& field) { mMagField = field; }
  /// Set magnetic field value in kilogauss (default is 0.5T)
  void SetMagneticField(const float& field) { setMagneticField(field); }

  /// Set event plane rotation
  void setRotateEventPlane(const bool& rotate) { mDoRotate = rotate; }
  /// Set event plane rotation
  void SetRotateEventPlane(const bool& rotate) { setRotateEventPlane(rotate); }
  /// Set event plane angle range [min, max]
  void setEventPlaneAngleRange(const float& low, const float& hi)
  { mPhi[0] = low; mPhi[1] = hi; }
  /// Set event plane angle range [min, max]
  void SetEventPlaneAngleRange(const float& low, const float& hi)
  { setEventPlaneAngleRange(low, hi); }
  /// Set event plane resolution
  void setEventPlaneResolution(const float& res) { mEventPlaneResolution = res; }
  /// Set event plane resolution
  void SetEventPlaneResolution(const float& res) { setEventPlaneResolution(res); }

 private:

  /// Simple dE/dx estimation (not for physics analysis)
  double dEdxMean(Double_t mass, Double_t momentum);

  /// Pointer to the McDstReader
  McDstReader *mMcDstReader;

  /// Magnetic field in kilogauss (default is set to 0.5 T)
  float mMagField;

  /// Current event number
  //int mCurrentEvent;

  /// Pointer StHbtEvent that should be return to StHbtAnalysis
  StHbtEvent *mHbtEvent;

  /// Use event plane rotation
  bool mDoRotate;
  /// Randomizer
  TRandom3 *mRandom;
  /// Phi range to generate event plane angle ( default: [-pi;pi] )
  float mPhi[2];
  /// Event plane resolution (default: ideal resolution, i.e. unity)
  float mEventPlaneResolution;

  /// Reference multiplicity (STAR: charged particles with pT>0.15, |eta|<0.5)
  unsigned short mRefMult;
  /// Reference multiplicity of positive particles (STAR: charged particles with pT>0.15, |eta|<0.5)
  unsigned short mRefMultPos;
  /// Reference multiplicity (STAR: charged particles with pT>0.15, |eta|<1)
  unsigned short mRefMult2;
  /// Reference multiplicity of positive particles (STAR: charged particles with pT>0.15, |eta|<1)
  unsigned short mRefMult2Pos;
  /// Sphericity esitmated by particles with  |eta|<0.5, pT>0.15
  float mSphericity;
  /// Sphericity esitmated by particles with  |eta|<1, pT>0.15
  float mSphericity2;

  /// Number of events passed
  long int mEventsPassed;

  /// Matrix for sphericity estimation (pT>0.15 && |eta|<0.5)
  TMatrixTSym<double> *mMatrix;
  /// Matrix for sphericity2 estimation (pT>0.15 && |eta|<1.0)
  TMatrixTSym<double> *mMatrix2;

#ifdef __ROOT__
  ClassDef(StHbtMcDstReader, 3)
#endif
};

#endif // StHbtMcDstReader_h
