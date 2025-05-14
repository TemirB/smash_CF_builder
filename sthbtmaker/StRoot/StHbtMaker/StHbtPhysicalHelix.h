/**
 * \class StHbtPhysicalHelix
 * \author Grigory Nigmatkulov, May 07 2018
 *
 * Parametrization of a physical helix (modification of StPhysicalHelix).
 *
 */

#ifndef StHbtPhysicalHelix_h
#define StHbtPhysicalHelix_h

// ROOT headers
#include "TVector3.h"

// PicoDst headers
#include "StHbtHelix.h"

//_________________
class StHbtPhysicalHelix : public StHbtHelix {

 public:
  /// Default constructor
  StHbtPhysicalHelix();
  /// Constructor with momentum, origin, signed Magnetic Field
  /// and Charge of particle (+/- 1)
  StHbtPhysicalHelix(const TVector3&,
		     const TVector3&,
		     double, double);
  /// Constructor with Curvature, dip angle, phase, origin, h
  StHbtPhysicalHelix(double, double, double,
		     const TVector3&, Int_t h=-1);
  /// Destructor
  ~StHbtPhysicalHelix();

  /// Requires: signed Magnetic Field
  TVector3 momentum(double) const;             // returns the momentum at origin
  TVector3 momentumAt(double, double) const;   // returns momemtum at S
  Int_t charge(double) const;                  // returns charge of particle
  /// 2d DCA to x,y point signed relative to curvature
  double curvatureSignedDistance(double x, double y) ;
  /// 2d DCA to x,y point signed relative to rotation
  double geometricSignedDistance(double x, double y) ;
  /// 3d DCA to 3d point signed relative to curvature
  double curvatureSignedDistance(const TVector3&) ;
  /// 3d DCA to 3d point signed relative to rotation
  double geometricSignedDistance(const TVector3&) ;

#ifdef __ROOT__
  ClassDef(StHbtPhysicalHelix,1)
#endif
};

#endif
