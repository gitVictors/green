#include "json_builder.h"

namespace json {

Builder::Builder() {
    // Инициализируем корневой узел как null
    root_ = Node();
    nodes_stack_.push_back(&root_);
}

Node::Value& Builder::GetCurrentValue() {
    if (nodes_stack_.empty()) {
        throw std::logic_error("No current value in the stack");
    }
    return nodes_stack_.back()->GetValue();
}

void Builder::AddValue(Node::Value value) {
    Node::Value& current = GetCurrentValue();
    
    if (std::holds_alternative<Dict>(current)) {
        if (!has_key_) {
            throw std::logic_error("Value added to dict without key");
        }
        Dict& dict = std::get<Dict>(current);
        dict.emplace(current_key_, std::move(value));
        has_key_ = false;
        current_key_.clear();
    } else if (std::holds_alternative<Array>(current)) {
        Array& array = std::get<Array>(current);
        array.emplace_back(std::move(value));
    } else if (std::holds_alternative<std::nullptr_t>(current)) {
        // Это корневой узел
        current = std::move(value);
    } else {
        throw std::logic_error("Cannot add value to non-container node");
    }
}

Builder& Builder::Key(const std::string& key) {
    if (!std::holds_alternative<Dict>(GetCurrentValue())) {
        throw std::logic_error("Key called outside dictionary");
    }
    if (has_key_) {
        throw std::logic_error("Key called without value for previous key");
    }
    current_key_ = key;
    has_key_ = true;
    return *this;
}

Builder& Builder::Value(Node::Value value) {
    AddValue(std::move(value));
    return *this;
}

Builder& Builder::StartDict() {
    Dict dict;
    AddValue(std::move(dict));
    
    // Добавляем новый словарь в стек для последующего заполнения
    Node::Value& current = GetCurrentValue();
    if (std::holds_alternative<Dict>(current)) {
        Dict& dict = std::get<Dict>(current);
        nodes_stack_.push_back(&dict.rbegin()->second);
    } else if (std::holds_alternative<Array>(current)) {
        Array& array = std::get<Array>(current);
        nodes_stack_.push_back(&array.back());
    } else {
        nodes_stack_.push_back(&root_);
    }
    
    return *this;
}

Builder& Builder::StartArray() {
    Array array;
    AddValue(std::move(array));
    
    // Добавляем новый массив в стек для последующего заполнения
    Node::Value& current = GetCurrentValue();
    if (std::holds_alternative<Dict>(current)) {
        Dict& dict = std::get<Dict>(current);
        nodes_stack_.push_back(&dict.rbegin()->second);
    } else if (std::holds_alternative<Array>(current)) {
        Array& array = std::get<Array>(current);
        nodes_stack_.push_back(&array.back());
    } else {
        nodes_stack_.push_back(&root_);
    }
    
    return *this;
}

Builder& Builder::EndDict() {
    if (!std::holds_alternative<Dict>(GetCurrentValue())) {
        throw std::logic_error("EndDict called when current value is not a dictionary");
    }
    nodes_stack_.pop_back();
    return *this;
}

Builder& Builder::EndArray() {
    if (!std::holds_alternative<Array>(GetCurrentValue())) {
        throw std::logic_error("EndArray called when current value is not an array");
    }
    nodes_stack_.pop_back();
    return *this;
}

Node Builder::Build() {
    if (nodes_stack_.size() != 1) {
        throw std::logic_error("Build called with unclosed containers");
    }
    if (has_key_) {
        throw std::logic_error("Build called with unfinished key-value pair");
    }
    return root_;
}

}
