#include <vector>
#include "svg.h"


namespace svg {

using namespace std::literals;


void Object::Render(const RenderContext& context) const {
    context.RenderIndent();

    // Делегируем вывод тега своим подклассам
    RenderObject(context);

    context.out << std::endl;
}

// ---------- Circle ------------------

Circle& Circle::SetCenter(Point center)  {
    center_ = center;
    return *this;
}

Circle& Circle::SetRadius(double radius)  {
    radius_ = radius;
    return *this;
}

void Circle::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    out << "<circle cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
    out << "r=\""sv << radius_ << "\" "sv;
    out << "/>"sv;
}

//------Polyline -------------------------------

Polyline& Polyline::AddPoint(Point point) {
    points_.push_back(point);
    return *this;
}

void Polyline::RenderObject(const RenderContext& context) const {

    auto& out = context.out;
    out << "<polyline points=\"";

    for (size_t i = 0; i < points_.size(); ++i) {
        out << points_[i].x << "," << points_[i].y;
        if (i < points_.size() - 1) {
            out << " ";
        }
    }

    out << "\" />";
}


//---------Text --------------------------------

void Text::HtmlEncodeString(std::ostream& out, std::string sv) const{
    for (char c : sv) {
        switch (c) {
        case '"':
            out << "&quot;";
            break;
        case '<':
            out << "&lt;";
            break;
        case '>':
            out << "&gt;";
            break;
        case '&':
            out << "&amp;";
            break;
        case '\'':
            out << "&apos;";
            break;
        default:
            out.put(c);
        }
    }
}

// Задаёт координаты опорной точки (атрибуты x и y)
Text&  Text::SetPosition(Point pos){
    position_ =  pos;
    return *this;
}

// Задаёт смещение относительно опорной точки (атрибуты dx, dy)
Text& Text::SetOffset(Point offset) {
    offset_ = offset;
    return *this;
}

// Задаёт размеры шрифта (атрибут font-size)
Text& Text::SetFontSize(uint32_t size) {
    font_size_ = size;
    return *this;
}

// Задаёт название шрифта (атрибут font-family)
Text& Text::SetFontFamily(std::string font_family){
    font_family_ = font_family;
    return *this;
}

// Задаёт толщину шрифта (атрибут font-weight)
Text& Text::SetFontWeight(std::string font_weight){
    font_weight_ = font_weight;
    return *this;
}

// Задаёт текстовое содержимое объекта (отображается внутри тега text)
Text& Text::SetData(std::string data){
    data_ = data;
    return *this;
}

Point Text::GetPosition() const{
    return position_;
}
Point Text::GetOffset() const{
    return offset_;
}
uint32_t Text::GetFontSize() const{
    return font_size_;
}
std::string Text::GetFontFamily() const{
    return font_family_;
}
std::string Text::GetFontWeight() const{
    return font_weight_;
}
std::string Text::GetData() const{
    return data_;
}

// void Text::RenderObject(const RenderContext& context) const {
//     context.RenderIndent();
//     auto& out = context.out;

//     out << "<text ";
//     out << " x=\"" << GetPosition().x << "\" ";
//     out << " y=\"" << GetPosition().y << "\" ";
//     out << " dx=\"" << GetOffset().x << "\" ";
//     out << " dy=\"" << GetOffset().y << "\" ";
//     out << " font-size=\"" << GetFontSize() << "\" ";

//     if (!font_family_.empty())
//         out << " font-family=\"" << GetFontFamily() << "\" ";
//     if (!font_weight_.empty())
//         out << " font-weight=\"" << GetFontWeight() << "\">";

//     out << ">";
//     HtmlEncodeString(out, data_);
//     out << "</text>";
// }

void Text::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    out << "<text";

    // Вывод атрибутов
    RenderAttr(out, " x", position_.x);
    RenderAttr(out, " y", position_.y);
    RenderAttr(out, " dx", offset_.x);
    RenderAttr(out, " dy", offset_.y);
    RenderAttr(out, " font-size", font_size_);

    // Условные атрибуты (выводятся только если не пустые)
    if (!font_family_.empty()) {
        RenderAttr(out, " font-family", font_family_);
    }
    if (!font_weight_.empty()) {
        RenderAttr(out, " font-weight", font_weight_);
    }

    // Закрывающий тег и содержимое
    out << ">";
    HtmlEncodeString(out, data_);
    out << "</text>";
}



//---------Document ----------------------------

// template <typename ObjectType>
// void Document::Add(ObjectType object) {
//     AddPtr(std::make_unique<ObjectType>(std::move(object)));
// }

void Document::AddPtr(std::unique_ptr<Object>&& obj) {
    objects_.emplace_back(std::move(obj));
}


void Document::Render(std::ostream& out) const {

    out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;

    for (const auto& obj : objects_) {
        obj->Render(RenderContext(out, 2));
    }

    out << "</svg>" << std::endl;
}


void Document::RenderObject(const RenderContext& context) const {
    for (const auto& obj : objects_) {
        obj->Render(context);
    }
}


}  // namespace svg
