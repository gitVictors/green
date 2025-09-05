#pragma once
#include "json.h"

namespace json {

class Builder {
public :
    Builder ();
    Builder& Key(const std::string&);
    Builder& Value(Node::Value);
    Builder& StartDict();
    Builder& StartArray();
    Builder& EndDict();
    Builder& EndArray();
    Node Build();


private:
   // void AddObject(Node::Value&& value, bool one_shot) ;
    void AddNode(Node&& node, bool one_shot);
    Node::Value& GetCurrentValue() ;

    Node root_;
    std::vector<Node*> nodes_stack_;
    std::string current_key_;
    bool has_key_ = false;
};

}
