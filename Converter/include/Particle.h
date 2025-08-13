#pragma once

class Particle {
public:
    double t, x, y, z, mass, p0, px, py, pz;
    int pdg, ID, charge;
    bool isInitNucl;

    Particle();
    Particle(double t, double x, double y, double z, double mass, double p0, double px, double py, double pz, int pdg, int ID, int charge);
    void SetSpectator();
};
