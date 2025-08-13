#include "OscarConverter.h"
#include "Particle.h"
#include "Mode.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <memory>

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

#include "McRun.h"
#include "McEvent.h"
#include "McParticle.h"
#include "McArrays.h"

bool OscarConverter::Convert(const std::string& inputFilename, const std::string& outputFilename) {
    TFile* outputFile = TFile::Open(outputFilename.c_str(), "RECREATE", "Oscar to McDst");
    if (!outputFile || outputFile->IsZombie()) {
        std::cerr << "Cannot create output file: " << outputFilename << std::endl;
        return false;
    }
    outputFile->SetCompressionLevel(1);

    TTree* tree = new TTree("McDst", "Converted Oscar Data");
    TClonesArray* arrays[McArrays::NAllMcArrays];

    for (unsigned int i = 0; i < McArrays::NAllMcArrays; i++) {
        arrays[i] = new TClonesArray(McArrays::mcArrayTypes[i], McArrays::mcArraySizes[i]);
        arrays[i]->SetOwner(kFALSE);
        auto br = tree->Branch(McArrays::mcArrayNames[i], &arrays[i], 65536, 99);
        if (br) br->SetAutoDelete(kFALSE);
    }

    std::ifstream infile(inputFilename);
    if (!infile.is_open()) {
        std::cerr << "Cannot open input file: " << inputFilename << std::endl;
        return false;
    }

    bool isElastic = false;
    int ev_num = -1;
    int n_part = -1;
    Mode mode = Mode::Init;
    int startParticlesNum = 394;

    double timpactParameter = -1.;

    std::unordered_map<int, Particle> buffer;
    std::unordered_map<int, Particle> endBuffer;
    std::unordered_map<int, Particle> eventBuffer;

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);

        if (line[0] == '#') {
            std::string interaction, dummy, keyWord;
            iss >> dummy >> interaction >> ev_num >> dummy >> dummy >> keyWord >> n_part;
            //       #        event          1      ensemble    0        in         394
            //       #        event          2      ensemble    0        out        399
            //       #      interaction      in        2       out       2          rho    0.0000000    weight     42.07034                         partial    3.7040866 type     3
            //       #        event          0      ensemble    0        end         0       impact      9.179       scattering_projectile_target        yes
            if (interaction == "interaction") {
                mode = Mode::Interaction;
                // тут можно посмотреть считать 
                // тип взаимодействия и его параметры
                continue;
            } else if (interaction == "event") {
                if (keyWord == "in") {
                    mode = Mode::InEvent;
                    isElastic = false;

                    buffer.clear();
                    endBuffer.clear();
                    eventBuffer.clear();
                    for (unsigned int i = 0; i < McArrays::NAllMcArrays; i++) arrays[i]->Clear();
                    continue;
                } else if (keyWord == "out") {
                    mode = (n_part == startParticlesNum) ? Mode::SkipEvent : Mode::OutEvent;
                    isElastic = (mode == Mode::SkipEvent);
                    continue;
                } else if (keyWord == "end") {
                    mode = Mode::EndEvent;
                    iss >> dummy >> timpactParameter;
                    //    impact      9.179             scattering_projectile_target        yes
                    if (isElastic) {
                        timpactParameter = -1.;
                        continue;
                    }
                } else {
                    mode = Mode::SkipEvent;
                    continue;
                }
            }
        }

        if (mode == Mode::SkipEvent) continue;

        double t, x, y, z, mass, p0, px, py, pz;
        int pdg, ID, charge;
        iss >> t >> x >> y >> z >> mass >> p0 >> px >> py >> pz >> pdg >> ID >> charge;
        Particle p(t, x, y, z, mass, p0, px, py, pz, pdg, ID, charge);

        if (mode == Mode::Interaction || mode == Mode::InEvent) {
            if (ID < 394) p.isInitNucl = true;
            buffer[ID] = p;
        } else if (mode == Mode::OutEvent) {
            if (isElastic) continue;
            endBuffer[ID] = p;
        } else if (mode == Mode::EndEvent) {
            for (const auto& entry : buffer) {
                int id = entry.first;
                const Particle& initParticle = entry.second;

                if (endBuffer.find(id) == endBuffer.end()) continue;

                if (initParticle.isInitNucl) {
                    Particle specParticle = initParticle;
                    specParticle.SetSpectator();
                    eventBuffer[id] = specParticle;
                } else {
                    eventBuffer[id] = initParticle;
                }
            }

            int child[2] = {-1, -1};
            int idx = 0;
            for (const auto& entry : eventBuffer) {
                const Particle& p1 = entry.second;
                new((*(arrays[McArrays::Particle]))[arrays[McArrays::Particle]->GetEntries()])
                McParticle(idx++, p1.pdg, 0, 0, 0, -1, 0, child,
                          p1.px, p1.py, p1.pz, p1.p0,
                          p1.x, p1.y, p1.z, p1.t);
            }

            McEvent* event = new((*(arrays[McArrays::Event]))[arrays[McArrays::Event]->GetEntries()]) McEvent();
            event->setEventNr(ev_num);
            event->setB(timpactParameter);
            event->setPhi(0.);
            event->setNes(1);
            event->setComment("");
            event->setStepNr(1);
            event->setStepT(200.);
            
            tree->Fill();
            buffer.clear();
            endBuffer.clear();
            eventBuffer.clear();
        }
    }

    McRun run("SMASH", "Converted from Oscar file",
              0, 0, 0., 0, 0, 0.,
              0., 0., -1, 0, 0, 0., tree->GetEntries());
    run.Write();

    std::cout << "Conversion completed. Total events: " << tree->GetEntries() << std::endl;

    outputFile->Write();
    outputFile->Close();

    return true;
}