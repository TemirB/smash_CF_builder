/**
 * \class StHbtKink
 * \brief Main class holding kink information
 *
 * StHbtKink holds all the necessary information about a kink
 */

#ifndef StHbtKink_h
#define StHbtKink_h

// StHbtMaker headers
#include "StHbtTrack.h"
#include "StHbtTypes.h"

// ROOT headers
#include "TVector3.h"

//_________________
class StHbtKink {

 public:
  /// Default constructor
  StHbtKink();
  /// Copy constructor
  StHbtKink(const StHbtKink&);
  /// Copy constructor
  StHbtKink& operator=(const StHbtKink &k);
  /// Default destructor
  virtual ~StHbtKink();

  //
  // Getters
  //

  float        dcaParentDaughter() const         { return mDcaParentDaughter; }
  float        dcaDaughterPrimaryVertex() const  { return mDaughter.gDCA().Mag(); }
  float        dcaParent2PrimaryVertex() const   { return mParent.gDCA().Mag(); }
  float        hitDistanceParentDaughter() const { return mHitDistanceParentDaughter; }
  float        hitDistanceParentVertex() const   { return mHitDistanceParentVertex; }
  float        deltaEnergy(int i=0) const        { return mDeltaEnergy[i]; }
  float        decayAngle() const                { return mDecayAngle; }
  float        decayAngleCM() const              { return mDecayAngleCM; }
  StHbtTrack   daughter() const                  { return mDaughter; }
  StHbtTrack   parent() const                    { return mParent; }
  TVector3     position() const                  { return TVector3( mPositionX, mPositionY, mPositionZ ); }
  TVector3     kinkPoint() const                 { return position(); }
  TVector3     decayPoint() const                { return position(); }
  TVector3     primaryVertex() const             { return mParent.primaryVertex(); }

  //
  // Setters
  //

  void setDcaParentDaughter(const float& dca)         { mDcaParentDaughter = dca; }
  void setHitDistanceParentDaugher(const float& dist) { mHitDistanceParentDaughter = dist; }
  void setHitDistanceParentVertex(const float& dist)  { mHitDistanceParentVertex = dist; }
  void setDeltaEnergy(const int& i, const float& e)   { mDeltaEnergy[i] = e; }
  void setDecayAngle(const float& angle)              { mDecayAngle = angle; }
  void setDecayAngleCM(const float& angle)            { mDecayAngleCM = angle; }
  void setDaugherHbtTrack(const StHbtTrack& trk);
  void setParetntHbtTrack(const StHbtTrack& trk);
  void setKinkPoint(const TVector3& pos)
  { mPositionX = pos.X(); mPositionY = pos.Y(); mPositionZ = pos.Z(); }
  void setKinkPoint(const float& x, const float& y, const float& z)
  { mPositionX = x; mPositionY = y; mPositionZ = z; }
  void setPoint(const TVector3& pos)                  { setKinkPoint( pos ); }
  void setPoint(const float& x, const float& y, const float& z) { setKinkPoint( x, y, z ); }

protected:

  /// DCA between parent and daugher
  float mDcaParentDaughter;
  /// Distance between parent track and daughter track
  float mHitDistanceParentDaughter;
  /// Distance between parent track and primary vertex
  float mHitDistanceParentVertex;
  /// Missed energy
  float mDeltaEnergy[3];
  /// Decay angles in the Lab frame
  float mDecayAngle;
  /// Decay angles in the CMS frame
  float mDecayAngleCM;
  /// Daughter track
  StHbtTrack mDaughter;
  /// Parent track
  StHbtTrack mParent;
  /// Decay point x of the kink
  float mPositionX;
  /// Decay point y of the kink
  float mPositionY;
  /// Decay point z of the kink
  float mPositionZ;

#ifdef __ROOT__
  ClassDef(StHbtKink, 1)
#endif
};

#endif // #define StHbtKink_h
