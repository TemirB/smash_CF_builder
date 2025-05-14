/**
 * \class StHbtCutMonitorCollection
 * \brief Keeps collection of cut monitors
 *
 * The class keeps a collection of cut monitors stored as
 * STL vector
 */

#ifndef StHbtCutMonitorCollection_h
#define StHbtCutMonitorCollection_h

// C++ headers
#include <vector>
#include <iterator>
//#include <memory> // for shared and unique pointers (should we use them?)

#if !defined(ST_NO_NAMESPACES)
using std::vector;
#endif

// StHbtMaker headers
class StHbtBaseCutMonitor;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef vector<StHbtBaseCutMonitor*, allocator<StHbtBaseCutMonitor*> >            StHbtCutMonitorCollection;
typedef vector<StHbtBaseCutMonitor*, allocator<StHbtBaseCutMonitor*> >::iterator  StHbtCutMonitorIterator;
#else
typedef vector<StHbtBaseCutMonitor*>            StHbtCutMonitorCollection;
typedef vector<StHbtBaseCutMonitor*>::iterator  StHbtCutMonitorIterator;
#endif

#endif // #define StHbtCutMonitorCollection_h
