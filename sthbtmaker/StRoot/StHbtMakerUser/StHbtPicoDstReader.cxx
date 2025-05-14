//
// Reader for the StPicoDst format
//

// StHbtMaker headers
#include "StHbtMaker/StHbtBaseEventCut.h"
#include "StHbtMaker/StHbtBaseTrackCut.h"
#include "StHbtMaker/StHbtBaseV0Cut.h"
#include "StHbtMaker/StHbtBaseKinkCut.h"
#include "StHbtMaker/StHbtBaseXiCut.h"

// StHbtMakerUser headers
#include "StHbtPicoDstReader.h"

#ifndef _VANILLA_ROOT_
// StRefMultCorr headers
#include "StRefMultCorr/StRefMultCorr.h"
#endif

// ROOT headers
#include "TMath.h"
#include "TMatrixDSymEigen.h"
#include "TVectorT.h"
#include "TMatrixTLazy.h"

// C++ headers
#include <cmath>

#ifdef __ROOT__
ClassImp(StHbtPicoDstReader)
#endif

//_________________
StHbtPicoDstReader::StHbtPicoDstReader() :
StHbtBaseEventReader(),
  mPicoDstReader(nullptr),
  mHbtEvent(nullptr),
  mUseRefMultCorr(false),
  mUseZdcCorrection(false),
  mSphericity(-1.),
  mSphericity2(-1.),
  mEventsPassed(0) {
  // Default Constructor

  // 0 - means good
  mReaderStatus = 0;

#ifndef _VANILLA_ROOT_
  mRefMultCorrUtil = nullptr;
#endif

}

//_________________
StHbtPicoDstReader::StHbtPicoDstReader(StPicoDstReader *picoDstReader, int debug) :
  StHbtBaseEventReader(),
  mPicoDstReader(picoDstReader),
  mHbtEvent(nullptr),
  mUseRefMultCorr(false),
  mUseZdcCorrection(false),
  mSphericity(-1.),
  mSphericity2(-1.),
  mEventsPassed(0) {
  // Parametrized constructor
  mDebug = debug;
  // 0 - means good
  mReaderStatus = 0;
#ifndef _VANILLA_ROOT_
  mRefMultCorrUtil = nullptr;
#endif
}

//_________________
StHbtPicoDstReader::StHbtPicoDstReader(const StHbtPicoDstReader& copy) :
  StHbtBaseEventReader(),
  mPicoDstReader(copy.mPicoDstReader),
  mHbtEvent(nullptr),
  mUseRefMultCorr(copy.mUseRefMultCorr),
  mUseZdcCorrection(copy.mUseZdcCorrection),
  mSphericity(copy.mSphericity),
  mSphericity2(copy.mSphericity2),
  mEventsPassed(0) {
  // Copy constructor

  // 0 - means good
  mReaderStatus = 0;

#ifndef _VANILLA_ROOT_
  mRefMultCorrUtil = copy.mRefMultCorrUtil;
#endif
}

//_________________
StHbtPicoDstReader& StHbtPicoDstReader::operator=(const StHbtPicoDstReader& copy) {
  // Assignment operator
  if (this != &copy) {
    mPicoDstReader = copy.mPicoDstReader;
    mUseRefMultCorr = copy.mUseRefMultCorr;
    mUseZdcCorrection = copy.mUseZdcCorrection;
    mSphericity = copy.mSphericity;
    mSphericity2 = copy.mSphericity2;
#ifndef _VANILLA_ROOT_
    mRefMultCorrUtil = copy.mRefMultCorrUtil;
#endif
    mHbtEvent = nullptr;
  } // if (this != &copy)

  // 0 - means good
  mReaderStatus = 0;
  mEventsPassed = 0;

  return *this;
}

//_________________
StHbtPicoDstReader::~StHbtPicoDstReader() {
  if(mPicoDstReader)   { delete mPicoDstReader; mPicoDstReader = nullptr; }
#ifndef _VANILLA_ROOT_
  if(mRefMultCorrUtil) { delete mRefMultCorrUtil; mRefMultCorrUtil = nullptr; }
#endif
  if(mHbtEvent)        { delete mHbtEvent; mHbtEvent = nullptr; }
}

//_________________
StHbtString StHbtPicoDstReader::report() {
  // Make report
  StHbtString repstr = "\nStHbtString StHbtPicoDstReader::report() - reporting\n";

  repstr += "---> Event cut in the reader: ";
  if (mEventCut) {
    repstr += mEventCut->report();
  }
  else {
    repstr += "\tNONE";
  }

  repstr += "\n---> Track cut in the reader: ";
  if (mTrackCut) {
    repstr += mTrackCut->report();
  }
  else {
    repstr += "\tNONE";
  }

  repstr += "\n---> V0 cut in the reader: ";
  if (mV0Cut) {
    repstr += mV0Cut->report();
  }
  else {
    repstr += "\tNONE";
  }

  repstr += "\n---> V0 cut in the reader: ";
  if (mV0Cut) {
    repstr += mV0Cut->report();
  }
  else {
    repstr += "\tNONE";
  }

  repstr += "\n---> Kink cut in the reader: ";
  if (mKinkCut) {
    repstr += mKinkCut->report();
  }
  else {
    repstr += "\tNONE";
  }

  repstr += "\n---> Xi cut in the reader: ";
  if (mXiCut) {
    repstr += mXiCut->report();
  }
  else {
    repstr += "\tNONE";
  }

  repstr += "\n";
  return repstr;
}

//_________________
StHbtEvent* StHbtPicoDstReader::returnHbtEvent() {
  // Read picoEvent, create StHbtEvent and return it to the StHbtAnalysis

  // Clean-up mHbtEvent from previous reading
  mHbtEvent = nullptr;

  // Check that StPicoDstReader exists
  if (!mPicoDstReader) {
    std::cout << "[ERROR] StHbtEvent* StHbtPicoDstReader::returnHbtEvent() - no StPicoDstReader is provided" << std::endl;
    mReaderStatus = 1;
    return mHbtEvent;
  }

  // Read (load) event
  mPicoDstReader->readPicoEvent(mEventsPassed);
  // Increment counter
  mEventsPassed++;

  // Check that picoDst exists
  StPicoDst* picoDst = (StPicoDst*)mPicoDstReader->picoDst();
  if (!picoDst) {
    std::cout << "[ERROR] StHbtEvent* StHbtPicoDstReader::returnHbtEvent() - no picoDst is in StPicoDstReader" << std::endl;
    mReaderStatus = 1;
    return mHbtEvent;
  }

  // Check that StPicoEvent exists
  if ( !picoDst->event() || !picoDst->numberOfTracks() ) {
    std::cout << "[WARNING] StHbtEvent* StHbtPicoDstReader::returnHbtEvent()"
              << " - StPicoEvent does not exist or particles missing"
              << std::endl;
    mReaderStatus = 1;
  }
  else {

    // Create new StHbtEvent
    mHbtEvent = new StHbtEvent();

    // Retrieve StPicoEvent
    StPicoEvent *picoEvent = (StPicoEvent*)picoDst->event();


    // Recalculate sphericity values
    sphericityCalculation();

    float bField = picoEvent->bField();

    mHbtEvent->setEventId( picoEvent->eventId() );
    mHbtEvent->setRunNumber( picoEvent->runId() );
    mHbtEvent->setBField( bField );
    mHbtEvent->setRefMult( picoEvent->refMult() );
    mHbtEvent->setRefMultPos( picoEvent->refMultPos() );
    mHbtEvent->setGRefMult( picoEvent->grefMult() );

    if (mUseRefMultCorr) {
#ifndef _VANILLA_ROOT_
      if (!mRefMultCorrUtil) {
        std::cout << "[WARNING] StHbtEvent* StHbtPicoDstReader::returnHbtEvent()"
                  << " - Pointer to mRefMultCorrUtil does not exist" << std::endl;
        mHbtEvent->setRefMultCorr(-1);
      }
      else {

        mRefMultCorrUtil->init( picoEvent->runId() );
        if ( mRefMultCorrUtil->isBadRun( picoEvent->runId() ) ) {
          // The run is bad
          delete mHbtEvent;
          mHbtEvent = nullptr;
          return mHbtEvent;
        }
        
        if ( !mRefMultCorrUtil->passnTofMatchRefmultCut(picoEvent->refMult(), picoEvent->nBTOFMatch() ) ) {
          // The event is pile-up
          delete mHbtEvent;
          mHbtEvent = nullptr;
          return mHbtEvent;
        }

        if (mUseZdcCorrection) {
          mRefMultCorrUtil->initEvent( picoEvent->refMult(),
                                       picoEvent->primaryVertex().Z(),
                                       picoEvent->ZDCx() );
        }
        else {
          mRefMultCorrUtil->initEvent( picoEvent->refMult(),
                                       picoEvent->primaryVertex().Z() );
        }

        if ( mRefMultCorrUtil->getCentralityBin16() < 0 ) {
          mHbtEvent->setCent16( -1 );
          mHbtEvent->setRefMultCorr( -1 );
          mHbtEvent->setRefMultCorrWeight( 1 );
        }
        else {
          mHbtEvent->setCent16( mRefMultCorrUtil->getCentralityBin16() );
          mHbtEvent->setRefMultCorr( mRefMultCorrUtil->getRefMultCorr() );
          mHbtEvent->setRefMultCorrWeight( mRefMultCorrUtil->getWeight() );
          //modification for Au+Au 200GeV
          mHbtEvent->setRefMult( round( mRefMultCorrUtil->getRefMultCorr() ) );
        }
      } // else
#endif
    } // if (mUseRefMultCorr)
    else {
      mHbtEvent->setCent16( -1 );
      mHbtEvent->setRefMultCorr(-1);
      mHbtEvent->setRefMultCorrWeight( 1 );
    }

    mHbtEvent->setBTofTrayMult( picoEvent->btofTrayMultiplicity() );
    mHbtEvent->setNumberOfBTofMatched( picoEvent->nBTOFMatch() );
    mHbtEvent->setNumberOfBEMCMatched( picoEvent->nBEMCMatch() );
    // Could be recalculated, but skipped for now
    // mHbtEvent->setNumberOfPrimaryTracks()
    // mHbtEvent->setNumberOfGlobalTracks()
    mHbtEvent->setZdcAdcEast( picoEvent->ZdcSumAdcEast() );
    mHbtEvent->setZdcAdcWest( picoEvent->ZdcSumAdcWest() );

    mHbtEvent->setZdcCoincidenceRate( picoEvent->ZDCx() );
    mHbtEvent->setBbcCoincidenceRate( picoEvent->BBCx() );

    mHbtEvent->setSphericity( mSphericity );
    mHbtEvent->setSphericity2( mSphericity2 );
    mHbtEvent->setPrimaryVertex( picoEvent->primaryVertex() );
    mHbtEvent->setVpdVz( picoEvent->vzVpd() );
    mHbtEvent->setRanking( picoEvent->ranking() );
    mHbtEvent->setTriggerIds( picoEvent->triggerIds() );

    // Loop over picoTracks in the event
    for (unsigned int iTrk=0; iTrk<picoDst->numberOfTracks(); iTrk++) {

      // Retrieve i-th picoTrack
      StPicoTrack *picoTrack = (StPicoTrack*)picoDst->track(iTrk);
      if (!picoTrack) continue;

      // Create new instance of the StHbtTrack
      StHbtTrack *hbtTrack = new StHbtTrack();
      hbtTrack->setId( picoTrack->id() );
      hbtTrack->setFlag( 300 );
      hbtTrack->setNHits( picoTrack->nHits() * picoTrack->charge() );
      hbtTrack->setNHitsPossible( picoTrack->nHitsPoss() );
      hbtTrack->setNHitsDedx( picoTrack->nHitsDedx() );
      hbtTrack->setChi2( picoTrack->chi2() );
      hbtTrack->setDedxFromKeV( picoTrack->dEdx() );
      hbtTrack->setNSigmaElectron( picoTrack->nSigmaElectron() );
      hbtTrack->setNSigmaPion( picoTrack->nSigmaPion() );
      hbtTrack->setNSigmaKaon( picoTrack->nSigmaKaon() );
      hbtTrack->setNSigmaProton( picoTrack->nSigmaProton() );
      hbtTrack->setPidProbElectron( 0.5 );
      hbtTrack->setPidProbPion( 0.5 );
      hbtTrack->setPidProbKaon( 0.5 );
      hbtTrack->setPidProbProton( 0.5 );
      hbtTrack->setDca( picoTrack->origin().X() - picoEvent->primaryVertex().X(),
                        picoTrack->origin().Y() - picoEvent->primaryVertex().Y(),
                        picoTrack->origin().Z() - picoEvent->primaryVertex().Z() );
      if ( picoTrack->isPrimary() ) {
        hbtTrack->setP( picoTrack->pMom() );
      }
      else {
        hbtTrack->setP( 0., 0., 0. );
      }
      hbtTrack->setGlobalP( picoTrack->gMom() );
      hbtTrack->setPrimaryVertex( picoEvent->primaryVertex() );
      hbtTrack->setMagneticField( bField );
      hbtTrack->setTopologyMap(0, picoTrack->topologyMap(0) );
      hbtTrack->setTopologyMap(1, picoTrack->topologyMap(1) );
      if ( picoTrack->isTofTrack() ) {
        StPicoBTofPidTraits *trait = picoDst->btofPidTraits( picoTrack->bTofPidTraitsIndex() );
        if (!trait) {
          std::cout << "[WARNING] StHbtEvent* StHbtPicoDstReader::returnHbtEvent()"
                    << " -  No StPicoBTofPidTraits was found by the index" << std::endl;
          hbtTrack->setBeta( -999. );
        }
        else {
          hbtTrack->setBeta( trait->btofBeta() );
        }
      }
      else {
        hbtTrack->setBeta( -999. );
      }

      // Hidden info should be used for the MC data
      StHbtHiddenInfo *hiddenInfo = nullptr;
      hbtTrack->setHiddenInfo( hiddenInfo );

      // Check if a front-loaded cut exists. The mTrackCut
      // is inherited from StHbtBaseReader
      if ( mTrackCut && !mTrackCut->pass( hbtTrack ) ) {
        delete hbtTrack;
        continue;
      } // if ( mTrackCut )

      mHbtEvent->trackCollection()->push_back( hbtTrack );

    } // for (int iTrk=0; iTrk<picoDst->numberOfTracks(); iTrk++)

    // Check front-loaded cuts here, because now all event information
    // should be filled making event cut on it possible. The mEventCut
    // is inherited from StHbtBaseReader
    if (mEventCut && !mEventCut->pass(mHbtEvent) ) {
      delete mHbtEvent;
      mHbtEvent = nullptr;
      // return mHbtEvent; // Will be deleted 6 lines below
    } // if (mEventCut)

  } // else

  return mHbtEvent;
}

//_________________
void StHbtPicoDstReader::sphericityCalculation() {

  // Calculate sphericity values for two different acceptance cuts
  mSphericity = -1.;
  mSphericity2 = -1.;

  if (!mPicoDstReader) {
    std::cout << "[WARNING] void StHbtPicoDstReader::sphericityCalculation()"
              << " - No StPicoDstReader is provided" << std::endl;
    return;
  }

  StPicoDst *picoDst = (StPicoDst*)mPicoDstReader->picoDst();
  if ( !picoDst || picoDst->numberOfTracks()<=0 ) {
    std::cout << "[WARNING] void StHbtPicoDstReader::sphericityCalculation()"
              << " - No StPicoDst or picoTracks in the event" << std::endl;
    return;
  }

  // Primary vertex position (needed for DCA calculation)
  TVector3 pVtx = picoDst->event()->primaryVertex();

  // Next matrices will be used for the sphericity calculation
  TMatrixTSym<double> *matrix = new TMatrixTSym<double>(2);
  TMatrixTSym<double> *matrix2 = new TMatrixTSym<double>(2);
  matrix->Zero(); matrix2->Zero();

  float pTsum = 0.;
  float pTsum2 = 0.;
  float px = 0.;
  float py = 0.;
  float pt = 0.;

  // Loop over tracks
  for (unsigned int iTrk=0; iTrk<picoDst->numberOfTracks(); iTrk++) {
    // Retrieve i-th track
    StPicoTrack* picoTrack = (StPicoTrack*)picoDst->track(iTrk);
    // Track must exist and it must be primary
    if (!picoTrack || !picoTrack->isPrimary() ) continue;

    // Do not use questionably-reconstructed tracks in sphericity calculation
    if ( picoTrack->pPt() < 0.15 ||
         TMath::Abs( picoTrack->pMom().PseudoRapidity() ) > 1. ||
         picoTrack->gDCA(pVtx).Mag()>3. ||
         picoTrack->nHits() < 11 ) continue;

    // Values for sphericity in |eta|<1.
    px = picoTrack->pMom().X();
    py = picoTrack->pMom().Y();
    pt = picoTrack->pMom().Perp();

    (*matrix2)(0, 0) += px * px / pt;
    (*matrix2)(1, 1) += py * py / pt;
    (*matrix2)(0, 1) += px * py / pt;
    (*matrix2)(1, 0) += px * py / pt;
    pTsum2 += pt;

    // Values for sphericity in |eta|<0.5
    if ( TMath::Abs( picoTrack->pMom().PseudoRapidity() ) <= 0.5 ) {
      (*matrix)(0, 0) += px * px / pt;
      (*matrix)(1, 1) += py * py / pt;
      (*matrix)(0, 1) += px * py / pt;
      (*matrix)(1, 0) += px * py / pt;
      pTsum += pt;
    } // if ( TMath::Abs( picoTrack->pMom().PseudoRapidity() ) <= 0.5 )
  } // for (int iTrk=0; iTrk<picoDst->numberOfTracks(); iTrk++)

  *matrix *= 1./pTsum;
  *matrix2 *= 1./pTsum2;
  TMatrixDSymEigen eigenEstimator( *matrix );
  TMatrixDSymEigen eigenEstimator2( *matrix2 );
  TVectorD eigen = eigenEstimator.GetEigenValues();
  TVectorD eigen2 = eigenEstimator2.GetEigenValues();
  mSphericity = 2. * eigen.Min() / ( eigen[0] + eigen[1] );
  mSphericity2 = 2. * eigen2.Min() / ( eigen2[0] + eigen2[1] );
}
