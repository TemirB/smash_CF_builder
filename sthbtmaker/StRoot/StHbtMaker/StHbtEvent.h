/**
 * \class StHbtEvent
 * \brief StHbtEvent holds the event information specific and particle collections
 *
 * StHbtEvent is the "transient DST". Objects of this class are
 * generated from the input data by an StHbtEventReader, and then
  *presented to the cuts of the various active Analyses.
 */

#ifndef StHbtEvent_h
#define StHbtEvent_h

// C++ headers
#include <vector>
#include <limits>

// ROOT headers
#include "TVector3.h"
#include "TLorentzVector.h"

// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtTrackCollection.h"
#include "StHbtV0Collection.h"
#include "StHbtXiCollection.h"
#include "StHbtKinkCollection.h"


// Forward declarations
class StHbtBaseTrackCut;
class StHbtBaseV0Cut;
class StHbtBaseXiCut;
class StHbtBaseKinkCut;

//_________________
class StHbtEvent {

 public:
  /// Constructor
  StHbtEvent();
  /// Copy constructor
  StHbtEvent(const StHbtEvent& ev, StHbtBaseTrackCut* track=nullptr,
             StHbtBaseV0Cut* v0=nullptr, StHbtBaseXiCut* xi=nullptr,
             StHbtBaseKinkCut* kink=nullptr);
  /// Assignment operator
  StHbtEvent& operator=(const StHbtEvent& event);
  /// Destructor
  virtual ~StHbtEvent();

  /// Rotate event
  void rotateZ(const double& angle);
  /// Rotate event
  void RotateZ(const double& angle) { rotateZ(angle); }

  //
  // Getters
  //

  /// Event ID
  unsigned int eventId() const { return mEventNumber; }
  /// Event ID
  unsigned int EventId() const { return eventId(); }
  /// Run ID
  unsigned int runId() const { return runNumber(); }
  /// Run ID
  unsigned int RunId() const { return runNumber(); }
  /// Run number
  unsigned int runNumber() const { return mRunNumber; }
  /// Run number
  unsigned int RunNumber() const { return runNumber(); }
  /// Magnetic field strength
  float magneticField() const { return bField(); }
  /// Magnetic field strength
  float MagneticField() const { return bField(); }
  /// Magnetic field strength
  float bField() const { return mMagneticField; }
  /// Magnetic field strength
  float BField() const { return bField(); }
  /// Reference multiplicity
  unsigned short refMult() const { return mRefMult; }
  /// Reference multiplicity
  unsigned short RefMult() const { return refMult(); }
  /// Reference multiplicity of positive tracks
  unsigned short refMultPositive() const { return mRefMultPos; }
  /// Reference multiplicity of positive tracks
  unsigned short RefMultPositive() const { return refMultPositive(); }
  /// Reference multiplicity of negative tracks
  unsigned short refMultNegative() const { return (mRefMult - mRefMultPos); }
  /// Reference multiplicity of negative tracks
  unsigned short RefMultNegative() const { return refMultNegative(); }
  /// Reference multiplicity (2)
  unsigned short refMult2() const { return mRefMult2; }
  /// Reference multiplicity (2)
  unsigned short RefMult2() const { return refMult2(); }
  /// Reference multiplicity (2) of positive tracks
  unsigned short refMult2Positive() const { return mRefMult2Pos; }
  /// Reference multiplicity (2) of positive tracks
  unsigned short RefMult2Positive() const { return refMult2Positive(); }
  /// Reference multiplicity (2) of negative tracks
  unsigned short refMult2Negative() const { return (mRefMult2 - mRefMult2Pos); }
  /// Reference multiplicity (2) of negative tracks
  unsigned short RefMult2Negative() const { return refMult2Negative(); }
  /// Corrected reference multiplicity
  unsigned short refMultCorr() const { return mRefMultCorr; }
  /// Corrected reference multiplicity
  unsigned short RefMultCorr() const { return refMultCorr(); }
  /// Weight of corrected reference multiplicity
  unsigned short refMultCorrWeight() const { return mRefMultCorrWeight; }
  /// Weight of corrected reference multiplicity
  unsigned short RefMultCorrWeight() const { return refMultCorrWeight(); }
  /// Reference multiplicity of global tracks
  unsigned short grefMult() const { return mGRefMult; }
  /// Reference multiplicity of global tracks
  unsigned short GRefMult() const { return grefMult(); }
  /// Reference multiplicity of positive global tracks
  unsigned short grefMultPositive() const { return mGRefMultPos; }
  /// Reference multiplicity of positive global tracks
  unsigned short GRefMultPositive() const { return grefMultPositive(); }
  /// Reference multiplicity of negative global tracks
  unsigned short grefMultNegative() const { return (mGRefMult - mGRefMultPos); }
  /// Reference multiplicity of negative global tracks
  unsigned short GRefMultNegative() const { return grefMultNegative(); }
  /// Multiplicity of TOF tray hits
  unsigned short btofTrayMultiplicity() const { return mBTofTrayMultiplicity; }
  /// Multiplicity of TOF tray hits
  unsigned short BTofTrayMultiplicity() const { return btofTrayMultiplicity(); }
  /// Number of TOF-matched tracks
  unsigned short numberOfBTofMatched() const { return mNBTOFMatch; }
  /// Number of TOF-matched tracks
  unsigned short NumberOfBTofMatched() const { return numberOfBTofMatched(); }
  /// Number of BEMC-matched tracks
  unsigned short numberOfBEMCMatched() const { return mNBEMCMatch; }
  /// Number of BEMC-matched tracks
  unsigned short NumberOfBEMCMatched() const { return numberOfBEMCMatched(); }
  /// Number of primary tracks
  unsigned short numberOfPrimaryTracks() const { return mNumberOfPrimaryTracks; }
  /// Number of primary tracks
  unsigned short NumberOfPrimaryTracks() const { return numberOfPrimaryTracks(); }
  /// Number of global tracks
  unsigned short numberOfGlobalTracks() const { return mNumberOfGlobalTracks; }
  /// Number of global tracks
  unsigned short NumberOfGlobalTracks() const { return numberOfGlobalTracks(); }
  /// Sum of ADC from east ZDC
  unsigned short zdcSumAdcEast() const { return mZdcSumAdcEast; }
  /// Sum of ADC from east ZDC
  unsigned short ZdcSumAdcEast() const { return zdcSumAdcEast(); }
  /// Sum of ADC from west ZDC
  unsigned short zdcSumAdcWest() const { return mZdcSumAdcWest; }
  /// Sum of ADC from west ZDC
  unsigned short ZdcSumAdcWest() const { return zdcSumAdcWest(); }
  /// ZDC coincidence rate
  float zdcCoincidenceRate() const { return mZdcCoincidenceRate; }
  /// ZDC coincidence rate
  float ZdcCoincidenceRate() const { return zdcCoincidenceRate(); }
  /// BBC coincidence rate
  float bbcCoincidenceRate() const { return mBbcCoincidenceRate; }
  /// BBC coincidence rate
  float BbcCoincidenceRate() const { return bbcCoincidenceRate(); }
  /// Sphericity (transverse) estimated in |eta|<0.5
  float sphericity() const { return (mSphericity<0) ? -1. : (float)mSphericity * 0.01; }
  /// Sphericity (transverse) estimated in |eta|<0.5
  float Sphericity() const { return sphericity(); }
  /// Sphericity (transverse) estimated in |eta|<1
  float sphericity2() const { return (mSphericity2<0) ? -1. : (float)mSphericity2 * 0.01; }
  /// Sphericity (transverse) estimated in |eta|<1
  float Sphericity2() const { return sphericity2(); }
  /// Event plane angle
  float eventPlaneAngle() const { return mEventPlaneAngle; }
  /// Event plane angle
  float EventPlaneAngle() const { return eventPlaneAngle(); }
  /// Event plane resolution
  float eventPlaneResolution() const { return mEventPlaneResolution; }
  /// Event plane resolution
  float EventPlaneResolution() const { return eventPlaneResolution(); }
  /// Return centrality for 16 bins:
  /// 15 = 0-5%
  /// 14 = 5-10%
  /// 13 = 10-15%
  /// 12 = 15-20%
  /// 11 = 20-25%
  /// 10 = 25-30%
  ///  9 = 30-35%
  ///  8 = 35-40%
  ///  7 = 40-45%
  ///  6 = 45-50%
  ///  5 = 50-55%
  ///  4 = 55-60%
  ///  3 = 60-65%
  ///  2 = 65-70%
  ///  1 = 70-75%
  ///  0 = 75-80%
  short cent16() const { return mCent16; }
  short Cent16() const { return cent16(); }
  /// Return centrality for 9 bins:
  /// 8 = 0-5%
  /// 7 = 5-10%
  /// 6 = 10-20%
  /// 5 = 20-30%
  /// 4 = 30-40%
  /// 3 = 40-50%
  /// 2 = 50-60%
  /// 1 = 60-70%
  /// 0 = 70-80%
  short cent9() const;
  /// Return centrality for 9 bins:
  /// 8 = 0-5%
  /// 7 = 5-10%
  /// 6 = 10-20%
  /// 5 = 20-30%
  /// 4 = 30-40%
  /// 3 = 40-50%
  /// 2 = 50-60%
  /// 1 = 60-70%
  /// 0 = 70-80%
  short Cent9() const           { return cent9(); }
  /// Return impact parameter (form simulation studies only)
  float impactParameter() const { return mImpactPar; }
  /// Return impact parameter (form simulation studies only)
  float ImpactParameter() const { return impactParameter(); }

  /// Primary vertex position
  TVector3 primaryVertex() const
  { return TVector3(mPrimaryVertexPositionX, mPrimaryVertexPositionY, mPrimaryVertexPositionZ); }
  /// Primary vertex position
  TVector3 PrimaryVertex() const { return primaryVertex(); }
  /// z-position estimated by VPD
  float vpdVz() const { return mVpdVz; }
  /// z-position estimated by VPD
  float VpdVz() const { return vpdVz(); }
  /// Return Vz_{TPC}-Vz_{VPD} difference
  float vpdVzDiff() const { return ( primaryVertex().Z() - vpdVz() ); }
  /// Return Vz_{TPC}-Vz_{VPD} difference
  float VpdVzDiff() const { return vpdVzDiff(); }
  /// Return primary vertex ranking. FemtoDst encoding:
  /// -10 = x < -10e9
  ///  -9 = -10e9 <= x < -10e6
  ///  -8 = -10e6 <= x < -10e3;
  ///  -7 = -10e3 <= x < -10e2
  ///  -6 = -10e2 <= x < -10
  ///  -5 = -10 <= x < -5
  ///  -4 = -5 <= x < -4
  ///  -3 = -4 <= x < -3
  ///  -2 = -3 <= x < -2
  ///  -1 = -2 <= x < -1
  ///   0 = -1 <= x < 1
  ///   1 = 1 <= x < 2
  ///   2 = 2 <= x < 3
  ///   3 = 3 <= x < 4
  ///   4 = 4 <= x < 5
  ///   5 = 5 <= x < 10
  ///   6 = 10 <= x < 10e2
  ///   7 = 10e2 <= x < 10e3
  ///   8 = 10e3 <= x < 10e6
  ///   9 = 10e6 <= x < 10e9
  ///  10 = 10e9 <= x
  float ranking() const { return mRanking; }
  float Ranking() const { return ranking(); }
  /// Return list of trigger IDs
  std::vector<unsigned int> triggerIds() const { return mTriggerIds; }
  /// Return list of trigger IDs
  std::vector<unsigned int> TriggerIds() const { return triggerIds(); }
  /// Return if trigger ID is in the list
  bool isTrigger(const unsigned int& word) const;
  /// Return if trigger ID is in the list
  bool IsTrigger(const unsigned int& word) const { return isTrigger(word); }

  /// Return track collection associated with the current event
  StHbtTrackCollection *trackCollection() const { return mTrackCollection; }
  /// Return track collection associated with the current event
  StHbtTrackCollection *TrackCollection() const { return trackCollection(); }
  /// Return v0 collection associated with the current event
  StHbtV0Collection *v0Collection() const { return mV0Collection; }
  /// Return v0 collection associated with the current event
  StHbtV0Collection *V0Collection() const { return v0Collection(); }
  /// Return xi collection associated with the current event
  StHbtXiCollection *xiCollection() const { return mXiCollection; }
  /// Return xi collection associated with the current event
  StHbtXiCollection *XiCollection() const { return xiCollection(); }
  /// Return kink collection associated with the current event
  StHbtKinkCollection *kinkCollection() const { return mKinkCollection; }
  /// Return kink collection associated with the current event
  StHbtKinkCollection *KinkCollection() const { return kinkCollection(); }

  //
  // Setters
  //

  /// Set event number
  void setEventNumber(const unsigned int& id) { mEventNumber = id; }
  /// Set event number
  void SetEventNumber(const unsigned int& id) { setEventNumber(id); }
  /// Set event number
  void setEventId(const unsigned int& id) { mEventNumber = id; }
  /// Set event number
  void SetEventId(const unsigned int& id) { setEventId(id); }
  /// Set run number
  void setRunNumber(const unsigned int& n) { mRunNumber = n; }
  /// Set run number
  void SetRunNumber(const unsigned int& n) { setRunNumber(n); }
  /// Set magnetic field magnitude
  void setMagneticField(const float& bField) { mMagneticField = bField; }
  /// Set magnetic field magnitude
  void SetMagneticField(const float& bField) { setMagneticField(bField); }
  /// Set magnetic field magnitude
  void setBField(const float& bField) { mMagneticField = bField; }
  /// Set magnetic field magnitude
  void SetBField(const float& bField) { setBField(bField); }
  /// Set reference multiplicity
  void setRefMult(const int& mult)
  { mRefMult = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                              std::numeric_limits<unsigned short>::max() :
                              (unsigned short)mult ) : 0 ); }
  /// Set reference multiplicity
  void SetRefMult(const int& mult) { setRefMult(mult); }
  /// Set reference multiplicity of positive tracks
  void setRefMultPos(const int& mult)
  { mRefMultPos = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                 std::numeric_limits<unsigned short>::max() :
                                 (unsigned short)mult ) : 0 ); }
  /// Set reference multiplicity of positive tracks
  void SetRefMultPos(const int& mult) { setRefMultPos(mult); }
  /// Set reference (2) multiplicity
  void setRefMult2(const int& mult)
  { mRefMult2 = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                               std::numeric_limits<unsigned short>::max() :
                               (unsigned short)mult ) : 0 ); }
  /// Set reference (2) multiplicity
  void SetRefMult2(const int& mult) { setRefMult2(mult); }
  /// Set reference (2) multiplicity of positive tracks
  void setRefMult2Pos(const int& mult)
  { mRefMult2Pos = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set reference (2) multiplicity of positive tracks
  void SetRefMult2Pos(const int& mult) { setRefMult2Pos(mult); }
  /// Set corrected reference multiplicity
  void setRefMultCorr(const float& mult)
  { mRefMultCorr = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set corrected reference multiplicity
  void SetRefMultCorr(const float& mult) { setRefMultCorr(mult); }
  /// Set weight of the corrected reference multiplicity
  void setRefMultCorrWeight(const float& wgt) { mRefMultCorrWeight = wgt; }
  /// Set weight of the corrected reference multiplicity
  void SetRefMultCorrWeight(const float& wgt) { setRefMultCorrWeight(wgt); }
  /// Set reference multiplicity of global tracks
  void setGRefMult(const int& mult)
  { mGRefMult = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set reference multiplicity of global tracks
  void SetGRefMult(const int& mult) { setGRefMult(mult); }
  /// Set reference multiplicity of positive global tracks
  void setGRefMultPos(const int& mult)
  { mGRefMultPos = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set reference multiplicity of positive global tracks
  void SetGRefMultPos(const int& mult) { setGRefMultPos(mult); }
  /// Set multiplicity of hits in BTof trays
  void setBTofTrayMult(const int& mult)
  { mBTofTrayMultiplicity = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set multiplicity of hits in BTof trays
  void SetBTofTrayMult(const int& mult) { setBTofTrayMult(mult); }
  /// Set number TOF-matched tracks
  void setNumberOfBTofMatched(const int& mult)
  { mNBTOFMatch = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set number TOF-matched tracks
  void SetNumberOfBTofMatched(const int& mult) { setNumberOfBTofMatched(mult); }
  /// Set number of BEMC-matched tracks
  void setNumberOfBEMCMatched(const int& mult)
  { mNBEMCMatch = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set number of BEMC-matched tracks
  void SetNumberOfBEMCMatched(const int& mult){ setNumberOfBEMCMatched(mult); }
  /// Set number of primary tracks
  void setNumberOfPrimaryTracks(const int& mult)
  { mNumberOfPrimaryTracks = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set number of primary tracks
  void SetNumberOfPrimaryTracks(const int& mult) { setNumberOfPrimaryTracks(mult); }
  /// Set number of global tracks
  void setNumberOfGlobalTracks(const int& mult)
  { mNumberOfGlobalTracks = ( (mult>0) ? ( ( mult>std::numeric_limits<unsigned short>::max() ) ?
                                std::numeric_limits<unsigned short>::max() :
                                (unsigned short)mult ) : 0 ); }
  /// Set number of global tracks
  void SetNumberOfGlobalTracks(const int& mult) { setNumberOfGlobalTracks(mult); }
  /// Set ADC of east ZDC
  void setZdcAdcEast(const float& adc)
  { mZdcSumAdcEast = ( (adc>0) ? ( ( adc>std::numeric_limits<unsigned short>::max() ) ?
                                 std::numeric_limits<unsigned short>::max() :
                                 (unsigned short)adc ) : 0 ); }
  /// Set ADC of east ZDC
  void SetZdcAdcEast(const float& adc) { setZdcAdcEast(adc); }
  /// Set ADC of east ZDC
  void setZdcAdcEast(const int& adc)
  { mZdcSumAdcEast = ( (adc>0) ? ( ( adc>std::numeric_limits<unsigned short>::max() ) ?
                                 std::numeric_limits<unsigned short>::max() :
                                 (unsigned short)adc ) : 0 ); }
  /// Set ADC of east ZDC
  void SetZdcAdcEast(const int& adc) { setZdcAdcEast(adc); }

  /// Set ADC of west ZDC
  void setZdcAdcWest(const float& adc)
  { mZdcSumAdcWest = ( (adc>0) ? ( ( adc>std::numeric_limits<unsigned short>::max() ) ?
                                 std::numeric_limits<unsigned short>::max() :
                                 (unsigned short)adc ) : 0 ); }
  /// Set ADC of west ZDC
  void SetZdcAdcWest(const float& adc) { setZdcAdcWest(adc); }
  /// Set ADC of west ZDC
  void setZdcAdcWest(const int& adc)
  { mZdcSumAdcWest = ( (adc>0) ? ( ( adc>std::numeric_limits<unsigned short>::max() ) ?
                                 std::numeric_limits<unsigned short>::max() :
                                 (unsigned short)adc ) : 0 ); }
  /// Set ADC of west ZDC
  void SetZdcAdcWest(const int& adc) { setZdcAdcWest(adc); }

  /// Set ZDC coincidence rate
  void setZdcCoincidenceRate(const float& rt) { mZdcCoincidenceRate = rt; }
  /// Set ZDC coincidence rate
  void SetZdcCoincidenceRate(const float& rt) { setZdcCoincidenceRate(rt); }
  /// Set BBC coincidence rate
  void setBbcCoincidenceRate(const float& rt) { mBbcCoincidenceRate = rt; }
  /// Set BBC coincidence rate
  void SetBbcCoincidenceRate(const float& rt) { setBbcCoincidenceRate(rt); }

  /// Set (transverse) sphericity in |eta|<0.5, pT>0.15, DCA<3 and nHits>10
  void setSphericity(const float& sph);
  /// Set (transverse) sphericity in |eta|<0.5, pT>0.15, DCA<3 and nHits>10
  void SetSphericity(const float& sph) { setSphericity(sph); }
  /// Set (transverse) sphericity in |eta|<1, pT>0.15, DCA<3 and nHits>10
  void setSphericity2(const float& sph);
  /// Set (transverse) sphericity in |eta|<1, pT>0.15, DCA<3 and nHits>10
  void SetSphericity2(const float& sph) { setSphericity2(sph); }

  /// Set event plane anagle
  void setEventPlaneAngle(const float& angle) { mEventPlaneAngle = angle; }
  /// Set event plane anagle
  void SetEventPlaneAngle(const float& angle) { setEventPlaneAngle(angle); }
  /// Set event plane ange resolution
  void setEventPlaneResolution(const float& res) { mEventPlaneResolution = res; }
  /// Set event plane ange resolution
  void SetEventPlaneResolution(const float& res) { setEventPlaneResolution(res); }
  /// Set centrality bin
  void setCent16(const int& cent) { mCent16 = cent; }
  /// Set centrality bin
  void SetCent16(const int& cent) { setCent16(cent); }

  /// Set primary vertex position using (x,y,z)
  void setPrimaryVertex(const float& x, const float& y, const float& z)
  { mPrimaryVertexPositionX = x; mPrimaryVertexPositionY = y; mPrimaryVertexPositionZ = z; }
  /// Set primary vertex (x,y,z)
  void SetPrimaryVertex(const float& x, const float& y, const float& z)
  { setPrimaryVertex(x, y, z); }
  /// Set primary vertex position using TVector3
  void setPrimaryVertex(const TVector3& pvtx)
  { mPrimaryVertexPositionX = pvtx.X(); mPrimaryVertexPositionY = pvtx.Y(); mPrimaryVertexPositionZ = pvtx.Z(); }
  /// Set x-position of primary vertex
  void setPrimaryVertexX(const float& x) { mPrimaryVertexPositionX = x; }
  /// Set x-position of primary vertex
  void SetPrimaryVertexX(const float& x) { setPrimaryVertexX(x); }
  /// Set y-position of primary vertex
  void setPrimaryVertexY(const float& y) { mPrimaryVertexPositionX = y; }
  /// Set y-position of primary vertex
  void SetPrimaryVertexY(const float& y) { setPrimaryVertexY(y); }
  /// Set z-position of primary vertex
  void setPrimaryVertexZ(const float& z) { mPrimaryVertexPositionX = z; }
  /// Set z-position of primary vertex
  void SetPrimaryVertexZ(const float& z) { setPrimaryVertexZ(z); }
  /// Set z-position estimated by EPD
  void setVpdVz(const float& vpdVz) { mVpdVz = vpdVz; }
  /// Set z-position estimated by EPD
  void SetVpdVz(const float& vpdVz) { setVpdVz(vpdVz); }
  /// Set primary vertex ranking
  void setRanking(const float& ranking) { mRanking = ranking; }
  /// Set primary vertex ranking
  void SetRanking(const float& ranking) { setRanking(ranking); }
  /// Set impact parameter (for simulation studies only)
  void setImpactParameter(const float& val) { mImpactPar = val; }
  /// Set impact parameter (for simulation studies only)
  void SetImpactParameter(const float& val) { setImpactParameter(val); }
  

  /// Set trigger IDs using STL vector
  void setTriggerIds(const std::vector<unsigned int>& ids) { mTriggerIds = ids; }
  /// Set trigger IDs using STL vector
  void SetTriggerIds(const std::vector<unsigned int>& ids) { setTriggerIds(ids); }
  /// trigger ID to the list of triggers
  void addTriggerId(const unsigned int& id);
  /// Add trigger ID to the list of triggers
  void AddTriggerId(const unsigned int& id) { addTriggerId(id); }

 private:

  /// Event number (ID)
  unsigned int mEventNumber;								
  /// Run number (ID)
  unsigned int mRunNumber;
  /// Magnetic field strength
  float mMagneticField;

  /// Reference multiplicity (|eta|<0.5)
  unsigned short mRefMult;
  /// Reference multiplicity of positive tracks (|eta|<0.5)
  unsigned short mRefMultPos;
  /// Corrected reference multiplicity (from StRefMultCorr)
  unsigned short mRefMultCorr;
  /// Weight of corrected reference multiplicity (from StRefMultCorr)
  unsigned short mRefMultCorrWeight;									
  /// Reference multiplicity (|eta|<1)
  unsigned short mRefMult2;											
  /// Reference multiplicity of positive tracks (|eta|<1)
  unsigned short mRefMult2Pos;										
  /// Reference multiplicity (|eta|<0.5) of global tracks
  unsigned short mGRefMult;											
  /// Reference multiplicity (|eta|<0.5) of positive global tracks
  unsigned short mGRefMultPos;										
  /// Number of hits int TOF trays
  unsigned short mBTofTrayMultiplicity;
  /// Number of TOF-matched tracks
  unsigned short mNBTOFMatch;
  /// Number of BEMC-matched tracks
  unsigned short mNBEMCMatch;											
  /// Number of primary tracks
  unsigned short mNumberOfPrimaryTracks;
  /// Number of global tracks
  unsigned short mNumberOfGlobalTracks;									

  /// Sum of ADC for east ZDC
  unsigned short mZdcSumAdcEast;
  /// Sum of ADC for west ZDC
  unsigned short mZdcSumAdcWest;
  /// ZDC coincidence rate
  float mZdcCoincidenceRate;											
  /// BBC coincidence rate
  float mBbcCoincidenceRate;											

  /// (Transverse) sphericity by tracks in |eta|<0.5
  float mSphericity;
  /// (Transverse) sphericity by tracks in |eta|<1
  float mSphericity2;												
  /// Event plane angle
  float mEventPlaneAngle;											
  /// Event plane resolution
  float mEventPlaneResolution;										
  /// 16 centrality bins:
  /// 15 = 0-5%
  /// 14 = 5-10%
  /// 13 = 10-15%
  /// 12 = 15-20%
  /// 11 = 20-25%
  /// 10 = 25-30%
  ///  9 = 30-35%
  ///  8 = 35-40%
  ///  7 = 40-45%
  ///  6 = 45-50%
  ///  5 = 50-55%
  ///  4 = 55-60%
  ///  3 = 60-65%
  ///  2 = 65-70%
  ///  1 = 70-75%
  ///  0 = 75-80%
  char  mCent16;//

  /// X position of the primary vertex
  float mPrimaryVertexPositionX;
  /// Y position of the primary vertex
  float mPrimaryVertexPositionY;
  /// Z position of the primary vertex
  float mPrimaryVertexPositionZ;
  /// Z position of primary vertex estimated by VPD
  float mVpdVz;
  /// Primary vertex ranking
  float mRanking;
  /// Float impact parameter (for simulation studies only)
  float mImpactPar;
  
  /// List of trigger IDs (STL vector)
  std::vector<unsigned int> mTriggerIds;

  /// Pointer to the track collection
  StHbtTrackCollection *mTrackCollection;
  /// Pointer to the v0 collection
  StHbtV0Collection *mV0Collection;									
  /// Pointer to the xi collection
  StHbtXiCollection *mXiCollection;									
  /// Pointer to the kink collection
  StHbtKinkCollection *mKinkCollection;									

#ifdef __ROOT__
ClassDef(StHbtEvent,1)
#endif
};

#endif // StHbtEvent_h
