/**
 * \class StHbtPicoEventCollection
 * \brief A collection of hbt pico events
 *
 * A collection of PicoEvents is what makes up the EventMixingBuffer
 * of each Analysis
 */

#ifndef StHbtPicoEventCollection_h
#define StHbtPicoEventCollection_h

// C++ headers
#include <list>

// StHbtMaker headers
class StHbtPicoEvent;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef std::list<StHbtPicoEvent*, std::allocator<StHbtPicoEvent*> >            StHbtPicoEventCollection;
typedef std::list<StHbtPicoEvent*, std::allocator<StHbtPicoEvent*> >::iterator  StHbtPicoEventIterator;
#else
typedef std::list<StHbtPicoEvent*>            StHbtPicoEventCollection;
typedef std::list<StHbtPicoEvent*>::iterator  StHbtPicoEventIterator;
#endif

#endif // #define StHbtPicoEventCollection_h
