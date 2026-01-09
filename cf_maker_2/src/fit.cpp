#include "fit.h"

#include <Rtypes.h>

Double_t CF_fit_3d(Double_t* q, Double_t* par) {
    const Double_t hc2 = 0.197 * 0.197;
    return 1.0 + par[3] * TMath::Exp(
        (-(q[0] * par[0]) * (q[0] * par[0])
         -(q[1] * par[1]) * (q[1] * par[1])
         -(q[2] * par[2]) * (q[2] * par[2])) / hc2
    );
}

TF3* CreateCF3DFit() {
    TF3* fit3d = new TF3(
        "fit3d",
        CF_fit_3d,
        -0.1, 0.1,
        -0.1, 0.1,
        -0.1, 0.1,
        4
    );

    fit3d->SetParameter(0, 5.5);  fit3d->SetParLimits(0, 2.0, 8.0); // R_out
    fit3d->SetParameter(1, 4.2);  fit3d->SetParLimits(1, 2.0, 8.0); // R_side
    fit3d->SetParameter(2, 3.8);  fit3d->SetParLimits(2, 2.0, 8.0); // R_long
    fit3d->SetParameter(3, 0.9);  fit3d->SetParLimits(3, 0.7, 1.1);

    return fit3d; // вызывающий обязан delete
}

FitResult FitCF3D(TH3D* hCF, TF3* fit3d) {
    FitResult res{};
    if (!hCF || hCF->GetEntries() == 0 || !fit3d) return res;

    fit3d->SetParameters(5.5, 4.2, 3.8, 0.9);

    hCF->Fit(fit3d, "RMQN0");

    for (int i = 0; i < 3; ++i) {
        res.R[i]   = fit3d->GetParameter(i);
        res.eR[i]  = fit3d->GetParError(i);
    }
    res.lambda   = fit3d->GetParameter(3);
    res.elambda  = fit3d->GetParError(3);
    res.ok = true;

    return res;
}
