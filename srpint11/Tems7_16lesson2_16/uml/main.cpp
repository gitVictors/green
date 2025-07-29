#include <cassert>
#include <string>
#include <iostream>

using namespace std;

class House {
    // Реализуйте самостоятельно
public :
    House (int len, int width, int height):
        length_(len)
        ,width_(width)
        , height_(height)

    {
    }
    int GetLength() const { return length_; }
    int GetWidth ()  const { return width_;  }
    int GetHeight () const {  return height_; }
private:
    int length_ = 0;
    int width_ = 0;
    int height_ = 0;
};

class Resources {
    // Реализуйте самостоятельно
public:
    Resources (int brick_count):
        brick_count_(brick_count)
    {
    }

    void TakeBricks(int count) {
        if (count < 0 || count > brick_count_) {
            throw out_of_range("Invalid brick count");
        }
        brick_count_ -= count;
    }

    int GetBrickCount () const { return brick_count_; }

private:
    int brick_count_;
};

struct HouseSpecification {
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder {
    // Реализуйте самостоятельно
public:
    Builder (Resources &res)
        : resourse_(res)
    {
    }

    House BuildHouse(HouseSpecification spec){

        int perimeter = 2 * (spec.length + spec.width);
        int rows = spec.height * 8; // 8 рядов на 1 метр высоты
        int bricks_needed = perimeter * 4 * rows; // 4 кирпича на 1 метр ряда

        try {
            resourse_.TakeBricks(bricks_needed);
        }catch (const out_of_range&){
            throw std::runtime_error("not bricket");
        }

        House house (spec.length, spec.width, spec.height );
        return house;
    }
private:
    Resources& resourse_;
};

int main() {

    Resources resources{10000};

    Builder builder1{resources};
    Builder builder2{resources};

    House house1 = builder1.BuildHouse(HouseSpecification{12, 9, 3});
    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{8, 6, 3});
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{4, 3, 2});
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;
}
