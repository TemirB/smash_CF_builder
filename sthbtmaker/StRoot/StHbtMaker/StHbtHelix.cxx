/**
 * \class StHbtHelix
 * \author Grigory Nigmatkulov, May 07 2018
 *
 * Parametrization of a helix (modification of StHelix). Can also cope
 * with straight tracks, i.e. with zero curvature. This represents only
 * the mathematical model of a helix. See the SCL user guide for more.
 *
 */

/// C++ headers
#if !defined(ST_NO_NUMERIC_LIMITS)
#    include <limits>
#    if !defined(ST_NO_NAMESPACES)
         using std::numeric_limits;
#    endif
#endif

#define FOR_PICO_HELIX

/// C++ headers
#include <float.h>
#include <ostream>

/// PicoDst headers
#include "StHbtHelix.h"
#ifdef _VANILLA_ROOT_
#include "PhysicalConstants.h"
#else
#include "StarClassLibrary/PhysicalConstants.h"
#endif

#ifdef __ROOT__
ClassImpT(StHbtHelix,double)
#endif

const double StHbtHelix::NoSolution = 3.e+33;

//_________________
StHbtHelix::StHbtHelix() : mSingularity(false), mOrigin(0, 0, 0),
			   mDipAngle(0), mCurvature(0), mPhase(0),
			   mH(0), mCosDipAngle(0), mSinDipAngle(0),
			   mCosPhase(0), mSinPhase(0) {
  /*no-op*/
}

//_________________
StHbtHelix::StHbtHelix(double c, double d, double phase,
		       const TVector3& o, int h) {
  setParameters(c, d, phase, o, h);
}

//_________________
StHbtHelix::StHbtHelix(const StHbtHelix &h) {
  mSingularity = h.mSingularity;
  mOrigin = h.mOrigin;
  mDipAngle = h.mDipAngle;
  mCurvature = h.mCurvature;
  mPhase = h.mPhase;
  mH = h.mH;
  mCosDipAngle = h.mCosDipAngle;
  mSinDipAngle = h.mSinDipAngle;
  mCosPhase = h.mCosPhase;
  mSinPhase = h.mSinPhase;
}

//_________________
StHbtHelix::~StHbtHelix() { /* noop */ };

//_________________
void StHbtHelix::setParameters(double c, double dip, double phase,
			       const TVector3& o, int h) {

  //
  //  The order in which the parameters are set is important
  //  since setCurvature might have to adjust the others.
  //
  mH = (h>=0) ? 1 : -1;    // Default is: positive particle
                           //             positive field
  mOrigin   = o;
  setDipAngle(dip);
  setPhase(phase);

  //
  // Check for singularity and correct for negative curvature.
  // May change mH and mPhase. Must therefore be set last.
  //
  setCurvature(c);

  //
  // For the case B=0, h is ill defined. In the following we
  // always assume h = +1. Since phase = psi - h * pi/2
  // we have to correct the phase in case h = -1.
  // This assumes that the user uses the same h for phase
  // as the one he passed to the constructor.
  //
  if (mSingularity && mH == -1) {
    mH = +1;
    setPhase(mPhase-M_PI);
  }
}

//_________________
void StHbtHelix::setCurvature(double val) {

  if (val < 0) {
    mCurvature = -val;
    mH = -mH;
    setPhase( mPhase+M_PI );
  }
  else {
    mCurvature = val;
  }

#ifndef ST_NO_NUMERIC_LIMITS
  if ( ::fabs(mCurvature) <= numeric_limits<double>::epsilon() ) {
#else
  if ( ::fabs(mCurvature) <= static_cast<double>(0) ) {
#endif
    mSingularity = true;  /// straight line
  }
  else {
    mSingularity = false; /// curved
  }
}

//_________________
void StHbtHelix::setPhase(double val) {

  mPhase       = val;
  mCosPhase    = cos(mPhase);
  mSinPhase    = sin(mPhase);
  if ( ::fabs(mPhase) > M_PI) {
    mPhase = atan2(mSinPhase, mCosPhase);  // force range [-pi,pi]
  }
}

//_________________
void StHbtHelix::setDipAngle(double val) {

  mDipAngle    = val;
  mCosDipAngle = cos(mDipAngle);
  mSinDipAngle = sin(mDipAngle);
}

//_________________
double StHbtHelix::xcenter() const {

  if (mSingularity) {
    return 0;
  }
  else {
    return mOrigin.x()-mCosPhase/mCurvature;
  }
}

//_________________
double StHbtHelix::ycenter() const {
  if (mSingularity) {
    return 0;
  }
  else {
    return mOrigin.y()-mSinPhase/mCurvature;
  }
}

//_________________
double StHbtHelix::fudgePathLength(const TVector3& p) const {

  double s;
  double dx = p.x()-mOrigin.x();
  double dy = p.y()-mOrigin.y();

  if (mSingularity) {
    s = (dy*mCosPhase - dx*mSinPhase)/mCosDipAngle;
  }
  else {
    s = atan2(dy*mCosPhase - dx*mSinPhase,
	      1/mCurvature + dx*mCosPhase+dy*mSinPhase)/
      (mH*mCurvature*mCosDipAngle);
  }
  return s;
}

//_________________
double StHbtHelix::distance(const TVector3& p, bool scanPeriods) const {
  return ( this->at( pathLength(p,scanPeriods) )-p ).Mag();
}

//_________________
double StHbtHelix::pathLength(const TVector3& p, bool scanPeriods) const {

  //
  //  Returns the path length at the distance of closest
  //  approach between the helix and point p.
  //  For the case of B=0 (straight line) the path length
  //  can be calculated analytically. For B>0 there is
  //  unfortunately no easy solution to the problem.
  //  Here we use the Newton method to find the root of the
  //  referring equation. The 'fudgePathLength' serves
  //  as a starting value.
  //

  double s;
  double dx = p.x()-mOrigin.x();
  double dy = p.y()-mOrigin.y();
  double dz = p.z()-mOrigin.z();

  if (mSingularity) {
    s = mCosDipAngle*(mCosPhase*dy-mSinPhase*dx) +
      mSinDipAngle*dz;
  }
  else {
#ifndef ST_NO_NUMERIC_LIMITS
    {
      using namespace units;
#endif
      const double MaxPrecisionNeeded = micrometer;
      const int    MaxIterations      = 100;

      //
      // The math is taken from Maple with C(expr,optimized) and
      // some hand-editing. It is not very nice but efficient.
      //
      double t34 = mCurvature*mCosDipAngle*mCosDipAngle;
      double t41 = mSinDipAngle*mSinDipAngle;
      double t6, t7, t11, t12, t19;

      //
      // Get a first guess by using the dca in 2D. Since
      // in some extreme cases we might be off by n periods
      // we add (subtract) periods in case we get any closer.
      //
      s = fudgePathLength(p);

      if (scanPeriods) {

	double ds = period();
	int    j;
	int jmin = 0;
	double d;
	double dmin = ( at(s) - p).Mag() ;

	for(j=1; j<MaxIterations; j++) {
	  d = ( at(s+j*ds) - p ).Mag();
	  if ( d  < dmin) {
	    dmin = d;
	    jmin = j;
	  }
	  else {
	    break;
	  }
	} //for(j=1; j<MaxIterations; j++)

	for(j=-1; -j<MaxIterations; j--) {
	  d = ( at(s+j*ds ) - p ).Mag() ;
	  if ( d < dmin) {
	    dmin = d;
	    jmin = j;
	  }
	  else {
	    break;
	  }
	} //for(j=-1; -j<MaxIterations; j--)

	if (jmin) {
	  s += jmin*ds;
	}
      } //if (scanPeriods)

      //
      // Newtons method:
      // Stops after MaxIterations iterations or if the required
      // precision is obtained. Whatever comes first.
      //
      double sOld = s;
      for (int i=0; i<MaxIterations; i++) {
	t6  = mPhase+s*mH*mCurvature*mCosDipAngle;
	t7  = cos(t6);
	t11 = dx-(1/mCurvature)*(t7-mCosPhase);
	t12 = sin(t6);
	t19 = dy-(1/mCurvature)*(t12-mSinPhase);
	s  -= (t11*t12*mH*mCosDipAngle-t19*t7*mH*mCosDipAngle -
	       (dz-s*mSinDipAngle)*mSinDipAngle)/
	  (t12*t12*mCosDipAngle*mCosDipAngle+t11*t7*t34 +
	   t7*t7*mCosDipAngle*mCosDipAngle +
	   t19*t12*t34+t41);
	if (fabs(sOld-s) < MaxPrecisionNeeded) break;
	sOld = s;
      } //for (int i=0; i<MaxIterations; i++)
#ifndef ST_NO_NUMERIC_LIMITS
    }
#endif
  } //else
  return s;
}

//_________________
double StHbtHelix::period() const {
  if (mSingularity) {
#ifndef ST_NO_NUMERIC_LIMITS
    return numeric_limits<double>::max();
#else
    return DBL_MAX;
#endif
  }
  else {
    return fabs(2*M_PI/(mH*mCurvature*mCosDipAngle));
  }
}

//_________________
pair<double, double> StHbtHelix::pathLength(double r) const {

  pair<double,double> value;
  pair<double,double> VALUE(999999999.,999999999.);
  //
  // The math is taken from Maple with C(expr,optimized) and
  // some hand-editing. It is not very nice but efficient.
  // 'first' is the smallest of the two solutions (may be negative)
  // 'second' is the other.
  //
  if (mSingularity) {
    double t1 = mCosDipAngle*(mOrigin.x()*mSinPhase-mOrigin.y()*mCosPhase);
    double t12 = mOrigin.y()*mOrigin.y();
    double t13 = mCosPhase*mCosPhase;
    double t15 = r*r;
    double t16 = mOrigin.x()*mOrigin.x();
    double t20 = -mCosDipAngle*mCosDipAngle*(2.0*mOrigin.x()*mSinPhase*mOrigin.y()*mCosPhase +
					       t12-t12*t13-t15+t13*t16);
    if (t20<0.) {
      return VALUE;
    }
    t20 = ::sqrt(t20);
    value.first  = (t1-t20)/(mCosDipAngle*mCosDipAngle);
    value.second = (t1+t20)/(mCosDipAngle*mCosDipAngle);
  }
  else {
    double t1 = mOrigin.y()*mCurvature;
    double t2 = mSinPhase;
    double t3 = mCurvature*mCurvature;
    double t4 = mOrigin.y()*t2;
    double t5 = mCosPhase;
    double t6 = mOrigin.x()*t5;
    double t8 = mOrigin.x()*mOrigin.x();
    double t11 = mOrigin.y()*mOrigin.y();
    double t14 = r*r;
    double t15 = t14*mCurvature;
    double t17 = t8*t8;
    double t19 = t11*t11;
    double t21 = t11*t3;
    double t23 = t5*t5;
    double t32 = t14*t14;
    double t35 = t14*t3;
    double t38 = 8.0*t4*t6 - 4.0*t1*t2*t8 - 4.0*t11*mCurvature*t6 +
      4.0*t15*t6 + t17*t3 + t19*t3 + 2.0*t21*t8 + 4.0*t8*t23 -
      4.0*t8*mOrigin.x()*mCurvature*t5 - 4.0*t11*t23 -
      4.0*t11*mOrigin.y()*mCurvature*t2 + 4.0*t11 - 4.0*t14 +
      t32*t3 + 4.0*t15*t4 - 2.0*t35*t11 - 2.0*t35*t8;
    double t40 = (-t3*t38);
    if (t40<0.) {
      return VALUE;
    }
    t40 = ::sqrt(t40);

    double t43 = mOrigin.x()*mCurvature;
    double t45 = 2.0*t5 - t35 + t21 + 2.0 - 2.0*t1*t2 -2.0*t43 - 2.0*t43*t5 + t8*t3;
    double t46 = mH*mCosDipAngle*mCurvature;

    value.first = (-mPhase + 2.0*atan((-2.0*t1 + 2.0*t2 + t40)/t45))/t46;
    value.second = -(mPhase + 2.0*atan((2.0*t1 - 2.0*t2 + t40)/t45))/t46;

    //
    //   Solution can be off by +/- one period, select smallest
    //
    double p = period();

    if ( ! std::isnan(value.first) ) {
      if ( ::fabs(value.first-p) < ::fabs(value.first) ) {
	value.first = value.first-p;
      }
      else if ( ::fabs(value.first+p) < ::fabs(value.first) ) {
	value.first = value.first+p;
      }
    } //if ( ! std::isnan(value.first) )

    if (! std::isnan(value.second)) {
      if ( ::fabs(value.second-p) < ::fabs(value.second) ) {
	value.second = value.second-p;
      }
      else if ( ::fabs(value.second+p) < ::fabs(value.second) ) {
	value.second = value.second+p;
      }
    } //if (! std::isnan(value.second))
  } //else

  if (value.first > value.second) {
    swap(value.first,value.second);
  }

  return(value);
}

//_________________
pair<double, double> StHbtHelix::pathLength(double r, double x, double y) {
  double x0 = mOrigin.x();
  double y0 = mOrigin.y();
  mOrigin.SetX(x0-x);
  mOrigin.SetY(y0-y);
  pair<double, double> result = this->pathLength(r);
  mOrigin.SetX(x0);
  mOrigin.SetY(y0);
  return result;
}

//________________
double StHbtHelix::pathLength(const TVector3& r,
			      const TVector3& n) const {
  //
  // Vector 'r' defines the position of the center and
  // vector 'n' the normal vector of the plane.
  // For a straight line there is a simple analytical
  // solution. For curvatures > 0 the root is determined
  // by Newton method. In case no valid s can be found
  // the max. largest value for s is returned.
  //
  double s;

  if (mSingularity) {
    double t = n.z()*mSinDipAngle +
      n.y()*mCosDipAngle*mCosPhase -
      n.x()*mCosDipAngle*mSinPhase;
    if (t == 0) {
      s = NoSolution;
    }
    else {
      s = ((r - mOrigin)*n)/t;
    }
  }
  else {
    const double MaxPrecisionNeeded = micrometer;
    const int    MaxIterations      = 20;

    double A = mCurvature*((mOrigin - r)*n) -
      n.x()*mCosPhase -
      n.y()*mSinPhase;
    double t = mH*mCurvature*mCosDipAngle;
    double u = n.z()*mCurvature*mSinDipAngle;

    double a, f, fp;
    double sOld = s = 0;
    // Next line is commented to prevent compiler warnings
    // double shiftOld = 0;
    double shift;
    //  (cos(angMax)-1)/angMax = 0.1
    const double angMax = 0.21;
    double deltas = fabs(angMax/(mCurvature*mCosDipAngle));
    //  dampingFactor = exp(-0.5);
    //	double dampingFactor = 0.60653;
    int i;

    for (i=0; i<MaxIterations; i++) {
      a  = t*s+mPhase;
      double sina = sin(a);
      double cosa = cos(a);
      f = A + n.x()*cosa + n.y()*sina +	u*s;
      fp = -n.x()*sina*t + n.y()*cosa*t + u;

      if ( fabs(fp)*deltas <= fabs(f) ) { //too big step
	int sgn = 1;
	if (fp<0.) sgn = -sgn;
	if (f <0.) sgn = -sgn;
	shift = sgn*deltas;
	if (shift<0) shift*=0.9;  // don't get stuck shifting +/-deltas
      }
      else {
	       shift = f/fp;
      }
      s -= shift;
      // Next line is commented to prevent compiler warnings
      //shiftOld = shift;
      if ( ::fabs(sOld-s) < MaxPrecisionNeeded ) {
	       break;
      }
      sOld = s;
    } //for (i=0; i<MaxIterations; i++)

    if (i == MaxIterations) {
      return NoSolution;
    }
  } //else
  return s;
}

//_________________
pair<double, double> StHbtHelix::pathLength(const StHbtHelix& h, double minStepSize,
					     double minRange) const {
  //
  //	Cannot handle case where one is a helix
  //  and the other one is a straight line.
  //
  if (mSingularity != h.mSingularity) {
    return pair<double, double>(NoSolution, NoSolution);
  }

  double s1, s2;

  if (mSingularity) {
    //
    //  Analytic solution
    //
    TVector3 dv = h.mOrigin - mOrigin;
    TVector3 a(-mCosDipAngle*mSinPhase,
	       mCosDipAngle*mCosPhase,
	       mSinDipAngle);
    TVector3 b(-h.mCosDipAngle*h.mSinPhase,
	       h.mCosDipAngle*h.mCosPhase,
	       h.mSinDipAngle);
    double ab = a*b;
    double g  = dv*a;
    double k  = dv*b;
    s2 = (k-ab*g)/(ab*ab-1.);
    s1 = g+s2*ab;
    return pair<double, double>(s1, s2);
  } //if (mSingularity)
  else {
    //
    //  First step: get dca in the xy-plane as start value
    //
    double dx = h.xcenter() - xcenter();
    double dy = h.ycenter() - ycenter();
    double dd = ::sqrt(dx*dx + dy*dy);
    double r1 = 1/curvature();
    double r2 = 1/h.curvature();

    double cosAlpha = (r1*r1 + dd*dd - r2*r2)/(2*r1*dd);

    double s;
    double x, y;
    if ( ::fabs(cosAlpha) < 1) {           // two solutions
      double sinAlpha = sin(acos(cosAlpha));
      x = xcenter() + r1*(cosAlpha*dx - sinAlpha*dy)/dd;
      y = ycenter() + r1*(sinAlpha*dx + cosAlpha*dy)/dd;
      s = pathLength(x, y);
      x = xcenter() + r1*(cosAlpha*dx + sinAlpha*dy)/dd;
      y = ycenter() + r1*(cosAlpha*dy - sinAlpha*dx)/dd;
      double a = pathLength(x, y);
      if ( h.distance(at(a)) < h.distance(at(s)) ) {
	s = a;
      }
    } //if ( ::fabs(cosAlpha) < 1)
    else {                              // no intersection (or exactly one)
      int rsign = ((r2-r1) > dd ? -1 : 1); // set -1 when *this* helix is
      // completely contained in the other
      x = xcenter() + rsign*r1*dx/dd;
      y = ycenter() + rsign*r1*dy/dd;
      s = pathLength(x, y);
    } //else

    //
    //   Second step: scan in decreasing intervals around seed 's'
    //   minRange and minStepSize are passed as arguments to the method.
    //   They have default values defined in the header file.
    //
    double dmin              = h.distance(at(s));
    double range             = max(2*dmin, minRange);
    double ds                = range/10;
    double slast=-999999, ss, d;
    s1 = s - range/2.;
    s2 = s + range/2.;

    while (ds > minStepSize) {

      for ( ss=s1; ss<s2+ds; ss+=ds ) {
	d = h.distance(at(ss));
	if (d < dmin) {
	  dmin = d;
	  s = ss;
	}
	slast = ss;
      } //for ( ss=s1; ss<s2+ds; ss+=ds )

      //
      //  In the rare cases where the minimum is at the
      //  the border of the current range we shift the range
      //  and start all over, i.e we do not decrease 'ds'.
      //  Else we decrease the search intervall around the
      //  current minimum and redo the scan in smaller steps.
      //
      if (s == s1) {
	d = 0.8*(s2-s1);
	s1 -= d;
	s2 -= d;
      }
      else if (s == slast) {
	d = 0.8*(s2-s1);
	s1 += d;
	s2 += d;
      }
      else {
	s1 = s-ds;
	s2 = s+ds;
	ds /= 10;
      }
    } //while (ds > minStepSize)
    return pair<double, double>(s, h.pathLength(at(s)));
  } //else
}

//_________________
void StHbtHelix::moveOrigin(double s) {

  if (mSingularity) {
    mOrigin = at(s);
  }
  else {
    TVector3 newOrigin = at(s);
    double newPhase = atan2(newOrigin.y() - ycenter(),
			      newOrigin.x() - xcenter());
    mOrigin = newOrigin;
    setPhase(newPhase);
  }
}

//_________________
int operator== (const StHbtHelix& a, const StHbtHelix& b) {

  //
  // Checks for numerical identity only !
  //
  return ( a.origin()    == b.origin()    &&
	   a.dipAngle()  == b.dipAngle()  &&
	   a.curvature() == b.curvature() &&
	   a.phase()     == b.phase()     &&
	   a.h()         == b.h() );
}

//_________________
int operator!= (const StHbtHelix& a, const StHbtHelix& b) {
  return !(a == b);
}

//_________________
std::ostream& operator<<(std::ostream& os, const StHbtHelix& h) {
  return os << '('
	    << "curvature = "  << h.curvature() << ", "
	    << "dip angle = "  << h.dipAngle()  << ", "
	    << "phase = "      << h.phase()     << ", "
	    << "h = "          << h.h()         << ", "
	    << "origin = "     << h.origin().X()
	    << " , " << h.origin().Y() << " , " << h.origin().Z() << " "
	    << ')';
}
