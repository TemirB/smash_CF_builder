/**
 * \class StHbtPairCutCollection
 * \brief Holds collection of pair cuts
 *
 * Holds collection (STL list) of pair cuts
 */

#ifndef StHbtPairCutCollection_h
#define StHbtPairCutCollection_h

// C++ headers
#include <list>

// Forward declarations
class StHbtPairCut;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef std::list<StHbtPairCut*, std::allocator<StHbtPairCut*> >            StHbtPairCutCollection;
typedef std::list<StHbtPairCut*, std::allocator<StHbtPairCut*> >::iterator  StHbtPairCutIterator;
#else
typedef std::list<StHbtPairCut*>            StHbtPairCutCollection;
typedef std::list<StHbtPairCut*>::iterator  StHbtPairCutIterator;
#endif

#endif // #define StHbtPairCutCollection_h
