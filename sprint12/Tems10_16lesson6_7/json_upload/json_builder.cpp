#include "json_builder.h"

namespace json {

Builder::Builder() {

    root_ = Node(); // Создаем корневой узел
    nodes_stack_.push_back(&root_); // Добавляем корневой узел в стек

}

Node::Value& Builder::GetCurrentValue() {

    if (nodes_stack_.empty()) {
        throw std::logic_error("No current value in the stack");
    }

    return nodes_stack_.back()->GetValue();
}


void Builder::AddObject(Node::Value&& value, bool one_shot) {

    Node::Value& host_value = GetCurrentValue();

    if (auto* dict = std::get_if<Dict>(&host_value)) {
        // Если текущее значение является словарем, добавляем новый ключ-значение
        dict->emplace(std::make_pair(std::string(""), std::move(value)));
    } else if (auto* array = std::get_if<Array>(&host_value)) {
        // Если текущее значение является массивом, добавляем новый элемент
        array->emplace_back(std::move(value));
    }

    // Если это однократный объект, не добавляем его в стек
    if (!one_shot) {
        nodes_stack_.push_back(&host_value);
    }
}

Builder& Builder::StartDict() {

    Node::Value& host_value = GetCurrentValue();

    // Создаем новый словарь
    Dict new_dict;

    // Добавляем новый словарь в текущее значение
    AddObject(std::move(new_dict), /* one_shot */ false);

    return *this;
}



Builder& Builder::Key(const std::string& key) {

    Node::Value& host_value = GetCurrentValue();

    if (!std::holds_alternative<Dict>(host_value)) {
        throw std::logic_error("Key method called outside a dictionary");
    }

    current_key_ = key; // Сохраняем ключ для последующего использования при добавлении значения

    return *this;
}

Builder& Builder::Value(Node::Value value) {

    Node::Value& host_value = GetCurrentValue();

    if (auto* dict = std::get_if<Dict>(&host_value)) {
        // Если текущее значение является словарем и установлен текущий ключ, добавляем пару ключ-значение
        if (!current_key_.empty()) {
            dict->emplace(std::make_pair(current_key_, std::move(value)));
            current_key_ = ""; // Сброс текущего ключа
        } else {
            throw std::logic_error("Value method called in dictionary without a key");
        }
    } else if (auto* array = std::get_if<Array>(&host_value)) {
        // Если текущее значение является массивом, добавляем новый элемент
        array->emplace_back(std::move(value));
    } else {
        throw std::logic_error("Value method called outside a dictionary or array");
    }

    return *this;
}


Builder& Builder::EndDict() {
    if (nodes_stack_.empty()) {
        throw std::logic_error("No dictionary to end");
    }

    Node::Value& host_value = GetCurrentValue();
    if (!std::holds_alternative<Dict>(host_value)) {
        throw std::logic_error("EndDict called when current value is not a dictionary");
    }

    nodes_stack_.pop_back(); // Удаляем текущий словарь из стека

    return *this;
}

Builder& Builder::StartArray() {
    Node::Value& host_value = GetCurrentValue();

    // Создаем новый массив
    Array new_array;

    // Добавляем новый массив в текущее значение
    AddObject(std::move(new_array), /* one_shot */ false);

    return *this;
}

Builder& Builder::EndArray() {

    if (nodes_stack_.empty()) {
        throw std::logic_error("No array to end");
    }

    Node::Value& host_value = GetCurrentValue();
    if (!std::holds_alternative<Array>(host_value)) {
        throw std::logic_error("EndArray called when current value is not an array");
    }

    nodes_stack_.pop_back(); // Удаляем текущий массив из стека

    return *this;
}



}
