#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TPaveText.h>
#include <TSystem.h>
#include <TStyle.h>
#include <iostream>
#include <array>
#include <string>

// Функция для гауссового фитирования корреляционной функции (1 + lambda * exp(-q^2 * R^2 / (ħc)^2))
Double_t gaussian(Double_t *x, Double_t *par) {
    Double_t arg = -1 * (x[0] * par[1] / 0.197) * (x[0] * par[1] / 0.197);
    Double_t fitval = 1 + par[0] * TMath::Exp(arg);
    return fitval;
}

// Вспомогательная функция оформления графика и добавления его в мультиграф и легенду
void make_style(TGraphErrors* graph, TMultiGraph* multigraph, TLegend* legend,
                int m_style, double m_size, int m_color, int l_color, std::string title) {
    graph->SetMarkerStyle(m_style);
    graph->SetMarkerSize(m_size);
    graph->SetMarkerColor(m_color);
    graph->SetLineColor(l_color);
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitleSize(0.05);
    graph->GetYaxis()->SetTitleSize(0.05);
    legend->AddEntry(graph, title.c_str(), "lp");
    multigraph->Add(graph, "lp");
}

// Основная функция обработки 1D-гистограмм
void process_1d_histograms(const char* fileName) {
    TFile* inputFile = TFile::Open(fileName, "READ");
    if (!inputFile || inputFile->IsZombie()) {
        std::cerr << "Error opening file " << fileName << std::endl;
        return;
    }
    
    const std::array<std::string, 4> centralityNames = {"0-10", "10-30", "30-50", "50-80"};
    const std::array<std::string, 4> ktNames         = {"0.15-0.25", "0.25-0.35", "0.35-0.45", "0.45-0.60"};
    const std::array<double, 5>      ktvalues        = {0.15, 0.25, 0.35, 0.45, 0.60};
    const std::array<int, 4>         colors          = {kRed, kBlue, kMagenta, kGreen};
    const std::array<std::string, 2> chargeNames          = {"pos", "neg"};
    
    // Создание полотен для всех 1D CF (положительные и отрицательные заряды) с разбивкой на пады
    TCanvas* c_all_1d_CF = new TCanvas("c_all_1d_CF", "All 1D CFs", 900, 700);
    TCanvas* c_all_1d_CF_pos = new TCanvas("c_all_1d_CF_pos", "All 1D CFs pos", 900, 700);
    c_all_1d_CF_pos->Divide(4, 4);
    TCanvas* c_all_1d_CF_neg = new TCanvas("c_all_1d_CF_neg", "All 1D CFs neg", 900, 700);
    c_all_1d_CF_neg->Divide(4, 4);
    
    // Полотна для R_inv vs k_t и lambda vs k_t (отдельно для положительных и отрицательных частиц)
    TCanvas* c_Rinv_vs_kt_pos   = new TCanvas("c_Rinv_vs_kt_pos", "Rinv vs kt pos", 900, 700);
    TCanvas* c_Rinv_vs_kt_neg   = new TCanvas("c_Rinv_vs_kt_neg", "Rinv vs kt neg", 900, 700);
    TCanvas* c_lambda_vs_kt_pos = new TCanvas("c_lambda_vs_kt_pos", "lambda vs kt pos", 900, 700);
    TCanvas* c_lambda_vs_kt_neg = new TCanvas("c_lambda_vs_kt_neg", "lambda vs kt neg", 900, 700);

    // Дополнительные холсты для специальных графиков
    TCanvas* c_1d_CF_4_center_pos = new TCanvas("c_1d_CF_4_center", "CF_{1d} 4 center", 900, 700);
    TCanvas* c_1d_CF_4_center_neg = new TCanvas("c_1d_CF_4_center", "CF_{1d} 4 center", 900, 700);
    TLegend* l_CF_4_center = new TLegend(0.5, 0.7, 0.9, 0.9);

    TLegend* l_CF_4_kt = new TLegend(0.5, 0.7, 0.9, 0.9);

    // Холст для "минимального" (0-10%, 0.15-0.25 GeV/c) случая
    TCanvas* c_1d_CF_at_min = new TCanvas("c_1d_CF_at_min", "CF at min kt/centr", 1200, 400);
    c_1d_CF_at_min->Divide(3, 2); // три пада: A, A_wei, CF

    TCanvas* c_1d_CF_4_kt_pos = new TCanvas("c_1d_CF_4_kt_pos", "CF_{1d} 4 kt pos", 900, 700);
    TCanvas* c_1d_CF_4_kt_neg = new TCanvas("c_1d_CF_4_kt_neg", "CF_{1d} 4 kt neg", 900, 700);
    
    // Легенды для графиков R_inv и lambda (для положительных и отрицательных частиц)
    TLegend* l_Rinv_pos   = new TLegend(0.5, 0.7, 0.9, 0.9);
    TLegend* l_Rinv_neg   = new TLegend(0.5, 0.7, 0.9, 0.9);
    TLegend* l_lambda_pos = new TLegend(0.5, 0.7, 0.9, 0.9);
    TLegend* l_lambda_neg = new TLegend(0.5, 0.7, 0.9, 0.9);
    
    // Мультиграфы для объединения графиков разных центральностей (R_inv и lambda для pos/neg)
    TMultiGraph* mg_Rinv_pos   = new TMultiGraph();
    TMultiGraph* mg_Rinv_neg   = new TMultiGraph();
    TMultiGraph* mg_lambda_pos = new TMultiGraph();
    TMultiGraph* mg_lambda_neg = new TMultiGraph();
    // (По умолчанию TMultiGraph владеет добавляемыми графиками, их удаление произойдет при удалении мультиграфа)
    
    // Функция для фитирования 1D корреляционной функции (гауссовский параметризация)
    TF1* fit = new TF1("fit", gaussian, 0.0, 0.05, 2);
    fit->SetParameter(0, 0.5);  fit->SetParLimits(0, 0.0, 1.0);
    fit->SetParameter(1, 4.5);  fit->SetParLimits(1, 0.0, 10.0);
    
    // Вектор для хранения указателей на временные гистограммы CF, чтобы затем их удалить
    std::vector<TH1D*> histCFList;
    
    // Цикл по заряду: k = 0 (pos), k = 1 (neg)
    for (unsigned int k = 0; k < 1; ++k) {
        // Цикл по центральностям
        for (unsigned int i = 0; i < centralityNames.size(); ++i) {
            // Создаем временные графики погрешностей для данной центральности (будут заполнены для всех k_t)
            TGraphErrors* g_tmp_Rinv   = new TGraphErrors();
            TGraphErrors* g_tmp_lambda = new TGraphErrors();
            
            // Цикл по диапазонам k_t
            for (unsigned int j = 0; j < ktNames.size(); ++j) {
                // Формируем базовую часть имени гистограммы (без индекса k_t)
                std::string suffix = chargeNames[k] + "_" + centralityNames[i] + "_" + ktNames[j] + "_GeVc";
                // Получаем гистограммы из файла: без весов (A) и с весами (A_wei) для данного k, i, j
                TH1D* h_A    = (TH1D*) inputFile->Get(("h_A_q_inv_" + suffix).c_str());
                TH1D* h_A_wei= (TH1D*) inputFile->Get(("h_A_wei_q_inv_" + suffix).c_str());
                
                if (!h_A || !h_A_wei) {
                    std::cerr << "Warning: input histograms for k=" << k << ", i=" << i << ", j=" << j << " not found!" << std::endl;
                    continue;  // пропускаем, если одна из гистограмм не найдена
                }
                
                // Создаем гистограмму корреляционной функции CF = A_wei / A.
                // Используем Clone от h_A_wei для совпадения числа бин и диапазона, затем Reset для очистки.
                TH1D* hist_CF = (TH1D*) h_A_wei->Clone(("CF(q_inv)_" + suffix).c_str());
                hist_CF->Reset();
                hist_CF->Divide(h_A_wei, h_A);         // делим взвешенную и невзвешенную гистограммы
                hist_CF->SetDirectory(nullptr);        // отвязываем от файла, чисто в памяти
                histCFList.push_back(hist_CF);         // сохраняем указатель для последующего удаления
                
                // Размещаем результат на соответствующем паде объединенного полотна
                if (k == 0) {
                    c_all_1d_CF_pos->cd(4 * i + j + 1);
                } else {
                    c_all_1d_CF_neg->cd(4 * i + j + 1);
                }
                
                // Настраиваем оформление гистограммы CF
                hist_CF->SetTitle(("CF(q_{inv}) " + centralityNames[i] + "%, " + ktNames[j] + " GeV/c").c_str());
                hist_CF->GetXaxis()->SetTitle("q_{inv} [GeV/c]");
                hist_CF->GetYaxis()->SetTitle("CF");
                hist_CF->GetXaxis()->SetRangeUser(0.0, 0.3);
                hist_CF->GetYaxis()->SetRangeUser(0.8, 2.0);
                hist_CF->SetMarkerColor(colors[i]);
                hist_CF->SetLineColor(colors[i]);
                hist_CF->SetMarkerStyle(20 + j);
                hist_CF->SetMarkerSize(0.8);
                hist_CF->Draw("P");  // рисуем точки на паде
                
                // Вычисляем средний k_t и погрешность по k_t для текущего бина
                double xval = (ktvalues[j+1] + ktvalues[j]) / 2.0;
                double xerr = ktvalues[j+1] - xval;
                
                // Фитируем полученную корреляционную функцию 1D-функцией (gaussian) и находим параметры
                hist_CF->Fit(fit, "RM");  // "R": в диапазоне гистограммы, "M": улучшенный расчет погрешностей
                
                // Сохраняем результаты фитирования: R_inv (параметр1) и λ (параметр0) с погрешностями
                g_tmp_Rinv->SetPoint(j, xval, fit->GetParameter(1));
                g_tmp_Rinv->SetPointError(j, xerr, fit->GetParError(1));
                g_tmp_lambda->SetPoint(j, xval, fit->GetParameter(0));
                g_tmp_lambda->SetPointError(j, xerr, fit->GetParError(0));

                if (i == 0) {
                    TH1D h_tmp_CF = TH1D(hist_CF); 
                    c_1d_CF_4_center_pos->cd();
                    hist_CF->Draw("P SAME");
                    l_CF_4_center->AddEntry(hist_CF, ("CF at k_{t}" + ktNames[j] + "GeV/c").c_str(), "lp");
                }

                if (i == 0 && j == 0) {
                    TH1D* h_A_file = (TH1D*)inputFile->Get(("h_A_q_inv_" + suffix).c_str());
                    if (h_A_file) {
                        TH1D* h_A_min_kt_center = new TH1D(*h_A_file);
                        h_A_min_kt_center->SetDirectory(nullptr); // <-- критически важно!
                        h_A_min_kt_center->SetTitle(("A(q_{inv})_" + suffix).c_str());
                        c_1d_CF_at_min->cd(1); h_A_min_kt_center->Draw("P");
                        // не добавляем в вектор для удаления!
                    }
                    TH1D* h_A_wei_file = (TH1D*)inputFile->Get(("h_A_wei_q_inv_" + suffix).c_str());
                    if (h_A_wei_file) {
                        TH1D* h_A_wei_min_kt_center = new TH1D(*h_A_wei_file);
                        h_A_wei_min_kt_center->SetDirectory(nullptr);
                        h_A_wei_min_kt_center->SetTitle(("A_{wei}(q_{inv})_" + suffix).c_str());
                        c_1d_CF_at_min->cd(2); h_A_wei_min_kt_center->Draw("P");
                    }
                    if (hist_CF) {
                        TH1D* h_C_wei_min_kt_center = new TH1D(*hist_CF);
                        h_C_wei_min_kt_center->SetDirectory(nullptr);
                        h_C_wei_min_kt_center->SetName("h_C_wei");
                        c_1d_CF_at_min->cd(3); h_C_wei_min_kt_center->Draw("P");
                    }
                }                
                
            }
            // После заполнения графиков для всех k_t бинов – добавляем их в мультиграф и легенду
            if (k == 0) {
                make_style(g_tmp_Rinv,   mg_Rinv_pos,   l_Rinv_pos,   21, 1.0, colors[i], colors[i], "R_{inv} " + centralityNames[i] + "% pos");
                make_style(g_tmp_lambda, mg_lambda_pos, l_lambda_pos, 20, 1.0, colors[i], colors[i], "#lambda " + centralityNames[i] + "% pos");
            } else {
                make_style(g_tmp_Rinv,   mg_Rinv_neg,   l_Rinv_neg,   21, 1.0, colors[i], colors[i], "R_{inv} " + centralityNames[i] + "% neg");
                make_style(g_tmp_lambda, mg_lambda_neg, l_lambda_neg, 20, 1.0, colors[i], colors[i], "#lambda " + centralityNames[i] + "% neg");
            }
            // (Примечание: make_style устанавливает стиль графика, добавляет его в мультиграф и легенду, см. выше)
        }
    }
    
    // Устанавливаем заголовки для мультиграфиков (оси и названия)
    mg_Rinv_pos->SetTitle("R_{inv}(k_{t});k_{t} [GeV/c]; R_{inv} [fm]");
    mg_Rinv_neg->SetTitle("R_{inv}(k_{t});k_{t} [GeV/c]; R_{inv} [fm]");
    mg_lambda_pos->SetTitle("#lambda(k_{t});k_{t} [GeV/c]; #lambda");
    mg_lambda_neg->SetTitle("#lambda(k_{t});k_{t} [GeV/c]; #lambda");
    
    // Рисуем мультиграфики на соответствующих холстах и добавляем легенды
    c_Rinv_vs_kt_pos->cd();
    mg_Rinv_pos->Draw("ALP");
    l_Rinv_pos->Draw("SAME");
    
    c_Rinv_vs_kt_neg->cd();
    mg_Rinv_neg->Draw("ALP");
    l_Rinv_neg->Draw("SAME");
    
    c_lambda_vs_kt_pos->cd();
    mg_lambda_pos->Draw("ALP");
    l_lambda_pos->Draw("SAME");
    
    c_lambda_vs_kt_neg->cd();
    mg_lambda_neg->Draw("ALP");
    l_lambda_neg->Draw("SAME");

    c_1d_CF_4_center_pos->cd();
    l_CF_4_center->Draw("SAME");
    
    // Сохраняем полученные холсты как изображения (PNG) в папку output_histograms_1d
    gSystem->Exec("mkdir -p output_histograms_1d");
    c_all_1d_CF_pos->SaveAs("output_histograms_1d/c_all_1d_CF_pos.png");
    c_all_1d_CF_neg->SaveAs("output_histograms_1d/c_all_1d_CF_neg.png");
    c_Rinv_vs_kt_pos->SaveAs("output_histograms_1d/c_Rinv_vs_kt_pos.png");
    c_Rinv_vs_kt_neg->SaveAs("output_histograms_1d/c_Rinv_vs_kt_neg.png");
    c_lambda_vs_kt_pos->SaveAs("output_histograms_1d/c_lambda_vs_kt_pos.png");
    c_lambda_vs_kt_neg->SaveAs("output_histograms_1d/c_lambda_vs_kt_neg.png");
    c_1d_CF_4_center_pos->SaveAs("output_histograms_1d/c_1d_CF_4_center_pos.png");
    c_1d_CF_4_center_neg->SaveAs("output_histograms_1d/c_1d_CF_4_center_neg.png");
    c_1d_CF_at_min->SaveAs("output_histograms_1d/c_1d_CF_at_min.png"); 
    
    // Закрываем входной файл с гистограммами
    inputFile->Close();
    
    // Открываем выходной файл для сохранения всех холстов (перезапись при существовании)
    TFile* outputFile1D = new TFile("1d_CF_pos_and_neg.root", "RECREATE");
    if (!outputFile1D || outputFile1D->IsZombie()) {
        std::cerr << "Error creating output file for 1D histograms!" << std::endl;
    } else {
        // Записываем все созданные холсты в выходной ROOT-файл
        c_all_1d_CF_pos->Write();
        c_all_1d_CF_neg->Write();
        c_Rinv_vs_kt_pos->Write();
        c_Rinv_vs_kt_neg->Write();
        c_lambda_vs_kt_pos->Write();
        c_lambda_vs_kt_neg->Write();
        c_1d_CF_4_center_pos->Write();
        c_1d_CF_4_center_neg->Write();
        c_1d_CF_at_min->Write();
    }
    outputFile1D->Close();
}
