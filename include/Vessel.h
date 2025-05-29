#ifndef VESSEL_H
#define VESSEL_H

#include <string>
#include <memory>
#include <vector>
#include "Reaction.h"
#include "SymbolTable.h"
#include "Agent.h"


// Overload >> for a single Agent
template <typename ValueType>
 std::pair<std::vector<Agent<ValueType>>, ValueType> operator>>(const Agent<ValueType>& reactant, const double& rate) {
    return {{reactant}, rate};
}

// Overload >> for std::vector<Agent<ValueType>>
template <typename ValueType>
std::pair<std::vector<Agent<ValueType>>, ValueType> operator>>(const std::vector<Agent<ValueType>>& reactants, const double& rate) {
    return {reactants, rate};
}

// Overload >>= for a single product
template <typename ValueType>
Reaction<ValueType> operator>>=(const std::pair<std::vector<Agent<ValueType>>, ValueType>& intermediate, const Agent<ValueType>& product) {
    return Reaction<ValueType>(intermediate.first, intermediate.second, {product});
}

// Overload >>= for multiple products
template <typename ValueType>
Reaction<ValueType> operator>>=(const std::pair<std::vector<Agent<ValueType>>, ValueType>& intermediate, const std::vector<Agent<ValueType>>& products) {
    return Reaction<ValueType>(intermediate.first, intermediate.second, products);
}

template <typename ValueType>
class Vessel {
    std::string name;
    SymbolTable<std::string, ValueType> items;
    std::vector<Reaction<ValueType>> reactions;

public:
    explicit Vessel(const std::string& vesselName) : name(vesselName) {}

    Agent<ValueType> add(const std::string& itemName, const ValueType& initialValue) {
        if (!items.insert(itemName, initialValue)) {
            throw std::runtime_error("Error: Item '" + itemName + "' already exists in the vessel.");
        }
        return Agent<ValueType>(itemName, items.lookup(itemName).value());
    }

    void add(const Reaction<ValueType>& reaction) {
        reactions.push_back(reaction);
    }

    void printItems() const {
        std::cout << "Vessel: " << name << "\n";
        items.print();
        for (const auto& reaction : reactions) {
            reaction.print();
        }
    }

    void beginSimulation() {

    }
};

#endif // VESSEL_H