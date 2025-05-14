/**
 * \class StHbtTrackCollection
 * \brief Holds collection of tracks
 *
 * Holds a collectin (STL list) of tracks
 */

#ifndef StHbtTrackCollection_h
#define StHbtTrackCollection_h

// C++ headers
#include <list>

// StHbtMaker headers
#include "StHbtTrack.h"

#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtTrack*, allocator<StHbtTrack*> >            StHbtTrackCollection;
typedef list<StHbtTrack*, allocator<StHbtTrack*> >::iterator  StHbtTrackIterator;
#else
typedef list<StHbtTrack*>            StHbtTrackCollection;
typedef list<StHbtTrack*>::iterator  StHbtTrackIterator;
#endif

#endif // #define StHbtTrackCollection_h
