#pragma once

#include <cassert>
#include <cmath>
#include <optional>
#include <tuple>
#include <string>
#include <sstream>

enum Orientation {
    kVertical, kHorizontal
};

enum Direction {
    kUp, kLeft, kRight, kDown
};

inline Direction Invert(Direction dir) {
    switch(dir) {
        case kUp: return kDown;
        case kLeft: return kRight;
        case kRight: return kLeft;
        case kDown: return kUp;
    }
}

inline Orientation ToOrientation(Direction dir) {
    switch(dir) {
    case kUp:
    case kDown: return kVertical;
    case kRight:
    case kLeft: return kHorizontal;
    }
}

struct Size {
    int width = 0;
    int height = 0;
};

struct CoordinateF {
    double Norm() const {
        return std::sqrt(Scalar(*this, *this));
    }
    static double Scalar(CoordinateF l, CoordinateF r) {
        return
            l.x_pos * r.x_pos +
            l.y_pos * r.y_pos +
            l.z_pos * r.z_pos;
    }
    CoordinateF Rotate90() const {
        return {y_pos, -x_pos, z_pos};
    }

    double x_pos = 0;
    double y_pos = 0;
    double z_pos = 0;
};

struct Coordinate2D {
    int x_pos = 0;
    int y_pos = 0;
};

struct Coordinate {
    static Coordinate FromDirection(Direction dir) {
        switch(dir) {
        case Direction::kUp:
            return Coordinate{.y_pos = -1};
        case Direction::kDown:
            return Coordinate{.y_pos = +1};
        case Direction::kLeft:
            return Coordinate{.x_pos = -1};
        case Direction::kRight:
            return Coordinate{.x_pos = +1};
        }
        assert(false);
    }
    static Coordinate FromOrientation(Orientation dir) {
        switch(dir) {
        case Orientation::kHorizontal:
            return Coordinate{.x_pos = 1};
        case Orientation::kVertical:
            return Coordinate{.y_pos = 1};
        }
        assert(false);
    }

    static Coordinate AddLevel(Coordinate2D xy, int level) {
        return {xy.x_pos, xy.y_pos, level};
    }

    Coordinate Rotate90() const {
        return {y_pos, -x_pos, z_pos};
    }

    static Coordinate Round(CoordinateF src) {
        auto round = [](double f) {
            return static_cast<int>(std::round(f));
        };
        return Coordinate{.x_pos = round(src.x_pos), .y_pos = round(src.y_pos), .z_pos = round(src.z_pos) };
    }

    operator CoordinateF() const {
        return {static_cast<double>(x_pos), static_cast<double>(y_pos), static_cast<double>(z_pos)};
    }

    operator Coordinate2D() const {
        return {x_pos, y_pos};
    }

    auto ToTuple() const {
        return std::tuple{x_pos, y_pos, z_pos};
    }

    auto operator <=>(const Coordinate r) const {
        return ToTuple() <=> r.ToTuple();
    }
    auto operator ==(const Coordinate r) const {
        return ToTuple() == r.ToTuple();
    }

    int x_pos = 0;
    int y_pos = 0;
    int z_pos = 0;
};

inline std::optional<Direction> GetDirectionToward(Coordinate from, Coordinate to) {
    if (from.x_pos < to.x_pos) {
        return Direction::kRight;
    } 
    if(from.x_pos > to.x_pos) {
        return Direction::kLeft;
    } 
    if (from.y_pos < to.y_pos) {
        return Direction::kDown;
    } 
    if (from.y_pos > to.y_pos) {
        return Direction::kUp;
    }
    return std::nullopt;
}

inline constexpr Coordinate operator+ (Coordinate src1, Coordinate src2) {
    return {src1.x_pos + src2.x_pos, src1.y_pos + src2.y_pos, src1.z_pos + src2.z_pos};
}

inline constexpr Coordinate2D operator+ (Coordinate2D src1, Coordinate2D src2) {
    return {src1.x_pos + src2.x_pos, src1.y_pos + src2.y_pos};
}

inline constexpr CoordinateF operator+ (CoordinateF src1, CoordinateF src2) {
    return {src1.x_pos + src2.x_pos, src1.y_pos + src2.y_pos, src1.z_pos + src2.z_pos};
}

inline constexpr CoordinateF operator- (CoordinateF src1, CoordinateF src2) {
    return {src1.x_pos - src2.x_pos, src1.y_pos - src2.y_pos, src1.z_pos - src2.z_pos};
}

inline constexpr CoordinateF operator* (CoordinateF src1, double coeff) {
    return {src1.x_pos * coeff, src1.y_pos * coeff, src1.z_pos * coeff};
}

inline constexpr Coordinate operator* (Coordinate src1, int coeff) {
    return {src1.x_pos * coeff, src1.y_pos * coeff, src1.z_pos * coeff};
}

inline constexpr Coordinate2D operator* (Coordinate2D src1, int coeff) {
    return {src1.x_pos * coeff, src1.y_pos * coeff};
}

inline constexpr Size operator* (Size src, int coeff) {
    return {src.width * coeff, src.height * coeff};
}

inline constexpr CoordinateF operator+ (CoordinateF src1, Size src2) {
    return {src1.x_pos + src2.width, src1.y_pos + src2.height, src1.z_pos};
}

inline constexpr CoordinateF operator- (CoordinateF src1, Size src2) {
    return {src1.x_pos - src2.width, src1.y_pos - src2.height, src1.z_pos};
}

inline constexpr Size operator+ (Size src1, Size src2) {
    return {src1.width + src2.width, src1.height + src2.height};
}

inline constexpr Size operator- (Size src1, Size src2) {
    return {src1.width - src2.width, src1.height - src2.height};
}

inline double GetDistance(CoordinateF from, CoordinateF to) {
    return (to - from).Norm();
}

struct FieldCoordinate {
    double x = 0;
    double y = 0;
};

inline constexpr FieldCoordinate operator* (FieldCoordinate src, double multiplyer) {
    return {src.x * multiplyer, src.y * multiplyer};
}

inline constexpr FieldCoordinate operator* (double multiplyer, FieldCoordinate src) {
    return {src.x * multiplyer, src.y * multiplyer};
}

inline constexpr FieldCoordinate operator/ (FieldCoordinate src, double multiplyer) {
    return {src.x / multiplyer, src.y / multiplyer};
}

inline constexpr FieldCoordinate operator/ (double multiplyer, FieldCoordinate src) {
    return {src.x / multiplyer, src.y / multiplyer};
}

inline constexpr FieldCoordinate operator+ (FieldCoordinate src1, FieldCoordinate src2) {
    return {src1.x + src2.x, src1.y + src2.y};
}

inline constexpr FieldCoordinate operator- (FieldCoordinate src1, FieldCoordinate src2) {
    return {src1.x - src2.x, src1.y - src2.y};
}

inline constexpr FieldCoordinate operator+ (FieldCoordinate src1, Size src2) {
    return {src1.x + src2.width, src1.y + src2.height};
}

inline constexpr FieldCoordinate operator- (FieldCoordinate src1, Size src2) {
    return {src1.x - src2.width, src1.y - src2.height};
}

inline std::string ToString(Coordinate c) {
    std::ostringstream out;
    out << c.x_pos << "," << c.y_pos << "," << c.z_pos;
    return out.str();
}

inline std::string ToString(CoordinateF c) {
    std::ostringstream out;
    out << c.x_pos << "," << c.y_pos << "," << c.z_pos;
    return out.str();
}

inline std::string ToString(Direction dir) {
    switch(dir) {
        case kUp: return "up";
        case kLeft: return "left";
        case kRight: return "right";
        case kDown: return "down";
    }
    assert(false);
}

inline std::string ToString(Orientation dir) {
    switch(dir) {
        case kVertical: return "vertical";
        case kHorizontal: return "horizontal";
    }
    assert(false);
}
