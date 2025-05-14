/**
 * \class StHbtModelHiddenInfo
 * \brief The hidden information for model calculations
 *
 * Stores information needed for the weight generation - the true
 * simulated momenta, freeze-out coordinates from model and particle PID
 */

#ifndef StHbtModelHiddenInfo_h
#define StHbtModelHiddenInfo_h

// C++ headers
#include <limits>

// StHbtMaker headers
#include "StHbtHiddenInfo.h"
#include "StHbtTypes.h"

// ROOT headers
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TParticle.h"

//_________________
class StHbtModelHiddenInfo : public StHbtHiddenInfo {

 public:
  /// Default constructor
  StHbtModelHiddenInfo();
  /// Copy constructor
  StHbtModelHiddenInfo(const StHbtModelHiddenInfo &aInfo);
  /// Assignment operator
  StHbtModelHiddenInfo& operator=(const StHbtModelHiddenInfo& aInfo);
  /// Destructor
  virtual ~StHbtModelHiddenInfo();

  /// Return true momentum of the particle (px,py,pz)
  TVector3 trueMomentum() const;
  /// Return true momentum of the particle (px,py,pz)
  TVector3 TrueMomentum() const             { return trueMomentum(); }
  /// Return momentum of the mother track (px,py,pz)
  TVector3 motherMomentum() const;
  /// Return momentum of the mother track (px,py,pz)
  TVector3 MotherMomentum() const           { return motherMomentum(); }
  /// Return emission point (x,y,z,t)
  TLorentzVector emissionPoint() const;
  /// Return emission point (x,y,z,t)
  TLorentzVector EmissionPoint() const      { return emissionPoint(); }
  /// PDG code
  int pdgId() const                         { return mPDGPid; }
  /// PDG code
  int PdgId() const                         { return pdgId(); }
  /// PDG code
  int pdgPid() const                        { return pdgId(); }
  /// PDG code
  int PdgPid() const                        { return pdgId(); }
  /// PDG code of the mother particle
  int motherPdgCode() const                 { return mMotherPdg; }
  /// PDG code of the mother particle
  int MotherPdgCode() const                 { return motherPdgCode(); }
  /// Particle mass
  float mass() const
  { return TDatabasePDG::Instance()->GetParticle( pdgPid() )->Mass(); }
  /// Particle mass
  float Mass() const                        { return mass(); }
  /// Particle charge
  float charge() const
  { return TDatabasePDG::Instance()->GetParticle( pdgPid() )->Charge(); }
  /// Particle charge
  float Charge() const                      { return charge(); }
  /// Return mother's mass
  float motherMass() const
  { return TDatabasePDG::Instance()->GetParticle( motherPdgCode() )->Mass(); }
  /// Return mother's mass
  float MotherMass() const                  { return motherMass(); }
  /// Return mother's charge
  float motherCharge() const
  {  return TDatabasePDG::Instance()->GetParticle( motherPdgCode() )->Charge(); }
  /// Return mother's charge
  float MotherCharge() const                { return motherCharge(); }


  /// Return true momentum of the positive track (px,py,pz)
  TVector3 trueMomentumPos() const;
  /// Return true momentum of the positive track (px,py,pz)
  TVector3 TrueMomentumPos() const          { return trueMomentumPos(); }
  /// Return emission point of the positive track (x,y,z,t)
  TLorentzVector emissionPointPos() const;
  /// Return emission point of the positive track (x,y,z,t)
  TLorentzVector EmissionPointPos() const   { return emissionPointPos(); }
  /// Return PDG code of the positive track
  int pdgPidPos() const                     { return mPDGPidPos; }
  /// Return PDG code of the positive track
  int PdgPidPos() const                     { return pdgPidPos(); }
  /// Return mass of the positive track
  float massPos() const
  { return TDatabasePDG::Instance()->GetParticle( pdgPidPos() )->Mass(); }
  /// Return mass of the positive track
  float MassPos() const                     { return massPos(); }

  /// Return true momentum of the negative track (px,py,pz)
  TVector3 trueMomentumNeg() const;
  /// Return true momentum of the negative track (px,py,pz)
  TVector3 TrueMomentumNeg() const          { return trueMomentumNeg(); }
  /// Return emission point of the negative track (x,y,z,t)
  TLorentzVector emissionPointNeg() const;
  /// Return emission point of the negative track (x,y,z,t)
  TLorentzVector EmissionPointNeg() const   { return emissionPointNeg(); };
  /// Return PDG code of the negative track
  int pdgPidNeg() const                     { return mPDGPidNeg; }
  /// Return PDG code of the negative track
  int PdgPidNeg() const                     { return pdgPidNeg(); }
  /// Return mass of the positive track
  float massNeg() const
  { return TDatabasePDG::Instance()->GetParticle( pdgPidNeg() )->Mass(); }
  /// Return mass of the positive track
  float MassNeg() const                     { return massNeg(); }

  /// Return origin:
  /// \param -1 unknown
  /// \param 0 physical primary
  /// \param 1 secondary from weak decay
  /// \param 2 secondary from material
  int  origin() const                       { return (int)mOrigin; }
  /// Return origin:
  /// \param -1 unknown
  /// \param 0 physical primary
  /// \param 1 secondary from weak decay
  /// \param 2 secondary from material
  int  Origin() const                       { return origin(); }

  /// Set true momentum of the particle
  void setTrueMomentum(TVector3 *aMom);
  /// Set true momentum of the particle
  void SetTrueMomentum(TVector3 *aMom)       { setTrueMomentum(aMom); }
  /// Set true momentum of the particle
  void setTrueMomentum(const TVector3& aMom);
  /// Set true momentum of the particle
  void SetTrueMomentum(const TVector3& aMom) { setTrueMomentum(aMom); }
  /// Set true momentum of the particle
  void setTrueMomentum(const double& aPx, const double& aPy, const double& aPz);
  /// Set true momentum of the particle
  void SetTrueMomentum(const double& aPx, const double& aPy, const double& aPz)
  { setTrueMomentum(aPx, aPy, aPz); }
  /// Set momentum of the mother track
  void setMotherMomentum(TVector3 *aMom);
  /// Set momentum of the mother track
  void SetMotherMomentum(TVector3 *aMom)    { setMotherMomentum(aMom); }
  /// Set momentum of the mother track
  void setMotherMomentum(const TVector3& aMom);
  /// Set momentum of the mother track
  void SetMotherMomentum(const TVector3& aMom) { setMotherMomentum(aMom); }
  /// Set momentum of the mother track
  void setMotherMomentum(const double& aPx, const double& aPy, const double& aPz);
  /// Set momentum of the mother track
  void SetMotherMomentum(const double& aPx, const double& aPy, const double& aPz)
  { setMotherMomentum(aPx, aPy, aPz); }

  /// Set emission point position (x,y,z,t)
  void setEmissionPoint(TLorentzVector *aPos);
  /// Set emission point position (x,y,z,t)
  void SetEmissionPoint(TLorentzVector *aPos)  { setEmissionPoint(aPos); }
  /// Set emission point position (x,y,z,t)
  void setEmissionPoint(const TLorentzVector& aPos);
  /// Set emission point position (x,y,z,t)
  void SetEmissionPoint(const TLorentzVector& aPos) { setEmissionPoint(aPos); }
  /// Set emission point position (x,y,z,t)
  void setEmissionPoint(const double& aRx, const double& aRy, const double& aRz, const double& aT);
  /// Set emission point position (x,y,z,t)
  void SetEmissionPoint(const double& aRx, const double& aRy, const double& aRz, const double& aT)
  { setEmissionPoint(aRx, aRy, aRz, aT); }
  /// Set PDG code
  void setPdgPid(const int& aPid)        { mPDGPid = aPid; }
  /// Set PDG code
  void setPDGPid(const int& aPid)        { setPdgPid(aPid); }
  /// Set PDG code
  void SetPdgPid(const int& aPid)        { setPdgPid(aPid); }
  /// Set PDG code of the mother particle
  void setMotherPdgCode(const int& motherPdg) { mMotherPdg = motherPdg; }
  /// Set PDG code of the mother particle
  void SetMotherPdgCode(const int& motherPdg) { setMotherPdgCode(motherPdg); }

  /// Set true momentum of the positive track (px,py,pz)
  void setTrueMomentumPos(TVector3 *aMom);
  /// Set true momentum of the positive track (px,py,pz)
  void SetTrueMomentumPos(TVector3 *aMom)  { setTrueMomentumPos(aMom); }
  /// Set true momentum of the positive track (px,py,pz)
  void setTrueMomentumPos(const TVector3& aMom);
  /// Set true momentum of the positive track (px,py,pz)
  void SetTrueMomentumPos(const TVector3& aMom) { setTrueMomentumPos(aMom); }
  /// Set true momentum of the positive track (px,py,pz)
  void setTrueMomentumPos(const double& aPx, const double& aPy, const double& aPz);
  /// Set true momentum of the positive track (px,py,pz)
  void SetTrueMomentumPos(const double& aPx, const double& aPy, const double& aPz)
  { setTrueMomentumPos(aPx, aPy, aPz); }
  /// Set emission point position of the positive track (x,y,z,t)
  void setEmissionPointPos(TLorentzVector *aPos);
  /// Set emission point position of the positive track (x,y,z,t)
  void SetEmissionPointPos(TLorentzVector *aPos) { setEmissionPointPos(aPos); }
  /// Set emission point position of the positive track (x,y,z,t)
  void setEmissionPointPos(const TLorentzVector& aPos);
  /// Set emission point position of the positive track (x,y,z,t)
  void SetEmissionPointPos(const TLorentzVector& aPos) { setEmissionPointPos(aPos); }
  /// Set emission point position of the positive track (x,y,z,t)
  void setEmissionPointPos(const double& aRx, const double& aRy, const double& aRz, const double& aT);
  /// Set emission point position of the positive track (x,y,z,t)
  void SetEmissionPointPos(const double& aRx, const double& aRy, const double& aRz, const double& aT)
  { setEmissionPointPos(aRx, aRy, aRz, aT); }
  /// Set PDG code of the positive track
  void setPdgPidPos(const int& aPid)   { mPDGPidPos = aPid; }
  /// Set PDG code of the positive track
  void setPDGPidPos(const int& aPid)   { setPdgPidPos(aPid); }
  /// Set PDG code of the positive track
  void SetPdgPidPos(const int& aPid)   { setPdgPidPos(aPid); }

  /// Set true momentum of the negative track (px,py,pz)
  void setTrueMomentumNeg(TVector3 *aMom);
  /// Set true momentum of the negative track (px,py,pz)
  void SetTrueMomentumNeg(TVector3 *aMom)  { setTrueMomentumNeg(aMom); }
  /// Set true momentum of the negative track (px,py,pz)
  void setTrueMomentumNeg(const TVector3& aMom);
  /// Set true momentum of the negative track (px,py,pz)
  void SetTrueMomentumNeg(const TVector3& aMom) { setTrueMomentumNeg(aMom); }
  /// Set true momentum of the negative track (px,py,pz)
  void setTrueMomentumNeg(const double& aPx, const double& aPy, const double& aPz);
  /// Set true momentum of the negative track (px,py,pz)
  void SetTrueMomentumNeg(const double& aPx, const double& aPy, const double& aPz)
  { setTrueMomentumNeg(aPx, aPy, aPz); }
  /// Set emission point position of the negative track (x,y,z,t)
  void setEmissionPointNeg(TLorentzVector *aNeg);
  /// Set emission point position of the negative track (x,y,z,t)
  void SetEmissionPointNeg(TLorentzVector *aNeg) { setEmissionPointNeg(aNeg); }
  /// Set emission point position of the negative track (x,y,z,t)
  void setEmissionPointNeg(const TLorentzVector& aNeg);
  /// Set emission point position of the negative track (x,y,z,t)
  void SetEmissionPointNeg(const TLorentzVector& aNeg) { setEmissionPointNeg(aNeg); }
  /// Set emission point position of the negative track (x,y,z,t)
  void setEmissionPointNeg(const double& aRx, const double& aRy, const double& aRz, const double& aT);
  /// Set emission point position of the negative track (x,y,z,t)
  void SetEmissionPointNeg(const double& aRx, const double& aRy, const double& aRz, const double& aT)
  { setEmissionPointNeg(aRx, aRy, aRz, aT); }
  /// Set PDG code of the negative track
  void setPdgPidNeg(const int& aPid)   { mPDGPidNeg = aPid; }
  /// Set PDG code of the negative track
  void setPDGPidNeg(const int& aPid)   { setPdgPidNeg(aPid); }
  /// Set PDG code of the negative track
  void SetPdgPidNeg(const int& aPid)   { setPdgPidNeg(aPid); }

  /// Set origin:
  /// \param 0 physical primary
  /// \param 1 secondary from weak decay
  /// \param 2 secondary from material
  void setOrigin(const int& origin)
  { mOrigin = ( ( origin > 2 || origin<0 ) ? -1 : (char)origin ); }
  /// Set origin:
  /// \param 0 physical primary
  /// \param 1 secondary from weak decay
  /// \param 2 secondary from material
  void SetOrigin(const int& origin) { setOrigin(origin); }

  // !!! MANDATORY !!!
  /// Copy the hidden info from StHbtTrack to StHbtParticle
  virtual StHbtHiddenInfo* clone() const { return getParticleHiddenInfo(); }
  /// Copy the hidden info from StHbtTrack to StHbtParticle
  virtual StHbtHiddenInfo* Clone() const { return clone(); }

 protected:

  /// Return copy of the hidden info
  virtual StHbtHiddenInfo* getParticleHiddenInfo() const;
  /// Return copy of the hidden info
  virtual StHbtHiddenInfo* GetParticleHiddenInfo() const { return getParticleHiddenInfo(); }

  /// X component of true (simulated) momentum
  float *mTrueMomentumX;
  /// Y component of true (simulated) momentum
  float *mTrueMomentumY;
  /// Z component of true (simulated) momentum
  float *mTrueMomentumZ;
  /// X component of momentum of mother particle
  float *mMotherMomentumX;
  /// Y component of momentum of mother particle
  float *mMotherMomentumY;
  /// Z component of momentum of mother particle
  float *mMotherMomentumZ;
  /// Emission point coordinate X
  float *mEmissionPointX;
  /// Emission point coordinate Y
  float *mEmissionPointY;
  /// Emission point coordinate Z
  float *mEmissionPointZ;
  /// Emission point coordinate T
  float *mEmissionPointT;
  /// True PID of the particle
  int    mPDGPid;
  /// PDG code of particle's mother
  int    mMotherPdg;

  /// X component of the daughter particle momentum
  float *mTrueMomentumPosX;
  /// Y component of the daughter particle momentum
  float *mTrueMomentumPosY;
  /// Z component of the daughter particle momentum
  float *mTrueMomentumPosZ;
  /// X coordinate of the emission point coordinates of positive daughter
  float *mEmissionPointPosX;
  /// Y coordinate of the emission point coordinates of positive daughter
  float *mEmissionPointPosY;
  /// Z coordinate of the emission point coordinates of positive daughter
  float *mEmissionPointPosZ;
  /// T coordinate of the emission point coordinates of positive daughter
  float *mEmissionPointPosT;
  /// True PID of positive daughter
  int    mPDGPidPos;

  /// X component of the daughter particle momentum
  float *mTrueMomentumNegX;
  /// Y component of the daughter particle momentum
  float *mTrueMomentumNegY;
  /// Z component of the daughter particle momentum
  float *mTrueMomentumNegZ;
  /// X coordinate of the emission point coordinates of negative daughter
  float *mEmissionPointNegX;
  /// Y coordinate of the emission point coordinates of negative daughter
  float *mEmissionPointNegY;
  /// Z coordinate of the emission point coordinates of negative daughter
  float *mEmissionPointNegZ;
  /// T coordinate of the emission point coordinates of negative daughter
  float *mEmissionPointNegT;
  /// True PID of negative daughter
  int    mPDGPidNeg;

  /// Origin of particles:
  /// \param -1 unknown
  /// \param 0 physical primary
  /// \param 1 secondary from weak decay
  /// \param 2 secondary from material
  char mOrigin;
};

#endif // StHbtModelHiddenInfo_h
