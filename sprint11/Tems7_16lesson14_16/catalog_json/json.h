#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>

namespace json {

class Node;
// Сохраните объявления Dict и Array без изменения
using Dict = std::map<std::string, Node>;
using Array = std::vector<Node>;

// Эта ошибка должна выбрасываться при ошибках парсинга JSON
class ParsingError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class Node {
public:
    /* Реализуйте Node, используя std::variant */
    using var = std::variant<std::nullptr_t, bool, double, Array, Dict, int, std::string>;

    Node () = default;
    Node(std::nullptr_t);
    Node(Array array);
    Node(Dict map);
    Node(int value);
    Node(std::string value);
    Node (bool value);
    Node (double value);


    bool IsInt() const;
    bool IsDouble() const;
    bool IsPureDouble() const;
    bool IsBool() const;
    bool IsString() const;
    bool IsNull() const;
    bool IsArray() const;
    bool IsMap() const;

    const Array& AsArray() const;
    const Dict& AsMap() const;
    int AsInt() const;
    const std::string& AsString() const;
    bool AsBool() const;
    double AsDouble() const;

    const var& GetVariant() const;// { return var_; }

    bool operator==(const Node& rhs) const;
    bool operator!=(const Node& rhs) const;

private:
    var var_;

};

class Document {
public:
    explicit Document(Node root);

    const Node& GetRoot() const;

    bool operator==(const Document& rhs) const;
    bool operator!=(const Document& rhs) const;

private:
    Node root_;
};

Document Load(std::istream& input);

void Print(const Document& doc, std::ostream& output);

}  // namespace json
