/**
 * \brief Example of how to read a file (list of files) using StFemtoEvent classes
 *
 * RunFemtoDstAnalyzer.C is an example of reading STAR FemtoDst format.
 * One can use either FemtoDst file or a list of femtoDst files (inFile.lis or
 * inFile.list) as an input, and preform physics analysis
 *
 * \author Grigory Nigmatkulov
 * \date May 29, 2018
 */

// This is needed for calling standalone classes (not needed on RACF)
#define _VANILLA_ROOT_

// C++ headers
#include <iostream>

// ROOT headers
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TSystem.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TMath.h"
#include "TString.h"
#include "TVector3.h"
#include "TLorentzVector.h"

// FemtoDst headers
#include "../StFemtoDstReader.h"
#include "../StFemtoDst.h"
#include "../StFemtoEvent.h"
#include "../StFemtoTrack.h"
#include "../StFemtoV0.h"
#include "../StFemtoXi.h"

// Load libraries (for ROOT_VERSTION_CODE >= 393215)
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,0,0)
R__LOAD_LIBRARY(../libStFemtoDst)
#endif

// Forward declarations
Bool_t isGoodEvent(const TVector3& vtx, const Float_t& vpdVz);
Bool_t isGoodTrack(const TVector3& vect, const Int_t& nHits,
                   const Int_t& nHitsPoss);

const Float_t electron_mass = 0.0005485799;
const Float_t pion_mass = 0.13957061;
const Float_t kaon_mass = 0.493677;
const Float_t proton_mass = 0.9382720813;

const Float_t electron_mass_sqr = 0.000000301;
const Float_t pion_mass_sqr = 0.019479955;
const Float_t kaon_mass_sqr = 0.24371698;
const Float_t proton_mass_sqr = 0.880354499;


// inFile - is a name of name.FemtoDst.root file or a name
//          of a name.lis(t) files that contains a list of
//          name1.FemtoDst.root files
//_________________
void FemtoDstAnalyzer(const Char_t *inFile = "st_physics_12150008_raw_4030001.femtoDst.root",
                      const Char_t *oFileName = "oTest.root") {

  std::cout << "Hi! Lets do some physics, Master!" << std::endl;

  Int_t runIdBins = 2000000;
  Int_t runIdRange[2] = { 11000000, 13000000 };

  gSystem->Load("./libStFemtoDst.so");
  #if ROOT_VERSION_CODE < ROOT_VERSION(6,0,0)
    gSystem->Load("./libStFemtoDst.so");
  #endif

  StFemtoDstReader* femtoReader = new StFemtoDstReader(inFile);
  femtoReader->Init();

  //Long64_t events2read = femtoReader->chain()->GetEntries();

  // This is a way if you want to spead up IO
  std::cout << "Explicit read status for some branches" << std::endl;
  femtoReader->SetStatus("*",0);
  femtoReader->SetStatus("Event",1);
  femtoReader->SetStatus("Track",1);
  std::cout << "Status has been set" << std::endl;

  std::cout << "Now I know what to read, Master!" << std::endl;

  if( !femtoReader->chain() ) {
    std::cout << "No chain has been found." << std::endl;
  }
  Long64_t eventsInTree = femtoReader->tree()->GetEntries();
  std::cout << "eventsInTree: "  << eventsInTree << std::endl;
  Long64_t events2read = femtoReader->chain()->GetEntries();

  std::cout << "Number of events to read: " << events2read << std::endl;

  TFile *oFile = new TFile(oFileName, "RECREATE");

  // Histogramming
  // Event
  TH1D *hRefMult = new TH1D("hRefMult", "Reference multiplicity;RefMult;Entries",
			                      600, -0.5, 599.5);
  TH2D *hVtxXvsY = new TH2D("hVtxXvsY", "hVtxXvsY;x (cm);y (cm)",
			                      200,-10.,10.,200,-10.,10.);
  TH1D *hVtxZ = new TH1D("hVtxZ","hVtxZ;z (cm); Entries",
			                   140, -70., 70.);
  TH1D *hRefMult2 = new TH1D("hRefMult2","Reference multiplicity in |#eta|<1;RefMult2;Entries",
                             600, -0.5, 599.5);
  TH1D *hGRefMult = new TH1D("hGRefMult","Reference multiplicity of global tracks;gRefMult;Entries",
                             800, -0.5, 799.5);
  TH1D *hNumberOfPrimaries = new TH1D("hNumberOfPrimaries","Number of primary tracks;Number of primary tracks;Entries",
                                      600, -0.5, 599.5);
  TH1D *hNumberOfGlobals = new TH1D("hNumberOfGlobals","Number of global tracks;Number of global tracks;Entries",
                                    600, -0.5, 599.5);
  TH1D *hCent9 = new TH1D("hCent9","Centralitity;Cent9;Entries",
                          13, -1.5, 11.5);
  TH1D *hCent16 = new TH1D("hCent16","Centralitity;Cent16;Entries",
                          19, -1.5, 17.5);
  TH1D *hBTofHit = new TH1D("hBTofHit","Number of hits in TOF;bTofTrayMult;Entries",
                            600, -0.5, 599.5);
  TH1D *hBTofMatched = new TH1D("hBTofMatched","Number of TOF-matched tracks;bTofMatched;Entries",
                                400, -0.5, 399.5);
  TH1D *hBemcMatched = new TH1D("hBemcMatched","Number of BEMC-matched tracks;bEmcMatched;Entries",
                                400, -0.5, 399.5);
  TH1D *hRanking = new TH1D("hRanking","Primary vertex ranking;Primary vertex ranking;Entries",
                            21, -10.5, 10.5);
  TH2D *hVpdVzDiffVsVz = new TH2D("hVpdVzDiffVsVz","v_{z}(TPC) - v_{z}(VPD) vs. v_{z}(TPC);v_{z}(TPC);v_{z}(TPC) - v_{z}(VPD)",
                                  280, -70., 70., 80, -20., 20.);
  TH2D *hBTofTrayMultVsRefMult = new TH2D("hBTofTrayMultVsRefMult","TOF tray multiplicity vs. refMult;refMult;bTofTrayMult",
                                          600, -0.5, 599.5, 600, -0.5, 599.5);
  TH2D *hBTofMatchedVsRefMult = new TH2D("hBTofMatchedVsRefMult","TOF-matched tracks vs. refMult;refMult;TOF-matched",
                                          600, -0.5, 599.5, 400, -0.5, 399.5);
  TH1D *hTransSphericity = new TH1D("hTransSphericity","Transverse sphericity;Sphericity;Entries",
                                    10, 0., 1.);
  TH1D *hTransSphericity2 = new TH1D("hTransSphericity2","Transverse sphericity in |#eta|<1;Sphericity;Entries",
                                     10, 0., 1.);
  TH1D *hNumberOfVertices = new TH1D("hNumberOfVertices","Number of primary vertices;Number of primary vertices;Entries",
                                     15, -0.5, 14.5);
  TProfile *hEventProfile[8];
  hEventProfile[0] = new TProfile("hEventProfile_0","Profile of refMult;Run ID;<refMult>",
                                  runIdBins, runIdRange[0], runIdRange[1] );
  hEventProfile[1] = new TProfile("hEventProfile_1","Profile of TOF tray multiplicity;Run ID;<bTofTrayMultiplicity>",
                                  runIdBins, runIdRange[0], runIdRange[1] );
  hEventProfile[2] = new TProfile("hEventProfile_2","Profile of TOF-matched tracks;Run ID;<bTofMatched>",
                                            runIdBins, runIdRange[0], runIdRange[1] );
  hEventProfile[3] = new TProfile("hEventProfile_3","Profile of number of primary tracks;Run ID;<nPrimTracks>",
                                            runIdBins, runIdRange[0], runIdRange[1] );
  hEventProfile[4] = new TProfile("hEventProfile_4","Profile of number of global tracks;Run ID;<nGlobTracks>",
                                            runIdBins, runIdRange[0], runIdRange[1] );
  hEventProfile[5] = new TProfile("hEventProfile_5","Profile of ZDC ADC;Run ID; <ADC_{ZDC}>",
                                            runIdBins, runIdRange[0], runIdRange[1] );
  hEventProfile[6] = new TProfile("hEventProfile_6","Profile of BBC ADC;Run ID; <ADC_{BBC}>",
                                            runIdBins, runIdRange[0], runIdRange[1] );
  hEventProfile[7] = new TProfile("hEventProfile_7","Profile of primary vertex Z position;Run ID; <VtxZ> (cm)",
                                            runIdBins, runIdRange[0], runIdRange[1] );
  for(int iHist=0; iHist<8; iHist++) {
    Int_t mColor = 1;
    hEventProfile[iHist]->SetMarkerStyle(20);    // filled circle
    hEventProfile[iHist]->SetMarkerColor(mColor);
    hEventProfile[iHist]->SetMarkerSize(1.1);
    hEventProfile[iHist]->SetLineWidth(2);
    hEventProfile[iHist]->SetLineColor(mColor);  // black
  }

  // Track
  TH1D *hGlobalPtot = new TH1D("hGlobalPtot","Global track momentum;p (GeV/c);Entries",
                  			       200, 0., 2. );
  TH1D *hPrimaryPtot = new TH1D("hPrimaryPtot","Primary track momentum;p (GeV/c);Entries",
                    			      200, 0., 2. );
  TH1D *hGlobalPt = new TH1D("hGlobalPt","Global track transverse momentum;p_{T} (GeV/c)",
                        		  200, 0., 2.);
  TH1D *hPrimaryPt = new TH1D("hPrimaryPt","Primary track transverse momentum;p_{T} (GeV/c)",
                        		  200, 0., 2.);
  TH1D *hNHits = new TH1D("hNHits","Number of hits;nHits;Entries", 80, -0.5, 79.5);
  TH1D *hNHitsRatio = new TH1D("hNHitsRatio","nHitsFit to nHitsPoss ratio;nHitsFit/nHitsRatio;Entries",
                               10, 0., 1. );
  TH1D *hChi2 = new TH1D("hChi2","#chi^{2} of the track;#chi^{2};Entries",
                         200, 0., 20.);
  TH1D *hDca = new TH1D("hDca","DCA to primary vertex;DCA (cm);Entries",
                        100, 0., 10.);
  TH2D *hDcaVsPt = new TH2D("hDcaVsPt","charge*p_{T} vs. DCA;charge * p_{T} (GeV/c);DCA (cm)",
                            840, -2.1, 2.1, 100, 0., 10.);
  TH1D *hPhi = new TH1D("hPhi","Azimuthal angle distribution;#phi;Entries",
                        640, -3.2, 3.2 );
  TH1D *hEta = new TH1D("hEta","Track pseudorapidity;#eta;Entries", 220, -1.1, 1.1 );
  TH1D *hEtaG = new TH1D("hEtaG","Track pseudorapidity of global track;#eta;Entires", 220, -1., 1. );
  TH2D *hPtVsEta = new TH2D("hPtVsEta","p_{T} vs. #eta of primary track;#eta;p_{T} (GeV/c)",
                            220, -1.1, 1.1, 80, 0.05, 2.05);
  TH2D *hPrimaryPhiVsPt[2];
  for(int i=0; i<2; i++) {
    hPrimaryPhiVsPt[i] = new TH2D(Form("hPrimaryPhiVsPt_%d",i),
				 Form("#phi vs. p_{T} for charge: %d;p_{T} (GeV/c);#phi (rad)", (i==0) ? 1 : -1),
				 300, 0., 3., 630, -3.15, 3.15 );
  }
  TH1D* hDedx = new TH1D("hDedx","dE/dx;dE/dx (keV/cm);Entries",
                         125, 0., 12.5);
  TH2D *hDedxVsPt = new TH2D("hDedxVsPt", "dE/dx vs. charge*p_{T};charge * p_{T} (GeV/c);dE/dx (keV/cm)",
                             840, -2.1, 2.1, 600, 0., 12.);
  TH2D *hNSigmaPionVsPt = new TH2D("hNSigmaPionVsPt","n#sigma(#pi) vs. charge*p_{T};charge * p_{T} (GeV/c);n#sigma(#pi)",
                                   840, -2.1, 2.1, 200, -10., 10.);
  TH2D *hNSigmaElectronVsPt = new TH2D("hNSigmaElectronVsPt","n#sigma(e) vs. charge*p_{T};charge * p_{T} (GeV/c);n#sigma(e)",
                        				       840, -2.1, 2.1, 200, -10., 10.);
  TH2D *hNSigmaKaonVsPt = new TH2D("hNSigmaKaonVsPt","n#sigma(K) vs. charge*p_{T};charge * p_{T} (GeV/c);n#sigma(K)",
                  			           840, -2.1, 2.1, 200, -10., 10.);
  TH2D *hNSigmaProtonVsPt = new TH2D("hNSigmaProtonVsPt","n#sigma(p) vs. charge*p_{T};charge * p_{T} (GeV/c);n#sigma(p)",
                        				     840, -2.1, 2.1, 200, -10., 10.);

  TH2D *hDedxVsPtPID[4];
  for ( int i=0; i<4; i++ ) {
    TString name = "hDedxVsPtPID_";
    name += i;
    TString title = "dE/dx vs. charge*p_{T} ";
    switch (i) {
      case 0: title += "|n#sigma(e)| #leq 2;"; break;
      case 1: title += "|n#sigma(#pi)| #leq 2;"; break;
      case 2: title += "|n#sigma(K)| #leq 2;"; break;
      case 3: title += "|n#sigma(p)| #leq 2;"; break;
      default: title += "unknown PID;";
    }
    title += "charge*p_{T} (GeV/c);dE/dx (keV/cm)";
    hDedxVsPtPID[i] = new TH2D(name.Data(), title.Data(),
                               840, -2.1, 2.1, 600, 0., 12.);
  }

  // TofPidTrait
  TH1D *hTofBeta = new TH1D("hTofBeta","BTofPidTraits #beta;#beta",
                  			    2000, 0., 2.);
  TH2D *hInvBetaVsPt = new TH2D("hInvBetaVsPt","1/#beta vs. charge*p_{T};charge * p_{T} (GeV/c);1/#beta",
                                840, -2.1, 2.1, 200, 0.8, 2.8);
  TH1D *hMassSqr = new TH1D("hMassSqr","m^{2};m^{2} (GeV/c^{2})^{2};dN/dm^{2} (entries)",
                            520, -0.1, 5.1 );
  TH2D *hMassSqrVsPt = new TH2D("hMassSqrVsPt","m^{2} vs. charge*p_{T};charge * p_{T} (GeV/c);m^{2} (GeV/c^{2})^{2}",
                                840, -2.1, 2.1, 200, -0.2, 1.8);
  TH2D *hDedxVsMassSqr[2];
  hDedxVsMassSqr[0] = new TH2D("hDedxVsMassSqr_0","dE/dx vs. mass^{2} charge>0;m^{2} (GeV/c^{2})^{2};dE/dx (keV/cm)",
			       440, -0.4, 1.8, 250, 0., 12.5 );
  hDedxVsMassSqr[1] = new TH2D("hDedxVsMassSqr_1","dE/dx vs. mass^{2} charge<0;m^{2} (GeV/c^{2})^{2};dE/dx (keV/cm)",
			       440, -0.4, 1.8, 250, 0., 12.5 );
  TH2D *hInvBetaDiffElectronVsPt = new TH2D("hInvBetaDiffElectronVsPt","1/#beta - 1/#beta(electron) vs. charge*p_{T};charge * p_{T} (GeV/c);1/#beta - 1/#beta(e)",
                                            840, -2.1, 2.1, 200, -0.1, 0.1);
  TH2D *hInvBetaDiffPionVsPt = new TH2D("hInvBetaDiffPionVsPt","1/#beta - 1/#beta(pion) vs. charge*p_{T};charge * p_{T} (GeV/c);1/#beta - 1/#beta(#pi)",
                                            840, -2.1, 2.1, 200, -0.1, 0.1);
  TH2D *hInvBetaDiffKaonVsPt = new TH2D("hInvBetaDiffKaonVsPt","1/#beta - 1/#beta(kaon) vs. charge*p_{T};charge * p_{T} (GeV/c);1/#beta - 1/#beta(K)",
                                            840, -2.1, 2.1, 200, -0.1, 0.1);
  TH2D *hInvBetaDiffProtonVsPt = new TH2D("hInvBetaDiffProtonVsPt","1/#beta - 1/#beta(p) vs. charge*p_{T};charge * p_{T} (GeV/c);1/#beta - 1/#beta(p)",
                                          840, -2.1, 2.1, 200, -0.1, 0.1);
  TProfile *hTrackProfile[6];
  hTrackProfile[0] = new TProfile("hTrackProfile_0","Profile of track #phi;Run ID;<#phi>",
                                           runIdBins, runIdRange[0], runIdRange[1] );
  hTrackProfile[1] = new TProfile("hTrackProfile_1","Profile of track p_{T};Run ID;<p_{T}>",
                                           runIdBins, runIdRange[0], runIdRange[1] );
  hTrackProfile[2] = new TProfile("hTrackProfile_2","Profile of track nHits;Run ID;<nHits>",
                                          runIdBins, runIdRange[0], runIdRange[1] );
  hTrackProfile[3] = new TProfile("hTrackProfile_3","Profile of track DCA;Run ID;<DCA>",
                                          runIdBins, runIdRange[0], runIdRange[1] );
  hTrackProfile[4] = new TProfile("hTrackProfile_4","Profile of track #beta;Run ID;<#beta>",
                                             runIdBins, runIdRange[0], runIdRange[1] );
  hTrackProfile[5] = new TProfile("hTrackProfile_5","Profile of track dE/dx;Run ID;<dE/dx> (keV/cm)",
                                            runIdBins, runIdRange[0], runIdRange[1] );

  for(int iTrk=0; iTrk<6; iTrk++) {
    Int_t mColor = 1;
    hTrackProfile[iTrk]->SetMarkerStyle(20);    // filled circle
    hTrackProfile[iTrk]->SetMarkerColor(mColor);
    hTrackProfile[iTrk]->SetMarkerSize(1.1);
    hTrackProfile[iTrk]->SetLineWidth(2);
    hTrackProfile[iTrk]->SetLineColor(mColor);  // black
  }

  Int_t eventCounter = 0;
  Int_t hundredIter = 0;
  // Loop over events
  for(Long64_t iEvent=0; iEvent<events2read; iEvent++) {

    eventCounter++;
    if( eventCounter >= 100000 ) {
      eventCounter = 0;
      hundredIter++;
      std::cout << "Working on event #[" << (hundredIter * 100000)
        	      << "/" << events2read << "]" << std::endl;
    }


    Bool_t readEvent = femtoReader->readFemtoEvent(iEvent);
    if( !readEvent ) {
      std::cout << "Something went wrong, Master! Nothing to analyze..." << std::endl;
      break;
    }

    // Retrieve femtoDst
    StFemtoDst *dst = femtoReader->femtoDst();

    // Retrieve event information
    StFemtoEvent *event = dst->event();
    if( !event ) {
      std::cout << "Something went wrong, Master! Event is hiding from me..." << std::endl;
      break;
    }

    TVector3 pVtx = event->primaryVertex();

    // Simple event cut
    if ( !isGoodEvent(pVtx, event->vpdVz() ) ) continue;

    // Fill event histograms
    hRefMult->Fill( event->refMult() );
    hVtxXvsY->Fill( event->primaryVertex().X(), event->primaryVertex().Y() );
    hVtxZ->Fill( event->primaryVertex().Z() );
    hRefMult2->Fill( event->refMult2() );
    hGRefMult->Fill( event->gRefMult() );
    hNumberOfPrimaries->Fill( event->numberOfPrimaryTracks() );
    hNumberOfGlobals->Fill( event->numberOfGlobalTracks() );
    hCent9->Fill( event->cent9() );
    hCent16->Fill( event->cent16() );
    hBTofHit->Fill( event->numberOfBTofHit() );
    hBTofMatched->Fill( event->numberOfTofMatched() );
    hBemcMatched->Fill( event->numberOfBEMCMatched() );
    hRanking->Fill( event->ranking() );
    hVpdVzDiffVsVz->Fill( event->primaryVertex().Z(),
                          event->primaryVertex().Z() - event->vpdVz() );
    hBTofTrayMultVsRefMult->Fill( event->refMult(),
                                  event->numberOfBTofHit() );
    hBTofMatchedVsRefMult->Fill( event->refMult(),
                                event->numberOfTofMatched() );
    hTransSphericity->Fill( event->transverseSphericity() );
    hTransSphericity2->Fill( event->transverseSphericity2() );
    hNumberOfVertices->Fill( event->numberOfPrimaryVertices() );
    hEventProfile[0]->Fill( event->runId(), event->gRefMult() );
    hEventProfile[1]->Fill( event->runId(), event->numberOfBTofHit() );
    hEventProfile[2]->Fill( event->runId(), event->numberOfTofMatched() );
    hEventProfile[3]->Fill( event->runId(), event->numberOfPrimaryTracks() );
    hEventProfile[4]->Fill( event->runId(), event->numberOfGlobalTracks() );
    hEventProfile[5]->Fill( event->runId(), event->zdcSumAdcEast() + event->zdcSumAdcWest() );
    Float_t bbcAdcSum = 0;
    for( Int_t iTile=0; iTile<24; iTile++ ) {
      bbcAdcSum += event->bbcAdcEast(iTile);
      bbcAdcSum += event->bbcAdcWest(iTile);
    }
    hEventProfile[6]->Fill( event->runId(), bbcAdcSum );
    hEventProfile[7]->Fill( event->runId(), pVtx.Z() );

    // Track analysis
    Int_t nTracks = dst->numberOfTracks();

    // Track loop
    for(Int_t iTrk=0; iTrk<nTracks; iTrk++) {

      // Retrieve i-th femto track
      StFemtoTrack *femtoTrack = dst->track(iTrk);

      if (!femtoTrack) continue;
      //std::cout << "Track #[" << (iTrk+1) << "/" << nTracks << "]"  << std::endl;

      if ( !femtoTrack->isPrimary() ) continue;

      // Simple single-track cut
      if( !isGoodTrack( femtoTrack->pMom(), femtoTrack->nHits(),
                        femtoTrack->nHitsPoss() ) ) {
        continue;
      }

      // Fill track histograms
      hGlobalPtot->Fill( femtoTrack->gMom().Mag() );
      hPrimaryPtot->Fill( femtoTrack->pMom().Mag() );
      hGlobalPt->Fill( femtoTrack->gMom().Pt() );
      hPrimaryPt->Fill( femtoTrack->pMom().Pt() );
      hNHits->Fill( femtoTrack->nHits() );
      hNHitsRatio->Fill( (Float_t)femtoTrack->nHitsFit()/femtoTrack->nHitsPoss() );
      hChi2->Fill( femtoTrack->chi2() );
      hDca->Fill( femtoTrack->gDCA( pVtx.X(), pVtx.Y(), pVtx.Z() ) );
      hDcaVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                      femtoTrack->gDCA( pVtx.X(), pVtx.Y(), pVtx.Z() ) );
      hPtVsEta->Fill( femtoTrack->pMom().Eta(), femtoTrack->pMom().Pt() );
      hPhi->Fill( femtoTrack->pMom().Phi() );
      hEta->Fill( femtoTrack->pMom().Eta() );
      hEtaG->Fill( femtoTrack->gMom().Eta() );
      hDedx->Fill( femtoTrack->dEdx() * 1e6 );
      hDedxVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                       femtoTrack->dEdx() * 1e6 );

      // If electron has passed PID nsigma cut
      if ( TMath::Abs( femtoTrack->nSigmaElectron() ) <= 2. ) {
        hDedxVsPtPID[0]->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                               femtoTrack->dEdx() * 1e6 );
      }

      // If pion has passed PID nsigma cut
      if ( TMath::Abs( femtoTrack->nSigmaPion() ) <= 2. ) {
        hDedxVsPtPID[1]->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                               femtoTrack->dEdx() * 1e6 );
      }

      // If kaon has passed PID nsigma cut
      if ( TMath::Abs( femtoTrack->nSigmaKaon() ) <= 2. ) {
        hDedxVsPtPID[2]->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                               femtoTrack->dEdx() * 1e6 );
      }

      // If proton has passed PID nsigma cut
      if ( TMath::Abs( femtoTrack->nSigmaProton() ) <= 2. ) {
        hDedxVsPtPID[3]->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                               femtoTrack->dEdx() * 1e6 );
      }

      if( femtoTrack->charge() > 0 ) {
      	hPrimaryPhiVsPt[0]->Fill( femtoTrack->pMom().Pt(),
                                  femtoTrack->pMom().Phi() );
      }
      else {
	       hPrimaryPhiVsPt[1]->Fill( femtoTrack->pMom().Pt(),
				                           femtoTrack->pMom().Phi() );
      }
      hNSigmaElectronVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                                 femtoTrack->nSigmaElectron() );
      hNSigmaPionVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                             femtoTrack->nSigmaPion() );
      hNSigmaKaonVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                             femtoTrack->nSigmaKaon() );
      hNSigmaProtonVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                               femtoTrack->nSigmaProton() );
      hTrackProfile[0]->Fill( event->runId(), femtoTrack->pMom().Phi() );
      hTrackProfile[1]->Fill( event->runId(), femtoTrack->pMom().Pt() );
      hTrackProfile[2]->Fill( event->runId(), femtoTrack->nHits() );
      hTrackProfile[3]->Fill( event->runId(),
                              femtoTrack->gDCA(pVtx.X(), pVtx.Y(), pVtx.Z() ) );
      hTrackProfile[5]->Fill( event->runId(),
                              femtoTrack->dEdx() * 1e6 );

      // Check if track has TOF signal
      if ( femtoTrack->isTofTrack() ) {
	      hTofBeta->Fill( femtoTrack->beta() );
        hInvBetaVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                            femtoTrack->invBeta() );
        hMassSqr->Fill( femtoTrack->massSqr() );
        hMassSqrVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                            femtoTrack->massSqr() );
        hInvBetaDiffElectronVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                                        femtoTrack->invBeta() - TMath::Sqrt(electron_mass_sqr +
                                          femtoTrack->pMom().Mag2() )/ femtoTrack->pMom().Mag() );
        hInvBetaDiffPionVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                                    femtoTrack->invBeta() - TMath::Sqrt(pion_mass_sqr +
                                        femtoTrack->pMom().Mag2() )/ femtoTrack->pMom().Mag() );
        hInvBetaDiffKaonVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                                    femtoTrack->invBeta() - TMath::Sqrt(kaon_mass_sqr +
                                        femtoTrack->pMom().Mag2() )/ femtoTrack->pMom().Mag() );
        hInvBetaDiffProtonVsPt->Fill( femtoTrack->charge() * femtoTrack->pMom().Pt(),
                                      femtoTrack->invBeta() - TMath::Sqrt(proton_mass_sqr +
                                        femtoTrack->pMom().Mag2() )/ femtoTrack->pMom().Mag() );
        if ( femtoTrack->charge() > 0 ) {
          hDedxVsMassSqr[0]->Fill( femtoTrack->massSqr(), femtoTrack->dEdx() * 1e6 );
        }
        else {
          hDedxVsMassSqr[1]->Fill( femtoTrack->massSqr(), femtoTrack->dEdx() * 1e6 );
        }
        hTrackProfile[4]->Fill( event->runId(), femtoTrack->beta() );
      } //if( isTofTrack() )

    } //for(Int_t iTrk=0; iTrk<nTracks; iTrk++)

  } //for(Long64_t iEvent=0; iEvent<events2read; iEvent++)

  oFile->Write();
  oFile->Close();

  femtoReader->Finish();

  std::cout << "I'm done with analysis. We'll have a Nobel Prize, Master!"
	    << std::endl;
}

//________________
Bool_t isGoodEvent(const TVector3& vtx, const Float_t& vpdVz) {
  return ( TMath::Abs( vtx.Z() ) <= 70. &&
           TMath::Abs( vtx.Z() - vpdVz ) <= 15. &&
           vtx.Perp() <= 2. );
}

//________________
Bool_t isGoodTrack(const TVector3& mom, const Int_t& nHits,
                   const Int_t& nHitsPoss) {
  return ( mom.Mag() >= 0.15 &&
           mom.Mag() <= 2.1 &&
           TMath::Abs( mom.Eta() ) <= 1. &&
           nHits >= 11 &&
           (Float_t)nHits/nHitsPoss >= 0.51 );
}
