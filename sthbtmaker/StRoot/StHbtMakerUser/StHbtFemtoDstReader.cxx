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
#include "StHbtFemtoDstReader.h"

// ROOT headers
#include "TMath.h"
#include "TMatrixDSymEigen.h"
#include "TVectorT.h"
#include "TMatrixTLazy.h"

#ifdef __ROOT__
ClassImp(StHbtFemtoDstReader)
#endif

//_________________
StHbtFemtoDstReader::StHbtFemtoDstReader() :
StHbtBaseEventReader(),
  mFemtoDstReader(nullptr),
  mHbtEvent(nullptr),
  mSphericity(-1.),
  mSphericity2(-1.),
  mEventsPassed(0),
  mMatrix(nullptr),
  mMatrix2(nullptr) {
  // Default Constructor

  // 0 - means good
  mReaderStatus = 0; // from StHbtBaseEventReader

  mMatrix = new TMatrixTSym<double>(2);
  mMatrix2 = new TMatrixTSym<double>(2);

}

//_________________
StHbtFemtoDstReader::StHbtFemtoDstReader(StFemtoDstReader *femtoDstReader, int debug) :
  StHbtBaseEventReader(),
  mFemtoDstReader(femtoDstReader),
  mHbtEvent(nullptr),
  mSphericity(-1.),
  mSphericity2(-1.),
  mEventsPassed(0),
  mMatrix(nullptr),
  mMatrix2(nullptr) {
  // Parametrized constructor
  mDebug = debug;
  // 0 - means good
  mReaderStatus = 0; // from StHbtBaseEventReader
  mMatrix = new TMatrixTSym<double>(2);
  mMatrix2 = new TMatrixTSym<double>(2);
}

//_________________
StHbtFemtoDstReader::StHbtFemtoDstReader(const StHbtFemtoDstReader& copy) :
  StHbtBaseEventReader(),
  mFemtoDstReader(copy.mFemtoDstReader),
  mHbtEvent(nullptr),
  mSphericity(copy.mSphericity),
  mSphericity2(copy.mSphericity2),
  mEventsPassed(0),
  mMatrix(nullptr),
  mMatrix2(nullptr) {
  // Copy constructor

  // 0 - means good
  mReaderStatus = 0; // from StHbtBaseEventReader
  mMatrix = new TMatrixTSym<double>(2);
  mMatrix2 = new TMatrixTSym<double>(2);
}

//_________________
StHbtFemtoDstReader& StHbtFemtoDstReader::operator=(const StHbtFemtoDstReader& copy) {
  // Assignment operator
  if (this != &copy) {
    mFemtoDstReader = copy.mFemtoDstReader;
    mSphericity = copy.mSphericity;
    mSphericity2 = copy.mSphericity2;
    mHbtEvent = nullptr;
  } // if (this != &copy)

  // 0 - means good
  mReaderStatus = 0; // from StHbtBaseEventReader
  mEventsPassed = 0;
  if (mMatrix) { delete mMatrix; mMatrix = new TMatrixTSym<double>(2); }
  if (mMatrix2) { delete mMatrix2; mMatrix = new TMatrixTSym<double>(2); }

  return *this;
}

//_________________
StHbtFemtoDstReader::~StHbtFemtoDstReader() {
  if(mFemtoDstReader)  { delete mFemtoDstReader; mFemtoDstReader = nullptr; }
  if(mHbtEvent)        { delete mHbtEvent; mHbtEvent = nullptr; }
  if(mMatrix)      { delete mMatrix; mMatrix = nullptr; }
  if(mMatrix2)     { delete mMatrix2; mMatrix = nullptr; }
}

//_________________
StHbtString StHbtFemtoDstReader::report() {
  // Make report
  StHbtString repstr = "\nStHbtString StHbtFemtoDstReader::report() - reporting\n";

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
StHbtEvent* StHbtFemtoDstReader::returnHbtEvent() {
  // Read femtoEvent, create StHbtEvent and return it to the StHbtAnalysis

  // Clean-up mHbtEvent from previous reading
  mHbtEvent = nullptr;

  // Check that StFemtoDstReader exists
  if (!mFemtoDstReader) {
    std::cout << "[ERROR] StHbtEvent* StHbtFemtoDstReader::returnHbtEvent() - no StFemtoDstReader is provided" << std::endl;
    mReaderStatus = 1;
    return mHbtEvent;
  }

  // Read (load) event
  mFemtoDstReader->readFemtoEvent(mEventsPassed);
  // Increment counter
  mEventsPassed++;

  // Check that femtoDst exists
  StFemtoDst* femtoDst = (StFemtoDst*)mFemtoDstReader->femtoDst();
  if (!femtoDst) {
    std::cout << "[ERROR] StHbtEvent* StHbtFemtoDstReader::returnHbtEvent() - "
	      << "no femtoDst is in StFemtoDstReader" << std::endl;
    mReaderStatus = 1;
    return mHbtEvent;
  }

  // Check that StFemtoEvent exists
  if ( !femtoDst->event() || femtoDst->numberOfTracks()<=0 ) {
    std::cout << "[WARNING] StHbtEvent* StHbtFemtoDstReader::returnHbtEvent()"
              << " - StFemtoEvent does not exist or particles missing"
              << std::endl;
    mReaderStatus = 1;
  }
  else {


    // Create new StHbtEvent
    mHbtEvent = new StHbtEvent();

    // Retrieve StFemtoEvent
    StFemtoEvent *femtoEvent = (StFemtoEvent*)femtoDst->event();

    // Initialize matrices with zeros
    mMatrix->Zero(); mMatrix2->Zero();

    float bField = femtoEvent->magneticField();

    mHbtEvent->setEventId(  femtoEvent->eventId() );
    mHbtEvent->setRunNumber(  femtoEvent->runId() );
    mHbtEvent->setBField( bField );

    mHbtEvent->setRefMult( femtoEvent->refMult() );
    mHbtEvent->setRefMultPos( femtoEvent->refMultPos() );
    mHbtEvent->setRefMultCorr( femtoEvent->refMultCorr() );
    mHbtEvent->setRefMultCorrWeight( femtoEvent->refMultCorrWeight() );
    mHbtEvent->setRefMult2( femtoEvent->refMult2() );
    mHbtEvent->setRefMult2Pos( femtoEvent->refMult2Pos() );
    mHbtEvent->setGRefMult( femtoEvent->gRefMult() );
    mHbtEvent->setGRefMultPos(0);
    mHbtEvent->setBTofTrayMult( femtoEvent->numberOfBTofHit() );
    mHbtEvent->setNumberOfBTofMatched( femtoEvent->numberOfTofMatched());
    mHbtEvent->setNumberOfBEMCMatched( femtoEvent->numberOfBEMCMatched() );
    mHbtEvent->setNumberOfPrimaryTracks(femtoEvent->numberOfPrimaryTracks());
    mHbtEvent->setNumberOfGlobalTracks( femtoEvent->numberOfGlobalTracks() );

    mHbtEvent->setZdcAdcEast( femtoEvent->zdcSumAdcEast() );
    mHbtEvent->setZdcAdcWest( femtoEvent->zdcSumAdcWest() );
    mHbtEvent->setZdcCoincidenceRate(0);
    mHbtEvent->setBbcCoincidenceRate(0);
    mHbtEvent->setEventPlaneAngle(0);
    mHbtEvent->setEventPlaneResolution(0);
    mHbtEvent->setCent16( femtoEvent->cent16() );
    mHbtEvent->setPrimaryVertex( femtoEvent->primaryVertex() );
    mHbtEvent->setVpdVz( femtoEvent->vpdVz() );
    mHbtEvent->setRanking( femtoEvent->ranking() );

    mHbtEvent->setTriggerIds( femtoEvent->triggerIds() );

    float pTsum = 0.;
    float pTsum2 = 0.;
    float px = 0.;
    float py = 0.;
    float pt = 0.;

    // Loop over femtoTracks in the event
    unsigned int mNFemtoTracks = femtoDst->numberOfTracks();
    for (unsigned int iTrk=0; iTrk<mNFemtoTracks; iTrk++) {

      // Retrieve i-th femtoTrack
      StFemtoTrack *femtoTrack = (StFemtoTrack*)femtoDst->track(iTrk);
      if (!femtoTrack) continue;

      // Create new instance of the StHbtTrack
      StHbtTrack *hbtTrack = new StHbtTrack();
      hbtTrack->setId( femtoTrack->id() );
      hbtTrack->setFlag( 300 );
      hbtTrack->setNHits( femtoTrack->nHits() * femtoTrack->charge() );
      hbtTrack->setNHitsPossible( femtoTrack->nHitsPoss() );
      hbtTrack->setNHitsDedx( femtoTrack->nHitsDedx() );
      hbtTrack->setChi2( femtoTrack->chi2() );
      hbtTrack->setDedx( femtoTrack->dEdx() );
      hbtTrack->setNSigmaElectron( femtoTrack->nSigmaElectron() );
      hbtTrack->setNSigmaPion( femtoTrack->nSigmaPion() );
      hbtTrack->setNSigmaKaon( femtoTrack->nSigmaKaon() );
      hbtTrack->setNSigmaProton( femtoTrack->nSigmaProton() );
      hbtTrack->setPidProbElectron(0.5);
      hbtTrack->setPidProbPion(0.5);
      hbtTrack->setPidProbKaon(0.5);
      hbtTrack->setPidProbProton(0.5);

      hbtTrack->setTopologyMap(0, femtoTrack->map0() );
      hbtTrack->setTopologyMap(1, femtoTrack->map1() );

      hbtTrack->setBeta(femtoTrack->beta());

      if ( femtoTrack->isPrimary() ) {
	hbtTrack->setP( femtoTrack->pMom() );
      }
      else {
	hbtTrack->setP( 0., 0., 0. );
      }
      hbtTrack->setGlobalP( femtoTrack->gMom() );
      hbtTrack->setDca( femtoTrack->origin().X() - femtoEvent->primaryVertex().X(),
			femtoTrack->origin().Y() - femtoEvent->primaryVertex().Y(),
			femtoTrack->origin().Z() - femtoEvent->primaryVertex().Z() );

      hbtTrack->setPrimaryVertex( femtoEvent->primaryVertex() );
      hbtTrack->setMagneticField( bField );

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

      // Further track analysis for sphericity calculation
      // Use only charged primary tracks
      if ( femtoTrack->charge() == 0 || !femtoTrack->isPrimary() )  continue;

      // Sphericity will be calculated only for tracks with pT>0.15 GeV/c, |eta|<1,
      // DCA<3 cm and nHits>=15
      if ( femtoTrack->pMom().Perp()<0.15 || TMath::Abs( femtoTrack->pMom().Eta() ) > 1. ||
	   femtoTrack->gDCA( femtoEvent->primaryVertex() ).Mag()>3. ||
	   femtoTrack->nHits()<15 ) continue;
      
      // Event properties in |eta|<1.
      px = femtoTrack->pMom().X();
      py = femtoTrack->pMom().Y();
      pt = femtoTrack->pMom().Z();

      (*mMatrix2)(0, 0) += px * px / pt;
      (*mMatrix2)(1, 1) += py * py / pt;
      (*mMatrix2)(0, 1) += px * py / pt;
      (*mMatrix2)(1, 0) += px * py / pt;
      pTsum2 += pt;

      // Event properties in |eta|<0.5
      if ( TMath::Abs( femtoTrack->pMom().Eta() ) <= 0.5 ) {
	(*mMatrix)(0, 0) += px * px / pt;
	(*mMatrix)(1, 1) += py * py / pt;
	(*mMatrix)(0, 1) += px * py / pt;
	(*mMatrix)(1, 0) += px * py / pt;
	pTsum += pt;
      } // if ( TMath::Abs( femtoTrack()->pMom().Eta() ) <= 0.5 )

    } // for (int iTrk=0; iTrk<picoDst->numberOfTracks(); iTrk++)

    mSphericity = -1.;
    mSphericity2 = -1.;
    if ( pTsum != 0 ) {
      *mMatrix *= 1./pTsum;
      TMatrixDSymEigen eigenEstimator( *mMatrix );
      TVectorD eigen = eigenEstimator.GetEigenValues();
      mSphericity = 2. * eigen.Min() / ( eigen[0] + eigen[1] );
    }
    if ( pTsum2 != 0 ) {
      *mMatrix2 *= 1./pTsum2;
      TMatrixDSymEigen eigenEstimator2( *mMatrix2 );
      TVectorD eigen2 = eigenEstimator2.GetEigenValues();
      mSphericity2 = 2. * eigen2.Min() / ( eigen2[0] + eigen2[1] );
    }

    mHbtEvent->setSphericity( mSphericity );
    mHbtEvent->setSphericity2( mSphericity2 );

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
