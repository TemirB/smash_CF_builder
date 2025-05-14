/**
 * \class StHbtKinkCollection
 * \brief Holds collection of kinks
 *
 * Holds a collectin (STL list) of kinks
 */

#ifndef StHbtKinkCollection_h
#define StHbtKinkCollection_h

// C++ headers
#include <list>

// StHbtMaker headers
#include "StHbtKink.h"

#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtKink*, allocator<StHbtKink*> >            StHbtKinkCollection;
typedef list<StHbtKink*, allocator<StHbtKink*> >::iterator  StHbtKinkIterator;
#else
typedef list<StHbtKink*>            StHbtKinkCollection;
typedef list<StHbtKink*>::iterator  StHbtKinkIterator;
#endif

#endif // #define StHbtKinkCollection_h
