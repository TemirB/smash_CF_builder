#include <TH3.h>
#include <TF3.h>
#include <TDirectory.h>

void get_1d_proj(
    TDirectory* dir ,TH3* h_A, TH3* h_A_wei, TF3* fit3d,
    const std::string& axis, const std::string& LCMS, const std::string& prefix
);

void do_1d_proj(
    TFile* inputFile, TFile* outFile, 
    FitResult (&fitRes)[chargeSize][centralitySize][ktSize][rapiditySize]
);