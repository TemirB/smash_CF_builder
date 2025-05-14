#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// Monitors
#pragma link C++ class fxtEventCutMonitor+;
#pragma link C++ class fxtTrackCutMonitor+;
#pragma link C++ class fxtPairCutMonitor+;

// Cuts
#pragma link C++ class StHbtBasicEventCut+;
#pragma link C++ class StHbtBasicTrackCut+;
#pragma link C++ class StHbtBasicPairCut+;
#pragma link C++ class StHbtDummyTrackCut+;

// Readers
#ifndef StHbtMcDstReaderExclude
#pragma link C++ class StHbtMcDstReader+;
#endif
#ifndef StHbtFemtoDstReaderExclude
#pragma link C++ class StHbtFemtoDstReader+;
#endif
#pragma link C++ class StHbtPicoDstReader+;

// Analyses
#pragma link C++ class StHbtVertexAnalysis+;
#pragma link C++ class StHbtVertexMultAnalysis+;
#pragma link C++ class StHbtReactionPlaneAnalysis+;
#pragma link C++ class StHbtModelSpectraAnalysis+;

// Correlation functions
#pragma link C++ class StHbtCorrFctn3DLCMSSym+;
#pragma link C++ class StHbtModelQinvCorrFctn+;
#pragma link C++ class StHbtModelQinvCorrFctnKt+;
#pragma link C++ class StHbtQinvCorrFctnKt+;
#pragma link C++ class StHbtBPLCMS3DCorrFctnKt+;
#pragma link C++ class StHbtModelBPLCMS3DCorrFctnKt+;
#pragma link C++ class StHbtDeltaEtaDeltaPhiStarMinKt+;

// Other classes
#pragma link C++ class StHbtCoulomb+;
#pragma link C++ class StHbtSmearPair+;

#endif
