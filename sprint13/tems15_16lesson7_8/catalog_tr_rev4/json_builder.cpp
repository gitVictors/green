#include <variant>
// #include <iostream>
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
    return nodes_stack_.back()->GetValueNoConst();
}


void Builder::AddNode(Node&& node, bool one_shot) {

    Node::Value& host_value = GetCurrentValue();

    if (std::holds_alternative<std::nullptr_t>(host_value)) {
        // Заменяем корневой узел nullptr на новое значение
        host_value = std::move(node.GetValueNoConst());
        // Если это контейнер (не one_shot), добавляем его в стек для дальнейшего построения
        if (!one_shot) {
            nodes_stack_.push_back(nodes_stack_.back());
        }
    } else if (auto* dict = std::get_if<Dict>(&host_value)) {
            // Для словаря используем сохраненный ключ
            // Вставляем и получаем итератор на вставленный элемент
            auto [it, inserted] = dict->emplace(current_key_, std::move(node));
            current_key_.clear();

            if (!one_shot) {
                // Добавляем указатель на только что вставленный узел
                nodes_stack_.push_back(&it->second);
            }

    } else if (auto* array = std::get_if<Array>(&host_value)) {
        // Для массива просто добавляем узел
        array->push_back(std::move(node));

        if (!one_shot) {
            // Получаем неконстантную ссылку на последний элемент
            nodes_stack_.push_back(&array->back());
        }
    } else {
        throw std::logic_error("AddNode called outside dictionary or array");
    }
}


json::Builder::DictItemContext  json::Builder::StartDict() {

    Node::Value& host_value = GetCurrentValue();

    // Проверяем, можно ли начать словарь в текущем контексте
     if (std::holds_alternative<Dict>(host_value) && !key_expected_) {
        throw std::logic_error("StartDict called in dictionary without a key");
    }

    if (!std::holds_alternative<std::nullptr_t>(host_value) &&
        !std::holds_alternative<Dict>(host_value) &&
        !std::holds_alternative<Array>(host_value)) {
        throw std::logic_error("StartDict called in invalid context");
    }

    // Создаем новый словарь как Node
    Node dict_node{Dict{}};
    AddNode(std::move(dict_node), false);

    // Сбрасываем флаг ожидания ключа после начала словаря
    if (std::holds_alternative<Dict>(host_value)) {
        key_expected_ = false;
    }

     return DictItemContext(*this);
}

Builder::DictKeyContext Builder::Key(const std::string& key) {

    Node::Value& host_value = GetCurrentValue();

    if (!std::holds_alternative<Dict>(host_value)) {
        throw std::logic_error("Key method called outside a dictionary");
    }

    if (key_expected_) {
        throw std::logic_error("Key called immediately after another Key without Value");
    }

    // Проверяем, что нет незакрытого ключа
    if (!current_key_.empty()) {
        throw std::logic_error("Key called immediately after another Key without Value");
    }

    current_key_ = key;
    key_expected_ = true; // После Key ожидается Value

    return DictKeyContext(*this);
}

Builder& Builder::Value(Node::Value value) {

    Node::Value& host_value = GetCurrentValue();

    // Проверяем, можно ли добавить значение в текущий контекст
    if (std::holds_alternative<Dict>(host_value) && !key_expected_) {
        throw std::logic_error("Value called in dictionary without a key");
    }

    // Проверяем, что не пытаемся добавить значение в неподдерживаемый контекст
    if (!std::holds_alternative<std::nullptr_t>(host_value) &&
        !std::holds_alternative<Dict>(host_value) &&
        !std::holds_alternative<Array>(host_value)) {
        throw std::logic_error("Value called in invalid context");
    }


    Node node(std::move(value));
    AddNode(std::move(node), true);

    // Сбрасываем флаг ожидания ключа после добавления значения
    if (std::holds_alternative<Dict>(host_value)) {
        key_expected_ = false;
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

    nodes_stack_.pop_back();
    return *this;
}

Builder::ArrayItemContext Builder::StartArray() {

    Node::Value& host_value = GetCurrentValue();

    // Проверяем, можно ли начать массив в текущем контексте
   if (std::holds_alternative<Dict>(host_value) && !key_expected_)  {
        throw std::logic_error("StartArray called in dictionary without a key");
    }

    if (!std::holds_alternative<std::nullptr_t>(host_value) &&
        !std::holds_alternative<Dict>(host_value) &&
        !std::holds_alternative<Array>(host_value)) {
        throw std::logic_error("StartArray called in invalid context");
    }

    // Создаем новый массив как Node
    Node array_node{Array{}};
    AddNode(std::move(array_node), false);

    // Сбрасываем флаг ожидания ключа после начала массива
    if (std::holds_alternative<Dict>(host_value)) {
        key_expected_ = false;
    }

    //return *this;
    return ArrayItemContext(*this);
}

Builder& Builder::EndArray() {
    if (nodes_stack_.empty()) {
        throw std::logic_error("No array to end");
    }

    Node::Value& host_value = GetCurrentValue();
    if (!std::holds_alternative<Array>(host_value)) {
        throw std::logic_error("EndArray called when current value is not an array");
    }

    nodes_stack_.pop_back();
    return *this;
}

Node Builder::Build() {
    // Проверяем, что стек содержит только корневой узел
    if (nodes_stack_.size() != 1) {
        throw std::logic_error("Build called with unfinished structures");
    }

    // Проверяем, что все структуры закрыты (нет незавершенных массивов/словарей)
    Node::Value& root_value = GetCurrentValue();
    if (std::holds_alternative<std::nullptr_t>(root_value)) {
        throw std::logic_error("Build called on empty builder");
    }

    // Проверяем, что нет незакрытых ключей
    if (!current_key_.empty()) {
        throw std::logic_error("Build called with unfinished key");
    }

    // Возвращаем корневой узел
    return std::move(root_);
}

// Реализации методов контекстных классов ===========================
Builder::DictKeyContext Builder::DictItemContext::Key(const std::string& key) {
    builder_.Key(key);
    return DictKeyContext(builder_); ;
}

Builder& Builder::DictItemContext::EndDict() {
    return builder_.EndDict();
}

Builder::DictItemContext Builder::DictKeyContext::Value(Node::Value value) {
    builder_.Value(std::move(value));
    return DictItemContext(builder_);
}

Builder::DictItemContext Builder::DictKeyContext::StartDict() {
    return builder_.StartDict();
}

Builder::ArrayItemContext Builder::DictKeyContext::StartArray() {
    return builder_.StartArray();
}

Builder::ArrayItemContext Builder::ArrayItemContext::Value(Node::Value value) {
    builder_.Value(std::move(value));
    return *this;
}

Builder& Builder::ArrayItemContext::EndArray() {
    return builder_.EndArray();
}

Builder::DictItemContext Builder::ArrayItemContext::StartDict() {
    return builder_.StartDict();
}

Builder::ArrayItemContext Builder::ArrayItemContext::StartArray() {
    return builder_.StartArray();
}

//==================================================================

} // namespace json
