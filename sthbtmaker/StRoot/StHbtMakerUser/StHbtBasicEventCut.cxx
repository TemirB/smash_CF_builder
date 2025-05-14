//
// The basic cut for events
//

// C++ headers
#include <limits>
#include <iostream>

// StHbtMakerUser headers
#include "StHbtBasicEventCut.h"

// ROOT headers
#include "TObjString.h"
#include "TMath.h"
#include "TString.h"

#ifdef __ROOT__
ClassImp(StHbtBasicEventCut);
#endif

//_________________
StHbtBasicEventCut::StHbtBasicEventCut():
  StHbtBaseEventCut(),
  mCheckBadRun(true),
  mRefMult(),
  mVertZPos(),
  mVpdVzDiff(),
  mVertXShift(0),
  mVertYShift(0),
  mVertRPos(),
  mSphericity(),
  mBTofTrayMult(),
  mBTofMatch(),
  mCent9(),
  mPsiEP(),
  mNEventsPassed(0),
  mNEventsFailed(0),
  mVerbose(false) {

  // Default constructor
  mRefMult[0] = -2000;
  mRefMult[1] = 30000;
  mVertZPos[0] = -20000.;
  mVertZPos[1] = 20000.;
  mVpdVzDiff[0] = -20000.;
  mVpdVzDiff[1] = 20000.;
  mVertRPos[0] = -1000.;
  mVertRPos[1] = 20000.;
  mSphericity[0] = -1000.;
  mSphericity[1] = 1000.;
  mBTofTrayMult[0] = -30000;
  mBTofTrayMult[1] = 30000;
  mBTofMatch[0] = -30000;
  mBTofMatch[1] = 30000;
  mCent9[0] = -2000;
  mCent9[1] = 2000;
  mPsiEP[0] = -300000.;
  mPsiEP[1] = 300000.;
  mImpactPar[0] = -0.1;
  mImpactPar[1] = 30.;
  if( !mTriggersToSelect.empty() ) {
    mTriggersToSelect.clear();
  }
}

//_________________
StHbtBasicEventCut::StHbtBasicEventCut(const StHbtBasicEventCut& c):
  StHbtBaseEventCut(c),
  mNEventsPassed(0),
  mNEventsFailed(0) {
  // Copy constructor
  mCheckBadRun = c.mCheckBadRun;
  mRefMult[0] = c.mRefMult[0];
  mRefMult[1] = c.mRefMult[1];
  mVertZPos[0] = c.mVertZPos[0];
  mVertZPos[1] = c.mVertZPos[1];
  mVpdVzDiff[0] = c.mVpdVzDiff[0];
  mVpdVzDiff[1] = c.mVpdVzDiff[1];
  mVertXShift = c.mVertXShift;
  mVertYShift = c.mVertYShift;
  mVertRPos[0] = c.mVertRPos[0];
  mVertRPos[1] = c.mVertRPos[1];
  mSphericity[0] = c.mSphericity[0];
  mSphericity[1] = c.mSphericity[1];
  mBTofTrayMult[0] = c.mBTofTrayMult[0];
  mBTofTrayMult[1] = c.mBTofTrayMult[1];
  mBTofMatch[0] = c.mBTofMatch[0];
  mBTofMatch[1] = c.mBTofMatch[1];
  mCent9[0] = c.mCent9[0];
  mCent9[1] = c.mCent9[1];
  mPsiEP[0] = c.mPsiEP[0];
  mPsiEP[1] = c.mPsiEP[1];
  mImpactPar[0] = c.mImpactPar[0];
  mImpactPar[1] = c.mImpactPar[1];
  mVerbose = c.mVerbose;
  if( mTriggersToSelect.empty() ) {
    for( unsigned int iIter=0; iIter<c.mTriggersToSelect.size(); iIter++ ) {
      mTriggersToSelect.push_back( c.mTriggersToSelect.at( iIter ) );
    }
  } // if( mTriggersToSelect.empty() )
  else {
    bool notInList = false;
    for( unsigned int iIter1=0; iIter1<c.mTriggersToSelect.size(); iIter1++) {
      for( unsigned int iIter2=0; iIter2<mTriggersToSelect.size(); iIter2++ ) {
	if( mTriggersToSelect.at( iIter2 ) == c.mTriggersToSelect.at( iIter1 ) ) {
	  continue;
	}
	else {
	  notInList = true;
	  break;
	}
      } // for( unsigned int iIter2=0; iIter2<mTriggersToSelect.size(); iIter2+ )

      /// Add trigger that is not in the list
      if( notInList ) {
	       mTriggersToSelect.push_back( c.mTriggersToSelect.at( iIter1 ) );
      }
    } // for( unsigned int iIter1=0; iIter1<c.mTriggersToSelect.size(); iIter1++)
  } // else
}

//_________________
StHbtBasicEventCut& StHbtBasicEventCut::operator=(const StHbtBasicEventCut& c) {
  // Assignment operator
  if ( this != &c ) {
    StHbtBaseEventCut::operator=(c);
    mCheckBadRun = c.mCheckBadRun;
    mRefMult[0] = c.mRefMult[0];
    mRefMult[1] = c.mRefMult[1];
    mVertZPos[0] = c.mVertZPos[0];
    mVertZPos[1] = c.mVertZPos[1];
    mVpdVzDiff[0] = c.mVpdVzDiff[0];
    mVpdVzDiff[1] = c.mVpdVzDiff[1];
    mVertXShift = c.mVertXShift;
    mVertYShift = c.mVertYShift;
    mVertRPos[0] = c.mVertRPos[0];
    mVertRPos[1] = c.mVertRPos[1];
    mSphericity[0] = c.mSphericity[0];
    mSphericity[1] = c.mSphericity[1];
    mBTofTrayMult[0] = c.mBTofTrayMult[0];
    mBTofTrayMult[1] = c.mBTofTrayMult[1];
    mBTofMatch[0] = c.mBTofMatch[0];
    mBTofMatch[1] = c.mBTofMatch[1];
    mCent9[0] = c.mCent9[0];
    mCent9[1] = c.mCent9[1];
    mPsiEP[0] = c.mPsiEP[0];
    mPsiEP[1] = c.mPsiEP[1];
    mImpactPar[0] = c.mImpactPar[0];
    mImpactPar[1] = c.mImpactPar[1];
    mVerbose = c.mVerbose;
    if( mTriggersToSelect.empty() ) {
      for( unsigned int iIter=0; iIter<c.mTriggersToSelect.size(); iIter++ ) {
	      mTriggersToSelect.push_back( c.mTriggersToSelect.at( iIter ) );
      }
    } // if( mTriggersToSelect.empty() )
    else {
      bool notInList = false;
      for( unsigned int iIter1=0; iIter1<c.mTriggersToSelect.size(); iIter1++ ) {
	for( unsigned int iIter2=0; iIter2<mTriggersToSelect.size(); iIter2++ ) {
	  if( mTriggersToSelect.at( iIter2 ) == c.mTriggersToSelect.at( iIter1 ) ) {
	    continue;
	  }
	  else {
	    notInList = true;
	    break;
	  }
	} // for( unsigned int iIter2=0; iIter2<mTriggersToSelect.size(); iIter2+ )

	/// Add trigger that is not in the list
	if( notInList ) {
	  mTriggersToSelect.push_back( c.mTriggersToSelect.at( iIter1 ) );
	}
      } // for( unsigned int iIter1=0; iIter1<c.mTriggersToSelect.size(); iIter1++)
    } // else
  } // if ( this != &c )

  return *this;
}

//_________________
StHbtBasicEventCut::~StHbtBasicEventCut() {
  // Default destructor
}

//_________________
bool StHbtBasicEventCut::pass(const StHbtEvent* ev) {
  // Pass events if they fall within the various multiplicities and z-vertex
  // position range. Fail otherwise

  if ( mVerbose ) {
    std::cout << "\n--StHbtBasicEventCut-- \n";
  }

  // Reestimate radial vertex position shifting the center
  float vtxR = TMath::Sqrt( (ev->primaryVertex().X() - mVertXShift) *
                            (ev->primaryVertex().X() - mVertXShift) +
			    (ev->primaryVertex().Y() - mVertYShift) *
                            (ev->primaryVertex().Y() - mVertYShift) );

  const bool passes_refMult = ( ( ev->refMult() >= mRefMult[0] ) &&
                                ( ev->refMult() < mRefMult[1] ) );

  if ( mVerbose ) {
    std::cout << Form("RefMult        : %d <= %d < %d \t %s \n",
		      mRefMult[0], ev->refMult(), mRefMult[1],
		      ( ev->refMult()>=mRefMult[0] &&
			ev->refMult()<mRefMult[1] ) ? "true" : "false" );
  }

  const bool passes_impact = ( (ev->impactParameter() >= mImpactPar[0] ) &&
			       (ev->impactParameter() <= mImpactPar[1] ) );
  if ( mVerbose ) {
    std::cout << Form("Impact parameter: %4.2f <= %4.2f <= %4.2f %s\n",
		      mImpactPar[0], ev->impactParameter(), mImpactPar[1],
		      ( ev->impactParameter() >= mImpactPar[0] &&
			ev->impactParameter() <= mImpactPar[1] ) ? "true" : "false" );
  }

  const bool passes_z = ( ( ev->primaryVertex().Z() >= mVertZPos[0] ) &&
			  ( ev->primaryVertex().Z() < mVertZPos[1] ) );

  if ( mVerbose ) {
    std::cout << Form("Vert Z         : %5.2f <= %5.2f < %5.2f \t %s \n",
		      mVertZPos[0], ev->primaryVertex().Z(), mVertZPos[1],
		      ( ev->primaryVertex().Z()>=mVertZPos[0] &&
			ev->primaryVertex().Z()<mVertZPos[1] ) ? "true" : "false" );
  }

  const bool passes_vpd = ( ( ev->vpdVzDiff() >= mVpdVzDiff[0] ) &&
			    ( ev->vpdVzDiff() <= mVpdVzDiff[1] ) );

  if ( mVerbose ) {
    std::cout << Form("VPD Vert Z diff: %5.2f <= %5.2f <= %5.2f \t %s \n",
		      mVpdVzDiff[0], ev->vpdVzDiff(), mVpdVzDiff[1],
		      ( ev->vpdVzDiff()>=mVpdVzDiff[0] &&
			ev->vpdVzDiff()<=mVpdVzDiff[1] ) ? "true" : "false" );
  }

  const bool passes_r = ( ( vtxR >= mVertRPos[0] ) &&
                          ( vtxR <= mVertRPos[1] ) );

  if ( mVerbose ) {
    std::cout << Form("Vert R         : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mVertRPos[0], vtxR, mVertRPos[1],
		      ( vtxR>=mVertRPos[0] && vtxR<=mVertRPos[1] ) ? "true" : "false" );
  } 

  const bool passes_sph = ( ( ev->sphericity() >= mSphericity[0] ) &&
                            ( ev->sphericity() <= mSphericity[1] ) );

  if ( mVerbose ) {
    std::cout << Form("Sphericity     : %3.2f <= %3.2f <= %3.2f \t %s \n",
		      mSphericity[0], ev->sphericity(), mSphericity[1],
		      ( ev->sphericity()>=mSphericity[0] &&
			ev->sphericity()<=mSphericity[1] ) ? "true" : "false" );
  }

  const bool passes_btofmult = ( ( ev->btofTrayMultiplicity() >= mBTofTrayMult[0] ) &&
				 ( ev->btofTrayMultiplicity() <= mBTofTrayMult[1] ) );

  if ( mVerbose ) {
    std::cout << Form("bTofMult       : %d <= %d <= %d \t %s \n",
		      mBTofTrayMult[0], ev->btofTrayMultiplicity(), mBTofTrayMult[1],
		      ( ev->btofTrayMultiplicity()>=mBTofTrayMult[0] &&
			ev->btofTrayMultiplicity()<=mBTofTrayMult[1] ) ? "true" : "false" );
  }

  const bool passes_btofmatch = ( ( ev->numberOfBTofMatched() >= mBTofMatch[0] ) &&
				  ( ev->numberOfBTofMatched() <= mBTofMatch[1] ) );

  if ( mVerbose ) {
    std::cout << Form("bTofMatched    : %d <= %d <= %d \t %s \n",
		      mBTofMatch[0], ev->numberOfBTofMatched(), mBTofMatch[1],
		      ( ev->numberOfBTofMatched()>=mBTofMatch[0] &&
			ev->numberOfBTofMatched()<=mBTofMatch[1] ) ? "true" : "false" );
  }

  const bool passes_cent = ( ( ev->cent9() >= mCent9[0] ) &&
                             ( ev->cent9() <= mCent9[1] ) );

  if ( mVerbose ) {
    std::cout << Form("cent9          : %d <= %d <= %d \t %s \n",
		      mCent9[0], ev->cent9(), mCent9[1],
		      ( ev->cent9()>=mCent9[0] && ev->cent9()<=mCent9[1] ) ? "true" : "false" );
  }

  const bool passes_ep = ( ( ev->eventPlaneAngle() >= mPsiEP[0] ) &&
			   ( ev->eventPlaneAngle() <= mPsiEP[1] ) ) ;
  
  if ( mVerbose ) {
    std::cout << Form("psi            : %6.3f <= %6.3f <= %6.3f \t %s \n",
		      mPsiEP[0], ev->eventPlaneAngle(),  mPsiEP[1],
		      ( ev->eventPlaneAngle()>=mPsiEP[0] &&
			ev->eventPlaneAngle()<=mPsiEP[1] ) ? "true" : "false" );
  }

  const bool passes_run = !mCheckBadRun ? true : !( isInBadRunList( ev->runNumber() ) );

  if ( mVerbose ) {
    std::cout << Form("isGoodRun       : %s \n", ( passes_run ) ? "true" : "false" );
  }

  bool passes_trigger = false;											
  if ( mTriggersToSelect.empty() ) {
    passes_trigger = true;
  } // if ( mTriggersToSelect.empty() )
  else {
    for ( unsigned int iIter=0; iIter<mTriggersToSelect.size(); iIter++ ) {
      if( ev->isTrigger( mTriggersToSelect.at( iIter ) ) ) {
	passes_trigger = true;
	break;
      } // if( ev->isTrigger( mTriggersToSelect.at( iIter ) ) )
    } // for ( unsigned int iIter=0; iIter<mTriggersToSelect.size(); iIter++ )	
  } // else

  if ( mVerbose ) {
    std::cout << Form("isGoodTrigger   : %s \n", ( passes_trigger ) ? "true" : "false" );
  }

  const bool goodEvent =  ( passes_refMult &&
			    passes_impact &&
			    passes_z &&
			    passes_vpd &&
			    passes_r &&
			    passes_sph &&
			    passes_btofmult &&
			    passes_btofmatch &&
			    passes_cent &&
			    passes_ep &&
			    passes_run &&
			    passes_trigger );

  if ( mVerbose ) {
    std::cout << Form("isGoodEvent      : %s \n", ( goodEvent ) ? "true" : "false" );
  }

  goodEvent ? mNEventsPassed++ : mNEventsFailed++ ;

  return goodEvent;
}

//_________________
TList* StHbtBasicEventCut::appendSettings(TList *settings, const TString &prefix) const {

  settings->AddVector(
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.refMult.min=%d", mRefMult[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.refMult.max=%d", mRefMult[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.impactPar.min=%4.2f", mImpactPar[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.impactPar.max=%4.2f", mImpactPar[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.vtxZ.min=%f", mVertZPos[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.vtxZ.max=%f", mVertZPos[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.vpdVzDiff.min=%f", mVpdVzDiff[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.vpdVzDiff.max=%f", mVpdVzDiff[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.vtxR.min=%f", mVertRPos[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.vtxR.max=%f", mVertRPos[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.spher.min=%f", mSphericity[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.spher.max=%f", mSphericity[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.btofTrayMult.min=%d", mBTofTrayMult[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.btofTrayMult.max=%d", mBTofTrayMult[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.btofMatch.min=%d", mBTofMatch[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.btofMatch.max=%d", mBTofMatch[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.cent9.min=%d", mCent9[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.cent9.max=%d", mCent9[1]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.psiep.min=%f", mPsiEP[0]) ),
    new TObjString( prefix + TString::Format("StHbtBasicEventCut.psiep.max=%f", mPsiEP[1]) ),
    NULL);

  return settings;
}

//_________________
StHbtString StHbtBasicEventCut::report() {
  // Prepare report
  TString report = TString::Format( "refMult              :\t %d - %d\n", mRefMult[0], mRefMult[1] );
  report += TString::Format( "Impact parameter     :\t %f - %f\n", mImpactPar[0], mImpactPar[1] );
  report += TString::Format( "Vertex Z-position    :\t %f - %f\n", mVertZPos[0], mVertZPos[1] );
  report += TString::Format( "VpdVz - Vz           :\t %f - %f\n", mVpdVzDiff[0], mVpdVzDiff[1] );
  report += TString::Format( "Vertex X and Y shifts:\t %f,  %f\n", mVertXShift, mVertYShift );
  report += TString::Format( "Vertex R             :\t %f - %f\n", mVertRPos[0], mVertRPos[1] );
  report += TString::Format( "Sphericity           :\t %f - %f\n", mSphericity[0], mSphericity[1] );
  report += TString::Format( "BTOF tray mult       :\t %d - %d\n", mBTofTrayMult[0], mBTofTrayMult[1] );
  report += TString::Format( "BTOF matrched        :\t %d - %d\n", mBTofMatch[0], mBTofMatch[1] );
  report += TString::Format( "Centrality (9 bins)  :\t %d - %d\n", mCent9[0], mCent9[1] );
  report += TString::Format( "Event plane angle    :\t %f - %f\n", mPsiEP[0], mPsiEP[1] );
  report += TString::Format( "List of triggers:");
  for ( unsigned int iIter=0; iIter<mTriggersToSelect.size(); iIter++ ) {
    report += TString::Format(" %u ", mTriggersToSelect.at( iIter ) );
  }
  report += TString::Format( "\nNumber of events which passed:\t%u  Number which failed:\t%u\n",
			     mNEventsPassed, mNEventsFailed );
  return StHbtString( (const char *)report );
}

//_________________
bool StHbtBasicEventCut::isInBadRunList(int runNumber) {
  // Compare current run number with the bad run list
  bool isIn_7gev =  ( std::find(bad_run_list_7gev.begin(), bad_run_list_7gev.end(), runNumber) != bad_run_list_7gev.end() );								 
  bool isIn_11gev = ( std::find(bad_run_list_11gev.begin(), bad_run_list_11gev.end(), runNumber) != bad_run_list_11gev.end() );								
  bool isIn_14gev = ( std::find(bad_run_list_14gev.begin(), bad_run_list_14gev.end(), runNumber) != bad_run_list_14gev.end() );								
  bool isIn_19gev = ( std::find(bad_run_list_19gev.begin(), bad_run_list_19gev.end(), runNumber) != bad_run_list_19gev.end() );								
  bool isIn_27gev = ( std::find(bad_run_list_27gev.begin(), bad_run_list_27gev.end(), runNumber) != bad_run_list_27gev.end() );								
  bool isIn_39gev = ( std::find(bad_run_list_39gev.begin(), bad_run_list_39gev.end(), runNumber) != bad_run_list_39gev.end() );								 
  bool isIn_62gev = ( std::find(bad_run_list_62gev.begin(), bad_run_list_62gev.end(), runNumber) != bad_run_list_62gev.end() );								
  bool isIn_200gev = ( std::find(bad_run_list_200gev.begin(), bad_run_list_200gev.end(), runNumber) != bad_run_list_200gev.end() );

  bool isIn_dau200_r16 = ( std::find(bad_run_list_dau200_2016.begin(), bad_run_list_dau200_2016.end(), runNumber) != bad_run_list_dau200_2016.end() );

  bool isIn_he3au_r14 = ( std::find(bad_run_list_he3au200_2014.begin(), bad_run_list_he3au200_2014.end(), runNumber) != bad_run_list_he3au200_2014.end() );
  
  return ( isIn_7gev || isIn_11gev || isIn_14gev || isIn_19gev || isIn_27gev ||
           isIn_39gev || isIn_62gev || isIn_200gev || isIn_dau200_r16 || isIn_he3au_r14 );
}

//_________________
void StHbtBasicEventCut::addTriggerId(const unsigned int& id) {
  // If trigger list is not empty then loop over it
  // and check if the new trigger already in.
  if( !mTriggersToSelect.empty() ) {

    // Assume that the new trigger is not in the list
    Bool_t isUsed = false;

    // Loop over the trigger list
    for(UInt_t iIter=0; iIter<mTriggersToSelect.size(); iIter++) {

      // Compare triggers
      if( mTriggersToSelect.at(iIter) == id ) {
	      isUsed = true;
      }
    } //(unsigned int iIter=0; iIter<mTriggerIds.size(); iIter++)

    // If the trigger not in the list then add it
    if( !isUsed ) {
      mTriggersToSelect.push_back(id);
    }
  } //if( !mTriggerIds.empty() )
  else {
    mTriggersToSelect.push_back(id);
  }
}

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_7gev = {
  11114084,11114085,11114086,11114088,11114089,11114094,11114095,11114100,
  11114109,11115005,11115007,11115013,11115019,11115025,11115027,11115028,
  11115030,11115032,11115051,11115062,11115064,11115069,11115072,11115078,
  11115079,11115080,11115086,11115088,11115094,11116001,11116002,11116005,
  11116006,11116010,11116014,11116020,11116023,11116028,11116060,11116061,
  11116062,11116064,11116068,11116070,11116072,11116073,11116075,11117002,
  11117006,11117031,11117033,11117034,11117036,11117039,11117044,11117045,
  11117046,11117052,11117055,11117063,11117064,11117071,11117075,11117085,
  11117088,11117089,11117090,11117093,11117094,11117095,11117098,11117100,
  11117103,11117104,11117107,11118007,11118008,11118016,11118024,11118025,
  11118026,11118039,11118044,11119001,11119003,11119006,11119007,11119009,
  11119012,11119013,11119015,11119016,11119017,11119022,11119024,11119026,
  11119029,11119030,11119056,11119057,11119060,11119062,11119067,11119069,
  11119070,11119071,11119074,11119075,11119077,11119079,11119081,11119090,
  11119091,11119100,11119101,11120003,11120006,11120008,11120011,11120014,
  11120019,11120023,11120030,11120034,11120037,11120039,11120040,11120045,
  11120052,11120057,11120062,11120063,11120069,11120070,11120071,11120074,
  11120077,11120078,11120084,11120092,11121006,11121014,11121015,11121019,
  11121029,11121030,11121034,11121035,11121043,11121044,11121054,11121058,
  11121066,11121067,11121070,11121075,11121082,11122001,11122007,11122008,
  11122010,11122017,11122024,11122037,11122038,11122047,11122048,11122049,
  11122050,11122053,11122058,11122062,11122069,11122073,11122078,11122085,
  11122097,11123003,11123004,11123015,11123026,11123028,11123040,11123044,
  11123055,11123057,11123058,11123059,11123067,11123075,11123076,11123077,
  11123079,11123081,11123084,11123086,11123088,11123089,11123093,11123094,
  11123095,11123100,11123101,11123102,11123104,11124001,11124005,11124007,
  11124008,11124015,11124016,11124018,11124041,11124046,11124050,11124051,
  11124052,11124053,11124058,11124060,11124061,11124062,11124063,11124064,
  11124065,11124066,11124069,11125002,11125003,11125004,11125005,11125006,
  11125008,11125012,11125013,11125014,11125015,11125016,11125017,11125020,
  11125021,11125022,11125023,11125073,11125081,11125089,11125090,11125096,
  11125097,11126005,11126006,11126007,11126016,11126018,11126022,11126023,
  11127001,11127002,11127043,11128005,11128012,11128018,11128050,11128056,
  11128072,11129018,11129022,11129028,11129051,11130027,11130034,11130057,
  11131038,11131062,11132013,11132070,11133006,11133019,11134053,11134060,
  11134067,11134076,11135068,11136003,11136005,11136006,11136007,11136008,
  11136012,11136013,11136014,11136061,11136076,11136101,11136130,11136160,
  11136163,11137019,11138027,11138049,11138086,11138124,11139014,11140076,
  11140086,11141063,11142117,11143026,11143028,11144001,11144009,11144031,
  11144033,11144040,11144043,11144052,11145008,11145028,11145035,11146061,
  11146076,11146079,11147004,11147006,11147014,11147017,11147021,11147023 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_11gev = {
  11148039,11148045,11149001,11149008,11149010,11149011,11149015,11149047,
  11150016,11150025,11150028,11151036,11151040,11151050,11152016,11152036,
  11152078,11153032,11153042,11155001,11155009,11156003,11156009,11157012,
  11158006,11158022,11158024 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_14gev = {
  999 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_19gev = {
  12113091,12114007,12114035,12114078,12114092,12114116,12115009,12115014,
  12115015,12115016,12115018,12115019,12115020,12115022,12115023,12115062,
  12115073,12115093,12115094,12116012,12116054,12117010,12117016,12117020,
  12117065,12119040,12119042,12120017,12120026,12121017,12121022,12121034,
  12121050,12121067,12122019 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_27gev = {
  12172050,12172051,12172055,12173030,12173031,12173032,12173033,12173034,
  12174067,12174085,12175062,12175087,12175113,12175114,12175115,12176001,
  12176044,12176054,12176071,12177015,12177061,12177092,12177099,12177101,
  12177106,12177107,12177108,12178003,12178004,12178005,12178006,12178013,
  12178099,12178120 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_39gev = {
  11199124,11100002,11100045,11101046,11102012,11102051,11102052,11102053,
  11102054,11102055,11102058,11103035,11103056,11103058,11103092,11103093,
  11105052,11105053,11105054,11105055,11107007,11107042,11107057,11107061,
  11107065,11107074,11108101,11109013,11109077,11109088,11109090,11109127,
  11110013,11110034,11110073,11110076,11111084,11111085 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_62gev = {
  11080072,11081023,11081025,11082012,11082013,11082046,11082056,11082057,
  11084009,11084011,11084012,11084013,11084020,11084021,11084035,11084044,
  11084064,11085015,11085025,11085030,11085046,11085055,11085056,11085057,
  11086005,11086007,11087001,11087002,11087003,11087004,11088013,11089026,
  11089028,11089029,11089055,11089068,11089072,11091007,11091015,11091021,
  11091078,11092010,11092011,11092012,11092032,11092033,11092034,11092067,
  11092096,11093001,11094016,11094017,11094018,11094019,11094020,11094021,
  11094022,11094023,11094024,11094027,11094028,11094042,11094044,11094045,
  11094046,11094047,11094048,11094050,11094051,11094052,11094053,11094054,
  11094055,11094074,11094075,11094077,11095001,11095002,11095003,11095004,
  11095005,11095006,11095009,11095010,11095011,11095012,11095013,11095014,
  11095015,11095022,11095040,11095048,11095050,11095051,11095061,11095062,
  11095063,11095064,11095082,11095087,11096024,11096039,11096043,11096044,
  11097093 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_200gev = {
  11002120,11002121,11002126,11002127,11002129,11003010,11003011,11003101,
  11003102,11004007,11004008,11004009,11004010,11004011,11004012,11004013,
  11004014,11004015,11004016,11004018,11004020,11004021,11004023,11004024,
  11004025,11004026,11004028,11004029,11004030,11004032,11004033,11004034,
  11004035,11004037,11004038,11005042,11006004,11006005,11006008,11007015,
  11010031,11011019,11011053,11015069,11015071,11016024,11017006,11018003,
  11018007,11018008,11018036,11019001,11019080,11019081,11021027,11021028,
  11021031,11023048,11025034,11025038,11025054,11025067,11025069,11026005,
  11026008,11026021,11026022,11026023,11026025,11026067,11026068,11028004,
  11028005,11028006,11028007,11028008,11028009,11028010,11028011,11028012,
  11028013,11028018,11028019,11028020,11028021,11028022,11028023,11028024,
  11028025,11028026,11028027,11030041,11030080,11031061,11031064,11035008,
  11035009,11035072,11036026,11037035,11037037,11037060,11037066,11037067,
  11038048,11038049,11038050,11039047,11039067,11040078,11040083,11041022,
  11041023,11041040,11041041,11042001,11042002,11042003,11042004,11042005,
  11042006,11042007,11042008,11042011,11042012,11042018,11042019,11042020,
  11042021,11042022,11042023,11042024,11042025,11042026,11042027,11042042,
  11042043,11042044,11042045,11042046,11042047,11042048,11042049,11044029,
  11047059,11047065,11047066,11047067,11048037,11049001,11049002,11049005,
  11049023,11051038,11051049,11051051,11051055,11051063,11051064,11051068,
  11052011,11053057,11054021,11054022,11054024,11054059,11054062,11054066,
  11057012,11057035,11057036,11058005,11058050,11058083,11059043,11059055,
  11059060,11059075,11059076,11059077,11060008,11060049,11060059,11060069,
  11060076,11061008,11061009,11061021,11061034,11061037,11061038,11061095,
  11063006,11063007,11063008,11063011,11063013,11063014,11063015,11063016,
  11063017,11063036,11063083,11064003,11064023,11065038,11066024,11066045,
  11071056,11072032,11072044,11072045,11073001,11073002,11073003,11073049,
  11075039,11075045,11075048,
  12127007,12127009,12127012,12127014,12127015,12127016,12127024,12127046, //acc. to Kate Kuzina study 
  12128016,12128024,12128028,12128031,12133002,12133003,12133004,12135027, //auau200_2011
  12135052,12136080,12138081,12138082,12138087,12138088,12138089,12138090,
  12138091,12138092,12139002,12139003,12139006,12139007,12139008,12139009,
  12139010,12139015,12139016,12139017,12139018,12139019,12139020,12139021,
  12140026,12141014,12141041,12142013,12142028,12143024,12144004,12144032,
  12144050,12144051,12149034,12150036,12150047,12150048,12150050,12150057,
  12151001,12151002,12151003,12151004,12151005,12151006,12151009,12151010,
  12151011,12151012,12151013,12151016,12151017,12151023,12151032,12151033,
  12151036,12151038,12151039,12151040,12151041,12151044,12151045,12151046,
  12151056,12151061,12151062,12152007,12155011,12155012,12155013,12156020,
  12158069,12160025,12162005,12163057,12164063,12165010,12167007,12168056,
  12168063,12169063,12171004
 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_he3au200_2014 = {
  15171017 };

//_________________
const std::vector<unsigned int> StHbtBasicEventCut::bad_run_list_dau200_2016 = {
  17138024,17139038,17140040,17136049,17137012,17140045,17139039,17135012,17138023,
  17139013,17139015,17140015,17140003,17140045,17137015 };

//_________________
void StHbtBasicEventCut::setEventMult(const int& lo, const int& hi) {
  
  if ( lo > hi ) {
    std::cout << "[WARNING] StHbtBasicEventCut::setEventMult -- lo>hi \n Resetting...\n";
    mRefMult[0] = -1;
    mRefMult[1] = 10000;
    return;
  }

  mRefMult[0] = ( ( lo < std::numeric_limits<short>::min() ) ?
		  std::numeric_limits<short>::min() :
		  (short)lo );

  mRefMult[1] = ( ( hi > std::numeric_limits<short>::max() ) ?
		  std::numeric_limits<short>::max() :
		  (short)hi );
}

//_________________
void StHbtBasicEventCut::setBTofTrayMult(const int& lo, const int& hi) {
  
  if ( lo > hi ) {
    std::cout << "[WARNING] StHbtBasicEventCut::setBTofTrayMult -- lo>hi \n Resetting...\n";
    mBTofTrayMult[0] = -1;
    mBTofTrayMult[1] = 10000;
    return;
  }

  mBTofTrayMult[0] = ( ( lo< std::numeric_limits<short>::min() ) ?
		       std::numeric_limits<short>::min() :
		       (short)lo );

  mBTofTrayMult[1] = ( ( hi > std::numeric_limits<short>::max() ) ?
		       std::numeric_limits<short>::max() :
		       (short)hi );
}

//_________________
void StHbtBasicEventCut::setBTofMatchMult(const int& lo, const int& hi) {
  
  if ( lo > hi ) {
    std::cout << "[WARNING] StHbtBasicEventCut::setBTofMatchMult -- lo>hi \n Resetting...\n";
    mBTofMatch[0] = -1;
    mBTofMatch[1] = 10000;
    return;
  }

  mBTofMatch[0] = ( ( lo< std::numeric_limits<short>::min() ) ?
		    std::numeric_limits<short>::min() :
		    (short)lo );

  mBTofMatch[1] = ( ( hi > std::numeric_limits<short>::max() ) ?
		    std::numeric_limits<short>::max() :
		    (short)hi );
}

//_________________
void StHbtBasicEventCut::setCent9(const int& lo, const int& hi) {
  if ( lo > hi ) {
    std::cout << "[WARNING] StHbtBasicEventCut::setCent9 -- lo>hi \n Resetting...\n";
    mCent9[0] = 0;
    mCent9[1] = 8;
    return;
  }

  if ( lo<0 || lo>8 ) {
    std::cout << "[WARNING] StHbtBasicEventCut::setCent9 -- Bad lo value \n Resetting...\n";
    mCent9[0] = -1;
  }
  else {
    mCent9[0] = (short)lo;
  }

  if ( hi<0 || hi>8 ) {
    std::cout << "[WARNING] StHbtBasicEventCut::setCent9 -- Bad hi value \n Resetting...\n";
    mCent9[1] = 8;
  }
  else {
    mCent9[1] = (short)hi;
  }
}
