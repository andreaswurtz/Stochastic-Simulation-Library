#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../include/SymbolTable.h"

TEST_CASE("SymbolTable: Insert and Lookup") {
    SymbolTable<std::string, int> table;

    SUBCASE("Insert and lookup a key") {
        CHECK(table.insert("key1", 42));
        auto value = table.lookup("key1");
        REQUIRE(value.has_value());
        CHECK(value.value() == 42);
    }

    SUBCASE("Insert duplicate key") {
        CHECK(table.insert("key1", 42));
        CHECK_FALSE(table.insert("key1", 100)); // Duplicate key should fail
    }

    SUBCASE("Lookup non-existent key") {
        auto value = table.lookup("nonexistent");
        CHECK_FALSE(value.has_value()); // Should return std::nullopt
    }
}

TEST_CASE("SymbolTable: Increment and Decrement") {
    SymbolTable<std::string, int> table;

    SUBCASE("Increment a key") {
        CHECK(table.insert("key1", 42));
        table.increment("key1");
        auto value = table.lookup("key1");
        REQUIRE(value.has_value());
        CHECK(value.value() == 43);
    }

    SUBCASE("Decrement a key") {
        CHECK(table.insert("key1", 42));
        table.decrement("key1");
        auto value = table.lookup("key1");
        REQUIRE(value.has_value());
        CHECK(value.value() == 41);
    }

    SUBCASE("Increment non-existent key") {
        CHECK_THROWS_AS(table.increment("nonexistent"), std::runtime_error);
    }

    SUBCASE("Decrement non-existent key") {
        CHECK_THROWS_AS(table.decrement("nonexistent"), std::runtime_error);
    }
}

TEST_CASE("SymbolTable: toMap and Print") {
    SymbolTable<std::string, int> table;

    SUBCASE("Convert to map") {
        CHECK(table.insert("key1", 42));
        CHECK(table.insert("key2", 100));
        auto map = table.toMap();
        CHECK(map.size() == 2);
        CHECK(map["key1"] == 42);
        CHECK(map["key2"] == 100);
    }

    SUBCASE("Print table") {
        CHECK(table.insert("key1", 42));
        CHECK(table.insert("key2", 100));
        // No direct way to test console output, but ensure no runtime errors
        table.print();
    }
}