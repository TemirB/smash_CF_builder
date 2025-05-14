/**
 * \class StHbtBaseAnalysis
 * \brief The pure virtual base class for analysis
 *
 * The StHbtBaseAnalysis class is a base class for analysis
 * classes must inherit from this one
 */

#ifndef StHbtBaseAnalysis_h
#define StHbtBaseAnalysis_h

// StHbtMaker headers
#include "StHbtTypes.h"

// ROOT headers
#include "TList.h"
#include "TObjString.h"

// Forward declaration
class StHbtEvent;

//_________________
class StHbtBaseAnalysis {

 public:
  /// Default constructor
  StHbtBaseAnalysis()                { /* noop */ }
  /// Default destructor
  virtual ~StHbtBaseAnalysis()       { /* noop */ }

  /// Returns reports of all cuts applied and
  /// correlation functions being done
  virtual StHbtString report() = 0;   //!<

  /// Return list of cut settings for the analysis
  virtual TList *listSettings() = 0;  //!<

  /// Obtain number of objects to be written as an output
  virtual TList *getOutputList() = 0; ///<

  /// Main machinery
  virtual void processEvent(const StHbtEvent*) = 0; ///<

  /// Finish
  virtual void finish() = 0; ///<

#ifdef __ROOT__
  ClassDef(StHbtBaseAnalysis, 0)
#endif
};

#endif // #define StHbtBaseAnalysis_h
