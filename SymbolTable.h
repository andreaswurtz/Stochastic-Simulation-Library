#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <optional>
#include <iostream>

template <typename KeyType, typename ValueType>
class SymbolTable {
    std::unordered_map<KeyType, ValueType> table;

public:
    bool insert(const KeyType& key, const ValueType& value) {
        if (table.contains(key)) {
            std::cerr << "Error: Key already exists in the symbol table.\n";
            return false;
        }
        table[key] = value;
        return true;
    }

    // Lookup a value by key
    std::optional<ValueType> lookup(const KeyType& key) const {
        auto it = table.find(key);
        if (it == table.end()) {
            std::cerr << "Error: Key not found in the symbol table.\n";
            return std::nullopt;
        }
        return it->second;
    }

    void print() const {
        for (const auto& [key, value] : table) {
            std::cout << "Key: " << key << ", Value: " << value << "\n";
        }
    }
};

#endif // SYMBOLTABLE_H