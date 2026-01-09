#include <iostream>
#include <cmath>

#include <TFile.h>
#include <TH3.h>
#include <TF3.h>
#include <TDirectory.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>

#include "helpers.h"
#include "fit.h"
#include "draw.h"
#include "cf3d.h"
#include "plots.h"
#include "ratios.h"
#include "proj1d.h"

int main()
{
    TH1::AddDirectory(kFALSE);

    TFile* input = TFile::Open("/home/tahea/smash_CF_builder/smash_CF_builder/cf_maker_new/test.root","READ");

    // ========== PHASE 1 ==========
    TFile* fCF = new TFile("output_3d.root","RECREATE");

    FitResult fitRes[chargeSize][centralitySize][ktSize][rapiditySize]{};

    for (int chIdx=0; chIdx<chargeSize; chIdx++)
        create_and_fit_3d(chIdx, input, fCF, fitRes);

    fCF->Write();
    fCF->Close();
    delete fCF;

    // ========== PHASE 2 ==========
    TFile* output = TFile::Open("output_3d.root", "UPDATE");

    do_kt_diff(output, fitRes);
    do_rapidity_diff(output, fitRes);
    do_CF_ratios(output, fitRes);
    do_1d_proj(input, output, fitRes);

    input->Close();
}


