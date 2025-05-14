// ROOT headers
#include "TVector3.h"
#include "TMath.h"

//_________________
int TpcLocalTransform( TVector3& aPoint, int& aSector, int& aRow,
		       						 float& aU, double& aPhi) {

  static const int mNumberOfPadrows = 45;
  static const int mNumberOfPadrowsInner = 13;
  static const int mNumberOfSectors = 24;

  // Number of pad in a row for each padrow
  static int tNPadAtRow[mNumberOfPadrows] = {
    88,96,104,112,118,126,134,142,150,158,166,174,182,
    98,100,102,104,106,106,108,110,112,112,114,116,118,120,122,122,
    124,126,128,128,130,132,134,136,138,138,140,142,144,144,144,144
  };
  // Phi angle of each of 24 sectors
  static double tSectToPhi[mNumberOfSectors] = {
    2., 1., 0., 11., 10., 9., 8., 7., 6., 5., 4., 3.,
    4., 5., 6., 7., 8., 9., 10., 11., 0., 1., 2., 3.
  };

  // Pad size for innner and outer sector
  static double tPadWidthInner = 0.335;
  static double tPadWidthOuter = 0.67;

  static double tPi = TMath::Pi();

  // Find sector number
  aPhi = aPoint.Phi();
  if( aPhi<0. ) {
    aPhi+=(2*tPi);
  }
  aPhi += tPi/12.;

  if( aPhi>2*tPi ) {
    aPhi-=2*tPi;
  }

  int tiPhi = (int) (aPhi/tPi*6.);
  if( aPoint.Z() < 0 ) {
    aSector = (tiPhi<3) ? 3-tiPhi : 15-tiPhi;
  }
  else{
    aSector = (tiPhi<4) ? 21+tiPhi : 9+tiPhi;
  }
  aPhi = tSectToPhi[aSector-1] * tPi/6.;

  //if((fabs(aPhi-aPoint.phi())>(tPi/12)){
  //cout << "Sector missmatch " << aPhi << " " << aPoint.phi() << " "
  // << aSector << endl;
  //}

  // Calculate local coordinate
  float tR = aPoint.X() * TMath::Cos(aPhi) + aPoint.Y() * TMath::Sin(aPhi);
  aU =      -aPoint.X() * TMath::Sin(aPhi) + aPoint.Y() * TMath::Cos(aPhi);

  // Find pad row
  if(tR<57.6) {
    aRow = 0;
    return 1;
  }
  float radmax = 62.4;
  float spacing= 4.8;
  aRow=1;
  while ( ( tR > radmax) && ( aRow < 46 ) ) {
    aRow++;
    if ( aRow == 8 ) {
      radmax = 96.2;
      spacing = 5.2;
    }
    else {
      // Row 13 is the last one of the inner sector
      if ( aRow == mNumberOfPadrowsInner ) {
				radmax = 126.195;
				spacing = 2.0;
      }
      else {
				radmax += spacing;
      }
    } //else
  } //while ( ( tR > radmax) && ( aRow < 46 ) )
  if ( aRow > mNumberOfPadrows ) {
    //cout << "No pad row " << tR << endl;
    return 2;
  }

  // Check if u (=aU) inbound
  double tPadWidth = (aRow < 14 ) ? tPadWidthInner : tPadWidthOuter;
  if( TMath::Abs(aU) > ( tNPadAtRow[aRow-1] * tPadWidth/2. ) ) {
    return 3;
  }

  return 0;
}
