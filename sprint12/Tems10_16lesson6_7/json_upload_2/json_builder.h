#pragma once
#include "json.h"

namespace json {

class Builder;
class DictKeyContext;
class ArrayItemContext;

class BaseContext {
public:
    BaseContext(Builder& builder) : builder_(builder) {}

protected:
    Builder& builder_;
};

class DictItemContext : public BaseContext {
public:
    DictItemContext(Builder& builder) : BaseContext(builder) {}

    DictKeyContext  Key(const std::string& key);
    Builder& EndDict();
};

class DictKeyContext : public BaseContext {
public:
    DictKeyContext(Builder& builder) : BaseContext(builder) {}

    DictItemContext Value(Node::Value value);
    DictItemContext StartDict();
    ArrayItemContext StartArray();
};

class ArrayItemContext : public BaseContext {
public:
    ArrayItemContext(Builder& builder) : BaseContext(builder) {}

    ArrayItemContext Value(Node::Value value);
    Builder& EndArray();

    // Методы для вложенных структур в массиве
    DictItemContext StartDict();
    ArrayItemContext StartArray();
};



class Builder {
public :
    Builder ();
    DictKeyContext Key(const std::string&);
    Builder& Value(Node::Value);
    DictItemContext StartDict();
    ArrayItemContext StartArray();
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
    bool key_expected_ = false; // Ожидается ли ключ в словаре

    // Дружественные классы для доступа к приватным методам
    friend class DictKeyContext;
    friend class DictItemContext;
    friend class ArrayItemContext;
};






}
