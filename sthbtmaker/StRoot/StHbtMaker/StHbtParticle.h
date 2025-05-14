/**
 * \class StHbtParticle
 * \brief Main class holding particle information
 *
 * StHbtParticle holds all the necessary information about a particle
 */

#ifndef StHbtParticle_h
#define StHbtParticle_h

// StHbtMaker headers
// Base
#include "StHbtHiddenInfo.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "StHbtKink.h"
#include "StHbtXi.h"
#include "StHbtPhysicalHelix.h"

// ROOT headers
#include "TLorentzVector.h"
#include "TVector3.h"

//_________________
class StHbtParticle {

 public:
  /// Default constructor
  StHbtParticle();
  /// Copy constructor
  StHbtParticle(const StHbtParticle &copy);
  /// Constructor for StHbtTrack
  StHbtParticle(const StHbtTrack* const hbtTrack, const double& mass);
  /// Constructor for StHbtV0
  StHbtParticle(const StHbtV0* const hbtV0, const double& mass);
  /// Constructor for StHbtKink
  StHbtParticle(const StHbtKink* const hbtKink, const double& mass);
  /// Constructor for StHbtXi
  StHbtParticle(const StHbtXi* const hbtXi, const double& mass);
  /// Assignment operator
  StHbtParticle& operator=(const StHbtParticle& copy);
  /// Default destructor
  virtual ~StHbtParticle();

  /// Radius of the inner TPC (cm)
  static float mInnerTpcRadius;
  /// Radius of the outer TPC (cm)
  static float mOuterTpcRadius;
  /// Half length of the TPC
  static float mTpcHalfLength;   //[cm]
  /// Number of points where perform calculations
  static const unsigned short mNumberOfPoints = 11;
  /// Total number of padrows in super sector
  static const unsigned short mNumberOfPadrows = 45;
  /// Radius at each padrow
  static float tRowRadius[mNumberOfPadrows];

  //
  // Getters
  //


  // Track information //


  /// Return pointer to track
  StHbtTrack *track() const                { return mTrack; }
  /// Return pointer to V0
  StHbtV0    *v0() const                   { return mV0; }
  /// Return pointer to kink
  StHbtKink  *kink() const                 { return mKink; }
  /// Return pointer to xi
  StHbtXi    *xi() const                   { return mXi; }
  /// Four-momentum of particle
  TLorentzVector fourMomentum() const      { return TLorentzVector( mPx, mPy, mPz, mEnergy ); }
  /// Pseudorapidity of particle
  double      eta() const                  { return fourMomentum().Eta(); }
  /// Pseudorapidity of particle
  double      pseudoRapidity()             { return eta(); }
  /// Rapidity of particle
  double      rapidity()                   { return fourMomentum().Rapidity(); }
  /// Azimuthal angle of particle
  double      phi() const                  { return fourMomentum().Phi(); }
  /// Three-momentum of particle
  TVector3    momentum() const             { return fourMomentum().Vect(); }
  /// Three-momentum of particle
  TVector3    p() const                    { return momentum(); }
  /// Px of particle
  double      px() const                   { return momentum().X(); }
  /// Py of particle
  double      py() const                   { return momentum().Y(); }
  /// Pz of particle
  double      pz() const                   { return momentum().Z(); }
  /// Momentum magnitude of particle
  double      ptot() const                 { return momentum().Mag(); }
  /// Momentum magnitude squared of particle
  double      ptot2() const                { return momentum().Mag2(); }
  /// Transverse momentum of particle
  double      pt() const                   { return momentum().Perp(); }
  /// Energy of particle
  double      energy() const               { return fourMomentum().Energy(); }
  /// Energy of particle
  double      e() const                    { return energy(); }
  /// Energy of particle
  double      t() const                    { return fourMomentum().T(); }
  /// Energy squared of particle
  double      energy2() const              { return ( energy() * energy() ); }

  /// Primary vertex position
  TVector3 primaryVertex() const
  { return TVector3( mPrimaryVertexX, mPrimaryVertexY, mPrimaryVertexZ ); }

  /// Helix of the track
  StHbtPhysicalHelix helix() const         { return mTrack ? mTrack->helix() : StHbtPhysicalHelix(); }
  /// Topology map of the track
  unsigned int topologyMap(const unsigned int& word) const { return mTrack ? mTrack->topologyMap(word) : 0; }
  /// Number of hits of the track
  unsigned short nHits() const             { return mTrack ? mTrack->nHits() : 0; }
  /// Number of hits of the track
  unsigned short numberOfHits() const      { return nHits(); }
  /// Track unique ID
  unsigned short trackId() const           { return mTrack ? mTrack->id() : -1; }
  /// Position of track exit TPC points assuming start it at (0,0,0)
  TVector3 nominalTpcExitPoint() const
  { return TVector3( mTpcTrackExitPointX, mTpcTrackExitPointY, mTpcTrackExitPointZ ); }
  /// Position of track entrance TPC points assuming start it at (0,0,0)
  TVector3 nominalTpcEntrancePoint() const
  { return TVector3( mTpcTrackEntrancePointX, mTpcTrackEntrancePointY, mTpcTrackEntrancePointZ ); }
  /// Information about track position x at mNumberOfPoints points in TPC
  const float *nominalPosSampleX() const   { return &mNominalPosSampleX[0]; }
  /// Information about track position y at mNumberOfPoints points in TPC
  const float *nominalPosSampleY() const   { return &mNominalPosSampleY[0]; }
  /// Information about track position z at mNumberOfPoints points in TPC
  const float *nominalPosSampleZ() const   { return &mNominalPosSampleZ[0]; }
  /// Position x at i-th radius
  float nominalPosSampleX(const int& point) const;
  /// Position y at i-th radius
  float nominalPosSampleY(const int& point) const;
  /// Position z at i-th radius
  float nominalPosSampleZ(const int& point) const;
  /// Position at i-th radius
  TVector3 nominalPosSample(const int& i) const;
  /// Information about hit position in TPC local coordinate system
  float *z()                    { return &mZ[0]; }
  /// Information about hit position in TPC local coordinate system
  float *u()                    { return &mU[0]; }
  /// Information about hit position in TPC local coordinate system
  int *sect()                   { return &mSect[0]; }

  /// Purity estimations
  void   calculatePurity();
  /// Pion purity
  double pionPurity();
  /// Kaon purity
  double kaonPurity();
  /// Proton purity
  double protonPurity();


  // StHbtV0 information //

  /// Decay point of V0
  TVector3 secondaryVertex() const
  { return TVector3( secondaryVertexX() , secondaryVertexY(), secondaryVertexZ() ); }
  /// x position of V0 decay
  float    secondaryVertexX() const;
  /// y position of V0 decay
  float    secondaryVertexY() const;
  /// z position of V0 decay
  float    secondaryVertexZ() const;
  /// Decay point of V0
  TVector3 decayVertexPosition() const     { return secondaryVertex(); }
  /// Unique ID of negative daugther
  unsigned short negTrackId() const        { return mV0->idNeg(); }
  /// Unique ID of positive daugther
  unsigned short posTrackId() const        { return mV0->idPos(); }
  /// Position of the exit point of positive daughter
  TVector3 tpcV0PosExitPoint() const
  { return TVector3( tpcV0PosExitPointX(), tpcV0PosExitPointY(), tpcV0PosExitPointZ() ); }
  /// x position of the exit point of positive daughter
  float    tpcV0PosExitPointX() const;
  /// y position of the exit point of positive daughter
  float    tpcV0PosExitPointY() const;
  /// z position of the exit point of positive daughter
  float    tpcV0PosExitPointZ() const;
  /// Position of the entrance point of positive daughter
  TVector3 tpcV0PosEntrancePoint() const
  { return TVector3( tpcV0PosEntrancePointX(), tpcV0PosEntrancePointY(), tpcV0PosEntrancePointZ() ); }
  /// x position of the entrance point of positive daughter
  float    tpcV0PosEntrancePointX() const;
  /// y position of the entrance point of positive daughter
  float    tpcV0PosEntrancePointY() const;
  /// z position of the entrance point of positive daughter
  float    tpcV0PosEntrancePointZ() const;
  /// Position of the exit point of negative daughter
  TVector3 tpcV0NegExitPoint() const
  { return TVector3( tpcV0NegExitPointX(), tpcV0NegExitPointY(), tpcV0NegExitPointZ() ); }
  /// x position of the exit point of negative daughter
  float    tpcV0NegExitPointX() const;
  /// y position of the exit point of negative daughter
  float    tpcV0NegExitPointY() const;
  /// z position of the exit point of negative daughter
  float    tpcV0NegExitPointZ() const;
  /// Position of the entrance point of negative daughter
  TVector3 tpcV0NegEntrancePoint() const
  { return TVector3( tpcV0NegEntrancePointX(), tpcV0NegEntrancePointY(), tpcV0NegEntrancePointZ() ); }
  /// x position of the entrance point of negative daughter
  float    tpcV0NegEntrancePointX() const;
  /// y position of the entrance point of negative daughter
  float    tpcV0NegEntrancePointY() const;
  /// z position of the entrance point of negative daughter
  float    tpcV0NegEntrancePointZ() const;

  /// x position of the negative daughter of V0
  const float *tpcV0NegPosSampleX() const   { return (mTpcV0NegPosSampleX) ? &mTpcV0NegPosSampleX[0] : nullptr; }
  /// y position of the negative daughter of V0
  const float *tpcV0NegPosSampleY() const   { return (mTpcV0NegPosSampleY) ? &mTpcV0NegPosSampleY[0] : nullptr; }
  /// z position of the negative daughter of V0
  const float *tpcV0NegPosSampleZ() const   { return (mTpcV0NegPosSampleZ) ? &mTpcV0NegPosSampleZ[0] : nullptr; }
  /// x position of the negative daughter of V0 at i-th point
  float tpcV0NegPosSampleX(const int& point) const;
  /// y position of the negative daughter of V0 at i-th point
  float tpcV0NegPosSampleY(const int& point) const;
  /// z position of the negative daughter of V0 at i-th point
  float tpcV0NegPosSampleZ(const int& point) const;
  /// Position of the negative daugther
  TVector3 tpcV0NegPosSample(const int& i) const;
  /// Info about hit positions in the local coordinate system (for V0 only)
  float *v0NegZ()  { return (mV0NegZ) ? &mV0NegZ[0] : nullptr; }
  /// Info about hit positions in the local coordinate system (for V0 only)
  float *v0NegU()  { return (mV0NegU) ? &mV0NegU[0] : nullptr; }
  /// Info about hit positions in the local coordinate system (for V0 only)
  int *v0NegSect() { return (mV0NegSect) ? &mV0NegSect[0] : nullptr;}

  /// The following method is for explicit internal calculation to fill datamembers.
  /// It is invoked automatically if StHbtParticle constructed from StHbtTrack
  void calculateTpcExitAndEntrancePoints( StHbtPhysicalHelix *tHelix,
                              					  TVector3 *PrimVert,
                              					  TVector3 *SecVert,
                              					  TVector3 *tmpTpcEntrancePoint,
                              					  TVector3 *tmpTpcExitPoint,
                              					  TVector3 *tmpPosSample,
                              					  float    *tmpZ,
                              					  float    *tmpU,
                              					  int      *tmpSect );

  //
  // Setters
  //

  /// Reset four-momentum
  void resetFourMomentum(const TLorentzVector& vec)
  { mPx = vec.Px(); mPy = vec.Py(); mPz = vec.Pz(); mEnergy = vec.E(); }
  /// Set primary vertex position
  void setPrimaryVertex(const TVector3& pvtx)
  { mPrimaryVertexX = pvtx.X(); mPrimaryVertexY = pvtx.Y(); mPrimaryVertexZ = pvtx.Z(); }
  /// Set position of track exit TPC point assuming start it at (0,0,0)
  void setNominalTpcExitPoint(const TVector3& point)
  { mTpcTrackExitPointX = point.X(); mTpcTrackExitPointY = point.Y(); mTpcTrackExitPointZ = point.Z(); }
  /// Set position of track entrance TPC point assuming start it at (0,0,0)
  void setNominalTpcEntrancePoint(const TVector3& point)
  { mTpcTrackEntrancePointX = point.X(); mTpcTrackEntrancePointY = point.Y(); mTpcTrackEntrancePointZ = point.Z(); }

  /// Set three-coordinate of decay point
  void setSecondaryVertex(const TVector3& vtx)
  { setSecondaryVertexX( vtx.X() ); setSecondaryVertexY( vtx.Y() ); setSecondaryVertexZ( vtx.Z() ); }
  /// Set x-coordinate of decay point
  void setSecondaryVertexX(const float& val);
  /// Set y-coordinate of decay point
  void setSecondaryVertexY(const float& val);
  /// Set z-coordinate of decay point
  void setSecondaryVertexZ(const float& val);
  /// Set decay point based on V0 information
  void setSecondaryVertex(StHbtV0 *v0)
  {
    setSecondaryVertexX( v0->decayPoint().X() );
    setSecondaryVertexY( v0->decayPoint().Y() );
    setSecondaryVertexZ( v0->decayPoint().Z() );
  }
  /// Set decay point
  void setDecayPoint(const TVector3& vtx) { setSecondaryVertex( vtx ); }
  /// Set decay point
  void setDecayPoint(StHbtV0 *v0)         { setSecondaryVertex( v0 ); }

  /// Set exit point of positive daughter of V0
  void setTpcV0PosExitPoint(const TVector3& vec)
  {
    setTpcV0PosExitPointX( vec.X() );
    setTpcV0PosExitPointY( vec.Y() );
    setTpcV0PosExitPointZ( vec.Z() );
  }
  /// Set exit x position of positive daughter of V0
  void setTpcV0PosExitPointX(const float& val);
  /// Set exit y position of positive daughter of V0
  void setTpcV0PosExitPointY(const float& val);
  /// Set exit z position of positive daughter of V0
  void setTpcV0PosExitPointZ(const float& val);
  /// Set entrance point of positive daughter of V0
  void setTpcV0PosEntrancePoint(const TVector3& vec)
  {
    setTpcV0PosEntrancePointX( vec.X() );
    setTpcV0PosEntrancePointY( vec.Y() );
    setTpcV0PosEntrancePointZ( vec.Z() );
  }
  /// Set entrance x position of positive daughter of V0
  void setTpcV0PosEntrancePointX(const float& val);
  /// Set entrance y position of positive daughter of V0
  void setTpcV0PosEntrancePointY(const float& val);
  /// Set entrance z position of positive daughter of V0
  void setTpcV0PosEntrancePointZ(const float& val);

  /// Set exit point of negative daughter of V0
  void setTpcV0NegExitPoint(const TVector3& vec)
  {
    setTpcV0NegExitPointX( vec.X() );
    setTpcV0NegExitPointY( vec.Y() );
    setTpcV0NegExitPointZ( vec.Z() );
  }
  /// Set exit x position of negative daughter of V0
  void setTpcV0NegExitPointX(const float& val);
  /// Set exit y position of negative daughter of V0
  void setTpcV0NegExitPointY(const float& val);
  /// Set exit z position of negative daughter of V0
  void setTpcV0NegExitPointZ(const float& val);
  /// Set entrance point of negative daughter of V0
  void setTpcV0NegEntrancePoint(const TVector3& vec)
  {
    setTpcV0NegEntrancePointX( vec.X() );
    setTpcV0NegEntrancePointY( vec.Y() );
    setTpcV0NegEntrancePointZ( vec.Z() );
  }
  /// Set entrance x position of negative daughter of V0
  void setTpcV0NegEntrancePointX(const float& val);
  /// Set entrance y position of negative daughter of V0
  void setTpcV0NegEntrancePointY(const float& val);
  /// Set entrance z position of negative daughter of V0
  void setTpcV0NegEntrancePointZ(const float& val);


  /// Set track positions at mNumberOfPoints points in TPC (x,y,z)
  void setNominalPosSample(float x[mNumberOfPoints], float y[mNumberOfPoints], float z[mNumberOfPoints]);
  /// Set track positions at mNumberOfPoints points in TPC (TVector3)
  void setNominalPosSample(TVector3 pos[mNumberOfPoints]);
  /// Set track x positions at i-th point in TPC
  void setNominalPosSampleX(const int& i, const float& val);
  /// Set track y positions at i-th point in TPC
  void setNominalPosSampleY(const int& i, const float& val);
  /// Set track z positions at i-th point points in TPC
  void setNominalPosSampleZ(const int& i, const float& val);
  /// Set track x positions at mNumberOfPoints points in TPC
  void setNominalPosSampleX(float x[mNumberOfPoints]);
  /// Set track y positions at mNumberOfPoints points in TPC
  void setNominalPosSampleY(float y[mNumberOfPoints]);
  /// Set track z positions at mNumberOfPoints points in TPC
  void setNominalPosSampleZ(float z[mNumberOfPoints]);

  /// Set V0 negative daughter positions at mNumberOfPoints points in TPC (x,y,z)
  void setTpcV0NegPosSample(float x[mNumberOfPoints], float y[mNumberOfPoints], float z[mNumberOfPoints]);
  /// Set V0 negative daughter positions at mNumberOfPoints points in TPC (TVector3)
  void setTpcV0NegPosSample(TVector3 vec[mNumberOfPoints]);
  /// Set V0 negative daughter x positions at mNumberOfPoints points in TPC
  void setTpcV0NegPosSampleX(float x[mNumberOfPoints]);
  /// Set V0 negative daughter y positions at mNumberOfPoints points in TPC
  void setTpcV0NegPosSampleY(float y[mNumberOfPoints]);
  /// Set V0 negative daughter z positions at mNumberOfPoints points in TPC
  void setTpcV0NegPosSampleZ(float z[mNumberOfPoints]);
  /// Set V0 negative daughter x positions at i-th point in TPC
  void setTpcV0NegPosSampleX(const int& i, const float& val);
  /// Set V0 negative daughter y positions at i-th point in TPC
  void setTpcV0NegPosSampleY(const int& i, const float& val);
  /// Set V0 negative daughter z positions at i-th point in TPC
  void setTpcV0NegPosSampleZ(const int& i, const float& val);

  /// Set information about hit positions in TPC local coordinate system
  void setZ(float z[mNumberOfPadrows]);
  /// Set information about hit positions in TPC local coordinate system
  void setU(float u[mNumberOfPadrows]);
  /// Set information about hit positions in TPC local coordinate system
  void setSect(int sector[mNumberOfPadrows]);

  /// Set information about hit positions in TPC local coordinate system
  void setV0NegZ(float z[mNumberOfPadrows]);
  /// Set information about hit positions in TPC local coordinate system
  void setV0NegU(float u[mNumberOfPadrows]);
  /// Set information about hit positions in TPC local coordinate system
  void setV0NegSect(int sect[mNumberOfPadrows]);

  /// Retrieve hidden information
  StHbtHiddenInfo*  hiddenInfo() const             { return mHiddenInfo; }
  /// Retrieve hidden information
  StHbtHiddenInfo*  getHiddenInfo() const          { return hiddenInfo(); }
  /// Check if hidden information is valid
  bool validHiddenInfo() const                     { return (mHiddenInfo) ? true : false; }
  /// Set hidden information
  void setHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { mHiddenInfo = aHiddenInfo->clone(); }

 private:

  /// Pointer to StHbtTrack
  StHbtTrack *mTrack;
  /// Pointer to StHbtV0
  StHbtV0    *mV0;
  /// Pointer to StHbtKink
  StHbtKink  *mKink;
  /// Pointer to StHbtXi
  StHbtXi    *mXi;

  /// Px of the particle
  float mPx;
  /// Py of the particle
  float mPy;
  /// Pz of the particle
  float mPz;
  /// Energy of the particle
  float mEnergy;
  /// x position of TPC entrance point
  float mTpcTrackEntrancePointX;
  /// y position of TPC entrance point
  float mTpcTrackEntrancePointY;
  /// z position of TPC entrance point
  float mTpcTrackEntrancePointZ;
  /// x position of TPC exit point
  float mTpcTrackExitPointX;
  /// y position of TPC exit point
  float mTpcTrackExitPointY;
  /// z position of TPC exit point
  float mTpcTrackExitPointZ;

  /// Calculated track x positions at each of mNumberOfPoints
  float mNominalPosSampleX[mNumberOfPoints];
  /// Calculated track y positions at each of mNumberOfPoints
  float mNominalPosSampleY[mNumberOfPoints];
  /// Calculated track z positions at each of mNumberOfPoints
  float mNominalPosSampleZ[mNumberOfPoints];

  // Next are the pointers (placeholders) for positions
  // of the negative V0 daughter track at mNumberOfPoints
  // in TPC. We will use *new* operator when the default or
  // StHbtV0 constructors are called. For positive V0 daughters
  // we will use existing mNominalPosSample arrays

  /// Calculated V0 negative daughter x positions at each of mNumberOfPoints
  float *mTpcV0NegPosSampleX;
  /// Calculated V0 negative daughter y positions at each of mNumberOfPoints
  float *mTpcV0NegPosSampleY;
  /// Calculated V0 negative daughter z positions at each of mNumberOfPoints
  float *mTpcV0NegPosSampleZ;

  /// Spacial hit positions at each padrow of mNumberOfPadrows in TPC local coordinate system
  float mZ[mNumberOfPadrows];
  /// Spacial hit positions at each padrow of mNumberOfPadrows in TPC local coordinate system
  float mU[mNumberOfPadrows];
  /// Spacial hit positions at each padrow of mNumberOfPadrows in TPC local coordinate system
  int   mSect[mNumberOfPadrows];

  // Next are the pointers (placeholders) for hit positions
  // of the negative V0 daughter track at each padrow of mNumberOfPadrows
  // at in TPC local coordinate system. We will use *new* operator
  // when the default or StHbtV0 constructors are called.
  // For positive V0 daughters we will use existing
  // mZ,mU and mSect arrays

  /// Spacial hit positions at each padrow of mNumberOfPadrows in TPC
  /// local coordinate system of V0 negative daughter
  float *mV0NegZ;
  /// Spacial hit positions at each padrow of mNumberOfPadrows in TPC
  /// local coordinate system of V0 negative daughter
  float *mV0NegU;
  /// Spacial hit positions at each padrow of mNumberOfPadrows in TPC
  /// local coordinate system of V0 negative daughter
  int   *mV0NegSect;

  /// Hidden information for simulated data
  StHbtHiddenInfo* mHiddenInfo;

  /// Purity parametrization parameters
  float mPurity[6];
  static float mPrimPimPar0;
  static float mPrimPimPar1;
  static float mPrimPimPar2;
  static float mPrimPipPar0;
  static float mPrimPipPar1;
  static float mPrimPipPar2;
  static float mPrimPmPar0;
  static float mPrimPmPar1;
  static float mPrimPmPar2;
  static float mPrimPpPar0;
  static float mPrimPpPar1;
  static float mPrimPpPar2;

  /// Primary vertex x position
  float mPrimaryVertexX;
  /// Primary vertex y position
  float mPrimaryVertexY;
  /// Primary vertex z position
  float mPrimaryVertexZ;

  // To save the memory lets use pointers for next variables

  /// Secondary vertex x position (V0 decay point)
  float *mSecondaryVertexX;
  /// Secondary vertex y position (V0 decay point)
  float *mSecondaryVertexY;
  /// Secondary vertex z position (V0 decay point)
  float *mSecondaryVertexZ;

  // Helices of positive and negative V0 dauthers can
  // be returned from the StHbtTrack information
  // Thus, for V0 daugthers we store only calculated TpcEntrance/ExitPoints

  /// X position of TPC entrance point of V0 positive daughter
  float *mTpcV0PosEntrancePointX;
  /// Y position of TPC entrance point of V0 positive daughter
  float *mTpcV0PosEntrancePointY;
  /// Z position of TPC entrance point of V0 positive daughter
  float *mTpcV0PosEntrancePointZ;
  /// X position of TPC exit point of V0 positive daughter
  float *mTpcV0PosExitPointX;
  /// Y position of TPC exit point of V0 positive daughter
  float *mTpcV0PosExitPointY;
  /// Z position of TPC exit point of V0 positive daughter
  float *mTpcV0PosExitPointZ;

  /// X position of TPC entrance point of V0 negative daughter
  float *mTpcV0NegEntrancePointX;
  /// Y position of TPC entrance point of V0 negative daughter
  float *mTpcV0NegEntrancePointY;
  /// Z position of TPC entrance point of V0 negative daughter
  float *mTpcV0NegEntrancePointZ;
  /// X position of TPC exit point of V0 negative daughter
  float *mTpcV0NegExitPointX;
  /// Y position of TPC exit point of V0 negative daughter
  float *mTpcV0NegExitPointY;
  /// Z position of TPC exit point of V0 negative daughter
  float *mTpcV0NegExitPointZ;

#ifdef __ROOT__
  ClassDef(StHbtParticle, 1)
#endif
};

#endif // #define StHbtParticle_h
