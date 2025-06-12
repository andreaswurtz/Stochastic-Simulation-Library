#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "../include/Vessel.h"

template <typename ValueType>
void generateGraphviz(const Vessel<ValueType>& vessel, const std::string& outputFile) {
    std::ofstream file(outputFile);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file for writing.");
    }

    file << "digraph {\n";

    // Add agent nodes
    for (const auto& [name, value] : vessel.getAgents()) {
        file << "    " << name << " [label=\"" << name << "\", shape=\"box\", style=\"filled\", fillcolor=\"cyan\"];\n";
    }

    // Add reaction nodes and edges
    int reactionIndex = 0;
    for (const auto& reaction : vessel.getReactions()) {
        std::string reactionNode = "r" + std::to_string(reactionIndex++);
        file << "    " << reactionNode << " [label=\"" << reaction.rate << "\", shape=\"oval\", style=\"filled\", fillcolor=\"yellow\"];\n";

        // Reactants -> Reaction
        for (const auto& reactant : reaction.reactants) {
            file << "    " << reactant.getName() << " -> " << reactionNode << " [arrowhead=\"tee\"];\n";
        }

        // Reaction -> Products
        for (const auto& product : reaction.products) {
            file << "    " << reactionNode << " -> " << product.getName() << ";\n";
        }
    }

    file << "}\n";
    file.close();
}