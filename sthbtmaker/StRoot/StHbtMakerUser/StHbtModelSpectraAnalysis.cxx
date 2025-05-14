#define StHbtModelSpectraAnalysis_cxx

// StHbtModelSpectraAnalysis headers
#include "StHbtModelSpectraAnalysis.h"
#ifdef __ROOT__
ClassImp(StHbtModelSpectraAnalysis);
#endif // #ifdef __ROOT__
//________________
StHbtModelSpectraAnalysis::StHbtModelSpectraAnalysis(const char* oFileName) :
  mDebug(false), 
  mEventVerbose(false),
  mOutFileName(nullptr), 
  mOutFile(nullptr),
  mReader(nullptr),
  mParticle(nullptr),
  mDst(nullptr),
  mEvent(nullptr),
  mLedWei(nullptr),
  mZResCh(0.) {
  // Constructor

  // Set output file name
  mOutFileName = oFileName;



  mEta[0]  = -1.5;  mEta[1]  = 1.5;
  mPt[0] = 0.0; mPt[1] = 10.;
}

//________________
StHbtModelSpectraAnalysis::~StHbtModelSpectraAnalysis() {
  // Destructor
  /* empty */
}



//________________
void StHbtModelSpectraAnalysis::Loop() {

  std::cout << "Lets process data, Master" << std::endl;
  // Retrieve number of events picoDst files
  Long64_t nEvents2Process = mReader->chain()->GetEntries();
  std::cout << " Number of events in files: " << nEvents2Process << std::endl;

  // Processing events
  for (Long64_t iEvent=0; iEvent<nEvents2Process; iEvent++) {
    if( iEvent % 10000 == 0 ) std::cout << "Working on event: [" << iEvent << "/" << nEvents2Process << "]" << std::endl;
    // Check return code
    int iret = Make(iEvent);
    // Quit event processing if return code is not 0
    if (iret) { std::cout << "Bad return code!" << iret << std::endl; break; }
  } // for (Int_t iEvent=0; iEvent<nEvents2Process; iEvent++)
  std::cout << "Data have been processed, Master" << std::endl;
}
//________________
Int_t StHbtModelSpectraAnalysis::Init(const char* inFile) {

  if (mDebug) { std::cout << "Initializing StHbtModelSpectraAnalysis..." << std::endl; }

  mReader = new McDstReader(inFile);
  mReader->Init();
  mReader->setStatus("*",0);
  mReader->setStatus("Event",1);
  mReader->setStatus("Particle",1);
  if( !mReader->chain() )  { std::cout << "No chain has been found." << std::endl; }

  // Create output file
  if (!mOutFile) { mOutFile = new TFile(mOutFileName, "recreate"); }
  // comes from 'append' - all output will be added (appended) to the end of the file.
  // In other words you cannot write anywhere else in the file but at the end.
  else {
    std::cout << "\n [WARNING] Output file: " << mOutFileName
              << " already exist!" << std::endl;
  }

  // Create histograms
  CreateHistograms();

  if (mDebug) {
    std::cout << "StHbtModelSpectraAnalysis has been initialized\n" << std::endl;
  }

  mLedWei = new StHbtModelWeightGeneratorLednicky();
  mLedWei->setPairType( StHbtModelWeightGeneratorLednicky::PionPlusPionPlus() );
  mLedWei->setCoulOff();
  mLedWei->setQuantumOff();
  // mLedWei->setQuantumOn();
  mLedWei->setStrongOff();
  mLedWei->set3BodyOn();
  mLedWei->setNuclCharge(mZResCh);

  if (mDebug) {
    std::cout << "StHbtModelWeightGeneratorLednicky has been initialized\n" << std::endl;
  }
  return 0; // kStOk
}

//________________
Int_t StHbtModelSpectraAnalysis::Finish() {

  if (mDebug) {
    std::cout << "Finishing StHbtModelSpectraAnalysis..." << std::endl;
  }

  // Write histograms to the file and then close it
  if (mOutFile) {
    std::cout << "Writing file: " << mOutFileName;
    mOutFile->Write();


    mOutFile->Close();
    std::cout << "\t[DONE]" << std::endl;
  }
  else {
    std::cout << "[WARNING] Output file does not exist. Nowhere to write!" << std::endl;
  }

  if (mDebug) {
    std::cout << "StHbtModelSpectraAnalysis has been finished\n" << std::endl;
  }

  return 0; // kStOk
}

//________________
void StHbtModelSpectraAnalysis::CreateHistograms() {
  if (mDebug) {
    std::cout << "Creating histograms..." << std::endl;
  }

  CreateEventHistograms();
  CreateTrackHistograms();

  if (mDebug) {
    std::cout << "Histograms have been created" << std::endl;
  }
}

//________________
void StHbtModelSpectraAnalysis::CreateEventHistograms() {

  if (mDebug) { std::cout << "Creating event histograms..."; }
  hImpParam = new TH1F("hImpParam","Impact parameter;b (fm);Entries", 100, 0., 20.);
  hCent = new TH1D("hCent","Event counter;Centrality bin;Events", nCent, 0., nCent);

  if (mDebug) { std::cout << "\t[DONE]" << std::endl; }
}

//________________
void StHbtModelSpectraAnalysis::CreateTrackHistograms() {

  if (mDebug) { std::cout << "Creating particle histograms..."; }
  for (int iCent=0; iCent<nCent; iCent++) {
    for (int iCh=0; iCh<nCh; iCh++) {
      hPtDistorted[iCent][iCh] = new TH1D(Form("hPtDistorted_cent%i_ch%i",iCent,iCh),";p_{T} (GeV/c);dN/dp_{T}",100,0.,2.);
      hPDistorted[iCent][iCh]  = new TH1D(Form("hPDistorted_cent%i_ch%i",iCent,iCh),";p (GeV/c);dN/dp",100,0.,2.);
      hPtOrigin[iCent][iCh] = new TH1D(Form("hPtOrigin_cent%i_ch%i",iCent,iCh),";p_{T} (GeV/c);dN/dp_{T}",100,0.,2.);
      hPOrigin[iCent][iCh]  = new TH1D(Form("hPOrigin_cent%i_ch%i",iCent,iCh),";p (GeV/c);dN/dp",100,0.,2.);
      hWeif[iCent][iCh]     = new TH1D(Form("hWeif_cent%i_ch%i",iCent,iCh),";Weif;dN/dWeif",500,0.,5.);
      hWeifVsP[iCent][iCh]  = new TH2F(Form("hWeifVsP_cent%i_ch%i",iCent,iCh),";p (GeV/c);Weif;dN/dWeif",200,0.,2.,500,0.,5.);
      pWeifVsP[iCent][iCh]  = new TProfile(Form("pWeifVsP_cent%i_ch%i",iCent,iCh),";p (GeV/c);Weif",200,0.,2.);
    } // for (int iCh=0; iCh<nCh; iCh++)
  } // for (int iCent=0; iCent<nCent; iCent++)
  if (mDebug) { std::cout << "\t[DONE]" << std::endl; }
}
//________________
Bool_t StHbtModelSpectraAnalysis::EventCut(McEvent *event) {
  /* empty */
  return true;
}

//________________
Bool_t StHbtModelSpectraAnalysis::TrackCut(McParticle *const& particle) {
  return (particle->pt() >= mPt[0] &&
          particle->pt() <= mPt[1] &&
          particle->eta() >= mEta[0] &&
          particle->eta() <= mEta[1] &&
          TMath::Abs(particle->pdg()) == 211);
}

//________________
Int_t StHbtModelSpectraAnalysis::Make(Long64_t iEvent) {


  bool readEvent = mReader->loadEntry(iEvent);

  if( !readEvent ) { std::cout << "[ERROR] Can't read event." << std::endl; return 3; }
  // Retrieve McDst
  mDst = mReader->mcDst();
  // Retrieve MC event
  mEvent = mDst->event();
  if ( !mEvent ) {
    std::cout << "[ERROR] PicoDst does not contain event information. Terminating" << std::endl; // LOG_ERROR
    return 3; // kStErr
  }

  // Check if event passes event cut
  if ( !EventCut(mEvent) ) {
    return 0; // kStOk
  }
  Double_t b = mEvent->b();
  Int_t iCent = -1;
  if      (b < 4.7 ) iCent = 0; // 0-10%
  else if (b < 8.1 ) iCent = 1; // 10-30%
  else if (b < 10.4) iCent = 2; // 30-50%
  else if (b < 13.2) iCent = 3; // 50-80%
  if (iCent < 0) return 0; // kStOk
  hImpParam->Fill( b );
  hCent->Fill(iCent);

  unsigned int nParticles = mDst->numberOfParticles();
  for (unsigned int iPart=0; iPart<nParticles; iPart++) {
    // Retrieve i-th MC particle
    mParticle = mDst->particle(iPart);
    if ( !mParticle ) continue;
    // Check if particle passes particle cut
    if ( !TrackCut(mParticle) ) continue;
    Int_t charge = mParticle->charge();
    Int_t iCh = (charge > 0) ? 0 : 1;
    Int_t pdg = mParticle->pdg();
    Double_t pt = mParticle->pt();
    Double_t ptot = mParticle->ptot();
    Double_t eta = mParticle->eta();
    Double_t rapidity = mParticle->momentum().Rapidity();

    hPtOrigin[iCent][iCh]->Fill(pt, 1.);
    hPOrigin[iCent][iCh]->Fill(ptot, 1.);
    double dWeif = mLedWei->generateSingleParticleThirdBodyWeight(mParticle->position(),mParticle->momentum(),pdg);
    // std::cout << " WEIF = " << dWeif << std::endl;
    hPtDistorted[iCent][iCh]->Fill(pt, dWeif);
    hPDistorted[iCent][iCh]->Fill(ptot, dWeif);
    hWeif[iCent][iCh]->Fill(dWeif);
    hWeifVsP[iCent][iCh]->Fill(ptot, dWeif);
    pWeifVsP[iCent][iCh]->Fill(ptot, dWeif);

  } // for (unsigned int iPart=0; iPart<nParticles; iPart++)
  return 0; // kStOk
}