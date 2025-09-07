#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <variant>

namespace svg {


struct Rgb {
    Rgb():
        red(0),
        green(0),
        blue(0)
    {}

    Rgb(uint8_t r, uint8_t g, uint8_t b ):
        red(r),
        green(g),
        blue(b)
    {}

    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Rgba: public Rgb {

    Rgba (): Rgb(), opacity(1.0)
    {}

    Rgba(uint8_t r, uint8_t g, uint8_t b, double a):
        Rgb(r,g,b),
        opacity(a)
    {}

    double opacity;
};

using Color = std::variant<std::monostate, std::string, svg::Rgb,svg::Rgba>; //std::string;


    // Объявив в заголовочном файле константу со спецификатором inline,
    // мы сделаем так, что она будет одной на все единицы трансляции,
    // которые подключают этот заголовок.
    // В противном случае каждая единица трансляции будет использовать свою копию этой константы
    inline const Color NoneColor{ std::monostate() };


enum class StrokeLineCap {
    BUTT,
    ROUND,
    SQUARE,
};

enum class StrokeLineJoin {
    ARCS,
    BEVEL,
    MITER,
    MITER_CLIP,
    ROUND,
};

std::ostream& operator<<(std::ostream& out, StrokeLineCap line_cap);
std::ostream& operator<<(std::ostream& out, StrokeLineJoin line_join);
std::ostream& operator<<(std::ostream& out, const Color& color);

template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; };

template <typename Owner>
class PathProps {
public:
    Owner& SetFillColor(Color color) {
        fill_color_ = std::move(color);
        return AsOwner();
    }
    Owner& SetStrokeColor(Color color) {
        stroke_color_ = std::move(color);
        return AsOwner();
    }

    Owner& SetStrokeWidth(double width){
        stroke_width_ = width;
        return AsOwner();
    }
    Owner& SetStrokeLineCap(StrokeLineCap line_cap) {
        line_cap_ = line_cap;
        return AsOwner();
    }
    Owner& SetStrokeLineJoin(StrokeLineJoin line_join) {
        line_join_ = line_join;
        return AsOwner();
    }

protected:
    ~PathProps() = default;

    // Метод RenderAttrs выводит в поток общие для всех путей атрибуты fill и stroke
    void RenderAttrs(std::ostream& out) const {
        using namespace std::literals;

        auto visitor = overloads{

            [&out](std::monostate ){ out <<  "none";  },
            [&out](const std::string color){ out << color; },
            [&out](const svg::Rgb rgb){  out << "rgb("
                                           << static_cast<int>(rgb.red) << "," << static_cast<int>(rgb.green) << "," << static_cast<int>(rgb.blue)
                                           << ")";},
            [&out](const svg::Rgba rgba){
                    out << "rgba("
                        << static_cast<int>(rgba.red) << "," << static_cast<int>(rgba.green) << "," << static_cast<int>(rgba.blue) << "," << rgba.opacity
                        << ")";
                }
        };



        if (fill_color_) {
            out << " fill=\""sv;
            std::visit(visitor, *fill_color_);
            out << "\""sv;
        }
        if (stroke_color_) {
            out << " stroke=\""sv;
            std::visit(visitor,  *stroke_color_ );
            out << "\""sv;
        }
        if (stroke_width_) {
            out << " stroke-width=\""sv << *stroke_width_ << "\""sv;
        }
        if (line_cap_) {
            out << " stroke-linecap=\""sv << *line_cap_ << "\""sv;
        }
        if (line_join_) {
            out << " stroke-linejoin=\""sv << *line_join_ << "\""sv;
        }
    }

private:
    Owner& AsOwner() {
        // static_cast безопасно преобразует *this к Owner&,
        // если класс Owner — наследник PathProps
        return static_cast<Owner&>(*this);
    }

    std::optional<Color> fill_color_;
    std::optional<Color> stroke_color_;
    std::optional<double>  stroke_width_;
    std::optional<StrokeLineCap> line_cap_;
    std::optional<StrokeLineJoin> line_join_;
};


struct Point {
    Point() = default;
    Point(double x, double y)
        : x(x)
        , y(y) {
    }
    double x = 0;
    double y = 0;
};

/*
 * Вспомогательная структура, хранящая контекст для вывода SVG-документа с отступами.
 * Хранит ссылку на поток вывода, текущее значение и шаг отступа при выводе элемента
 */
struct RenderContext {
    RenderContext(std::ostream& out)
        : out(out) {
    }

    RenderContext(std::ostream& out, int indent_step, int indent = 0)
        : out(out)
        , indent_step(indent_step)
        , indent(indent) {
    }

    RenderContext Indented() const {
        return {out, indent_step, indent + indent_step};
    }

    void RenderIndent() const {
        for (int i = 0; i < indent; ++i) {
            out.put(' ');
        }
    }

    std::ostream& out;
    int indent_step = 0;
    int indent = 0;
};

/*
 * Абстрактный базовый класс Object служит для унифицированного хранения
 * конкретных тегов SVG-документа
 * Реализует паттерн "Шаблонный метод" для вывода содержимого тега
 */
class Object {
public:

    virtual void Render(const RenderContext& context) const ;

    virtual ~Object() = default;

private:
    virtual void RenderObject(const RenderContext& context) const = 0;
};



// Интерфейс для контейнеров объектов SVG
class ObjectContainer {
public:
    virtual ~ObjectContainer() = default;
    virtual void AddPtr(std::unique_ptr<Object>&& obj) = 0;

    template <typename ObjectType>
    void Add(ObjectType object) {
        AddPtr(std::make_unique<ObjectType>(std::move(object)));
    }
};

// Интерфейс для объектов, которые можно нарисовать
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void Draw(ObjectContainer& container) const = 0;
};

/*
 * Класс Circle моделирует элемент <circle> для отображения круга
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/circle
 */
class Circle final : public Object, public PathProps<Circle> {
public:
    Circle& SetCenter(Point center);
    Circle& SetRadius(double radius);

private:
    void RenderObject(const RenderContext& context) const override;

    Point center_;
    double radius_ = 1.0;
};

/*
 * Класс Polyline моделирует элемент <polyline> для отображения ломаных линий
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/polyline
 */
class Polyline : public Object, public PathProps<Polyline> {
public:
    // Добавляет очередную вершину к ломаной линии
    Polyline& AddPoint(Point point);

private :
    void RenderObject(const RenderContext& context) const override;

    std::vector<Point> points_;
};

/*
 * Класс Text моделирует элемент <text> для отображения текста
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/text
 */
class Text : public Object, public PathProps<Text> {
public:
    Text() = default;
    // Задаёт координаты опорной точки (атрибуты x и y)
    Text& SetPosition(Point pos);

    // Задаёт смещение относительно опорной точки (атрибуты dx, dy)
    Text& SetOffset(Point offset);

    // Задаёт размеры шрифта (атрибут font-size)
    Text& SetFontSize(uint32_t size);


    // Задаёт название шрифта (атрибут font-family)
    Text& SetFontFamily(std::string font_family);

    // Задаёт толщину шрифта (атрибут font-weight)
    Text& SetFontWeight(std::string font_weight);

    // Задаёт текстовое содержимое объекта (отображается внутри тега text)
    Text& SetData(std::string data);

    Point GetPosition() const;
    Point GetOffset() const;
    uint32_t GetFontSize() const;
    std::string GetFontFamily() const;
    std::string GetFontWeight() const;
    std::string GetData() const;

   template <typename AttrType>
   inline void RenderAttr(std::ostream& out, std::string_view name, const AttrType& value) const {
        using namespace std::literals;
        out << name << "=\""sv;
        RenderValue(out, value);
        out.put('"');
    }


    // Прочие данные и методы, необходимые для реализации элемента <text>
private:
    template <typename T>
    void RenderValue(std::ostream& out, const T& value) const {
        out << value;
    }

    // Специализация для строк
    void RenderValue(std::ostream& out, const std::string& value) const {
        HtmlEncodeString(out, value);
    }
    void HtmlEncodeString(std::ostream& out, std::string sv) const;
    void RenderObject(const RenderContext& context) const override;

    std::string data_;
    std::string font_weight_= {};
    std::string font_family_={};
    uint32_t font_size_ = 1;
    Point position_;
    Point offset_;
};

class Document : public Object, public ObjectContainer {
public:
    /*
     Метод Add добавляет в svg-документ любой объект-наследник svg::Object.
     Пример использования:
     Document doc;
     doc.Add(Circle().SetCenter({20, 30}).SetRadius(15));
    */

     using Object::Render;

    // Добавляет в svg-документ объект-наследник svg::Object
    void AddPtr(std::unique_ptr<Object>&& obj) override ;


    // Выводит в ostream svg-представление документа
    void Render(std::ostream& out)  const ;

    // Прочие методы и данные, необходимые для реализации класса Document
private:
    void RenderObject(const RenderContext& context) const override;
    std::vector<std::unique_ptr<Object>> objects_;
};

}  // namespace svg
