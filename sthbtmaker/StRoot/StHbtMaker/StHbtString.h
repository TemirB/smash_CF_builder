/**
 * \class StHbtString
 * \brief A file that returns a string
 *
 * The StHbtString header provides a typedef for the string
 */

#ifndef StHbtString_h
#define StHbtString_h

#ifndef __CINT__

#ifndef StHbtString_noCint
#define StHbtString_noCint

// C++ headers
#include <string>
#if !defined(ST_NO_NAMESPACES)
using std::string;
#endif
typedef string StHbtString;

#endif //StHbtString_noCint

#else // else to #ifndef __CINT__

#ifndef StHbtString_yesCint
#define StHbtString_yesCint
class StHbtString;
#endif //#define StHbtString_yesCint

#endif // #ifndef __CINT__

#endif // #define StHbtString_h
