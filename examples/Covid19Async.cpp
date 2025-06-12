// #include <iostream>
// #include <vector>
// #include <future>
// #include <numeric>
// #include "../include/Vessel.h"
//
// // Function to run a single simulation and return the peak hospitalization value
// double runSimulation(int N) {
//     double peakHospitalization = 0.0;
//
//     auto trackPeakHospitalization = [&peakHospitalization](double time, const SymbolTable<std::string, double>& agentState) {
//         auto hospitalValue = agentState.lookup("H");
//         if (hospitalValue.has_value()) {
//             peakHospitalization = std::max(peakHospitalization, hospitalValue.value());
//         }
//     };
//
//     Vessel<double> v("COVID19 SEIHR: " + std::to_string(N), trackPeakHospitalization);
//
//     const auto eps = 0.0009;
//     const auto I0 = size_t(std::round(eps * N));
//     const auto E0 = size_t(std::round(eps * N * 15));
//     const auto S0 = N - I0 - E0;
//
//     const auto R0 = 2.4;
//     const auto alpha = 1.0 / 5.1;
//     const auto gamma = 1.0 / 3.1;
//     const auto beta = R0 * gamma;
//     const auto P_H = 0.9e-3;
//     const auto kappa = gamma * P_H * (1.0 - P_H);
//     const auto tau = 1.0 / 10.12;
//
//     const auto S = v.add("S", S0);
//     const auto E = v.add("E", E0);
//     const auto I = v.add("I", I0);
//     const auto H = v.add("H", 0);
//     const auto R = v.add("R", 0);
//
//     v.add((S + I) >> beta / N >>= E + I);
//     v.add(E >> alpha >>= I);
//     v.add(I >> gamma >>= R);
//     v.add(I >> kappa >>= H);
//     v.add(H >> tau >>= R);
//
//     v.beginSimulation(100);
//
//     return peakHospitalization;
// }
//
// int main() {
//     const int numSimulations = 100;
//     const int populationSize = 10000;
//
//     // Vector to store futures
//     std::vector<std::future<double>> futures;
//
//     // Launch simulations in parallel
//     for (int i = 0; i < numSimulations; ++i) {
//         futures.push_back(std::async(std::launch::async, runSimulation, populationSize));
//     }
//
//     // Collect results
//     std::vector<double> peakValues;
//     for (auto& future : futures) {
//         peakValues.push_back(future.get());
//     }
//
//     // Compute average peak hospitalization
//     double averagePeak = std::accumulate(peakValues.begin(), peakValues.end(), 0.0) / peakValues.size();
//
//     std::cout << "Average Peak Hospitalization over " << numSimulations << " simulations: " << averagePeak << "\n";
//
//     return 0;
// }