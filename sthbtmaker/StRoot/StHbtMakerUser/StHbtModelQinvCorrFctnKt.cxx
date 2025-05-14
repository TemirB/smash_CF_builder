//
// One-dimensional correlation function for the model estimations
//

// StHbtMaker headers
#include "StHbtMaker/StHbtModelGausLCMSFreezeOutGenerator.h"
#include "StHbtMaker/StHbtModelHiddenInfo.h"
#include "StHbtMaker/StHbtModelManager.h"
#include "StHbtMaker/StHbtPair.h"

// StHbtMakerUser headers
#include "StHbtMakerUser/StHbtModelQinvCorrFctnKt.h"

// ROOT headers
#include "TH1D.h"
#include "TString.h"

#ifdef __ROOT__
ClassImp(StHbtModelQinvCorrFctnKt);
#endif

//_________________
StHbtModelQinvCorrFctnKt::StHbtModelQinvCorrFctnKt(const char *title,
                                                   const int& nQbins,
                                                   const double& qLo,
                                                   const double& qHi,
                                                   const int& nKtBins,
                                                   const double& ktLo,
                                                   const double& ktHi,
                                                   const bool& isFillDenominators):
  StHbtBaseCorrFctn(),
  mManager(nullptr) {
  // Constructor

  // Define number of kT bins and kT step
  setKtRange(nKtBins, ktLo, ktHi);

  // Set fill denominator histograms
  mFillMixedDistributions = isFillDenominators;

  TString baseName(title);
  TString baseTitle(title);
  TString appendix = ";q_{inv} (GeV/c);Entries";

  // Histogram loop
  for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++) {

    // Numberators

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
    baseName += "_num_wei_";
    baseName += iKtBin;
    baseTitle = baseName;
    baseTitle += " ";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
    baseTitle += "#leq k_{T} (GeV/c) #leq";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
    baseTitle += appendix;
    TH1D *histoNumW = new TH1D(baseName.Data(), baseTitle.Data(),
                               nQbins, qLo, qHi);
    histoNumW->Sumw2();
    mNumeratorWeighted.push_back( histoNumW );

    // Denominators

    if ( mFillMixedDistributions ) {

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

      baseName = title;
      baseName += "_den_wei_";
      baseName += iKtBin;
      baseTitle = baseName;
      baseTitle += " ";
      baseTitle += Form("%3.2f",(mKtRange[0] + mKtStep * iKtBin) );
      baseTitle += "#leq k_{T} (GeV/c) #leq";
      baseTitle += Form("%3.2f",(mKtRange[0] + mKtStep * (iKtBin+1)));
      baseTitle += appendix;
      TH1D *histoDenW = new TH1D(baseName.Data(), baseTitle.Data(),
                                 nQbins, qLo, qHi);
      histoDenW->Sumw2();
      mDenominatorWeighted.push_back( histoDenW );
    } // if ( mFillMixedDistributions )

  } // for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++)
}

//_________________
StHbtModelQinvCorrFctnKt::StHbtModelQinvCorrFctnKt(const StHbtModelQinvCorrFctnKt& c) :
  StHbtBaseCorrFctn(c),
  mManager(nullptr),
  mFillMixedDistributions(c.mFillMixedDistributions) {
  // Copy constructor

  setKtRange( c.mNKtBins, c.mKtRange[0], c.mKtRange[1] );

  // Create histograms for multiple kT bins
  for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
    mNumerator.push_back( ( c.mNumerator.at(iCF) ) ? new TH1D( *c.mNumerator.at(iCF) ) : nullptr );
    mNumeratorWeighted.push_back( ( c.mNumeratorWeighted.at(iCF) ) ? new TH1D( *c.mNumeratorWeighted.at(iCF) ) : nullptr );

    if ( mFillMixedDistributions ) {
      mDenominator.push_back( ( c.mDenominator.at(iCF) ) ? new TH1D( *c.mDenominator.at(iCF) ) : nullptr );
      mDenominatorWeighted.push_back( ( c.mDenominatorWeighted.at(iCF) ) ? new TH1D( *c.mDenominatorWeighted.at(iCF) ) : nullptr );
    }
  } // for ( int iCF=0; iCF<mNKtBins; iCF++ )

  mManager = c.mManager;
}

//_________________
StHbtModelQinvCorrFctnKt::~StHbtModelQinvCorrFctnKt() {
  // Destructor
  if ( !mNumerator.empty() )           mNumerator.clear();
  if ( !mNumeratorWeighted.empty() )   mNumeratorWeighted.clear();
  if ( !mDenominator.empty() )         mDenominator.clear();
  if ( !mDenominatorWeighted.empty() ) mDenominatorWeighted.clear();
}

//_________________
StHbtModelQinvCorrFctnKt& StHbtModelQinvCorrFctnKt::operator=(const StHbtModelQinvCorrFctnKt& c) {

  // Assignment operator
  if (this == &c) {
    return *this;
  }

  setKtRange( c.mNKtBins, c.mKtRange[0], c.mKtRange[1] );
  mFillMixedDistributions = c.mFillMixedDistributions;

  for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
    mNumerator.push_back( ( c.mNumerator.at(iCF) ) ? new TH1D( *c.mNumerator.at(iCF) ) : nullptr );
    mNumeratorWeighted.push_back( ( c.mNumeratorWeighted.at(iCF) ) ? new TH1D( *c.mNumeratorWeighted.at(iCF) ) : nullptr );

    if ( mFillMixedDistributions ) {
      mDenominator.push_back( ( c.mDenominator.at(iCF) ) ? new TH1D( *c.mDenominator.at(iCF) ) : nullptr );
      mDenominatorWeighted.push_back( ( c.mDenominatorWeighted.at(iCF) ) ? new TH1D( *c.mDenominatorWeighted.at(iCF) ) : nullptr );
    }
  } // for ( int iCF=0; iCF<mNKtBins; iCF++ )

  mManager = c.mManager;

  return *this;
}

//_________________
void StHbtModelQinvCorrFctnKt::connectToManager(StHbtModelManager *manager) {
  mManager = manager;
}

//_________________
StHbtString StHbtModelQinvCorrFctnKt::report() {
  // Make a report
  StHbtString tStr = "StHbtModelQinvCorrFctnKt report";

  int mNumeratorEntries = 0;
  int mNumeratorWEntries = 0;
  int mDenominatorEntries = 0;
  int mDenominatorWEntries = 0;

  for (int i=0; i<mNKtBins; i++) {
    mNumeratorEntries += (int)mNumerator.at(i)->GetEntries();
    mNumeratorWEntries += (int)mNumeratorWeighted.at(i)->GetEntries();
    if ( mFillMixedDistributions ) {
      mDenominatorEntries += (int)mDenominator.at(i)->GetEntries();
      mDenominatorWEntries += (int)mDenominatorWeighted.at(i)->GetEntries();
    }
  } // for (int i=0; i<mNumberKt; i++)

  tStr += TString::Format( "\nTotal number of pairs in the numerator  :\t%d\n", mNumeratorEntries );
  tStr += TString::Format( "\nTotal number of pairs in the weighted numerator  :\t%d\n", mNumeratorWEntries );
  tStr += TString::Format( "Total number of pairs in the denominator:\t%d\n", mDenominatorEntries );
  tStr += TString::Format( "Total number of pairs in the weighted denominator:\t%d\n", mDenominatorEntries );

  for(int i=0; i<mNKtBins; i++) {
    tStr += TString::Format( "Total number of pairs in %d-th numerator :\t%E\n",
                             i, mNumerator.at(i)->GetEntries() );
    tStr += TString::Format( "Total number of pairs in %d-th weighted numerator :\t%E\n",
                             i, mNumeratorWeighted.at(i)->GetEntries() );

    if ( mFillMixedDistributions ) {
      tStr += TString::Format( "Total number of pairs in %d-th denominator  :\t%E\n",
                               i, mDenominator.at(i)->GetEntries() );
      tStr += TString::Format( "Total number of pairs in %d-th weighted denominator  :\t%E\n",
                               i, mDenominatorWeighted.at(i)->GetEntries() );
    }
  } // for(int i=0; i<mNKtBins; i++)

  if (mPairCut) {
    tStr += "Here is the PairCut specific to this CorrFctn\n";
    tStr += mPairCut->report();
  }
  else {
    tStr += "No PairCut specific to this CorrFctn\n";
  }

  return tStr;
}

//_________________
void StHbtModelQinvCorrFctnKt::addRealPair(StHbtPair* pair) {
  // Perform operations on pairs from same event

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
  // Check if pair passes front-loaded cut if exists
  if ( mPairCut && !mPairCut->pass(pair) ) {
    return;
  }

  // Find index for the current kT value
  int mIndexKt = (int)( ( ( pair->kT() - mKtRange[0] ) / mKtStep ) );

  // Check that index is in the requested kT range
  if ( ( mIndexKt>=0 ) && ( mIndexKt<mNKtBins ) ) {

    // Retrieve femtoscopic weight
    double weight = mManager->weight(pair);

    if ( mNumerator.at(mIndexKt) ) {
      mNumerator.at(mIndexKt)->Fill( fabs( pair->qInv() ), 1. );
      mNumeratorWeighted.at(mIndexKt)->Fill( fabs( pair->qInv() ),  weight );
    }
    else {
      std::cout << "[ERROR] void StHbtQinvCorrFctnKt::addRealPair(StHbtPair* pair) - "
                << "No correlation function with index: " << mIndexKt << " was found"
                << std::endl;
    }
  } // if ( ( mIndexKt>=0 ) && ( mIndexKt<mNKtBins ) )
}

//_________________
void StHbtModelQinvCorrFctnKt::addMixedPair(StHbtPair* pair) {
  // Perform operations on pairs from mixed events

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
  // Check if pair passes front-loaded cut if exists
  if ( mPairCut && !mPairCut->pass(pair) ) {
    return;
  }

  if ( mFillMixedDistributions ) {

    // Find index for the current kT value
    int mIndexKt = (int)( ( pair->kT() - mKtRange[0] ) / mKtStep );

    if ( ( mIndexKt>=0 ) && ( mIndexKt<mNKtBins ) ) {

      // Retrieve femtoscopic weight
      double weight = mManager->weight(pair);

      if ( mDenominator.at(mIndexKt) ) {
        mDenominator.at(mIndexKt)->Fill( fabs( pair->qInv() ), 1. );
        mDenominatorWeighted.at(mIndexKt)->Fill( fabs( pair->qInv() ), weight );
      }
      else {
        std::cout << "[ERROR] void StHbtQinvCorrFctnKt::addMixedPair(StHbtPair* pair) - "
                  << "No correlation function with index: " << mIndexKt << " was found"
                  << std::endl;
      }
    } // if ( ( mIndexKt>=0 ) && ( mIndexKt<mNumberKt ) )
  } // if ( mFillMixedDistributions )
}

//_________________
void StHbtModelQinvCorrFctnKt::eventBegin(const StHbtEvent* /* event */) {
  /* empty */
}

//_________________
void StHbtModelQinvCorrFctnKt::eventEnd(const StHbtEvent* /* event */) {
  /* empty */
}

//_________________
void StHbtModelQinvCorrFctnKt::finish() {
  /* empty */
}

//_________________
void StHbtModelQinvCorrFctnKt::writeOutHistos() {

  // Write out data histos
  for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
    mNumerator.at(iCF)->Write();
    mNumeratorWeighted.at(iCF)->Write();

    if ( mFillMixedDistributions ) {
      mDenominator.at(iCF)->Write();
      mDenominatorWeighted.at(iCF)->Write();
    }
  }
}

//_________________
TList* StHbtModelQinvCorrFctnKt::getOutputList() {

  // Prepare the list of objects to be written to the output
  TList *tOutputList = new TList();

  for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
    tOutputList->Add( mNumerator.at(iCF) );
    tOutputList->Add( mNumeratorWeighted.at(iCF) );

    if ( mFillMixedDistributions ) {
      tOutputList->Add( mDenominator.at(iCF) );
      tOutputList->Add( mDenominatorWeighted.at(iCF) );
    }
  }
  return tOutputList;
}

//_________________
void StHbtModelQinvCorrFctnKt::setKtRange(const int& nbins, const double& ktLo, const double& ktHi) {
  if ( nbins>= 1) {
    mNKtBins = nbins;
  }
  else {
    std::cout << "[WARNING} void StHbtModelQinvCorrFctnKt::setKtRange - "
              << "Number of kT bins must be positive" << std::endl;
    mNKtBins = 1;
  }

  if ( ktLo<ktHi ) {
    mKtRange[0] = ktLo;
    mKtRange[1] = ktHi;
  }
  else {
    std::cout << "[WARNING} void StHbtModelQinvCorrFctnKt::setKtRange - "
              << "kTLow < kTHi. Resetting to the integral" << std::endl;
    mKtRange[0] = 0.05;
    mKtRange[1] = 1.05;
  }
  mKtStep = ( mKtRange[1] - mKtRange[0] ) /  mNKtBins;
}
