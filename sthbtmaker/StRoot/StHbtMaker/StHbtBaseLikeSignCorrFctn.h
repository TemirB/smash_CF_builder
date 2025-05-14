/**
 * \class StHbtBaseLikeSignCorrFctn
 * \brief A pure virtual base class for the like sign correlation function
 *
 * All like sign correlation functions  must inherit from this one
 */

#ifndef StHbtBaseLikeSignCorrFctn_h
#define StHbtBaseLikeSignCorrFctn_h

// Forward declaration
class StHbtPair;

// StHbtMaker headers
#include "StHbtBaseCorrFctn.h"

// ROOT headers
#include "TList.h"

//_________________
class StHbtBaseLikeSignCorrFctn : public StHbtBaseCorrFctn {

 public:
  /// Default constructor
  StHbtBaseLikeSignCorrFctn() { /* empty */ }
  /// Copy constructor
  StHbtBaseLikeSignCorrFctn(const StHbtBaseLikeSignCorrFctn& copy);
  /// Assignment operator
  StHbtBaseLikeSignCorrFctn& operator=(const StHbtBaseLikeSignCorrFctn& copy);
  /// Default destructor
  virtual ~StHbtBaseLikeSignCorrFctn() { /* empty */ }

  /// Add positive pair
  virtual void addLikeSignPositivePair(const StHbtPair*) = 0;
  /// Add negative pair
  virtual void addLikeSignNegativePair(const StHbtPair*) = 0;

  /// Clone like-sign correlation function
  virtual StHbtBaseLikeSignCorrFctn* clone() const = 0;

  /// Return output list
  virtual TList* getOutputList() = 0;

  /// The following allows "back-pointing" from the CorrFctn
  /// to the "parent" Analysis
  friend class StHbtLikeSignAnalysis;
};

//_________________
inline StHbtBaseLikeSignCorrFctn::StHbtBaseLikeSignCorrFctn(const StHbtBaseLikeSignCorrFctn& c) : StHbtBaseCorrFctn(c)
{ mBaseAnalysis = nullptr; }

//_________________
inline StHbtBaseLikeSignCorrFctn& StHbtBaseLikeSignCorrFctn::operator=(const StHbtBaseLikeSignCorrFctn& c)
{ if ( this != &c ) { StHbtBaseCorrFctn::operator=(c); } return *this; }

#endif // #define StHbtLikeSignCorrFctn_h
