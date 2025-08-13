#include "Particle.h"

Particle::Particle()
    : t(-1), x(0), y(0), z(0), mass(0), p0(0), px(0), py(0), pz(0), pdg(0), ID(0), charge(0), isInitNucl(false) {}

Particle::Particle(double t, double x, double y, double z, double mass, double p0, double px, double py, double pz, int pdg, int ID, int charge)
    : t(t), x(x), y(y), z(z), mass(mass), p0(p0), px(px), py(py), pz(pz), pdg(pdg), ID(ID), charge(charge), isInitNucl(false) {}

void Particle::SetSpectator() {
    t = x = y = z = -999.;
}
