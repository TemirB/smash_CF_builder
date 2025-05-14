/**
 * \class StHbtHiddenInfo
 * \brief A pure virtual base class for the hidden (Monte Carlo) data.
 *
 * Hidden info stores additional information, which is not in a standard track.
 */

#ifndef StHbtHiddenInfo_h
#define StHbtHiddenInfo_h

// StHbtMaker headers
#include "StHbtTypes.h"

// ROOT headers
#include "TLorentzVector.h"

//_________________
class StHbtHiddenInfo {

 public:
  /// Default constructor
  StHbtHiddenInfo()            { /* empty */ }
  /// Default destructor
  virtual ~StHbtHiddenInfo()   { /* empty */ }

  // !!! MANDATORY !!!
  // --- Copy the hidden info from StHbtTrack to StHbtParticle

  /// Set emission point
  virtual void setEmissionPoint(const double& x, const double& y, const double& z, const double& t) = 0;
  /// Set emission point
  virtual void SetEmissionPoint(const double& x, const double& y, const double& z, const double& t)
  { setEmissionPoint(x, y, z, t); }
  /// Retrieve emission point
  virtual TLorentzVector emissionPoint() const = 0;
  /// Retrieve emission point
  virtual TLorentzVector EmissionPoint() const { return emissionPoint(); }
  /// Return PDG code of the particle
  virtual int pdgId() const = 0;
  /// Return PDG code of the particle
  virtual int PdgId() const                    { return pdgId(); }
  /// Retrieve hidden information
  virtual StHbtHiddenInfo* getParticleHiddenInfo() const = 0;
  /// Retrieve hidden information
  virtual StHbtHiddenInfo* GetParticleHiddenInfo() const { return getParticleHiddenInfo(); }
  /// Clone hidden information
  virtual StHbtHiddenInfo* clone() const;
  /// Clone hidden information
  virtual StHbtHiddenInfo* Clone() const { return clone(); }
};

//_________________
inline StHbtHiddenInfo* StHbtHiddenInfo::clone() const {
  return getParticleHiddenInfo();
}

#endif // #define StHbtHiddenInfo_h
