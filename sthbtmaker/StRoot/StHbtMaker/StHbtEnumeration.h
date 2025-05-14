/**
 * \class StHbtEnumeration
 * \brief Enumerations for StHbtMaker
 *
 * The file keeps enumarations for particle types and I/O mode
 */

#ifndef StHbtEnumeration_h
#define StHbtEnumeration_h

/// Particle types
enum StHbtParticleType { hbtUndefined, hbtTrack, hbtV0, hbtKink, hbtXi };
/// I/O mode
enum StHbtIOMode       { hbtRead, hbtWrite };

#endif //#define StHbtEnumeration_h
