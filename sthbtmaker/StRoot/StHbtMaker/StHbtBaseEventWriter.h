/**
 * \class StHbtBaseEventWriter
 * \brief Typedef for the StHbtBaseEventReader that makes it a Writer
 *
 * The typedef for the StHbtBaseEventReader that makes it a Writer
 */

#ifndef StHbtBaseEventWriter_h
#define StHbtBaseEventWriter_h

// StHbtMaker headers
#include "StHbtBaseEventReader.h"

// The writer is reader-writer
typedef StHbtBaseEventReader StHbtBaseEventWriter; //!

#endif // #define StHbtBaseEventWriter_h
