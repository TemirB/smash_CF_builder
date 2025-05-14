/**
 * \class StHbtManager
 * \brief The Manager is the top-level object containing an EventReader
 * (the input), and collections of EventWriters and StHbtAnalyses
 * (the outputs)
 *
 * Manager is the top-level object containing an EventReader
 * (the input), and collections of EventWriters and StHbtAnalyses
 * (the outputs).
 *
 * A manager object is owned by an StHbtTaskFemto object which
 * calls the `processEvent()` method, which reads an StHbtEvent
 * from the input files, and forwards it to the `processEvent` method
 * in each output analysis, which is responsible for carrying out the
 * actual cuts & computation.
 *
 * StHbtManager objects "own" the EventReader, Analyses, and
 * EventWriters added to them, and is responsible for deleting them
 * upon its own destruction.
 *
 * StHbtManager objects are not copyable, as the StHbtAnalysis
 * objects they contain have no means of copying/cloning.
 * Denying copyability by making the copy constructor and assignment
 * operator private prevents potential dangling pointer (segfault)
 * errors.
 */

#ifndef StHbtManager_h
#define StHbtManager_h

// StHbtMaker headers
// Base
#include "StHbtBaseAnalysis.h"
#include "StHbtBaseEventReader.h"
#include "StHbtBaseEventWriter.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtAnalysisCollection.h"
#include "StHbtEventWriterCollection.h"
#include "StHbtEvent.h"

//_________________
class StHbtManager{

 public:
  /// Default constructor
  StHbtManager();
  /// Copy constructor
  StHbtManager(const StHbtManager& copy);
  /// Copy constructor
  StHbtManager& operator=(const StHbtManager& man);
  /// Default destructor
  virtual ~StHbtManager();

  /// Return pointer to the analysis collection
  StHbtAnalysisCollection *analysisCollection()     { return mAnalysisCollection; }
  /// Access to the n-th analysis within Collection
  StHbtBaseAnalysis *analysis(int n);
  /// Add analysis
  void addAnalysis(StHbtBaseAnalysis *analysis)     { mAnalysisCollection->push_back(analysis); }

  /// Return pointer to the Collection of event writers
  StHbtEventWriterCollection* eventWriterCollection()  { return mEventWriterCollection; }
  /// Access to n-th EventWriter within Collection
  StHbtBaseEventWriter *eventWriter(int n);
  /// Add event writer
  void setEventWriter(StHbtBaseEventWriter *writer) { addEventWriter( writer ); }
  /// Add event writer
  void addEventWriter(StHbtBaseEventWriter* writer) { mEventWriterCollection->push_back(writer); }

  /// Return event reader
  StHbtBaseEventReader* eventReader()   { return mEventReader; }
  /// Add EventReader
  void setEventReader(StHbtBaseEventReader* reader) { mEventReader = reader; }

  /// Calls `init()` on all owned EventWriters
  /// Returns 0 for success, 1 for failure.
  int init();
  /// A "0" return value means success - otherwise quit
  int processEvent();
  /// Calls `Finish()` on the EventReader, EventWriters, and the Analyses.
  void finish();

  /// Construct report
  StHbtString report();

 private:

  /// Pointer to a collection of analyses
  StHbtAnalysisCollection *mAnalysisCollection;
  /// Pointer to event reader
  StHbtBaseEventReader *mEventReader;
  /// Pointer to a collection of event writers
  StHbtEventWriterCollection *mEventWriterCollection;

#ifdef __ROOT__
  ClassDef(StHbtManager, 0)
#endif
};

#endif // StHbtManager_h
