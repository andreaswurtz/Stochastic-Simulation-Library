// //
// // Created by andreas on 5/31/25.
// //
// #include "../include/Vessel.h"
// #include <QtCharts/QChartView>
// #include <QtCharts/QLineSeries>
// #include <QtCharts/QValueAxis>
// #include <QWidget>
// #include <QVBoxLayout>
//
// #include <QApplication>
// #include "../graphs/qt.hpp"
// #include "../graphs/graphix.hpp"
//
// int main(int argc, char* argv[]) {
//     QApplication app(argc, argv);
//
//     int N = 10000;
//
//     Vessel<double> v("COVID19 SEIHR: " + std::to_string(N));
//
//     const auto eps = 0.0009;                         // initial fraction of infectious
//     const auto I0 = size_t(std::round(eps * N));     // initial infectious
//     const auto E0 = size_t(std::round(eps * N * 15)); // initial exposed
//     const auto S0 = N - I0 - E0;                     // initial susceptible
//
//     const auto R0 = 2.4;                             // basic reproductive number
//     const auto alpha = 1.0 / 5.1;                    // incubation rate (E -> I)
//     const auto gamma = 1.0 / 3.1;                    // recovery rate (I -> R)
//     const auto beta = R0 * gamma;                    // infection/generation rate (S+I -> E+I)
//     const auto P_H = 0.9e-3;                         // probability of hospitalization
//     const auto kappa = gamma * P_H * (1.0 - P_H);    // hospitalization rate (I -> H)
//     const auto tau = 1.0 / 10.12;                    // removal rate in hospital (H -> R)
//
//     const auto S = v.add("S", S0);                   // susceptible
//     const auto E = v.add("E", E0);                   // exposed
//     const auto I = v.add("I", I0);                   // infectious
//     const auto H = v.add("H", 0);                    // hospitalized
//     const auto R = v.add("R", 0);                    // removed/immune
//
//     v.add((S + I) >> beta / N >>= E + I);            // S + I -> E + I
//     v.add(E >> alpha >>= I);                         // E -> I
//     v.add(I >> gamma >>= R);                         // I -> R
//     v.add(I >> kappa >>= H);                         // I -> H
//     v.add(H >> tau >>= R);                           // H -> R
//
//     generateGraphviz(v, "../dotoutput/covid19.dot");
//
//
//     // v.beginSimulation(100);
//     //
//     // auto history = v.getStateHistory();
//     // auto* chartWidget = new StateHistoryChart(history);
//     // chartWidget->resize(800, 600);
//     // chartWidget->show();
//     //
//     // return app.exec();
//     //
//     // return 0;
// }
