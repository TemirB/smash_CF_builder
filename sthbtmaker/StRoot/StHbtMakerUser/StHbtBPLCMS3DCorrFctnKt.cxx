//
// A class to calculate 3D correlation for pairs of identical particles
//

// StHbtMakerUser headers
#include "StHbtMakerUser/StHbtBPLCMS3DCorrFctnKt.h"

// ROOT headers
#include "TMath.h"
#include "TString.h"

// C++ headers
#include <cmath>

#ifdef __ROOT__
ClassImp(StHbtBPLCMS3DCorrFctnKt);
#endif

//_________________
StHbtBPLCMS3DCorrFctnKt::StHbtBPLCMS3DCorrFctnKt(const char* title, const int& nBins,
                                                 const double& qLo, const double& qHi,
                                                 const int& ktBins, const double& ktLo,
                                                 const double& ktHi):
  StHbtBaseCorrFctn() {
  // Clean histograms
  for (int iHisto=0; iHisto<20; iHisto++ ) {
    mNumerator[iHisto] = nullptr;
    mDenominator[iHisto] = nullptr;
    mQinvHisto[iHisto] = nullptr;
  } // for (int iHisto=0; iHisto<20; iHisto++ )

  // Set general parameters
  setHistoParameters(nBins, qLo, qHi);
  setKtRange(ktBins, ktLo, ktHi);

  // Define string parameters
  TString baseName(title);
  TString baseTitle(title);
  TString appendix = ";q_{out} (GeV/c);q_{side} (GeV/c);q_{long} (GeV/c)";

  // Loop over kTBins
  for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++ ) {

    // Set numerator
    baseName = title;
    baseName += "_num_";
    baseName += iKtBin;
    baseTitle = baseName;
    baseTitle += " ";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
    baseTitle += "#leq k_{T} (GeV/c) #leq";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
    baseTitle += appendix;
    mNumerator[iKtBin] = new TH3F(baseName.Data(), baseTitle.Data(),
                                  mNQbins, mQRange[0], mQRange[1],
                                  mNQbins, mQRange[0], mQRange[1],
                                  mNQbins, mQRange[0], mQRange[1]);
    mNumerator[iKtBin]->Sumw2();

    // Denominator
    baseName = title;
    baseName += "_den_";
    baseName += iKtBin;
    baseTitle = baseName;
    baseTitle += " ";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
    baseTitle += "#leq k_{T} (GeV/c) #leq";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
    baseTitle += appendix;
    mDenominator[iKtBin] = new TH3F(baseName.Data(), baseTitle.Data(),
                                    mNQbins, mQRange[0], mQRange[1],
                                    mNQbins, mQRange[0], mQRange[1],
                                    mNQbins, mQRange[0], mQRange[1]);
    mDenominator[iKtBin]->Sumw2();

    // Weighted denominator
    baseName = title;
    baseName += "_qinv_";
    baseName += iKtBin;
    baseTitle = baseName;
    baseTitle += " ";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * iKtBin) );
    baseTitle += "#leq k_{T} (GeV/c) #leq";
    baseTitle += Form("%3.2f",( mKtRange[0] + mKtStep * (iKtBin+1) ) );
    baseTitle += appendix;
    mQinvHisto[iKtBin] = new TH3F(baseName.Data(), baseTitle.Data(),
                                  mNQbins, mQRange[0], mQRange[1],
                                  mNQbins, mQRange[0], mQRange[1],
                                  mNQbins, mQRange[0], mQRange[1]);
    mQinvHisto[iKtBin]->Sumw2();
  } // for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++ )
}

//_________________
StHbtBPLCMS3DCorrFctnKt::StHbtBPLCMS3DCorrFctnKt(const StHbtBPLCMS3DCorrFctnKt& copy):
  StHbtBaseCorrFctn(copy),
  mNQbins( copy.mNQbins ),
  mNKtBins( copy.mNKtBins ),
  mKtStep( copy. mKtStep ) {

  // Copy constructor
  for (int i=0; i<2; i++) {
    mQRange[i] = copy.mQRange[i];
    mKtRange[i] = copy.mKtRange[i];
  }

  // Clean histograms
  for (int iHisto=0; iHisto<20; iHisto++ ) {
    if(mNumerator[iHisto])   { delete mNumerator[iHisto]; mNumerator[iHisto] = nullptr; }
    if(mDenominator[iHisto]) { delete mDenominator[iHisto]; mDenominator[iHisto] = nullptr; }
    if(mQinvHisto[iHisto])   { delete mQinvHisto[iHisto]; mQinvHisto[iHisto] = nullptr; }
  } // for (int iHisto=0; iHisto<20; iHisto++ )

  // Loop over kT bins and make histogram copies
  for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++) {
    mNumerator[iKtBin] = new TH3F( *copy.mNumerator[iKtBin] );
    mNumerator[iKtBin]->Sumw2();
    mDenominator[iKtBin] = new TH3F( *copy.mDenominator[iKtBin] );
    mDenominator[iKtBin]->Sumw2();
    mQinvHisto[iKtBin] = new TH3F( *copy.mQinvHisto[iKtBin] );
    mQinvHisto[iKtBin]->Sumw2();
  }
}

//____________________________
StHbtBPLCMS3DCorrFctnKt::~StHbtBPLCMS3DCorrFctnKt() {
  // Destructor
  for (int i=0; i<20; i++) {
    if (mNumerator[i])   { delete mNumerator[i]; mNumerator[i]=nullptr; }
    if (mDenominator[i]) { delete mDenominator[i]; mDenominator[i]=nullptr; }
    if (mQinvHisto[i])   { delete mQinvHisto[i]; mQinvHisto[i]=nullptr; }
  } // for (int i=0; i<20; i++)
}

//_________________________
StHbtBPLCMS3DCorrFctnKt& StHbtBPLCMS3DCorrFctnKt::operator=(const StHbtBPLCMS3DCorrFctnKt& copy) {

  // Assignment operator
  if (this != &copy) {
    mNQbins = copy.mNQbins;
    mQRange[0] = copy.mQRange[0];
    mQRange[1] = copy.mQRange[1];
    mNKtBins = copy.mNKtBins;
    mKtStep = copy.mKtStep;
    mKtRange[0] = copy.mKtRange[0];
    mKtRange[1] = copy.mKtRange[1];

    // Clean histograms
    for (int iHisto=0; iHisto<20; iHisto++ ) {
      if(mNumerator[iHisto])   { delete mNumerator[iHisto]; mNumerator[iHisto] = nullptr; }
      if(mDenominator[iHisto]) { delete mDenominator[iHisto]; mDenominator[iHisto] = nullptr; }
      if(mQinvHisto[iHisto])   { delete mQinvHisto[iHisto]; mQinvHisto[iHisto] = nullptr; }
    } // for (int iHisto=0; iHisto<20; iHisto++ )

    // Loop over kT bins and make histogram copies
    for (int iKtBin=0; iKtBin<mNKtBins; iKtBin++) {
      mNumerator[iKtBin] = new TH3F( *copy.mNumerator[iKtBin] );
      mNumerator[iKtBin]->Sumw2();
      mDenominator[iKtBin] = new TH3F( *copy.mDenominator[iKtBin] );
      mDenominator[iKtBin]->Sumw2();
      mQinvHisto[iKtBin] = new TH3F( *copy.mQinvHisto[iKtBin] );
      mQinvHisto[iKtBin]->Sumw2();
    }
  }

  return *this;
}

//_________________________
void StHbtBPLCMS3DCorrFctnKt::writeOutHistos() {
  // Write out all histograms to file
  for (int i=0; i<mNKtBins; i++) {
    mNumerator[i]->Write();
    mDenominator[i]->Write();
    mQinvHisto[i]->Write();
  } // for (int i=0; i<mNKtBins; i++)
}

//______________________________
TList* StHbtBPLCMS3DCorrFctnKt::getOutputList() {
  // Prepare the list of objects to be written to the output
  TList *tOutputList = new TList();

  for (int i=0; i<mNKtBins; i++) {
    tOutputList->Add(mNumerator[i]);
    tOutputList->Add(mDenominator[i]);
    tOutputList->Add(mQinvHisto[i]);
  } // for (int i=0; i<mNKtBins; i++)

  return tOutputList;
}

//_________________________
void StHbtBPLCMS3DCorrFctnKt::finish() {
  /* empty */
}

//____________________________
StHbtString StHbtBPLCMS3DCorrFctnKt::report() {
  // Construct the report
  TString report("LCMS frame Bertsch-Pratt 3D correlation functions with kT binning report:\n");
  for (int iKt=0; iKt<mNKtBins; iKt++) {
    report += TString::Format("Number of entries in %d-th numerator                :\t%E\n",
                              iKt, mNumerator[iKt]->GetEntries() );
    report += TString::Format("Number of entries in %d-th denominator              :\t%E\n",
                              iKt, mDenominator[iKt]->GetEntries() );
    report += TString::Format("Number of entries in %d-th qInv weighted denominator:\t%E\n",
                              iKt, mDenominator[iKt]->GetEntries() );
  } // for (int iKt=0; iKt<mNKtBins; iKt++)

  if (mPairCut) {
    report += "Report from the front-loaded PairCut specific to this CorrFctn\n";
    report += mPairCut->report();
  }
  else {
    report += "No front-loaded PairCut specific to this CorrFctn\n";
  }

  return StHbtString((const char *)report);
}

//_________________
void StHbtBPLCMS3DCorrFctnKt::addRealPair(StHbtPair* pair) {
  // Perform operations on real pairs

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
  // Check front-loaded pair cut
  if ( mPairCut && !mPairCut->pass(pair) ) {
    return;
  }

  // Find index for the current kT value
  int mIndexKt = (int)( ( pair->kT() - mKtRange[0] ) / mKtStep );

  // Check that index is in the requested kT range
  if ( (mIndexKt>=0) && (mIndexKt<mNKtBins) ) {
    // Check that histrogram exists
    if ( mNumerator[mIndexKt] ) {
      mNumerator[mIndexKt]->Fill( pair->qOutCMS(),
                                  pair->qSideCMS(),
                                  pair->qLongCMS(),
                                  1. );
    }
  } // if ( (mIndexKt>=0) && (mIndexKt<mNKtBins) )
}

//_________________
void StHbtBPLCMS3DCorrFctnKt::addMixedPair(StHbtPair* pair) {

  if(pair->kT() < mKtRange[0] || pair->kT() > mKtRange[1]) return;
  // Check front-loaded pair cut
  if ( mPairCut && !mPairCut->pass(pair) ) {
    return;
  }

  // Find index for the current kT value
  int mIndexKt = (int)( ( pair->kT() - mKtRange[0] ) / mKtStep );

  // Check that index is in the requested kT range
  if ( (mIndexKt>=0) && (mIndexKt<mNKtBins) ) {

    // Check that histrogram exists
    if ( mDenominator[mIndexKt] ) {
      mDenominator[mIndexKt]->Fill( pair->qOutCMS(),
                                    pair->qSideCMS(),
                                    pair->qLongCMS(),
                                    1. );
    }

    // Check that histrogram exists
    if ( mQinvHisto[mIndexKt] ) {
      mQinvHisto[mIndexKt]->Fill( pair->qOutCMS(),
                                  pair->qSideCMS(),
                                  pair->qLongCMS(),
                                  TMath::Abs( pair->qInv() ) );
    }
  } // if ( (mIndexKt>=0) && (mIndexKt<mNKtBins) )
}

//_________________
void StHbtBPLCMS3DCorrFctnKt::setKtRange(const int& nKtBins, const float& kTLow, const float& kTHi) {
  if ( nKtBins>= 1) {
    mNKtBins = nKtBins;
  }
  else {
    std::cout << "[WARNING} void StHbtBPLCMS3DCorrFctnKt::setKtRange - "
              << "Number of kT bins must be positive" << std::endl;
    mNKtBins = 1;
  }

  if ( kTLow<kTHi ) {
    mKtRange[0] = kTLow;
    mKtRange[1] = kTHi;
  }
  else {
    std::cout << "[WARNING} void StHbtBPLCMS3DCorrFctnKt::setKtRange - "
              << "kTLow < kTHi. Resetting to the integral" << std::endl;
    mKtRange[0] = 0.;
    mKtRange[1] = 1.5;
  }
  mKtStep = ( mKtRange[1] - mKtRange[0] ) /  mNKtBins;
}

//_________________
void StHbtBPLCMS3DCorrFctnKt::setHistoParameters(const int& nBins,  const float& qLo,  const float& qHi) {
  if ( qLo > qHi ) {
    std::cout << "[WARNING] void StHbtBPLCMS3DCorrFctnKt::void setHistoParameters - "
              << " qLo > qHi. Resetting to defaults." << std::endl;
    mQRange[0] = -0.4;
    mQRange[1] = 0.4;
  }
  else {
    mQRange[0] = qLo;
    mQRange[1] = qHi;
  }

  if ( nBins<1 ) {
    std::cout << "[WARNING] void StHbtBPLCMS3DCorrFctnKt::void setHistoParameters - "
              << " nQbins<1. Resetting to defaults." << std::endl;
    mNQbins = 80;
  }
  else {
    mNQbins = nBins;
  }
}
