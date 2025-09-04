#pragma once
#include "json.h"
#include <vector>
#include <string>
#include <stdexcept>

namespace json {

class Builder {
public:
    Builder();
    Builder& Key(std::string key);
    Builder& Value(Node::Value value);
    Builder& StartDict();
    Builder& StartArray();
    Builder& EndDict();
    Builder& EndArray();
    Node Build();

private:
    Node::Value& GetCurrentValue();
    void AddValue(Node::Value value);

    Node root_;
    std::vector<Node*> nodes_stack_;
    std::string current_key_;
    bool has_key_ = false;
};

}
