//
// Reader for the McDst format that takes McDstReader
//

// StHbtMaker headers
// Base
#include "StHbtMaker/StHbtBaseEventCut.h"
#include "StHbtMaker/StHbtBaseTrackCut.h"
#include "StHbtMaker/StHbtBaseV0Cut.h"
#include "StHbtMaker/StHbtBaseKinkCut.h"
#include "StHbtMaker/StHbtBaseXiCut.h"
// Infrastructure
#include "StHbtMaker/StHbtModelHiddenInfo.h"

// StHbtMakerUser headers
#include "StHbtMcDstReader.h"

// ROOT headers
#include "TMath.h"
#include "TMatrixDSymEigen.h"
#include "TVectorT.h"

#ifdef __ROOT__
ClassImp(StHbtMcDstReader)
#endif

//_________________
StHbtMcDstReader::StHbtMcDstReader() :
StHbtBaseEventReader(),
  mMcDstReader(nullptr),
  mMagField(-5.),
  mHbtEvent(nullptr),
  mDoRotate(false),
  mEventPlaneResolution(1.),
  mRefMult(0),
  mRefMultPos(0),
  mRefMult2(0),
  mRefMult2Pos(0),
  mSphericity(-1.),
  mSphericity2(-1.),
  mEventsPassed(0),
  mMatrix(nullptr),
  mMatrix2(nullptr) {
  // Default constructor
  mReaderStatus = 0;
  mRandom = new TRandom3(0);
  mPhi[0] = -100. * TMath::Pi();
  mPhi[1] =  100. * TMath::Pi();
  mMatrix = new TMatrixTSym<double>(2);
  mMatrix2 = new TMatrixTSym<double>(2);
  }

//_________________
StHbtMcDstReader::StHbtMcDstReader(McDstReader *reader, int debug) :
  StHbtBaseEventReader(),
  mMcDstReader(reader),
  mMagField(-5.),
  mHbtEvent(nullptr),
  mDoRotate(false),
  mEventPlaneResolution(1.),
  mRefMult(0),
  mRefMultPos(0),
  mRefMult2(0),
  mRefMult2Pos(0),
  mSphericity(-1.),
  mSphericity2(-1.),
  mEventsPassed(0),
  mMatrix(nullptr),
  mMatrix2(nullptr) {
  
  // Parametrized constructor
  mRandom = new TRandom3(0);
  // mDebug (defined in the base class)
  mDebug = debug;
  mPhi[0] = -100. * TMath::Pi();
  mPhi[1] =  100. * TMath::Pi();
  mMatrix = new TMatrixTSym<double>(2);
  mMatrix2 = new TMatrixTSym<double>(2);
}

//_________________
StHbtMcDstReader::StHbtMcDstReader(const StHbtMcDstReader& copy) :
  StHbtBaseEventReader(),
  mMcDstReader(copy.mMcDstReader),
  mMagField(copy.mMagField),
  mHbtEvent(nullptr),
  mDoRotate(copy.mDoRotate),
  mEventPlaneResolution(copy.mEventPlaneResolution),
  mRefMult(0),
  mRefMultPos(0),
  mRefMult2(0),
  mRefMult2Pos(0),
  mSphericity(-1.),
  mSphericity2(-1.),
  mEventsPassed(0),
  mMatrix(nullptr),
  mMatrix2(nullptr) {
  // Copy constructor
  if (mRandom) { delete mRandom; mRandom = new TRandom3(0); }
  mPhi[0] = copy.mPhi[0];
  mPhi[1] = copy.mPhi[1];
  mMatrix = new TMatrixTSym<double>(2);
  mMatrix2 = new TMatrixTSym<double>(2);
  }

//_________________
StHbtMcDstReader& StHbtMcDstReader::operator=(const StHbtMcDstReader& copy) {
  // Assignment operator
  if (this != &copy) {
    mMcDstReader = copy.mMcDstReader;
    mMagField = copy.mMagField;
    mHbtEvent = nullptr;
    mDoRotate = copy.mDoRotate;
    if (mRandom) { delete mRandom; mRandom = new TRandom3(0); }
    mPhi[0] = copy.mPhi[0];
    mPhi[1] = copy.mPhi[1];
    mEventPlaneResolution = copy.mEventPlaneResolution;
    mRefMult = 0;
    mRefMultPos = 0;
    mRefMult2 = 0;
    mRefMult2Pos = 0;
    mSphericity = -1.;
    mSphericity2 = -1.;
    mEventsPassed = 0;
    if (mMatrix) { delete mMatrix; mMatrix = new TMatrixTSym<double>(2); }
    if (mMatrix2) { delete mMatrix2; mMatrix = new TMatrixTSym<double>(2); }
  }

  return *this;
}

//_________________
StHbtMcDstReader::~StHbtMcDstReader() {
  // Destructor
  if(mMcDstReader) { delete mMcDstReader; mMcDstReader = nullptr; }
  if(mHbtEvent)    { delete mHbtEvent; mHbtEvent = nullptr; }
  if(mRandom)      { delete mRandom; mRandom = nullptr; }
  if(mMatrix)      { delete mMatrix; mMatrix = nullptr; }
  if(mMatrix2)     { delete mMatrix2; mMatrix = nullptr; }
}

//_________________
StHbtEvent* StHbtMcDstReader::returnHbtEvent() {
  // Read McDst and construct StHbtEvent

  // Clean-up mHbtEvent from previous reading
  mHbtEvent = nullptr;

  // Check that McDstReader exists
  if (!mMcDstReader) {
    std::cout << "[ERROR] StHbtEvent* StHbtMcDstReader::returnHbtEvent() - no McDstReader is provided" << std::endl;
    mReaderStatus = 1;
    return mHbtEvent;
  }

  // Load event
  mMcDstReader->loadEntry(mEventsPassed);
  // Increment counter
  mEventsPassed++;

  // Check that McDst exists
  McDst *mcDst = mMcDstReader->mcDst();
  if (!mcDst) {
    std::cout << "[ERROR] StHbtEvent* StHbtMcDstReader::returnHbtEvent() - no McDst is in McDstReader" << std::endl;
    mReaderStatus = 1;
    return mHbtEvent;
  }

  // Check that McEvent exists
  if ( !mcDst->event() || mcDst->numberOfParticles()<=0 ) {
    if ( !mcDst->event() ) {
      std::cout << "[WARNING] StHbtEvent* StHbtMcDstReader::returnHbtEvent()"
                << " - McEvent does not exist" << std::endl;
    }
    if ( mcDst->numberOfParticles()<=0 ) {
      std::cout << "[WARNING] StHbtEvent* StHbtMcDstReader::returnHbtEvent()"
                << " - No particles in the event were found" << std::endl;
    }
    mReaderStatus = 1;
  }
  else {
    // Create empty HBT event and then fill it
    mHbtEvent = new StHbtEvent();

    // Retrieve Monte Carlo event
    McEvent *mcEvent = (McEvent*)mcDst->event();

    // Simple protection
    if ( !mcEvent ) {
      delete mHbtEvent;
      mHbtEvent = nullptr;
      return mHbtEvent;
    }

    // Next matrices will be used for the sphericity calculation
    mMatrix->Zero(); mMatrix2->Zero();

    mHbtEvent->setEventNumber( mcEvent->eventNr() );
    mHbtEvent->setRunNumber( 0 );
    mHbtEvent->setMagneticField( mMagField );
    mHbtEvent->setNumberOfPrimaryTracks( 0 );
    mHbtEvent->setCent16(-1);
    mHbtEvent->setImpactParameter( mcEvent->impact() );

    double azimuthalAngle = 0.;
    double phi = mcEvent->phi();
    // Generate rotation angle by request
    if (mDoRotate) {
      phi = mRandom->Uniform( mPhi[0], mPhi[1] );
    }
    mHbtEvent->setEventPlaneAngle(phi);
    // Set ideal resolution
    mHbtEvent->setEventPlaneResolution(mEventPlaneResolution);

    // Initialize values
    mRefMult = 0;
    mRefMultPos = 0;
    mRefMult2 = 0;
    mRefMult2Pos = 0;
    mSphericity = -1.;
    mSphericity2 = -1.;

    float pTsum = 0.;
    float pTsum2 = 0.;
    float px = 0.;
    float py = 0.;
    float pz = 0.;
    float pt = 0.;

    // Track loop
    for(unsigned int iTrk=0; iTrk<mcDst->numberOfParticles(); iTrk++) {

      // Retrieve i-th particle
      McParticle *particle = (McParticle*)mcDst->particle(iTrk);
      if ( !particle ) {
        std::cout << "[WARNING] StHbtEvent* StHbtMcDstReader::returnHbtEvent() - Particle does not exist"
                  << std::endl;
        continue;
      } // if(!trk)

      // Create new StHbtTrack and fill it with required information
      StHbtTrack *hbtTrack = new StHbtTrack();
      hbtTrack->setId( particle->index() );
      // Set number of hits (45 correspond to the number
      // of pad row in STAR TPC)
      // IMPORTANT!!!! nHits also stores charge as: nHits * charge
      // but charge in the TDataBasePDF is 3 for positive and -3 for negative
      if ( particle->charge()>0 ) {
        hbtTrack->setNHits( 45 );
      }
      else if ( particle->charge()==0 ) {
        hbtTrack->setNHits( 0 );
      }
      else {
        hbtTrack->setNHits( -45 );
      }
      hbtTrack->setNHitsPossible( 45 );
      hbtTrack->setNHitsDedx( 45 );
      hbtTrack->setChi2( 1. );
      hbtTrack->setDedx( dEdxMean( particle->mass(), particle->ptot() ) );
      if ( TMath::Abs(particle->pdg()) == 211) {
        // Pion
        hbtTrack->setNSigmaElectron(-65.);
        hbtTrack->setNSigmaPion(0.);
        hbtTrack->setNSigmaKaon(65.);
        hbtTrack->setNSigmaProton(65.);

        hbtTrack->setPidProbElectron(0.);
        hbtTrack->setPidProbPion(1.);
        hbtTrack->setPidProbKaon(0.);
        hbtTrack->setPidProbProton(0.);
      }
      else if ( TMath::Abs(particle->pdg()) == 321 ) {
        // Kaon
        hbtTrack->setNSigmaElectron(-65.);
        hbtTrack->setNSigmaPion(-65.);
        hbtTrack->setNSigmaKaon(0.);
        hbtTrack->setNSigmaProton(65.);

        hbtTrack->setPidProbElectron(0.);
        hbtTrack->setPidProbPion(0.);
        hbtTrack->setPidProbKaon(1.);
        hbtTrack->setPidProbProton(0.);
      }
      else if ( TMath::Abs(particle->pdg()) == 2212 ) {
        // Proton
        hbtTrack->setNSigmaElectron(-65.);
        hbtTrack->setNSigmaPion(-65.);
        hbtTrack->setNSigmaKaon(-65.);
        hbtTrack->setNSigmaProton(0.);

        hbtTrack->setPidProbElectron(0.);
        hbtTrack->setPidProbPion(0.);
        hbtTrack->setPidProbKaon(0.);
        hbtTrack->setPidProbProton(1.);
      }
      else if ( TMath::Abs(particle->pdg()) == 11 ) {
        // Electron
        hbtTrack->setNSigmaElectron(0.);
        hbtTrack->setNSigmaPion(65.);
        hbtTrack->setNSigmaKaon(65.);
        hbtTrack->setNSigmaProton(65.);

        hbtTrack->setPidProbElectron(1.);
        hbtTrack->setPidProbPion(0.);
        hbtTrack->setPidProbKaon(0.);
        hbtTrack->setPidProbProton(0.);
      }
      else {
        // Other particles
        hbtTrack->setNSigmaElectron(-65.);
        hbtTrack->setNSigmaPion(-65.);
        hbtTrack->setNSigmaKaon(-65.);
        hbtTrack->setNSigmaProton(-65.);

        hbtTrack->setPidProbElectron(0.);
        hbtTrack->setPidProbPion(0.);
        hbtTrack->setPidProbKaon(0.);
        hbtTrack->setPidProbProton(0.);
      }

      // McParticle stores emission point (last or decay point) in fm,
      // but DCA is stored in cm
      hbtTrack->setDca( particle->x() * 1e-13,
                        particle->y() * 1e-13,
                        particle->x() * 1e-13 );

      px = particle->px();
      py = particle->py();
      pz = particle->pz();
      pt = particle->pt();
      
      if (mDoRotate) {
        hbtTrack->setPz( pz );
        hbtTrack->setGlobalPz( pz );
        azimuthalAngle = particle->phi();
        azimuthalAngle += phi;
        hbtTrack->setPx( pt * TMath::Cos(azimuthalAngle) );
        hbtTrack->setPy( pt * TMath::Sin(azimuthalAngle) );
        hbtTrack->setGlobalPx( pt * TMath::Cos(azimuthalAngle) );
        hbtTrack->setGlobalPy( pt * TMath::Sin(azimuthalAngle) );
      }
      else {
        hbtTrack->setP( px, py, pz );
        hbtTrack->setGlobalP( px, pt, pz );
      }

      // McDst assumes that event happen at (0.,0.,0.)
      hbtTrack->setPrimaryVertex(0., 0., 0.);
      hbtTrack->setMagneticField( mMagField );
      // Set topology map (probably can insert probabilty function from data)
      hbtTrack->setTopologyMap(0, 0.);
      hbtTrack->setTopologyMap(1, 0.);

      hbtTrack->setBeta( particle->ptot() / particle->energy() );

      // Create model hidden info and fill it
      StHbtModelHiddenInfo *hiddenInfo = new StHbtModelHiddenInfo();

      // px and py values are not a mistake and take into
      // account event plane angle rotation
      hiddenInfo->setTrueMomentum( hbtTrack->p().X(),
                                   hbtTrack->p().Y(),
                                   pz );

      // Check if rotate event plane angle (IS IT NEEDED??)
      if (mDoRotate) {
        double radialPos = TMath::Sqrt( particle->x() * particle->x() +
                                        particle->y() * particle->y() );
        azimuthalAngle = TMath::ATan2( particle->y(), particle->x() );
        azimuthalAngle += phi;
        hiddenInfo->setEmissionPoint( radialPos * TMath::Cos( azimuthalAngle ),
                                      radialPos * TMath::Sin( azimuthalAngle ),
                                      particle->z(),
                                      particle->t() );
      }
      else {
        hiddenInfo->setEmissionPoint( particle->x(),
                                      particle->y(),
                                      particle->z(),
                                      particle->t() );
      }
      hiddenInfo->setPdgPid( particle->pdg() );
      hiddenInfo->setOrigin( 0 );
      hbtTrack->setHiddenInfo( hiddenInfo );

      // Check if a front-loaded cut exists. The mTrackCut
      // is inherited from StHbtBaseReader
      if ( mTrackCut && !mTrackCut->pass(hbtTrack) ) {
        delete hbtTrack;
        continue;
      } // if ( mTrackCut )

      // Add track to track collection
      mHbtEvent->trackCollection()->push_back( hbtTrack );

      //
      // Calculate event properties: refMult, sphericity
      //

      // In the experiment, one works only with charged particles
      if (particle->charge() == 0) continue;
      // Remove nucleons from incoming nuclei (should work for UrQMD)
      //if (particle->parent() == 0) continue;

      // Particle must have pT>0.15 GeV/c and |eta|<1 (STAR acceptance)
      if ( TMath::Abs( particle->eta() ) > 1. ||
	   pt<0.15 ) continue;

      mRefMult2++;
      if ( particle->charge() > 0 ) {
	mRefMult2Pos++;
      }

      // Event properties in |eta|<1.
      px = particle->px();
      py = particle->py();
      pt = particle->pt();

      (*mMatrix2)(0, 0) += px * px / pt;
      (*mMatrix2)(1, 1) += py * py / pt;
      (*mMatrix2)(0, 1) += px * py / pt;
      (*mMatrix2)(1, 0) += px * py / pt;
      pTsum2 += pt;

      // Event properties in |eta|<0.5
      if ( TMath::Abs( particle->eta() ) <= 0.5 ) {
	mRefMult++;
	if ( particle->charge() > 0 ) {
	  mRefMultPos++;
	}

	(*mMatrix)(0, 0) += px * px / pt;
	(*mMatrix)(1, 1) += py * py / pt;
	(*mMatrix)(0, 1) += px * py / pt;
	(*mMatrix)(1, 0) += px * py / pt;
	pTsum += pt;
      } // if ( TMath::Abs( particle->eta() ) <= 0.5 )
      
    } // for(int iTrk=0; iTrk<mcDst->numberOfParticles(); iTrk++)

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

    mHbtEvent->setPrimaryVertex(0., 0., 0.);
    mHbtEvent->setRefMult( mRefMult );
    mHbtEvent->setRefMultPos( mRefMultPos );
    mHbtEvent->setRefMult2( mRefMult2 );
    mHbtEvent->setRefMult2Pos( mRefMult2Pos );
    mHbtEvent->setGRefMult( mRefMult );
    mHbtEvent->setGRefMultPos( mRefMultPos );
    mHbtEvent->setBTofTrayMult( mRefMult );
    mHbtEvent->setNumberOfBTofMatched( mRefMult );
    mHbtEvent->setNumberOfBEMCMatched( mRefMult );
    mHbtEvent->setSphericity( mSphericity );
    mHbtEvent->setSphericity2( mSphericity2 );

    // Check front-loaded cuts here, because now all event information
    // should be filled making event cut on it possible. The mEventCut
    // is inherited from StHbtBaseReader
    if (mEventCut && !mEventCut->pass( mHbtEvent ) ) {
      delete mHbtEvent;
      mHbtEvent = nullptr;
      // return mHbtEvent; // Will be deleted 6 lines below
    } // if (mEventCut)
  } // else {

  return mHbtEvent;
}

//_________________
double StHbtMcDstReader::dEdxMean(Double_t mass, Double_t momentum) {

  Double_t dedxMean = 0.;
  Double_t tpcDedxGain = 0.174325e-06;
  Double_t tpcDedxOffset = -2.71889;
  Double_t tpcDedxRise = 776.626;

  Double_t gamma = TMath::Sqrt(momentum*momentum/(mass*mass)+1.);
  Double_t beta = TMath::Sqrt(1. - 1./(gamma*gamma));
  Double_t rise = tpcDedxRise* beta*beta*gamma*gamma;
  if ( beta > 0) {
    dedxMean = tpcDedxGain / (beta * beta) * ( 0.5 * TMath::Log(rise) -
                                               beta*beta - tpcDedxOffset );
  }
  else {
    dedxMean = 1000.;
  }
  return dedxMean;
}

//_________________
StHbtString StHbtMcDstReader::report() {
  // Make a report
  StHbtString repstr = "\nStHbtString StHbtMcDstReader::report() - reporting\n";

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
