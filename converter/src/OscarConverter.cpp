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
    outputFile->SetCompressionLevel(9);

    TTree* tree = new TTree("McDst", "Converted Oscar Data");
    TClonesArray* arrays[McArrays::NAllMcArrays];

    for (unsigned int i = 0; i < McArrays::NAllMcArrays; i++) {
        arrays[i] = new TClonesArray(McArrays::mcArrayTypes[i], McArrays::mcArraySizes[i]);
        tree->Branch(McArrays::mcArrayNames[i], &arrays[i], 65536, 99);
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
            std::string dummy, keyWord;
            iss >> dummy >> dummy >> ev_num >> keyWord >> n_part;

            if (dummy == "interaction") {
                mode = Mode::Interaction;
                continue;
            } else if (dummy == "event") {
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

            int idx = 0;
            for (const auto& entry : eventBuffer) {
                const Particle& p1 = entry.second;
                new((*(arrays[McArrays::Particle]))[arrays[McArrays::Particle]->GetEntries()])
                McParticle(idx++, p1.pdg, 0, 0, 0, -1, 0, nullptr,
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

    outputFile->Write();
    outputFile->Close();

    std::cout << "Conversion completed. Total events: " << tree->GetEntries() << std::endl;

    return true;
}