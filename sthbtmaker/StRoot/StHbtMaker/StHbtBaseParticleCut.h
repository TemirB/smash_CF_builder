/**
 * \class StHbtBaseParticleCut
 * \brief The pure virtual base class for the particle cut.
 *
 * All particle cuts must inherit from this one
 */

#ifndef StHbtBaseParticleCut_h
#define StHbtBaseParticleCut_h

// C++ headers
#include <iostream>

// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtCutMonitorHandler.h"

// ROOT headers
#include "TList.h"
#include "TObjString.h"
#include "TString.h"

// Forward declaration
class StHbtBaseAnalysis;

//_________________
class StHbtBaseParticleCut : public StHbtCutMonitorHandler {

 public:
  /// Default constructor
  StHbtBaseParticleCut();
  /// Copy constructor
  StHbtBaseParticleCut(const StHbtBaseParticleCut& copy);
  /// Assignment operator
  StHbtBaseParticleCut& operator=(const StHbtBaseParticleCut& c);
  /// Default destructor
  virtual ~StHbtBaseParticleCut() { /* no-op */ }

  /// User-written method to return string describing cuts
  virtual StHbtString report() = 0;
  /// User-written list of settings which is stored in the result file
  virtual TList *listSettings();

  /// Return mass of the particle to be selected
  double mass() { return mMass; }
  /// Set mass of the particle to be selected
  virtual void setMass(const double& mass) { mMass = mass; }

  /// Declare event start
  virtual void eventBegin(const StHbtEvent*) { /* no-op */ }
  /// Declare event end
  virtual void eventEnd(const StHbtEvent*) { /* no-op */ }
  /// Clone base particle cut
  virtual StHbtBaseParticleCut* clone() { return nullptr; }

  /// Return particle type
  virtual StHbtParticleType type() = 0;

  /// The following allows "back-pointing" from the CorrFctn
  /// to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  /// Return a pointer to the analysis
  StHbtBaseAnalysis* hbtAnalysis() { return mBaseAnalysis; }
  /// Set analysis
  void setAnalysis(StHbtBaseAnalysis* ana) { mBaseAnalysis = ana; }

 protected:

  /// Particle mass
  double mMass;
  /// Pointer to the base analysis
  StHbtBaseAnalysis* mBaseAnalysis; //!<!

#ifdef __ROOT__
  ClassDef(StHbtBaseParticleCut, 0)
#endif
};

//_________________
inline StHbtBaseParticleCut::StHbtBaseParticleCut() : StHbtCutMonitorHandler(), mMass(0), mBaseAnalysis(nullptr)
{ /* empty */ }

//_________________
inline StHbtBaseParticleCut::StHbtBaseParticleCut(const StHbtBaseParticleCut& c) :
			StHbtCutMonitorHandler(c), mMass(c.mMass), mBaseAnalysis(c.mBaseAnalysis) { /* empty */ }

//_________________
inline StHbtBaseParticleCut& StHbtBaseParticleCut::operator=(const StHbtBaseParticleCut& c) {
  if( this != &c ) {
    StHbtCutMonitorHandler::operator=(c); mBaseAnalysis = c.mBaseAnalysis; mMass = c.mMass;
  }
  return *this;
}

//_________________
inline TList *StHbtBaseParticleCut::listSettings() {
  TList *listOfSettings = new TList();
  listOfSettings->Add( new TObjString( Form("StHbtBaseParticleCut::mass = %5.3f",mMass) ) );
  return listOfSettings;
}

#endif // #define StHbtBaseParticleCut_h
