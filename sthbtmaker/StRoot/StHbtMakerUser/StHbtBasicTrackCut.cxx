//
// The basic track cut
//

// C++ headers
#include <iostream>

// StHbtMaker headers
#include "StHbtMaker/phys_constants.h"

// StHbtMakerUser headers
#include "StHbtBasicTrackCut.h"

// ROOT headers
#include "TString.h"
#include "TMath.h"

#ifdef __ROOT__
ClassImp(StHbtBasicTrackCut)
#endif

//_________________
StHbtBasicTrackCut::StHbtBasicTrackCut() :
  StHbtBaseTrackCut(),
  mType(true),
  mCharge(1),
  mNHitsRat(0),
  mDetSelection(3),
  mPidSelection(HbtPID::Pion),
  mNTracksPassed(0),
  mNTracksFailed(0) {
  // Default constructor

  mNHits[0] = 10;
  mNHits[1] = 100;
  mPt[0] = 0.05;
  mPt[1] = 2.;
  mP[0] = 0.05;
  mP[1] = 2.;
  mRapidity[0] = -1e6;
  mRapidity[1] = 1e6;
  mEta[0] = -1.;
  mEta[1] = 1.;
  mDCA[0] = -0.1;
  mDCA[1] = 3.;

  mNSigmaElectron[0] = -100.;
  mNSigmaElectron[1] = 100.;
  mNSigmaPion[0] = -100.0;
  mNSigmaPion[1] = 100.0;
  mNSigmaKaon[0] = -100.0;
  mNSigmaKaon[1] = 100.0;
  mNSigmaProton[0] = -100.0;
  mNSigmaProton[1] = 100.0;
  mNSigmaOther[0] = 0.;
  mNSigmaOther[1] = 0.;
  mTpcMom[0] = 0.1;
  mTpcMom[1] = 0.55;

  mTofMassSqr[0] = -0.15;
  mTofMassSqr[1] = 1.2;
  mTofMom[0] = 0.1;
  mTofMom[1] = 1.45;

  mTnTNSigmaElectron[0] = -100.;
  mTnTNSigmaElectron[1] = 100.;
  mTnTNSigmaPion[0] = -100.;
  mTnTNSigmaPion[1] = 100.;
  mTnTNSigmaKaon[0] = -100.;
  mTnTNSigmaKaon[1] = 100.;
  mTnTNSigmaProton[0] = -100.;
  mTnTNSigmaProton[1] = 100.;

  mIsTheory = false;
  // Positive pion
  mPdgId = 211;
  mInvBetaDiff[0] = -1e6;
  mInvBetaDiff[1] = 1e6;
  mPthresh = 0.45;
  mVerbose = false;
}

//_________________
StHbtBasicTrackCut::StHbtBasicTrackCut(const StHbtBasicTrackCut& c) :
  StHbtBaseTrackCut(c),
  mType(c.mType),
  mCharge(c.mCharge),
  mNHitsRat(c.mNHitsRat),
  mDetSelection(c.mDetSelection),
  mPidSelection(c.mPidSelection),
  mNTracksPassed(0),
  mNTracksFailed(0) {
  // Copy constructor

  mNHits[0] = c.mNHits[0];
  mNHits[1] = c.mNHits[1];
  mPt[0] = c.mPt[0];
  mPt[1] = c.mPt[1];
  mP[0] = c.mP[0];
  mP[1] = c.mP[1];
  mRapidity[0] = c.mRapidity[0];
  mRapidity[1] = c.mRapidity[1];
  mEta[0] = c.mEta[0];
  mEta[1] = c.mEta[1];
  mDCA[0] = c.mDCA[0];
  mDCA[1] = c.mDCA[1];

  mNSigmaElectron[0] = c.mNSigmaElectron[0];
  mNSigmaElectron[1] = c.mNSigmaElectron[1];
  mNSigmaPion[0] = c.mNSigmaPion[0];
  mNSigmaPion[1] = c.mNSigmaPion[1];
  mNSigmaKaon[0] = c.mNSigmaKaon[0];
  mNSigmaKaon[1] = c.mNSigmaKaon[1];
  mNSigmaProton[0] = c.mNSigmaProton[0];
  mNSigmaProton[1] = c.mNSigmaProton[1];
  mNSigmaOther[0] = c.mNSigmaOther[0];
  mNSigmaOther[1] = c.mNSigmaOther[1];
  mTpcMom[0] = c.mTpcMom[0];
  mTpcMom[1] = c.mTpcMom[1];

  mTofMassSqr[0] = c.mTofMassSqr[0];
  mTofMassSqr[1] = c.mTofMassSqr[1];
  mTofMom[0] = c.mTofMom[0];
  mTofMom[1] = c.mTofMom[1];

  mTnTNSigmaElectron[0] = c.mTnTNSigmaElectron[0];
  mTnTNSigmaElectron[1] = c.mTnTNSigmaElectron[1];
  mTnTNSigmaPion[0] = c.mTnTNSigmaPion[0];
  mTnTNSigmaPion[1] = c.mTnTNSigmaPion[1];
  mTnTNSigmaKaon[0] = c.mTnTNSigmaKaon[0];
  mTnTNSigmaKaon[1] = c.mTnTNSigmaKaon[1];
  mTnTNSigmaProton[0] = c.mTnTNSigmaProton[0];
  mTnTNSigmaProton[1] = c.mTnTNSigmaProton[1];

  mIsTheory = c.mIsTheory;
  mPdgId = c.mPdgId;
  mInvBetaDiff[0] = c.mInvBetaDiff[0];
  mInvBetaDiff[1] = c.mInvBetaDiff[1];
  mPthresh = c.mPthresh;
  mVerbose = c.mVerbose;
}

//_________________
StHbtBasicTrackCut& StHbtBasicTrackCut::operator=(const StHbtBasicTrackCut& c) {
  // Assignment operator
  if ( this != &c ) {
    StHbtBaseTrackCut::operator=(c);
    mType = c.mType;
    mCharge = c.mCharge;
    mNHits[0] = c.mNHits[0];
    mNHits[1] = c.mNHits[1];
    mNHitsRat = c.mNHitsRat;
    mPt[0] = c.mPt[0];
    mPt[1] = c.mPt[1];
    mP[0] = c.mP[0];
    mP[1] = c.mP[1];
    mRapidity[0] = c.mRapidity[0];
    mRapidity[1] = c.mRapidity[1];
    mEta[0] = c.mEta[0];
    mEta[1] = c.mEta[1];
    mDCA[0] = c.mDCA[0];
    mDCA[1] = c.mDCA[1];

    mDetSelection = c.mDetSelection;

    mNSigmaElectron[0] = c.mNSigmaElectron[0];
    mNSigmaElectron[1] = c.mNSigmaElectron[1];
    mNSigmaPion[0] = c.mNSigmaPion[0];
    mNSigmaPion[1] = c.mNSigmaPion[1];
    mNSigmaKaon[0] = c.mNSigmaKaon[0];
    mNSigmaKaon[1] = c.mNSigmaKaon[1];
    mNSigmaProton[0] = c.mNSigmaProton[0];
    mNSigmaProton[1] = c.mNSigmaProton[1];
    mNSigmaOther[0] = c.mNSigmaOther[0];
    mNSigmaOther[1] = c.mNSigmaOther[1];
    mTpcMom[0] = c.mTpcMom[0];
    mTpcMom[1] = c.mTpcMom[1];

    mTofMassSqr[0] = c.mTofMassSqr[0];
    mTofMassSqr[1] = c.mTofMassSqr[1];
    mTofMom[0] = c.mTofMom[0];
    mTofMom[1] = c.mTofMom[1];

    mTnTNSigmaElectron[0] = c.mTnTNSigmaElectron[0];
    mTnTNSigmaElectron[1] = c.mTnTNSigmaElectron[1];
    mTnTNSigmaPion[0] = c.mTnTNSigmaPion[0];
    mTnTNSigmaPion[1] = c.mTnTNSigmaPion[1];
    mTnTNSigmaKaon[0] = c.mTnTNSigmaKaon[0];
    mTnTNSigmaKaon[1] = c.mTnTNSigmaKaon[1];
    mTnTNSigmaProton[0] = c.mTnTNSigmaProton[0];
    mTnTNSigmaProton[1] = c.mTnTNSigmaProton[1];

    mPidSelection = c.mPidSelection;

    mIsTheory = c.mIsTheory;
    mPdgId = c.mPdgId;
    mInvBetaDiff[0] = c.mInvBetaDiff[0];
    mInvBetaDiff[1] = c.mInvBetaDiff[1];
    mPthresh = c.mPthresh;
    mVerbose = c.mVerbose;

    mNTracksPassed = 0;
    mNTracksFailed = 0;
  }

  return *this;
}

//_________________
StHbtBasicTrackCut::~StHbtBasicTrackCut() {
  /* emtpy */
}

//_________________
bool StHbtBasicTrackCut::pass(const StHbtTrack* t) {
  
  // Test the particle and return true if it meets all the criteria
  // false if it doesn't meet at least one of the criteria

  if ( mVerbose ) {
    std::cout << "\n -- StHbtBasicTrackCut-- \n";
  }

  // Check track type (1 - primary, 0 - global )
  const bool goodType = ( mType == t->type() );
  if ( mVerbose ) {
    std::cout << Form("Type      : %d == %d \t %s \n", t->type(), mType, ( goodType ) ? "true" : "false");
  }
  if ( !goodType ) {
    // Increment number of failed tracks
    mNTracksFailed++;
    return false;
  }
  
  // Use for TLorentzVector vec esitmation (for further selection criteria)
  const bool primTrk = ( goodType && t->isPrimary() );
  TLorentzVector vec;
  if( primTrk ) {
    vec.SetXYZM( t->pMom().X(), t->pMom().Y(), t->pMom().Z(), mMass );
  }
  else {
    vec.SetXYZM( t->gMom().X(), t->gMom().Y(), t->gMom().Z(), mMass );
  }

  // For theoretical estimations
  if (mIsTheory) {
    if ( !t->hiddenInfo() ) {
      std::cout << "[WARNING] StHbtBasicTrackCut::pass(const StHbtTrack* t) "
                << "- Track does not have hidden info" << std::endl;
      // Increment number of failed tracks
      mNTracksFailed++;
      return false;
    }

    if ( mVerbose ) {
      std::cout << Form("PdgId      : %d == %d \t %s \n", t->hiddenInfo()->pdgId(), mPdgId,
			( t->hiddenInfo()->pdgId()==mPdgId ) ? "true" : "false");
    }
    if ( mPdgId != t->hiddenInfo()->pdgId() ) {
      // Increment number of failed tracks
      mNTracksFailed++;
      return false;
    }
  }

  // Check particle charge
  const bool goodCharge = ( mCharge == (char)t->charge() );
  if ( mVerbose ) {
    std::cout << Form("Charge    : %d == %d \t %s \n", t->charge(), mCharge, goodCharge ? "true" : "false");
  }
  if ( !goodCharge ) {
    // Increment number of failed tracks
    mNTracksFailed++;
    return false;
  }
  
  // Check kinematics
  const bool goodKine = isGoodKine( t, vec );
  if ( mVerbose ) {
    std::cout << Form("Pass kine : %s \n", ( goodKine ) ? "true" : "false" );
  }
  // Check just first particles cuts without PID (fasten track processing)
  if( !goodKine ) {
    // Increment number of failed tracks
    mNTracksFailed++;
    return false;
  }

  bool goodPID = false;

  // Choose identification scheme
  if( mDetSelection == 0 ) {       // TPC selection
    goodPID = isGoodCleanTpcPid( t, vec );
  }
  else if ( mDetSelection == 1 ) { // TOF selection
    goodPID = isGoodTofPid( t );
  }
  else if ( mDetSelection == 2 ) { // TPC+TOF selection
    goodPID = isGoodTnT( t );
  }
  else if ( mDetSelection == 3 ) { // if(TOF) {TPC+TOF} else {TPC}
    goodPID = isGoodToT( t, vec );
  }
  else if ( mDetSelection == 4 ) { // if (TOF && p>Pthreshold) {TPC+TOF} else {TPC}
    goodPID = isGoodToTThresh( t, vec );
  }
  else {
    std::cout << "[ERROR] StHbtBasicTrackCut: Wrong particle identification scheme "
	      << mDetSelection << std::endl;
    return false;
  }

  if ( mVerbose ) {
    std::cout << Form("goodPID     : %s \n", ( goodPID ) ? "true" : "false" );
  }
  
  // Final calculation
  const bool goodTrack = goodCharge && goodType && goodKine && goodPID;

  if ( mVerbose ) {
    std::cout << Form("goodTrack   : %s \n", ( goodTrack ) ? "true" : "false" );
  }

  // Choose your destiny
  goodTrack ? mNTracksPassed++ : mNTracksFailed++;
  return goodTrack;
}

//_________________
StHbtString StHbtBasicTrackCut::report() {
  // Construct report
  TString report;

  report += TString::Format( "Particle mass:\t%E\n", mMass );
  report += TString::Format( "Particle type:\t%d\n", mType );
  report += TString::Format( "Particle charge:\t%d\n", mCharge );
  report += TString::Format( "Particle nhits:\t%d - %d\n", mNHits[0], mNHits[1] );
  report += TString::Format( "Particle nHitsFit/nHitsPossible:\t%E\n", mNHitsRat );
  report += TString::Format( "Particle pT:\t%E - %E\n", mPt[0], mPt[1] );
  report += TString::Format( "Particle p:\t%E - %E\n", mP[0], mP[1] );
  report += TString::Format( "Particle rapidity:\t%E - %E\n", mRapidity[0], mRapidity[1] );
  report += TString::Format( "Particle pseudoRapidity:\t%E - %E\n", mEta[0], mEta[1] );
  report += TString::Format( "Particle DCA:\t%E - %E\n", mDCA[0], mDCA[1] );
  report += TString::Format( "Particle nSigma from electron:\t%E - %E\n", mNSigmaElectron[0], mNSigmaElectron[1] );
  report += TString::Format( "Particle nSigma from pion:\t%E - %E\n", mNSigmaPion[0], mNSigmaPion[1] );
  report += TString::Format( "Particle nSigma from kaon:\t%E - %E\n", mNSigmaKaon[0], mNSigmaKaon[1] );
  report += TString::Format( "Particle nSigma from proton:\t%E - %E\n", mNSigmaProton[0], mNSigmaProton[1] );
  report += TString::Format( "Particle nSigma from other:\t%E - %E\n", mNSigmaOther[0], mNSigmaOther[1] );
  report += TString::Format( "Particle TPC momentum:\t%E - %E\n", mTpcMom[0], mTpcMom[1] );
  report += TString::Format( "Particle TOF mass square:\t%E - %E\n", mTofMassSqr[0], mTofMassSqr[1] );
  report += TString::Format( "Particle TOF momentum:\t%E - %E\n", mTofMom[0], mTofMom[1] );
  report += TString::Format( "Particle TPC+TOF nSigma for electron:\t%E - %E\n", mTnTNSigmaElectron[0], mTnTNSigmaElectron[1] );
  report += TString::Format( "Particle TPC+TOF nSigmat for pion:\t%E - %E\n", mTnTNSigmaPion[0], mTnTNSigmaPion[1] );
  report += TString::Format( "Particle TPC+TOF nSigmat for kaon:\t%E - %E\n", mTnTNSigmaKaon[0], mTnTNSigmaKaon[1] );
  report += TString::Format( "Particle TPC+TOF nSigmat for proton:\t%E - %E\n", mTnTNSigmaProton[0], mTnTNSigmaProton[1] );
  if ( mPidSelection == HbtPID::Electron ) {
    report += TString::Format( "Particle PID to select: electron\n" );
  }
  else if( mPidSelection == HbtPID::Pion ) {
    report += TString::Format( "Particle PID to select: pion\n" );
  }
  else if( mPidSelection == HbtPID::Kaon ) {
    report += TString::Format( "Particle PID to select: kaon\n" );
  }
  else if( mPidSelection == HbtPID::Proton ) {
    report += TString::Format( "Particle PID to select: proton\n" );
  }
  else {
    report += TString::Format( "Particle PID to select: unknown\n" );
  }
  report += TString::Format( "Number of tracks which passed:\t%u  Number which failed:\t%u\n",
			     mNTracksPassed, mNTracksFailed);

    return StHbtString((const char *)report);
}

//_________________
TList *StHbtBasicTrackCut::listSettings() {

  // Return a list of settings in a writable form
  TList *settings_list = new TList();

  settings_list->AddVector(
    new TObjString( TString::Format( "StHbtBasicTrackCut.mass=%f", mMass ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.type=%u", mType ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.charge=%i", mCharge) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nhits.min=%u", mNHits[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nhits.max=%u", mNHits[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nhits.nhitsratio=%f", mNHitsRat ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.pt.min=%f", mPt[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.pt.max=%f", mPt[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.p.min=%f", mP[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.p.max=%f", mP[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.rapidity.min=%f", mRapidity[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.rapidity.max=%f", mRapidity[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.pseudorapidity.min=%f", mEta[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.pseudorapidity.max=%f", mEta[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.dca.min=%f", mDCA[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.dca.max=%f", mDCA[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmaelectron.min=%f", mNSigmaElectron[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmaelectron.max=%f", mNSigmaElectron[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmapion.min=%f", mNSigmaPion[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmapion.max=%f", mNSigmaPion[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmakaon.min=%f", mNSigmaKaon[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmakaon.max=%f", mNSigmaKaon[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmaproton.min=%f", mNSigmaProton[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmaproton.max=%f", mNSigmaProton[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmaother.min=%f", mNSigmaOther[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.nsigmaother.max=%f", mNSigmaOther[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tpcmom.min=%f", mTpcMom[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tpcmom.max=%f", mTpcMom[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tofmasssqr.min=%f", mTofMassSqr[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tofmasssqr.max=%f", mTofMassSqr[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tofmom.min=%f", mTofMom[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tofmom.max=%f", mTofMom[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmaelectron.min=%f", mTnTNSigmaElectron[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmaelectron.max=%f", mTnTNSigmaElectron[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmapion.min=%f", mTnTNSigmaPion[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmapion.max=%f", mTnTNSigmaPion[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmakaon.min=%f", mTnTNSigmaKaon[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmakaon.max=%f", mTnTNSigmaKaon[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmaproton.min=%f", mTnTNSigmaProton[0] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.tntnsigmaproton.max=%f", mTnTNSigmaProton[1] ) ),
    new TObjString( TString::Format( "StHbtBasicTrackCut.hbtpid=%d", mPidSelection) ),
    NULL
			   );

  return settings_list;
}

//_________________
void StHbtBasicTrackCut::setNHits(const short& lo, const short& hi) {

  short low = 0;
  short high = 100;
  // Check that not error is made in setting the low/high values
  if ( lo > hi ) {
    std::cout << "[WARNING] StHbtBasicTrackCut::setNHits() -- bad nhits limits (low,high): ("
	      << low << "," << hi << ")" << std::endl;
  }
  else {
    low = lo;
    high = hi;
  }

  // Low value
  if (low <=0 ) {
    mNHits[0] = 0;
  }
  else {
    mNHits[0] = ( ( low > std::numeric_limits<unsigned char>::max() ) ?
		  std::numeric_limits<unsigned char>::max() :
		  (unsigned char)low );
  }

  // High value
  if (high <=0 ) {
    mNHits[1] = 0;
  }
  else {
    mNHits[1] = ( ( high > std::numeric_limits<unsigned char>::max() ) ?
		  std::numeric_limits<unsigned char>::max() :
		  (unsigned char)high );
  }
}

//_________________
void StHbtBasicTrackCut::setCharge(const short& charge) {

  // Check the value of particle charge:
  // if it == 0, then use zero value but throw the warning
  // if <0, then check the range. In case of out of range (< CHAR_MIN) assign -1
  // if >0, then check the range. In case of out of range (> CHAR_MAX) assign +1
  if (charge == 0) {
    std::cout << "[WARNING] StHbtBasicTrackCut::setCharge() -- charge=0 is requested" << std::endl;
    mCharge = 0;
  }
  else if ( charge<0 ) {
    mCharge = ( ( charge < std::numeric_limits<char>::min() ) ?
		-1 : (char)charge );
  }
  else {
    mCharge = ( (charge > std::numeric_limits<char>::max() ) ?
		+1 : (char) charge );
  }
}

//_________________
bool StHbtBasicTrackCut::isGoodCleanTpcPid(const StHbtTrack *t, TLorentzVector vec) {
  
  bool goodClean = false;
  if ( mPidSelection == HbtPID::Electron ) {    // Electron
    goodClean = isTpcCleanElectron( t, vec );
  }
  else if ( mPidSelection == HbtPID::Pion ) {   // Pion
    goodClean = isTpcCleanPion( t, vec );
  }
  else if ( mPidSelection == HbtPID::Kaon ) {   // Kaon
    goodClean = isTpcCleanKaon( t, vec );
  }
  else if ( mPidSelection == HbtPID::Proton ) { // Proton
    goodClean = isTpcCleanProton( t, vec );
  }
  else {
    std::cout << "[ERROR] StHbtBasicTrackCut::isGoodCleanTpcPid -- Wrong HbtPID selection"
	      << mPidSelection << std::endl;
  }

  if ( mVerbose ) {
    std::cout << Form("isGoodCleaTpcPid : %s \n", ( goodClean ) ? "true" : "false" );
  }
  
  return goodClean;
}

//_________________
bool StHbtBasicTrackCut::isTpcCleanElectron(const StHbtTrack *t, TLorentzVector vec) {

  bool goodTpcClean = false;
  if ( mVerbose ) {
    std::cout << "isTpcCleanElectron: \n"
	      << Form("nSigma(electron)   : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mNSigmaElectron[0], t->nSigmaElectron(), mNSigmaElectron[1],
		      ( mNSigmaElectron[0]<=t->nSigmaElectron() &&
			t->nSigmaElectron()<=mNSigmaElectron[1]  ) ? "true" : "false")
	      << Form("p                  : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTpcMom[0], vec.P(), mTpcMom[1],
		      ( mTpcMom[0]<=vec.P() && vec.P()<=mTpcMom[1] ) ? "true" : "false")
	      << Form("nSigmaOther(pion)  : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaPion(), mNSigmaOther[0] , t->nSigmaPion(), mNSigmaOther[0],
		      ( ( t->nSigmaPion()<=mNSigmaOther[0] ) ||
			( t->nSigmaPion()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(kaon)  : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaKaon(), mNSigmaOther[0] , t->nSigmaKaon(), mNSigmaOther[0],
		      ( ( t->nSigmaKaon()<=mNSigmaOther[0] ) ||
			( t->nSigmaKaon()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(proton): %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaProton(), mNSigmaOther[0] , t->nSigmaProton(), mNSigmaOther[0],
		      ( ( t->nSigmaProton()<=mNSigmaOther[0] ) ||
			( t->nSigmaProton()>=mNSigmaOther[1] )  ) ? "true" : "false");      
  } // if ( mVerbose )
  
  goodTpcClean = ( mNSigmaElectron[0] <= t->nSigmaElectron() &&
		   t->nSigmaElectron() <= mNSigmaElectron[1] &&
		   ( mTpcMom[0] <= vec.P() ) && ( vec.P() <= mTpcMom[1] ) &&
		   ( ( t->nSigmaPion() <= mNSigmaOther[0] ) || ( t->nSigmaPion() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaKaon() <= mNSigmaOther[0] ) || ( t->nSigmaKaon() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaProton() <= mNSigmaOther[0] ) || ( t->nSigmaProton() >= mNSigmaOther[1] ) ) );

  if ( mVerbose ) {
    std::cout << Form("isTpcCleanElectron: %s \n", ( goodTpcClean ) ? "true" : "false" );
  }

  return goodTpcClean;
} 

//_________________
bool StHbtBasicTrackCut::isTpcCleanPion(const StHbtTrack *t, TLorentzVector vec) {

  bool goodTpcClean = false;
  if ( mVerbose ) {
    std::cout << "isTpcCleanPion: \n"
	      << Form("nSigma(pion)       : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mNSigmaPion[0], t->nSigmaPion(), mNSigmaPion[1],
		      ( mNSigmaPion[0]<=t->nSigmaPion() &&
			t->nSigmaPion()<=mNSigmaPion[1]  ) ? "true" : "false")
	      << Form("p                  : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTpcMom[0], vec.P(), mTpcMom[1],
		      ( mTpcMom[0]<=vec.P() && vec.P()<=mTpcMom[1] ) ? "true" : "false")
	      << Form("nSigmaOther(electron)  : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaElectron(), mNSigmaOther[0] , t->nSigmaElectron(), mNSigmaOther[0],
		      ( ( t->nSigmaElectron()<=mNSigmaOther[0] ) ||
			( t->nSigmaElectron()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(kaon)  : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaKaon(), mNSigmaOther[0] , t->nSigmaKaon(), mNSigmaOther[0],
		      ( ( t->nSigmaKaon()<=mNSigmaOther[0] ) ||
			( t->nSigmaKaon()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(proton): %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaProton(), mNSigmaOther[0] , t->nSigmaProton(), mNSigmaOther[0],
		      ( ( t->nSigmaProton()<=mNSigmaOther[0] ) ||
			( t->nSigmaProton()>=mNSigmaOther[1] )  ) ? "true" : "false");      
  } // if ( mVerbose )
    
  goodTpcClean = ( mNSigmaPion[0] <= t->nSigmaPion() &&
		   t->nSigmaPion() <= mNSigmaPion[1] &&
		   ( mTpcMom[0] <= vec.P() ) && ( vec.P() <= mTpcMom[1] ) &&
		   ( ( t->nSigmaElectron() <= mNSigmaOther[0] ) || ( t->nSigmaElectron() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaKaon() <= mNSigmaOther[0] ) || ( t->nSigmaKaon() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaProton() <= mNSigmaOther[0] ) || ( t->nSigmaProton() >= mNSigmaOther[1] ) ) );

  if ( mVerbose ) {
    std::cout << Form("isTpcCleanPion      : %s \n", ( goodTpcClean ) ? "true" : "false" );
  }

  return goodTpcClean;
}

//_________________
bool StHbtBasicTrackCut::isTpcCleanKaon(const StHbtTrack *t, TLorentzVector vec) {

  bool goodTpcClean = false;
  if ( mVerbose ) {
    std::cout << "isTpcCleanKaon: \n"
	      << Form("nSigma(kaon)         : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mNSigmaKaon[0], t->nSigmaKaon(), mNSigmaKaon[1],
		      ( mNSigmaKaon[0]<=t->nSigmaKaon() &&
			t->nSigmaKaon()<=mNSigmaKaon[1]  ) ? "true" : "false")
	      << Form("p                    : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTpcMom[0], vec.P(), mTpcMom[1],
		      ( mTpcMom[0]<=vec.P() && vec.P()<=mTpcMom[1] ) ? "true" : "false")
	      << Form("nSigmaOther(electron): %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaElectron(), mNSigmaOther[0] , t->nSigmaElectron(), mNSigmaOther[0],
		      ( ( t->nSigmaElectron()<=mNSigmaOther[0] ) ||
			( t->nSigmaElectron()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(pion)    : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaPion(), mNSigmaOther[0] , t->nSigmaPion(), mNSigmaOther[0],
		      ( ( t->nSigmaPion()<=mNSigmaOther[0] ) ||
			( t->nSigmaPion()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(proton)  : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaProton(), mNSigmaOther[0] , t->nSigmaProton(), mNSigmaOther[0],
		      ( ( t->nSigmaProton()<=mNSigmaOther[0] ) ||
			( t->nSigmaProton()>=mNSigmaOther[1] )  ) ? "true" : "false");      
  } // if ( mVerbose )
    
  goodTpcClean = ( mNSigmaKaon[0] <= t->nSigmaKaon() &&
		   t->nSigmaKaon() <= mNSigmaKaon[1] &&
		   ( mTpcMom[0] <= vec.P() ) && ( vec.P() <= mTpcMom[1] ) &&
		   ( ( t->nSigmaElectron() <= mNSigmaOther[0] ) || ( t->nSigmaElectron() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaPion() <= mNSigmaOther[0] ) || ( t->nSigmaPion() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaProton() <= mNSigmaOther[0] ) || ( t->nSigmaProton() >= mNSigmaOther[1] ) ) );
  
  if ( mVerbose ) {
    std::cout << Form("isTpcCleanKaon      : %s \n", ( goodTpcClean ) ? "true" : "false" );
  }

  return goodTpcClean;
}

//_________________
bool StHbtBasicTrackCut::isTpcCleanProton(const StHbtTrack *t, TLorentzVector vec) {

  bool goodTpcClean = false;
  if ( mVerbose ) {
    std::cout << "isTpcCleanProton: \n"
	      << Form("nSigma(proton)        : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mNSigmaProton[0], t->nSigmaProton(), mNSigmaProton[1],
		      ( mNSigmaProton[0]<=t->nSigmaProton() &&
			t->nSigmaProton()<=mNSigmaProton[1]  ) ? "true" : "false")
	      << Form("p                     : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTpcMom[0], vec.P(), mTpcMom[1],
		      ( mTpcMom[0]<=vec.P() && vec.P()<=mTpcMom[1] ) ? "true" : "false")
	      << Form("nSigmaOther(electron) : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaElectron(), mNSigmaOther[0] , t->nSigmaElectron(), mNSigmaOther[0],
		      ( ( t->nSigmaElectron()<=mNSigmaOther[0] ) ||
			( t->nSigmaElectron()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(pion)     : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaPion(), mNSigmaOther[0] , t->nSigmaPion(), mNSigmaOther[0],
		      ( ( t->nSigmaPion()<=mNSigmaOther[0] ) ||
			( t->nSigmaPion()>=mNSigmaOther[1] )  ) ? "true" : "false")
      	      << Form("nSigmaOther(kaon)     : %3.2f <= %3.2f || %3.2f >= %3.2f \t %s \n",
		      t->nSigmaKaon(), mNSigmaOther[0] , t->nSigmaKaon(), mNSigmaOther[0],
		      ( ( t->nSigmaKaon()<=mNSigmaOther[0] ) ||
			( t->nSigmaKaon()>=mNSigmaOther[1] )  ) ? "true" : "false");      
  } // if ( mVerbose )
    
  goodTpcClean = ( mNSigmaProton[0] <= t->nSigmaProton() &&
		   t->nSigmaProton() <= mNSigmaProton[1] &&
		   ( mTpcMom[0] <= vec.P() ) && ( vec.P() <= mTpcMom[1] ) &&
		   ( ( t->nSigmaElectron() <= mNSigmaOther[0] ) || ( t->nSigmaElectron() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaPion() <= mNSigmaOther[0] ) || ( t->nSigmaPion() >= mNSigmaOther[1] ) ) &&
		   ( ( t->nSigmaKaon() <= mNSigmaOther[0] ) || ( t->nSigmaKaon() >= mNSigmaOther[1] ) ) );

  if ( mVerbose ) {
    std::cout << Form("isTpcCleanProton     : %s \n", ( goodTpcClean ) ? "true" : "false" );
  }

  return goodTpcClean;
}

//_________________
bool StHbtBasicTrackCut::isGoodTofPid(const StHbtTrack *t) {

  // Check if track passes TOF selection criteria.
  // TOF usage assumes that track is primary and momentum of the primary
  // track is used for mass^2 and 1/beta-1/beta_expected calculations
  bool goodTOF = false;

  if ( mVerbose ) {
    std::cout << Form("isGoodTofPid: \n");
  } // if ( mVerbose )
  
  if ( t->isPrimary() && t->isTofTrack() ) {
    float invBetaDiff = -999.;
    if ( mPidSelection == HbtPID::Electron ) {
      invBetaDiff = t->invBetaDiffElectron();
    }
    else if ( mPidSelection == HbtPID::Pion ) {
      invBetaDiff = t->invBetaDiffPion();
    }
    else if ( mPidSelection == HbtPID::Kaon ) {
      invBetaDiff = t->invBetaDiffKaon();
    }
    else if ( mPidSelection == HbtPID::Proton ) {
      invBetaDiff = t->invBetaDiffProton();
    }
    else {
      std::cout << "[WARNING] StHbtBasicTrackCut::isGoodTofPid -- Wrong PID type selection: "
		<< mPidSelection << std::endl;
    }

    goodTOF = ( ( mTofMassSqr[0] <= t->massSqr() ) && ( t->massSqr() <= mTofMassSqr[1] ) &&
		( mInvBetaDiff[0] <= invBetaDiff ) && ( invBetaDiff <= mInvBetaDiff[1] ) &&
		( mTofMom[0] <= t->pMom().Mag() ) && ( t->pMom().Mag() <= mTofMom[1] ) );


    if ( mVerbose ) {
      std::cout << Form("Mass^2                 : %3.2f <= %3.2f <= %3.2f \t %s \n",
			mTofMassSqr[0], t->massSqr(),  mTofMassSqr[1],
			( mTofMassSqr[0]<=t->massSqr() && t->massSqr()<=mTofMassSqr[1] ) ? "true" : "false")
		<< Form("1/beta-1/beta_expected : %4.3f <= %4.3f <= %4.3f \t %s \n",
			mInvBetaDiff[0], invBetaDiff, mInvBetaDiff[0],
			( mInvBetaDiff[0]<=invBetaDiff && invBetaDiff<=mInvBetaDiff[1] ) ? "true" : "false")
		<< Form("p                      : %3.2f <= %3.2f <= %3.2f \t %s \n",
			mTofMom[0], t->pMom().Mag(), mTofMom[0],
			( mTofMom[0]<=t->pMom().Mag() && t->pMom().Mag()<=mTofMom[1] ) ? "true" : "false");
    } // if ( mVerbose )
    
  } // if ( t->isPrimary() && t->isTofTrack() )

  if ( mVerbose ) {
    std::cout << Form("isGoodTofPid    : %s \n", ( goodTOF ) ? "true" : "false");
  }
  
  return goodTOF;
}

//_________________
bool StHbtBasicTrackCut::isTpcElectron(const StHbtTrack *t) {
  if ( mVerbose ) {
    std::cout << "isTpcElectron: \n"
	      << Form("nSigma(electron) : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTnTNSigmaElectron[0],  t->nSigmaElectron(),  mTnTNSigmaElectron[1],
		      ( mTnTNSigmaElectron[0]<=t->nSigmaElectron() &&
			t->nSigmaElectron()<=mTnTNSigmaElectron[1] ) ? "true" : "false" );
  } // if ( mVerbose )
  
  return ( (mTnTNSigmaElectron[0] <= t->nSigmaElectron() ) &&
	   ( t->nSigmaElectron() <= mTnTNSigmaElectron[1] ) );
}

//_________________
bool StHbtBasicTrackCut::isTpcPion(const StHbtTrack *t) {
  if ( mVerbose ) {
    std::cout << "isTpcPion: \n"
	      << Form("nSigma(pion) : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTnTNSigmaPion[0],  t->nSigmaPion(),  mTnTNSigmaPion[1],
		      ( mTnTNSigmaPion[0]<=t->nSigmaPion() &&
			t->nSigmaPion()<=mTnTNSigmaPion[1] ) ? "true" : "false" );
  } // if ( mVerbose )
    
  return ( (mTnTNSigmaPion[0] <= t->nSigmaPion() ) &&
	   ( t->nSigmaPion() <= mTnTNSigmaPion[1] ) );
}

//_________________
bool StHbtBasicTrackCut::isTpcKaon(const StHbtTrack *t) {
  if ( mVerbose ) {
    std::cout << "isTpcKaon: \n"
	      << Form("nSigma(kaon) : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTnTNSigmaKaon[0],  t->nSigmaKaon(),  mTnTNSigmaKaon[1],
		      ( mTnTNSigmaKaon[0]<=t->nSigmaKaon() &&
			t->nSigmaKaon()<=mTnTNSigmaKaon[1] ) ? "true" : "false" );
  } // if ( mVerbose )
    
  return ( (mTnTNSigmaKaon[0] <= t->nSigmaKaon() ) &&
	   ( t->nSigmaKaon() <= mTnTNSigmaKaon[1] ) );
}

//_________________
bool StHbtBasicTrackCut::isTpcProton(const StHbtTrack *t) {
  if ( mVerbose ) {
    std::cout << "isTpcProton: \n"
	      << Form("nSigma(proton) : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mTnTNSigmaProton[0],  t->nSigmaProton(),  mTnTNSigmaProton[1],
		      ( mTnTNSigmaProton[0]<=t->nSigmaProton() &&
			t->nSigmaProton()<=mTnTNSigmaProton[1] ) ? "true" : "false" );
  } // if ( mVerbose )
    
  return ( (mTnTNSigmaProton[0] <= t->nSigmaProton() ) &&
	   ( t->nSigmaProton() <= mTnTNSigmaProton[1] ) );
}

//_________________
bool StHbtBasicTrackCut::isGoodTnT(const StHbtTrack *t) {
  // Check good TPC and TOF identification
  bool goodTnT = false;
  
  if ( t->isPrimary() && t->isTofTrack() ) {

    if( mPidSelection == HbtPID::Electron ) {        // Electron
      goodTnT = isGoodTofPid( t ) && isTpcElectron( t );
    }
    else if ( mPidSelection == HbtPID::Pion ) {      // Pion
      goodTnT = isGoodTofPid( t ) && isTpcPion( t );
    }
    else if ( mPidSelection == HbtPID::Kaon ) {      // Kaon
      goodTnT = isGoodTofPid( t ) && isTpcKaon( t );
    }
    else if ( mPidSelection == HbtPID::Proton ) {    // Proton
      goodTnT = isGoodTofPid( t ) && isTpcProton( t );
    }
    else {
      std::cout << "[ERROR] StHbtBasicTrackCut::isGoodTnT --  Wrong HbtPID " << mPidSelection << std::endl;
    }
  } // if ( t->isPrimary() && t->isTofTrack() )

  if ( mVerbose ) {
    std::cout << Form("isGoodTnT      : %s \n", ( goodTnT ) ? "true" : "false" );
  }

  return goodTnT;
}

//_________________
bool StHbtBasicTrackCut::isGoodToT(const StHbtTrack *t, TLorentzVector vec) {
  
  bool goodToT = false;
  // If there is a TOF hit, then use TPC+TOF identification
  if( t->isPrimary() && t->isTofTrack() ) {
    goodToT = isGoodTnT( t );
  }
  else {  // When no TOF hit is available check TPC only
    goodToT = isGoodCleanTpcPid( t, vec );
  }

  if ( mVerbose ) {
    std::cout << Form("isGoodToT      : %s \n", ( goodToT ) ? "true" : "false" );
  }
    
  return goodToT;
}

//_________________
bool StHbtBasicTrackCut::isGoodToTThresh(const StHbtTrack *t, TLorentzVector vec) {
  bool goodToTThresh = false;
  if ( t->pMom().Mag() >= mPthresh ) {
    goodToTThresh = isGoodTnT( t );
  }
  else {
    goodToTThresh = isGoodCleanTpcPid( t, vec );
  }
  
  if ( mVerbose ) {
    std::cout << Form("isGoodToTThresh : %s \n", ( goodToTThresh ) ? "true" : "false" );
  }

  return goodToTThresh;
}

//_________________
bool StHbtBasicTrackCut::isGoodKine(const StHbtTrack *t, TLorentzVector vec) {

  if ( mVerbose ) {
    std::cout << Form("nHits           : %d <= %d <= %d \t %s \n",
		      mNHits[0], t->nHits(),  mNHits[1],
		      ( mNHits[0]<=t->nHits() && t->nHits()<=mNHits[1] ) ? "true" : "false")
	      << Form("nHits/nHitsPoss : %3.2f <= %3.2f \t %s \n",
		      mNHitsRat, t->nHitsFit2PossRatio(),
		      ( t->nHitsFit2PossRatio()>=mNHitsRat ) ? "true" : "false")
	      << Form("pT              : %4.2f <= %4.2f <= %4.2f \t %s \n",
		      mPt[0], vec.Pt(), mPt[1],
		      ( mPt[0]<=vec.Pt() && vec.Pt()<=mPt[1] ) ? "true" : "false" )
	      << Form("p               : %4.2f <= %4.2f <= %4.2f \t %s \n",
		      mP[0], vec.P(), mP[1],
		      ( mP[0]<=vec.P() && vec.P()<=mP[1] ) ? "true" : "false" )
	      << Form("y               : %4.2f <= %4.2f <= %4.2f \t %s \n",
		      mRapidity[0], vec.Rapidity(), mRapidity[1],
		      ( mRapidity[0]<=vec.Rapidity() && vec.Rapidity()<=mRapidity[1] ) ? "true" : "false" )
	      << Form("eta             : %4.2f <= %4.2f <= %4.2f \t %s \n",
		      mEta[0], vec.Eta(), mEta[1],
		      ( mEta[0]<=vec.Eta() && vec.Eta()<=mEta[1] ) ? "true" : "false" )
	      << Form("DCA             : %4.2f <= %4.2f <= %4.2f \t %s \n",
		      mDCA[0], t->gDCA().Mag(), mDCA[1],
		      ( mDCA[0]<=t->gDCA().Mag() && t->gDCA().Mag()<=mDCA[1] ) ? "true" : "false" );
  }
  
  return  ( ( mNHits[0] <= t->nHits() ) && ( t->nHits() <= mNHits[1] ) &&
	    ( t->nHitsFit2PossRatio() >= mNHitsRat ) &&
	    ( mPt[0] <= vec.Pt() ) && ( vec.Pt() <= mPt[1] ) &&
	    ( mP[0] <= vec.P() ) && ( vec.P() <= mP[1] ) &&
	    ( mRapidity[0] <= vec.Rapidity() ) && ( vec.Rapidity() <= mRapidity[1] ) &&
	    ( mEta[0] <= vec.Eta() ) && ( vec.Eta() <= mEta[1] ) &&
	    ( mDCA[0] <= t->gDCA().Mag() ) && ( t->gDCA().Mag() <= mDCA[1] ) );
}
