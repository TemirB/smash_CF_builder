/**
 * \class StHbtV0Collection
 * \brief Holds collection of V0s
 *
 * Holds a collectin (STL list) of V0s
 */

#ifndef StHbtV0Collection_h
#define StHbtV0Collection_h

// C++ headers
#include <list>

// StHbtMaker headers
#include "StHbtV0.h"

#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtV0*, allocator<StHbtV0*> >            StHbtV0Collection;
typedef list<StHbtV0*, allocator<StHbtV0*> >::iterator  StHbtV0Iterator;
#else
typedef list<StHbtV0*>            StHbtV0Collection;
typedef list<StHbtV0*>::iterator  StHbtV0Iterator;
#endif

#endif // #define StHbtV0Collection_h
