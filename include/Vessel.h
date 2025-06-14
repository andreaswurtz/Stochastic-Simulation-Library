#ifndef VESSEL_H
#define VESSEL_H

#include <algorithm>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "Reaction.h"
#include "SymbolTable.h"
#include "Agent.h"
#include <functional>


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
    std::vector<Reaction<ValueType>> reactions;
    std::vector<std::pair<double, std::map<std::string, ValueType>>> stateHistory;
    std::function<void(double, const SymbolTable<std::string, ValueType>&)> observer; // Observer function

public:
    explicit Vessel(const std::string& vesselName,
                    std::function<void(double, const SymbolTable<std::string, ValueType>&)> observerFunc = nullptr)
        : name(vesselName), observer(std::move(observerFunc)) {}

    const auto& getStateHistory() const {
        return stateHistory;
    }

    const auto& getReactions() const {
        return reactions;
    }

    auto getAgents() const {
        return agentState.toMap();
    }

    Agent<ValueType> add(const std::string& itemName, const ValueType& initialValue) {
        if (!agentState.insert(itemName, initialValue)) {
            throw std::runtime_error("Error: Item '" + itemName + "' already exists in the vessel.");
        }
        return Agent<ValueType>(itemName, agentState.lookup(itemName).value());
    }

    void add(const Reaction<ValueType>& reaction) {
        reactions.push_back(reaction);
    }

    Agent<ValueType> environment() {
        if (!agentState.insert("env", 0)) {
            throw std::runtime_error("Environment already exists in the vessel.");
        }
        return Agent<ValueType>("env", agentState.lookup("env").value());
    }

    void printItems() const {
        std::cout << "Vessel: " << name << "\n";
        agentState.print();
        for (const auto& reaction : reactions) {
            reaction.print();
        }
    }

    void beginSimulation(double maxTime) {
        for (double time = 0; time < maxTime;) {
            for (auto& reaction : reactions) {
                reaction.delay = reaction.getDelay(agentState);
            }
            auto selectedIt = std::min_element(
                reactions.begin(), reactions.end(),
                [](const Reaction<ValueType>& a, const Reaction<ValueType>& b) {
                    return a.delay < b.delay;
                }
            );

            if (selectedIt != reactions.end()) {
                Reaction<ValueType>& selectedReaction = *selectedIt;
                time += selectedReaction.delay;

                bool allAvailable = std::all_of(
                    selectedReaction.reactants.begin(),
                    selectedReaction.reactants.end(),
                    [this](const Agent<ValueType>& agent) {
                        auto valOpt = this->agentState.lookup(agent.getName());
                        return valOpt.has_value() && valOpt.value() > 0;
                    }
                );

                if (allAvailable) {
                    for (const Agent<ValueType>& inputAgent : selectedReaction.reactants) {
                        agentState.decrement(inputAgent.getName());
                    }

                    for (const auto& outputAgent : selectedReaction.products) {
                        agentState.increment(outputAgent.getName());
                    }

                    if (observer) {
                        observer(time, agentState); // Call the observer function
                    }

                    auto snapshot = agentState.toMap();
                    stateHistory.emplace_back(time, snapshot);
                }
            }
        }
    }
};

#endif // VESSEL_H
