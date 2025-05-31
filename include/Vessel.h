#ifndef VESSEL_H
#define VESSEL_H

#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include "Reaction.h"
#include "SymbolTable.h"
#include "Agent.h"


// Overload >> for a single Agent
template<typename ValueType>
std::pair<std::vector<Agent<ValueType> >, double> operator>>(const Agent<ValueType> &reactant, const double &rate) {
    return {{reactant}, rate};
}

// Overload >> for std::vector<Agent<ValueType>>
template<typename ValueType>
std::pair<std::vector<Agent<ValueType> >, double> operator>>(const std::vector<Agent<ValueType> > &reactants,
                                                             const double &rate) {
    return {reactants, rate};
}

// Overload >>= for a single product
template<typename ValueType>
Reaction<ValueType> operator>>=(const std::pair<std::vector<Agent<ValueType> >, double> &intermediate,
                                const Agent<ValueType> &product) {
    return Reaction<ValueType>(intermediate.first, intermediate.second, {product});
}

// Overload >>= for multiple products
template<typename ValueType>
Reaction<ValueType> operator>>=(const std::pair<std::vector<Agent<ValueType> >, double> &intermediate,
                                const std::vector<Agent<ValueType> > &products) {
    return Reaction<ValueType>(intermediate.first, intermediate.second, products);
}

template<typename ValueType>
class Vessel {
    std::string name;
    SymbolTable<std::string, ValueType> agentState;
    std::vector<Reaction<ValueType> > reactions;

public:
    explicit Vessel(const std::string &vesselName) : name(vesselName) {
    }

    Agent<ValueType> add(const std::string &itemName, const ValueType &initialValue) {
        if (!agentState.insert(itemName, initialValue)) {
            throw std::runtime_error("Error: Item '" + itemName + "' already exists in the vessel.");
        }
        return Agent<ValueType>(itemName, agentState.lookup(itemName).value());
    }

    void add(const Reaction<ValueType> &reaction) {
        reactions.push_back(reaction);
    }

    void printItems() const {
        std::cout << "Vessel: " << name << "\n";
        agentState.print();
        for (const auto &reaction: reactions) {
            reaction.print();
        }
    }

    void beginSimulation(double maxTime) {
        for (double time = 0; time < maxTime;) {
            for (auto& reaction: reactions) {
                reaction.delay = reaction.getDelay(agentState);
                std::cout << "Reaction delay for " << reaction.reactants.size() << " reactants: " << reaction.delay << "\n";
            }
            auto selectedIt = std::min_element(
                reactions.begin(), reactions.end(),
                [](const Reaction<ValueType> &a, const Reaction<ValueType> &b) {
                    return a.delay < b.delay;
                }
            );

            if (selectedIt != reactions.end()) {
                Reaction<ValueType> &selectedReaction = *selectedIt;
                time += selectedReaction.delay;

                // Check if all reactants have value > 0
                // [this] is used so the lambda inside a member function can access this->agentState, which is a member variable of the class. Without capturing this, the lambda cannot access class members.
                bool allAvailable = std::all_of(
                    selectedReaction.reactants.begin(),
                    selectedReaction.reactants.end(),
                    [this](const Agent<ValueType> &agent) {
                        auto valOpt = this->agentState.lookup(agent.getName());
                        return valOpt.has_value() && valOpt.value() > 0;
                    }
                );

                if (allAvailable) {
                    // Decrease each reactant by 1
                    for (const Agent<ValueType> &inputAgent: selectedReaction.reactants) {
                        agentState.decrement(inputAgent.getName());
                    }

                    // Increase each product by 1
                    for (const auto &outputAgent: selectedReaction.products) {
                        agentState.increment(outputAgent.getName());
                    }

                    // Print the reaction
                    std::cout << "Time: " << time << ", Agent State: ";
                    agentState.print();
                } else {
                    // Skip or handle unavailable reactants
                }
            }
        }
    }
};

#endif // VESSEL_H
