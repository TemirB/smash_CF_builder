//
// Three-dimensional Bertsch-Pratt correlation function in LCMS for the model estimations
//

// StHbtMaker headers
#include "StHbtMaker/StHbtModelGausLCMSFreezeOutGenerator.h"
#include "StHbtMaker/StHbtModelHiddenInfo.h"
#include "StHbtMaker/StHbtModelManager.h"
#include "StHbtMaker/StHbtPair.h"

// StHbtMakerUser headers
#include "StHbtMakerUser/StHbtModelBPLCMS3DCorrFctnKt.h"

// ROOT headers
#include "TMath.h"
#include "TString.h"

// C++ headers
#include <cmath>

#ifdef __ROOT__
ClassImp(StHbtModelBPLCMS3DCorrFctnKt);
#endif

//_________________
StHbtModelBPLCMS3DCorrFctnKt::StHbtModelBPLCMS3DCorrFctnKt(const char* title,
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

  // Set general parameters
  setKtRange(nKtBins, ktLo, ktHi);

  // Set fill denominator histograms
  mFillMixedDistributions = isFillDenominators;

  // Define string parameters
  TString baseName(title);
  TString baseTitle(title);
  TString appendix = ";q_{out} (GeV/c);q_{side} (GeV/c);q_{long} (GeV/c)";

  // Loop over kTBins
  for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++ ) {

    // Numerators
    baseName = title;
    baseName += "_num_";
    baseName += iKtBin;
    baseTitle = baseName;
    baseTitle += " ";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
    baseTitle += "#leq k_{T} (GeV/c) #leq";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
    baseTitle += appendix;
    TH3F *histoNum = new TH3F(baseName.Data(), baseTitle.Data(),
                              nQbins, qLo, qHi,
                              nQbins, qLo, qHi,
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
    TH3F *histoNumW = new TH3F(baseName.Data(), baseTitle.Data(),
                               nQbins, qLo, qHi,
                               nQbins, qLo, qHi,
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
      baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
      baseTitle += "#leq k_{T} (GeV/c) #leq";
      baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
      baseTitle += appendix;
      TH3F *histoDen = new TH3F(baseName.Data(), baseTitle.Data(),
                                nQbins, qLo, qHi,
                                nQbins, qLo, qHi,
                                nQbins, qLo, qHi);

      histoDen->Sumw2();
      mDenominator.push_back( histoDen );

      baseName = title;
      baseName += "_den_wei_";
      baseName += iKtBin;
      baseTitle = baseName;
      baseTitle += " ";
      baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
      baseTitle += "#leq k_{T} (GeV/c) #leq";
      baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
      baseTitle += appendix;
      TH3F *histoDenW = new TH3F(baseName.Data(), baseTitle.Data(),
                                 nQbins, qLo, qHi,
                                 nQbins, qLo, qHi,
                                 nQbins, qLo, qHi);
      histoDenW->Sumw2();
      mDenominatorWeighted.push_back( histoDenW );
    }

  } // for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++ )
}

//_________________
StHbtModelBPLCMS3DCorrFctnKt::StHbtModelBPLCMS3DCorrFctnKt(const StHbtModelBPLCMS3DCorrFctnKt& c):
  StHbtBaseCorrFctn(c),
  mManager(nullptr),
  mFillMixedDistributions(c.mFillMixedDistributions) {
  // Copy constructor

  setKtRange( c.mNKtBins, c.mKtRange[0], c.mKtRange[1] );

  // Create histograms for multiple kT bins
  for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
    mNumerator.push_back( ( c.mNumerator.at(iCF) ) ? new TH3F( *c.mNumerator.at(iCF) ) : nullptr );
    mNumeratorWeighted.push_back( ( c.mNumeratorWeighted.at(iCF) ) ? new TH3F( *c.mNumeratorWeighted.at(iCF) ) : nullptr );

    if ( mFillMixedDistributions ) {
      mDenominator.push_back( ( c.mDenominator.at(iCF) ) ? new TH3F( *c.mDenominator.at(iCF) ) : nullptr );
      mDenominatorWeighted.push_back( ( c.mDenominatorWeighted.at(iCF) ) ? new TH3F( *c.mDenominatorWeighted.at(iCF) ) : nullptr );
    }
  } // for ( int iCF=0; iCF<mNKtBins; iCF++ )

  mManager = c.mManager;
}

//____________________________
StHbtModelBPLCMS3DCorrFctnKt::~StHbtModelBPLCMS3DCorrFctnKt() {
  // Destructor
  if ( !mNumerator.empty() )           mNumerator.clear();
  if ( !mNumeratorWeighted.empty() )   mNumeratorWeighted.clear();
  if ( !mDenominator.empty() )         mDenominator.clear();
  if ( !mDenominatorWeighted.empty() ) mDenominatorWeighted.clear();
}

//_________________________
StHbtModelBPLCMS3DCorrFctnKt& StHbtModelBPLCMS3DCorrFctnKt::operator=(const StHbtModelBPLCMS3DCorrFctnKt& c) {

  // Assignment operator
  if (this == &c) {
    return *this;
  }

  setKtRange( c.mNKtBins, c.mKtRange[0], c.mKtRange[1] );
  mFillMixedDistributions = c.mFillMixedDistributions;

  // Create histograms for multiple kT bins
  for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
    mNumerator.push_back( ( c.mNumerator.at(iCF) ) ? new TH3F( *c.mNumerator.at(iCF) ) : nullptr );
    mNumeratorWeighted.push_back( ( c.mNumeratorWeighted.at(iCF) ) ? new TH3F( *c.mNumeratorWeighted.at(iCF) ) : nullptr );

    if ( mFillMixedDistributions ) {
      mDenominator.push_back( ( c.mDenominator.at(iCF) ) ? new TH3F( *c.mDenominator.at(iCF) ) : nullptr );
      mDenominatorWeighted.push_back( ( c.mDenominatorWeighted.at(iCF) ) ? new TH3F( *c.mDenominatorWeighted.at(iCF) ) : nullptr );
    }
  } // for ( int iCF=0; iCF<mNKtBins; iCF++ )

  mManager = c.mManager;

  return *this;
}

//_________________
void StHbtModelBPLCMS3DCorrFctnKt::connectToManager(StHbtModelManager *manager) {
  mManager = manager;
}

//_________________
void StHbtModelBPLCMS3DCorrFctnKt::eventBegin(const StHbtEvent* /* event */ ) {
  /* empty */
}

//_________________
void StHbtModelBPLCMS3DCorrFctnKt::eventEnd(const StHbtEvent* /* event */ ) {
  /* empty */
}

//_________________________
void StHbtModelBPLCMS3DCorrFctnKt::writeOutHistos() {
  // Write out all histograms to file
  for ( int iCF=0; iCF<mNKtBins; iCF++ ) {
    mNumerator.at(iCF)->Write();
    mNumeratorWeighted.at(iCF)->Write();

    if ( mFillMixedDistributions ) {
      mDenominator.at(iCF)->Write();
      mDenominatorWeighted.at(iCF)->Write();
    }
  }
}

//______________________________
TList* StHbtModelBPLCMS3DCorrFctnKt::getOutputList() {
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

//_________________________
void StHbtModelBPLCMS3DCorrFctnKt::finish() {
  /* empty */
}

//____________________________
StHbtString StHbtModelBPLCMS3DCorrFctnKt::report() {
  // Construct the report
  StHbtString tStr = "LCMS frame Bertsch-Pratt 3D correlation functions with kT binning report with model weights:\n";

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
void StHbtModelBPLCMS3DCorrFctnKt::addRealPair(StHbtPair* pair) {
  // Perform operations on pairs from same event

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
  // Check front-loaded pair cut
  if ( mPairCut && !mPairCut->pass(pair) ) {
    return;
  }

  // Find index for the current kT value
  int mIndexKt = (int)( ( pair->kT() - mKtRange[0] ) / mKtStep );

  // Check that index is in the requested kT range
  if ( ( mIndexKt>=0 ) && ( mIndexKt<mNKtBins ) ) {

    // Retrieve femtoscopic weight
    double weight = mManager->weight(pair);

    if ( mNumerator.at(mIndexKt) ) {
      mNumerator.at(mIndexKt)->Fill( pair->qOutCMS(),
                                     pair->qSideCMS(),
                                     pair->qLongCMS(),
                                     1. );
      mNumeratorWeighted.at(mIndexKt)->Fill( pair->qOutCMS(),
                                             pair->qSideCMS(),
                                             pair->qLongCMS(),
                                             weight );
    }
    else {
      std::cout << "[ERROR] void StHbtModelBPLCMS3DCorrFctnKt::addRealPair(StHbtPair* pair) - "
                << "No correlation function with index: " << mIndexKt << " was found"
                << std::endl;
    }
  } // if ( ( mIndexKt>=0 ) && ( mIndexKt<mNKtBins ) )
}

//_________________
void StHbtModelBPLCMS3DCorrFctnKt::addMixedPair(StHbtPair* pair) {
  // Perform operations on pairs from mixed events

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
  // Check front-loaded pair cut
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
        mDenominator.at(mIndexKt)->Fill( pair->qOutCMS(),
                                         pair->qSideCMS(),
                                         pair->qLongCMS(),
                                         1. );
        mDenominatorWeighted.at(mIndexKt)->Fill( pair->qOutCMS(),
                                                 pair->qSideCMS(),
                                                 pair->qLongCMS(),
                                                 weight );
      }
      else {
        std::cout << "[ERROR] void StHbtModelBPLCMS3DCorrFctnKt::addMixedPair(StHbtPair* pair) - "
                  << "No correlation function with index: " << mIndexKt << " was found"
                  << std::endl;
      }
    } // if ( ( mIndexKt>=0 ) && ( mIndexKt<mNumberKt ) )
  } // if ( mFillMixedDistributions )
}

//_________________
void StHbtModelBPLCMS3DCorrFctnKt::setKtRange(const int& nbins, const double& ktLo, const double& ktHi) {
  if ( nbins>= 1) {
    mNKtBins = nbins;
  }
  else {
    std::cout << "[WARNING} void StHbtModelBPLCMS3DCorrFctnKt::setKtRange - "
              << "Number of kT bins must be positive" << std::endl;
    mNKtBins = 1;
  }

  if ( ktLo<ktHi ) {
    mKtRange[0] = ktLo;
    mKtRange[1] = ktHi;
  }
  else {
    std::cout << "[WARNING} void StHbtModelBPLCMS3DCorrFctnKt::setKtRange - "
              << "kTLow < kTHi. Resetting to the integral" << std::endl;
    mKtRange[0] = 0.05;
    mKtRange[1] = 1.05;
  }
  mKtStep = ( mKtRange[1] - mKtRange[0] ) /  mNKtBins;
}
