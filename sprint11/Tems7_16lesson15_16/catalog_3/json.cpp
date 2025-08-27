#include <cmath>
#include <sstream>
#include <iomanip>

#include "json.h"

using namespace std;

namespace json {

namespace {


using Number = std::variant<int, double>;

Node LoadNode(istream& input);

Node LoadNull(istream& input) {
    const string nameNull = "null";
    for (size_t i = 0; i < nameNull.size(); i++) {

        if (input.peek() == -1) {
            throw ParsingError("Null parsing error");
        }

        if (nameNull.at(i) == input.get()) continue;
        else throw ParsingError("Null parsing error");
    }

    // Проверяем, что после "null" нет буквенно-цифровых символов
    if (isalnum(input.peek())) {
        throw ParsingError("Invalid null value: extra characters after literal");
    }

    return {};
}

Node LoadNumber(std::istream& input) {
    using namespace std::literals;

    std::string parsed_num;

    // Считывает в parsed_num очередной символ из input
    auto read_char = [&parsed_num, &input] {
        parsed_num += static_cast<char>(input.get());
        if (!input) {
            throw ParsingError("Failed to read number from stream"s);
        }
    };

    // Считывает одну или более цифр в parsed_num из input
    auto read_digits = [&input, read_char] {
        if (!std::isdigit(input.peek())) {
            throw ParsingError("A digit is expected"s);
        }
        while (std::isdigit(input.peek())) {
            read_char();
        }
    };

    if (input.peek() == '-') {
        read_char();
    }
    // Парсим целую часть числа
    if (input.peek() == '0') {
        read_char();
        // После 0 в JSON не могут идти другие цифры
    }
    else {
        read_digits();
    }

    bool is_int = true;
    // Парсим дробную часть числа
    if (input.peek() == '.') {
        read_char();
        read_digits();
        is_int = false;
    }

    // Парсим экспоненциальную часть числа
    if (int ch = input.peek(); ch == 'e' || ch == 'E') {
        read_char();
        if (ch = input.peek(); ch == '+' || ch == '-') {
            read_char();
        }
        read_digits();
        is_int = false;
    }

    try {
        if (is_int) {
            // Сначала пробуем преобразовать строку в int
            try {
                return std::stoi(parsed_num);
            }
            catch (...) {
                // В случае неудачи, например, при переполнении,
                // код ниже попробует преобразовать строку в double
            }
        }
        return std::stod(parsed_num);
    }
    catch (...) {
        throw ParsingError("Failed to convert "s + parsed_num + " to number"s);
    }
}

// Считывает содержимое строкового литерала JSON-документа
// Функцию следует использовать после считывания открывающего символа ":
std::string LoadString(std::istream& input) {
    using namespace std::literals;

    auto it = std::istreambuf_iterator<char>(input);
    auto end = std::istreambuf_iterator<char>();
    std::string s;
    while (true) {
        if (it == end) {
            // Поток закончился до того, как встретили закрывающую кавычку?
            throw ParsingError("String parsing error");
        }
        const char ch = *it;
        if (ch == '"') {
            // Встретили закрывающую кавычку
            ++it;
            break;
        } else if (ch == '\\') {
            // Встретили начало escape-последовательности
            ++it;
            if (it == end) {
                // Поток завершился сразу после символа обратной косой черты
                throw ParsingError("String parsing error");
            }
            const char escaped_char = *(it);
            // Обрабатываем одну из последовательностей: \\, \n, \t, \r, \"
            switch (escaped_char) {
            case 'n':
                s.push_back('\n');
                break;
            case 't':
                s.push_back('\t');
                break;
            case 'r':
                s.push_back('\r');
                break;
            case '"':
                s.push_back('"');
                break;
            case '\\':
                s.push_back('\\');
                break;
            default:
                // Встретили неизвестную escape-последовательность
                throw ParsingError("Unrecognized escape sequence \\"s + escaped_char);
            }
        } else if (ch == '\n' || ch == '\r') {
            // Строковый литерал внутри- JSON не может прерываться символами \r или \n
            throw ParsingError("Unexpected end of line"s);
        } else {
            // Просто считываем очередной символ и помещаем его в результирующую строку
            s.push_back(ch);
        }
        ++it;
    }

    return s;
}


Node LoadArray(istream& input) {

    Array result;

    if (input.peek() == -1) throw ParsingError("Array parsing error");

    for (char c; input >> c && c != ']';) {
        if (c != ',') {
            input.putback(c);
        }
        result.push_back(LoadNode(input));
    }

    return Node(std::move(result));
}



Node LoadDict(istream& input) {
    Dict result;

    if (input.peek() == -1) throw ParsingError("Dict parsing error");

    for (char c; input >> c && c != '}';) {
        if (c == ',') {
            input >> c;
        }

        string key = LoadString(input);
        input >> c;
        result.insert({std::move(key), LoadNode(input)});
    }

    return Node(std::move(result));
}



Node LoadBool(istream& input) {
    const string nameFalse = "false";
    const string nameTrue = "true";
    char c = input.get();
    bool value = (c == 't');
    std::string const* name = value ? &nameTrue : &nameFalse;
    for (size_t i = 1; i < name->size(); i++) {
        if (name->at(i) == input.get()) continue;
        else throw ParsingError("Bool parsing error");
    }
    // Проверяем, что после "true"/"false" нет буквенно-цифровых символов
    if (isalnum(input.peek())) {
        throw ParsingError("Invalid bool value: extra characters after literal");
    }

    return Node(value);
}




Node LoadNode(istream& input) {
    char c;
    if (!(input >> c)) {
        throw ParsingError("Unexpected end of input");
    }

    if (c == 'n') {
        input.putback(c);
        return LoadNull(input);
    }
    else if (c == '"') {
        return LoadString(input);
    }
    else if (c == 't' || c == 'f') {
        input.putback(c);
        return LoadBool(input);
    }
    else if (c == '[') {
        return LoadArray(input);
    }
    else if (c == '{') {
        return LoadDict(input);
    }
    else {
        input.putback(c);
        return LoadNumber(input);
        // Number num = LoadNumber(input);
        // if (std::holds_alternative<int>(num)) {
        //     return Node(std::get<int>(num));
        // } else {
        //     return Node(std::get<double>(num));
        // }
    }
}

}  // namespace

//--------------- NODE  ---------------------------------------------------------

// Node::Node(std::nullptr_t) : var_(nullptr)
// {}

// Node::Node(Array array)
//     : var_(std::move(array)) //as_array_(move(array))
// {
// }

// Node::Node(Dict map)
//     : var_(std::move(map)) //as_map_(move(map))
// {
// }

// Node::Node(int value)
//     : var_(value) //as_int_(value)
// {
// }

// Node::Node(string value)
//     : var_( std::move(value)) // as_string_(move(value))
// {
// }

// Node::Node (bool value)
//     : var_(value)
// {}

// Node::Node (double value)
//     : var_(value)
// {}

//конструктор для const char*
Node::Node(const char* value) : Var(std::string(value)) {}

const Array& Node::AsArray() const {
    if (!std::holds_alternative<Array>(*this)) {
        throw std::logic_error("Узел не содержит массива");
    }
    return std::get<Array>(*this);
}

const Dict& Node::AsMap() const {
    if (!std::holds_alternative<Dict>(*this)){
        throw std::logic_error("Узел не содержит map");
    }
    return std::get<Dict>(*this);
}

int Node::AsInt() const {
    if (!std::holds_alternative<int>(*this)) {
        throw std::logic_error("Узел не содержит целого числа");
    }
    return std::get<int>(*this);

}

const string& Node::AsString() const {
    if (!std::holds_alternative<string>(*this)) {
        throw std::logic_error("Узел не содержит строки");
    }
    return std::get<string>(*this);
}

bool Node::AsBool() const{
    if (!std::holds_alternative<bool>(*this)) {
        throw std::logic_error("Узел не содержит bool");
    }
    return std::get<bool>(*this);
}

double Node::AsDouble() const{
    if (!IsDouble()) throw std::logic_error("wrong type");
    if (IsInt()) return static_cast<double>(std::get<int>(*this));
    return std::get<double>(*this);
}

bool Node::IsInt() const {
    return std::holds_alternative<int>(*this);
}
bool Node::IsDouble() const{
    return std::holds_alternative<int>(*this) || std::holds_alternative<double>(*this);
}
bool Node::IsPureDouble() const{
    return std::holds_alternative<double>(*this);
}
bool Node::IsBool() const {
    return std::holds_alternative<bool>(*this);
}
bool Node::IsString() const{
    return std::holds_alternative<string>(*this);
}
bool Node::IsNull() const{
    return std::holds_alternative<std::nullptr_t>(*this);
}
bool Node::IsArray() const{
    return std::holds_alternative<Array>(*this);

}
bool Node::IsMap() const{
    return std::holds_alternative<Dict>(*this);
}

 bool Node::operator==(const Node& rhs) const {
     return  static_cast<const Var&>(*this) == static_cast<const Var&>(rhs);
 }

bool Node::operator!=(const Node& rhs) const {
    return !(*this == rhs);
}

const Node::Var& Node::GetVariant() const {
    return *this;
}
//-----------------------------------------------------------------------------------

Document::Document(Node root)
    :  root_(std::move(root))
{
}

const Node& Document::GetRoot() const {
    return root_;
}

Document Load(istream& input) {
    return Document{LoadNode(input)};
}

bool Document::operator==(const Document& rhs) const {
    return root_ == rhs.root_;
}

bool Document::operator!=(const Document& rhs) const {
    return !(*this == rhs);
}

//------------------------------------------------------------------------------------

void PrintNode(const Node& node, std::ostream& out);

void PrintValue(const std::string& value, std::ostream& out) {
    out << "\"";
    for (char c : value) {
        switch (c) {
        case '"':  out << "\\\""; break;
        case '\\': out << "\\\\"; break;
        case '\n': out << "\\n"; break;
        case '\r': out << "\\r"; break;
        case '\t': out << "\\t"; break;
        default:   out << c; break;
        }
    }
    out << "\"";
}

void PrintValue(std::nullptr_t, std::ostream& out) {
    out << "null";
}

void PrintValue(bool value, std::ostream& out) {
    out << (value ? "true" : "false");
}

template <typename Number>
void PrintNumber(Number value, std::ostream& out) {
    out << value;

}

void PrintValue(const Array& array, std::ostream& out) {
    out << "[";
    bool first = true;
    for (const auto& item : array) {
        if (!first) {
            out << ",";
        }
        PrintNode(item, out);
        first = false;
    }
    out << "]";
}

void PrintValue(const Dict& dict, std::ostream& out) {
    out << "{";
    bool first = true;
    for (const auto& [key, value] : dict) {
        if (!first) {
            out << ",";
        }
        PrintValue(key, out);
        out << ":";
        PrintNode(value, out);
        first = false;
    }
    out << "}";
}

void PrintNode(const Node& node, std::ostream& out) {
    if (node.IsNull()) {
        PrintValue(nullptr, out);
    } else if (node.IsInt()) {
        PrintNumber(node.AsInt(), out);
    } else if (node.IsPureDouble()) {
        PrintNumber(node.AsDouble(), out);
    } else if (node.IsString()) {
        PrintValue(node.AsString(), out);
    } else if (node.IsBool())  {
        PrintValue(node.AsBool(), out);
    } else if (node.IsArray()) {
        PrintValue(node.AsArray(), out);
    } else if (node.IsMap()) {
        PrintValue(node.AsMap(), out);
    }

}

void Print(const Document& doc, std::ostream& output) {
    PrintNode(doc.GetRoot(), output);
}

}  // namespace json
