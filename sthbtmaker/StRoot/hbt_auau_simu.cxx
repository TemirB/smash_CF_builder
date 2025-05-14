// C++ headers
#include <iostream>
#include "TROOT.h"
#include "TObject.h"
#include "Riostream.h"
#include "TSystem.h"
#include <math.h> 


// StHbtMaker headers
#include "StHbtMaker/StHbtMaker.h"
#include "StHbtMaker/StHbtManager.h"
#include "StHbtMaker/StHbtAnalysis.h"
#include "StHbtMaker/phys_constants.h"
#include "StHbtMaker/StHbtModelWeightGeneratorLednicky.h"
#include "StHbtMaker/StHbtModelManager.h"

// StHbtMakerUser headers
#include "StHbtMakerUser/StHbtBasicEventCut.h"
#include "StHbtMakerUser/StHbtBasicTrackCut.h"
#include "StHbtMakerUser/StHbtBasicPairCut.h"
#include "StHbtMakerUser/fxtEventCutMonitor.h"
#include "StHbtMakerUser/fxtTrackCutMonitor.h"
#include "StHbtMakerUser/fxtPairCutMonitor.h"
#include "StHbtMakerUser/StHbtModelBPLCMS3DCorrFctnKt.h"
#include "StHbtMakerUser/StHbtModelVertexImpactAnalysis.h"
#include "StHbtMakerUser/StHbtModelQinvCorrFctnKt.h"
#include "StHbtMakerUser/StHbtMcDstReader.h"

#include "McDst/McDstReader.h"

//________________
void fillEventCut(StHbtBasicEventCut *eventCut,
                  int iCent,
                  fxtEventCutMonitor *moniPass,
                  fxtEventCutMonitor *moniFail) {

  if ( !eventCut ) {
    std::cout << "[ERROR] fillEventCut -- No event cut was provided \n";
    return;
  }

  // Cut values
  int mCent[2] = { -1000000, 1000000 };
  int mMult[2] = { -1000000, 1000000 };
  float mImpact[2] = { -100., 100. }; 
  float vtxXShift = 0.;
  float vtxYShift = 0.;
  float vpdVzDiff[2] = { -1e6, 1e6 };
  float r[2] = { 0., 2. };
  float sphericity[2] = { -1e6, 1e6 };
  int bTofMatch[2] = { 0, 5000 };
  int bTofMult[2] = { 0, 5000 };
  bool verbose = false;

  switch ( iCent) {
    // for sigma_NN = 28 mb
    case 0:  mImpact[0] = 0.00; mImpact[1] = 4.6; break; // 0-10%
    case 1:  mImpact[0] = 4.6; mImpact[1] = 8.; break; // 10-30%
    case 2:  mImpact[0] = 8.; mImpact[1] = 10.4; break; // 30-50%
    case 3:  mImpact[0] = 10.4; mImpact[1] = 13.1; break; // 50-80%
    default: mImpact[0] = 0.0; mImpact[1] = 30.;  break;
  };  

  eventCut->setCheckBadRun( false );
  eventCut->setEventMult( mMult[0], mMult[1] );
  eventCut->setImpactParameter(mImpact[0], mImpact[1]);
  eventCut->setVpdVzDiff( vpdVzDiff[0], vpdVzDiff[1] );
  eventCut->setVertXShift( vtxXShift );
  eventCut->setVertYShift( vtxYShift );
  eventCut->setVertRPos( r[0], r[1] );
  eventCut->setSphericity( sphericity[0], sphericity[1] );
  eventCut->setBTofTrayMult( bTofMult[0], bTofMult[1] );
  eventCut->setBTofMatchMult( bTofMatch[0], bTofMatch[1] );
  eventCut->setCent9( mCent[0], mCent[1] );
  eventCut->setVerbose( verbose );
  
  if ( moniPass && moniFail ) {
    eventCut->addCutMonitor( moniPass, moniFail );
  }
  
}

//_________________
void fillTrackCut(StHbtBasicTrackCut *trackCut,
                  int charge, int particleType, int detSel,
                  fxtTrackCutMonitor *moniPass,
                  fxtTrackCutMonitor *moniFail) {

  if ( !trackCut ) {
    std::cout << "[ERROR] fillTrackCut -- No track cut was provided\n";
    return;
  }

  // charge = +-1
  // particleType = StHbtBasicTrackCut:: enum HbtPID { Electron=1, Pion, Kaon, Proton };
  // detSel = 0 TPC; 1 TOF; 2 TPC+TOF; 3 if(TOF){TPC+TOF} else{TPC};
  //          4 if(TOF&&p>pthresh){TPC+TOF} else if (p<pthresh){TPC}
  
  // Cut values

  // Standard cuts and kinematics
  bool isTheory = true;
  int pdgId = (charge>0) ? 211 : -211;
  bool primaryTracks = true;
  bool verbose = false;
  int nHits[2] = { 15, 100 };
  float nHitsRatio = 0.;
  float dca[2] = { 0., 3. };
  float pT[2] = { 0.15,  1.5 };
  
  float p[2] = { 0.15, 1.5 };
  float eta[2] = { -1.5, 1.5 };
  float rap[2] = { -9999., 9999.};

  // ToT with threshold
  float mPThresh = 0.55;

  // TPC identification only cuts
  float tpcMom[2] = { 0.15, mPThresh }; // real world
  float nSigmaTpcElectron[2] = { -2., 2. };
  float nSigmaTpcPion[2] = { -1.5, 2.5 };
  float nSigmaTpcKaon[2] = { -2., 2. };
  float nSigmaTpcProton[2] = { -2., 2. };
  float nSigmaTpcOther[2] = { -2., 2. };

  // TOF identification only cuts
  float tofMom[2] = { mPThresh, 1.5 };
  float massSqr[2] = { -0.05, 0.08 };
  float invBetaDiff[2] = { -0.015, 0.015 };

  // TPC+TOF identification
  float nSigmaTnTElectron[2] = { -3., 3. };
  float nSigmaTnTPion[2] = { -3., 3. };
  float nSigmaTnTKaon[2] = { -3., 3. };
  float nSigmaTnTProton[2] = { -3., 3. };

// Set track cut parameters
  trackCut->selectPrimary( primaryTracks );
  trackCut->setCharge( charge );
  trackCut->setNHits( nHits[0], nHits[1] );
  trackCut->setAntiSplit( nHitsRatio );
  trackCut->setPt( pT[0], pT[1] );
  trackCut->setP( p[0], p[1] );
  trackCut->setEta( eta[0], eta[1] );
  trackCut->setDCA( dca[0], dca[1] );
  trackCut->setRapidity(rap[0],rap[1]);

  // Detector selection
  trackCut->setDetectorSelection( detSel );

  // TPC identification
  trackCut->setNSigmaElectron( nSigmaTpcElectron[0], nSigmaTpcElectron[1] );
  trackCut->setNSigmaPion( nSigmaTpcPion[0], nSigmaTpcPion[1] );
  trackCut->setNSigmaKaon( nSigmaTpcKaon[0], nSigmaTpcKaon[1] );
  trackCut->setNSigmaProton( nSigmaTpcProton[0], nSigmaTpcProton[1] );
  trackCut->setNSigmaOther( nSigmaTpcOther[0], nSigmaTpcOther[1] );
  trackCut->setTpcMom( tpcMom[0], tpcMom[1] );

  // TOF identification
  trackCut->setMassSqr( massSqr[0], massSqr[1] );
  trackCut->setInvBetaDiff( invBetaDiff[0], invBetaDiff[1] );
  trackCut->setTofMom( tofMom[0], tofMom[1] );

  // TPC+TOF identification
  trackCut->setTnTNSigmaElectron( nSigmaTnTElectron[0], nSigmaTnTElectron[1] );
  trackCut->setTnTNSigmaPion( nSigmaTnTPion[0], nSigmaTnTPion[1] );
  trackCut->setTnTNSigmaKaon( nSigmaTnTKaon[0], nSigmaTnTKaon[1] );
  trackCut->setTnTNSigmaProton( nSigmaTnTProton[0], nSigmaTnTProton[1] );

  // Set which particle type to select
  if ( particleType == 1 ) {
    trackCut->setHbtPid( StHbtBasicTrackCut::HbtPID::Electron );
    trackCut->setMass( M_ELECTRON );
  }
  else if ( particleType == 2 ) {
    trackCut->setHbtPid( StHbtBasicTrackCut::HbtPID::Pion );
    trackCut->setMass( M_PION_PLUS );
  }
  else if ( particleType == 3 ) {
    trackCut->setHbtPid( StHbtBasicTrackCut::HbtPID::Kaon );
    trackCut->setMass( M_KAON_PLUS );
  }
  else if ( particleType == 4 ) {
    trackCut->setHbtPid( StHbtBasicTrackCut::HbtPID::Proton );
    trackCut->setMass( M_PROTON );
  }
  else {
    //std::cout << "[WARNING] fillTrackCut -- Unknown particle type: " << particleType<< "\nSwitching to pion PID" << std::endl;
    trackCut->setHbtPid( StHbtBasicTrackCut::HbtPID::Pion );
    trackCut->setMass( M_PION_PLUS );
  }

  // Set momentum threshold for detector selection == 4
  trackCut->setPthresh( mPThresh );
  
  trackCut->setIsTheory( isTheory );
  trackCut->setPdgId( pdgId );

  // Print cut information for each track
  trackCut->setVerboseMode( verbose );

  // Add track cut monitors
  if ( moniPass && moniFail ) {
    trackCut->addCutMonitor( moniPass, moniFail );
  }
 
}

//_________________
void fillTrackPairCut(StHbtBasicPairCut *pairCut,
                      fxtPairCutMonitor *moniPass,
                      fxtPairCutMonitor *moniFail) {

  if ( !pairCut ) {
    std::cout << "[ERROR] fillTrackPairCut -- No pair cut was provided\n";
    return;
  }

  // Cut values
  float quality[2] = { -0.5, 0.6 }; // antisplitting
  float kT[2] = { 0.15, 0.6};
  float pT[2] = { 0., 1e5 };
  float openingAngle[2] = { -1e6, 1e6 };
  float entranceSeparation[2] = { 0., 1e6 };
  float y[2] = { -0.5, 0 }; // need to be changed to [-0.5, 0]
  float eta[2] = { -1e5, 1e5 };
  float qInv[2] = { -1e5, 1e5 };
  float mInv[2] = { 0., 1e5 };
  float emissionAngle[2] = { -1e6, 1e6 };
  float fmr[2] = { -1.1, 0.1 };
  float closestRowAtDCA[2] = { -1e6, 1e6 };
  float weightedAveSep[2] = { -1e6, 1e6 };
  float aveSep[2] = { -1e6, 1e6 };
  float rValue = -1e6;
  float dPhiStarMin[2] = { -1e6, 1e6 };
  bool verbose = false;

  // Set pair cut values
  pairCut->setQuality( quality[0], quality[1] );
  pairCut->setKt( kT[0], kT[1] );
  pairCut->setPt( pT[0], pT[1] );
  pairCut->setOpeningAngle( openingAngle[0], openingAngle[1] );
  pairCut->setEntranceSeparation( entranceSeparation[0], entranceSeparation[1] );
  pairCut->setRapidity( y[0], y[1] );
  pairCut->setEta( eta[0], eta[1] );
  pairCut->setQinv( qInv[0], qInv[1] );
  pairCut->setMinv( mInv[0], mInv[1] );
  pairCut->setAngleToPrimaryVertex( emissionAngle[0], emissionAngle[1] );
  pairCut->setFracOfMergedRow( fmr[0], fmr[1] );
  pairCut->setClosestRowAtDCA( closestRowAtDCA[0], closestRowAtDCA[1] );
  pairCut->setWeightedAvSep( weightedAveSep[0], weightedAveSep[1] );
  pairCut->setAverageSeparation( aveSep[0], aveSep[1] );
  pairCut->setRValue( rValue );
  pairCut->setDPhiStarMin( dPhiStarMin[0], dPhiStarMin[1] );
  pairCut->setVerboseMode( verbose );

  
  // Add pair cut monitors
  if ( moniPass && moniFail ) {
    pairCut->addCutMonitor( moniPass, moniFail );
  }
  
}

//________________
void fillLikeSignAnalysis(StHbtModelVertexImpactAnalysis *analysis,
                          StHbtBasicEventCut *eventCut,
                          StHbtBasicTrackCut *trackCut,
                          StHbtBasicPairCut *pairCut,
                          StHbtModelQinvCorrFctnKt *qInvCorrFctn,
                          StHbtModelBPLCMS3DCorrFctnKt *bpCorrFctn) {

  if ( !analysis ) {
    std::cout << "[ERROR] fillLikeSignAnalysis -- No analysis was provided \n";
    return;
  }

  if ( !eventCut ) {
    std::cout << "[ERROR] fillLikeSignAnalysis -- No event cut was provided \n";
    return;
  }

  if ( !trackCut ) {
    std::cout << "[ERROR] fillLikeSignAnalysis -- No track cut was provided \n";
    return;
  }

  if ( !pairCut ) {
    std::cout << "[ERROR] fillLikeSignAnalysis -- No pair cut was provided \n";
    return;
  }

  // Talk or not to talk
  analysis->setVerboseMode(false);

  // Set event cut
  analysis->setEventCut(eventCut);
  
  // Set first and second particle cuts
  analysis->setFirstParticleCut( trackCut );
  analysis->setSecondParticleCut( trackCut );

  // Set pair cut
  analysis->setPairCut( pairCut );
  
  // Set qInv correlation function if exists
  if ( qInvCorrFctn ) {
    analysis->addCorrFctn( qInvCorrFctn );
  }
  if ( bpCorrFctn ) {
    analysis->addCorrFctn( bpCorrFctn );
  }
}

//________________
int main(int argc, char *argv[]) {

  const char* inFileList;
  const char* oFileName;
  bool useMonitors = false;

  switch (argc) {
  case 4:
    inFileList  = argv[1];
    oFileName   = argv[2];
    useMonitors = ( atoi(argv[3]) != 0 ) ? true : false;
    break;
  default:
    std::cout << "Usage: ./hbt_auau_simu input.list outputFile.root useMonitors" << std::endl;
    return -1;
  }


  std::cout << " Input file list: " << inFileList << std::endl;


  //
  // Monte Carlo input setup
  //

  std::cout << "Initializing McDstReader..." << std::endl;
  McDstReader *mcDstReader = new McDstReader(inFileList);
  mcDstReader->Init();
  mcDstReader->setStatus("*",0);
  mcDstReader->setStatus("Event*",1);
  mcDstReader->setStatus("Particle*",1);
  std::cout << "McDstReader initialized" << std::endl;

  if( !mcDstReader->chain() ) {
    std::cout << "[ERROR] No chain has been found in McDst. Terminating."
              << std::endl;
    return -1;
  }

  Long64_t events2read = mcDstReader->chain()->GetEntries();
  std::cout << "Number of events in chain: " << events2read << std::endl;
  //events2read = 10;
  //
  // StHbtMaker setup
  //

  // StHbtMaker
  std::cout << "Initializing StHbtMaker" << std::endl;
  StHbtMaker* hbtMaker = new StHbtMaker("HBT","title");

  // Create manager
  StHbtManager* hbtManager = hbtMaker->hbtManager();

  // Setup StHbtReader
  StHbtMcDstReader *mcHbtReader = new StHbtMcDstReader(mcDstReader);
  mcHbtReader->setRotateEventPlane(false);
  mcHbtReader->setMagneticField(-5.); // in kilogaus = -0.5 Tesla

  // Add reader to the manager
  hbtManager->setEventReader(mcHbtReader);

  const int ChargeBins = 2; // 0 - positive, 1 - negative
  const int DetSelBins = 1;
  const int kTBins = 4;
  const double kTRange[2] = { 0.15, 0.6 };
  const int qInvNbins = 40;
  const double qInvRange[2] = { 0., 0.4 };
  const int bpNbins = 80;
  const double bpRange[2] = { -0.4, 0.4 };

  const int mImpactBins = 1;
  const float mImpact[2] = { -100., 100. };
  const int mZBins = 1;
  const float mZ[2] = { -30., 30. };
  const int mEvents2Mix = 1;


  // 0-TPC,
  // 1-TOF,
  // 2-TPC+TOF,
  // 3-if(TOF){TPC+TOF} else{TPC},
  // 4-if(TOF&&p>pthresh){TPC+TOF} else if (p<pthresh){TPC}
  int mLocalDetSel = 4;
  const int MultBins = 4;

  StHbtModelVertexImpactAnalysis *hbtAnalysis[ChargeBins][DetSelBins][MultBins];
  StHbtBasicEventCut *hbtEventCut[ChargeBins][DetSelBins][MultBins];
  StHbtBasicTrackCut *hbtTrackCut[ChargeBins][DetSelBins][MultBins];
  StHbtBasicPairCut *hbtPairCut[ChargeBins][DetSelBins][MultBins];
  fxtEventCutMonitor *eventPass[ChargeBins][DetSelBins][MultBins];
  fxtEventCutMonitor *eventFail[ChargeBins][DetSelBins][MultBins];
  fxtTrackCutMonitor *trackPass[ChargeBins][DetSelBins][MultBins];
  fxtTrackCutMonitor *trackFail[ChargeBins][DetSelBins][MultBins];
  fxtPairCutMonitor *pairPass[ChargeBins][DetSelBins][MultBins];
  fxtPairCutMonitor *pairFail[ChargeBins][DetSelBins][MultBins];
  
  StHbtModelWeightGeneratorLednicky *hbtWeight;
  StHbtModelManager                 *thModelManager;

  StHbtModelBPLCMS3DCorrFctnKt *bpCorrFctn[ChargeBins][DetSelBins][MultBins];
  StHbtModelQinvCorrFctnKt *qInvCorrFctn[ChargeBins][DetSelBins][MultBins];
  // Lednicky weight generator                                                                                                                                                                                                             
  hbtWeight = new StHbtModelWeightGeneratorLednicky();
  hbtWeight->setPairType( StHbtModelWeightGeneratorLednicky::PionPlusPionPlus() );
  hbtWeight->setCoulOff();
  hbtWeight->setQuantumOn();
  hbtWeight->setStrongOff();
  hbtWeight->set3BodyOff();

  // Theoretical model manager                                                                                                                                                                                                             
  thModelManager = new StHbtModelManager();
  thModelManager->setWeightGenerator( hbtWeight );
  thModelManager->createCopyHiddenInfo( true );

  int mLocalCharge = 0;

  // Loop over charges
  for ( int iCharge = 0; iCharge < ChargeBins; iCharge++ ) {
    // Loop over multiplicity bins
    for ( int iDetSelBins = 0; iDetSelBins < DetSelBins; iDetSelBins++ ) {
      for ( int iCent = 0; iCent < MultBins; iCent++ ) {
        // Define local charge
        mLocalCharge = ( iCharge == 0 ) ? 1 : -1;
        // Define detector selection
        if      ( iDetSelBins == 0 ) mLocalDetSel = 4;
        else if ( iDetSelBins == 1 ) mLocalDetSel = 0;
        else {
          std::cout << "[WARNING] Wrong detector selection: " << iDetSelBins << std::endl;
          mLocalDetSel = 0;
        }

        // Create vertex mult analysis
        hbtAnalysis[iCharge][iDetSelBins][iCent] = new StHbtModelVertexImpactAnalysis(mZBins, mZ[0], mZ[1],
                                                                                      mImpactBins, mImpact[0], mImpact[1] );
        hbtAnalysis[iCharge][iDetSelBins][iCent]->setNumEventsToMix( mEvents2Mix );
	
	      eventPass[iCharge][iDetSelBins][iCent] =
          new fxtEventCutMonitor(Form("fxtEventCutMoni_%d_%d_%d_",iCharge, iDetSelBins, iCent), "pass");
        eventFail[iCharge][iDetSelBins][iCent] =
          new fxtEventCutMonitor(Form("fxtEventCutMoni_%d_%d_%d_",iCharge, iDetSelBins, iCent), "fail");

        trackPass[iCharge][iDetSelBins][iCent] =
          new fxtTrackCutMonitor(Form("_pass_%d_%d_%d_",iCharge,iDetSelBins,iCent), M_PION_PLUS);
        trackFail[iCharge][iDetSelBins][iCent] =
          new fxtTrackCutMonitor(Form("_fail_%d_%d_%d_",iCharge,iDetSelBins,iCent), M_PION_PLUS);
        pairPass[iCharge][iDetSelBins][iCent] = 
          new fxtPairCutMonitor(Form("_pass_%d_%d_%d_", iCharge,iDetSelBins,iCent));
              pairFail[iCharge][iDetSelBins][iCent] = 
          new fxtPairCutMonitor(Form("_fail_%d_%d_%d_", iCharge,iDetSelBins,iCent));

        // Fill event cut and monitors
        hbtEventCut[iCharge][iDetSelBins][iCent] = new StHbtBasicEventCut();
        fillEventCut( hbtEventCut[iCharge][iDetSelBins][iCent], iCent,
                      eventPass[iCharge][iDetSelBins][iCent],
                      eventFail[iCharge][iDetSelBins][iCent] );

        // Fill track cut and monitors
        hbtTrackCut[iCharge][iDetSelBins][iCent] = new StHbtBasicTrackCut();
        fillTrackCut(hbtTrackCut[iCharge][iDetSelBins][iCent],
                     mLocalCharge, StHbtBasicTrackCut::HbtPID::Pion, mLocalDetSel,
                     trackPass[iCharge][iDetSelBins][iCent],
                     trackFail[iCharge][iDetSelBins][iCent]);

        // Fill pair cut and monitors
        hbtPairCut[iCharge][iDetSelBins][iCent] = new StHbtBasicPairCut();
        fillTrackPairCut( hbtPairCut[iCharge][iDetSelBins][iCent],
                            pairPass[iCharge][iDetSelBins][iCent],
                            pairFail[iCharge][iDetSelBins][iCent] );
        
        qInvCorrFctn[iCharge][iDetSelBins][iCent] = new StHbtModelQinvCorrFctnKt( Form("qinv_%d_%d_%d",iCharge,iDetSelBins,iCent),
        qInvNbins, qInvRange[0], qInvRange[1], kTBins, kTRange[0], kTRange[1] );
        qInvCorrFctn[iCharge][iDetSelBins][iCent]->connectToManager(thModelManager);
        bpCorrFctn[iCharge][iDetSelBins][iCent] = new StHbtModelBPLCMS3DCorrFctnKt(Form("bp_%d_%d_%d",iCharge,iDetSelBins,iCent),
                                                                                    bpNbins, bpRange[0], bpRange[1],
                                                                                    kTBins, kTRange[0], kTRange[1]);
        bpCorrFctn[iCharge][iDetSelBins][iCent]->connectToManager(thModelManager);
        // Fill like sign analysis
        fillLikeSignAnalysis( hbtAnalysis[iCharge][iDetSelBins][iCent],
                              hbtEventCut[iCharge][iDetSelBins][iCent],
                              hbtTrackCut[iCharge][iDetSelBins][iCent],
                              hbtPairCut[iCharge][iDetSelBins][iCent],
                              qInvCorrFctn[iCharge][iDetSelBins][iCent],
                              bpCorrFctn[iCharge][iDetSelBins][iCent]);
        // Add analysis to manager
        hbtManager->addAnalysis( hbtAnalysis[iCharge][iDetSelBins][iCent] );
      } //iCent
    } // for ( int iDetSelBins=0; iDetSelBins<MultBins; iDetSelBins++ )
  } // for ( int iCharge=0; iCharge<ChargeBins; iCharge++ )

  // Initialize StHbtMaker
  int iret = 0;

  // Loop over events
  for (int iEvent=0; iEvent<events2read; iEvent++) {

    if (iEvent % 1000 == 0) std::cout << "hbt_simu -- Working on event # " << iEvent <<"/"<<events2read<< std::endl;
    //cout<<iEvent<<endl;
    iret = hbtMaker->make();
    if ( iret!=0 ) {
      std::cout << "[WARNING] hbt_dau_exp returned status: " << iret
                << ". Processing will be finished" << std::endl;
      break;
    }
    hbtMaker->clear();
  } // for (int iEvent=0; iEvent<events2read; iEvent++)

  // Write histograms to the output file
  TFile *oFile = new TFile(oFileName,"recreate");
  
  // Write histograms to the output file
  for ( int iCharge = 0; iCharge < ChargeBins; iCharge++ ) {
    for ( int iDetSelBins = 0; iDetSelBins < DetSelBins; iDetSelBins++ ) {
      for ( int iCent = 0; iCent < MultBins; iCent++ ) {
        if (useMonitors) {
        eventPass[iCharge][iDetSelBins][iCent]->writeOutHistos();
        eventFail[iCharge][iDetSelBins][iCent]->writeOutHistos();
	      trackPass[iCharge][iDetSelBins][iCent]->writeOutHistos();
        trackFail[iCharge][iDetSelBins][iCent]->writeOutHistos();
	      pairPass[iCharge][iDetSelBins][iCent]->writeOutHistos();
        pairFail[iCharge][iDetSelBins][iCent]->writeOutHistos();
        } // if (useMonitors)
        qInvCorrFctn[iCharge][iDetSelBins][iCent]->writeOutHistos();
        bpCorrFctn[iCharge][iDetSelBins][iCent]->writeOutHistos();
      } //iCent
    } // for ( int iDetSelBins=0; iDetSelBins<MultBins; iDetSelBins++ )
  } // for ( int iCharge=0; iCharge<ChargeBins; iCharge++ )
  oFile->Close();
  hbtMaker->finish();
  // Maker finish flag
}
