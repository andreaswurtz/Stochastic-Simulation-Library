#include <iostream>
#include <vector>
#include <future>
#include <numeric>
#include "../include/Vessel.h"
#include <chrono>

// Function to run a single simulation and return the peak hospitalization value
double runSimulation(int N) {
    double peakHospitalization = 0.0;

    auto trackPeakHospitalization = [&peakHospitalization](double time, const SymbolTable<std::string, double>& agentState) {
        auto hospitalValue = agentState.lookup("H");
        if (hospitalValue.has_value()) {
            peakHospitalization = std::max(peakHospitalization, hospitalValue.value());
        }
    };

    Vessel<double> v("COVID19 SEIHR: " + std::to_string(N), trackPeakHospitalization);

    const auto eps = 0.0009;
    const auto I0 = size_t(std::round(eps * N));
    const auto E0 = size_t(std::round(eps * N * 15));
    const auto S0 = N - I0 - E0;

    const auto R0 = 2.4;
    const auto alpha = 1.0 / 5.1;
    const auto gamma = 1.0 / 3.1;
    const auto beta = R0 * gamma;
    const auto P_H = 0.9e-3;
    const auto kappa = gamma * P_H * (1.0 - P_H);
    const auto tau = 1.0 / 10.12;

    const auto S = v.add("S", S0);
    const auto E = v.add("E", E0);
    const auto I = v.add("I", I0);
    const auto H = v.add("H", 0);
    const auto R = v.add("R", 0);

    v.add((S + I) >> beta / N >>= E + I);
    v.add(E >> alpha >>= I);
    v.add(I >> gamma >>= R);
    v.add(I >> kappa >>= H);
    v.add(H >> tau >>= R);

    v.beginSimulation(100);

    return peakHospitalization;
}

int main() {
    const int numSimulations = 100;
    const int populationSize = 10000;

    using clk = std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::milli;
    using std::cout;
    using std::endl;

    // Benchmark sequential execution
    auto t0 = clk::now();
    std::vector<double> sequentialResults;
    for (int i = 0; i < numSimulations; ++i) {
        sequentialResults.push_back(runSimulation(populationSize));
    }
    auto t1 = clk::now();
    cout << "Time for 100 simulations sequentially: "
         << duration<double, milli>(t1 - t0).count() << " ms\n";

    // Benchmark parallel execution
    t0 = clk::now();
    std::vector<std::future<double>> futures;
    for (int i = 0; i < numSimulations; ++i) {
        futures.push_back(std::async(std::launch::async, runSimulation, populationSize));
    }

    std::vector<double> parallelResults;
    for (auto& future : futures) {
        parallelResults.push_back(future.get());
    }
    t1 = clk::now();
    cout << "Time for 100 simulations in parallel: "
         << duration<double, milli>(t1 - t0).count() << " ms\n";

    // Compute average peak hospitalization for parallel results
    double averagePeak = std::accumulate(parallelResults.begin(), parallelResults.end(), 0.0) / parallelResults.size();
    cout << "Average Peak Hospitalization over " << numSimulations << " simulations: " << averagePeak << "\n";

    return 0;
}