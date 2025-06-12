#ifndef REACTION_H
#define REACTION_H

#include <vector>
#include <iostream>
#include <random>
#include <limits> // For std::numeric_limits

#include "SymbolTable.h"

// Forward declaration of Agent
template <typename ValueType>
class Agent;

template <typename ValueType>
class Reaction {


public:
    double delay = 0.0;
    std::vector<Agent<ValueType>> reactants;
    std::vector<Agent<ValueType>> products;
    double rate;
    // Constructor
    Reaction(const std::vector<Agent<ValueType>>& reactants, const double& rate, const std::vector<Agent<ValueType>>& products)
        : reactants(reactants), products(products), rate(rate) {}


    void setDelay(double delay) const { *this.delay = delay; }
    // Print the reaction
    void print() const {
        std::cout << "Reaction: ";
        for (size_t i = 0; i < reactants.size(); ++i) {
            std::cout << reactants[i].getName();
            if (i < reactants.size() - 1) std::cout << " + ";
        }
        std::cout << " >> " << rate << " >>= ";
        for (size_t i = 0; i < products.size(); ++i) {
            std::cout << products[i].getName();
            if (i < products.size() - 1) std::cout << " + ";
        }
        std::cout << std::endl;

    }

    // Calculate the product of reactant values using the current agentState
    double calculateReactantProduct(const SymbolTable<std::string, ValueType>& agentState) const {
        double product = 1.0;
        for (const auto& agent : reactants) {
            auto valOpt = agentState.lookup(agent.getName());
            if (!valOpt.has_value() || valOpt.value() == 0) return 0.0;
            product *= static_cast<double>(valOpt.value());
        }
        return product;
    }

    // Calculate delay using the current agentState
    double getDelay(const SymbolTable<std::string, ValueType>& agentState) const {
        std::random_device rd;
        std::mt19937 gen(rd());

        double product = calculateReactantProduct(agentState);
        if (product == 0.0) {
            return std::numeric_limits<double>::infinity();
        }
        double lambda = rate * product;
        std::exponential_distribution<double> distribution(lambda);
        return distribution(gen);
    }



};

#endif // REACTION_H