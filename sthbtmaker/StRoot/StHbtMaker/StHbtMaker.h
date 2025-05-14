/**
 * \class StHbtMaker
 * \brief The Maker that runs StHbtMaker maker subclasses.
 *
 * One uses the maker to instantiate and add analysis into it.
 * To work in the STAR environment, sl73_gcc485 global variable
 * must be defined at the compilation and a the run time.
 */

#ifndef StHbtMaker_h
#define StHbtMaker_h

#ifdef sl73_gcc485
// STAR headers
#include "StMaker.h"
#endif

// StHbtMaker headers
#include "StHbtManager.h"

//_________________
class StHbtMaker
#ifdef sl73_gcc485
: public StMaker
#endif
{

 public:
  /// Constructor
  StHbtMaker(const char* name = "StHbt", const char* title = "StHbtTitle");
  /// Destructor
  virtual ~StHbtMaker();

  // Standard StChain (STAR) options that can be used
  // in a standalone mode.

  /// Clear method
  virtual void clear(const char* opt="");
  /// Clear method
  virtual void Clear(const char* opt) { clear(opt); }
  /// Init method
  virtual Int_t init();
  virtual Int_t Init()   { return init(); }
  /// Make method
  virtual Int_t make();
  /// Make method
  virtual Int_t Make()   { return make(); }
  /// Finish method
  virtual Int_t finish();
  /// Finish method
  virtual Int_t Finish() { return finish(); }

  /// Return a pointer to StHbtManager
  StHbtManager* hbtManager()  { return mHbtManager; }
  /// Return a pointer to StHbtManager
  StHbtManager* HbtManager()  { return hbtManager(); }
  /// Return debug value
  int debug() const           { return mDebug; }
  /// Return debug value
  int Debug() const           { return debug(); }
  /// Set debug value
  void setDebug(int debug)    { mDebug = debug; }
  /// Set debug value
  void SetDebug(int debug)    { setDebug(debug); }

#ifdef sl73_gcc485
  /// Pointer to a chain
  StMaker* currentChain;
#endif

 private:

  /// Pointer to StHbtManager
  StHbtManager* mHbtManager;  //! tells cint to skip it

  /// Debug value
  int mDebug;

#ifdef __ROOT__
  ClassDef(StHbtMaker,0)
#endif
};

#endif // #define StHbtMaker_h
