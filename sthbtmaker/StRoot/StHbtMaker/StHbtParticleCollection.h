/**
 * \class StHbtParticleCollection
 * \brief Holds collection of particles
 *
 * Holds collection (STL list) of particles
 */

#ifndef StHbtParticleCollection_h
#define StHbtParticleCollection_h

// C++ headers
#include <list>

// StHbtMaker headers
#include "StHbtParticle.h"

#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtParticle*, allocator<StHbtParticle*> >                 StHbtParticleCollection;
typedef list<StHbtParticle*, allocator<StHbtParticle*> >::iterator       StHbtParticleIterator;
typedef list<StHbtParticle*, allocator<StHbtParticle*> >::const_iterator StHbtParticleConstIterator;
#else
typedef list<StHbtParticle*>                 StHbtParticleCollection;
typedef list<StHbtParticle*>::iterator       StHbtParticleIterator;
typedef list<StHbtParticle*>::const_iterator StHbtParticleConstIterator;
#endif

#endif // #define StHbtParticleCollection_h
