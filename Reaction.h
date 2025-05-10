#ifndef REACTION_H
#define REACTION_H

#include <vector>
#include <iostream>

// Forward declaration of Agent
template <typename ValueType>
class Agent;

template <typename ValueType>
class Reaction {
    std::vector<Agent<ValueType>> reactants;
    std::vector<Agent<ValueType>> products;
    ValueType rate;

public:
    // Constructor
    Reaction(const std::vector<Agent<ValueType>>& reactants, const ValueType& rate, const std::vector<Agent<ValueType>>& products)
        : reactants(reactants), rate(rate), products(products) {}

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
    }
};

#endif // REACTION_H