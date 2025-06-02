#pragma once

#include "geometry.h"
#include "assets.h"

#include <QPixmap>
#include <QPainter>

class Painter {
public:
    Painter(QPainter& painter) : painter_{painter} {}

    FieldCoordinate Get3dPointWoOffset(CoordinateF pos) const;

    FieldCoordinate Get3dPoint(CoordinateF pos) const {
        return Get3dPointWoOffset(pos) + field_offset_;
    }

    void PreparePaint(CoordinateF player_pos, Size field_size, Size window_size);

    void DrawFloor(const Asset& asset, Coordinate pos, double darkness=0);

    void DrawWall(const Asset& asset, Coordinate pos, Orientation dir, double darkness=0);

    void DrawObject(const Asset& object_sprite, CoordinateF pos, double darkness=0);

    void DrawRect(CoordinateF p1, CoordinateF p2, CoordinateF p3, QColor fill_color, QColor edge_color, double edge_width=1, double darkness=0);

#ifdef PRAC_TESTS
    static CoordinateF GetPlayerPos();
#endif

private:
    int current_flow_ = 0;
    QPainter& painter_;
    FieldCoordinate field_offset_;
};
