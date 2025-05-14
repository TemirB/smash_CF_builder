/**
 * \class StHbtBasePairCut
 * \brief The pure virtual base class for the pair cut
 *
 * All pair cuts must inherit from this one
 */

#ifndef StHbtBasePairCut_h
#define StHbtBasePairCut_h

// C++ headers
#include <string>

// Forward declaration
class StHbtBaseAnalysis;

// StHbtMaker headers
#include "StHbtString.h"
#include "StHbtEvent.h"
#include "StHbtPair.h"
#include "StHbtCutMonitorHandler.h"

// ROOT headers
#include "TList.h"
#include "TObjString.h"

//_________________
class StHbtBasePairCut : public StHbtCutMonitorHandler {

 public:
  /// Default constructor
  StHbtBasePairCut();
  /// Copy constructor
  StHbtBasePairCut(const StHbtBasePairCut& c);
  /// Assignment operator
  StHbtBasePairCut& operator=(const StHbtBasePairCut& c);
  /// Default destructor
  virtual ~StHbtBasePairCut()                    { /* no-op */ }

  /// Returns true in pair passed the cut and false if not
  virtual bool pass(const StHbtPair* pair) = 0;

  /// User-written method to return string describing cuts
  virtual StHbtString report() = 0;
  /// Returns a TList with settings
  virtual TList *listSettings() = 0;

  /// Declare event start
  virtual void eventBegin(const StHbtEvent*) { /* no-op */ }
  /// Declare event end
  virtual void eventEnd(const StHbtEvent*)   { /* no-op */ }
  /// Clone pair cut
  virtual StHbtBasePairCut* clone() { return nullptr; }

  /// The following allows "back-pointing" from the CorrFctn
  /// to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  /// Return pointer to the analysis
  StHbtBaseAnalysis* hbtAnalysis()           { return mBaseAnalysis; }
  /// Set analysis
  void setAnalysis(StHbtBaseAnalysis* ana)   { mBaseAnalysis = ana; }

 protected:
  /// Pointer to the base analysis
  StHbtBaseAnalysis* mBaseAnalysis;   //!<!

#ifdef __ROOT__
  ClassDef(StHbtBasePairCut, 0)
#endif
};

//_________________
inline StHbtBasePairCut::StHbtBasePairCut() : StHbtCutMonitorHandler(), mBaseAnalysis() { /* empty */ }

//_________________
inline StHbtBasePairCut::StHbtBasePairCut(const StHbtBasePairCut& /* c */) : StHbtCutMonitorHandler(), mBaseAnalysis(nullptr)
{ /* empty */ }

//_________________
inline StHbtBasePairCut& StHbtBasePairCut::operator=(const StHbtBasePairCut& c)
{ if ( this != &c ) { mBaseAnalysis = c.mBaseAnalysis; } return *this; }

#endif // #define StHbtBasePairCut_h
