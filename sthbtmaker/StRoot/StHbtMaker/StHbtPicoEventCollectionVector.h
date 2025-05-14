/**
 * \class StHbtPicoEventCollectionVector
 * \brief Holds collection of PicoEvents for vertex-dependent analysis
 *
 * Holds collection (STL vector) and analysis for vertex-dependent event mixing.
 */

#ifndef StHbtPicoEventCollectionVector_h
#define StHbtPicoEventCollectionVector_h

// C++ headers
#include <vector>
#include <list>

// StHbtMaker header
#include "StHbtPicoEventCollection.h"

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef std::vector<StHbtPicoEventCollection*, std::allocator<StHbtPicoEventCollection*> >            StHbtPicoEventCollectionVector;  //!
typedef std::vector<StHbtPicoEventCollection*, std::allocator<StHbtPicoEventCollection*> >::iterator  StHbtPicoEventCollectionIterator;//!
#else
typedef std::vector<StHbtPicoEventCollection*>            StHbtPicoEventCollectionVector;//!
typedef std::vector<StHbtPicoEventCollection*>::iterator  StHbtPicoEventCollectionIterator;//!
#endif

#endif // #define StHbtPicoEventCollectionVector_h
