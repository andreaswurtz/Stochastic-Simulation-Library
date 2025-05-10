#ifndef VESSEL_H
#define VESSEL_H

#include <string>
#include "SymbolTable.h"

template <typename ValueType>
class Vessel {
    std::string name;
    SymbolTable<std::string, ValueType> items;

public:
    explicit Vessel(const std::string& vesselName) : name(vesselName) {}

    // Add an item to the vessel
    bool add(const std::string& itemName, const ValueType& initialValue) {
        return items.insert(itemName, initialValue);
    }

    // Print all items in the vessel
    void printItems() const {
        std::cout << "Vessel: " << name << "\n";
        items.print();
    }
};

#endif // VESSEL_H