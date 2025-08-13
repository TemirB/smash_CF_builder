#pragma once

#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TClonesArray.h>
#include "McEvent.h"
#include "McParticle.h"
#include "McArrays.h"

#include "RootConverter.h"

void ConvertRootToMcDst(const std::string& inName, const std::string& outName) {
    TFile* inFile = TFile::Open(inName.c_str(), "READ");
    if (!inFile || inFile->IsZombie()) {
        std::cerr << "Ошибка открытия файла: " << inName << std::endl;
        return;
    }

    TTree* inTree = dynamic_cast<TTree*>(inFile->Get("Particles"));
    if (!inTree) {
        std::cerr << "Дерево 'Particles' не найдено в файле: " << inName << std::endl;
        return;
    }

    TTreeReader reader(inTree);
    TTreeReaderValue<int> npart(reader, "npart");
    TTreeReaderValue<double> impactParameter(reader, "impactParameter");
    TTreeReaderValue<std::vector<double>> t(reader, "t"), x(reader, "x"), y(reader, "y"), z(reader, "z");
    TTreeReaderValue<std::vector<double>> mass(reader, "mass"), p0(reader, "p0");
    TTreeReaderValue<std::vector<double>> px(reader, "px"), py(reader, "py"), pz(reader, "pz");
    TTreeReaderValue<std::vector<int>> pdg(reader, "pdg"), ID(reader, "ID"), charge(reader, "charge");

    TFile* outFile = TFile::Open(outName.c_str(), "RECREATE");
    TTree* outTree = new TTree("McDst", "Converted McDst Data");

    const int bufsize = 65536, split = 99;
    TClonesArray* arrays[McArrays::NAllMcArrays];
    arrays[McArrays::Event] = new TClonesArray("McEvent", 1);
    arrays[McArrays::Particle] = new TClonesArray("McParticle", 10000);

    outTree->Branch("Event", &arrays[McArrays::Event], bufsize, split);
    outTree->Branch("Particle", &arrays[McArrays::Particle], bufsize, split);

    int eventNumber = 0;
    int child[2] = {-1, -1};

    while (reader.Next()) {
        arrays[McArrays::Event]->Clear();
        arrays[McArrays::Particle]->Clear();

        McEvent* event = new ((*arrays[McArrays::Event])[0]) McEvent();
        event->setEventNr(eventNumber);
        event->setB(*impactParameter);
        event->setStepNr(1);
        event->setStepT(200.0);
        event->setNes(1);
        event->setPhi(0);
        event->setComment("");

        int n = *npart;

        for (int j = 0; j < n; ++j) {
            new ((*arrays[McArrays::Particle])[j]) McParticle(
                j, (*pdg)[j],
                0, -1, 0, -1, 0, child,
                (*px)[j], (*py)[j], (*pz)[j], (*p0)[j], (*x)[j], (*y)[j], (*z)[j], (*t)[j]
            );
        }

        outTree->Fill();
        eventNumber++;
    }

    outFile->Write();
    outFile->Close();
    inFile->Close();
}