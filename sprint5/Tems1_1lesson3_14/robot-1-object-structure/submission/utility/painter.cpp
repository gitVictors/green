#include "painter.h"

#include <numbers>

namespace {

constexpr double kWallHeight = 1.5;
constexpr double kCellWidth = 25;
constexpr double kIsometryAngle = 30 * std::numbers::pi_v<double> / 180;

constexpr FieldCoordinate x_off{kCellWidth, 0};
static const FieldCoordinate y_off = kCellWidth * FieldCoordinate{std::sin(kIsometryAngle), -std::cos(kIsometryAngle)};
constexpr FieldCoordinate z_off{0, -kWallHeight * kCellWidth};

constexpr QPoint kObjectSpritePlateLT{453, 242};
constexpr QPoint kObjectSpritePlateRB{507, 299};

inline QPointF ToQPointF(FieldCoordinate c) {
    return {c.x, c.y};
}

template<class Cb>
void DrawTransformed(QPainter& painter, double w, double h, QPointF v1, QPointF v2, QPointF v3, Cb drawer) {
    painter.save();

    double m11 = (v2.x() - v1.x()) / w;
    double m12 = (v3.x() - v1.x()) / h;
    double m21 = (v2.y() - v1.y()) / w;
    double m22 = (v3.y() - v1.y()) / h;

    double dx = v1.x(), dy = v1.y();

    painter.setTransform(QTransform(m11, m21, m12, m22, dx, dy));
    drawer();

    painter.restore();
}

void DrawImageTransformedAndDarkened(QPainter& painter, const QPixmap& img, QPointF v1, QPointF v2, QPointF v3, double darkness) {
    DrawTransformed(painter, img.width(), img.height(), v1, v2, v3, [&]{
        if (darkness < 1) {
            painter.drawPixmap(0, 0, img);
        }
        if (darkness > 0) {
            double prev_opacity = painter.opacity();
            painter.setOpacity(1);
            painter.fillRect(QRect{0, 0, img.width(), img.height()}, QColor::fromRgb(0, 0, 0, static_cast<int>(255 * darkness)));
            painter.setOpacity(prev_opacity);
        }
    });
}

void DrawImageMatchPoints(QPainter& painter, const QPixmap& img, QPoint img_point1, QPoint img_point2, QPointF screen_point1, QPointF screen_point2) {
    painter.save();

    auto d_img = img_point2 - img_point1;
    auto d_screen = screen_point2 - screen_point1;

    painter.translate(screen_point1);
    painter.scale(d_screen.x() / d_img.x(), d_screen.y() / d_img.y());
    painter.translate(-img_point1);
    painter.drawPixmap(0, 0, img);

    painter.restore();
}

QColor DarkenColor(QColor c, float darkness) {
    if (darkness <= 0) {
        return c;
    }
    if (darkness >= 1) {
        return QColor(0, 0, 0, c.alpha());
    }
    int h, s, v, a;
    c.getHsv(&h, &s, &v, &a);
    return QColor::fromHsv(h, s, static_cast<int>(v * (1 - darkness)), a);
}

}

#ifdef PRAC_TESTS
namespace {
CoordinateF last_player_pos{};
}

CoordinateF Painter::GetPlayerPos() {
    return last_player_pos;
}
#endif

FieldCoordinate Painter::Get3dPointWoOffset(CoordinateF pos) const {
    return pos.x_pos * x_off - pos.y_pos * y_off + (pos.z_pos - current_flow_) * z_off;
}

void Painter::PreparePaint(CoordinateF player_pos, Size field_size, Size window_size) {
#ifdef PRAC_TESTS
    ::last_player_pos = player_pos;
#endif

    static const int off_x = 50;
    static const int off_y = 50;
    static const Size off = {off_x, off_y};

    current_flow_ = static_cast<int>(player_pos.z_pos);

    QColor background_color_ = QColor::fromRgb(203, 240, 247);

    painter_.fillRect(QRect{0, 0, window_size.width, window_size.height}, background_color_);

    auto palyer_center_pos = Get3dPointWoOffset(player_pos + CoordinateF{.5, .5});

    Size size_wo_offset = window_size - off * 2;

    if (size_wo_offset.width < (field_size.width - 1) * x_off.x) {
        double k_x = double(size_wo_offset.width) / (field_size.width - 1);
        field_offset_.x = off.width + k_x * player_pos.x_pos - palyer_center_pos.x;
    } else {
        double zero = size_wo_offset.width - (field_size.width - 1) * x_off.x;
        field_offset_.x = off.width + x_off.x * player_pos.x_pos + zero / 2 - palyer_center_pos.x;
    }
    if (size_wo_offset.height < (field_size.height - 1) * std::abs(y_off.y)) {
        double k_y = double(size_wo_offset.height) / (field_size.height - 1);
        field_offset_.y = off.height + k_y * player_pos.y_pos - palyer_center_pos.y;
    } else {
        double zero = size_wo_offset.height - (field_size.height - 1) * std::abs(y_off.y);
        field_offset_.y = off.height + std::abs(y_off.y) * player_pos.y_pos + zero / 2 - palyer_center_pos.y;
    }
}

void Painter::DrawFloor(const Asset &asset, Coordinate pos, double darkness) {
    auto p1 = ToQPointF(Get3dPoint(pos));
    auto p2 = ToQPointF(Get3dPoint(pos + Coordinate{1, 0, 0}));
    auto p3 = ToQPointF(Get3dPoint(pos + Coordinate{0, 1, 0}));

    DrawImageTransformedAndDarkened(painter_, asset.pixmap, p1, p2, p3, darkness);
}

void Painter::DrawWall(const Asset &asset, Coordinate pos, Orientation dir, double darkness) {
    auto other_vertex = dir == Orientation::kHorizontal ? Coordinate{1, 0, 0} : Coordinate{0, 1, 0};

    auto p1 = ToQPointF(Get3dPoint(pos));
    auto p2 = ToQPointF(Get3dPoint(pos + other_vertex));
    auto p3 = ToQPointF(Get3dPoint(pos + Coordinate{0, 0, 1}));

    painter_.setOpacity(0.5);
    DrawImageTransformedAndDarkened(painter_, asset.pixmap, p1, p2, p3, darkness);
    painter_.setOpacity(1);
}

void Painter::DrawObject(const Asset &object_sprite, CoordinateF pos, double darkness) {
    auto p1 = ToQPointF(Get3dPoint(pos));
    auto p2 = ToQPointF(Get3dPoint(pos + CoordinateF{1, 1, 0}));

    painter_.setOpacity(1 - darkness);
    DrawImageMatchPoints(painter_, object_sprite.pixmap, kObjectSpritePlateLT, kObjectSpritePlateRB, p1, p2);
    painter_.setOpacity(1);
}

void Painter::DrawRect(CoordinateF pos1, CoordinateF pos2, CoordinateF pos3, QColor fill_color, QColor edge_color, double edge_width, double darkness) {
    auto p1 = ToQPointF(Get3dPoint(pos1));
    auto p2 = ToQPointF(Get3dPoint(pos2));
    auto p3 = ToQPointF(Get3dPoint(pos3));
    auto p4 = p1 - p2 + p3;

    QPen pen(DarkenColor(edge_color, darkness));
    pen.setWidthF(edge_width);
    painter_.setPen(pen);
    painter_.setBrush(DarkenColor(fill_color, darkness));
    std::vector points = {p1, p2, p3, p4};
    painter_.drawPolygon(points.data(), points.size());
}
