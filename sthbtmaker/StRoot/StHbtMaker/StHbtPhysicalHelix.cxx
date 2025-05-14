/**
 * \class StHbtPhysicalHelix
 * \author Grigory Nigmatkulov, May 07 2018
 *
 * Parametrization of a physical helix (modification of StPhysicalHelix).
 *
 */

/// C++ headers
#include <math.h>

/// PicoDst headers
#include "StHbtHelix.h"
#include "StHbtPhysicalHelix.h"
#ifdef _VANILLA_ROOT_
#include "PhysicalConstants.h"
#include "SystemOfUnits.h"
#else
#include "StarClassLibrary/PhysicalConstants.h"
#include "StarClassLibrary/SystemOfUnits.h"
#endif

#ifdef __ROOT__
ClassImpT(StHbtPhysicalHelix, Double_t)
#endif

//_________________
StHbtPhysicalHelix::StHbtPhysicalHelix(){
  /* no-op */
}

//_________________
StHbtPhysicalHelix::~StHbtPhysicalHelix() {
  /* no-op */
}

//_________________
StHbtPhysicalHelix::StHbtPhysicalHelix(const TVector3& p,
				       const TVector3& o,
				       double B, double q) {
  mH = (q*B <= 0) ? 1 : -1;
  if(p.y() == 0 && p.x() == 0) {
    setPhase((M_PI/4)*(1-2.*mH));
  }
  else {
    setPhase(atan2(p.y(),p.x())-mH*M_PI/2);
  }
  setDipAngle(atan2(p.z(),p.Perp()));
  mOrigin = o;

#ifndef ST_NO_NAMESPACES
  {
    using namespace units;
#endif
    setCurvature( ::fabs( (c_light*nanosecond/meter*q*B/tesla) /
			  ( p.Mag()/GeV*mCosDipAngle) / meter) );
#ifndef ST_NO_NAMESPACES
  }
#endif
}

//_________________
StHbtPhysicalHelix::StHbtPhysicalHelix(double c, double d,
				       double phase, const TVector3& o,
				       int h) : StHbtHelix(c, d, phase, o, h) {
  /* no-op */
}

//_________________
TVector3 StHbtPhysicalHelix::momentum(double B) const {

  if (mSingularity) {
    return(TVector3(0,0,0));
  }
  else {
#ifndef ST_NO_NAMESPACES
    {
      using namespace units;
#endif
      double pt = GeV*fabs(c_light*nanosecond/meter*B/tesla)/(fabs(mCurvature)*meter);

      return ( TVector3( pt*cos(mPhase+mH*M_PI/2),   // pos part pos field
			 pt*sin(mPhase+mH*M_PI/2),
			 pt*tan(mDipAngle) ) );
#ifndef ST_NO_NAMESPACES
    }
#endif
  } //else
}

//_________________
TVector3 StHbtPhysicalHelix::momentumAt(double S, double B) const {
  /// Obtain phase-shifted momentum from phase-shift of origin
  StHbtPhysicalHelix tmp(*this);
  tmp.moveOrigin(S);
  return tmp.momentum(B);
}

//_________________
int StHbtPhysicalHelix::charge(double B) const {
  return (B > 0 ? -mH : mH);
}

//_________________
double StHbtPhysicalHelix::geometricSignedDistance(double x, double y) {
  // Geometric signed distance
  double thePath = this->pathLength(x,y);
  TVector3 DCA2dPosition = this->at(thePath);
  DCA2dPosition.SetZ(0);
  TVector3 position(x,y,0);
  TVector3 DCAVec = (DCA2dPosition-position);
  TVector3 momVec;
  /// Deal with straight tracks
  if (this->mSingularity) {
    momVec = this->at(1)- this->at(0);
    momVec.SetZ(0);
  }
  else {
    momVec = this->momentumAt(thePath,1./tesla); // Don't care about Bmag.  Helicity is what matters.
    momVec.SetZ(0);
  }

  double cross = DCAVec.x()*momVec.y() - DCAVec.y()*momVec.x();
  double theSign = (cross>=0) ? 1. : -1.;
  return theSign*DCAVec.Perp();
}

//_________________
double StHbtPhysicalHelix::curvatureSignedDistance(double x, double y) {
  /// Protect against mH = 0 or zero field
  if (this->mSingularity || abs(this->mH)<=0) {
    return (this->geometricSignedDistance(x,y));
  }
  else {
    return (this->geometricSignedDistance(x,y))/(this->mH);
  }
}

//_________________
double StHbtPhysicalHelix::geometricSignedDistance(const TVector3& pos) {
  double sdca2d = this->geometricSignedDistance(pos.x(),pos.y());
  double theSign = (sdca2d>=0) ? 1. : -1.;
  return (this->distance(pos))*theSign;
}

//_________________
double StHbtPhysicalHelix::curvatureSignedDistance(const TVector3& pos) {
  double sdca2d = this->curvatureSignedDistance(pos.x(),pos.y());
  double theSign = (sdca2d>=0) ? 1. : -1.;
  return (this->distance(pos))*theSign;
}
