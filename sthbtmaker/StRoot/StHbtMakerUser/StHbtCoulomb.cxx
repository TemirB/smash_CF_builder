//
// Class that performs Coulomb correction
//

// StHbtMaker headers
#include "StHbtCoulomb.h"
#ifdef _VANILLA_ROOT_
#include "StHbtMaker/PhysicalConstants.h"
#else
#include "StarClassLibrary/PhysicalConstants.h"
#endif

// C++ headers
#include <cstdio>
#include <cassert>
#include <iostream>
#include <fstream>

// ROOT headers
#include "TMath.h"

#ifdef __ROOT__
ClassImp(StHbtCoulomb)
#endif

//_________________
StHbtCoulomb::StHbtCoulomb() : mFile(""), mRadius(-1.), mZ1Z2(1.), mEta{}, mCoulomb{}, mNLines(0) {

  mFile = "/afs/rhic.bnl.gov/star/hbt/coul/StHbtCorrectionFiles/correctionpp.dat";
  if (!mFile) {
    std::cout << " No file, dummy!" << std::endl;
    assert(0);
  }
  std::cout << "StHbtCoulomb::StHbtCoulomb() - You have 1 default Coulomb correction!" << std::endl;
}

//_________________
StHbtCoulomb::StHbtCoulomb(const char* readFile, const double& radius, const double& charge) :
  mFile( readFile ),
  mRadius( radius ),
  mZ1Z2( charge ),
  mNLines( 0 ) {

  // Constructor with parameters
  createLookupTable( mRadius );
  std::cout << "StHbtCoulomb::StHbtCoulomb(...) - You have 1 Coulomb correction!" << std::endl;
}

//_________________
StHbtCoulomb::StHbtCoulomb(const StHbtCoulomb& copy) :
  mFile( copy.mFile ),
  mRadius( copy.mRadius ),
  mZ1Z2( copy.mZ1Z2 ),
  mNLines( 0 ) {

  // Copy constructor
  createLookupTable( mRadius );
}

//_________________
StHbtCoulomb& StHbtCoulomb::operator=(const StHbtCoulomb& copy) {
  // Assignment operator
  if ( this !=  &copy ) {
    mFile = copy.mFile;
    mRadius = copy.mRadius;
    mZ1Z2 = copy.mZ1Z2;

    createLookupTable( mRadius );
  }

  return *this;
}

//_________________
StHbtCoulomb::~StHbtCoulomb() {
  /* empty */
}

//_________________
void StHbtCoulomb::setRadius(const double& radius) {
  // Set the Coulomb radius
  std::cout << " StHbtCoulomb::setRadius() " << std::endl;
  mRadius = radius;
  createLookupTable(mRadius);
}

//_________________
void StHbtCoulomb::setFile(const char* readFile) {
  std::cout << " StHbtCoulomb::setFile() " << std::endl;
  mFile = readFile;
  // Create new lookup table since file has changed
  if ( mRadius>0.0 ) {
    createLookupTable( mRadius );
  }
}

//_________________
void StHbtCoulomb::setChargeProduct(const double& charge) {
  std::cout << " StHbtCoulomb::setChargeProduct() " << std::endl;
  if ( mZ1Z2!=charge ) {
    mZ1Z2 = charge;
    if ( mZ1Z2>0 ) {
      mFile = "/afs/rhic.bnl.gov/star/hbt/coul/StHbtCorrectionFiles/correctionpp.dat";
    }
    else {
      mFile = "/afs/rhic.bnl.gov/star/hbt/coul/StHbtCorrectionFiles/correctionpm.dat";
    }
    createLookupTable(mRadius);
  }
}

//_________________
void StHbtCoulomb::createLookupTable(const double& radius) {
  // Read radii from mFile
  // Create array(pair) of linear interpolation between radii
  std::cout << " StHbtCoulomb::createLookupTable() " << std::endl;

  if (radius<0.0) {
    std::cout << " StHbtCoulomb::createLookupTable -> NEGATIVE RADIUS " << std::endl;
    std::cout << "  call StHbtCoulomb::setRadius(r) with positive r " << std::endl;
    std::cerr << " StHbtCoulomb::createLookupTable -> NEGATIVE RADIUS " << std::endl;
    std::cerr << "  call StHbtCoulomb::setRadius(r) with positive r " << std::endl;
    assert(0);
  }

  std::ifstream mystream(mFile);
  if ( !mystream ) {
    std::cout << "Could not open file" << std::endl;
    assert(0);
  }
  else {
    std::cout << "Input correction file opened" << std::endl;
  }

  static char tempstring[2001];
  static float radii[2000];
  static int NRadii = 0;
  NRadii = 0;

  if (!mystream.getline(tempstring,2000)) {
    std::cout << "Could not read radii from file" << std::endl;
    assert(0);
  }

  for (unsigned int ii=0; ii<strlen(tempstring); ii++) {
    while (tempstring[ii]==' ') ii++;
    sscanf(&tempstring[ii++],"%f",&radii[++NRadii]);
    while ( tempstring[ii]!=' ' && (ii)<strlen(tempstring) )ii++;
  }

  std::cout << " Read " << NRadii << " radii from file" << std::endl;

  static double LowRadius = -1.0;
  static double HighRadius = -1.0;
  static int LowIndex = 0;
  LowRadius = -1.0;
  HighRadius = -1.0;
  LowIndex = 0;
  for(int iii=1; iii<=NRadii-1; iii++) { // Loop to one less than #radii
    if ( radius >= radii[iii] && radius <= radii[iii+1] ) {
      LowRadius = radii[iii];
      HighRadius = radii[iii+1];
      LowIndex = iii;
    }
  }
  if ( (LowRadius < 0.0) || (HighRadius < 0.0) ) {
    std::cout << "StHbtCoulomb::createLookupTable --> Problem interpolating radius" << std::endl;
    std::cout << "  Check range of radii in lookup file...." << std::endl;
    std::cerr << "StHbtCoulomb::createLookupTable --> Problem interpolating radius" << std::endl;
    std::cerr << "  Check range of radii in lookup file...." << std::endl;
    assert(0);
  }

  static double corr[100];           // array of corrections ... must be > NRadii
  mNLines = 0;
  static double tempEta = 0;
  tempEta = 0;
  while (mystream >> tempEta) {
    for (int i=1; i<=NRadii; i++) {
      mystream >> corr[i];
    }
    static double LowCoulomb = 0;
    static double HighCoulomb = 0;
    static double nCorr = 0;
    LowCoulomb = corr[LowIndex];
    HighCoulomb = corr[LowIndex+1];
    nCorr = ( (radius-LowRadius)*HighCoulomb+(HighRadius-radius)*LowCoulomb )/(HighRadius-LowRadius);
      mEta[mNLines] = tempEta;     // Eta
      mCoulomb[mNLines] = nCorr;   // Interpolated Coulomb correction for radius
      mNLines++;
  }
  mystream.close();
  std::cout << "Lookup Table is created with " << mNLines << " points" << std::endl;
}

//_________________
double StHbtCoulomb::coulombCorrect(const double& eta) {
  // Interpolates in eta
  if (mRadius < 0.0) {
    std::cout << "StHbtCoulomb::coulombCorrect(eta) --> Trying to correct for negative radius!" << std::endl;
    std::cerr << "StHbtCoulomb::coulombCorrect(eta) --> Trying to correct for negative radius!" << std::endl;
    assert(0);
  }
  static int middle=0;
  middle=int( (mNLines-1)/2 );
  if (eta*mEta[middle]<0.0) {
    std::cout << "StHbtCoulomb::coulombCorrect(eta) --> eta: " << eta
	      << " has wrong sign for data file! " << std::endl;
    std::cerr << "StHbtCoulomb::coulombCorrect(eta) --> eta: " << eta
	      << " has wrong sign for data file! " << std::endl;
    assert(0);
  }

  static double Corr = 0;
  Corr = -1.0;

  if ( (eta>mEta[0]) && (mEta[0]>0.0) ) {
    Corr = mCoulomb[0];
    return (Corr);
  }
  if ( (eta<mEta[mNLines-1]) && (mEta[mNLines-1]<0.0) ) {
    Corr = mCoulomb[mNLines-1];
    return (Corr);
  }
  // This is a binary search for the bracketing pair of data points
  static int high = 0;
  static int low = 0;
  static int width = 0;
  high = mNLines-1;
  low = 0;
  width = high-low;
  middle = int(width/2.0); // Was instantiated above
  while (middle > 0) {
    if (mEta[low+middle] < eta) {
      // eta is in the 1st half
      high-=middle;
      width = high-low;
      middle = int(width/2.0);
    }
    else {
      // eta is in the 2nd half
      low+=middle;
      width = high-low;
      middle = int(width/2.0);
    }
  }
  // Make sure we found the right one
  if ( (mEta[low] >= eta) && (eta >= mEta[low+1]) ) {
    static double LowEta = 0;
    static double HighEta = 0;
    static double LowCoulomb = 0;
    static double HighCoulomb = 0;
    LowEta = mEta[low];
    HighEta = mEta[low+1];
    LowCoulomb = mCoulomb[low];
    HighCoulomb = mCoulomb[low+1];
    //      cout << LowEta << " *** Eta *** " << HighEta << endl;
    //      cout << LowCoulomb << " *** Coulomb *** " << HighCoulomb << endl;
    Corr = ( (eta-LowEta)*HighCoulomb+(HighEta-eta)*LowCoulomb )/(HighEta-LowEta);
  }
  if (Corr<0.0) {
    std::cout << "StHbtCoulomb::coulombCorrect(eta) --> No correction" << std::endl;
    std::cout << "  Check range of eta in file: Input eta  " << eta << std::endl;
    std::cerr << "StHbtCoulomb::coulombCorrect(eta) --> No correction" << std::endl;
    std::cerr << "  Check range of eta in file: Input eta  " << eta << std::endl;
    assert(0);
  }
  return (Corr);
}

//_________________
double StHbtCoulomb::coulombCorrect(const double& eta,
				                            const double& radius) {
  // Checks radii ... input radius and mRadius
  // Calls createLookupTable if neccessary
  // Interpolate(linear) between etas in the created lookup table

  if (radius < 0.0) {
    if (mRadius < 0.0) {
      // Both radii are negative
      std::cout << "StHbtCoulomb::coulombCorrect(eta,r) --> input and member radii are negative!" << std::endl;
      std::cerr << "StHbtCoulomb::coulombCorrect(eta,r) --> input and member radii are negative!" << std::endl;
      assert(0);
    }
  }
  else {
    // radius > 0.0
    if (radius == mRadius) {
      // Both radii are positive and equal
      //      cout << "Radii are the same!!!" << endl;
    }
    else {
      // Both radii are positive but not equal
      mRadius = radius;
      createLookupTable(mRadius);
    }
  }

  // Interpolate in eta
  return ( coulombCorrect(eta) );
}

//_________________
double StHbtCoulomb::eta(const StHbtPair* pair) {
  static double px1,py1,pz1,px2,py2,pz2;
  static double px1new,py1new,pz1new;
  static double px2new,py2new,pz2new;
  static double vx1cms,vy1cms,vz1cms;
  static double vx2cms,vy2cms,vz2cms;
  static double VcmsX,VcmsY,VcmsZ;
  static double dv = 0.0;
  static double e1,e2,e1new,e2new;
  static double psi,theta;
  static double beta,gamma;
  static double VcmsXnew;

  px1 = pair->track1()->px();
  py1 = pair->track1()->py();
  pz1 = pair->track1()->pz();
  e1 = pair->track1()->e();
  px2 = pair->track2()->px();
  py2 = pair->track2()->py();
  pz2 = pair->track2()->pz();
  e2 = pair->track2()->e();

  VcmsX = ( px1+px2 ) / ( e1+e2 );
  VcmsY = ( py1+py2 ) / ( e1+e2 );
  VcmsZ = ( pz1+pz2 ) / ( e1+e2 );
  // Rotate Vcms to x-direction
  psi = TMath::ATan( VcmsY / VcmsX );
  VcmsXnew = VcmsX * TMath::Cos(psi) + VcmsY * TMath::Sin( psi );
  VcmsX = VcmsXnew;
  theta = TMath::ATan( VcmsZ / VcmsX );
  VcmsXnew = VcmsX * TMath::Cos( theta) + VcmsZ * TMath::Sin( theta );
  VcmsX = VcmsXnew;
  // Gamma and Beta
  beta = VcmsX;
  gamma = 1. / TMath::Sqrt( 1.0 - beta * beta );

  // Rotate p1 and p2 to new frame
  px1new = px1 * TMath::Cos( psi ) + py1 * TMath::Sin( psi );
  py1new = -px1 * TMath::Sin( psi ) + py1 * TMath::Cos( psi );
  px1 = px1new;
  px1new = px1 * TMath::Cos( theta ) + pz1 * TMath::Sin( theta );
  pz1new = -px1 * TMath::Sin( theta ) + pz1 * TMath::Cos( theta );
  px1 = px1new;
  py1 = py1new;
  pz1 = pz1new;

  px2new = px2 * TMath::Cos( psi ) + py2 * TMath::Sin( psi );
  py2new = -px2 * TMath::Sin( psi ) + py2 * TMath::Cos( psi );
  px2 = px2new;
  px2new = px2 * TMath::Cos( theta ) + pz2 * TMath::Sin( theta );
  pz2new = -px2 * TMath::Sin( theta ) + pz2 * TMath::Cos( theta );
  px2 = px2new;
  py2 = py2new;
  pz2 = pz2new;

  // Lorentz transform the x component and energy
  e1new = gamma * e1 - gamma * beta * px1;
  px1new = -gamma * beta * e1 + gamma * px1;
  e2new = gamma * e2 - gamma * beta * px2;
  px2new = -gamma * beta * e2 + gamma * px2;
  px1 = px1new;
  px2 = px2new;

  // New velocities
  vx1cms = px1 / e1new;
  vy1cms = py1 / e1new;
  vz1cms = pz1 / e1new;
  vx2cms = px2 / e2new;
  vy2cms = py2 / e2new;
  vz2cms = pz2 / e2new;

  // Velocity difference in CMS frame
  dv = TMath::Sqrt( ( vx1cms - vx2cms ) * ( vx1cms - vx2cms ) +
		    ( vy1cms - vy2cms ) * ( vy1cms - vy2cms ) +
		    ( vz1cms - vz2cms ) * ( vz1cms - vz2cms ) );

  return ( mZ1Z2 * fine_structure_const / (dv) );
}

//_________________
TH1D* StHbtCoulomb::correctionHistogram(const double& mass1, const double& mass2, const int& nBins,
					                              const double& low, const double& high) {
  if ( mass1!=mass2 ) {
    std::cout << "Masses not equal ... try again.  No histogram created." << std::endl;
    assert(0);
  }
  TH1D* correction = new TH1D("correction", "Coulomb correction", nBins, low, high);
  const double reducedMass = mass1 * mass2 / ( mass1 + mass2 );
  double qInv = low;
  //double dQinv = (high-low)/( (double)nBins );
  double eta;
  for (int ii=1; ii<=nBins; ii++) {
    qInv = correction->GetBinCenter(ii);
    eta = 2.0 * mZ1Z2 * reducedMass * fine_structure_const / ( qInv );
    coulombCorrect( eta );
    correction->Fill( qInv, coulombCorrect( eta, mRadius ) );
  }

  return correction;
}

#ifdef __ROOT__
TH1D* StHbtCoulomb::correctionHistogram(const TH1D* histo, const double mass) {

  TH1D* correction = (TH1D*) ( (TH1D*)histo)->Clone();
  correction->Reset();
  correction->SetDirectory(0);
  int nBins = correction->GetXaxis()->GetNbins();
  const double reducedMass = 0.5 * mass;
  double qInv;
  double eta;
  for (int ii=1; ii<=nBins; ii++) {
    qInv = correction->GetBinCenter(ii);
    eta = 2.0 * mZ1Z2 * reducedMass * fine_structure_const / ( qInv );
    correction->Fill( qInv, coulombCorrect( eta, mRadius ) );
  }

  return correction;
}

//_________________
TH3D* StHbtCoulomb::correctionHistogram(const TH3D* histo, const double mass) {

  TH3D* correction = (TH3D*) ( (TH3D*)histo )->Clone();
  correction->Reset();
  correction->SetDirectory(0);
  int nBinsX = correction->GetXaxis()->GetNbins();
  int nBinsY = correction->GetYaxis()->GetNbins();
  int nBinsZ = correction->GetZaxis()->GetNbins();
  const double reducedMass = 0.5 * mass;
  double eta;
  double qInv;
  int binNumber;
  for (int ii=1; ii<=nBinsX; ii++) {
    for (int iii=1; iii<=nBinsY; iii++) {
      for (int iv=1; iv<=nBinsZ; iv++) {
      	binNumber = histo->GetBin(ii,iii,iv);
      	qInv = histo->GetBinContent( binNumber );
      	eta = 2.0 * mZ1Z2 * reducedMass * fine_structure_const / ( qInv );
      	correction->SetBinContent(binNumber, coulombCorrect( eta, mRadius ) );
      } // for (int iv=1; iv<=nBinsZ; iv++)
    } // for (int iii=1; iii<=nBinsY; iii++)
  } // for (int ii=1; ii<=nBinsX; ii++)
  return correction;
}
#endif

//_________________
double StHbtCoulomb::coulombCorrect( const double& mass,   const double& charge,
				     const double& radius, const double& qInv ) {
  mRadius = radius;
  mZ1Z2 = charge;
  const double reducedMass = 0.5 * mass; // must be same mass particles
  double eta = 2.0 * mZ1Z2 * reducedMass * fine_structure_const / ( qInv );
  return coulombCorrect( eta, mRadius );
}
