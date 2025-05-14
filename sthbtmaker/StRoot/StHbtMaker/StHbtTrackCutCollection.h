/**
 * \class StHbtTrackCutCollection
 * \brief Holds collection of track cuts
 *
 * Holds collection (STL list) of track cuts
 */

#ifndef StHbtTrackCutCollection_h
#define StHbtTrackCutCollection_h

// C++ headers
#include <list>

// StHbtMaker headers
class StHbtBaseTrackCut;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef std::list<StHbtBaseTrackCut*, std::allocator<StHbtBaseTrackCut*> >            StHbtTrackCutCollection;
typedef std::list<StHbtBaseTrackCut*, std::allocator<StHbtBaseTrackCut*> >::iterator  StHbtTrackCutIterator;
#else
typedef std::list<StHbtBaseTrackCut*>            StHbtTrackCutCollection;
typedef std::list<StHbtBaseTrackCut*>::iterator  StHbtTrackCutIterator;
#endif

#endif // #define StHbtTrackCutCollection_h
