/**
 * \class StHbtPair
 * \brief Holds information about pair of particles
 *
 * The class describes a pair of StHbtParticle instances and allows various
 * relative 4-momentum quantities, such as, qInv, qOut, qSide and qLong in different
 * frames (CMS - center of mass of the experiment, LCMS - longitudinally co-moving
 * system, PF - pair frame), as well as, sum of 4-momenta, such as, invariant mass,
 * kT, mT and so on.
 * It also provides esitmations for two-particle effects, for instance, track-merging
 * and track-splitiing effects.
 */

#ifndef StHbtPair_h
#define StHbtPair_h

// C++ headers
#include <utility>
#include <vector>

// StHbtMaker headers
#include "StHbtParticle.h"
#include "StHbtTypes.h"

// ROOT headers
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TMath.h"

//_________________
class StHbtPair {

 public:
  /// Default constructor
  StHbtPair();
  /// Constructor with particles
  StHbtPair(StHbtParticle*, StHbtParticle*);
  /// Copy constructor
  StHbtPair(const StHbtPair& copy);
  /// Copy constructor
  StHbtPair& operator=(const StHbtPair& copy);
  /// Default destructor
  virtual ~StHbtPair();

  //
  // Getters
  //

  /// First particle from a pair
  StHbtParticle* track1() const                 { return mTrack1; }
  /// Second particle from a pair
  StHbtParticle* track2() const                 { return mTrack2; }

  /// Relative four-momentum
  TLorentzVector fourMomentumDiff() const
  { return ( mTrack1->fourMomentum() - mTrack2->fourMomentum() ); }
  /// Sum of four-momenta
  TLorentzVector fourMomentumSum() const
  { return ( mTrack1->fourMomentum() + mTrack2->fourMomentum() ); }
  /// Invariant relative momentum of the pair
  double qInv() const                           { return (-1.)*fourMomentumDiff().M(); }
  /// Pair transverse momentum of the pair
  double pT() const                             { return p().Perp(); }
  /// Half of pair transverse momentum of the pair
  double kT()   const                           { return 0.5 * pT(); }
  /// Invariant mass of the pair
  double mInv() const                           { return fourMomentumSum().M(); }
  /// Three-momentum of the pair
  TVector3 momentum() const                     { return fourMomentumSum().Vect(); }
  /// Three-momentum of the pair
  TVector3 p() const                            { return momentum(); }
  /// Px of the pair
  double px() const                             { return p().X(); }
  /// Py of the pair
  double py() const                             { return p().Y(); }
  /// Pz of the pair
  double pz() const                             { return p().Z(); }
  /// Momentum of the pair
  double ptot() const                           { return p().Mag(); }
  /// Squared momentum of the pair
  double ptot2() const                          { return p().Mag2(); }
  /// Energy of the pair
  double energy() const                         { return fourMomentumSum().Energy(); }

  /// Rapidity of the pair
  double rap() const                            { return fourMomentumSum().Rapidity(); }
  /// Rapidity of the pair
  double rapidity() const                       { return rap(); }
  /// Pair emission angle
  double emissionAngle() const;
  /// Pseudorapidity of the pair
  double eta() const                            { return fourMomentumSum().Eta(); }
  /// Pseudorapidity of the pair
  double pseudoRapidity() const                 { return eta(); }
  /// Azimuthal angle of the pair
  double phi() const                            { return fourMomentumSum().Phi(); }
  /// Delta phi between two particles
  double deltaPhi() const                       { return ( mTrack1->phi() - mTrack2->phi() ); }
  /// Delta eta between two particles
  double deltaEta() const                       { return ( mTrack1->eta() - mTrack2->eta() ); }
  /// Sqrt(dEta^2+dPhi^2)
  double rValue() const
  { return TMath::Sqrt( deltaEta()*deltaEta() + deltaPhi()*deltaPhi() ); }

  /// Bertsch-Pratt side momentum component in Pair Frame
  double qSidePf() const;
  /// Bertsch-Pratt out momentum component in Pair Frame
  double qOutPf() const;
  /// Bertsch-Pratt long momentum component in Pair Frame
  double qLongPf() const;

  /// Bertsch-Pratt side momentum component in Local CMS (longitudinally comoving) frame
  double qSideCMS() const;
  /// Bertsch-Pratt out momentum component in Local CMS (longitudinally comoving) frame
  double qOutCMS() const;
  /// Bertsch-Pratt long momentum component in Local CMS (longitudinally comoving) frame
  double qLongCMS() const;

  /// Bertsch-Pratt side momentum component in Local CMS (longitudinally comoving) frame
  /// for non-identical pairs
  double dKSide() const     { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKSide; }
  /// Bertsch-Pratt out momentum component in Local CMS (longitudinally comoving) frame
  /// for non-identical pairs
  double dKOut() const      { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKOut; }
  /// Bertsch-Pratt long momentum component in Local CMS (longitudinally comoving) frame
  /// for non-identical pairs
  double dKLong() const     { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKLong; }

  /// Bertsch-Pratt side momentum component in a longitudinally boosted frame
  /// the argument is the beta of the longitudinal boost (default is 0.0, meaning lab frame)
  double qSideBf(double beta=0.0) const;
  /// Bertsch-Pratt side momentum component in a longitudinally boosted frame
  /// the argument is the beta of the longitudinal boost (default is 0.0, meaning lab frame)
  double qOutBf(double beta=0.0) const;
  /// Bertsch-Pratt side momentum component in a longitudinally boosted frame
  /// the argument is the beta of the longitudinal boost (default is 0.0, meaning lab frame)
  double qLongBf(double beta=0.0) const;

  /// Yano-Koonin-Podgoretskii Parametrisation in
  /// source rest frame (usually lab frame)
  void qYKPCMS(double& qP, double& qT, double& q0) const ;
  /// Yano-Koonin-Podgoretskii Parametrisation in
  /// longitudinal co-moving frame
  void qYKPLCMS(double& qP, double& qT, double& q0) const ;
  /// Yano-Koonin-Podgoretskii Parametrisation in
  /// pair rest frame
  void qYKPPF(double& qP, double& qT, double& q0) const ;

  /// Track-splitting quantity
  double quality() const;
  /// Track-splitting quantity
  double splittingLevel() const { return quality(); }

  // The following two methods calculate the "nominal" separation of the tracks
  // at the inner field cage (EntranceSeparation) and when they exit the TPC,
  // which may be at the outer field cage, or at the endcaps.
  // "nominal" means that the tracks are assumed to start at (0,0,0).  Making this
  // assumption is important for the Event Mixing -- it is not a mistake.

  /// Distance between particles at TPC exit points
  double nominalTpcExitSeparation() const;
  /// Distance between particles at TPC entrance points
  double nominalTpcEntranceSeparation() const;
  /// Average distance between particles within TPC
  double nominalTpcAverageSeparation() const;

  // Adopted calculation of Entrance/Exit/Average TPC separation to V0 daughters

  double tpcExitSeparationTrackV0Pos() const
  { return ( mTrack1->nominalTpcExitPoint() - mTrack2->tpcV0PosExitPoint() ).Mag(); }
  double tpcEntranceSeparationTrackV0Pos() const
  { return ( mTrack1->nominalTpcEntrancePoint() - mTrack2->tpcV0PosEntrancePoint() ).Mag(); }
  double tpcAverageSeparationTrackV0Pos() const;

  double tpcExitSeparationTrackV0Neg() const
  { return ( mTrack1->nominalTpcExitPoint() - mTrack2->tpcV0NegExitPoint() ).Mag(); }
  double tpcEntranceSeparationTrackV0Neg() const
  { return ( mTrack1->nominalTpcEntrancePoint() - mTrack2->tpcV0NegEntrancePoint() ).Mag(); }
  double tpcAverageSeparationTrackV0Neg() const;

  double tpcExitSeparationV0PosV0Pos() const
  { return ( mTrack1->tpcV0PosExitPoint() - mTrack2->tpcV0PosExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0PosV0Pos() const
  { return ( mTrack1->tpcV0PosEntrancePoint() - mTrack2->tpcV0PosEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0PosV0Pos() const;

  double tpcExitSeparationV0PosV0Neg() const
  { return ( mTrack1->tpcV0PosExitPoint() - mTrack2->tpcV0NegExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0PosV0Neg() const
  { return ( mTrack1->tpcV0PosEntrancePoint() - mTrack2->tpcV0NegEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0PosV0Neg() const;

  double tpcExitSeparationV0NegV0Pos() const
  { return (  mTrack1->tpcV0NegExitPoint() - mTrack2->tpcV0PosExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0NegV0Pos() const
  { return ( mTrack1->tpcV0NegEntrancePoint() - mTrack2->tpcV0PosEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0NegV0Pos() const;

  double tpcExitSeparationV0NegV0Neg() const
  { return ( mTrack1->tpcV0NegExitPoint() - mTrack2->tpcV0NegExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0NegV0Neg() const
  { return ( mTrack1->tpcV0NegEntrancePoint() - mTrack2->tpcV0NegEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0NegV0Neg() const;

  /// Invariant total momentum
  double pInv() const;
  /// k^* of non-identical particles
  double kStar() const           { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mKStarCalc; }
  /// k^* of non-identical particles when one of particles was rotated
  double kStarFlipped() const;
  double cvk() const             { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mCVK; }
  double cvkFlipped() const;
  /// Invariant momentum of a pair with the first particle
  /// flipped in xy-plane (px,py,pz) -> (-px,-py,pz)
  double qInvFlippedXY() const;
  /// Invariant momentum of a pair with one of the particles
  /// flipped in xy-plane (px,py,pz) -> (-px,-py,pz)
  double qInvRandomFlippedXY() const;
  /// Invariant momentum of a pair with the first particle
  /// rotated to opposite-hemisphere (px,py,pz) -> (-px,-py,-pz)
  double qInvFlippedXYZ() const;
  /// Invariant momentum of a pair with one of the particles
  /// rotated to opposite-hemisphere (px,py,pz) -> (-px,-py,-pz)
  double qInvRandomFlippedXYZ() const;

  /// Opening angle between two particles
  double openingAngle() const
  { return TMath::RadToDeg() * ( mTrack1->p().Angle( mTrack2->p() ) ); }

  /// Side component of k^*
  double kStarSide() const       { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKSide; }
  /// Out component of k^*
  double kStarOut() const        { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKOut; }
  /// Long component of k^*
  double kStarLong() const       { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKLong; }

  double electronPairProbability() const
  { return (mTrack1->track()->pidProbElectron()) * (mTrack2->track()->pidProbElectron()); }
  double pionPairProbability() const
  { return (mTrack1->track()->pidProbPion()) * (mTrack2->track()->pidProbPion()); }
  double kaonPairProbability() const
  { return (mTrack1->track()->pidProbKaon()) * (mTrack2->track()->pidProbKaon()); }
  double protonPairProbability() const
  { return (mTrack1->track()->pidProbProton()) * (mTrack2->track()->pidProbProton()); }
  double kaonPionPairProbability() const
  { return (mTrack1->track()->pidProbKaon()) * (mTrack2->track()->pidProbPion()); }

  double dcaInsideTpc() const;
  double quality2() const;

  double kStarGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mKStarCalcGlobal; }
  double cvkGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mCVKGlobal; }
  double kStarSideGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mDKSideGlobal; }
  double kStarOutGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mDKOutGlobal; }
  double kStarLongGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mDKLongGlobal; }

  double fractionOfMergedRow() const
  { if(mMergingParNotCalculated) { calcMergingPar(); } return mFracOfMergedRow; }
  double closestRowAtDCA() const
  { if(mMergingParNotCalculated) { calcMergingPar(); } return mClosestRowAtDCA; }
  double weightedAvSep() const
  { if(mMergingParNotCalculated) { calcMergingPar(); } return mWeightedAvSep; }
  double fractionOfMergedRowTrkV0Pos() const
  { if(mMergingParNotCalculatedTrkV0Pos)
      { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Pos,
			    mTrack1->z(), mTrack1->u(),
			    mTrack2->z(), mTrack2->u(),
			    mTrack1->sect(), mTrack2->sect(),
			    &mFracOfMergedRowTrkV0Pos,
			    &mClosestRowAtDCATrkV0Pos );
      }
    return mFracOfMergedRowTrkV0Pos;
  }
  double closestRowAtDCATrkV0Pos() const
  { if(mMergingParNotCalculatedTrkV0Pos) { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Pos,
							       mTrack1->z(), mTrack1->u(),
							       mTrack2->z(), mTrack2->u(),
							       mTrack1->sect(), mTrack2->sect(),
							       &mFracOfMergedRowTrkV0Pos,
							       &mClosestRowAtDCATrkV0Pos ); }
    return mClosestRowAtDCATrkV0Pos;
  }

  double fractionOfMergedRowTrkV0Neg() const
  { if(mMergingParNotCalculatedTrkV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Neg,
							       mTrack1->z(), mTrack1->u(),
							       mTrack2->v0NegZ(), mTrack2->v0NegU(),
							       mTrack1->sect(), mTrack2->v0NegSect(),
							       &mFracOfMergedRowTrkV0Neg,
							       &mClosestRowAtDCATrkV0Neg ); }
    return mFracOfMergedRowTrkV0Neg;
  }
  double closestRowAtDCATrkV0Neg() const
  { if(mMergingParNotCalculatedTrkV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Neg,
							       mTrack1->z(),  mTrack1->u(),
							       mTrack2->v0NegZ(), mTrack2->v0NegU(),
							       mTrack1->sect(), mTrack2->v0NegSect(),
							       &mFracOfMergedRowTrkV0Neg,
							       &mClosestRowAtDCATrkV0Neg ); }
    return mClosestRowAtDCATrkV0Neg;
  }

  double fractionOfMergedRowV0PosV0Neg() const
  { if(mMergingParNotCalculatedV0PosV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedV0PosV0Neg,
								 mTrack1->z(), mTrack1->u(),
								 mTrack2->v0NegZ(),mTrack2->v0NegU(),
								 mTrack1->sect(), mTrack2->v0NegSect(),
								 &mFracOfMergedRowV0PosV0Neg,
								 &mClosestRowAtDCAV0PosV0Neg ); }
    return mFracOfMergedRowV0PosV0Neg;
  }
  double fractionOfMergedRowV0NegV0Pos() const
  { if(mMergingParNotCalculatedV0NegV0Pos) { calcMergingParFctn( &mMergingParNotCalculatedV0NegV0Pos,
								 mTrack1->v0NegZ(), mTrack1->v0NegU(),
								 mTrack2->z(), mTrack2->u(),
								 mTrack1->v0NegSect(), mTrack2->sect(),
								 &mFracOfMergedRowV0NegV0Pos,
								 &mClosestRowAtDCAV0NegV0Pos ); }
    return mFracOfMergedRowV0NegV0Pos;
  }
  double fractionOfMergedRowV0PosV0Pos() const
  { if(mMergingParNotCalculatedV0PosV0Pos) { calcMergingParFctn( &mMergingParNotCalculatedV0PosV0Pos,
								 mTrack1->z(), mTrack1->u(),
								 mTrack2->z(), mTrack2->u(),
								 mTrack1->sect(), mTrack2->sect(),
								 &mFracOfMergedRowV0PosV0Pos,
								 &mClosestRowAtDCAV0PosV0Pos ); }
    return mFracOfMergedRowV0PosV0Pos;
  }
  double fractionOfMergedRowV0NegV0Neg() const
  { if(mMergingParNotCalculatedV0NegV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedV0NegV0Neg,
								 mTrack1->v0NegZ(), mTrack1->v0NegU(),
								 mTrack2->v0NegZ(), mTrack2->v0NegU(),
								 mTrack1->v0NegSect(), mTrack2->v0NegSect(),
								 &mFracOfMergedRowV0NegV0Neg,
								 &mClosestRowAtDCAV0NegV0Neg ); }
    return mFracOfMergedRowV0NegV0Neg;
  }

  //
  // Setters
  //

  /// Set the first particle from a pair
  void setTrack1(const StHbtParticle* trkPtr) { mTrack1=(StHbtParticle*)trkPtr; resetParCalculated(); }
  /// Set the second particle from a pair
  void setTrack2(const StHbtParticle* trkPtr) { mTrack2=(StHbtParticle*)trkPtr; resetParCalculated(); }

  /// Set track-merging parameters
  void setMergingPar(float aMaxDuInner, float aMaxDzInner,
		     float aMaxDuOuter, float aMaxDzOuter);
  /// Set parameters used for track-merging estimation assuming half field
  void setDefaultHalfFieldMergingPar();
  /// Set parameters used for track-merging estimation assuming full field
  void setDefaultFullFieldMergingPar();

  /// Calculate the \Delta\phi^{*} between two particles, which is minal across several points
  /// \param p_a momentum of first particle
  /// \param charge_a charge of the first particle
  /// \param p_b momentum of second particle
  /// \param charge_b charge of the second particle
  /// \param radius_in_meters Radial distance at which the angle should be taken [Meters]
  /// \param magnetic_field_in_tesla Strength and direction of the magnetic field in the detector [Tesla]
  ///
  static double calculateDPhiStarMin(const TVector3& p_a,
                                     const short& charge_a,
                                     const TVector3& p_b,
                                     const short& charge_b,
                                     const double& rad_step_in_meters,
                                     const double& rad_min_in_meters,
                                     const double& rad_max_in_meters,
                                     const double& magnetic_field);

  /// Calculate the \Delta\phi^{*} between two particles at each radial step between
  ///
  /// \param p_a momentum of first particle
  /// \param charge_a charge of the first particle
  /// \param p_b momentum of second particle
  /// \param charge_b charge of the second particle
  /// \param radius_in_meters Radial distance at which the angle should be taken [Meters]
  /// \param magnetic_field_in_tesla Strength and direction of the magnetic field in the detector [Tesla]
  ///
  static std::vector<double> calculateDPhiStarValues(const TVector3& p_a,
                                                     const short& charge_a,
                                                     const TVector3& p_b,
                                                     const short& charge_b,
                                                     const double& rad_step_in_meters,
                                                     const double& rad_min_in_meters,
                                                     const double& rad_max_in_meters,
                                                     const double& magnetic_field);

  /// Calculate the \Delta\phi^{*} between two particles.
  /// \param p_a momentum of first particle
  /// \param charge_a charge of the first particle
  /// \param p_b momentum of second particle
  /// \param charge_b charge of the second particle
  /// \param radius_in_meters Radial distance at which the angle should be taken [Meters]
  /// \param magnetic_field_in_tesla Strength and direction of the magnetic field in the detector [Tesla]
  ///
  static double calculateDPhiStar(const TVector3& p_a,
				  const short& charge_a,
				  const TVector3& p_b,
				  const short& charge_b,
				  const double& radius_in_meters,
				  const double& magnetic_field);

  /// Calculate \Delta\phi between two particles.
  /// \param a Momentum of first particle
  /// \param b Momentum of second particle
  ///
  /// The calculation returns $\Delta\phi = \phi2 - \phi1$
  ///
  static double calculateDPhi(const TVector3& a, const TVector3& b);

  /// Calculate \Delta\eta between two particles.
  /// \param a Momentum of first particle
  /// \param b Momentum of second particle
  ///
  /// The calculation returns $\Delta\eta = \eta_2 - \eta_1$
  ///
  static double calculateDEta(const TVector3& a, const TVector3& b);

  /// Calculate \Delta\eta between two particles.
  /// \param a Momentum of first particle
  /// \param b Momentum of second particle
  /// \param minRad Radial distance at which the eta value should be taken?
  static double calculateDEtaStar(const TVector3& a, const TVector3& b,
                                  const double& radius_in_meters);

 private:

  /// The first particle from a pair
  StHbtParticle* mTrack1;
  /// The second particle from a pair
  StHbtParticle* mTrack2;

  mutable short mNonIdParNotCalculated;
  mutable float mDKSide;
  mutable float mDKOut;
  mutable float mDKLong;
  mutable float mCVK;
  mutable float mKStarCalc;
  void calcNonIdPar() const;

  mutable short mNonIdParNotCalculatedGlobal;
  mutable float mDKSideGlobal;
  mutable float mDKOutGlobal;
  mutable float mDKLongGlobal;
  mutable float mKStarCalcGlobal;
  mutable float mCVKGlobal;
  void calcNonIdParGlobal() const;

  mutable short mMergingParNotCalculated;
  mutable float mWeightedAvSep;
  mutable float mFracOfMergedRow;
  mutable float mClosestRowAtDCA;

  mutable short mMergingParNotCalculatedTrkV0Pos;
  mutable float mFracOfMergedRowTrkV0Pos;
  mutable float mClosestRowAtDCATrkV0Pos;

  mutable short mMergingParNotCalculatedTrkV0Neg;
  mutable float mFracOfMergedRowTrkV0Neg;
  mutable float mClosestRowAtDCATrkV0Neg;

  mutable short mMergingParNotCalculatedV0PosV0Neg;
  mutable float mFracOfMergedRowV0PosV0Neg;
  mutable float mClosestRowAtDCAV0PosV0Neg;

  mutable short mMergingParNotCalculatedV0NegV0Pos;
  mutable float mFracOfMergedRowV0NegV0Pos;
  mutable float mClosestRowAtDCAV0NegV0Pos;

  mutable short mMergingParNotCalculatedV0PosV0Pos;
  mutable float mFracOfMergedRowV0PosV0Pos;
  mutable float mClosestRowAtDCAV0PosV0Pos;

  mutable short mMergingParNotCalculatedV0NegV0Neg;
  mutable float mFracOfMergedRowV0NegV0Neg;
  mutable float mClosestRowAtDCAV0NegV0Neg;

  static float mMaxDuInner;
  static float mMaxDzInner;
  static float mMaxDuOuter;
  static float mMaxDzOuter;
  static float mTpcRadiusMin;   //[cm]
  static float mTpcRadiusMax;   //[cm]
  void calcMergingPar() const;

  /// Calculate track-merging parameters
  void calcMergingParFctn(short* tmpMergingParNotCalculatedFctn,
			  float* tmpZ1, float* tmpU1,
			  float* tmpZ2, float* tmpU2,
			  int *tmpSect1, int *tmpSect2,
			  float* tmpFracOfMergedRow,
			  float* tmpClosestRowAtDCA) const;

  /// Reset calculated parameters
  void resetParCalculated() {
    mNonIdParNotCalculated=1; mNonIdParNotCalculatedGlobal=1;
    mMergingParNotCalculated=1; mMergingParNotCalculatedTrkV0Pos=1;
    mMergingParNotCalculatedTrkV0Neg=1; mMergingParNotCalculatedV0PosV0Pos=1;
    mMergingParNotCalculatedV0NegV0Pos=1; mMergingParNotCalculatedV0PosV0Neg=1;
    mMergingParNotCalculatedV0NegV0Neg=1;
  }
};

#endif // #define StHbtPair_h
