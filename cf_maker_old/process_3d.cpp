#include <TFile.h>
#include <TH3D.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TF3.h>
#include <TStyle.h>
#include <TSystem.h>
#include <iostream>
#include <array>
#include <string>
#include <unordered_map>

// Аналитическая функция для 3D-корреляционной функции (гауссовская форма: 1 + λ * exp(-(q_out*R_out)^2 - ...))
Double_t CF_fit_3d(Double_t *q, Double_t *par) {
    const Double_t hc2 = 0.197 * 0.197;  // (ħc)^2 константа
    // par[0]=R_out, par[1]=R_side, par[2]=R_long, par[3]=λ
    Double_t fitval = 1 + par[3] * TMath::Exp(
        (-(q[0] * par[0]) * (q[0] * par[0]) 
         - (q[1] * par[1]) * (q[1] * par[1]) 
         - (q[2] * par[2]) * (q[2] * par[2])) / hc2
    );
    return fitval;
}

void draw_mg_on_c(TCanvas* canvas, TMultiGraph* multigraph, TLegend* legend, std::string title, int padIndex,
    double minY, double maxY, std::string titleY){
    multigraph->GetXaxis()->SetRangeUser(-0.3, 4.3);    multigraph->GetXaxis()->SetTitle("k_{t} [GeV/c]");
    multigraph->GetYaxis()->SetRangeUser(minY, maxY);   multigraph->GetYaxis()->SetTitle(titleY.c_str());
    multigraph->SetTitle(title.c_str());

    canvas->cd(padIndex);
    multigraph->Draw("alp");
    legend->Draw("SAME");
}

// Глобальный список для указателей на временные гистограммы (1D, 2D, 3D), чтобы удалить их позже
static std::vector<TH1*> histList;

// Вспомогательная функция для проекции 3D-гистограммы на 1D и рисования на заданных холстах
void ProjectAndDraw1D(TFile* inputFile, TCanvas* canvas_all, TCanvas* canvas_min, TF3* fit3d,
                      unsigned int i, unsigned int j, unsigned int padIndex, 
                      const std::string& axis, const std::string& LCMS, const std::string& suffix) {
    // Читаем 3D-гистограммы A (без весов) и A_wei (с весами) для заданных i, j
    TH3D* tmp_h_A_3d     = (TH3D*) inputFile->Get(("h3d_A_q_" + suffix).c_str());
    TH3D* tmp_h_A_wei_3d = (TH3D*) inputFile->Get(("h3d_A_wei_q_" + suffix).c_str());
    if (!tmp_h_A_3d || !tmp_h_A_wei_3d) {
        std::cerr << "Warning: 3D histograms for suffix=" << suffix << " j=" << j << " not found!" << std::endl;
        return;
    }
    // Создаем вспомогательные 3D-гистограммы для аналитической модели (числитель и знаменатель)
    TH3D* denominator = new TH3D("denom", "denom", 80, -0.4, 0.4, 80, -0.4, 0.4, 80, -0.4, 0.4);
    denominator->SetDirectory(nullptr);
    TH3D* numerator   = new TH3D("numer", "numer", 80, -0.4, 0.4, 80, -0.4, 0.4, 80, -0.4, 0.4);
    numerator->SetDirectory(nullptr);
    // Заполняем numerator значениями аналитической функции (fit3d), denominator = 1 во всех ячейках
    for (int xbin = 1; xbin <= 80; ++xbin) {
        for (int ybin = 1; ybin <= 80; ++ybin) {
            for (int zbin = 1; zbin <= 80; ++zbin) {
                denominator->SetBinContent(xbin, ybin, zbin, 1.0);
                denominator->SetBinError(xbin, ybin, zbin, 0.0);
                double xval = numerator->GetXaxis()->GetBinCenter(xbin);
                double yval = numerator->GetYaxis()->GetBinCenter(ybin);
                double zval = numerator->GetZaxis()->GetBinCenter(zbin);
                double value = fit3d->Eval(xval, yval, zval);
                numerator->SetBinContent(xbin, ybin, zbin, value);
                numerator->SetBinError(xbin, ybin, zbin, 0.0);
            }
        }
    }
    // Устанавливаем диапазон по осям (ограничиваем проекцию области |q| < 0.05 ГэВ/с вдоль остальных направлений)
    if (LCMS == "out") {
        tmp_h_A_wei_3d->GetYaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_wei_3d->GetZaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetYaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetZaxis()->SetRangeUser(-0.05, 0.05);
        denominator->GetYaxis()->SetRangeUser(-0.05, 0.05);
        denominator->GetZaxis()->SetRangeUser(-0.05, 0.05);
        numerator->GetYaxis()->SetRangeUser(-0.05, 0.05);
        numerator->GetZaxis()->SetRangeUser(-0.05, 0.05);
    } else if (LCMS == "side") {
        tmp_h_A_wei_3d->GetXaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_wei_3d->GetZaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetXaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetZaxis()->SetRangeUser(-0.05, 0.05);
        denominator->GetXaxis()->SetRangeUser(-0.05, 0.05);
        denominator->GetZaxis()->SetRangeUser(-0.05, 0.05);
        numerator->GetXaxis()->SetRangeUser(-0.05, 0.05);
        numerator->GetZaxis()->SetRangeUser(-0.05, 0.05);
    } else if (LCMS == "long") {
        tmp_h_A_wei_3d->GetXaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_wei_3d->GetYaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetXaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetYaxis()->SetRangeUser(-0.05, 0.05);
        denominator->GetXaxis()->SetRangeUser(-0.05, 0.05);
        denominator->GetYaxis()->SetRangeUser(-0.05, 0.05);
        numerator->GetXaxis()->SetRangeUser(-0.05, 0.05);
        numerator->GetYaxis()->SetRangeUser(-0.05, 0.05);
    }
    // Проецируем 3D-гистограммы на указанную ось (x, y или z) для получения 1D распределений
    TH1D* h_1d_projection_A     = (TH1D*) tmp_h_A_3d->Project3D(axis.c_str());
    TH1D* h_1d_projection_A_wei = (TH1D*) tmp_h_A_wei_3d->Project3D(axis.c_str());
    TH1D* h_1d_denominator      = (TH1D*) denominator->Project3D(axis.c_str());
    TH1D* h_1d_numerator        = (TH1D*) numerator->Project3D(axis.c_str());
    // Отключаем привязку проекций к файлам/директориям
    h_1d_projection_A->SetDirectory(nullptr);
    h_1d_projection_A_wei->SetDirectory(nullptr);
    h_1d_denominator->SetDirectory(nullptr);
    h_1d_numerator->SetDirectory(nullptr);
    // Создаем гистограммы для отображения: h_1d_tmp_C (CF по данным) и h_1d_fit (CF по фит-модели)
    TH1D* h_1d_tmp_C = (TH1D*) h_1d_projection_A_wei->Clone(("h3d_C_q_" + LCMS + "_" + suffix).c_str());
    h_1d_tmp_C->Reset();
    TH1D* h_1d_fit   = (TH1D*) h_1d_denominator->Clone(("h_1d_fit_" + LCMS + "_" + suffix).c_str());
    h_1d_fit->Reset();
    // Вычисляем CF: делим взвешенное и невзвешенное проекции, а также числитель/знаменатель аналитической модели
    h_1d_tmp_C->Divide(h_1d_projection_A_wei, h_1d_projection_A);
    h_1d_fit->Divide(h_1d_numerator, h_1d_denominator);
    // Настраиваем гистограмму CF (масштаб осей, цвета, маркировка)
    h_1d_tmp_C->GetYaxis()->SetRangeUser(0.8, 1.9);
    h_1d_tmp_C->GetYaxis()->SetTitle(("CF_{" + LCMS + "}").c_str());
    h_1d_tmp_C->GetXaxis()->SetRangeUser(-0.2, 0.2);
    h_1d_tmp_C->GetXaxis()->SetTitle(("q_{" + LCMS + "} [GeV/c]").c_str());
    const std::array<int, 4> colors = {kRed, kBlue, kMagenta, kGreen};
    h_1d_tmp_C->SetLineColor(colors[(i+j) % 4]);
    h_1d_tmp_C->SetMarkerColor(colors[(i+j) % 4]);
    h_1d_tmp_C->SetMarkerStyle(20 + ((i+j) % 4));
    h_1d_tmp_C->GetXaxis()->SetTitleSize(0.05);
    h_1d_tmp_C->GetYaxis()->SetTitleSize(0.05);
    h_1d_tmp_C->GetXaxis()->SetTitleOffset(0.8);
    h_1d_fit->SetLineColor(colors[(i+j) % 4]);
    h_1d_fit->SetLineWidth(4);
    // Размещаем 1D CF на соответствующей паде (canvas_all - все проекции, canvas_min - холст 2x2 для min. проекций)
    canvas_all->cd(4 * i + j + 1);
    h_1d_tmp_C->Draw("LP");
    h_1d_fit->Draw("L SAME");
    if (i == 0 && j == 0) {
        // Дополнительно выводим первые проекции (для i=0,j=0) на отдельный холст минимальных проекций (например, для сравнения)
        canvas_min->cd(padIndex);
        h_1d_tmp_C->Draw("LP");
        h_1d_fit->Draw("L SAME");
    }
    // Удаляем временные проекции и 3D гистограммы numerator/denominator (они более не нужны)
    delete h_1d_projection_A;
    delete h_1d_projection_A_wei;
    delete h_1d_numerator;
    delete h_1d_denominator;
    delete numerator;
    delete denominator;
    // Отключаем привязку и сохраняем указатели на созданные гистограммы для последующего удаления
    h_1d_tmp_C->SetDirectory(nullptr);
    h_1d_fit->SetDirectory(nullptr);
    histList.push_back(h_1d_tmp_C);
    histList.push_back(h_1d_fit);
}

// Вспомогательная функция для проекции 3D-гистограммы на 2D и рисования на заданных холстах
void ProjectAndDraw2D(TFile* inputFile, TCanvas* c_axis1_vs_axis2, TCanvas* c_2DCF_min,
                      unsigned int i, unsigned int j,
                      const std::string& axis1_vs_axis2, const std::string& LCMS1, const std::string& LCMS2,
                      const std::string& suffix, unsigned int padMinIndex) {
    // Читаем 3D-гистограммы A и A_wei для заданных параметров
    TH3D* tmp_h_A_3d     = (TH3D*) inputFile->Get(("h3d_A_q_" + suffix).c_str());
    TH3D* tmp_h_A_wei_3d = (TH3D*) inputFile->Get(("h3d_A_wei_q_" + suffix).c_str());
    if (!tmp_h_A_3d || !tmp_h_A_wei_3d) {
        std::cerr << "Warning: 3D histograms for 2D-projection suffix=" << suffix << " j=" << j << " not found!" << std::endl;
        return;
    }
    // Ограничиваем диапазон по оставшейся координате для 2D проекции (оставляем |q| < 0.05 ГэВ/с)
    if (axis1_vs_axis2 == "xy") {
        tmp_h_A_wei_3d->GetZaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetZaxis()->SetRangeUser(-0.05, 0.05);
    } else if (axis1_vs_axis2 == "xz") {
        tmp_h_A_wei_3d->GetYaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetYaxis()->SetRangeUser(-0.05, 0.05);
    } else if (axis1_vs_axis2 == "yz") {
        tmp_h_A_wei_3d->GetXaxis()->SetRangeUser(-0.05, 0.05);
        tmp_h_A_3d->GetXaxis()->SetRangeUser(-0.05, 0.05);
    }
    // Формируем имя для 2D CF и проецируем 3D-гистограммы на заданную плоскость (xy, xz или yz)
    std::string name = "CF_{q_" + LCMS1 + "_vs_" + LCMS2 + "}_" + suffix;
    TH2D* h2d_projection_A     = (TH2D*) tmp_h_A_3d->Project3D(axis1_vs_axis2.c_str());
    TH2D* h2d_projection_A_wei = (TH2D*) tmp_h_A_wei_3d->Project3D(axis1_vs_axis2.c_str());
    // Отключаем привязку 2D-проекций к файлам
    h2d_projection_A->SetDirectory(nullptr);
    h2d_projection_A_wei->SetDirectory(nullptr);
    // Создаем новую 2D-гистограмму для CF и вычисляем CF = A_wei / A
    TH2D* h2d_tmp_C = (TH2D*) h2d_projection_A_wei->Clone(name.c_str());
    h2d_tmp_C->Reset();
    h2d_tmp_C->Divide(h2d_projection_A_wei, h2d_projection_A);
    h2d_tmp_C->GetYaxis()->SetRangeUser(-0.13, 0.13);
    h2d_tmp_C->GetYaxis()->SetTitle(("q_{" + LCMS1 + "} [GeV/c]").c_str());
    h2d_tmp_C->GetXaxis()->SetRangeUser(-0.13, 0.13);
    h2d_tmp_C->GetXaxis()->SetTitle(("q_{" + LCMS2 + "} [GeV/c]").c_str());
    h2d_tmp_C->GetZaxis()->SetRangeUser(0.95, 1.3);
    h2d_tmp_C->GetYaxis()->SetTitleOffset(0.8);
    // Размещаем 2D CF на соответствующем паде большого полотна и (первый график) на полотне 2x2 минимальных проекций
    c_axis1_vs_axis2->cd(4 * i + j + 1);
    h2d_tmp_C->Draw("COLZ");
    if (i == 0 && j == 0) {
        c_2DCF_min->cd(padMinIndex);
        h2d_tmp_C->Draw("COLZ");
    }
    // Удаляем временные 2D-проекции (они не нужны после вычисления CF)
    delete h2d_projection_A;
    delete h2d_projection_A_wei;
    // Отключаем привязку и сохраняем указатель для удаления
    h2d_tmp_C->SetDirectory(nullptr);
    histList.push_back(h2d_tmp_C);
}

// Основная функция обработки 3D-гистограмм
void process_3d_histograms(const char* fileName) {
    TFile* inputFile = TFile::Open(fileName, "READ");
    if (!inputFile || inputFile->IsZombie()) {
        std::cerr << "Error opening file " << fileName << std::endl;
        return;
    }
    
    const std::array<std::string, 4> centralityNames = {"0-10", "10-30", "30-50", "50-80"};
    const std::array<std::string, 4> ktNames         = {"0.15-0.25", "0.25-0.35", "0.35-0.45", "0.45-0.60"};
    const std::array<double, 5>      ktvalues        = {0.15, 0.25, 0.35, 0.45, 0.60};
    const std::array<std::string, 3> axis            = {"x", "y", "z"};
    const std::array<std::string, 3> LCMS            = {"out", "side", "long"};
    const std::array<std::string, 2> chargeNames          = {"pos", "neg"};
    const std::array<int, 4> markers = {20, 21, 22, 23};
    const std::array<int, 4> colors = {kRed, kBlue, kMagenta, kGreen};

    // Подготовка холстов (каждый размером 900x700) для различных групп графиков (массивы размера 2 - для pos/neg)
    std::array<TCanvas*, 2> c_all_3d_CF;
    std::array<TCanvas*, 2> c_lambda_vs_kt;
    std::array<TCanvas*, 2> c_all_3d_CF_proj_out;
    std::array<TCanvas*, 2> c_all_3d_CF_proj_side;
    std::array<TCanvas*, 2> c_all_3d_CF_proj_long;
    std::array<TCanvas*, 2> c_2DCF_out_vs_side;
    std::array<TCanvas*, 2> c_2DCF_out_vs_long;
    std::array<TCanvas*, 2> c_2DCF_side_vs_long;
    std::array<TCanvas*, 2> c_1DCF_min;
    std::array<TCanvas*, 2> c_2DCF_min;
    std::array<TCanvas*, 2> c_ROSL_lambda;
    std::array<TCanvas*, 2> c_out_side_long_lambda;
    
    // Словарь холстов радиусов vs k_t: по заряду (ключ 0/1) хранится массив из 3 холстов (out/side/long радиусы)
    std::unordered_map<int, std::array<TCanvas*, 3>> c_R_vs_kt;
    // Легенды для λ-графиков (отдельно для pos/neg) и для радиусов (массив из 3 для out/side/long на каждый заряд)
    std::array<TLegend*, 2> l_lambda;
    std::unordered_map<int, std::array<TLegend*, 3>> l_R;
    
    // Инициализация холстов и легенд для каждой группы
    for (unsigned int i = 0; i < chargeNames.size(); ++i) {
        // Главные холсты 3D CF и λ vs k_t
        c_all_3d_CF[i]   = new TCanvas(("c_all_3d_CF_" + chargeNames[i]).c_str(), ("All 3D CFs " + chargeNames[i]).c_str(), 900, 700);
        c_all_3d_CF[i]->Divide(4, 4);
        c_lambda_vs_kt[i] = new TCanvas(("c_lambda_vs_kt_3d_" + chargeNames[i]).c_str(), ("#lambda vs k_t (3D) " + chargeNames[i]).c_str(), 900, 700);
        // Холсты для проекций 3D CF (на out/side/long оси)
        c_all_3d_CF_proj_out[i]  = new TCanvas(("c_all_3d_CF_proj_out_"  + chargeNames[i]).c_str(), "All 3D CF projections (out)", 900, 700);
        c_all_3d_CF_proj_out[i]->Divide(4, 4, 0.001, 0.001);
        c_all_3d_CF_proj_side[i] = new TCanvas(("c_all_3d_CF_proj_side_" + chargeNames[i]).c_str(), "All 3D CF projections (side)", 900, 700);
        c_all_3d_CF_proj_side[i]->Divide(4, 4, 0.001, 0.001);
        c_all_3d_CF_proj_long[i] = new TCanvas(("c_all_3d_CF_proj_long_" + chargeNames[i]).c_str(), "All 3D CF projections (long)", 900, 700);
        c_all_3d_CF_proj_long[i]->Divide(4, 4, 0.001, 0.001);
        // Холсты для 2D проекций CF (пары направлений)
        c_2DCF_out_vs_side[i] = new TCanvas(("c_2DCF_out_vs_side_" + chargeNames[i]).c_str(), "2D CF out-vs-side", 900, 700);
        c_2DCF_out_vs_side[i]->Divide(4, 4, 0.01, 0.01);
        c_2DCF_out_vs_long[i] = new TCanvas(("c_2DCF_out_vs_long_" + chargeNames[i]).c_str(), "2D CF out-vs-long", 900, 700);
        c_2DCF_out_vs_long[i]->Divide(4, 4, 0.01, 0.01);
        c_2DCF_side_vs_long[i] = new TCanvas(("c_2DCF_side_vs_long_" + chargeNames[i]).c_str(), "2D CF side-vs-long", 900, 700);
        c_2DCF_side_vs_long[i]->Divide(4, 4, 0.01, 0.01);
        // Холсты для "минимальных" проекций (1D и 2D на одном холсте 2x2)
        c_1DCF_min[i] = new TCanvas(("c_1DCF_min_" + chargeNames[i]).c_str(), "1D CF projections (min)", 900, 700);
        c_1DCF_min[i]->Divide(2, 2, 0.001, 0.001);
        c_2DCF_min[i] = new TCanvas(("c_2DCF_min_" + chargeNames[i]).c_str(), "2D CF projections (min)", 900, 700);
        c_2DCF_min[i]->Divide(2, 2, 0.001, 0.001);
        // Холсты для комбинированных графиков радиусов (R_out, R_side, R_long) и λ (4 пады: 3 радиуса + λ)
        c_ROSL_lambda[i]          = new TCanvas(("c_ROSL_lambda_" + chargeNames[i]).c_str(), "R(out,side,long) & lambda", 900, 700);
        c_ROSL_lambda[i]->Divide(2, 2, 0.001, 0.001);
        c_out_side_long_lambda[i] = new TCanvas(("c_out_side_long_lambda_" + chargeNames[i]).c_str(), "R_out-side-long vs k_t", 900, 700);
        c_out_side_long_lambda[i]->Divide(2, 2, 0.001, 0.001);
        // Легенды для λ-графиков (по одному на каждый заряд) и для радиусов (3 на каждый заряд)
        l_lambda[i] = new TLegend(0.5, 0.7, 0.9, 0.9);
        for (unsigned int j = 0; j < LCMS.size(); ++j) {
            l_R[i][j] = new TLegend(0.5, 0.7, 0.9, 0.9);
        }
        // Подготавливаем словарь холстов радиусо-зависимых графиков (3 холста на каждый заряд)
        c_R_vs_kt[i] = { 
            new TCanvas(("c_radius_vs_kt_3d_" + chargeNames[i] + "_out").c_str(),  ("R_{out} vs k_t (3D) " + chargeNames[i]).c_str(), 900, 700),
            new TCanvas(("c_radius_vs_kt_3d_" + chargeNames[i] + "_side").c_str(), ("R_{side} vs k_t (3D) " + chargeNames[i]).c_str(), 900, 700),
            new TCanvas(("c_radius_vs_kt_3d_" + chargeNames[i] + "_long").c_str(), ("R_{long} vs k_t (3D) " + chargeNames[i]).c_str(), 900, 700)
        };
    }
    
    // Создаем функцию для 3D-фитирования корреляционной функции (с 4 параметрами: R_out, R_side, R_long, λ)
    TF3* fit3d = new TF3("fit3d", CF_fit_3d, -0.1, 0.1, -0.1, 0.1, -0.1, 0.1, 4);
    fit3d->SetParameter(0, 5.5);  fit3d->SetParLimits(0, 2, 8.0);
    fit3d->SetParameter(1, 4.2);  fit3d->SetParLimits(1, 2, 8.0);
    fit3d->SetParameter(2, 3.8);  fit3d->SetParLimits(2, 2, 8.0);
    fit3d->SetParameter(3, 0.9);  fit3d->SetParLimits(3, 0.7, 1.1);
    
    // Мультиграфы для значений λ и радиусов (R_out, R_side, R_long) в зависимости от k_t (массивы на 2 заряда)
    std::array<TMultiGraph*, 2> mg_lambda;
    std::array<TMultiGraph*, 2> mg_R_out;
    std::array<TMultiGraph*, 2> mg_R_side;
    std::array<TMultiGraph*, 2> mg_R_long;
    
    // Внешний цикл по заряду k: 0 = pos, 1 = neg
    for (unsigned int k = 0; k < 1; ++k) {
        // Создаем мультиграфы для данного заряда
        mg_lambda[k] = new TMultiGraph();
        mg_R_out[k]  = new TMultiGraph();
        mg_R_side[k] = new TMultiGraph();
        mg_R_long[k] = new TMultiGraph();
        
        // Внутренний цикл по центральностям i
        for (unsigned int i = 0; i < centralityNames.size(); ++i) {
            // Временные графики погрешностей для данной центральности (будут содержать 4 точки по k_t)
            TGraphErrors* g_lambda = new TGraphErrors();
            TGraphErrors* g_R_out  = new TGraphErrors();
            TGraphErrors* g_R_side = new TGraphErrors();
            TGraphErrors* g_R_long = new TGraphErrors();

            g_R_out->SetLineColor(colors[i]);
            g_R_out->SetMarkerColor(colors[i]);
            g_R_out->SetMarkerStyle(markers[i]);

            g_R_side->SetLineColor(colors[i]);
            g_R_side->SetMarkerColor(colors[i]);
            g_R_side->SetMarkerStyle(markers[i]);

            g_R_long->SetLineColor(colors[i]);
            g_R_long->SetMarkerColor(colors[i]);
            g_R_long->SetMarkerStyle(markers[i]);

            g_lambda->SetLineColor(colors[i]);
            g_lambda->SetMarkerColor(colors[i]);
            g_lambda->SetMarkerStyle(markers[i]);
            
            // Цикл по k_t бинам j
            for (unsigned int j = 0; j < ktNames.size(); ++j) {
                gStyle->SetOptStat(0);  // отключаем статистические окна на графиках
                
                // Составляем суффикс для имен гистограмм (k, i, без j)
                std::string suffix = chargeNames[k] + "_" + centralityNames[i] + "_" + ktNames[j] + "_GeVc";
                // Получаем 3D-гистограммы (A и A_wei) из входного файла
                TH3D* h_A    = (TH3D*) inputFile->Get(("h3d_A_q_" + suffix).c_str());
                TH3D* h_A_wei= (TH3D*) inputFile->Get(("h3d_A_wei_q_" + suffix).c_str());
                if (!h_A || !h_A_wei) {
                    // Если данных нет, переходим к следующему j
                    continue;
                }
                // Создаем новую 3D-гистограмму для CF = A_wei / A с тем же бинированием, что и у входных
                std::string hname = "h3d_CF_q_" + suffix;
                TH3D* h_CF = (TH3D*) h_A_wei->Clone(hname.c_str());
                h_CF->Reset();
                h_CF->Divide(h_A_wei, h_A);
                h_CF->SetDirectory(nullptr);
                histList.push_back(h_CF);
                
                // Размещаем гистограмму CF на соответствующей паде холста c_all_3d_CF
                c_all_3d_CF[k]->cd(4 * i + j + 1);
                h_CF->GetXaxis()->SetRangeUser(-0.4, 0.4);
                h_CF->GetYaxis()->SetRangeUser(-0.4, 0.4);
                h_CF->GetZaxis()->SetRangeUser(-0.4, 0.4);
                h_CF->GetXaxis()->SetTitleOffset(0.8);
                h_CF->Draw("BOX2");  // рисуем 3D CF как цветной куб (BOX2)
                
                // Выполняем фит 3D гистограммы нашей функцией fit3d, получаем параметры R_out, R_side, R_long, λ
                h_CF->Fit(fit3d, "RM");  // "M" – улучшенный расчет погрешностей
                
                double xval = (ktvalues[j+1] + ktvalues[j]) / 2.0;
                double xerr = ktvalues[j+1] - xval;
                // Сохраняем λ (параметр3) и радиусы (параметры0,1,2) с погрешностями для текущего k_t
                g_lambda->SetPoint(j, xval, fit3d->GetParameter(3));
                g_lambda->SetPointError(j, xerr, fit3d->GetParError(3));
                g_R_out->SetPoint(j, xval, fit3d->GetParameter(0));
                g_R_out->SetPointError(j, xerr, fit3d->GetParError(0));
                g_R_side->SetPoint(j, xval, fit3d->GetParameter(1));
                g_R_side->SetPointError(j, xerr, fit3d->GetParError(1));
                g_R_long->SetPoint(j, xval, fit3d->GetParameter(2));
                g_R_long->SetPointError(j, xerr, fit3d->GetParError(2));
                
                // Строим проекции CF на 1D оси (out, side, long) и 2D плоскости (out-side, out-long, side-long)
                ProjectAndDraw1D(inputFile, c_all_3d_CF_proj_out[k],  c_1DCF_min[k], fit3d, i, j, 1, axis[0], LCMS[0], suffix);
                ProjectAndDraw1D(inputFile, c_all_3d_CF_proj_side[k], c_1DCF_min[k], fit3d, i, j, 2, axis[1], LCMS[1], suffix);
                ProjectAndDraw1D(inputFile, c_all_3d_CF_proj_long[k], c_1DCF_min[k], fit3d, i, j, 3, axis[2], LCMS[2], suffix);
                ProjectAndDraw2D(inputFile, c_2DCF_out_vs_side[k], c_2DCF_min[k], i, j, axis[0] + axis[1], LCMS[0], LCMS[1], suffix, 1);
                ProjectAndDraw2D(inputFile, c_2DCF_out_vs_long[k], c_2DCF_min[k], i, j, axis[0] + axis[2], LCMS[0], LCMS[2], suffix, 2);
                ProjectAndDraw2D(inputFile, c_2DCF_side_vs_long[k], c_2DCF_min[k], i, j, axis[1] + axis[2], LCMS[1], LCMS[2], suffix, 3);
            }
            // (При необходимости можно удалить некоторые точки графиков на основе условий, закомментировано)
            if(i == 2){
                g_R_out->RemovePoint(3);
                g_R_side->RemovePoint(3);
                g_R_long->RemovePoint(3);
                g_lambda->RemovePoint(3);
            }
            if(i == 3){
                g_R_out->RemovePoint(3);     g_R_out->RemovePoint(2);         g_R_out->RemovePoint(1);
                g_R_side->RemovePoint(3);    g_R_side->RemovePoint(2);        g_R_side->RemovePoint(1);
                g_R_long->RemovePoint(3);    g_R_long->RemovePoint(2);        g_R_long->RemovePoint(1);
                g_lambda->RemovePoint(3);    g_lambda->RemovePoint(2);        g_lambda->RemovePoint(1);
            }
            // Добавляем полученные графики R_out, R_side, R_long, λ в мультиграфы и легенды
            mg_R_out[k]->Add(g_R_out, "lp");
            mg_R_side[k]->Add(g_R_side, "lp");
            mg_R_long[k]->Add(g_R_long, "lp");
            mg_lambda[k]->Add(g_lambda, "lp");
            l_R[k][0]->AddEntry(g_R_out,   (std::string("R_{out} ")  + centralityNames[i] + "%").c_str(),  "lp");
            l_R[k][1]->AddEntry(g_R_side,  (std::string("R_{side} ") + centralityNames[i] + "%").c_str(),  "lp");
            l_R[k][2]->AddEntry(g_R_long,  (std::string("R_{long} ") + centralityNames[i] + "%").c_str(),  "lp");
            l_lambda[k]->AddEntry(g_lambda, (std::string("#lambda ") + centralityNames[i] + "%").c_str(), "lp");
        }
        // После заполнения всех графиков для данного заряда – рисуем их на комбинированных холстах
        // Рисуем графики радиусов и λ на холсте c_ROSL_lambda (4x4 подложек, где 1-3 пады – радиусы, 4-я – λ)
        c_ROSL_lambda[k]->cd(1); mg_R_out[k]->Draw("ALP");   l_R[k][0]->Draw("SAME");
        c_ROSL_lambda[k]->cd(2); mg_R_side[k]->Draw("ALP");  l_R[k][1]->Draw("SAME");
        c_ROSL_lambda[k]->cd(3); mg_R_long[k]->Draw("ALP");  l_R[k][2]->Draw("SAME");
        c_ROSL_lambda[k]->cd(4); mg_lambda[k]->Draw("ALP");  l_lambda[k]->Draw("SAME");
        // Рисуем объединенные мультиграфы на холсте c_out_side_long_lambda (2x2 подложки)
        draw_mg_on_c(c_out_side_long_lambda[k], mg_R_out[k],   l_R[k][0], "R_{out}",  1, 2, 7, ("R_{" + LCMS[0] + "} [fm]").c_str());
        draw_mg_on_c(c_out_side_long_lambda[k], mg_R_side[k],  l_R[k][1], "R_{side}", 2, 2, 5, ("R_{" + LCMS[1] + "} [fm]").c_str());
        draw_mg_on_c(c_out_side_long_lambda[k], mg_R_long[k],  l_R[k][2], "R_{long}", 3, 2, 5, ("R_{" + LCMS[2] + "} [fm]").c_str());
        draw_mg_on_c(c_out_side_long_lambda[k], mg_lambda[k],  l_lambda[k], "#lambda", 4, 0.6, 1.2, "#lambda");
        // (Функция draw_mg_on_c условно подразумевает оформление осей и масштабов для наглядности)
        
        // Создаем директорию для PNG-изображений и сохраняем холсты данного заряда
        std::string outputDir = "output_histograms_3d_" + chargeNames[k];
        const char* format    = "png";
        gSystem->Exec(Form("mkdir -p %s", outputDir.c_str()));
        c_all_3d_CF[k]->SaveAs(Form("%s/c_all_3d_CF.%s", outputDir.c_str(), format));
        c_out_side_long_lambda[k]->SaveAs(Form("%s/c_out_side_long_lambda.%s", outputDir.c_str(), format));
        c_ROSL_lambda[k]->SaveAs(Form("%s/c_ROSL_lambda.%s", outputDir.c_str(), format));
        c_1DCF_min[k]->SaveAs(Form("%s/c_1DCF_min.%s", outputDir.c_str(), format));
        c_2DCF_min[k]->SaveAs(Form("%s/c_2DCF_min.%s", outputDir.c_str(), format));
        c_all_3d_CF_proj_out[k]->SaveAs(Form("%s/c_all_3d_CF_proj_out.%s", outputDir.c_str(), format));
        c_all_3d_CF_proj_side[k]->SaveAs(Form("%s/c_all_3d_CF_proj_side.%s", outputDir.c_str(), format));
        c_all_3d_CF_proj_long[k]->SaveAs(Form("%s/c_all_3d_CF_proj_long.%s", outputDir.c_str(), format));
        c_2DCF_out_vs_side[k]->SaveAs(Form("%s/c_2DCF_out_vs_side.%s", outputDir.c_str(), format));
        c_2DCF_out_vs_long[k]->SaveAs(Form("%s/c_2DCF_out_vs_long.%s", outputDir.c_str(), format));
        c_2DCF_side_vs_long[k]->SaveAs(Form("%s/c_2DCF_side_vs_long.%s", outputDir.c_str(), format));
    }
    
    // Закрываем входной файл
    inputFile->Close();
    
    // Создаем выходной ROOT-файл и сохраняем в него все холсты (и связанные объекты)
    TFile* outputFile3D = new TFile("3d_CF_pos_and_neg.root", "RECREATE");
    if (!outputFile3D || outputFile3D->IsZombie()) {
        std::cerr << "Error creating output file for 3D histograms!" << std::endl;
    } else {
        for (unsigned int i = 0; i < 1; ++i) {
            c_all_3d_CF[i]->Write();
            c_lambda_vs_kt[i]->Write();
            c_all_3d_CF_proj_out[i]->Write();
            c_all_3d_CF_proj_side[i]->Write();
            c_all_3d_CF_proj_long[i]->Write();
            c_2DCF_out_vs_side[i]->Write();
            c_2DCF_out_vs_long[i]->Write();
            c_2DCF_side_vs_long[i]->Write();
            c_1DCF_min[i]->Write();
            c_2DCF_min[i]->Write();
            c_ROSL_lambda[i]->Write();
            c_out_side_long_lambda[i]->Write();
            // Холсты с радиусами vs k_t
            for (unsigned int j = 0; j < LCMS.size(); ++j) {
                c_R_vs_kt[i][j]->Write();
            }
        }
    }
    outputFile3D->Close();
    delete outputFile3D;
    
    // // Удаляем все динамически созданные объекты, чтобы освободить память:
    // // 1. Удаляем все холсты (TCanvas)
    // for (unsigned int i = 0; i < chargeNames.size(); ++i) {
    //     delete c_all_3d_CF[i];
    //     delete c_lambda_vs_kt[i];
    //     delete c_all_3d_CF_proj_out[i];
    //     delete c_all_3d_CF_proj_side[i];
    //     delete c_all_3d_CF_proj_long[i];
    //     delete c_2DCF_out_vs_side[i];
    //     delete c_2DCF_out_vs_long[i];
    //     delete c_2DCF_side_vs_long[i];
    //     delete c_1DCF_min[i];
    //     delete c_2DCF_min[i];
    //     delete c_ROSL_lambda[i];
    //     delete c_out_side_long_lambda[i];
    //     // Холсты c_R_vs_kt хранятся в map
    //     for (unsigned int j = 0; j < LCMS.size(); ++j) {
    //         delete c_R_vs_kt[i][j];
    //     }
    // }
    // c_R_vs_kt.clear();
    // // 2. Удаляем мультиграфы (удаление освободит включенные TGraphErrors)
    // for (unsigned int k = 0; k < 2; ++k) {
    //     delete mg_lambda[k];
    //     delete mg_R_out[k];
    //     delete mg_R_side[k];
    //     delete mg_R_long[k];
    // }
    // // 3. Удаляем легенды
    // for (unsigned int k = 0; k < 2; ++k) {
    //     for (unsigned int j = 0; j < LCMS.size(); ++j) {
    //         delete l_R[k][j];
    //     }
    //     delete l_lambda[k];
    // }
    // l_R.clear();
    // // 4. Удаляем все временные гистограммы (TH1/TH2/TH3), сохраненные в списке histList
    // for (TH1* hist : histList) {
    //     delete hist;
    // }
    // histList.clear();
    // // 5. Удаляем функцию фитирования 3D
    // delete fit3d;
}
