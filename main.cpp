#include <iostream>
#include <string>

#include "SymbolTable.h"

int main() {
    SymbolTable<std::string, int> reactants;

    // Insert reactants
    reactants.insert("H2", 10);
    reactants.insert("O2", 5);

    // Attempt to insert a duplicate
    reactants.insert("H2", 20);

    // Lookup reactants
    auto h2 = reactants.lookup("H2");
    if (h2) {
        std::cout << "H2 count: " << *h2 << "\n";
    }

    auto co2 = reactants.lookup("CO2");
    if (!co2) {
        std::cout << "CO2 not found.\n";
    }

    // Print all reactants
    reactants.print();

    return 0;
}
