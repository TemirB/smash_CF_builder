//
// Pair cut monitor for basic analysis
//

// StHbtMaker headers
#include "StHbtMaker/StHbtPair.h"
#include "StHbtMaker/phys_constants.h"

// StHbtMakerUser headers
#include "StHbtMakerUser/fxtPairCutMonitor.h"

// C++ headers
#include <cstdio>
#include <string>

#ifdef __ROOT__
ClassImp(fxtPairCutMonitor)
#endif

//_________________
fxtPairCutMonitor::fxtPairCutMonitor(const char* name) :
  StHbtBaseCutMonitor(),
  mKt(nullptr),
  mPt1Pt2Qinv(nullptr),
  mFMRvsQinv(nullptr),
  mSLvsQinv(nullptr),
  mAveSepVsQinv(nullptr),
  mRValueVsQinv(nullptr),
  mDEtaDPhi(nullptr),
  mMinv(nullptr),
  mPtVsEta(nullptr) {

  // Constructor
  string s("fxtPairCutMonitor");
  string n(name);
  mKt = new TH1F( (s+n+"mKt").c_str(),"Kt;k_{T} (GeV/c)",
			           75, 0., 1.5);
  mPt1Pt2Qinv = new TH3F( (s+n+"mPt1Pt2Qinv").c_str(),
				                  "p_{T1} vs. p_{T2} vs. q_{inv};p_{T1} (GeV/c);p_{T2} (GeV/c);q_{inv} (GeV/c)",
				                  32, 0., 1.6, 32, 0., 1.6, 400, 0., 0.8);
  mFMRvsQinv = new TH2F( (s+n+"mFMRvsQinv").c_str(),
				                 "FMR vs. q_{inv};q_{Inv} (GeV/c);Fraction of merged rows",
				                 200, 0., 0.8, 100, 0., 1.);
  mSLvsQinv = new TH2F( (s+n+"mSLvsQinv").c_str(),
				                "SL vs. q_{inv};q_{inv} (GeV/c);Splitting level",
				                200, 0., 0.8, 32, -0.6, 1.);
  mAveSepVsQinv = new TH2F( (s+n+"mAveSepVsQinv").c_str(),
				                    "AveSep vs. q_{inv};q_{inv} (GeV/c); Average two-track separation (cm)",
				                    200, 0., 0.8, 100, 0., 50.);
  mRValueVsQinv = new TH2F( (s+n+"mRValueVsQinv").c_str(),
				                    "R=#sqrt{#Delta#eta+#Delta#phi} vs. q_{inv};q_{inv} (GeV/c);R",
				                    200, 0., 0.8, 200, 0., 2.);
  mDEtaDPhi = new TH2F( (s+n+"mDEtaDPhi").c_str(),
				                "#Delta#eta vs. #Delta#phi;#Delta#phi;#Delta#eta",
                        400, -2., 2., 300, -1.5, 1.5 );
  mMinv = new TH1F( (s+n+"mMinv").c_str(),"M_{inv};M_{inv} (GeV/c^{2});Entries",
                    200, 0., 2.);
  mPtVsEta = new TH2F( (s+n+"mPtVsEta").c_str(),
                       "p_{T} vs. #eta;#eta;p_{T} (GeV/c)",
                        60, -1.5, 1.5, 40, 0., 2.);
  mDEtaVsDPhiStarMin = new TH2F( (s+n+"mDEtaVsDPhiStarMin").c_str(),
                                 "#Delta#eta vs. #Delta#phi*min;#Delta#phi*min (rad);#Delta#eta",
                                 40, -0.2, 0.2, 40, -0.2, 0.2 );

  mPartMass = M_PION_PLUS;
}

//_________________
fxtPairCutMonitor::fxtPairCutMonitor( const  fxtPairCutMonitor& cutMoni) :
  StHbtBaseCutMonitor(cutMoni)  {
  // Copy constructor
  if (mKt) delete mKt;
  mKt = new TH1F( *cutMoni.mKt );
  if (mPt1Pt2Qinv) delete mPt1Pt2Qinv;
  mPt1Pt2Qinv = new TH3F( *cutMoni.mPt1Pt2Qinv );
  if (mFMRvsQinv) delete mFMRvsQinv;
  mFMRvsQinv = new TH2F( *cutMoni.mFMRvsQinv );
  if (mSLvsQinv) delete mSLvsQinv;
  mSLvsQinv = new TH2F( *cutMoni.mSLvsQinv );
  if (mAveSepVsQinv) delete mAveSepVsQinv;
  mAveSepVsQinv = new TH2F( *cutMoni.mAveSepVsQinv );
  if (mRValueVsQinv) delete mRValueVsQinv;
  mRValueVsQinv = new TH2F( *cutMoni.mRValueVsQinv );
  if (mDEtaDPhi) delete mDEtaDPhi;
  mDEtaDPhi = new TH2F( *cutMoni.mDEtaDPhi );
  if (mMinv) delete mMinv;
  mMinv = new TH1F( *cutMoni.mMinv );
  if (mPtVsEta) delete mPtVsEta;
  mPtVsEta = new TH2F( *cutMoni.mPtVsEta );
  if (mDEtaVsDPhiStarMin) delete mDEtaVsDPhiStarMin;
  mDEtaVsDPhiStarMin = new TH2F( *cutMoni.mDEtaVsDPhiStarMin );
  mPartMass = cutMoni.mPartMass;
}

//_________________
fxtPairCutMonitor fxtPairCutMonitor::operator=(const fxtPairCutMonitor& cutMoni) {
  // Assignment operator
  if ( this != &cutMoni ) {
    if (mKt) delete mKt;
    mKt = new TH1F( *cutMoni.mKt );
    if (mPt1Pt2Qinv) delete mPt1Pt2Qinv;
    mPt1Pt2Qinv = new TH3F( *cutMoni.mPt1Pt2Qinv );
    if (mFMRvsQinv) delete mFMRvsQinv;
    mFMRvsQinv = new TH2F( *cutMoni.mFMRvsQinv );
    if (mSLvsQinv) delete mSLvsQinv;
    mSLvsQinv = new TH2F( *cutMoni.mSLvsQinv );
    if (mAveSepVsQinv) delete mAveSepVsQinv;
    mAveSepVsQinv = new TH2F( *cutMoni.mAveSepVsQinv );
    if (mRValueVsQinv) delete mRValueVsQinv;
    mRValueVsQinv = new TH2F( *cutMoni.mRValueVsQinv );
    if (mDEtaDPhi) delete mDEtaDPhi;
    mDEtaDPhi = new TH2F( *cutMoni.mDEtaDPhi );
    if (mMinv) delete mMinv;
    mMinv = new TH1F( *cutMoni.mMinv );
    if (mPtVsEta) delete mPtVsEta;
    mPtVsEta = new TH2F( *cutMoni.mPtVsEta );
    if (mDEtaVsDPhiStarMin) delete mDEtaVsDPhiStarMin;
    mDEtaVsDPhiStarMin = new TH2F( *cutMoni.mDEtaVsDPhiStarMin );
  } // if ( this != cutMoni )

  return *this;
}

//_________________
fxtPairCutMonitor::~fxtPairCutMonitor(){
  if(mKt)         { delete mKt; mKt = nullptr; }
  if(mPt1Pt2Qinv) { delete mPt1Pt2Qinv; mPt1Pt2Qinv = nullptr; }
  if(mFMRvsQinv)  { delete mFMRvsQinv; mFMRvsQinv = nullptr; }
  if(mSLvsQinv)   { delete mSLvsQinv; mSLvsQinv = nullptr; }
  if(mAveSepVsQinv) { delete mAveSepVsQinv; mAveSepVsQinv = nullptr; }
  if(mRValueVsQinv) { delete mRValueVsQinv; mRValueVsQinv = nullptr; }
  if(mMinv)       { delete mMinv; mMinv = nullptr; }
  if(mDEtaDPhi)   { delete mDEtaDPhi; mDEtaDPhi = nullptr; }
  if(mPtVsEta)    { delete mPtVsEta; mPtVsEta = nullptr; }
  if(mDEtaVsDPhiStarMin) { delete mDEtaVsDPhiStarMin; mDEtaVsDPhiStarMin = nullptr; }
}

//_________________
void fxtPairCutMonitor::fill(const StHbtPair* pair) {
  // Fill cut monitor information

  mKt->Fill( pair->kT() );

  mPt1Pt2Qinv->Fill(  pair->track1()->track()->pt(),
            		      pair->track2()->track()->pt(),
            		      pair->qInv() );

  mFMRvsQinv->Fill( pair->qInv(), pair->fractionOfMergedRow() );

  mSLvsQinv->Fill( pair->qInv(), pair->splittingLevel() );

  mAveSepVsQinv->Fill( pair->qInv(), pair->nominalTpcAverageSeparation() );

  mRValueVsQinv->Fill( pair->qInv(), pair->rValue() );

  mDEtaDPhi->Fill( pair->deltaPhi(), pair->deltaEta() );

  mMinv->Fill( pair->mInv() );

  mPtVsEta->Fill( pair->eta(), pair->pT() );

  // For charged TRACKS only (call static function of the pair class)
  float dPhiStarMin = StHbtPair::calculateDPhiStarMin( pair->track1()->momentum(),
                                                       pair->track1()->track()->charge(),
                                                       pair->track2()->momentum(),
                                                       pair->track2()->track()->charge(),
                                                       0.1, 0.6, 2.,                           /* in meters */
                                                       pair->track1()->track()->bField() * 0.1 /* in Tesla */
                                                     );

  mDEtaVsDPhiStarMin->Fill( dPhiStarMin, pair->eta() );
}

//_________________
void fxtPairCutMonitor::writeOutHistos() {
  // Write all histograms
	mKt->Write();
	mPt1Pt2Qinv->Write();
	mFMRvsQinv->Write();
	mSLvsQinv->Write();
	mAveSepVsQinv->Write();
	mRValueVsQinv->Write();
	mDEtaDPhi->Write();
	mMinv->Write();
     mPtVsEta->Write();
     mDEtaVsDPhiStarMin->Write();
}

//_________________
TList* fxtPairCutMonitor::getOutputList() {
  // Prepare ouput list with histograms
  TList *outputList = new TList();

  outputList->Add(mKt);
  outputList->Add(mPt1Pt2Qinv);
  outputList->Add(mFMRvsQinv);
  outputList->Add(mSLvsQinv);
  outputList->Add(mAveSepVsQinv);
  outputList->Add(mRValueVsQinv);
  outputList->Add(mDEtaDPhi);
  outputList->Add(mMinv);
  outputList->Add(mPtVsEta);
  outputList->Add(mDEtaVsDPhiStarMin);

  return outputList;
}
