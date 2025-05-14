//
// One-dimensional correlation function with kT-binning
//

// StHbtMakerUser headers
#include "StHbtQinvCorrFctnKt.h"

// ROOT headers
#include "TString.h"

// C++ headers
#include <iostream>

#ifdef __ROOT__
ClassImp(StHbtQinvCorrFctnKt)
#endif

//_________________
StHbtQinvCorrFctnKt::StHbtQinvCorrFctnKt(const char* title,
																				 const int &nQbins, const double &qLo, const double &qHi,
																				 const int& nKtBins, const double& ktLo, const double& ktHi) :
 StHbtBaseCorrFctn() {
	// Constructor

	// Define number of kT bins and kT step
	setKtRange(nKtBins, ktLo, ktHi);

	TString baseName(title);
  TString baseTitle(title);
  TString appendix = ";q_{inv} (GeV/c);Entries";

  // Histogram loop
  for(int iKtBin=0; iKtBin<mNKtBins; iKtBin++) {

		baseName = title;
    baseName += "_num_";
    baseName += iKtBin;
    baseTitle = baseName;
    baseTitle += " ";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
    baseTitle += "#leq k_{T} (GeV/c) #leq";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
    baseTitle += appendix;
		TH1D *histoNum = new TH1D(baseName.Data(), baseTitle.Data(),
															nQbins, qLo, qHi);
		histoNum->Sumw2();
		mNumerator.push_back( histoNum );


    baseName = title;
    baseName += "_den_";
    baseName += iKtBin;
    baseTitle = baseName;
    baseTitle += " ";
    baseTitle += Form("%3.2f",(mKtRange[0] + mKtStep * iKtBin) );
    baseTitle += "#leq k_{T} (GeV/c) #leq";
    baseTitle += Form("%3.2f",(mKtRange[0] + mKtStep * (iKtBin+1)));
    baseTitle += appendix;
		TH1D *histoDen = new TH1D(baseName.Data(), baseTitle.Data(),
															nQbins, qLo, qHi);
		histoDen->Sumw2();
		mDenominator.push_back( histoDen );
  } // for(int i=0; i<mNumberKt; i++)
}

//_________________
StHbtQinvCorrFctnKt::StHbtQinvCorrFctnKt(const StHbtQinvCorrFctnKt& c) :
	StHbtBaseCorrFctn(c) {
	// Copy constructor

	setKtRange( c.mNKtBins, c.mKtRange[0], c.mKtRange[1] );

	for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
		mNumerator.push_back( ( c.mNumerator.at(iCF) ) ? new TH1D( *c.mNumerator.at(iCF) ) : nullptr );
		mDenominator.push_back( ( c.mDenominator.at(iCF) ) ? new TH1D( *c.mDenominator.at(iCF) ) : nullptr );
	} // for ( int iBin=0; iBin<mNumberKt; iBin++ )
}

//_________________
StHbtQinvCorrFctnKt& StHbtQinvCorrFctnKt::operator=(const StHbtQinvCorrFctnKt& c) {
	// Assignment operator
	if (this != &c) {

		setKtRange( c.mNKtBins, c.mKtRange[0], c.mKtRange[1] );

		for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
			mNumerator.push_back( ( c.mNumerator.at(iCF) ) ? new TH1D( *c.mNumerator.at(iCF) ) : nullptr );
			mDenominator.push_back( ( c.mDenominator.at(iCF) ) ? new TH1D( *c.mDenominator.at(iCF) ) : nullptr );
		} // for ( int iBin=0; iBin<mNumberKt; iBin++ )
	} // if (this != &c)

	return *this;
}

//_________________
StHbtQinvCorrFctnKt::~StHbtQinvCorrFctnKt() {
	// Destructor
	if ( !mNumerator.empty() ) {
		mNumerator.clear();
	}
	if ( !mDenominator.empty() ) {
		mDenominator.clear();
	}
}

//_________________
void StHbtQinvCorrFctnKt::writeOutHistos() {
	// Write histograms to the file
	if ( !mNumerator.empty() ) {
		for (unsigned int i=0; i<mNumerator.size(); i++ ) {
			mNumerator.at(i)->Write();
		}
	}
	if ( !mDenominator.empty() ) {
		for (unsigned int i=0; i<mDenominator.size(); i++ ) {
			mDenominator.at(i)->Write();
		}
	}
}

//_________________
TList* StHbtQinvCorrFctnKt::getOutputList() {
  // Prepare the list of objects to be written to the output
  TList *outputList = new TList();
  for (int i = 0; i < mNKtBins; i++) {
    outputList->Add( mNumerator.at(i) );
    outputList->Add( mDenominator.at(i) );
  }
  return outputList;
}

//_________________
void StHbtQinvCorrFctnKt::eventBegin(const StHbtEvent* /* event */) {
	/* empty */
}

//_________________
void StHbtQinvCorrFctnKt::eventEnd(const StHbtEvent* /* event */) {
	/* empty */
}

//_________________
void StHbtQinvCorrFctnKt::finish() {
	/* empty */
}

//_________________
void StHbtQinvCorrFctnKt::setKtRange(const int& nbins, const double& ktLo, const double& ktHi) {

	if ( nbins>= 1) {
    mNKtBins = nbins;
  }
  else {
    std::cout << "[WARNING} void StHbtQinvCorrFctnKt::setKtRange - "
              << "Number of kT bins must be positive" << std::endl;
    mNKtBins = 1;
  }

  if ( ktLo<ktHi ) {
    mKtRange[0] = ktLo;
    mKtRange[1] = ktHi;
  }
  else {
    std::cout << "[WARNING} void StHbtQinvCorrFctnKt::setKtRange - "
              << "kTLow < kTHi. Resetting to the integral" << std::endl;
    mKtRange[0] = 0.05;
    mKtRange[1] = 1.05;
  }
  mKtStep = ( mKtRange[1] - mKtRange[0] ) /  mNKtBins;
}

//_________________
void StHbtQinvCorrFctnKt::addRealPair(StHbtPair* pair) {

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
	// Check if pair passes front-loaded cut if exists
  if ( mPairCut && !mPairCut->pass( pair ) ) {
    return;
  }

  int mIndexKt = (int)( ( ( pair->kT() - mKtRange[0] ) / mKtStep ) );

  if ( ( mIndexKt>=0 ) && ( mIndexKt<mNKtBins ) ) {
		if ( mNumerator.at(mIndexKt) ) {
    	mNumerator.at(mIndexKt)->Fill( fabs( pair->qInv() ) );
		}
		else {
			std::cout << "[ERROR] void StHbtQinvCorrFctnKt::addRealPair(StHbtPair* pair) - "
								<< "No correlation function with index: " << mIndexKt << " was found"
								<< std::endl;
		}
  } // if ( ( mIndexKt>=0 ) && ( mIndexKt<mNumberKt ) )
}

//_________________
void StHbtQinvCorrFctnKt::addMixedPair(StHbtPair* pair) {

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
	// Check if pair passes front-loaded cut if exists
  if ( mPairCut && !mPairCut->pass( pair ) ) {
    return;
  }

  int mIndexKt = (int)( ( ( fabs( pair->kT() ) - mKtRange[0] ) / mKtStep ) );

  if ( ( mIndexKt>=0 ) && ( mIndexKt<mNKtBins ) ) {
		if ( mDenominator.at(mIndexKt) ) {
    	mDenominator.at(mIndexKt)->Fill( fabs( pair->qInv() ) );
		}
		else {
			std::cout << "[ERROR] void StHbtQinvCorrFctnKt::addMixedPair(StHbtPair* pair) - "
								<< "No correlation function with index: " << mIndexKt << " was found"
								<< std::endl;
		}
  } // if ( ( mIndexKt>=0 ) && ( mIndexKt<mNumberKt ) )
}

//_________________
StHbtString StHbtQinvCorrFctnKt::report() {

	// Make a report
  StHbtString tStr = "StHbtQinvCorrFctnKt report";

  int mNumeratorEntries = 0;
  int mDenominatorEntries = 0;

  for (int i=0; i<mNKtBins; i++) {
    mNumeratorEntries += (int)mNumerator.at(i)->GetEntries();
    mDenominatorEntries += (int)mDenominator.at(i)->GetEntries();
  } // for (int i=0; i<mNumberKt; i++)

	tStr += TString::Format( "\nTotal number of pairs in the numerator  :\t%d\n", mNumeratorEntries );
	tStr += TString::Format( "Total number of pairs in the denominator:\t%d\n", mDenominatorEntries );
  for(int i=0; i<mNKtBins; i++) {
		tStr += TString::Format( "Total number of pairs in %d-th numerator :\t%E\n",
														 i, mNumerator.at(i)->GetEntries() );
	  tStr += TString::Format( "Total number of pairs in %d-th denominator  :\t%E\n",
														 i, mDenominator.at(i)->GetEntries() );
  }

	if (mPairCut) {
		tStr += "Here is the PairCut specific to this CorrFctn\n";
		tStr += mPairCut->report();
	}
	else {
		tStr += "No PairCut specific to this CorrFctn\n";
	}

  return tStr;
}
