//
// Created by andreas on 5/29/25.
//

#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <vector>

template <typename ValueType>
class Agent {
    std::string name;
    ValueType value;

public:
    Agent(const std::string& name, const ValueType& value) : name(name), value(value) {}

    const ValueType& get() const { return value; }
    const std::string& getName() const { return name; }

    friend std::vector<Agent<ValueType>> operator+(const Agent<ValueType>& lhs, const Agent<ValueType>& rhs) {
        return {lhs, rhs};
    }
};


#endif //AGENT_H
