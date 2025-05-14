//
// Main class holding particle information
//

// C++ headers
#include <iostream>
#include <utility>

// StHbtMaker headers
#include "StHbtParticle.h"
#include "math_constants.h"

// ROOT headers
#include "TMath.h"

#ifdef __ROOT__
ClassImp(StHbtParticle)
#endif

float StHbtParticle::mPrimPimPar0= 9.05632e-01;
float StHbtParticle::mPrimPimPar1= -2.26737e-01;
float StHbtParticle::mPrimPimPar2= -1.03922e-01;
float StHbtParticle::mPrimPipPar0= 9.09616e-01;
float StHbtParticle::mPrimPipPar1= -9.00511e-02;
float StHbtParticle::mPrimPipPar2= -6.02940e-02;
float StHbtParticle::mPrimPmPar0= 0.;
float StHbtParticle::mPrimPmPar1= 0.;
float StHbtParticle::mPrimPmPar2= 0.;
float StHbtParticle::mPrimPpPar0= 0.;
float StHbtParticle::mPrimPpPar1= 0.;
float StHbtParticle::mPrimPpPar2= 0.;

float StHbtParticle::mInnerTpcRadius  = 50.f;   //[cm]
float StHbtParticle::mOuterTpcRadius = 200.f;   //[cm]
float StHbtParticle::mTpcHalfLength  = 200.f;   //[cm]
float StHbtParticle::tRowRadius[mNumberOfPadrows] = { 60, 64.8,69.6,74.4,79.2,84,88.8,93.6,98.8,
																								      104,109.2,114.4,119.6,127.195,129.195,131.195,
																								      133.195,135.195,137.195,139.195,141.195,
																								      143.195,145.195,147.195,149.195,151.195,
																								      153.195,155.195,157.195,159.195,161.195,
																								      163.195,165.195,167.195,169.195,171.195,
																								      173.195,175.195,177.195,179.195,181.195,
																								      183.195,185.195,187.195,189.195 };

//_________________
int TpcLocalTransform( TVector3& xgl,
								       int& iSector,
								       int& iPadrow,
								       float& xlocal,
								       double& ttPhi );

//_________________
StHbtParticle::StHbtParticle() :
  mTrack(nullptr),
  mV0(nullptr),
  mKink(nullptr),
  mXi(nullptr),
  mPx(0), mPy(0), mPz(0), mEnergy(0),
  mTpcTrackEntrancePointX(0),
  mTpcTrackEntrancePointY(0),
  mTpcTrackEntrancePointZ(0),
  mTpcTrackExitPointX(0),
  mTpcTrackExitPointY(0),
  mTpcTrackExitPointZ(0),
  mNominalPosSampleX{}, mNominalPosSampleY{}, mNominalPosSampleZ{},
  mTpcV0NegPosSampleX(nullptr),
  mTpcV0NegPosSampleY(nullptr),
  mTpcV0NegPosSampleZ(nullptr),
  mZ{}, mU{}, mSect{},
  mV0NegZ(nullptr),
  mV0NegU(nullptr),
  mV0NegSect(nullptr),
  mHiddenInfo(nullptr),
  mPurity{},
  mPrimaryVertexX(-999),
  mPrimaryVertexY(-999),
  mPrimaryVertexZ(-999),
  mSecondaryVertexX(nullptr),
  mSecondaryVertexY(nullptr),
  mSecondaryVertexZ(nullptr),
  mTpcV0PosEntrancePointX(nullptr),
  mTpcV0PosEntrancePointY(nullptr),
  mTpcV0PosEntrancePointZ(nullptr),
  mTpcV0PosExitPointX(nullptr),
  mTpcV0PosExitPointY(nullptr),
  mTpcV0PosExitPointZ(nullptr),
  mTpcV0NegEntrancePointX(nullptr),
  mTpcV0NegEntrancePointY(nullptr),
  mTpcV0NegEntrancePointZ(nullptr),
  mTpcV0NegExitPointX(nullptr),
  mTpcV0NegExitPointY(nullptr),
  mTpcV0NegExitPointZ(nullptr) {

  // Since we do not know which type of particles will be filled
  // we will make arrays for V0 by default
  mTpcV0NegPosSampleX = new float[mNumberOfPoints];
  mTpcV0NegPosSampleY = new float[mNumberOfPoints];
  mTpcV0NegPosSampleZ = new float[mNumberOfPoints];

  mV0NegZ = new float[mNumberOfPadrows];
  mV0NegU = new float[mNumberOfPadrows];
  mV0NegSect = new int[mNumberOfPadrows];

  mSecondaryVertexX = new float;
  mSecondaryVertexY = new float;
  mSecondaryVertexZ = new float;

  mTpcV0PosEntrancePointX = new float;
  mTpcV0PosEntrancePointY = new float;
  mTpcV0PosEntrancePointZ = new float;
  mTpcV0PosExitPointX = new float;
  mTpcV0PosExitPointY = new float;
  mTpcV0PosExitPointZ = new float;

  mTpcV0NegEntrancePointX = new float;
  mTpcV0NegEntrancePointY = new float;
  mTpcV0NegEntrancePointZ = new float;
  mTpcV0NegExitPointX = new float;
  mTpcV0NegExitPointY = new float;
  mTpcV0NegExitPointZ = new float;
}

//_________________
StHbtParticle::StHbtParticle(const StHbtParticle &part) :
  mTrack(nullptr), mV0(nullptr), mKink(nullptr),
  mXi(nullptr), mPx(part.mPx), mPy(part.mPy),
  mPz(part.mPz), mEnergy(part.mEnergy),
  mTpcTrackEntrancePointX(part.mTpcTrackEntrancePointX),
  mTpcTrackEntrancePointY(part.mTpcTrackEntrancePointY),
  mTpcTrackEntrancePointZ(part.mTpcTrackEntrancePointZ),
  mTpcTrackExitPointX(part.mTpcTrackExitPointX),
  mTpcTrackExitPointY(part.mTpcTrackExitPointY),
  mTpcTrackExitPointZ(part.mTpcTrackExitPointZ),
  mTpcV0NegPosSampleX(nullptr),
  mTpcV0NegPosSampleY(nullptr),
  mTpcV0NegPosSampleZ(nullptr),
  mV0NegZ(nullptr),
  mV0NegU(nullptr),
  mV0NegSect(nullptr),
  mHiddenInfo(nullptr),
  mPrimaryVertexX(part.mPrimaryVertexX),
  mPrimaryVertexY(part.mPrimaryVertexY),
  mPrimaryVertexZ(part.mPrimaryVertexZ),
  mSecondaryVertexX(nullptr),
  mSecondaryVertexY(nullptr),
  mSecondaryVertexZ(nullptr),
  mTpcV0PosEntrancePointX(nullptr),
  mTpcV0PosEntrancePointY(nullptr),
  mTpcV0PosEntrancePointZ(nullptr),
  mTpcV0PosExitPointX(nullptr),
  mTpcV0PosExitPointY(nullptr),
  mTpcV0PosExitPointZ(nullptr),
  mTpcV0NegEntrancePointX(nullptr),
  mTpcV0NegEntrancePointY(nullptr),
  mTpcV0NegEntrancePointZ(nullptr),
  mTpcV0NegExitPointX(nullptr),
  mTpcV0NegExitPointY(nullptr),
  mTpcV0NegExitPointZ(nullptr) {

  memcpy( mNominalPosSampleX, part.mNominalPosSampleX, sizeof(mNominalPosSampleX) );
  memcpy( mNominalPosSampleY, part.mNominalPosSampleY, sizeof(mNominalPosSampleY) );
  memcpy( mNominalPosSampleZ, part.mNominalPosSampleZ, sizeof(mNominalPosSampleZ) );
  if( part.mTpcV0NegPosSampleX ) {
    if( !mTpcV0NegPosSampleX ) {
      mTpcV0NegPosSampleX = new float[mNumberOfPoints];
    }
    for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
      mTpcV0NegPosSampleX[iPoint] = part.mTpcV0NegPosSampleX[iPoint];
    }
  }
  if( part.mTpcV0NegPosSampleY ) {
    if( !mTpcV0NegPosSampleY ) {
      mTpcV0NegPosSampleY = new float[mNumberOfPoints];
    }
    for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
      mTpcV0NegPosSampleY[iPoint] = part.mTpcV0NegPosSampleY[iPoint];
    }
  }
  if( part.mTpcV0NegPosSampleZ ) {
    if( !mTpcV0NegPosSampleZ ) {
      mTpcV0NegPosSampleZ = new float[mNumberOfPoints];
    }
    for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
      mTpcV0NegPosSampleZ[iPoint] = part.mTpcV0NegPosSampleZ[iPoint];
    }
  }

  // Copy hit position information in the TPC local coordinate system
  memcpy( mZ, part.mZ, sizeof(mZ) );
  memcpy( mU, part.mU, sizeof(mU) );
  memcpy( mSect, part.mSect, sizeof(mSect) );
  if( part.mV0NegZ ) {
    if( !mV0NegZ ) {
      mV0NegZ = new float[mNumberOfPadrows];
    }
    for(int iPad=0; iPad<mNumberOfPadrows; iPad++) {
      mV0NegZ[iPad] = part.mV0NegZ[iPad];
    }
  }
  if( part.mV0NegU ) {
    if( !mV0NegU ) {
      mV0NegU = new float[mNumberOfPadrows];
    }
    for(int iPad=0; iPad<mNumberOfPadrows; iPad++) {
      mV0NegU[iPad] = part.mV0NegU[iPad];
    }
  }
  if( part.mV0NegSect ) {
    if( !mV0NegSect ) {
      mV0NegSect = new int[mNumberOfPadrows];
    }
    for(int iPad=0; iPad<mNumberOfPadrows; iPad++) {
      mV0NegSect[iPad] = part.mV0NegSect[iPad];
    }
  }

  // Copy purity information
  memcpy( mPurity, part.mPurity, sizeof(mPurity) );

  // Copy secondary vertex information
  if( part.mSecondaryVertexX ) {
    setSecondaryVertexX( *part.mSecondaryVertexX );
  }
  if( part.mSecondaryVertexY ) {
    setSecondaryVertexY( *part.mSecondaryVertexY );
  }
  if( part.mSecondaryVertexZ ) {
    setSecondaryVertexZ( *part.mSecondaryVertexZ );
  }

  // Copy V0 entrance/exit point information
  if( part.mTpcV0PosEntrancePointX ) {
    setTpcV0PosEntrancePointX( *part.mTpcV0PosEntrancePointX );
  }
  if( part.mTpcV0PosEntrancePointY ) {
    setTpcV0PosEntrancePointY( *part.mTpcV0PosEntrancePointY );
  }
  if( part.mTpcV0PosEntrancePointZ ) {
    setTpcV0PosEntrancePointZ( *part.mTpcV0PosEntrancePointZ );
  }
  if( part.mTpcV0PosExitPointX ) {
    setTpcV0PosExitPointX( *part.mTpcV0PosExitPointX );
  }
  if( part.mTpcV0PosExitPointY ) {
    setTpcV0PosExitPointY( *part.mTpcV0PosExitPointY );
  }
  if( part.mTpcV0PosExitPointZ ) {
    setTpcV0PosExitPointZ( *part.mTpcV0PosExitPointZ );
  }
  if( part.mTpcV0NegEntrancePointX ) {
    setTpcV0NegEntrancePointX( *part.mTpcV0NegEntrancePointX );
  }
  if( part.mTpcV0NegEntrancePointY ) {
    setTpcV0NegEntrancePointY( *part.mTpcV0NegEntrancePointY );
  }
  if( part.mTpcV0NegEntrancePointZ ) {
    setTpcV0NegEntrancePointZ( *part.mTpcV0NegEntrancePointZ );
  }
  if( part.mTpcV0NegExitPointX ) {
    setTpcV0NegExitPointX( *part.mTpcV0NegExitPointX );
  }
  if( part.mTpcV0NegExitPointY ) {
    setTpcV0NegExitPointY( *part.mTpcV0NegExitPointY );
  }
  if( part.mTpcV0NegExitPointZ ) {
    setTpcV0NegExitPointZ( *part.mTpcV0NegExitPointZ );
  }

  if( part.mTrack ) {
    mTrack = new StHbtTrack( *part.mTrack );
  }
  if( part.mV0 ) {
    mV0 = new StHbtV0( *part.mV0 );
  }
  if( part.mKink ) {
    mKink = new StHbtKink( *part.mKink );
  }
  if( part.mXi ) {
    mXi = new StHbtXi( *part.mXi );
  }
}

//_________________
StHbtParticle& StHbtParticle::operator=(const StHbtParticle& part) {

  if ( this != &part ) {

    if( part.mTrack ) {
      if( !mTrack ) {
				mTrack = new StHbtTrack( *part.mTrack );
      }
      else {
				mTrack = part.mTrack;
      }
    }

    if( part.mV0 ) {
      if( !mV0 ) {
				mV0 = new StHbtV0( *part.mV0 );
      }
      else {
				mV0 = part.mV0;
      }
    } //if( part.mV0 )

    if( part.mKink ) {
      if( !mKink ) {
				mKink = new StHbtKink( *part.mKink );
      }
      else {
				mKink = part.mKink;
      }
    } //if( part.mKink )

    if( part.mXi ) {
      if( !mXi ) {
				mXi = new StHbtXi( *part.mXi );
      }
      else {
				mXi = part.mXi;
      }
    } //if( part.mXi )

    mPx = part.mPx;
    mPy = part.mPy;
    mPz = part.mPz;
    mEnergy = part.mEnergy;

    mTpcTrackEntrancePointX = part.mTpcTrackEntrancePointX;
    mTpcTrackEntrancePointY = part.mTpcTrackEntrancePointY;
    mTpcTrackEntrancePointZ = part.mTpcTrackEntrancePointZ;
    mTpcTrackExitPointX = part.mTpcTrackExitPointX;
    mTpcTrackExitPointY = part.mTpcTrackExitPointY;
    mTpcTrackExitPointZ = part.mTpcTrackExitPointZ;

    memcpy( mNominalPosSampleX, part.mNominalPosSampleX, sizeof(mNominalPosSampleX) );
    memcpy( mNominalPosSampleY, part.mNominalPosSampleY, sizeof(mNominalPosSampleY) );
    memcpy( mNominalPosSampleZ, part.mNominalPosSampleZ, sizeof(mNominalPosSampleZ) );

    if( part.mTpcV0NegPosSampleX ) {
      if( !mTpcV0NegPosSampleX ) {
				mTpcV0NegPosSampleX = new float;
      }
      mTpcV0NegPosSampleX = part.mTpcV0NegPosSampleX;
    } //if( part.mTpcV0NegPosSampleX )

    if( part.mTpcV0NegPosSampleY ) {
      if( !mTpcV0NegPosSampleY ) {
				mTpcV0NegPosSampleY = new float;
      }
      mTpcV0NegPosSampleY = part.mTpcV0NegPosSampleY;
    } //if( part.mTpcV0NegPosSampleY )

    if( part.mTpcV0NegPosSampleZ ) {
      if( !mTpcV0NegPosSampleZ ) {
				mTpcV0NegPosSampleZ = new float;
      }
      mTpcV0NegPosSampleZ = part.mTpcV0NegPosSampleZ;
    } //if( part.mTpcV0NegPosSampleZ )

    memcpy( mZ, part.mZ, sizeof( mZ ) );
    memcpy( mU, part.mU, sizeof( mU ) );
    memcpy( mSect, part.mSect, sizeof( mSect ) );

    if( part.mV0NegZ ) {
      if( !mV0NegZ ) {
				mV0NegZ = new float;
      }
      mV0NegZ = part.mV0NegZ;
    }

    if( part.mV0NegU ) {
      if( !mV0NegU ) {
				mV0NegU = new float;
      }
      mV0NegU = part.mV0NegU;
    }

    if( part.mV0NegSect ) {
      if( !mV0NegSect ) {
				mV0NegSect = new int[mNumberOfPadrows];
      }
      mV0NegSect = part.mV0NegSect;
    }

    delete mHiddenInfo;
    if( part.mHiddenInfo ) {
      mHiddenInfo = part.hiddenInfo()->clone();
    }

    memcpy( mPurity, part.mPurity, sizeof(mPurity) );

    mPrimaryVertexX = part.mPrimaryVertexX;
    mPrimaryVertexY = part.mPrimaryVertexY;
    mPrimaryVertexZ = part.mPrimaryVertexZ;

    if( part.mSecondaryVertexX ) {
      if( !mSecondaryVertexX ) {
				mSecondaryVertexX = new float;
      }
      mSecondaryVertexX = part.mSecondaryVertexX;
    }

    if( part.mSecondaryVertexY ) {
      if( !mSecondaryVertexY ) {
				mSecondaryVertexY = new float;
      }
      mSecondaryVertexY = part.mSecondaryVertexY;
    }

    if( part.mSecondaryVertexZ ) {
      if( !mSecondaryVertexZ ) {
				mSecondaryVertexZ = new float;
      }
      mSecondaryVertexZ = part.mSecondaryVertexZ;
    }

    // Copy entrance/exit points
    if( part.mTpcV0PosEntrancePointX ) {
      if( !mTpcV0PosEntrancePointX ) {
				mTpcV0PosEntrancePointX = new float;
      }
      mTpcV0PosEntrancePointX = part.mTpcV0PosEntrancePointX;
    } //if( part.mTpcV0PosEntrancePointX )
    if( part.mTpcV0PosEntrancePointY ) {
      if( !mTpcV0PosEntrancePointY ) {
				mTpcV0PosEntrancePointY = new float;
      }
      mTpcV0PosEntrancePointY = part.mTpcV0PosEntrancePointY;
    } //if( part.mTpcV0PosEntrancePointY )
    if( part.mTpcV0PosEntrancePointZ ) {
      if( !mTpcV0PosEntrancePointZ ) {
				mTpcV0PosEntrancePointZ = new float;
      }
      mTpcV0PosEntrancePointZ = part.mTpcV0PosEntrancePointZ;
    } //if( part.mTpcV0PosEntrancePointZ )
    if( part.mTpcV0PosExitPointX ) {
      if( !mTpcV0PosExitPointX ) {
				mTpcV0PosExitPointX = new float;
      }
      mTpcV0PosExitPointX = part.mTpcV0PosExitPointX;
    } //if( part.mTpcV0PosExitPointX )
    if( part.mTpcV0PosExitPointY ) {
      if( !mTpcV0PosExitPointY ) {
				mTpcV0PosExitPointY = new float;
      }
      mTpcV0PosExitPointY = part.mTpcV0PosExitPointY;
    } //if( part.mTpcV0PosExitPointY )
    if( part.mTpcV0PosExitPointZ ) {
      if( !mTpcV0PosExitPointZ ) {
				mTpcV0PosExitPointZ = new float;
      }
      mTpcV0PosExitPointZ = part.mTpcV0PosExitPointZ;
    } //if( part.mTpcV0PosExitPointZ )
    if( part.mTpcV0NegEntrancePointX ) {
      if( !mTpcV0NegEntrancePointX ) {
				mTpcV0NegEntrancePointX = new float;
      }
      mTpcV0NegEntrancePointX = part.mTpcV0NegEntrancePointX;
    } //if( part.mTpcV0NegEntrancePointX )
    if( part.mTpcV0NegEntrancePointY ) {
      if( !mTpcV0NegEntrancePointY ) {
				mTpcV0NegEntrancePointY = new float;
      }
      mTpcV0NegEntrancePointY = part.mTpcV0NegEntrancePointY;
    } //if( part.mTpcV0NegEntrancePointY )
    if( part.mTpcV0NegEntrancePointZ ) {
      if( !mTpcV0NegEntrancePointZ ) {
				mTpcV0NegEntrancePointZ = new float;
      }
      mTpcV0NegEntrancePointZ = part.mTpcV0NegEntrancePointZ;
    } //if( part.mTpcV0NegEntrancePointZ )
    if( part.mTpcV0NegExitPointX ) {
      if( !mTpcV0NegExitPointX ) {
				mTpcV0NegExitPointX = new float;
      }
      mTpcV0NegExitPointX = part.mTpcV0NegExitPointX;
    } //if( part.mTpcV0NegExitPointX )
    if( part.mTpcV0NegExitPointY ) {
      if( !mTpcV0NegExitPointY ) {
				mTpcV0NegExitPointY = new float;
      }
      mTpcV0NegExitPointY = part.mTpcV0NegExitPointY;
    } //if( part.mTpcV0NegExitPointY )
    if( part.mTpcV0NegExitPointZ ) {
      if( !mTpcV0NegExitPointZ ) {
				mTpcV0NegExitPointZ = new float;
      }
      mTpcV0NegExitPointZ = part.mTpcV0NegExitPointZ;
    } //if( part.mTpcV0NegExitPointZ )
  }

  return *this;
}

//_________________
StHbtParticle::~StHbtParticle() {
  if (mTrack) { delete mTrack; mTrack = nullptr; }
  if (mV0)    { delete mV0; mV0 = nullptr; }
  if (mKink)  { delete mKink; mKink = nullptr; }
  if (mXi)    { delete mXi; mXi = nullptr; }
  if (mTpcV0NegPosSampleX) delete mTpcV0NegPosSampleX;
  if (mTpcV0NegPosSampleY) delete mTpcV0NegPosSampleY;
  if (mTpcV0NegPosSampleZ) delete mTpcV0NegPosSampleZ;
  if (mV0NegZ) delete mV0NegZ;
  if (mV0NegU) delete mV0NegU;
  if (mV0NegSect) delete mV0NegSect;
  if (mHiddenInfo) delete mHiddenInfo;
  if (mSecondaryVertexX) delete mSecondaryVertexX;
  if (mSecondaryVertexY) delete mSecondaryVertexY;
  if (mSecondaryVertexZ) delete mSecondaryVertexZ;
  if (mTpcV0PosEntrancePointX) delete mTpcV0PosEntrancePointX;
  if (mTpcV0PosEntrancePointY) delete mTpcV0PosEntrancePointY;
  if (mTpcV0PosEntrancePointZ) delete mTpcV0PosEntrancePointZ;
  if (mTpcV0PosExitPointX) delete mTpcV0PosExitPointX;
  if (mTpcV0PosExitPointY) delete mTpcV0PosExitPointY;
  if (mTpcV0PosExitPointZ) delete mTpcV0PosExitPointZ;
  if (mTpcV0NegEntrancePointX) delete mTpcV0NegEntrancePointX;
  if (mTpcV0NegEntrancePointY) delete mTpcV0NegEntrancePointY;
  if (mTpcV0NegEntrancePointZ) delete mTpcV0NegEntrancePointZ;
  if (mTpcV0NegExitPointX) delete mTpcV0NegExitPointX;
  if (mTpcV0NegExitPointY) delete mTpcV0NegExitPointY;
  if (mTpcV0NegExitPointZ) delete mTpcV0NegExitPointZ;
}

//_________________
StHbtParticle::StHbtParticle(const StHbtTrack* const hbtTrack, const double& mass) :
  mTrack( new StHbtTrack(*hbtTrack) ),
  mV0(nullptr),
  mKink(nullptr),
  mXi(nullptr),
  mPx( hbtTrack->p().X() ),
  mPy( hbtTrack->p().Y() ),
  mPz( hbtTrack->p().Z() ),
  mEnergy( TMath::Sqrt( hbtTrack->ptot2() + mass*mass ) ),
  mTpcTrackEntrancePointX(0),
  mTpcTrackEntrancePointY(0),
  mTpcTrackEntrancePointZ(0),
  mTpcTrackExitPointX(0),
  mTpcTrackExitPointY(0),
  mTpcTrackExitPointZ(0),
  mNominalPosSampleX{},
  mNominalPosSampleY{},
  mNominalPosSampleZ{},
  mTpcV0NegPosSampleX(nullptr),
  mTpcV0NegPosSampleY(nullptr),
  mTpcV0NegPosSampleZ(nullptr),
  mZ{}, mU{}, mSect{},
  mV0NegZ(nullptr), mV0NegU(nullptr), mV0NegSect(nullptr),
  mHiddenInfo(nullptr),
  mPrimaryVertexX( hbtTrack->primaryVertex().X() ),
  mPrimaryVertexY( hbtTrack->primaryVertex().Y() ),
  mPrimaryVertexZ( hbtTrack->primaryVertex().Z() ),
  mSecondaryVertexX(nullptr),
  mSecondaryVertexY(nullptr),
  mSecondaryVertexZ(nullptr),
  mTpcV0PosEntrancePointX(nullptr),
  mTpcV0PosEntrancePointY(nullptr),
  mTpcV0PosEntrancePointZ(nullptr),
  mTpcV0PosExitPointX(nullptr),
  mTpcV0PosExitPointY(nullptr),
  mTpcV0PosExitPointZ(nullptr),
  mTpcV0NegEntrancePointX(nullptr),
  mTpcV0NegEntrancePointY(nullptr),
  mTpcV0NegEntrancePointZ(nullptr),
  mTpcV0NegExitPointX(nullptr),
  mTpcV0NegExitPointY(nullptr),
  mTpcV0NegExitPointZ(nullptr) {

  // Primary and secondary vertex positions INTENTIOANLLY set to (0,0,0)
  // in order to make all estimations for future pair cuts,
  // i.e. in order to remove merged tracks.
  // This also implies, that all tracks originate from (0,0,0)

  StHbtPhysicalHelix helix = hbtTrack->helix();
  TVector3 pVtx( 0., 0., 0. );
  TVector3 sVtx( 0., 0., 0. );
  TVector3 entrancePoint(0, 0, 0);
  TVector3 exitPoint(0, 0, 0);
  TVector3 posSample[mNumberOfPoints];

  calculateTpcExitAndEntrancePoints( &helix,
																     &pVtx,
																     &sVtx,
																     &entrancePoint,
																     &exitPoint,
																     &posSample[0],
																     &mZ[0],
																     &mU[0],
																     &mSect[0] );

  // Set TPC entrance and exit point parameters
  setNominalTpcExitPoint( exitPoint );
  setNominalTpcEntrancePoint( entrancePoint );
  setNominalPosSample( posSample );
  // mZ, mU and mSect arrays will be set in calculateTpcExitAndEntrancePoints()

  calculatePurity();

  mHiddenInfo = nullptr;
  if( hbtTrack->validHiddenInfo() ) {
    mHiddenInfo= hbtTrack->getHiddenInfo()->getParticleHiddenInfo();
  }
}

//_________________
StHbtParticle::StHbtParticle(const StHbtV0* const hbtV0,
			     									 const double& mass) :
  mTrack(nullptr),
  mV0( new StHbtV0( *hbtV0 ) ),
  mKink(nullptr),
  mXi(nullptr),
  mPx( hbtV0->momV0X() ),
  mPy( hbtV0->momV0Y() ),
  mPz( hbtV0->momV0Z() ),
  mEnergy( TMath::Sqrt( hbtV0->ptot2V0() + mass*mass ) ),
  mTpcTrackEntrancePointX(0), mTpcTrackEntrancePointY(0), mTpcTrackEntrancePointZ(0),
  mTpcTrackExitPointX(0), mTpcTrackExitPointY(0), mTpcTrackExitPointZ(0),
  mNominalPosSampleX{}, mNominalPosSampleY{}, mNominalPosSampleZ{},
  mTpcV0NegPosSampleX(nullptr), mTpcV0NegPosSampleY(nullptr), mTpcV0NegPosSampleZ(nullptr),
  mZ{}, mU{}, mSect{}, mV0NegZ(nullptr), mV0NegU(nullptr), mV0NegSect(nullptr),
  mHiddenInfo(nullptr),
  mPurity{},
  mPrimaryVertexX( hbtV0->primaryVertex().X() ),
  mPrimaryVertexY( hbtV0->primaryVertex().Y() ),
  mPrimaryVertexZ( hbtV0->primaryVertex().Z() ),
  mSecondaryVertexX( nullptr ),
  mSecondaryVertexY( nullptr ),
  mSecondaryVertexZ( nullptr ) {

  // Set secondary vertex information
  setSecondaryVertexX( hbtV0->decayPoint().X() );
  setSecondaryVertexY( hbtV0->decayPoint().Y() );
  setSecondaryVertexZ( hbtV0->decayPoint().Z() );

  // Retrieve helix of the positive track
  StHbtPhysicalHelix posHelix = hbtV0->helixPos();
  TVector3 primVtx( mPrimaryVertexX, mPrimaryVertexY, mPrimaryVertexZ );
  TVector3 secVtx( *mSecondaryVertexX, *mSecondaryVertexY, *mSecondaryVertexZ );
  TVector3 posEntrancePoint( 0, 0, 0 );
  TVector3 posExitPoint( 0, 0, 0 );
  TVector3 posSamplePos[mNumberOfPoints];

  calculateTpcExitAndEntrancePoints( &posHelix,
				     &primVtx,
				     &secVtx,
				     &posEntrancePoint,
				     &posExitPoint,
				     &posSamplePos[0],
				     &mZ[0],
				     &mU[0],
				     &mSect[0] );
  // Set positive daughter estimated parameters
  setTpcV0PosEntrancePoint( posEntrancePoint );
  setTpcV0PosExitPoint( posExitPoint );
  setNominalPosSample( posSamplePos );
  // mZ, mU and mSect arrays will be set in calculateTpcExitAndEntrancePoints(


  StHbtPhysicalHelix negHelix = hbtV0->helixNeg();
  TVector3 negEntrancePoint( 0, 0, 0 );
  TVector3 negExitPoint( 0, 0, 0 );
  TVector3 negSamplePos[mNumberOfPoints];
  mV0NegZ = new float[mNumberOfPadrows];
  mV0NegU = new float[mNumberOfPadrows];
  mV0NegSect = new int[mNumberOfPadrows];

  calculateTpcExitAndEntrancePoints( &negHelix,
																     &primVtx,
																     &secVtx,
																     &negEntrancePoint,
																     &negExitPoint,
																     &negSamplePos[0],
																     &mV0NegZ[0],
																     &mV0NegU[0],
																     &mV0NegSect[0] );

  // Set positive daughter estimated parameters
  setTpcV0NegEntrancePoint( negEntrancePoint );
  setTpcV0NegExitPoint( negExitPoint );
  setTpcV0NegPosSample( posSamplePos );
  // mZ, mU and mSect arrays will be set in calculateTpcExitAndEntrancePoints(

  mHiddenInfo= nullptr;
  if ( hbtV0->validHiddenInfo() ) {
    mHiddenInfo= hbtV0->getHiddenInfo()->clone();
  }
}

//_________________
StHbtParticle::StHbtParticle(const StHbtKink* const hbtKink,
			     									 const double& mass) :
  mTrack(nullptr),
  mV0(nullptr),
  mKink( new StHbtKink( *hbtKink ) ),
  mXi(nullptr),
  mPx( hbtKink->parent().p().X() ),
  mPy( hbtKink->parent().p().Y() ),
  mPz( hbtKink->parent().p().Z() ),
  mEnergy( TMath::Sqrt(hbtKink->parent().ptot2() + mass*mass) ),
  mTpcTrackEntrancePointX(0),
  mTpcTrackEntrancePointY(0),
  mTpcTrackEntrancePointZ(0),
  mTpcTrackExitPointX(0),
  mTpcTrackExitPointY(0),
  mTpcTrackExitPointZ(0),
  mNominalPosSampleX{},
  mNominalPosSampleY{},
  mNominalPosSampleZ{},
  mTpcV0NegPosSampleX( nullptr ),
  mTpcV0NegPosSampleY( nullptr ),
  mTpcV0NegPosSampleZ( nullptr ),
  mZ{}, mU{}, mSect{},
  mV0NegZ( nullptr ), mV0NegU( nullptr ), mV0NegSect( nullptr ),
  mHiddenInfo( nullptr ),
  mPurity{},
  mPrimaryVertexX( hbtKink->primaryVertex().X() ),
  mPrimaryVertexY( hbtKink->primaryVertex().Y() ),
  mPrimaryVertexZ( hbtKink->primaryVertex().Z() ),
  mSecondaryVertexX(nullptr),
  mSecondaryVertexY(nullptr),
  mSecondaryVertexZ(nullptr),
  mTpcV0PosEntrancePointX(nullptr),
  mTpcV0PosEntrancePointY(nullptr),
  mTpcV0PosEntrancePointZ(nullptr),
  mTpcV0PosExitPointX(nullptr),
  mTpcV0PosExitPointY(nullptr),
  mTpcV0PosExitPointZ(nullptr),
  mTpcV0NegEntrancePointX(nullptr),
  mTpcV0NegEntrancePointY(nullptr),
  mTpcV0NegEntrancePointZ(nullptr),
  mTpcV0NegExitPointX(nullptr),
  mTpcV0NegExitPointY(nullptr),
  mTpcV0NegExitPointZ(nullptr) {
    // Some information related to kink analysis should
    // be estimated here
}

//_________________
StHbtParticle::StHbtParticle(const StHbtXi* const hbtXi, const double& mass) :
  mTrack(nullptr),
  mV0(nullptr),
  mKink( nullptr ),
  mXi( new StHbtXi( *hbtXi ) ),
  mPx( hbtXi->momXi().X() ),
  mPy( hbtXi->momXi().Y() ),
  mPz( hbtXi->momXi().Z() ),
  mEnergy( TMath::Sqrt( hbtXi->ptot2Xi() + mass*mass) ),
  mTpcTrackEntrancePointX(0),
  mTpcTrackEntrancePointY(0),
  mTpcTrackEntrancePointZ(0),
  mTpcTrackExitPointX(0),
  mTpcTrackExitPointY(0),
  mTpcTrackExitPointZ(0),
  mNominalPosSampleX{},
  mNominalPosSampleY{},
  mNominalPosSampleZ{},
  mTpcV0NegPosSampleX( nullptr ),
  mTpcV0NegPosSampleY( nullptr ),
  mTpcV0NegPosSampleZ( nullptr ),
  mZ{}, mU{}, mSect{},
  mV0NegZ( nullptr ), mV0NegU( nullptr ), mV0NegSect( nullptr ),
  mHiddenInfo( nullptr ),
  mPurity{},
  mPrimaryVertexX( hbtXi->bachelor()->primaryVertex().X() ),
  mPrimaryVertexY( hbtXi->bachelor()->primaryVertex().Y() ),
  mPrimaryVertexZ( hbtXi->bachelor()->primaryVertex().Z() ),
  mSecondaryVertexX(nullptr),
  mSecondaryVertexY(nullptr),
  mSecondaryVertexZ(nullptr),
  mTpcV0PosEntrancePointX(nullptr),
  mTpcV0PosEntrancePointY(nullptr),
  mTpcV0PosEntrancePointZ(nullptr),
  mTpcV0PosExitPointX(nullptr),
  mTpcV0PosExitPointY(nullptr),
  mTpcV0PosExitPointZ(nullptr),
  mTpcV0NegEntrancePointX(nullptr),
  mTpcV0NegEntrancePointY(nullptr),
  mTpcV0NegEntrancePointZ(nullptr),
  mTpcV0NegExitPointX(nullptr),
  mTpcV0NegExitPointY(nullptr),
  mTpcV0NegExitPointZ(nullptr) {
    // Some information related to Xi analysis should
    // be estimated here
}

//_________________
void StHbtParticle::calculatePurity() {
  double tPt = fourMomentum().Perp();
  // pi -
  mPurity[0] = mPrimPimPar0*(1.-exp((tPt-mPrimPimPar1)/mPrimPimPar2));
  mPurity[0] *= mTrack->pidProbPion();
  // pi+
  mPurity[1] = mPrimPipPar0*(1.-exp((tPt-mPrimPipPar1)/mPrimPipPar2));
  mPurity[1] *= mTrack->pidProbPion();
  // K-
  mPurity[2] = mTrack->pidProbKaon();
  // K+
  mPurity[3] = mTrack->pidProbKaon();
  // pbar
  mPurity[4] = mTrack->pidProbProton();
  // p
  mPurity[5] = mTrack->pidProbProton();
}

//_________________
double StHbtParticle::pionPurity() {
  return (mTrack->charge()>0) ? mPurity[1] : mPurity[0];
}

//_________________
double StHbtParticle::kaonPurity() {
  return (mTrack->charge()>0) ? mPurity[3] : mPurity[2];
}

//_________________
double StHbtParticle::protonPurity() {
  return (mTrack->charge()>0) ? mPurity[5] : mPurity[4];
}

//_________________
void StHbtParticle::calculateTpcExitAndEntrancePoints(StHbtPhysicalHelix* tHelix,
																								      TVector3* PrimVert,
																								      TVector3* SecVert,
																								      TVector3* tmpTpcEntrancePoint,
																								      TVector3* tmpTpcExitPoint,
																								      TVector3* tmpPosSample,
																								      float* tmpZ,
																								      float* tmpU,
																								      int* tmpSect) {

  // This calculates the exit point of a secondary track,
  // either through the endcap or through the Outer Field Cage
  // We assume the track to start at tHelix.origin-PrimaryVertex
  // it also calculates the entrance point of the secondary track,
  // which is the point at which it crosses the inner field cage.
  TVector3 ZeroVec(0.,0.,0.);

  ZeroVec.SetX(SecVert->x()-PrimVert->x());
  ZeroVec.SetY(SecVert->y()-PrimVert->y());
  ZeroVec.SetZ(SecVert->z()-PrimVert->z());

  double dip, curv, phase;
  int h;
  curv = tHelix->curvature();
  dip  = tHelix->dipAngle();
  phase= tHelix->phase();
  h    = tHelix->h();

  StHbtHelix hel(curv, dip, phase, ZeroVec, h);

  std::pair< double, double > candidates;
  // This is how much length to go to leave through sides of TPC
  double sideLength;
  // This is how much length to go to leave through endcap of TPC
  double endLength;

  // Figure out how far to go to leave through side...
  candidates = hel.pathLength( mTpcHalfLength );
  sideLength = (candidates.first > 0) ? candidates.first : candidates.second;

  static TVector3 WestEnd( 0., 0., mTpcHalfLength  );
  static TVector3 EastEnd( 0., 0., -mTpcHalfLength );
  static TVector3 EndCapNormal( 0., 0., 1.0);

  endLength = hel.pathLength( WestEnd, EndCapNormal);
  if (endLength < 0.0) {
    endLength = hel.pathLength( EastEnd, EndCapNormal);
  }

  if (endLength < 0.0) {
    std::cout << "void StHbtParticle::calculateTpcExitAndEntrancePoints : "
	      << "Hey -- I cannot find an exit point out endcaps" << std::endl;
  }

  // OK, firstExitLength will be the shortest way out of the detector...
  double firstExitLength = (endLength < sideLength) ? endLength : sideLength;

  // Now then, let's return the POSITION at which particle leaves TPC...
  *tmpTpcExitPoint = hel.at( firstExitLength );

  // Finally, calculate the position at which the track crosses the inner field cage
  candidates = hel.pathLength( mInnerTpcRadius );

  sideLength = (candidates.first > 0) ? candidates.first : candidates.second;

  *tmpTpcEntrancePoint = hel.at(sideLength);

  // Check that the entrance point exists and was found
  if (std::isnan( tmpTpcEntrancePoint->X() ) ||
      std::isnan( tmpTpcEntrancePoint->Y() ) ||
      std::isnan( tmpTpcEntrancePoint->Z() ) ) {

    std::cout << "void StHbtParticle::calculateTpcExitAndEntrancePoints : NAN" << std::endl;
    std::cout << "tmpNominalTpcEntrancePoint = ( "
	      << tmpTpcEntrancePoint->X() << " , "
	      << tmpTpcEntrancePoint->Y() << " , "
	      << tmpTpcEntrancePoint->Z() << " ) " << std::endl;
    tmpTpcEntrancePoint->SetX(-9999.);
    tmpTpcEntrancePoint->SetY(-9999.);
    tmpTpcEntrancePoint->SetZ(-9999.);
  }

  // Check that the exit point exists and was found
  if ( std::isnan( tmpTpcExitPoint->X() ) ||
       std::isnan( tmpTpcExitPoint->Y() ) ||
       std::isnan( tmpTpcExitPoint->Z() ) ) {

    std::cout << "void StHbtParticle::calculateTpcExitAndEntrancePoints : NAN" << std::endl;
    std::cout << "tmpNominalTpcExitPoint = ( "
	      << tmpTpcExitPoint->X() << " , "
	      << tmpTpcExitPoint->Y() << " , "
	      << tmpTpcExitPoint->Z() << " ) " << std::endl;
    tmpTpcExitPoint->SetX(-9999.);
    tmpTpcExitPoint->SetY(-9999.);
    tmpTpcExitPoint->SetZ(-9999.);
  }

  // Mike Lisa: OK, let's try something a little more along the lines
  // of NA49 and E895 strategy. Calculate the "nominal" position at N
  // radii (say N=11) within the TPC, and for a pair cut use the average
  // separation of these N
  // Grigory Nigmatkulov: For the future measurements N was changed
  // to mNumberOfPoints and the *magic numbers* were changed to the
  // mInnerTpcRadius and mOuterTpcRadius
  int irad = 0;
  candidates = hel.pathLength( mInnerTpcRadius );
  float step  = (mOuterTpcRadius - mInnerTpcRadius) / ( mNumberOfPoints - 1 ) ;
  sideLength = (candidates.first > 0) ? candidates.first : candidates.second;

  // Declare and initialize variable outside the loop
  float radius = mInnerTpcRadius;

  // Loop over radii
  while( irad<mNumberOfPoints && !std::isnan( sideLength ) ) {

    radius = mInnerTpcRadius + irad * step;
    candidates = hel.pathLength( radius );
    sideLength = (candidates.first > 0) ? candidates.first : candidates.second;
    tmpPosSample[irad] = hel.at(sideLength);

    if(std::isnan(tmpPosSample[irad].x()) ||
       std::isnan(tmpPosSample[irad].y()) ||
       std::isnan(tmpPosSample[irad].z()) ) {

      std::cout << "tmpPosSample for radius = " << radius << " NAN"<< std::endl;
      std::cout << "tmpPosSample = ( "
		<< tmpPosSample[irad].X() << " , "
		<< tmpPosSample[irad].Y() << " , "
		<< tmpPosSample[irad].Z() << " ) " << std::endl;
      tmpPosSample[irad] =  TVector3(-9999.,-9999.,-9999);
    }

    // Do not forget to increment radii
    irad++;

    if ( irad<mNumberOfPoints ) {
      float radius = mInnerTpcRadius + irad*step;
      candidates = hel.pathLength(radius);
      sideLength = (candidates.first > 0) ? candidates.first : candidates.second;
    }
  } //while( irad<11 && !std::isnan(sideLength) )

  // In case, when track left TPC, the rest of postions will
  // be set to unphysical values
  for (int i=irad; i<11; i++) {
    tmpPosSample[i] = TVector3(-9999.,-9999.,-9999);
  }
  /*
  // Lets see if it will work out and move it to the protected area
  static float tRowRadius[mNumberOfPadrows] = {60,64.8,69.6,74.4,79.2,84,88.8,93.6,98.8,
					       104,109.2,114.4,119.6,127.195,129.195,131.195,
					       133.195,135.195,137.195,139.195,141.195,
					       143.195,145.195,147.195,149.195,151.195,
					       153.195,155.195,157.195,159.195,161.195,
					       163.195,165.195,167.195,169.195,171.195,
					       173.195,175.195,177.195,179.195,181.195,
					       183.195,185.195,187.195,189.195};
  */

  int tRow,tSect,tOutOfBound;
  double tLength,tPhi;
  float tU;
  TVector3 tPoint(0,0,0);
  TVector3 tn(0,0,0);
  TVector3 tr(0,0,0);
  int ti = 0;

  // Test to enter the loop
  candidates =  hel.pathLength(tRowRadius[ti]);
  tLength = (candidates.first > 0) ? candidates.first : candidates.second;

  if ( std::isnan(tLength) ) {

    std::cout << "tLength Init tmp NAN" << std::endl;
    std::cout << "padrow number = " << ti << " not reached " << std::endl;
    std::cout << "*** DO NOT ENTER THE LOOP***" << std::endl;

    // Sector
    tmpSect[ti] = -1;
  } //if ( std::isnan(tLength) )

  // Start iteration over all padrows
  while( ti<mNumberOfPadrows && !std::isnan(tLength) ) {

    candidates =  hel.pathLength(tRowRadius[ti]);
    tLength = (candidates.first > 0) ? candidates.first : candidates.second;

    if ( std::isnan(tLength) ) {

      std::cout << "tLength loop 1st NAN" << std::endl;
      std::cout << "padrow number =  " << ti << " not reached" << std::endl;
      std::cout << "*** THIS IS AN ERROR SHOULDN'T  LOOP ***" << std::endl;
      // Sector
      tmpSect[ti] = -1;
    } // if ( std::isnan(tLength) )

    tPoint = hel.at(tLength);
    // Find which sector it is on
    TpcLocalTransform( tPoint, tmpSect[ti], tRow, tU, tPhi );

    if ( std::isnan(tmpSect[ti]) ) {
      std::cout << "***ERROR tmpSect" << std::endl;
    }
    if ( std::isnan(tRow) ) {
      std::cout << "***ERROR tRow" << std::endl;
    }
    if ( std::isnan(tU) ) {
      std::cout << "***ERROR tU" << std::endl;
    }
    if ( std::isnan(tPhi) ) {
      std::cout << "***ERROR tPhi" << std::endl;
    }

    // calculate crossing plane
    tn.SetX( TMath::Cos(tPhi) );
    tn.SetY( TMath::Sin(tPhi) );
    tr.SetX( tRowRadius[ti] * TMath::Cos(tPhi) );
    tr.SetY( tRowRadius[ti] * TMath::Sin(tPhi) );

    // Find crossing point
    tLength = hel.pathLength(tr,tn);
    if ( std::isnan(tLength) ) {

      std::cout <<"tLength loop 2nd NAN" << std::endl;
      std::cout <<"padrow number = " << ti << " not reached" << std::endl;
      // Sector
      tmpSect[ti] = -2;
    } //if ( std::isnan(tLength) )

    tPoint = hel.at(tLength);
    tmpZ[ti] = tPoint.z();
    tOutOfBound = TpcLocalTransform( tPoint, tSect, tRow, tmpU[ti],  tPhi );
    if ( std::isnan(tSect) ) {
      std::cout << "***ERROR tSect 2" << std::endl;
    }
    if ( std::isnan(tRow) ) {
      std::cout << "***ERROR tRow 2" << std::endl;
    }
    if ( std::isnan(tmpU[ti]) ) {
      std::cout << "***ERROR tmpU[ti] 2" << std::endl;
    }
    if ( std::isnan(tPhi) ) {
      std::cout << "***ERROR tPhi 2 " << std::endl;
    }

    if( tOutOfBound ||
				( ( tmpSect[ti] == tSect ) && ( tRow != (ti+1) ) ) ) {
      // Sector
      tmpSect[ti]=-2;
    }
    else {

      if( tmpSect[ti] != tSect ) {

				// Try again on the other sector
				tn.SetX( TMath::Cos(tPhi) );
				tn.SetY( TMath::Sin(tPhi) );
				tr.SetX( tRowRadius[ti] * TMath::Cos(tPhi) );
				tr.SetY( tRowRadius[ti] * TMath::Sin(tPhi) );

				// Find crossing point
				tLength = hel.pathLength(tr,tn);
				tPoint = hel.at(tLength);
				if ( std::isnan(tLength) ) {
				  std::cout << "tLength loop 3rd NAN" << std::endl;
				  std::cout << "padrow number = " << ti << " not reached" << std::endl;
				  // Sector
				  tmpSect[ti] = -1;
				} //if ( std::isnan(tLength) )

				tmpZ[ti] = tPoint.z();
				tmpSect[ti] = tSect;
				tOutOfBound = TpcLocalTransform( tPoint, tSect, tRow, tmpU[ti], tPhi);

				if ( std::isnan(tSect) ) {
				  std::cout << "***ERROR tSect 3" << std::endl;
				}
				if ( std::isnan(tRow) ) {
				  std::cout << "***ERROR tRow 3" << std::endl;
				}
				if ( std::isnan(tmpU[ti]) ) {
				  std::cout << "***ERROR tmpU[ti] 3" << std::endl;
				}
				if ( std::isnan(tPhi) ) {
				  std::cout << "***ERROR tPhi 3 " << std::endl;
				}

				if( tOutOfBound || ( tSect != tmpSect[ti] ) || ( tRow!=(ti+1) ) ) {
				  // Sector
				  tmpSect[ti] = -1;
				} //if( tOutOfBound || ( tSect != tmpSect[ti] ) || ( tRow!=(ti+1) ) )
      } //if(tmpSect[ti] != tSect)
    } //else

    if (std::isnan(tmpSect[ti])){
      std::cout << "*******************ERROR***************************" << std::endl;
      std::cout <<"StHbtParticle--Fctn tmpSect=" << tmpSect[ti] << std::endl;
      std::cout << "*******************ERROR***************************" << std::endl;
    }
    if (std::isnan(tmpU[ti])){
      std::cout << "*******************ERROR***************************" << std::endl;
      std::cout <<"StHbtParticle--Fctn tmpU=" << tmpU[ti] << std::endl;
      std::cout << "*******************ERROR***************************" << std::endl;
    }
    if (std::isnan(tmpZ[ti])){
      std::cout << "*******************ERROR***************************" << std::endl;
      std::cout <<"StHbtParticle--Fctn tmpZ=" << tmpZ[ti] << std::endl;
      std::cout << "*******************ERROR***************************" << std::endl;
    }

    // If padrow ti not reached all other beyond are not reached
    // in this case set sector to -1
    if ( tmpSect[ti] == -1 ) {
      for (int tj=ti; tj<mNumberOfPadrows; tj++) {
				tmpSect[tj] = -1;
				ti=mNumberOfPadrows;
      }
    } //if ( tmpSect[ti] == -1 )

    // Increment padrow
    ti++;

    if ( ti<mNumberOfPadrows ) {
      candidates =  hel.pathLength(tRowRadius[ti]);
      tLength = (candidates.first > 0) ? candidates.first : candidates.second;
    } //if ( ti<mNumberOfPadrows )
  } //while( ti<mNumberOfPadrows && !std::isnan(tLength) )
}

//_________________
void StHbtParticle::setNominalPosSample( float x[mNumberOfPoints],
																				 float y[mNumberOfPoints],
																				 float z[mNumberOfPoints] ) {
  setNominalPosSampleX( x );
  setNominalPosSampleY( y );
  setNominalPosSampleZ( z ); //[mNumberOfPoints]
}

//_________________
void StHbtParticle::setNominalPosSample(TVector3 pos[mNumberOfPoints]) {
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    setNominalPosSampleX( iPoint, pos[iPoint].X() );
    setNominalPosSampleY( iPoint, pos[iPoint].Y() );
    setNominalPosSampleZ( iPoint, pos[iPoint].Z() );
  }
}

//_________________
void StHbtParticle::setTpcV0NegPosSample(TVector3 pos[mNumberOfPoints]) {
  if( !mTpcV0NegPosSampleX ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSample(TVector3 pos[mNumberOfPoints]) : "
	      << "mTpcV0NegPosSampleX instance does not exist" << std::endl;
    return;
  }
  if( !mTpcV0NegPosSampleY ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSample(TVector3 pos[mNumberOfPoints]) : "
	      << "mTpcV0NegPosSampleY instance does not exist" << std::endl;
    return;
  }
  if( !mTpcV0NegPosSampleZ ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSample(TVector3 pos[mNumberOfPoints]) : "
	      << "mTpcV0NegPosSampleZ instance does not exist" << std::endl;
    return;
  }
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    setTpcV0NegPosSampleX( iPoint, pos[iPoint].X() );
    setTpcV0NegPosSampleY( iPoint, pos[iPoint].Y() );
    setTpcV0NegPosSampleZ( iPoint, pos[iPoint].Z() );
  }
}

//_________________
void StHbtParticle::setTpcV0NegPosSampleX(const int& i, const float& val) {
  if( !mTpcV0NegPosSampleX ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSampleX(const int& i, const float& val) : "
	      << "mTpcV0NegPosSampleX instance does not exist" << std::endl;
    return;
  }
  mTpcV0NegPosSampleX[i] = val;
}

//_________________
void StHbtParticle::setTpcV0NegPosSampleY(const int& i, const float& val) {
  if( !mTpcV0NegPosSampleY ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSampleY(const int& i, const float& val) : "
	      << "mTpcV0NegPosSampleY instance does not exist" << std::endl;
    return;
  }
  mTpcV0NegPosSampleY[i] = val;
}

//_________________
void StHbtParticle::setTpcV0NegPosSampleZ(const int& i, const float& val) {
  if( !mTpcV0NegPosSampleZ ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSampleZ(const int& i, const float& val) : "
	      << "mTpcV0NegPosSampleZ instance does not exist" << std::endl;
    return;
  }
  mTpcV0NegPosSampleZ[i] = val;
}

//_________________
void StHbtParticle::setNominalPosSampleX(const int& i, const float& val) {
  if(i<0 || i>=mNumberOfPoints) {
    std::cerr << "void StHbtParticle::setNominalPosSampleX(const int& i, const float& val) : Bad index = " << i
	      << std::endl;
    return;
  }
  mNominalPosSampleX[i] = val;
}

//_________________
void StHbtParticle::setNominalPosSampleY(const int& i, const float& val) {
  if(i<0 || i>=mNumberOfPoints) {
    std::cerr << "void StHbtParticle::setNominalPosSampleY(const int& i, const float& val) : Bad index = " << i
	      << std::endl;
    return;
  }
  mNominalPosSampleY[i] = val;
}

//_________________
void StHbtParticle::setNominalPosSampleZ(const int& i, const float& val) {
  if(i<0 || i>=mNumberOfPoints) {
    std::cerr << "void StHbtParticle::setNominalPosSampleZ(const int& i, const float& val) : Bad index = " << i
	      << std::endl;
    return;
  }
  mNominalPosSampleZ[i] = val;
}

//_________________
void StHbtParticle::setNominalPosSampleX(float x[mNumberOfPoints]) {
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    mNominalPosSampleX[iPoint] = x[iPoint];
  }
}

//_________________
void StHbtParticle::setNominalPosSampleY(float y[mNumberOfPoints]) {
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    mNominalPosSampleY[iPoint] = y[iPoint];
  }
}

//_________________
void StHbtParticle::setNominalPosSampleZ(float z[mNumberOfPoints]) {
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    mNominalPosSampleZ[iPoint] = z[iPoint];
  }
}

//_________________
float StHbtParticle::nominalPosSampleX(const int& point) const {
  if(point<0 || point>=mNumberOfPoints) {
    std::cerr << "float StHbtParticle::nominalPosSampleX : Bad index = "
	      << point << std::endl;
    return 0;
  }
  return mNominalPosSampleX[point];
}

//_________________
float StHbtParticle::nominalPosSampleY(const int& point) const {
  if(point<0 || point>=mNumberOfPoints) {
    std::cerr << "float StHbtParticle::nominalPosSampleY : Bad index = "
	      << point << std::endl;
    return 0;
  }
  return mNominalPosSampleY[point];
}

//_________________
float StHbtParticle::nominalPosSampleZ(const int& point) const {
  if(point<0 || point>=mNumberOfPoints) {
    std::cerr << "float StHbtParticle::nominalPosSampleZ : Bad index = "
	      << point << std::endl;
    return 0;
  }
  return mNominalPosSampleZ[point];
}

//_________________
TVector3 StHbtParticle::nominalPosSample(const int& i) const {
  // Check range
  if(i<0 || i>=mNumberOfPoints) {
    std::cerr << "TVector3 StHbtParticle::nominalPosSample : Bad index = "
	      << i << std::endl;
    return TVector3(0,0,0);
  }
  return TVector3( nominalPosSampleX( i ), nominalPosSampleY( i ), nominalPosSampleZ( i ) );
}

//_________________
void StHbtParticle::setTpcV0NegPosSampleX(float x[mNumberOfPoints]) {
  if( !mTpcV0NegPosSampleX ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSampleX : mTpcV0NegPosSampleX instanse does not exist"
	      << std::endl;
    return;
  }
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    mTpcV0NegPosSampleX[iPoint] = x[iPoint];
  }
}

//_________________
void StHbtParticle::setTpcV0NegPosSampleY(float y[mNumberOfPoints]) {
  if( !mTpcV0NegPosSampleY ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSampleY : mTpcV0NegPosSampleY instanse does not exist"
	      << std::endl;
    return;
  }
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    mTpcV0NegPosSampleY[iPoint] = y[iPoint];
  }
}

//_________________
void StHbtParticle::setTpcV0NegPosSampleZ(float z[mNumberOfPoints]) {
  if( !mTpcV0NegPosSampleZ ) {
    std::cerr << "void StHbtParticle::setTpcV0NegPosSampleZ : mTpcV0NegPosSampleZ instanse does not exist"
	      << std::endl;
    return;
  }
  for(int iPoint=0; iPoint<mNumberOfPoints; iPoint++) {
    mTpcV0NegPosSampleZ[iPoint] = z[iPoint];
  }
}

//_________________
void StHbtParticle::setTpcV0NegPosSample( float x[mNumberOfPoints],
																				  float y[mNumberOfPoints],
																				  float z[mNumberOfPoints] ) {
  setTpcV0NegPosSampleX( x );
  setTpcV0NegPosSampleY( y );
  setTpcV0NegPosSampleZ( z );
}

//_________________
float StHbtParticle::tpcV0NegPosSampleX(const int& point) const {
  if( !mTpcV0NegPosSampleX ) {
    std::cerr << "float StHbtParticle::tpcV0NegPosSampleX : mTpcV0NegPosSampleX instanse does not exist"
	      << std::endl;
    return 0;
  }
  if(point<0 || point>=mNumberOfPoints) {
    std::cerr << "float StHbtParticle::tpcV0NegPosSampleX : Bad index = " << point
	      << std::endl;
    return 0;
  }
  return mTpcV0NegPosSampleX[point];
}

//_________________
float StHbtParticle::tpcV0NegPosSampleY(const int& point) const {
  if( !mTpcV0NegPosSampleY ) {
    std::cerr << "float StHbtParticle::tpcV0NegPosSampleY : mTpcV0NegPosSampleY instanse does not exist"
	      << std::endl;
    return 0;
  }
  if(point<0 || point>=mNumberOfPoints) {
    std::cerr << "float StHbtParticle::tpcV0NegPosSampleY : Bad index = " << point
	      << std::endl;
    return 0;
  }
  return mTpcV0NegPosSampleY[point];
}

//_________________
float StHbtParticle::tpcV0NegPosSampleZ(const int& point) const {
  if( !mTpcV0NegPosSampleZ ) {
    std::cerr << "float StHbtParticle::tpcV0NegPosSampleZ : mTpcV0NegPosSampleZ instanse does not exist"
	      << std::endl;
    return 0;
  }
  if(point<0 || point>=mNumberOfPoints) {
    std::cerr << "float StHbtParticle::tpcV0NegPosSampleZ : Bad index = " << point
	      << std::endl;
    return 0;
  }
  return mTpcV0NegPosSampleZ[point];
}

//_________________
TVector3 StHbtParticle::tpcV0NegPosSample(const int& i) const {
  if( !mTpcV0NegPosSampleX ) {
    std::cerr << "TVector3 StHbtParticle::tpcV0NegPosSample : mTpcV0NegPosSampleX instanse does not exist"
	      << std::endl;
    return TVector3(0,0,0);
  }
  if( !mTpcV0NegPosSampleY ) {
    std::cerr << "TVector3 StHbtParticle::tpcV0NegPosSample : mTpcV0NegPosSampleY instanse does not exist"
	      << std::endl;
    return TVector3(0,0,0);
  }
  if( !mTpcV0NegPosSampleZ ) {
    std::cerr << "TVector3 StHbtParticle::tpcV0NegPosSample : mTpcV0NegPosSampleZ instanse does not exist"
	      << std::endl;
    return TVector3(0,0,0);
  }
  if(i<0 || i>=mNumberOfPoints) {
    std::cerr << "TVector3 StHbtParticle::tpcV0NegPosSample : Bad point = " << i
	      << std::endl;
    return TVector3(0,0,0);
  }
  return TVector3( tpcV0NegPosSampleX( i ),
								   tpcV0NegPosSampleY( i ),
								   tpcV0NegPosSampleZ( i ) );
}

//_________________
void StHbtParticle::setZ(float z[mNumberOfPadrows]) {
  for(int iRow=0; iRow<mNumberOfPadrows; iRow++) {
    mZ[iRow] = z[iRow];
  }
}

//_________________
void StHbtParticle::setU(float u[mNumberOfPadrows]) {
  for(int iRow=0; iRow<mNumberOfPadrows; iRow++) {
    mU[iRow] = u[iRow];
  }
}

//_________________
void StHbtParticle::setSect(int sect[mNumberOfPadrows]) {
  for(int iRow=0; iRow<mNumberOfPadrows; iRow++) {
    mSect[iRow] = sect[iRow];
  }
}

//_________________
void StHbtParticle::setV0NegZ(float z[mNumberOfPadrows]) {
  if( !mV0NegZ ) {
    std::cerr << "void StHbtParticle::setV0NegZ : mV0NegZ instanse does not exist"
	      << std::endl;
    return;
  }
  for(int iRow=0; iRow<mNumberOfPadrows; iRow++) {
    mV0NegZ[iRow] = z[iRow];
  }
}

//_________________
void StHbtParticle::setV0NegU(float u[mNumberOfPadrows]) {
  if( !mV0NegU ) {
    std::cerr << "void StHbtParticle::setV0NegU : mV0NegU instanse does not exist"
	      << std::endl;
    return;
  }
  for(int iRow=0; iRow<mNumberOfPadrows; iRow++) {
    mV0NegU[iRow] = u[iRow];
  }
}

//_________________
void StHbtParticle::setV0NegSect(int sect[mNumberOfPadrows]) {
  if( !mV0NegSect ) {
    std::cerr << "void StHbtParticle::setV0NegSect : mV0NegSect instanse does not exist"
	      << std::endl;
    return;
  }
  for(int iRow=0; iRow<mNumberOfPadrows; iRow++) {
    mV0NegSect[iRow] = sect[iRow];
  }
}

//_________________
float StHbtParticle::tpcV0PosExitPointX() const {
  return (mTpcV0PosExitPointX) ? *mTpcV0PosExitPointX : 0.f;
}

//_________________
float StHbtParticle::tpcV0PosExitPointY() const {
  return (mTpcV0PosExitPointY) ? *mTpcV0PosExitPointY : 0.f;
}

//_________________
float StHbtParticle::tpcV0PosExitPointZ() const {
  return (mTpcV0PosExitPointZ) ? *mTpcV0PosExitPointZ : 0.f;
}

//_________________
float StHbtParticle::tpcV0PosEntrancePointX() const {
  return (mTpcV0PosEntrancePointX) ? *mTpcV0PosEntrancePointX : 0.f;
}

//_________________
float StHbtParticle::tpcV0PosEntrancePointY() const {
  return (mTpcV0PosEntrancePointY) ? *mTpcV0PosEntrancePointY : 0.f;
}

//_________________
float StHbtParticle::tpcV0PosEntrancePointZ() const {
  return (mTpcV0PosEntrancePointZ) ? *mTpcV0PosEntrancePointZ : 0.f;
}

//_________________
float StHbtParticle::tpcV0NegExitPointX() const {
  return (mTpcV0NegExitPointX) ? *mTpcV0NegExitPointX : 0.f;
}

//_________________
float StHbtParticle::tpcV0NegExitPointY() const {
  return (mTpcV0NegExitPointY) ? *mTpcV0NegExitPointY : 0.f;
}

//_________________
float StHbtParticle::tpcV0NegExitPointZ() const {
  return (mTpcV0NegExitPointZ) ? *mTpcV0NegExitPointZ : 0.f;
}

//_________________
float StHbtParticle::tpcV0NegEntrancePointX() const {
  return (mTpcV0NegEntrancePointX) ? *mTpcV0NegEntrancePointX : 0.f;
}

//_________________
float StHbtParticle::tpcV0NegEntrancePointY() const {
  return (mTpcV0NegEntrancePointY) ? *mTpcV0NegEntrancePointY : 0.f;
}

//_________________
float StHbtParticle::tpcV0NegEntrancePointZ() const {
  return (mTpcV0NegEntrancePointZ) ? *mTpcV0NegEntrancePointZ : 0.f;
}

//_________________
float StHbtParticle::secondaryVertexX() const {
  return (mSecondaryVertexX) ? *mSecondaryVertexX : 0.f;
}

//_________________
float StHbtParticle::secondaryVertexY() const {
  return (mSecondaryVertexY) ? *mSecondaryVertexY : 0.f;
}

//_________________
float StHbtParticle::secondaryVertexZ() const {
  return (mSecondaryVertexZ) ? *mSecondaryVertexZ : 0.f;
}

//_________________
void StHbtParticle::setSecondaryVertexX(const float& x) {
  if ( !mSecondaryVertexX ) {
    mSecondaryVertexX = new float;
  }
  *mSecondaryVertexX = x;
}

//_________________
void StHbtParticle::setSecondaryVertexY(const float& y) {
  if ( !mSecondaryVertexY ) {
    mSecondaryVertexY = new float;
  }
  *mSecondaryVertexY = y;
}

//_________________
void StHbtParticle::setSecondaryVertexZ(const float& z) {
  if ( !mSecondaryVertexZ ) {
    mSecondaryVertexZ = new float;
  }
  *mSecondaryVertexZ = z;
}

//_________________
void StHbtParticle::setTpcV0PosExitPointX(const float& val) {
  if( !mTpcV0PosExitPointX ) {
    mTpcV0PosExitPointX = new float;
  }
  *mTpcV0PosExitPointX = val;
}

//_________________
void StHbtParticle::setTpcV0PosExitPointY(const float& val) {
  if( !mTpcV0PosExitPointY ) {
    mTpcV0PosExitPointY = new float;
  }
  *mTpcV0PosExitPointY = val;
}

//_________________
void StHbtParticle::setTpcV0PosExitPointZ(const float& val) {
  if( !mTpcV0PosExitPointZ ) {
    mTpcV0PosExitPointZ = new float;
  }
  *mTpcV0PosExitPointZ = val;
}

//_________________
void StHbtParticle::setTpcV0PosEntrancePointX(const float& val) {
  if ( !mTpcV0PosEntrancePointX ) {
    mTpcV0PosEntrancePointX = new float;
  }
  *mTpcV0PosEntrancePointX = val;
}

//_________________
void StHbtParticle::setTpcV0PosEntrancePointY(const float& val) {
  if ( !mTpcV0PosEntrancePointY ) {
    mTpcV0PosEntrancePointY = new float;
  }
  *mTpcV0PosEntrancePointY = val;
}

//_________________
void StHbtParticle::setTpcV0PosEntrancePointZ(const float& val) {
  if ( !mTpcV0PosEntrancePointZ ) {
    mTpcV0PosEntrancePointZ = new float;
  }
  *mTpcV0PosEntrancePointZ = val;
}

//_________________
void StHbtParticle::setTpcV0NegExitPointX(const float& val) {
  if( !mTpcV0NegExitPointX ) {
    mTpcV0NegExitPointX = new float;
  }
  *mTpcV0NegExitPointX = val;
}

//_________________
void StHbtParticle::setTpcV0NegExitPointY(const float& val) {
  if( !mTpcV0NegExitPointY ) {
    mTpcV0NegExitPointY = new float;
  }
  *mTpcV0NegExitPointY = val;
}

//_________________
void StHbtParticle::setTpcV0NegExitPointZ(const float& val) {
  if( !mTpcV0NegExitPointZ ) {
    mTpcV0NegExitPointZ = new float;
  }
  *mTpcV0NegExitPointZ = val;
}

//_________________
void StHbtParticle::setTpcV0NegEntrancePointX(const float& val) {
  if ( !mTpcV0NegEntrancePointX ) {
    mTpcV0NegEntrancePointX = new float;
  }
  *mTpcV0NegEntrancePointX = val;
}

//_________________
void StHbtParticle::setTpcV0NegEntrancePointY(const float& val) {
  if ( !mTpcV0NegEntrancePointY ) {
    mTpcV0NegEntrancePointY = new float;
  }
  *mTpcV0NegEntrancePointY = val;
}

//_________________
void StHbtParticle::setTpcV0NegEntrancePointZ(const float& val) {
  if ( !mTpcV0NegEntrancePointZ ) {
    mTpcV0NegEntrancePointZ = new float;
  }
  *mTpcV0NegEntrancePointZ = val;
}
