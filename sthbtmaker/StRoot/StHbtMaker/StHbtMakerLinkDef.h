#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// Main StHbtMaker classes
#pragma link C++ class StHbtMaker+;
#pragma link C++ class StHbtManager+;

// Base analyses (other should be defined in StHbtMakerUser)
#pragma link C++ class StHbtAnalysis+;
#pragma link C++ class StHbtLikeSignAnalysis+;

// Base classes
#pragma link C++ class StHbtBaseAnalysis+;
#pragma link C++ class StHbtBaseEventReader+;
#pragma link C++ class StHbtBaseEventCut+;
#pragma link C++ class StHbtBaseTrackCut+;
#pragma link C++ class StHbtBaseV0Cut+;
#pragma link C++ class StHbtBaseXiCut+;
#pragma link C++ class StHbtBaseKinkCut+;
#pragma link C++ class StHbtBaseParticleCut+;
#pragma link C++ class StHbtBasePairCut+;
#pragma link C++ class StHbtBaseCutMonitor+;
#pragma link C++ class StHbtBaseCorrFctn+;
#pragma link C++ class StHbtBaseModelFreezeOutGenerator+;
#pragma link C++ class StHbtBaseModelWeightGenerator+;

// Cuts and
#pragma link C++ class StHbtMultiTrackCut+;
#pragma link C++ class StHbtCutMonitorHandler+;

// Main classes
#pragma link C++ class StHbtEvent+;
#pragma link C++ class StHbtTrack+;
#pragma link C++ class StHbtV0+;
#pragma link C++ class StHbtKink+;
#pragma link C++ class StHbtXi+;
#pragma link C++ class StHbtTriplet+;
#pragma link C++ class StHbtParticle+;
#pragma link C++ class StHbtPair+;

// Internal PicoEvent and PicoCollection
#pragma link C++ class StHbtPicoEvent+;
#pragma link C++ class StHbtPicoEventCollectionVectorHideAway+;

// Monte Carlo weights
#pragma link C++ class StHbtModelHiddenInfo+;
#pragma link C++ class StHbtModelGausLCMSFreezeOutGenerator+;
#pragma link C++ class StHbtModelManager+;
#pragma link C++ class StHbtModelWeightGeneratorLednicky+;

// StarClassLibrary adopted classes
#pragma link C++ class StHbtHelix+;
#pragma link C++ class StHbtPhysicalHelix+;

#endif
