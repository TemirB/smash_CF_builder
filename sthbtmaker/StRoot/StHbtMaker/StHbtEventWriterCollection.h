/**
 * \class StHbtEventWriterCollection
 * \brief Holds collection of Writers
 *
 * The class keeps a collection (STL list) of event writers
 */

#ifndef StHbtEventWriterCollection_h
#define StHbtEventWriterCollection_h

// StHbtMaker headers
// Base
#include "StHbtBaseEventWriter.h"

// C++ headers
#include <list>

#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtBaseEventWriter*, allocator<StHbtBaseEventWriter*> >            StHbtEventWriterCollection;
typedef list<StHbtBaseEventWriter*, allocator<StHbtBaseEventWriter*> >::iterator  StHbtEventWriterIterator;
#else
typedef list<StHbtBaseEventWriter*>            StHbtEventWriterCollection;
typedef list<StHbtBaseEventWriter*>::iterator  StHbtEventWriterIterator;
#endif

#endif // #define StHbtEventWriterCollection_h
