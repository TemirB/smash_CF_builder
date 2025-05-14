//
// Track cut monitor for basic analysis
//

// StHbtMaker headers
#include "StHbtMaker/StHbtTrack.h"
#include "StHbtMaker/phys_constants.h"

// StHbtMakerUser headers
#include "fxtTrackCutMonitor.h"

// C++ headers
#include <cstdio>
#include <string>

// ROOT headers
#include "TMath.h"

#ifdef __ROOT__
ClassImp(fxtTrackCutMonitor)
#endif

//_________________
fxtTrackCutMonitor::fxtTrackCutMonitor(const char* name,
				       const double ParticleMass) :
  StHbtBaseCutMonitor(),
  mDCAGlobal(nullptr),
  mNhits(nullptr),
  mP(nullptr),
  mPt(nullptr),
  mPVsNsigmaPion(nullptr),
  mPVsNsigmaKaon(nullptr),
  mPVsNsigmaProton(nullptr),
  mPVsNsigmaElectron(nullptr),
  mPvsDedx(nullptr),
  mRapidity(nullptr),
  mPseudoRapidity(nullptr),
  mPvsMassSqr(nullptr),
  mPvsInvBeta(nullptr),
  mPtVsEta(nullptr),
  mInvBetaDiffPionVsP(nullptr),
  mInvBetaDiffKaonVsP(nullptr),
  mInvBetaDiffProtonVsP(nullptr),
  mInvBetaDiffElectronVsP(nullptr),
  monMass(ParticleMass) {

  // Constructor
  string s("fxtTrackCutMonitor");
  string n(name);
  mDCAGlobal= new TH1F( (s+n+"mDCAGlobal").c_str(),
												"DCA Global; DCA Global (cm)",
												100, 0., 5.);
  mNhits = new TH1F( (s+n+"mNhits").c_str(),"nHits;nHits",
			     					 80, -0.5, 79.5);
  mP = new TH1F( (s+n+"mP").c_str(),"Momentum;p (GeV/c);Entries",
			  				 76, 0., 1.9);
  mPt = new TH1F( (s+n+"mPt").c_str(), "Transverse momentum;p_{T} (GeV/c);Entries",
			  					76, 0., 1.9);
  mPVsNsigmaPion = new TH2F( (s+n+"mPVsNsigmaPion").c_str(),
				     									"n#sigma(#pi) vs. p;p (GeV/c);n#sigma(#pi)",
				      								150, 0., 1.5, 2000, -10., 10.);
  mPVsNsigmaKaon = new TH2F( (s+n+"mPVsNsigmaKaon").c_str(),
				     									"n#sigma(K) vs. p;p (GeV/c);n#sigma(K)",
				     									150, 0., 1.5, 2000, -10., 10.);
  mPVsNsigmaProton = new TH2F( (s+n+"mPVsNsigmaProton").c_str(),
				    										"n#sigma(p) vs. p;p (GeV/c);n#sigma(p)",
																150, 0., 1.5, 2000, -10., 10.);
  mPVsNsigmaElectron = new TH2F( (s+n+"mPVsNsigmaElectron").c_str(),
				    										"n#sigma(p) vs. p;p (GeV/c);n#sigma(p)",
																150, 0., 1.5, 2000, -10., 10.);
  mPvsDedx= new TH2F( (s+n+"mPvsDedx").c_str(),
								      "dE/dx vs. momentum;p (GeV/c);dE/dx (keV/cm)",
								      76, 0.0, 1.9, 100, 0., 10.);
  mRapidity = new TH1F( (s+n+"mRapidity").c_str(), "Rapidity;y;Entries",
												56, -1.2, 1.2);
  mPseudoRapidity = new TH1F( (s+n+"mPseudoRapidity").c_str(), "Pseudorapidity;#eta;Entries",
				      								56, -1.2, 1.2);
  mPvsMassSqr = new TH2F( (s+n+"mPvsMassSqr").c_str(),
				  								"m^{2} vs. p_{T};p_{T} (GeV/c);m^{2} (GeV/c^{2})^{2}",
				   								76, 0., 1.9, 120, -0.1, 1.1);
  mPvsInvBeta = new TH2F( (s+n+"mPvsInvBeta").c_str(),
				  								"1/#beta vs. p;p (GeV/c);1/#beta",
				  								76, 0., 1.9, 60, 0.8, 2.);
  mPtVsEta  = new TH2F( (s+n+"mPtVsEta").c_str(), "#eta vs. p_{T};#eta;p_{T} (GeV/c)",
												44, -1.1, 1.1, 76, 0., 1.9);
  mInvBetaDiffPionVsP = new TH2F( (s+n+"mInvBetaDiffPionVsP").c_str(),
																	"1/#beta-1/#beta(#pi) vs. p;p (GeV/c);1/#beta-1/#beta(#pi)",
																	150, 0., 1.5, 2000, -0.1, 0.1);
	mInvBetaDiffKaonVsP = new TH2F( (s+n+"mInvBetaDiffKaonVsP").c_str(),
																	"1/#beta-1/#beta(K) vs. p;p (GeV/c);1/#beta-1/#beta(K)",
																	150, 0., 1.5, 2000, -0.1, 0.1);
	mInvBetaDiffProtonVsP = new TH2F( (s+n+"mInvBetaDiffProtonVsP").c_str(),
																		"1/#beta-1/#beta(p) vs. p;p (GeV/c);1/#beta-1/#beta(p)",
																		150, 0., 1.5, 2000, -0.1, 0.1);
	mInvBetaDiffElectronVsP = new TH2F( (s+n+"mInvBetaDiffElectronVsP").c_str(),
																		"1/#beta-1/#beta(e) vs. p;p (GeV/c);1/#beta-1/#beta(e)",
																		150, 0., 1.5, 2000, -0.1, 0.1);
}

//_________________
fxtTrackCutMonitor::fxtTrackCutMonitor(const fxtTrackCutMonitor& cutMoni) :
	StHbtBaseCutMonitor(cutMoni) {
	// Copy constructor
	if (mDCAGlobal) delete mDCAGlobal;
  mDCAGlobal = new TH1F(*(cutMoni.mDCAGlobal));
	if (mNhits) delete mNhits;
  mNhits = new TH1F(*(cutMoni.mNhits));
	if (mP) delete mP;
  mP = new TH1F(*(cutMoni.mP));
	if (mPt) delete mPt;
  mPt = new TH1F(*(cutMoni.mPt));
	if (mPVsNsigmaPion) delete mPVsNsigmaPion;
  mPVsNsigmaPion = new TH2F(*(cutMoni.mPVsNsigmaPion));
	if (mPVsNsigmaKaon) delete mPVsNsigmaKaon;
  mPVsNsigmaKaon = new TH2F(*(cutMoni.mPVsNsigmaKaon));
	if (mPVsNsigmaProton) delete mPVsNsigmaProton;
  mPVsNsigmaProton = new TH2F(*(cutMoni.mPVsNsigmaProton));
	if (mPVsNsigmaElectron) delete mPVsNsigmaElectron;
  mPVsNsigmaElectron = new TH2F(*(cutMoni.mPVsNsigmaElectron));
	if (mPvsDedx) delete mPvsDedx;
  mPvsDedx =new TH2F(*(cutMoni.mPvsDedx));
	if (mRapidity) delete mRapidity;
  mRapidity= new TH1F(*(cutMoni.mRapidity));
	if (mPseudoRapidity) delete mPseudoRapidity;
  mPseudoRapidity = new TH1F(*(cutMoni.mPseudoRapidity));
	if (mPvsMassSqr) delete mPvsMassSqr;
  mPvsMassSqr = new TH2F(*(cutMoni.mPvsMassSqr));
	if (mPvsInvBeta) delete mPvsInvBeta;
  mPvsInvBeta = new TH2F(*(cutMoni.mPvsInvBeta));
	if (mPtVsEta) delete mPtVsEta;
  mPtVsEta = new TH2F(*(cutMoni.mPtVsEta));
	if (mInvBetaDiffPionVsP) delete mInvBetaDiffPionVsP;
	mInvBetaDiffPionVsP = new TH2F(*(cutMoni.mInvBetaDiffPionVsP));
	if (mInvBetaDiffKaonVsP) delete mInvBetaDiffKaonVsP;
	mInvBetaDiffKaonVsP = new TH2F(*(cutMoni.mInvBetaDiffKaonVsP));
	if (mInvBetaDiffProtonVsP) delete mInvBetaDiffProtonVsP;
	mInvBetaDiffProtonVsP = new TH2F(*(cutMoni.mInvBetaDiffProtonVsP));
	if (mInvBetaDiffElectronVsP) delete mInvBetaDiffElectronVsP;
	mInvBetaDiffElectronVsP = new TH2F(*(cutMoni.mInvBetaDiffElectronVsP));
  monMass = cutMoni.monMass;
}

//_________________
fxtTrackCutMonitor fxtTrackCutMonitor::operator=(const fxtTrackCutMonitor& cutMoni) {
	// Assignment operator
	if (this != &cutMoni) {
		if (mDCAGlobal) delete mDCAGlobal;
	  mDCAGlobal = new TH1F(*(cutMoni.mDCAGlobal));
		if (mNhits) delete mNhits;
	  mNhits = new TH1F(*(cutMoni.mNhits));
		if (mP) delete mP;
	  mP = new TH1F(*(cutMoni.mP));
		if (mPt) delete mPt;
	  mPt = new TH1F(*(cutMoni.mPt));
		if (mPVsNsigmaPion) delete mPVsNsigmaPion;
	  mPVsNsigmaPion = new TH2F(*(cutMoni.mPVsNsigmaPion));
		if (mPVsNsigmaKaon) delete mPVsNsigmaKaon;
	  mPVsNsigmaKaon = new TH2F(*(cutMoni.mPVsNsigmaKaon));
		if (mPVsNsigmaProton) delete mPVsNsigmaProton;
	  mPVsNsigmaProton = new TH2F(*(cutMoni.mPVsNsigmaProton));
		if (mPVsNsigmaElectron) delete mPVsNsigmaElectron;
	  mPVsNsigmaElectron = new TH2F(*(cutMoni.mPVsNsigmaElectron));
		if (mPvsDedx) delete mPvsDedx;
	  mPvsDedx =new TH2F(*(cutMoni.mPvsDedx));
		if (mRapidity) delete mRapidity;
	  mRapidity= new TH1F(*(cutMoni.mRapidity));
		if (mPseudoRapidity) delete mPseudoRapidity;
	  mPseudoRapidity = new TH1F(*(cutMoni.mPseudoRapidity));
		if (mPvsMassSqr) delete mPvsMassSqr;
	  mPvsMassSqr = new TH2F(*(cutMoni.mPvsMassSqr));
		if (mPvsInvBeta) delete mPvsInvBeta;
	  mPvsInvBeta = new TH2F(*(cutMoni.mPvsInvBeta));
		if (mPtVsEta) delete mPtVsEta;
	  mPtVsEta = new TH2F(*(cutMoni.mPtVsEta));
		if (mInvBetaDiffPionVsP) delete mInvBetaDiffPionVsP;
		mInvBetaDiffPionVsP = new TH2F(*(cutMoni.mInvBetaDiffPionVsP));
		if (mInvBetaDiffKaonVsP) delete mInvBetaDiffKaonVsP;
		mInvBetaDiffKaonVsP = new TH2F(*(cutMoni.mInvBetaDiffKaonVsP));
		if (mInvBetaDiffProtonVsP) delete mInvBetaDiffProtonVsP;
		mInvBetaDiffProtonVsP = new TH2F(*(cutMoni.mInvBetaDiffProtonVsP));
		if (mInvBetaDiffElectronVsP) delete mInvBetaDiffElectronVsP;
		mInvBetaDiffElectronVsP = new TH2F(*(cutMoni.mInvBetaDiffElectronVsP));
	  monMass = cutMoni.monMass;
	} // if (this != &c)

	return *this;
}

//_________________
fxtTrackCutMonitor::~fxtTrackCutMonitor(){
  if(mDCAGlobal) { delete mDCAGlobal; mDCAGlobal = nullptr; }
  if(mNhits)     { delete mNhits; mNhits = nullptr; }
  if(mP)         { delete mP; mP = nullptr; }
  if(mPt)        { delete mPt; mPt = nullptr; }
  if(mPVsNsigmaPion)       { delete mPVsNsigmaPion; mPVsNsigmaPion = nullptr; }
  if(mPVsNsigmaKaon)       { delete mPVsNsigmaKaon; mPVsNsigmaKaon = nullptr; }
  if(mPVsNsigmaProton)     { delete mPVsNsigmaProton; mPVsNsigmaProton = nullptr; }
  if(mPVsNsigmaElectron)     { delete mPVsNsigmaElectron; mPVsNsigmaElectron = nullptr; }
  if(mPvsDedx)              { delete mPvsDedx; mPvsDedx = nullptr; }
  if(mRapidity)             { delete mRapidity; mRapidity = nullptr; }
  if(mPseudoRapidity)       { delete mPseudoRapidity; mPseudoRapidity = nullptr; }
  if(mPvsMassSqr)           { delete mPvsMassSqr; mPvsMassSqr = nullptr; }
  if(mPvsInvBeta)           { delete mPvsInvBeta; mPvsInvBeta = nullptr; }
  if(mPtVsEta)              { delete mPtVsEta; mPtVsEta = nullptr; }
	if(mInvBetaDiffPionVsP)   { delete mInvBetaDiffPionVsP; mInvBetaDiffPionVsP = nullptr; }
	if(mInvBetaDiffKaonVsP)   { delete mInvBetaDiffKaonVsP; mInvBetaDiffKaonVsP = nullptr; }
	if(mInvBetaDiffProtonVsP) { delete mInvBetaDiffProtonVsP; mInvBetaDiffProtonVsP = nullptr; }
	if(mInvBetaDiffElectronVsP) { delete mInvBetaDiffElectronVsP; mInvBetaDiffElectronVsP = nullptr; }
}

//_________________
void  fxtTrackCutMonitor::fill(const StHbtTrack* track){

  /*
    float TPhi = atan2(track->P().y(),track->P().x());
    if(TPhi<0.0) { TPhi += 2.*TMath::Pi(); }
    TPhi *= 180./TMath::Pi();
  */

  mDCAGlobal->Fill( track->gDCA().Mag() );
  mNhits->Fill( track->nHits() );
  mP->Fill( track->p().Mag() );
  mPt->Fill( track->pt() );
  mPVsNsigmaPion->Fill( track->ptot(), track->nSigmaPion() );
  mPVsNsigmaKaon->Fill( track->ptot(), track->nSigmaKaon() );
  mPVsNsigmaProton->Fill( track->ptot(), track->nSigmaProton() );
  mPVsNsigmaElectron->Fill( track->ptot(), track->nSigmaElectron() );
  mPvsDedx->Fill( track->ptot(), track->dEdxInKeV() );
  mPseudoRapidity->Fill( track->eta() );
  mPvsMassSqr->Fill( track->ptot(), track->massSqr() );
  mPvsInvBeta->Fill( track->ptot(), (1./track->beta()) );
  mPtVsEta->Fill( track->eta(), track->pt() );
	mInvBetaDiffPionVsP->Fill( track->ptot(),
														 track->invBeta() -
														 TMath::Sqrt( M_PION_PLUS * M_PION_PLUS +
															 						track->p().Mag2() ) / track->ptot() );
	mInvBetaDiffKaonVsP->Fill( track->ptot(),
														 track->invBeta() -
														 TMath::Sqrt( M_KAON_PLUS * M_KAON_PLUS +
															 						track->p().Mag2() ) / track->ptot() );
	mInvBetaDiffProtonVsP->Fill( track->ptot(),
															 track->invBeta() -
															 TMath::Sqrt( M_PROTON * M_PROTON +
																						track->p().Mag2() ) / track->ptot() );
	mInvBetaDiffElectronVsP->Fill( track->ptot(),
															 track->invBeta() -
															 TMath::Sqrt( M_ELECTRON * M_ELECTRON +
																						track->p().Mag2() ) / track->ptot() );

}

//_________________
void fxtTrackCutMonitor::writeOutHistos() {
  // Write all histograms
	mDCAGlobal->Write();
	mNhits->Write();
	mP->Write();
	mPt->Write();
	mPVsNsigmaPion->Write();
	mPVsNsigmaKaon->Write();
	mPVsNsigmaProton->Write();
	mPVsNsigmaElectron->Write();
	mPvsDedx->Write();
	mRapidity->Write();
	mPseudoRapidity->Write();
	mPvsMassSqr->Write();
	mPvsInvBeta->Write();
	mPtVsEta->Write();
	mInvBetaDiffPionVsP->Write();
	mInvBetaDiffKaonVsP->Write();
	mInvBetaDiffProtonVsP->Write();
	mInvBetaDiffElectronVsP->Write();
}

//_________________
TList* fxtTrackCutMonitor::getOutputList() {
  // Prepare ouput list with histograms
  TList *outputList = new TList();

  outputList->Add(mDCAGlobal);
  outputList->Add(mNhits);
  outputList->Add(mP);
  outputList->Add(mPt);
  outputList->Add(mPVsNsigmaPion);
  outputList->Add(mPVsNsigmaKaon);
  outputList->Add(mPVsNsigmaProton);
  outputList->Add(mPVsNsigmaElectron);
  outputList->Add(mPvsDedx);
	outputList->Add(mRapidity);
  outputList->Add(mPseudoRapidity);
  outputList->Add(mPvsMassSqr);
  outputList->Add(mPvsInvBeta);
  outputList->Add(mPtVsEta);
  outputList->Add(mInvBetaDiffPionVsP);
	outputList->Add(mInvBetaDiffKaonVsP);
  outputList->Add(mInvBetaDiffProtonVsP);
  outputList->Add(mInvBetaDiffElectronVsP);

  return outputList;
}
