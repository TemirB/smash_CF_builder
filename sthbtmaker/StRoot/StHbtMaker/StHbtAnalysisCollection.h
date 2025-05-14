/**
 * \class StHbtAnalysisCollection
 * \brief Holds a collection of analyses
 *
 * The class holds a collection (STL list) of analyses
 */

#ifndef StHbtAnalysisCollection_h
#define StHbtAnalysisCollection_h

// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

// Forward declaration
class StHbtBaseAnalysis;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtBaseAnalysis*, allocator<StHbtBaseAnalysis*> >            StHbtAnalysisCollection;
typedef list<StHbtBaseAnalysis*, allocator<StHbtBaseAnalysis*> >::iterator  StHbtAnalysisIterator;
#else
typedef list<StHbtBaseAnalysis*>            StHbtAnalysisCollection;
typedef list<StHbtBaseAnalysis*>::iterator  StHbtAnalysisIterator;
#endif

#endif // #define StHbtAnalysisCollection_h
