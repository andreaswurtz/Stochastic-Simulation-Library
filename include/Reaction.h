#ifndef REACTION_H
#define REACTION_H

#include <vector>
#include <iostream>
#include <random>

// Forward declaration of Agent
template <typename ValueType>
class Agent;

template <typename ValueType>
class Reaction {
    std::vector<Agent<ValueType>> reactants;
    std::vector<Agent<ValueType>> products;
    double rate;
    double delay = 0.0;

public:
    // Constructor
    Reaction(const std::vector<Agent<ValueType>>& reactants, const ValueType& rate, const std::vector<Agent<ValueType>>& products)
        : reactants(reactants), products(products), rate(rate) {}

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
        std::cout << "\n";
        std::cout << "Product of reactants: " << calculateReactantProduct() << "\n";
        std::cout << "Delay: " << getDelay() << "\n";


    }

    // Calculate the product of reactant values
    double calculateReactantProduct() const {
        return std::accumulate(
            reactants.begin(), reactants.end(), 1.0,
            [](double acc, const Agent<ValueType>& agent) {
                return acc * agent.get(); // Multiply the current value
            }
        );
    }

#include <limits> // For std::numeric_limits

    double getDelay() const {
        double product = calculateReactantProduct();

        // If any reactant is exhausted, return infinite delay
        if (product == 0.0) {
            return std::numeric_limits<double>::infinity();
        }

        // Calculate the rate parameter for the exponential distribution
        double lambda = rate * product;

        // Generate the delay using the exponential distribution
        std::default_random_engine generator; // Random number generator
        std::exponential_distribution<double> distribution(lambda);
        return distribution(generator);
    }
};

#endif // REACTION_H