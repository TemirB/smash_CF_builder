/**
 * \class StHbtCorrFctnCollection
 * \brief Holds collection of correlation functions
 *
 *   The CorrFctnCollection contains pointers to all correlation functions
 *   that are associated with a particular analysis object.
 */

#ifndef StHbtCorrFctnCollection_h
#define StHbtCorrFctnCollection_h

// C++ headeres
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

// Forward declaration
class StHbtBaseCorrFctn;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtBaseCorrFctn*, allocator<StHbtBaseCorrFctn*> >            StHbtCorrFctnCollection;
typedef list<StHbtBaseCorrFctn*, allocator<StHbtBaseCorrFctn*> >::iterator  StHbtCorrFctnIterator;
#else
typedef list<StHbtBaseCorrFctn*>            StHbtCorrFctnCollection;
typedef list<StHbtBaseCorrFctn*>::iterator  StHbtCorrFctnIterator;
#endif

#endif // #define StHbtCorrFctnCollection_h
