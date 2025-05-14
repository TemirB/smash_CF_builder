/**
 * \class StFemtoKFP
 * \brief Keeps information about V0/Kinks reconstructed via KFParticle
 *
 * The class keeps mass, PDG information about particles
 * and its daughter indexes
 *
 * \author Egor Alpatov, Grigory Nigmatkulov; e-mail: nigmatkulov@gmail.com
 * \date November 20, 2021
 */

#ifndef StFemtoKFP_h
#define StFemtoKFP_h

// ROOT headers
#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TParticle.h"

//________________
class StFemtoKFP : public TObject {

public:
  /// Default costructor
  StFemtoKFP();
  /// Copy constructor
  StFemtoKFP(const StFemtoKFP &kfp);
  /// Destructor 
  virtual ~StFemtoKFP()  { /* empty */ }
  /// Print KFParic information
  void print();

  //
  // Setters
  //

  /// Set Momentum
  void setMom(TVector3 p)   { mMomX = p.X(); mMomY = p.Y(); mMomZ = p.Z(); }
  /// Set Mass
  void setMass(Float_t m)   { mMass = m; }
  /// Set PDG code
  void setPDG(Int_t pdg)    { mPdgCode = pdg; }
  /// Set DaughterIds vector
  void setDaughterIds(std::vector<int> ids) { mDaughterIds = ids; } // positive of KFP, negative for FemtoTrack
  /// Set Chi2/NDF
  void setChi2NDF(Float_t chi2); 
  /// Set decay point
  void setDecayPoint(TVector3 p) { mDecPointX = p.X(); mDecPointY = p.Y(); mDecPointZ = p.Z(); }
  /// Set DCA of KFParticle to primary vertex
  void setDcaKFP2Vertex(Float_t x) { mDcaKFParticle2Vertex = x; }
  /// Set DCA between daughters
  void setDcaBetweenDaughters(Float_t x) { mDcaBetweenDaughters = x; }

  //
  // Getters
  //

  /// Return three-momentum
  TVector3 p() const              { return TVector3(mMomX, mMomY, mMomZ); }
  /// Return three-momentum
  TVector3 momentum() const       { return p(); }
  /// Return total momentum (GeV/c)
  Float_t ptot() const            { return p().Mag(); }
  /// Return transverse momentum (GeV/c)
  Float_t pt() const              { return p().Perp(); }
  /// Return pseudorapidity
  Float_t eta() const             { return p().Eta(); }
  /// Return azimuthal angel
  Float_t phi() const             { return p().Phi(); }
  /// Return KFParticle mass
  Float_t mass() const            { return mMass; }
  /// Return PDG code
  Int_t pdg() const               { return mPdgCode; }
  /// Return PDG code
  Int_t pdgId() const             { return pdg(); }
  /// Return vector of daughter IDs. Positive values
  /// correspond to the IDs of the other KFParticles from
  /// the StFemtoKFP array. Negative values correspond to the indices
  /// in the StFemtoTrack array.
  std::vector<int> daughterIds() const { return mDaughterIds; }
  /// Return particle charge 
  Double_t charge() const {
    return ( TDatabasePDG::Instance()->GetParticle( pdgId() ) ) ?
      TDatabasePDG::Instance()->GetParticle( pdgId() )->Charge() : 0; 
  }
  /// Return chi2/NDF return by the KFParticle fit
  Float_t chi2() const             { return (Float_t)mChi2/100; }
  /// Return decay point position (cm,cm,cm)
  TVector3 decayPoint() const      { return TVector3(mDecPointX, mDecPointY, mDecPointZ); }
  /// Return decay vector
  /// \param v Primary vertex position
  TVector3 decayVector(TVector3 v) const { return decayPoint() - v; }
  /// Return decay length
  /// \param v Primary vertex position
  Float_t decayLength(TVector3 v) const  { return decayVector(v).Mag(); }
  /// Return DCA between KFParticle and primary vertex
  Float_t dcaKFP2Vertex() const          { return mDcaKFParticle2Vertex; }
  /// Return DCA between daughter tracks (need to revisit for three particle decays)
  Float_t dcaBetweenDaughters() const    { return mDcaBetweenDaughters; }
  /// Return number of daughter tracks
  Int_t nDaughters() const               { return mDaughterIds.size(); }
  /// Return four-momentum of KFParticle
  TLorentzVector fourMomentum() const    { return TLorentzVector(mMomX, mMomY, mMomZ, e()); }
  /// Return energy of KFParticle
  Float_t e() const                      { return TMath::Sqrt(p().Mag2() + mMass * mMass); }
  /// Return Podolanski-Armenteros parameters
  /// \par pMomPos Three-momentum of the positive track (from pair)
  /// \par pMomNeg Three-momentum of the negargive track (from pair)
  /// \par arm[2] 
  static void armenterosPodolanski(TVector3 pMomPos, TVector3 pMomNeg, Float_t arm[2]);

private:
  /// Momentum X (GeV/c)
  Float_t mMomX;
  /// Momentum Y (GeV/c)
  Float_t mMomY;
  /// Momentum Z (GeV/c)
  Float_t mMomZ;
  /// PDG code
  Int_t mPdgCode;
  /// Particle reconstructed mass
  Float_t mMass;
  /// Vector of daughter particles
  std::vector<Int_t> mDaughterIds; // Xi^2, LdL, armenteros, decayPoint???? Truly KFParticle parameters

  /// Chi_square/NDF of this KFParticle fit (compression factor 10^2)
  UShort_t mChi2;
  /// Decay point position in X direction (cm)
  Float_t mDecPointX;
  /// Decay point position in Y direction (cm)
  Float_t mDecPointY;
  /// Decay point position in Z direction (cm)
  Float_t mDecPointZ;

  /// Distance of closest approach of KFParticle to primary vertex (cm)
  Float_t mDcaKFParticle2Vertex;
  /// Distance of closes approach between daughter tracks (cm)
  Float_t mDcaBetweenDaughters;

  // TVector3 mDecPoint; //use GetX(), GetY(), GetZ() // point = (GetX,GetY,GetZ), L = (point-PV) //dL - ???
  //  Decay point Erros
  //   float mdL;

  ClassDef(StFemtoKFP, 1);
};

#endif // #define StFemtoKFP_h
