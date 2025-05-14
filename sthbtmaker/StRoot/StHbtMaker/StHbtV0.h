/**
 * \class StHbtV0
 * \brief A special type of particle dealing with the V0
 *
 * This class stores the information both about the V0 itself and about its
 * daughters. This easily enables cuts on daughter characteristics.
 */

#ifndef StHbtV0_h
#define StHbtV0_h

// C++ headers
#include <limits>

// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtPhysicalHelix.h"
#include "StHbtHiddenInfo.h"
#include "phys_constants.h"

// ROOT headers
#include "TVector3.h"
#include "TMath.h"

//_________________
class StHbtV0 {

 public:
  /// Constructor
  StHbtV0();
  /// Copy constructor
  StHbtV0(const StHbtV0& copy);
  /// Assignment operator
  StHbtV0& operator=(const StHbtV0& copy);
  /// Destructor
  virtual ~StHbtV0();


  // V0 parameters //


  /// Decay point
  TVector3 decayPoint() const    { return TVector3( mV0DecayPointX, mV0DecayPointY, mV0DecayPointZ ); }
  /// Decay point
  TVector3 DecayPoint() const    { return decayPoint(); }
  /// Decay point
  TVector3 decayVertex() const   { return decayPoint(); }
  /// Primary vertex position
  TVector3 primaryVertex() const { return TVector3( mPrimaryVertexX, mPrimaryVertexY, mPrimaryVertexZ ); }
  /// Primary vertex position
  TVector3 PrimaryVertex() const { return primaryVertex(); }
  /// Magnetic field strength
  float bField() const           { return mBField; }
  /// Magnetic field strength
  float BField() const           { return bField(); }
  /// Magnetic field strength
  float magneticField() const    { return bField(); }
  /// Magnetic field strength
  float MagneticField() const    { return bField(); }
  /// Vector from primary vertex position to the decay point
  TVector3 v0DecayVector() const { return ( decayPoint() - primaryVertex() ); }
  /// Vector from primary vertex position to the decay point
  TVector3 V0DecayVector() const { return v0DecayVector(); }
  /// V0 decay length
  float v0DecayLength() const    { return v0DecayVector().Mag(); }
  /// V0 decay length
  float V0DecayLength() const    { return v0DecayLength(); }
  /// V0 decay length
  float decayLength() const      { return v0DecayLength(); }
  /// V0 decay length
  float DecayLength() const      { return v0DecayLength(); }
  /// Angle between momentum and decay vector
  float v0AndgleBetweenMomentumAndDecayVector() const
  { return TMath::Cos( momV0().Angle( v0DecayVector() ) ); }
  /// Angle between momentum and decay vector
  float V0AndgleBetweenMomentumAndDecayVector() const
  { return v0AndgleBetweenMomentumAndDecayVector(); }
  /// V0 momentum
  TVector3 momV0() const         { return TVector3( mV0MomX, mV0MomY, mV0MomZ); }
  /// V0 momentum
  TVector3 MomV0() const         { return momV0(); }
  /// Px of V0
  float momV0X() const           { return momV0().X(); }
  /// Px of V0
  float MomV0X() const           { return momV0X(); }
  /// Py of V0
  float momV0Y() const           { return momV0().Y(); }
  /// Py of V0
  float MomV0Y() const           { return momV0Y(); }
  /// Pz of V0
  float momV0Z() const           { return momV0().Z(); }
  /// Pz of V0
  float MomV0Z() const           { return momV0Z(); }
  /// Transverse momentum of V0
  float ptV0() const             { return momV0().Perp(); }
  /// Transverse momentum of V0
  float PtV0() const             { return ptV0(); }
  /// Transverse momentum squared of V0
  float pt2V0() const            { return momV0().Perp2(); }
  /// Transverse momentum squared of V0
  float Pt2V0() const            { return pt2V0(); }
  /// Magnitude of the V0 momentum
  float ptotV0() const           { return momV0().Mag(); }
  /// Magnitude of the V0 momentum
  float PtotV0() const           { return ptotV0(); }
  /// Magnitude of the V0 momentum squared
  float ptot2V0() const          { return momV0().Mag2(); }
  /// Magnitude of the V0 momentum squared
  float Ptot2V0() const          { return ptot2V0(); }
  /// Pseudorapidity of V0
  float etaV0() const            { return momV0().PseudoRapidity(); }
  /// Pseudorapidity of V0
  float EtaV0() const            { return etaV0(); }
  /// Pseudorapidity of V0
  float pseudoRapV0() const      { return etaV0(); }
  /// Pseudorapidity of V0
  float PseudoRapV0() const      { return etaV0(); }
  /// Azimuthal angle of V0
  float phiV0() const            { return momV0().Phi(); }
  /// Azimuthal angle of V0
  float PhiV0() const            { return phiV0(); }
  /// Momentum of the V0 positive daughter
  float v0PtotPos() const        { return mV0PtotPos; }
  /// Momentum of the V0 positive daughter
  float V0PtotPos() const        { return v0PtotPos(); }
  /// Momentum of the V0 negative daughter
  float v0PtotNeg() const        { return mV0PtotNeg; }
  /// Alpha of the Podolyanski-Armenteros distribution
  float alphaArmV0() const       { return mAlphaV0; }
  /// Alpha of the Podolyanski-Armenteros distribution
  float AlphaArmV0() const       { return alphaArmV0(); }
  /// pT of the Podolyanski-Armenteros distribution
  float ptArmV0() const          { return mPtArmV0; }
  /// pT of the Podolyanski-Armenteros distribution
  float PtArmV0() const          { return ptArmV0(); }
  /// Energy of the V0 assuming Lambda -> p + pi^- decay
  float eLambda() const          { return TMath::Sqrt(ptot2V0() + M_LAMBDA*M_LAMBDA); }
  /// Energy of the V0 assuming Lambda -> p + pi^- decay
  float ELambda() const          { return eLambda(); }
  /// Energy of the V0 assuming AntiLambda -> anti(p) + pi^+ decay
  float eAntiLambda() const      { return TMath::Sqrt(ptot2V0() + M_LAMBDA*M_LAMBDA); }
  /// Energy of the V0 assuming AntiLambda -> anti(p) + pi^+ decay
  float EAntiLambda() const      { return eAntiLambda(); }
  /// Energy of the V0 assuming K_s^0 -> pi^+ + pi^- decay
  float eK0Short() const         { return TMath::Sqrt(ptot2V0() + M_KAON_0_SHORT*M_KAON_0_SHORT); }
  /// Energy of the V0 assuming K_s^0 -> pi^+ + pi^- decay
  float EK0Short() const         { return eK0Short(); }
  /// Energy of the V0 assuming phi^0 -> K^+ + K^- decay
  float ePhi() const             { return TMath::Sqrt(ptot2V0() + M_PHI*M_PHI); }
  /// Energy of the V0 assuming phi^0 -> K^+ + K^- decay
  float EPhi() const             { return ePhi(); }
  /// Mass of V0 assuming Lambda -> p + pi^- decay
  float massLambda() const
  { return TMath::Sqrt( ( eNegPion() + ePosProton() ) * ( eNegPion() + ePosProton() ) + ptot2V0() ); }
  /// Mass of V0 assuming Lambda -> p + pi^- decay
  float MassLambda() const       { return massLambda(); }
  /// Mass of V0 assuming AntiLambda -> anti(p) + pi^+ decay
  float massAntiLambda() const
  { return TMath::Sqrt( ( ePosPion() + eNegProton() ) * ( ePosPion() + eNegProton() ) + ptot2V0() ); }
  /// Mass of V0 assuming AntiLambda -> anti(p) + pi^+ decay
  float MassAntiLambda() const   { return massAntiLambda(); }
  /// Mass of the V0 assuming K_s^0 -> pi^+ + pi^- decay
  float massK0Short() const
  { return TMath::Sqrt( ( ePosPion() + eNegPion() ) * ( ePosPion() + ePosPion() ) + ptot2V0() ); }
  /// Mass of the V0 assuming K_s^0 -> pi^+ + pi^- decay
  float MassK0Short() const      { return massK0Short(); }
  /// Mass of the V0 assuming phi^0 -> K^+ + K^- decay
  float massPhi() const
  { return TMath::Sqrt( ( ePosKaon() + eNegKaon() ) * ( ePosKaon() + eNegKaon() ) + ptot2V0() ); }
  /// Mass of the V0 assuming phi^0 -> K^+ + K^- decay
  float MassPhi() const          { return massPhi(); }
  /// Mass difference between measured and PDG values
  float dMLambda() const         { return (massLambda() - M_LAMBDA); }
  /// Mass difference between measured and PDG values
  float dMAntiLambda() const     { return (massAntiLambda() - M_LAMBDA); }
  /// Mass difference between measured and PDG values
  float dMK0Short() const        { return (massK0Short() - M_KAON_0_SHORT); }
  /// Mass difference between measured and PDG values
  float dMPhi() const            { return (massPhi() - M_PHI); }
  /// Rapidity of V0 assuming Lambda
  float rapidityLambda() const;
  /// Rapidity of V0 assuming Lambda
  float RapidityLambda() const   { return rapidityLambda(); }
  /// Rapidity of V0 assuming K_s^0
  float rapidityK0Short() const;
  /// Rapidity of V0 assuming K_s^0
  float RapidityK0Short() const  { return rapidityK0Short(); }
  /// Rapidity of V0 assuming phi^0
  float rapidityPhi() const;
  /// Rapidity of V0 assuming phi^0
  float RapidityPhi() const      { return rapidityPhi(); }
  /// Rapidity of V0 assuming Lambda
  float rapLambda() const        { return rapidityLambda(); }
  /// Rapidity of V0 assuming K_s^0
  float rapK0Short() const       { return rapidityK0Short(); }
  /// Rapidity of V0 assuming phi^0
  float rapPhi() const           { return rapidityPhi(); }
  /// ctau for V0 assuming Lambda
  float cTauLambda() const       { return ( M_LAMBDA * v0DecayLength() / ptotV0() ); }
  /// ctau for V0 assuming Lambda
  float CTauLambda() const       { return cTauLambda(); }
  /// ctau for V0 assuming K_s^0
  float cTauK0Short() const      { return ( M_KAON_0_SHORT * v0DecayLength() / ptotV0() ); }
  /// ctau for V0 assuming K_s^0
  float CTauK0Short() const      { return cTauK0Short(); }
  /// ctau for V0 assuming phi^0
  float cTauPhi() const          { return ( M_PHI * v0DecayLength() / ptotV0() ); }
  /// ctau for V0 assuming phi^0
  float CTauPhi() const          { return cTauPhi(); }
  /// Energy of positive track assuming proton
  float ePosProton() const       { return TMath::Sqrt(M_PROTON*M_PROTON + mV0PtotPos*mV0PtotPos); }
  /// Energy of positive track assuming proton
  float EPosProton() const       { return ePosProton(); }
  /// Energy of positive track assuming pion
  float ePosPion() const         { return TMath::Sqrt(M_PION_PLUS*M_PION_PLUS + mV0PtotPos*mV0PtotPos); }
  /// Energy of positive track assuming pion
  float EPosPion() const         { return ePosPion(); }
  /// Energy of positive track assuming kaon
  float ePosKaon() const         { return TMath::Sqrt(M_KAON_PLUS*M_KAON_PLUS + mV0PtotPos*mV0PtotPos); }
  /// Energy of positive track assuming kaon
  float EPosKaon() const         { return ePosKaon(); }
  /// Energy of positive track assuming antiproton
  float eNegProton() const       { return TMath::Sqrt(M_ANTIPROTON *M_ANTIPROTON + mV0PtotNeg*mV0PtotNeg); }
  /// Energy of positive track assuming antiproton
  float ENegProton() const       { return eNegProton(); }
  /// Energy of positive track assuming pion
  float eNegPion() const         { return TMath::Sqrt(M_PION_MINUS*M_PION_MINUS + mV0PtotNeg*mV0PtotNeg); }
  /// Energy of positive track assuming pion
  float ENegPion() const         { return eNegPion(); }
  /// Energy of positive track assuming kaon
  float eNegKaon() const         { return TMath::Sqrt(M_KAON_MINUS*M_KAON_MINUS + mV0PtotNeg*mV0PtotNeg); }
  /// Energy of positive track assuming kaon
  float ENegKaon() const         { return eNegKaon(); }
  /// chi2 of the V0 reconstruction
  float chi2V0() const           { return (float)mChi2V0 / 10.; }
  /// chi2 of the V0 reconstruction
  float Chi2V0() const           { return chi2V0(); }
  /// Confidence level of V0 reconstruction
  float clV0() const             { return mClV0; }
  /// Confidence level of V0 reconstruction
  float ClV0() const             { return clV0(); }

  /// Set primary vertex position (x,y,z)
  void setPrimaryVertex(const float& x, const float& y, const float& z)
  { mPrimaryVertexX = x; mPrimaryVertexY = y; mPrimaryVertexZ = z; }
  /// Set primary vertex position (x,y,z)
  void SetPrimaryVertex(const float& x, const float& y, const float& z)
  { setPrimaryVertex(x, y, z); }
  /// Set primary vertex position (TVector3)
  void setPrimaryVertex(const TVector3& vtx) { setPrimaryVertex( vtx.X(), vtx.Y(), vtx.Z() ); }
  /// Set primary vertex position (TVector3)
  void SetPrimaryVertex(const TVector3& vtx) { setPrimaryVertex( vtx.X(), vtx.Y(), vtx.Z() ); }
  /// Set decay point (x,y,z)
  void setDecayPoint(const float& x, const float& y, const float& z)
  { mV0DecayPointX = x; mV0DecayPointY = y; mV0DecayPointZ = z; }
  /// Set decay point (x,y,z)
  void SetDecayPoint(const float& x, const float& y, const float& z)
  { setDecayPoint(x, y, z); }
  /// Set decay point (TVector3)
  void setDecayPoint(const TVector3& point) { setDecayPoint( point.X(), point.Y(), point.Z() ); }
  /// Set decay point (TVector3)
  void SetDecayPoint(const TVector3& point) { setDecayPoint( point.X(), point.Y(), point.Z() ); }
  /// Set magnetic field strength
  void setBField(const float& field)        { mBField = field; }
  /// Set magnetic field strength
  void SetBField(const float& field)        { setBField(field); }
  /// Set magnetic field strength
  void setMagneticField(const float& field) { setBField( field ); }
  /// Set magnetic field strength
  void SetMagneticField(const float& field) { setBField( field ); }
  /// Set V0 momentum (x,y,z)
  void setV0Mom(const float& px, const float& py, const float& pz)
  { mV0MomX = px; mV0MomY = py; mV0MomZ = pz; }
  /// Set V0 momentum (x,y,z)
  void SetV0Mom(const float& px, const float& py, const float& pz)
  { setV0Mom(px, py, pz); }
  /// Set V0 momentum (TVector3)
  void setV0Mom(const TVector3& mom)        { setV0Mom( mom.X(), mom.Y(), mom.Z() ); }
  /// Set V0 momentum (TVector3)
  void SetV0Mom(const TVector3& mom)        { setV0Mom( mom.X(), mom.Y(), mom.Z() ); }
  /// Set V0 momentum (TVector3)
  void setMomV0(const TVector3& mom)        { setV0Mom( mom ) ; }
  /// Set V0 momentum (TVector3)
  void SetMomV0(const TVector3& mom)        { setV0Mom( mom ) ; }
  /// Set momentum of positive V0 daughter
  void setV0PtotPos(const float& ptot)      { mV0PtotPos = ptot; }
  /// Set momentum of positive V0 daughter
  void SetV0PtotPos(const float& ptot)      { setV0PtotPos(ptot); }
  /// Set momentum of negative V0 daughter
  void setV0PtotNeg(const float& ptot)      { mV0PtotNeg = ptot; }
  /// Set momentum of negative V0 daughter
  void SetV0PtotNeg(const float& ptot)      { setV0PtotNeg(ptot); }
  /// Set DCA between daughters
  void setV0DcaDaughters(const float& dca)  { mV0DcaDaughters = dca; }
  /// Set DCA between daughters
  void SetV0DcaDaughters(const float& dca)  { setV0DcaDaughters(dca); }
  /// Set DCA of V0 to primary vertex
  void setV0Dca2PrimaryVertex(const float& dca) { mV0DcaToPrimVertex = dca; }
  /// Set DCA of V0 to primary vertex
  void SetV0Dca2PrimaryVertex(const float& dca) { setV0Dca2PrimaryVertex(dca); }
  /// Set DCA of V0 to primary vertex
  void setV0DcaToPrimaryVertex(const float& dca) { mV0DcaToPrimVertex = dca; }
  /// Set chi2 of V0 reconstruction
  void setChi2V0(const float& chi2);
  /// Set chi2 of V0 reconstruction
  void SetChi2V0(const float& chi2)         { setChi2V0(chi2); }
  /// Set confidence level of V0 reconstruction
  void setClV0(const float& cl)             { mClV0 = cl; }
  /// Set confidence level of V0 reconstruction
  void SetClV0(const float& cl)             { setClV0(cl); }
  /// Set alpha of Podolyanski-Armenteros
  void setArmAlphaV0(const float& alpha)    { mAlphaV0 = alpha; }
  /// Set alpha of Podolyanski-Armenteros
  void SetArmAlphaV0(const float& alpha)    { setArmAlphaV0(alpha); }
  /// Set pT of Podolyanski-Armenteros
  void setArmPtV0(const float& pt)          { mPtArmV0 = pt; }
  /// Set pT of Podolyanski-Armenteros
  void SetArmPtV0(const float& pt)          { setArmPtV0(pt); }

  /// Recalculate most of V0 parameters using daughter tracks
  /// and primary vertex information
  void updateV0();
  /// Recalculate most of V0 parameters using daughter tracks
  /// and primary vertex information
  void UpdateV0() { updateV0(); }


  // Positive daughter //


  /// Unique ID of the positive daughter
  unsigned short idPos() const   { return mPosId; }
  /// Unique ID of the positive daughter
  unsigned short IdPos() const   { return idPos(); }
  /// Unique ID of the positive daughter
  unsigned short keyPos() const  { return mPosId; }
  /// Unique ID of the positive daughter
  unsigned short KeyPos() const  { return keyPos(); }
  /// Momentum of the positive daughter
  TVector3 momPos() const        { return TVector3( mPosMomX, mPosMomY, mPosMomZ ); }
  /// Momentum of the positive daughter
  TVector3 MomPos() const        { return momPos(); }
  /// Px of the positive daughter
  float momXPos() const          { return momPos().X(); }
  /// Px of the positive daughter
  float MomXPos() const          { return momXPos(); }
  /// Py of the positive daughter
  float momYPos() const          { return momPos().Y(); }
  /// Py of the positive daughter
  float MomYPos() const          { return momYPos(); }
  /// Pz of the positive daughter
  float momZPos() const          { return momPos().Z(); }
  /// Pz of the positive daughter
  float MomZPos() const          { return momZPos(); }
  /// Transverse momentum of positive daughter
  float ptPos() const            { return momPos().Perp(); }
  /// Transverse momentum of positive daughter
  float PtPos() const            { return ptPos(); }
  /// Momentum magnitude of the positive daughter
  float ptotPos() const          { return momPos().Mag(); }
  /// Momentum magnitude of the positive daughter
  float PtotPos() const          { return ptotPos(); }
  /// Momentum squared of the positive daughter
  float ptot2Pos() const         { return momPos().Mag2(); }
  /// Momentum squared of the positive daughter
  float Ptot2Pos() const         { return ptot2Pos(); }
  /// Pseudorapidity of the positive daughter
  float etaPos() const           { return momPos().PseudoRapidity(); }
  /// Pseudorapidity of the positive daughter
  float EtaPos() const           { return etaPos(); }
  /// Pseudorapidity of the positive daughter
  float pseudoRapPos() const     { return etaPos(); }
  /// Pseudorapidity of the positive daughter
  float PseudoRapPos() const     { return etaPos(); }
  /// Azimuthal angel of the positive daughter
  float phiPos() const           { return momPos().Phi(); }
  /// Azimuthal angel of the positive daughter
  float PhiPos() const           { return phiPos(); }
  /// DCA of the positive daughter to primary vertex
  TVector3 dcaPosToPrimVertex() const
  { return TVector3( mPosDca2PrimVertexX, mPosDca2PrimVertexY, mPosDca2PrimVertexZ ); }
  /// DCA of the positive daughter to primary vertex
  TVector3 DcaPosToPrimVertex() const { return dcaPosToPrimVertex(); }
  /// Origin of the positive daughter (point of DCA to primary vertex)
  TVector3 originPos() const          { return ( primaryVertex() + dcaPosToPrimVertex() ); }
  /// Origin of the positive daughter (point of DCA to primary vertex)
  TVector3 OriginPos() const          { return originPos(); }
  /// Number of hits of positive daughter
  unsigned short tpcHitsPos() const   { return nHitsPos(); }
  /// Number of hits of positive daughter
  unsigned short nHitsPos() const     { return (unsigned short)mPosNHits; }
  /// Number of hits of positive daughter
  unsigned short NHitsPos() const     { return nHitsPos(); }
  /// Number of fitted points of positive daughter
  unsigned short nHitsFitPos() const  { return (unsigned short)mPosNHits; }
  /// Number of fitted points of positive daughter
  unsigned short NHitsFitPos() const  { return nHitsFitPos(); }
  /// Possible number of hits of positive track
  unsigned short nHitsPossiblePos() const { return (unsigned short)mPosNHitsPoss; }
  /// Possible number of hits of positive track
  unsigned short NHitsPossiblePos() const { return nHitsPossiblePos(); }
  /// nHitsFit/nHitsPossible of positive track
  float nHitsFitOPossRatioPos() const { return (float)nHitsFitPos()/ nHitsPossiblePos(); }
  /// nHitsFit/nHitsPossible of positive track
  float NHitsFitOPossRatioPos() const { return nHitsFitOPossRatioPos(); }
  /// Number of hits used for dE/dx of positive daughter
  unsigned short nHitsDedxPos() const { return (unsigned short)mPosNHitsDedx; }
  /// Number of hits used for dE/dx of positive daughter
  unsigned short NHitsDedxPos() const { return nHitsDedxPos(); }
  /// Number of hits used for dE/dx of positive daughter
  unsigned short numdedxPos() const   { return nHitsDedxPos(); }
  /// Chi2 of resonstruction of the positive daughter
  float chi2Pos() const               { return (float)mPosChi2 / 10.f; }
  /// Chi2 of resonstruction of the positive daughter
  float Chi2Pos() const               { return chi2Pos(); }
  /// dE/dx of the positive daughter (in GeV/cm)
  float dedxPos() const               { return dEdxPos(); }
  /// dE/dx of the positive daughter (in GeV/cm)
  float dEdxPos() const               { return (float)mPosDedx * 1e-9; }
  /// nSigma(e) of positive daughter
  float nSigmaElectronPos() const     { return (float)mPosNSigmaElectron / 1000.f; }
  /// nSigma(e) of positive daughter
  float NSigmaElectronPos() const     { return nSigmaElectronPos(); }
  /// nSigma(pi) of positive daughter
  float nSigmaPionPos() const         { return (float)mPosNSigmaPion / 1000.f; }
  /// nSigma(pi) of positive daughter
  float NSigmaPionPos() const         { return nSigmaPionPos(); }
  /// nSigma(K) of positive daughter
  float nSigmaKaonPos() const         { return (float)mPosNSigmaKaon / 1000.f; }
  /// nSigma(K) of positive daughter
  float NSigmaKaonPos() const         { return nSigmaKaonPos(); }
  /// nSigma(p) of positive daughter
  float nSigmaProtonPos() const       { return (float)mPosNSigmaProton / 1000.f; }
  /// nSigma(p) of positive daughter
  float NSigmaProtonPos() const       { return nSigmaProtonPos(); }
  /// If positive daughter has signal in TOF
  bool isTofTrackPos() const          { return (mPosTofBeta>0) ? true : false; }
  /// If positive daughter has signal in TOF
  bool IsTofTrackPos() const          { return isTofTrackPos(); }
  /// Velocity of the positive daughter (by TOF)
  float betaPos() const               { return ( isTofTrackPos() ) ? (float)mPosTofBeta / 20000.f : -999.f; }
  /// Velocity of the positive daughter (by TOF)
  float BetaPos() const               { return betaPos(); }
  /// Inversed beta of the positive daughter
  float inverseBetaPos() const        { return ( isTofTrackPos() ) ? 1./betaPos() : -999.f; }
  /// Inversed beta of the positive daughter
  float InverseBetaPos() const        { return inverseBetaPos(); }
  /// Square of inversed beta of the positive daughter
  float inverseBeta2Pos() const       { return ( isTofTrackPos() ) ? 1./ ( betaPos() * betaPos() ) : -999.f; }
  /// Square of inversed beta of the positive daughter
  float InverseBeta2Pos() const       { return inverseBeta2Pos(); }
  /// Squared mass of the positive daughter (by TOF)
  float massSqrPos() const
  { return ( isTofTrackPos() ) ? ( ptot2Pos() * (inverseBeta2Pos() - 1.) ) : -999.f; }
  /// Squared mass of the positive daughter (by TOF)
  float MassSqrPos() const            { return massSqrPos(); }
  /// Topology map of the positive daughter
  unsigned int topologyMapPos(unsigned int& word) const { return mPosTopologyMap[word]; }
  /// Topology map of the positive daughter
  unsigned int TopologyMapPos(unsigned int& word) const { return topologyMapPos(word); }
  /// Topology map of the positive daughter
  unsigned int trackTopologyMapPos(unsigned int& word) const { return topologyMapPos(word); }
  /// Helix of the positive daughter
  StHbtPhysicalHelix helixPos() const;

  /// Set unique ID of the positive daughter
  void setIdPos(const int& id)        { mPosId = (id>0) ? id : 0; }
  /// Set unique ID of the positive daughter
  void SetIdPos(const int& id)        { setIdPos(id); }
  /// Set unique ID of the positive daughter
  void setIdPos(const short& id)      { mPosId = (id>0) ? id : 0; }
  /// Set unique ID of the positive daughter
  void setKeyPos(const int& id)       { mPosId = (id>0) ? id : 0; }
  /// Set unique ID of the positive daughter
  void SetKeyPos(const int& id)       { setKeyPos(id); }
  /// Set unique ID of the positive daughter
  void setKeyPos(const short& id)     { mPosId = (id>0) ? id : 0; }
  /// Set momentum of the positive daughter (x,y,z)
  void setMomPos(const float& px, const float& py, const float& pz)
  { mPosMomX = px; mPosMomY = py; mPosMomZ = pz; }
  /// Set momentum of the positive daughter (x,y,z)
  void SetMomPos(const float& px, const float& py, const float& pz)
  { setMomPos(px, py, pz); }
  /// Set momentum of the positive daughter (TVector3)
  void setMomPos(const TVector3& mom) { setMomPos( mom.X(), mom.Y(), mom.Z() ); }
  /// Set momentum of the positive daughter (TVector3)
  void SetMomPos(const TVector3& mom) { setMomPos(mom); }
  /// Set px of the positive daughter
  void setMomXPos(const float& px)    { mPosMomX = px; }
  /// Set px of the positive daughter
  void SetMomXPos(const float& px)    { setMomXPos(px); }
  /// Set py of the positive daughter
  void setMomYPos(const float& py)    { mPosMomY = py; }
  /// Set py of the positive daughter
  void SetMomYPos(const float& py)    { setMomYPos(py); }
  /// Set pz of the positive daughter
  void setMomZPos(const float& pz)    { mPosMomZ = pz; }
  /// Set pz of the positive daughter
  void SetMomZPos(const float& pz)    { setMomZPos(pz); }
  /// Set DCA of the positive daughter to primary vertex (x,y,z)
  void setDcaGlobalPos(const float& x, const float& y, const float& z)
  { mPosDca2PrimVertexX = x; mPosDca2PrimVertexY = y; mPosDca2PrimVertexZ = z; }
  /// Set DCA of the positive daughter to primary vertex (x,y,z)
  void SetDcaGlobalPos(const float& x, const float& y, const float& z)
  { setDcaGlobalPos(x, y, z); }
  /// Set DCA of the positive daughter to primary vertex (TVector3)
  void setDcaGlobalPos(const TVector3& dca) { setDcaGlobalPos( dca.X(), dca.Y(), dca.Z() ); }
  /// Set DCA of the positive daughter to primary vertex (TVector3)
  void SetDcaGlobalPos(const TVector3& dca) { setDcaGlobalPos( dca.X(), dca.Y(), dca.Z() ); }
  /// Set DCAx of the positive daughter to primary vertex
  void setDcaGlobalXPos(const float& x)     { mPosDca2PrimVertexX = x; }
  /// Set DCAx of the positive daughter to primary vertex
  void SetDcaGlobalXPos(const float& x)     { setDcaGlobalXPos(x); }
  /// Set DCAy of the positive daughter to primary vertex
  void setDcaGlobalYPos(const float& y)     { mPosDca2PrimVertexY = y; }
  /// Set DCAy of the positive daughter to primary vertex
  void SetDcaGlobalYPos(const float& y)     { setDcaGlobalYPos(y); }
  /// Set DCAz of the positive daughter to primary vertex
  void setDcaGlobalZPos(const float& z)     { mPosDca2PrimVertexZ = z; }
  /// Set DCAz of the positive daughter to primary vertex
  void SetDcaGlobalZPos(const float& z)     { setDcaGlobalZPos(z); }
  /// Set number of hits of the positive daughter
  void setNHitsPos(const int& nhits)        { mPosNHits = (nhits>0) ? nhits : 0; }
  /// Set number of hits of the positive daughter
  void SetNHitsPos(const int& nhits)        { setNHitsPos(nhits); }
  /// Set positive number of hits of the positive daughter
  void setNHitsPossiblePos(const int& nhits){ mPosNHitsPoss = (nhits>0) ? nhits : 0; }
  /// Set positive number of hits of the positive daughter
  void SetNHitsPossiblePos(const int& nhits){ setNHitsPossiblePos(nhits); }
  /// Set number of hits used for dE/dx estimation of the positive daughter
  void setNHitsDedxPos(const int& nhits)    { mPosNHitsDedx = (nhits>0) ? nhits : 0; }
  /// Set number of hits used for dE/dx estimation of the positive daughter
  void SetNHitsDedxPos(const int& nhits)    { setNHitsDedxPos(nhits); }
  /// Set topology map of the positive daughter
  void setTopologyMapPos(const int& word, const int& val) { mPosTopologyMap[word] = val; }
  /// Set topology map of the positive daughter
  void SetTopologyMapPos(const int& word, const int& val) { setTopologyMapPos(word, val); }
  /// Set chi2 of reconstruction of the positive daughter
  void setChi2Pos(const float& chi2)
  { mPosChi2 = ( (chi2 * 10) > std::numeric_limits<unsigned char>::max() ?
							   std::numeric_limits<unsigned char>::max() :
							   (unsigned char)TMath::Nint( chi2 * 10.f ) ); }
  /// Set chi2 of reconstruction of the positive daughter
  void SetChi2Pos(const float& chi2)        { setChi2Pos(chi2); }
  /// Set dE/dx of the positive daughter (from GeV/cm)
  void setDedxPos(const double& dEdx)
  { if( dEdx <= 0 ) { mPosDedx = 0; }
    else {
      mPosDedx = ( (dEdx * 1e9) > std::numeric_limits<unsigned short>::max() ?
		   std::numeric_limits<unsigned short>::max() :
		   (unsigned short) (dEdx * 1e9) );
    }
  }
  /// Set dE/dx of the positive daughter (from GeV/cm)
  void SetDedxPos(const double& dEdx)       { setDedxPos(dEdx); }
  /// Set dE/dx of the positive daughter (from keV/cm)
  void setDedxPosInKeV(const double& dEdx)
  { if( dEdx <= 0 ) { mPosDedx = 0; }
    else {
      mPosDedx = ( (dEdx * 1e3) > std::numeric_limits<unsigned short>::max() ?
		   std::numeric_limits<unsigned short>::max() :
		   (unsigned short) (dEdx * 1e3) );
    }
  }
  /// Set dE/dx of the positive daughter (from GeV/cm)
  void SetDedxPosInKeV(const double& dEdx)  { setDedxPosInKeV(dEdx); }
  /// Set nSigma(e) of the positive daughter
  void setNSigmaElectronPos(const float& nsigma);
  /// Set nSigma(e) of the positive daughter
  void SetNSigmaElectronPos(const float& nsigma) { setNSigmaElectronPos(nsigma); }
  /// Set nSigma(pi) of the positive daughter
  void setNSigmaPionPos(const float& nsigma);
  /// Set nSigma(pi) of the positive daughter
  void SetNSigmaPionPos(const float& nsigma)     { setNSigmaPionPos(nsigma); }
  /// Set nSigma(K) of the positive daughter
  void setNSigmaKaonPos(const float& nsigma);
  /// Set nSigma(K) of the positive daughter
  void SetNSigmaKaonPos(const float& nsigma)     { setNSigmaKaonPos(nsigma); }
  /// Set nSigma(p) of the positive daughter
  void setNSigmaProtonPos(const float& nsigma);
  /// Set nSigma(p) of the positive daughter
  void SetNSigmaProtonPos(const float& nsigma)   { setNSigmaProtonPos(nsigma); }
  /// Set velocity of the positive daughter (from TOF)
  void setTofBetaPos(const float& beta);
  /// Set velocity of the positive daughter (from TOF)
  void SetTofBetaPos(const float& beta)          { setTofBetaPos(beta); }


  // Negative daughter //


  /// Unique ID of the negative daughter
  unsigned short idNeg() const   { return mNegId; }
  /// Unique ID of the negative daughter
  unsigned short IdNeg() const   { return idNeg(); }
  /// Unique ID of the negative daughter
  unsigned short keyNeg() const  { return mNegId; }
  /// Unique ID of the negative daughter
  unsigned short KeyNeg() const  { return keyNeg(); }
  /// Momentum of the negative daughter
  TVector3 momNeg() const        { return TVector3( mNegMomX, mNegMomY, mNegMomZ ); }
  /// Momentum of the negative daughter
  TVector3 MomNeg() const        { return momNeg(); }
  /// Px of the negative daughter
  float momXNeg() const          { return momNeg().X(); }
  /// Px of the negative daughter
  float MomXNeg() const          { return momXNeg(); }
  /// Py of the negative daughter
  float momYNeg() const          { return momNeg().Y(); }
  /// Py of the negative daughter
  float MomYNeg() const          { return momYNeg(); }
  /// Pz of the negative daughter
  float momZNeg() const          { return momNeg().Z(); }
  /// Pz of the negative daughter
  float MomZNeg() const          { return momZNeg(); }
  /// Transverse momentum of negative daughter
  float ptNeg() const            { return momNeg().Perp(); }
  /// Transverse momentum of negative daughter
  float PtNeg() const            { return ptNeg(); }
  /// Momentum magnitude of the negative daughter
  float ptotNeg() const          { return momNeg().Mag(); }
  /// Momentum magnitude of the negative daughter
  float PtotNeg() const          { return ptotNeg(); }
  /// Momentum squared of the negative daughter
  float ptot2Neg() const         { return momNeg().Mag2(); }
  /// Momentum squared of the negative daughter
  float Ptot2Neg() const         { return ptot2Neg(); }
  /// Pseudorapidity of the negative daughter
  float etaNeg() const           { return momNeg().PseudoRapidity(); }
  /// Pseudorapidity of the negative daughter
  float EtaNeg() const           { return etaNeg(); }
  /// Pseudorapidity of the negative daughter
  float pseudoRapNeg() const     { return etaNeg(); }
  /// Pseudorapidity of the negative daughter
  float PseudoRapNeg() const     { return etaNeg(); }
  /// Azimuthal angel of the negative daughter
  float phiNeg() const           { return momNeg().Phi(); }
  /// Azimuthal angel of the negative daughter
  float PhiNeg() const           { return phiNeg(); }
  /// DCA of the negative daughter to primary vertex
  TVector3 dcaNegToPrimVertex() const
  { return TVector3( mNegDca2PrimVertexX, mNegDca2PrimVertexY, mNegDca2PrimVertexZ ); }
  /// DCA of the negative daughter to primary vertex
  TVector3 DcaNegToPrimVertex() const { return dcaNegToPrimVertex(); }
  /// Origin of the negative daughter (point of DCA to primary vertex)
  TVector3 originNeg() const          { return ( primaryVertex() + dcaNegToPrimVertex() ); }
  /// Origin of the negative daughter (point of DCA to primary vertex)
  TVector3 OriginNeg() const          { return originNeg(); }
  /// Number of hits of negative daughter
  unsigned short tpcHitsNeg() const   { return nHitsNeg(); }
  /// Number of hits of negative daughter
  unsigned short nHitsNeg() const     { return (unsigned short)mNegNHits; }
  /// Number of hits of negative daughter
  unsigned short NHitsNeg() const     { return nHitsNeg(); }
  /// Number of fitted points of negative daughter
  unsigned short nHitsFitNeg() const  { return (unsigned short)mNegNHits; }
  /// Number of fitted points of negative daughter
  unsigned short NHitsFitNeg() const  { return nHitsFitNeg(); }
  /// Negsible number of hits of negative track
  unsigned short nHitsPossibleNeg() const { return (unsigned short)mNegNHitsPoss; }
  /// Possible number of hits of negative track
  unsigned short NHitsPossibleNeg() const { return nHitsPossibleNeg(); }
  /// nHitsFit/nHitsPossible of negative track
  float nHitsFitOPossRatioNeg() const { return (float)nHitsFitNeg()/ nHitsPossibleNeg(); }
  /// nHitsFit/nHitsPossible of negative track
  float NHitsFitOPossRatioNeg() const { return nHitsFitOPossRatioNeg(); }
  /// Number of hits used for dE/dx of negative daughter
  unsigned short nHitsDedxNeg() const { return (unsigned short)mNegNHitsDedx; }
  /// Number of hits used for dE/dx of negative daughter
  unsigned short NHitsDedxNeg() const { return nHitsDedxNeg(); }
  /// Number of hits used for dE/dx of negative daughter
  unsigned short numdedxNeg() const   { return nHitsDedxNeg(); }
  /// Chi2 of resonstruction of the negative daughter
  float chi2Neg() const               { return (float)mNegChi2 / 10.f; }
  /// Chi2 of resonstruction of the negative daughter
  float Chi2Neg() const               { return chi2Neg(); }
  /// dE/dx of the negative daughter (in GeV/cm)
  float dedxNeg() const               { return dEdxNeg(); }
  /// dE/dx of the negative daughter (in GeV/cm)
  float dEdxNeg() const               { return (float)mNegDedx * 1e-9; }
  /// nSigma(e) of negative daughter
  float nSigmaElectronNeg() const     { return (float)mNegNSigmaElectron / 1000.f; }
  /// nSigma(e) of negative daughter
  float NSigmaElectronNeg() const     { return nSigmaElectronNeg(); }
  /// nSigma(pi) of negative daughter
  float nSigmaPionNeg() const         { return (float)mNegNSigmaPion / 1000.f; }
  /// nSigma(pi) of negative daughter
  float NSigmaPionNeg() const         { return nSigmaPionNeg(); }
  /// nSigma(K) of negative daughter
  float nSigmaKaonNeg() const         { return (float)mNegNSigmaKaon / 1000.f; }
  /// nSigma(K) of negative daughter
  float NSigmaKaonNeg() const         { return nSigmaKaonNeg(); }
  /// nSigma(p) of negative daughter
  float nSigmaProtonNeg() const       { return (float)mNegNSigmaProton / 1000.f; }
  /// nSigma(p) of negative daughter
  float NSigmaProtonNeg() const       { return nSigmaProtonNeg(); }
  /// If negative daughter has signal in TOF
  bool isTofTrackNeg() const          { return (mNegTofBeta>0) ? true : false; }
  /// If negative daughter has signal in TOF
  bool IsTofTrackNeg() const          { return isTofTrackNeg(); }
  /// Velocity of the negative daughter (by TOF)
  float betaNeg() const               { return ( isTofTrackNeg() ) ? (float)mNegTofBeta / 20000.f : -999.f; }
  /// Velocity of the negative daughter (by TOF)
  float BetaNeg() const               { return betaNeg(); }
  /// Inversed beta of the negative daughter
  float inverseBetaNeg() const        { return ( isTofTrackNeg() ) ? 1./betaNeg() : -999.f; }
  /// Inversed beta of the negative daughter
  float InverseBetaNeg() const        { return inverseBetaNeg(); }
  /// Square of inversed beta of the negative daughter
  float inverseBeta2Neg() const       { return ( isTofTrackNeg() ) ? 1./ ( betaNeg() * betaNeg() ) : -999.f; }
  /// Square of inversed beta of the negative daughter
  float InverseBeta2Neg() const       { return inverseBeta2Neg(); }
  /// Squared mass of the negative daughter (by TOF)
  float massSqrNeg() const
  { return ( isTofTrackNeg() ) ? ( ptot2Neg() * (inverseBeta2Neg() - 1.) ) : -999.f; }
  /// Squared mass of the negative daughter (by TOF)
  float MassSqrNeg() const            { return massSqrNeg(); }
  /// Topology map of the negative daughter
  unsigned int topologyMapNeg(unsigned int& word) const { return mNegTopologyMap[word]; }
  /// Topology map of the negative daughter
  unsigned int TopologyMapNeg(unsigned int& word) const { return topologyMapNeg(word); }
  /// Topology map of the negative daughter
  unsigned int trackTopologyMapNeg(unsigned int& word) const { return topologyMapNeg(word); }
  /// Helix of the negative daughter
  StHbtPhysicalHelix helixNeg() const;

  /// Set unique ID of the negative daughter
  void setIdNeg(const int& id)        { mNegId = (id>0) ? id : 0; }
  /// Set unique ID of the negative daughter
  void SetIdNeg(const int& id)        { setIdNeg(id); }
  /// Set unique ID of the negative daughter
  void setIdNeg(const short& id)      { mNegId = (id>0) ? id : 0; }
  /// Set unique ID of the negative daughter
  void setKeyNeg(const int& id)       { mNegId = (id>0) ? id : 0; }
  /// Set unique ID of the negative daughter
  void SetKeyNeg(const int& id)       { setKeyNeg(id); }
  /// Set unique ID of the negative daughter
  void setKeyNeg(const short& id)     { mNegId = (id>0) ? id : 0; }
  /// Set momentum of the negative daughter (x,y,z)
  void setMomNeg(const float& px, const float& py, const float& pz)
  { mNegMomX = px; mNegMomY = py; mNegMomZ = pz; }
  /// Set momentum of the negative daughter (x,y,z)
  void SetMomNeg(const float& px, const float& py, const float& pz)
  { setMomNeg(px, py, pz); }
  /// Set momentum of the negative daughter (TVector3)
  void setMomNeg(const TVector3& mom) { setMomNeg( mom.X(), mom.Y(), mom.Z() ); }
  /// Set momentum of the negative daughter (TVector3)
  void SetMomNeg(const TVector3& mom) { setMomNeg(mom); }
  /// Set px of the negative daughter
  void setMomXNeg(const float& px)    { mNegMomX = px; }
  /// Set px of the negative daughter
  void SetMomXNeg(const float& px)    { setMomXNeg(px); }
  /// Set py of the negative daughter
  void setMomYNeg(const float& py)    { mNegMomY = py; }
  /// Set py of the negative daughter
  void SetMomYNeg(const float& py)    { setMomYNeg(py); }
  /// Set pz of the negative daughter
  void setMomZNeg(const float& pz)    { mNegMomZ = pz; }
  /// Set pz of the negative daughter
  void SetMomZNeg(const float& pz)    { setMomZNeg(pz); }
  /// Set DCA of the negative daughter to primary vertex (x,y,z)
  void setDcaGlobalNeg(const float& x, const float& y, const float& z)
  { mNegDca2PrimVertexX = x; mNegDca2PrimVertexY = y; mNegDca2PrimVertexZ = z; }
  /// Set DCA of the negative daughter to primary vertex (x,y,z)
  void SetDcaGlobalNeg(const float& x, const float& y, const float& z)
  { setDcaGlobalNeg(x, y, z); }
  /// Set DCA of the negative daughter to primary vertex (TVector3)
  void setDcaGlobalNeg(const TVector3& dca) { setDcaGlobalNeg( dca.X(), dca.Y(), dca.Z() ); }
  /// Set DCA of the negative daughter to primary vertex (TVector3)
  void SetDcaGlobalNeg(const TVector3& dca) { setDcaGlobalNeg( dca.X(), dca.Y(), dca.Z() ); }
  /// Set DCAx of the negative daughter to primary vertex
  void setDcaGlobalXNeg(const float& x)     { mNegDca2PrimVertexX = x; }
  /// Set DCAx of the negative daughter to primary vertex
  void SetDcaGlobalXNeg(const float& x)     { setDcaGlobalXNeg(x); }
  /// Set DCAy of the negative daughter to primary vertex
  void setDcaGlobalYNeg(const float& y)     { mNegDca2PrimVertexY = y; }
  /// Set DCAy of the negative daughter to primary vertex
  void SetDcaGlobalYNeg(const float& y)     { setDcaGlobalYNeg(y); }
  /// Set DCAz of the negative daughter to primary vertex
  void setDcaGlobalZNeg(const float& z)     { mNegDca2PrimVertexZ = z; }
  /// Set DCAz of the negative daughter to primary vertex
  void SetDcaGlobalZNeg(const float& z)     { setDcaGlobalZNeg(z); }
  /// Set number of hits of the negative daughter
  void setNHitsNeg(const int& nhits)        { mNegNHits = (nhits>0) ? nhits : 0; }
  /// Set number of hits of the negative daughter
  void SetNHitsNeg(const int& nhits)        { setNHitsNeg(nhits); }
  /// Set possible number of hits of the negative daughter
  void setNHitsPossibleNeg(const int& nhits){ mNegNHitsPoss = (nhits>0) ? nhits : 0; }
  /// Set possible number of hits of the negative daughter
  void SetNHitsPossibleNeg(const int& nhits){ setNHitsPossibleNeg(nhits); }
  /// Set number of hits used for dE/dx estimation of the negative daughter
  void setNHitsDedxNeg(const int& nhits)    { mNegNHitsDedx = (nhits>0) ? nhits : 0; }
  /// Set number of hits used for dE/dx estimation of the negative daughter
  void SetNHitsDedxNeg(const int& nhits)    { setNHitsDedxNeg(nhits); }
  /// Set topology map of the negative daughter
  void setTopologyMapNeg(const int& word, const int& val) { mNegTopologyMap[word] = val; }
  /// Set topology map of the negative daughter
  void SetTopologyMapNeg(const int& word, const int& val) { setTopologyMapNeg(word, val); }
  /// Set chi2 of reconstruction of the negative daughter
  void setChi2Neg(const float& chi2)
  { mNegChi2 = ( (chi2 * 10) > std::numeric_limits<unsigned char>::max() ?
							   std::numeric_limits<unsigned char>::max() :
							   (unsigned char)TMath::Nint( chi2 * 10.f ) ); }
  /// Set chi2 of reconstruction of the negative daughter
  void SetChi2Neg(const float& chi2)        { setChi2Neg(chi2); }
  /// Set dE/dx of the negative daughter (from GeV/cm)
  void setDedxNeg(const double& dEdx)
  { if( dEdx <= 0 ) { mNegDedx = 0; }
    else {
      mNegDedx = ( (dEdx * 1e9) > std::numeric_limits<unsigned short>::max() ?
		   std::numeric_limits<unsigned short>::max() :
		   (unsigned short) (dEdx * 1e9) );
    }
  }
  /// Set dE/dx of the negative daughter (from GeV/cm)
  void SetDedxNeg(const double& dEdx)       { setDedxNeg(dEdx); }
  /// Set dE/dx of the negative daughter (from keV/cm)
  void setDedxNegInKeV(const double& dEdx)
  { if( dEdx <= 0 ) { mNegDedx = 0; }
    else {
      mNegDedx = ( (dEdx * 1e3) > std::numeric_limits<unsigned short>::max() ?
		   std::numeric_limits<unsigned short>::max() :
		   (unsigned short) (dEdx * 1e3) );
    }
  }
  /// Set dE/dx of the negative daughter (from GeV/cm)
  void SetDedxNegInKeV(const double& dEdx)  { setDedxNegInKeV(dEdx); }
  /// Set nSigma(e) of the negative daughter
  void setNSigmaElectronNeg(const float& nsigma);
  /// Set nSigma(e) of the negative daughter
  void SetNSigmaElectronNeg(const float& nsigma) { setNSigmaElectronNeg(nsigma); }
  /// Set nSigma(pi) of the negative daughter
  void setNSigmaPionNeg(const float& nsigma);
  /// Set nSigma(pi) of the negative daughter
  void SetNSigmaPionNeg(const float& nsigma)     { setNSigmaPionNeg(nsigma); }
  /// Set nSigma(K) of the negative daughter
  void setNSigmaKaonNeg(const float& nsigma);
  /// Set nSigma(K) of the negative daughter
  void SetNSigmaKaonNeg(const float& nsigma)     { setNSigmaKaonNeg(nsigma); }
  /// Set nSigma(p) of the negative daughter
  void setNSigmaProtonNeg(const float& nsigma);
  /// Set nSigma(p) of the negative daughter
  void SetNSigmaProtonNeg(const float& nsigma)   { setNSigmaProtonNeg(nsigma); }
  /// Set velocity of the negative daughter (from TOF)
  void setTofBetaNeg(const float& beta);
  /// Set velocity of the negative daughter (from TOF)
  void SetTofBetaNeg(const float& beta)          { setTofBetaNeg(beta); }


  // Th. stuff //

  /// Set hidden information
  void setHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { mHiddenInfo = aHiddenInfo; }
  /// Set hidden information
  void SetHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { setHiddenInfo(aHiddenInfo); }
  /// Check if hidden information is valid
  bool isValidHiddenInfo() const                   { return (mHiddenInfo) ? true : false; }
  /// Check if hidden information is valid
  bool IsValidHiddenInfo() const                   { return isValidHiddenInfo(); }
  /// Check if hidden information is valid
  bool validHiddenInfo() const                     { return isValidHiddenInfo(); }
  /// Retrieve hidden information
  StHbtHiddenInfo* getHiddenInfo() const           { return mHiddenInfo; }
  /// Retrieve hidden information
  StHbtHiddenInfo* GetHiddenInfo() const           { return getHiddenInfo(); }

 protected:

  /// Primary vertex position x
  float mPrimaryVertexX;
  /// Primary vertex position y
  float mPrimaryVertexY;
  /// Primary vertex position z
  float mPrimaryVertexZ;

  /// Magnetic field strength
  float mBField;


  //   V0 parameters   //


  /// Decay point x of V0
  float mV0DecayPointX;
  /// Decay point y of V0
  float mV0DecayPointY;
  /// Decay point z of V0
  float mV0DecayPointZ;

  /// Px of V0
  float mV0MomX;
  /// Py of V0
  float mV0MomY;
  /// Pz of V0
  float mV0MomZ;

  /// Total momentum of positive daughter at decay point
  float mV0PtotPos;
  /// Total momentum of negative daughter at decay point
  float mV0PtotNeg;

  /// Distance between daughters at DCA
  float mV0DcaDaughters;
  /// DCA of V0 to primary vertex
  float mV0DcaToPrimVertex;

  /// Chi2 of the V0 reconstruction (compression *= 10)
  unsigned char mChi2V0;
  /// Confidence level of V0 reconstruction
  float mClV0;
  /// Alpha of V0 Podolyanski-Armenteros
  float mAlphaV0;
  /// pT of V0 Podolyanski-Armenteros
  float mPtArmV0;

  //
  // Important: For daughters we store DCA to primary vertex,
  // momentum of the global track at DCA and the other parameters.
  // this is important, because it provides the ability to recalculate
  // V0 parameters at any time.
  //


  // Positive daughter //


  /// Unique ID of positive daughter
  unsigned short mPosId;
  /// Px of positive daughter at DCA to primary vertex
  float mPosMomX;
  /// Py of positive daughter at DCA to primary vertex
  float mPosMomY;
  /// Pz of positive daughter at DCA to primary vertex
  float mPosMomZ;
  /// DCAx of positive daughter to primary vertex
  float mPosDca2PrimVertexX;
  /// DCAy of positive daughter to primary vertex
  float mPosDca2PrimVertexY;
  /// DCAz of positive daughter to primary vertex
  float mPosDca2PrimVertexZ;

  /// Number of hits of positive daughter
  unsigned char mPosNHits;
  /// Possible number of hits of positive daughter
  unsigned char mPosNHitsPoss;
  /// Number of hits used for dE/dx esitmation of positive daughter
  unsigned char mPosNHitsDedx;
  /// Topology map of positive daughter
  unsigned int mPosTopologyMap[2];

  /// chi2 of the track reconstruction (compression factor *= 10)
  unsigned char mPosChi2;
  /// dEdx of the track (in eV/cm) (compression factor = *10^9)
  unsigned short mPosDedx;

  /// Number of sigma for electron hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mPosNSigmaElectron;
  /// Number of sigma for pion hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mPosNSigmaPion;
  /// Number of sigma for kaon hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mPosNSigmaKaon;
  /// Number of sigma for proton hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mPosNSigmaProton;

  /// Time-of-Flight information. 0 correseponds
  /// to the absence of the signal (compression = *20000)
  unsigned short mPosTofBeta;


  // Negative daughter //


  /// Unique ID of negative daughter
  unsigned short mNegId;
  /// Px of negative daughter at DCA to primary vertex
  float mNegMomX;
  /// Py of negative daughter at DCA to primary vertex
  float mNegMomY;
  /// Pz of negative daughter at DCA to primary vertex
  float mNegMomZ;
  /// DCAx of negative daughter to primary vertex
  float mNegDca2PrimVertexX;
  /// DCAy of negative daughter to primary vertex
  float mNegDca2PrimVertexY;
  /// DCAz of negative daughter to primary vertex
  float mNegDca2PrimVertexZ;

  /// Number of hits of negative daughter
  unsigned char mNegNHits;
  /// Negsible number of hits of negative daughter
  unsigned char mNegNHitsPoss;
  /// Number of hits used for dE/dx esitmation of negative daughter
  unsigned char mNegNHitsDedx;
  /// Topology map of negative daughter
  unsigned int mNegTopologyMap[2];

  /// chi2 of the track reconstruction (compression factor *= 10)
  unsigned char mNegChi2;
  /// dEdx of the track (in eV/cm) (compression factor = *10^9)
  unsigned short mNegDedx;

  /// Number of sigma for electron hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNegNSigmaElectron;
  /// Number of sigma for pion hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNegNSigmaPion;
  /// Number of sigma for kaon hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNegNSigmaKaon;
  /// Number of sigma for proton hypothesis estimated via dE/dx
  /// in TPC (compression factor = *1000)
  short mNegNSigmaProton;

  /// Time-of-Flight information. 0 correseponds
  /// to the absence of the signal (compression = *20000)
  unsigned short mNegTofBeta;

  /// Theoretical information
  mutable StHbtHiddenInfo* mHiddenInfo; //!

#ifdef __ROOT__
  ClassDef(StHbtV0, 1)
#endif
};

#endif // #define StHbtV0_h
