#pragma once
#include "json.h"

namespace json {


class Builder {


private:

    class BaseContext;
    class DictKeyContext;
    class DictItemContext;
    class ArrayItemContext;

    class BaseContext {
    public:
        BaseContext(Builder& builder) : builder_(builder) {}

        // Все методы Builder
        DictKeyContext Key(const std::string& key);
        BaseContext Value(Node::Value value);
        DictItemContext StartDict();
        ArrayItemContext StartArray();
        Builder& EndDict();
        Builder& EndArray();

    protected:
        Builder& builder_;
    };

    class DictItemContext : public BaseContext {
    public:
        using BaseContext::BaseContext;

        DictKeyContext Key(const std::string& key);
        Builder& EndDict();
        // Запрещаем недопустимые
        BaseContext Value(Node::Value) = delete;
        DictItemContext StartDict() = delete;
        ArrayItemContext StartArray() = delete;
        Builder& EndArray() = delete;
    };

    class DictKeyContext : public BaseContext {
    public:
        using BaseContext::BaseContext;

        DictKeyContext(Builder& builder) : BaseContext(builder) {}

        DictItemContext Value(Node::Value value);
        DictItemContext StartDict();
        ArrayItemContext StartArray();

        DictKeyContext Key(const std::string& key) = delete;
        Builder& EndDict() = delete;
        Builder& EndArray() = delete;
    };

    class ArrayItemContext : public BaseContext {
    public:
        ArrayItemContext(Builder& builder) : BaseContext(builder) {}

        ArrayItemContext Value(Node::Value value);
        DictItemContext StartDict();
        ArrayItemContext StartArray();
        Builder& EndArray();

        DictKeyContext Key(const std::string& key) = delete;
        Builder& EndDict() = delete;
    };

    // void AddObject(Node::Value&& value, bool one_shot) ;
    void AddNode(Node&& node, bool one_shot);
    Node::Value& GetCurrentValue() ;

    Node root_;
    std::vector<Node*> nodes_stack_;
    std::string current_key_;
    bool key_expected_ = false; // Ожидается ли ключ в словаре

public :

    Builder ();

    DictKeyContext Key(const std::string&);
    Builder& Value(Node::Value);
    DictItemContext StartDict();
    ArrayItemContext StartArray();
    Builder& EndDict();
    Builder& EndArray();

    Node Build();


};






}
