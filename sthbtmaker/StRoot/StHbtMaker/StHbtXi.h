/**
 * \class StHbtXi
 * \brief Main class holding xi information
 *
 * StHbtXi holds all the necessary information about a xi
 */

#ifndef StHbtXi_h
#define StHbtXi_h

// StHbtMaker headers
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "phys_constants.h"

// ROOT headers
#include "TVector3.h"
#include "TMath.h"

//_________________
class StHbtXi : public StHbtV0 {

 public:
  /// Default constructor
  StHbtXi();
  /// Copy constructor
  StHbtXi(const StHbtXi& copy);
  /// Copy constructor
  StHbtXi& operator=(const StHbtXi& copy);
  /// Default destructor
  virtual ~StHbtXi();

  //
  // Getters
  //

  /// Charge of Xi
  short chargeXi() const             { return (mCharge) ? 1 : -1; }
  /// Vector from the primary vertex to the decay point of Xi
  TVector3 decayVectorXi() const
  { return (mBachelor) ? ( decayVertexXi() - primaryVertex() ) : TVector3(0.,0.,0.); }
  float decayLengthXi() const        { return decayVectorXi().Mag(); }
  /// Xi decay vertex position
  TVector3 decayPointXi() const      { return decayVertexXi(); }
  TVector3 decayVertexXi() const     { return TVector3( mDecayVertexXiX, mDecayVertexXiY, mDecayVertexXiZ ); }
  float decayVertexXiX() const       { return decayVertexXi().X(); }
  float decayVertexXiY() const       { return decayVertexXi().Y(); }
  float decayVertexXiZ() const       { return decayVertexXi().Z(); }
  /// DCA of Xi daughters at decay vertex
  float dcaXiDaughters() const       { return mDcaXiDaughters; }
  /// DCA of xi to primary vertex
  float dcaXiToPrimVertex() const    { return mDcaXiToPrimVertex; }
  /// Reconstructed Xi momentum
  TVector3 momXi() const             { return TVector3( mMomXiX, mMomXiY, mMomXiZ ); }
  float momXiX() const               { return momXi().X(); }
  float momXiY() const               { return momXi().Y(); }
  float momXiZ() const               { return momXi().Z(); }
  /// Transverse momentum of Xi
  float ptXi() const                 { return momXi().Perp(); }
  /// Total momentum of Xi
  float ptotXi() const               { return momXi().Mag(); }
  float ptot2Xi() const              { return momXi().Mag2(); }
  float etaXi() const                { return momXi().PseudoRapidity(); }
  float pseudoRapXi() const          { return etaXi(); }
  float phiXi() const                { return momXi().Phi(); }
  /// Rapidity assuming (anti) Xi
  float rapXi() const                { return 0.5 * TMath::Log( ( eXi()+momXiZ() ) / ( eXi()-momXiZ() ) ); }
  /// Rapidity assuming (anti) Omega
  float rapOmega() const             { return 0.5 * TMath::Log( ( eOmega()+momXiZ() ) / ( eOmega()-momXiZ() ) ); }
  /// Armenteros-Podolanski parameters
  float alphaXi() const              { return alphaArmXi(); }
  float alphaArmXi() const;
  float ptArmXi() const;
  /// Energy assuming Xi hypothesis
  float eXi() const                  { return TMath::Sqrt( momXi().Mag2() + M_XI_MINUS*M_XI_MINUS); }
  /// Energy assuming Omega hypothesis
  float eOmega() const               { return TMath::Sqrt( momXi().Mag2() + M_OMEGA_MINUS*M_OMEGA_MINUS); }
  /// Mass assuming (anti) Xi hypothesis
  float massXi() const
  { return TMath::Sqrt( TMath::Power( (eBacPion()+eLambda()), 2 ) + ptot2Xi() ); }
  /// Mass assuming (anti) Omega hypothesis
  float massOmega() const
  { return TMath::Sqrt( TMath::Power( (eBacKaon()+eLambda()), 2 ) + ptot2Xi() ); }
  /// Lifetime (ctau) const assuming (anti) Xi
  float cTauXi() const               { return M_XI_MINUS * decayLengthXi() / ptotXi(); }
  /// Lifetime (ctau) const assuming (anti) Omega
  float cTauOmega() const            { return M_OMEGA_MINUS * decayLengthXi() / ptotXi(); }
  float chi2Xi() const               { return (float)mChi2Xi / 10; }
  float clXi() const                 { return mClXi; }

  /// Bachelor information
  StHbtTrack *bachelor() const       { return (mBachelor) ? mBachelor : nullptr; }
  TVector3 primaryVertex() const     { return (mBachelor) ? mBachelor->primaryVertex() : TVector3(0,0,0); }
  TVector3 momBac() const
  { return ( (mBachelor) ?
	     TVector3( mMomBacAtDca2DecayPointX, mMomBacAtDca2DecayPointY, mMomBacAtDca2DecayPointX ) :
	     TVector3(0,0,0) ); }
  float momBacX() const              { return momBac().X(); }
  float momBacY() const              { return momBac().Y(); }
  float momBacZ() const              { return momBac().Z(); }
  float momBacPt() const             { return momBac().Perp(); }
  float ptBac() const                { return momBac().Perp(); }
  float momBacPtot() const           { return momBac().Mag(); }
  float ptotBac() const              { return momBac().Mag(); }
  float ptot2Bac() const             { return momBac().Mag2(); }
  unsigned int trackTopologyMapBac(const int& i) { return (mBachelor) ? mBachelor->topologyMap(i) : 0; }
  unsigned short nHitsBac() const    { return (mBachelor) ? mBachelor->nHits() : 0; }
  unsigned short tpcHitsBac() const  { return nHitsBac(); }
  short chargeBac() const            { return (mBachelor) ? mBachelor->charge() : 0; }
  double dEdxBac() const             { return (mBachelor) ? mBachelor->dEdx() : -1.e-9; }
  unsigned short idBac() const       { return (mBachelor) ? mBachelor->id() : 0; }
  unsigned short keyBac() const      { return idBac(); }
  float dcaBacToPrimVertex() const   { return (mBachelor) ? mBachelor->gDCA().Mag() : 999.f; }
  float eBacKaon() const
  { return (mBachelor) ? TMath::Sqrt( ptot2Bac() + M_KAON_PLUS*M_KAON_PLUS ) : 0; }
  float eBacPion() const
  { return (mBachelor) ? TMath::Sqrt( ptot2Bac() + M_PION_PLUS*M_PION_PLUS ) : 0; }

  void  updateXi();

  //
  // Setters
  //

  void setChargeXi(const int& charge)           { mCharge = (charge>0) ? true : false; }
  void setDecayVertexXi(const float& x, const float& y, const float& z)
  { mDecayVertexXiX = x; mDecayVertexXiY = y; mDecayVertexXiZ = z; }
  void setDecayVertexXiX(const float& x)        { mDecayVertexXiX = x; }
  void setDecayVertexXiY(const float& y)        { mDecayVertexXiX = y; }
  void setDecayVertexXiZ(const float& z)        { mDecayVertexXiX = z; }
  void setDecayVertexXi(const TVector3& vec)
  { mDecayVertexXiX = vec.X(); mDecayVertexXiY = vec.Y(); mDecayVertexXiZ = vec.Z(); }
  void setChi2Xi(const float& chi2);
  void setConfidenceLeveXi(const float& cl)     { mClXi = cl; }

  void setDcaXiDaughters(const float& dca)      { mDcaXiDaughters = dca; }
  void setDcaXiToPrimVertex(const float& dca)   { mDcaXiToPrimVertex = dca; }
  void setMomXiX(const float& px)               { mMomXiX = px; }
  void setMomXiY(const float& py)               { mMomXiY = py; }
  void setMomXiZ(const float& pz)               { mMomXiZ = pz; }
  void setMomXi(const float& px, const float& py, const float& pz)
  { mMomXiX = px; mMomXiY = py; mMomXiZ = pz; }
  void setMomXi(const TVector3& p)              { mMomXiX = p.X(); mMomXiY = p.Y(); mMomXiZ = p.Z(); }
  void setBachelor(StHbtTrack* bachelor)        { mBachelor = (bachelor) ? bachelor : nullptr; }
  void setMomAtDecayPointBac(const float& px, const float& py, const float& pz)
  { mMomBacAtDca2DecayPointX = px; mMomBacAtDca2DecayPointY = py; mMomBacAtDca2DecayPointZ = pz; }
  void setMomAtDecayPointBac(const TVector3& p)
  { mMomBacAtDca2DecayPointX = p.X(); mMomBacAtDca2DecayPointY = p.Y(); mMomBacAtDca2DecayPointZ = p.Z(); }
  void setMomAtDecayPointBacX(const float& px)  { mMomBacAtDca2DecayPointX = px; }
  void setMomAtDecayPointBacY(const float& py)  { mMomBacAtDca2DecayPointY = py; }
  void setMomAtDecayPointBacZ(const float& pz)  { mMomBacAtDca2DecayPointZ = pz; }

 protected:

  // Xi information

  /// Charge: true - positive, false - negative
  bool  mCharge;
  /// Xi decay point
  float mDecayVertexXiX;
  float mDecayVertexXiY;
  float mDecayVertexXiZ;
  /// DCA between V0 and bachelor
  float mDcaXiDaughters;
  /// DCA of Xi to the  primary vertex
  float mDcaXiToPrimVertex;
  /// The following variables are not in the persistent version
  /// and can be calculated via updateXi();
  float mMomXiX;
  float mMomXiY;
  float mMomXiZ;
  /// Fit quality for Xi ( compression = *10)
  unsigned char mChi2Xi;
  /// Confidence level for Xi
  float mClXi;

  // Bachelor information

  StHbtTrack *mBachelor;
  float mMomBacAtDca2DecayPointX;
  float mMomBacAtDca2DecayPointY;
  float mMomBacAtDca2DecayPointZ;

#ifdef __ROOT__
  ClassDef(StHbtXi, 1)
#endif
};

#endif // #define StHbtXi_h
