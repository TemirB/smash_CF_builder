/**
 * \class StHbtBaseEventCut
 * \brief The pure virtual base class for the event cut
 *
 * All event cuts must inherit from this one and implement the pass() and
 * report() methods. The ::clone() function simply returns nullptr, so if
 * users want their cuts to behave as expected, they should also write
 * their own.
 */

#ifndef StHbtBaseEventCut_h
#define StHbtBaseEventCut_h

// Forward declarations
class StHbtEvent;
class StHbtBaseAnalysis;

// StHbtMaker headers
#include "StHbtCutMonitorHandler.h"
#include "StHbtString.h"

// ROOT headers
#include "TList.h"
#include "TString.h"

//_________________
class StHbtBaseEventCut : public StHbtCutMonitorHandler {

 public:
  /// Default constructor
  StHbtBaseEventCut();
  /// Copy constructor
  StHbtBaseEventCut(const StHbtBaseEventCut& copy);
  /// Assignment operator
  StHbtBaseEventCut& operator=(const StHbtBaseEventCut& copy);
  /// Default destructor
  virtual ~StHbtBaseEventCut() { /* no-op */ }

  /// True if event has passed the cut and false if not
  virtual bool pass(const StHbtEvent* event) = 0;

  /// Return new settings list.
  ///
  /// This method creates a new list of TObjStrings describing cut parameters.
  /// The default implementation automatically calls the AppendSettings method
  /// to fill the list, so users only need to overload that method.
  virtual TList* listSettings() const;

  /// Appends cut settings to a TList
  ///
  /// This method should be overloaded by the user to add any relevent settings
  /// of the cut to the list
  ///
  /// No settings are added by this class. Simply returns the incoming TList.
  ///
  /// \param A list to append settings to.
  /// \param prefix An optional prefix to prepend to the beginning of each setting
  /// \return The same pointer as the parameter
  virtual TList* appendSettings(TList*, const TString& prefix="") const;

  /// User-written method to return string describing cuts
  virtual StHbtString report() = 0;

  /// Default clone
  virtual StHbtBaseEventCut* clone() const = 0;

  /// The following allows "back-pointing" from the CorrFctn
  ///to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  /// Return a pointer to the analysis
  StHbtBaseAnalysis* hbtAnalysis()       { return mBaseAnalysis; }
  /// Set analysis
  void setAnalysis(StHbtBaseAnalysis* a) { mBaseAnalysis = a; }

 protected:
  /// Pointer to the base analysis
  StHbtBaseAnalysis* mBaseAnalysis;   //!<!

#ifdef __ROOT__
  ClassDef(StHbtBaseEventCut, 0)
#endif
};

//_________________
inline StHbtBaseEventCut::StHbtBaseEventCut() : StHbtCutMonitorHandler(), mBaseAnalysis(nullptr) { /* empty */ }

//_________________
inline StHbtBaseEventCut::StHbtBaseEventCut(const StHbtBaseEventCut& c) :
	StHbtCutMonitorHandler(c), mBaseAnalysis( c.mBaseAnalysis )	{ /* empty */ }

//_________________
inline StHbtBaseEventCut& StHbtBaseEventCut::operator=(const StHbtBaseEventCut& c) {
  if ( this != &c ) {
    mBaseAnalysis = c.mBaseAnalysis;
  }
  return *this;
}

//_________________
inline TList* StHbtBaseEventCut::listSettings() const { return appendSettings( new TList() ); }

//_________________
inline TList* StHbtBaseEventCut::appendSettings(TList *listOfSettings, const TString& /* prefix */) const
{ return listOfSettings; }

#endif // #define StHbtBaseEventCut_h
