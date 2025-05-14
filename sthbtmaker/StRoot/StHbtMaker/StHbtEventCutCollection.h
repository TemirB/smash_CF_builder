/**
 * \class StHbtEventCutCollection
 * \brief Holds collection of event cuts
 *
 * The class holds collection (STL list) of event cuts
 */

#ifndef StHbtEventCutCollection_h
#define StHbtEventCutCollection_h

// C++ headers
#include <list>

// Forward declaration
class StHbtBaseEventCut;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef std::list<StHbtBaseEventCut*, std::allocator<StHbtBaseEventCut*> >            StHbtEventCutCollection;
typedef std::list<StHbtBaseEventCut*, std::allocator<StHbtBaseEventCut*> >::iterator  StHbtEventCutIterator;
#else
typedef std::list<StHbtBaseEventCut*>            StHbtEventCutCollection;
typedef std::list<StHbtBaseEventCut*>::iterator  StHbtEventCutIterator;
#endif

#endif // #define StHbtEventCutCollection_h
