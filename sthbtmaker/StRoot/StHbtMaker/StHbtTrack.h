/**
 * \class StHbtTrack
 * \brief Main class holding track information
 *
 * StHbtTrack holds all the necessary information about a track that is
 * required during femtoscopic analysis. This class is filled with information
 * from the input stream by the reader. A particle has a link back to the Track
 * it was created from, so we do not copy the information.
 */

#ifndef StHbtTrack_h
#define StHbtTrack_h

// C++ headers
#include <cmath>
#include <limits>

// StHbtMaker headers
// Base
#include "StHbtHiddenInfo.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtPhysicalHelix.h"

// ROOT headers
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"

//_________________
class StHbtTrack {

 public:
  /// Constructor
  StHbtTrack();
  /// Copy constructor
  StHbtTrack(const StHbtTrack& track);
  /// Copy constructor
  StHbtTrack& operator=(const StHbtTrack& track);
  /// Destructor
  virtual ~StHbtTrack();

  //
  // Getters
  //

  /// ID of the track
  unsigned short id() const { return mId; }
  /// ID of the track
  unsigned short Id() const { return id(); }
  /// Particle type: 1-primary, 0-global
  short type() const { return ( isPrimary() ) ? 1 : 0; }
  /// Particle type: 1-primary, 0-global
  short Type() const { return type(); }
  /// Return true if track is primary, false if not
  bool isPrimary() const { return ( pMom().Mag()>0 ) ? true : false; }
  /// Return true if track is primary, false if not
  bool IsPrimary() const { return isPrimary(); }
  /// Track charge
  short charge() const { return ( mNHits>0) ? 1 : -1; }
  /// Track charge
  short Charge() const { return charge(); }
  /// Track flag (redundant)
  unsigned short flag() const { return mFlag; }
  /// Track flag (redundant)
  unsigned short Flag() const { return flag(); }
  /// Number of hits
  unsigned short nHits() const { return (unsigned short)TMath::Abs(mNHits); }
  /// Number of hits
  unsigned short NHits() const { return nHits(); }
  /// Number of hits
  unsigned short numberOfHits() const { return nHits(); }
  /// Number of fitted points
  unsigned short nHitsFit() const { return nHits(); }
  /// Number of fitted points
  unsigned short NHitsFit() const { return nHits(); }
  /// Number of possible points
  unsigned short nHitsPossible() const { return (unsigned short)mNHitsPoss; }
  /// Number of possible points
  unsigned short nHitsPoss() const { return nHitsPossible(); }
  /// Number of possible points
  unsigned short NHitsPoss() const { return nHitsPossible(); }
  /// Number of possible points
  unsigned short nHitsMax() const { return nHitsPossible(); }
  /// Number of hits used for dE/dx estimation
  unsigned short nHitsDedx() const { return (unsigned short)mNHitsDedx; }
  /// Number of hits used for dE/dx estimation
  unsigned short NHitsDedx() const { return nHitsDedx(); }
  /// Ratio of nHits/nHitsPossible
  float nHitsFit2PossRatio() const { return ( nHitsPossible()>0 ) ? (float)nHits()/nHitsPossible() : 0; }
  /// Ratio of nHits/nHitsPossible
  float NHitsFit2PossRatio() const { return nHitsFit2PossRatio(); }

  /// nSigma(electron) by dE/dx
  float nSigmaElectron() const     { return (float)mNSigmaElectron / 1000.f; }
  /// nSigma(electron) by dE/dx
  float NSigmaElectron() const     { return nSigmaElectron(); }
  /// nSigma(pion) by dE/dx
  float nSigmaPion() const         { return (float)mNSigmaPion / 1000.f; }
  /// nSigma(pion) by dE/dx
  float NSigmaPion() const         { return nSigmaPion(); }
  /// nSigma(kaon) by dE/dx
  float nSigmaKaon() const         { return (float)mNSigmaKaon / 1000.f; }
  /// nSigma(kaon) by dE/dx
  float NSigmaKaon() const         { return nSigmaKaon(); }
  /// nSigma(proton) by dE/dx
  float nSigmaProton() const       { return (float)mNSigmaProton / 1000.f; }
  /// nSigma(proton) by dE/dx
  float NSigmaProton() const       { return nSigmaProton(); }
  /// Probability to be electron
  float pidProbElectron() const    { return (float)mPidProbElectron / 10000.f; }
  /// Probability to be electron
  float PidProbElectron() const    { return pidProbElectron(); }
  /// Probability to be pion
  float pidProbPion() const        { return (float)mPidProbPion / 10000.f; }
  /// Probability to be pion
  float PidProbPion() const        { return pidProbPion(); }
  /// Probability to be kaon
  float pidProbKaon() const        { return (float)mPidProbKaon / 10000.f; }
  /// Probability to be kaon
  float PidProbKaon() const        { return pidProbKaon(); }
  /// Probability to be proton
  float pidProbProton() const      { return (float)mPidProbProton / 10000.f; }
  /// Probability to be proton
  float PidProbProton() const      { return pidProbProton(); }

  /// dE/dx of the track in (GeV/cm)
  double dEdx() const              { return (double)mDedx * 1e-9; }
  /// dE/dx of the track in (GeV/cm)
  double Dedx() const              { return dEdx(); }
  /// dE/dx of the track in (keV/cm)
  double dEdxInKeV() const         { return (double)mDedx * 1e-3; }
  /// dE/dx of the track in (keV/cm)
  double DedxInKeV() const         { return dEdxInKeV(); }
  /// Momentum of the track. Return momentum of the primary track
  /// if track is primary
  TVector3 momentum() const        { return ( isPrimary() ) ? pMom() : gMom(); }
  /// Momentum of the track. Return momentum of the primary track
  /// if track is primary
  TVector3 Momentum() const        { return momentum(); }
  /// Momentum of the track. Return momentum of the primary track
  /// if track is primary
  TVector3 p() const               { return momentum(); }
  /// Momentum of the primary track
  TVector3 pMom() const            { return TVector3(mPrimaryPx, mPrimaryPy, mPrimaryPz); }
  /// Momentum of the track (magnitude). Return momentum of the primary
  /// track if track is primary, and global if not primary
  float ptot() const               { return ( isPrimary() ) ? pMom().Mag() : gPtot(); }
  /// Squared momentum of the track (squared magnitude). Return momentum
  /// of the primary track if track is primary, and global if not primary
  float ptot2() const              { return ( isPrimary() ) ? pMom().Mag2() : gPtot2(); }
  /// Transverse momentum of the track. Return momentum of the primary
  /// track if track is primary, and global if not primary
  float pt() const                 { return ( isPrimary() ) ? pMom().Perp() : gPt(); }
  /// Squared transverse momentum of the track. Return momentum of the primary
  /// track if track is primary, and global if not primary
  float pt2() const                { return ( isPrimary() ) ? pMom().Perp2() : gPt2(); }
  /// Pseudorapidity of the track. Return pseudorapidity of the primary
  /// track if track is primary, and global if not primary
  float eta() const                { return ( isPrimary() ) ? pMom().PseudoRapidity() : gEta(); }
  /// Pseudorapidity of the track. Return pseudorapidity of the primary
  /// track if track is primary, and global if not primary
  float Eta() const                { return eta(); }
  /// Pseudorapidity of the track. Return pseudorapidity of the primary
  /// track if track is primary, and global if not primary
  float pseudoRapidity() const     { return ( isPrimary() ) ? eta() : gEta(); }
  /// Pseudorapidity of the track. Return pseudorapidity of the primary
  /// track if track is primary, and global if not primary
  float PseudoRapidity() const     { return pseudoRapidity(); }
  /// Azimuthal angle of the track. Return azimuthal angle of the primary
  /// track if track is primary, and global if not primary
  float phi() const                { return ( isPrimary() ) ? pMom().Phi() : gPhi(); }
  /// Azimuthal angle of the track. Return azimuthal angle of the primary
  /// track if track is primary, and global if not primary
  float Phi() const                { return phi(); }
  /// Polar angle of the track. Return polar angle of the primary
  /// track if track is primary, and global if not primary
  float theta() const              { return ( isPrimary() ) ? pMom().Theta() : gTheta(); }
  /// Polar angle of the track. Return polar angle of the primary
  /// track if track is primary, and global if not primary
  float Theta() const              { return theta(); }
  /// Momentum of the global track
  TVector3 gMom() const            { return TVector3(mGlobalPx, mGlobalPy, mGlobalPz); }
  /// Momentum of the global track (magnitude)
  float gPtot() const              { return gMom().Mag(); }
  /// Squared momentum of the global track (squared magnitude)
  float gPtot2() const             { return gMom().Mag2(); }
  /// Transverse momentum of the global track
  float gPt() const                { return gMom().Perp(); }
  /// Squared transverse momentum of the global track
  float gPt2() const               { return gMom().Perp2(); }
  /// Pseudorapidity of the global track
  float gEta() const               { return gMom().Eta(); }
  /// Polar angle of the global track
  float gTheta() const             { return gMom().Theta(); }
  /// Azimuthal angle of the global track
  float gPhi() const               { return gMom().Phi(); }
  /// Primary vertex position
  TVector3 primaryVertex() const   { return TVector3(mPrimaryVertexX, mPrimaryVertexY, mPrimaryVertexZ); }
  /// Primary vertex position
  TVector3 PrimaryVertex() const   { return primaryVertex(); }
  /// Origin of the track
  TVector3 origin() const          { return ( primaryVertex()+gDCA() ); }
  /// Origin of the track
  TVector3 Origin() const          { return origin(); }
  /// DCA of the track to the primary vertex
  TVector3 gDCA() const            { return TVector3(mDcaX, mDcaY, mDcaZ); }
  /// DCA of the track to the primary vertex in the transverse plane
  float gDCAxy() const             { return gDCA().Perp(); }
  /// DCA of the track to the primary vertex in z direction
  float gDCAz() const              { return gDCA().Z(); }
  /// chi2 of the track
  float chi2() const               { return (float)mChi2 * 0.001; }
  /// chi2 of the track
  float Chi2() const               { return chi2(); }
  /// Topology map of 2 words
  unsigned int topologyMap(const unsigned int& word) const { return mMap[word]; }
  /// Topology map of 2 words
  unsigned int TopologyMap(const unsigned int& word) const { return topologyMap(word); }
  /// Velocity of the track from TOF
  float beta() const               { return ( isPrimary() && isTofTrack() ) ? (float)mTofBeta / 20000.f : -999; }
  /// Velocity of the track from TOF
  float Beta() const               { return beta(); }
  /// If track has signal in TOF
  bool isTofTrack() const          { return ( mTofBeta<=0 ) ? false : true; }
  /// If track has signal in TOF
  bool IsTofTrack() const          { return isTofTrack(); }
  /// Inversed velocity
  float invBeta() const            { return ( isPrimary() && isTofTrack() ) ? 1./beta() : -999.; }
  /// Inversed velocity
  float InvBeta() const            { return invBeta(); }
  /// Square of inversed velocity
  float invBeta2() const           { return ( isPrimary() && isTofTrack() ) ? invBeta()*invBeta() : -999.; }
  /// Square of inversed velocity
  float InvBeta2() const           { return invBeta2(); }
  /// Squared mass (from TOF)
  float massSqr() const;
  /// Squared mass (from TOF)
  float MassSqr() const            { return massSqr(); }
  /// Return magnetic field (in kilogaus)
  float bField() const             { return mBField; }
  /// 1/beta - 1/beta(e)
  float invBetaDiffElectron() const;
  /// 1/beta - 1/beta(pion)
  float invBetaDiffPion() const;
    /// 1/beta - 1/beta(kaon)
  float invBetaDiffKaon() const;
  /// 1/beta - 1/beta(proton)
  float invBetaDiffProton() const;

  /// Helix of the primary track
  StHbtPhysicalHelix helix() const;
  /// Helix of the primary track
  StHbtPhysicalHelix Helix() const { return helix(); }
  /// Helix of the global track
  StHbtPhysicalHelix gHelix() const;

  //
  // Setters
  //

  /// Set track unique ID
  void setId(const unsigned short& id)   { mId = (unsigned short)id; }
  /// Set track unique ID
  void SetId(const unsigned short& id)   { setId(id); }
  /// Set track flag
  void setFlag(const short& flag)        { mFlag = flag; }
  /// Set track flag
  void SetFlag(const short& flag)        { setFlag(flag); }
  /// Set number of hits. IMPORTANT: must be charge*nHits
  void setNHits(const short& nhits)      { mNHits = (char)nhits; }
  /// Set number of hits. IMPORTANT: must be charge*nHits
  void SetNHits(const short& nhits)      { setNHits(nhits); }
  /// Set number of possible hits
  void setNHitsPossible(const short& nh) { mNHitsPoss = (unsigned char)nh; }
  /// Set number of possible hits
  void SetNHitsPossible(const short& nh) { setNHitsPossible(nh); }
  /// Set number of hits used for dE/dx estimation
  void setNHitsDedx(const short& nh)     { mNHitsDedx = (unsigned char)nh; }
  /// Set number of hits used for dE/dx estimation
  void SetNHitsDedx(const short& nh)     { setNHitsDedx(nh); }
  /// Set chi2 of the track reconstruction
  void setChi2(const float& chi2);
  /// Set chi2 of the track reconstruction
  void SetChi2(const float& chi2)        { setChi2(chi2); }
  /// Set dE/dx (from GeV/cm)
  void setDedx(const double& dEdx);
  /// Set dE/dx (from GeV/cm)
  void SetDedx(const double& dEdx)       { setDedx(dEdx); }
  /// Set dE/dx (from keV/cm)
  void setDedxFromKeV(const double& dEdx);
  /// Set dE/dx (from keV/cm)
  void SetDedxFromKeV(const double& dEdx){ setDedxFromKeV(dEdx); }
  /// Set nSigma(electron)
  void setNSigmaElectron(const float& nsigma);
  /// Set nSigma(electron)
  void SetNSigmaElectron(const float& nsigma) { setNSigmaElectron(nsigma); }
  /// Set nSigma(pion)
  void setNSigmaPion(const float& nsigma);
  /// Set nSigma(pion)
  void SetNSigmaPion(const float& nsigma) { setNSigmaPion(nsigma); }
  /// Set nSigma(kaon)
  void setNSigmaKaon(const float& nsigma);
  /// Set nSigma(kaon)
  void SetNSigmaKaon(const float& nsigma) { setNSigmaKaon(nsigma); }
  /// Set nSigma(proton)
  void setNSigmaProton(const float& nsigma);
  /// Set nSigma(proton)
  void SetNSigmaProton(const float& nsigma){ setNSigmaProton(nsigma); }
  /// Set probability of track to be electron
  void setPidProbElectron(const float& prob);
  /// Set probability of track to be electron
  void SetPidProbElectron(const float& prob){ setPidProbElectron(prob); }
  /// Set probability of track to be pion
  void setPidProbPion(const float& prob);
  /// Set probability of track to be pion
  void SetPidProbPion(const float& prob)    { setPidProbPion(prob); }
  /// Set probability of track to be kaon
  void setPidProbKaon(const float& prob);
  /// Set probability of track to be kaon
  void SetPidProbKaon(const float& prob)    { setPidProbKaon(prob); }
  /// Set probability of track to be proton
  void setPidProbProton(const float& prob);
  /// Set probability of track to be proton
  void SetPidProbProton(const float& prob)  { setPidProbProton(prob); }
  /// Set DCA of the track to primary vertex (x,y,z)
  void setDca(const float& x, const float& y, const float& z) { mDcaX=x; mDcaY=y; mDcaZ=z; }
  /// Set DCA of the track to primary vertex (x,y,z)
  void SetDca(const float& x, const float& y, const float& z) { setDca(x, y, z); }
  /// Set DCAx of the track to primary vertex
  void setDcaX(const float& x)              { mDcaX=x; }
  /// Set DCAx of the track to primary vertex
  void SetDcaX(const float& x)              { setDcaX(x); }
  /// Set DCAy of the track to primary vertex
  void setDcaY(const float& y)              { mDcaY=y; }
  /// Set DCAy of the track to primary vertex
  void SetDcaY(const float& y)              { setDcaY(y); }
  /// Set DCAz of the track to primary vertex
  void setDcaZ(const float& z)              { mDcaZ=z; }
  /// Set DCAz of the track to primary vertex
  void SetDcaZ(const float& z)              { setDcaZ(z); }

  /// Set momentum of the primary track (x,y,z)
  void setP(const float& px, const float& py, const float& pz)
  { mPrimaryPx=px; mPrimaryPy=py; mPrimaryPz=pz; }
  /// Set momentum of the primary track (x,y,z)
  void SetP(const float& px, const float& py, const float& pz)
  { setP(px, py, pz); }
  /// Set momentum of the primary track (TVector3)
  void setP(const TVector3& mom)
  { mPrimaryPx=mom.X(); mPrimaryPy=mom.Y(); mPrimaryPz=mom.Z(); }
  /// Set momentum of the primary track (TVector3)
  void SetP(const TVector3& mom)            { setP(mom); }
  /// Set px of the primary track
  void setPx(const float& px)               { mPrimaryPx=px; }
  /// Set px of the primary track
  void SetPx(const float& px)               { setPx(px); }
  /// Set py of the primary track
  void setPy(const float& py)               { mPrimaryPy=py; }
  /// Set py of the primary track
  void SetPy(const float& py)               { setPy(py); }
  /// Set pz of the primary track
  void setPz(const float& pz)               { mPrimaryPz=pz; }
  /// Set pz of the primary track
  void SetPz(const float& pz)               { setPz(pz); }

  /// Set momentum of the global track (x,y,z)
  void setGlobalP(const float& px, const float& py, const float& pz)
  { mGlobalPx=px; mGlobalPy=py; mGlobalPz=pz; }
  /// Set momentum of the global track (x,y,z)
  void SetGlobalP(const float& px, const float& py, const float& pz)
  { setGlobalP(px, py, pz); }
  /// Set momentum of the global track (TVector3)
  void setGlobalP(const TVector3& mom)
  { mGlobalPx=mom.X(); mGlobalPy=mom.Y(); mGlobalPz=mom.Z(); }
  /// Set momentum of the global track (TVector3)
  void SetGlobalP(const TVector3& mom)       { setGlobalP(mom); }
  /// Set px of the global track
  void setGlobalPx(const float& px)          { mGlobalPx=px; }
  /// Set px of the global track
  void SetGlobalPx(const float& px)          { setGlobalPx(px); }
  /// Set py of the global track
  void setGlobalPy(const float& py)          { mGlobalPy=py; }
  /// Set py of the global track
  void SetGlobalPy(const float& py)          { setGlobalPy(py); }
  /// Set pz of the global track
  void setGlobalPz(const float& pz)          { mGlobalPz=pz; }
  /// Set pz of the global track
  void SetGlobalPz(const float& pz)          { setGlobalPz(pz); }

  /// Set primary vertex position (x,y,z)
  void setPrimaryVertex(const float& x, const float& y, const float& z)
  { mPrimaryVertexX=x; mPrimaryVertexY=y; mPrimaryVertexZ=z; }
  /// Set primary vertex position (x,y,z)
  void SetPrimaryVertex(const float& x, const float& y, const float& z)
  { setPrimaryVertex(x, y, z); }
  /// Set primary vertex position (TVector3)
  void setPrimaryVertex(const TVector3& vtx)
  { mPrimaryVertexX=vtx.X(); mPrimaryVertexY=vtx.Y(); mPrimaryVertexZ=vtx.Z(); }
  /// Set primary vertex position (TVector3)
  void SetPrimaryVertex(const TVector3& vtx)  { setPrimaryVertex(vtx); }
  /// Set x position of the primary vertex
  void setPrimaryVertexX(const float& x)      { mPrimaryVertexX=x; }
  /// Set x position of the primary vertex
  void SetPrimaryVertexX(const float& x)      { setPrimaryVertexX(x); }
  /// Set y position of the primary vertex
  void setPrimaryVertexY(const float& y)      { mPrimaryVertexY=y; }
  /// Set y position of the primary vertex
  void SetPrimaryVertexY(const float& y)      { setPrimaryVertexY(y); }
  /// Set z position of the primary vertex
  void setPrimaryVertexZ(const float& z)      { mPrimaryVertexZ=z; }
  /// Set z position of the primary vertex
  void SetPrimaryVertexZ(const float& z)      { setPrimaryVertexZ(z); }
  /// Set magnetic field strength
  void setMagneticField(const float& bField)  { mBField = bField; }
  /// Set magnetic field strength
  void SetMagneticField(const float& bField)  { setMagneticField(bField); }
  /// Set magnetic field strength
  void setBField(const float& bField)         { setMagneticField(bField); }
  /// Set magnetic field strength
  void SetBField(const float& bField)         { setMagneticField(bField); }
  /// Set topology map (2 words)
  void setTopologyMap(const int word, const unsigned int map)
  { mMap[word] = map; }
  /// Set topology map (2 words)
  void SetTopologyMap(const int word, const unsigned int map)
  { setTopologyMap(word, map); }
  /// Set velocity (from TOF)
  void setBeta(const float &beta);
  /// Set velocity (from TOF)
  void SetBeta(const float &beta)              { setBeta(beta); }


  // Theoretical information that should be created and coppied manually

  /// Set hidden information
  void setHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { mHiddenInfo = aHiddenInfo; }
  /// Set hidden information
  void SetHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { setHiddenInfo(aHiddenInfo); }
  /// If hidden info is valid
  bool validHiddenInfo() const { return (mHiddenInfo) ? true : false; }
  /// If hidden info is valid
  bool ValidHiddenInfo() const { return validHiddenInfo(); }
  /// Retrieve hidden info
  StHbtHiddenInfo* getHiddenInfo() const { return mHiddenInfo; }
  /// Retrieve hidden info
  StHbtHiddenInfo* hiddenInfo() const { return getHiddenInfo(); }
  /// Retrieve hidden info
  StHbtHiddenInfo* GetHiddenInfo() const { return getHiddenInfo(); }

 private:

  /// Unique track ID
  unsigned short mId;
  /// Flag (redundant)
  short mFlag;
  /// Number of hits and charge (encoding: nHits*charge)
  char  mNHits;
  /// Number of possible hits
  unsigned char mNHitsPoss;
  /// Number of hits used for dE/dx estimation
  unsigned char mNHitsDedx;
  /// Chi2 of the track reconstruction (compression factor = *1000)
  unsigned short mChi2;
  /// Ionization energy loss (in eV/cm) (compression factor = *10^9)
  unsigned short mDedx;

  /// Number of sigma for electron estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNSigmaElectron;
  /// Number of sigma for pion estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNSigmaPion;
  /// Number of sigma for kaon estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNSigmaKaon;
  /// Number of sigma for proton estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNSigmaProton;
  /// Probability of the track to be electron
  /// (compression factor = *10000)
  unsigned short mPidProbElectron;
  /// Probability of the track to be pion
  /// (compression factor = *10000)
  unsigned short mPidProbPion;
  /// Probability of the track to be kaon
  /// (compression factor = *10000)
  unsigned short mPidProbKaon;
  /// Probability of the track to be proton
  /// (compression factor = *10000)
  unsigned short mPidProbProton;

  /// Topology map
  unsigned int mMap[2];

  /// Time-of-Flight information. 0 correseponds
  /// to the absence of the signal (compression = *20000)
  unsigned short mTofBeta;

  /// px of the primary track momentum (0 -  if not primary)
  float mPrimaryPx;
  /// py of the primary track momentum (0 -  if not primary)
  float mPrimaryPy;
  /// pz of the primary track momentum (0 -  if not primary)
  float mPrimaryPz;
  /// px of global track at DCA to primary vertex
  float mGlobalPx;
  /// py of global track at DCA to primary vertex
  float mGlobalPy;
  /// pz of global track at DCA to primary vertex
  float mGlobalPz;


  
  /// DCAx of the global track to primary vertex (cm)
  float mDcaX;
  /// DCAy of the global track to primary vertex (cm)
  float mDcaY;
  /// DCAz of the global track to primary vertex (cm)
  float mDcaZ;

  // Primary vertex position ( dca2pvtx = trackOrigin - vertexPosition )

  /// x position of the primary vertex
  float mPrimaryVertexX;
  /// y position of the primary vertex
  float mPrimaryVertexY;
  /// z position of the primary vertex
  float mPrimaryVertexZ;
  /// Magnetic field strength (needed for helix esitmation)
  float mBField;

  /// Hidden info (to work with MC data)
  StHbtHiddenInfo* mHiddenInfo; //!

#ifdef __ROOT__
  ClassDef(StHbtTrack, 2)
#endif
};

#endif // #define StHbtTrack_h
