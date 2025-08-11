#include <istream>
#include "json.h"
#include "json_reader.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */


namespace json_reader {

using namespace json;
using namespace std;

JsonReader::JsonReader (std::istream& input ):
    doc_input_( json::Load(input))
{
}


const json::Document& JsonReader::GetDocument() const {
    return doc_input_;
}

}
