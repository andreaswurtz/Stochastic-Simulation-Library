#ifndef VESSEL_H
#define VESSEL_H

#include <string>
#include <memory>
#include "SymbolTable.h"

template <typename ValueType>
class Agent {
    std::string name;
    ValueType value; // Store by value

public:
    // Constructor
    Agent(const std::string& name, const ValueType& value) : name(name), value(value) {}

    // Access the value
    ValueType& get() { return value; }

    // Access the name
    const std::string& getName() const { return name; }

    // Overload operators for reactions (example: addition)
    Agent operator+(const Agent& other) const {
        return Agent("temp", value + other.value); // Temporary agent for demonstration
    }

    // Add more operators as needed
};

template <typename ValueType>
class Vessel {
    std::string name;
    SymbolTable<std::string, ValueType> items;

public:
    explicit Vessel(const std::string& vesselName) : name(vesselName) {}

    // Add an item to the vessel and return an Agents wrapper
    Agent<ValueType> add(const std::string& itemName, const ValueType& initialValue) {
        if (!items.insert(itemName, initialValue)) {
            throw std::runtime_error("Error: Item '" + itemName + "' already exists in the vessel.");
        }
        return Agent<ValueType>(itemName, items.lookup(itemName).value());
    }

    // Print all items in the vessel
    void printItems() const {
        std::cout << "Vessel: " << name << "\n";
        items.print();
    }
};
#endif // VESSEL_H