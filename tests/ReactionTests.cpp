#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../include/Reaction.h"
#include "../include/Agent.h"
#include "../include/SymbolTable.h"

TEST_CASE("Reaction: Constructor and Print") {
    SymbolTable<std::string, int> agentState;
    agentState.insert("A", 10);
    agentState.insert("B", 5);
    agentState.insert("C", 0);

    Agent<int> A("A", agentState.lookup("A").value());
    Agent<int> B("B", agentState.lookup("B").value());
    Agent<int> C("C", agentState.lookup("C").value());

    SUBCASE("Reaction creation and print") {
        Reaction<int> reaction({A, B}, 0.5, {C});
        CHECK_NOTHROW(reaction.print());
    }
}

TEST_CASE("Reaction: Calculate Reactant Product") {
    SymbolTable<std::string, int> agentState;
    agentState.insert("A", 10);
    agentState.insert("B", 5);
    agentState.insert("C", 0);
    agentState.insert("D", 0);

    Agent<int> A("A", agentState.lookup("A").value());
    Agent<int> B("B", agentState.lookup("B").value());
    Agent<int> C("C", agentState.lookup("C").value());
    Agent<int> D("D", agentState.lookup("D").value());

    Reaction<int> reaction({A, B}, 0.5, {C});
    Reaction<int> reaction2({C, D}, 0.5, {A});

    SUBCASE("Valid reactant product") {
        CHECK(reaction.calculateReactantProduct(agentState) == 50.0); // 10 * 5
    }

    SUBCASE("Reactant product with zero value") {
        CHECK(reaction2.calculateReactantProduct(agentState) == 0.0);
    }

    SUBCASE("Reactant product with missing key") {
        agentState.insert("D", 0);
        CHECK(reaction.calculateReactantProduct(agentState) == 50.0); // Unrelated key doesn't affect result
    }
}



TEST_CASE("Reaction: Get Delay") {
    SymbolTable<std::string, int> agentState;
    agentState.insert("A", 10);
    agentState.insert("B", 5);
    agentState.insert("C", 0);

    Agent<int> A("A", agentState.lookup("A").value());
    Agent<int> B("B", agentState.lookup("B").value());
    Agent<int> C("C", agentState.lookup("C").value());

    Reaction<int> reaction({A, B}, 0.5, {});
    Reaction<int> reaction2({C}, 0.5, {});

    SUBCASE("Valid delay calculation") {
        double delay = reaction.getDelay(agentState);
        CHECK(delay > 0.0);
    }

    SUBCASE("Infinite delay with zero reactant product") {
        double delay = reaction2.getDelay(agentState);
        CHECK(delay == std::numeric_limits<double>::infinity());
    }
}