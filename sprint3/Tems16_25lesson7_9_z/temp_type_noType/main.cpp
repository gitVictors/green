#include <cassert>
#include "universe_model.h"

int main() {
    const double EPS = 0.0001;
    {
        auto universe_model = UniverseModel<0, 0>();
        assert(universe_model.CountStars(0) == 0);
        assert(universe_model.CountStars(100) == 0);
    } {
        auto universe_model = UniverseModel<1, 1>();
        assert(universe_model.CountStars(0) == 0);
        assert(abs(universe_model.CountStars(1) - 4.9348) < EPS);
        assert(abs(universe_model.CountStars(10) - 49.348) < EPS);
        assert(abs(universe_model.CountStars(100) - 493.48022) < EPS);
    } {
        auto universe_model = UniverseModel<7, 1>();
        assert(universe_model.CountStars(0) == 0);
        assert(abs(universe_model.CountStars(1.1) - 5.42828) < EPS);
        assert(abs(universe_model.CountStars(10.5) - 51.8154) < EPS);
        assert(abs(universe_model.CountStars(100) - 493.48022) < EPS);
    } {
        auto universe_model = UniverseModel<7, 3>();
        assert(abs(universe_model.CountStars(1.1) - 146.5636) < EPS);
        assert(abs(universe_model.CountStars(10.5) - 1399.0164) < EPS);
        assert(abs(universe_model.CountStars(100) - 13323.96594) < EPS);
    }
    {
        auto universe_model = UniverseModel<8, 1>();
        assert(universe_model.CountStars(0) == 0);
        assert(universe_model.CountStars(1) == 1);
        assert(universe_model.CountStars(1.1) == 1.1);
        assert(universe_model.CountStars(10.5) == 10.5);
        assert(universe_model.CountStars(100) == 100);
    } {
        auto universe_model = UniverseModel<8, 2>();
        assert(universe_model.CountStars(1) == 4);
        assert(universe_model.CountStars(1.1) == 4.4);
        assert(universe_model.CountStars(10.5) == 42);
        assert(universe_model.CountStars(100) == 400);
    } {
        auto universe_model = UniverseModel<8, 111>();
        assert(universe_model.CountStars(1) == 12321);
        assert(universe_model.CountStars(1.1) == 13553.1);
        assert(universe_model.CountStars(10.5) == 129370.5);
        assert(universe_model.CountStars(15) == 184815);
    }
    {
        auto universe_model = UniverseModel<9, 1>();
        assert(universe_model.CountStars(0) == 0);
        assert(abs(universe_model.CountStars(1) - 4.18879) < EPS);
        assert(abs(universe_model.CountStars(1.1) - 4.60767) < EPS);
        assert(abs(universe_model.CountStars(10.5) - 43.9823) < EPS);
        assert(abs(universe_model.CountStars(115) - 481.71087) < EPS);
    } {
        auto universe_model = UniverseModel<9, 13>();
        assert(abs(universe_model.CountStars(1) - 9202.77208) < EPS);
        assert(abs(universe_model.CountStars(1.1) - 10123.04929) < EPS);
        assert(abs(universe_model.CountStars(10.5) - 96629.10684) < EPS);
        assert(abs(universe_model.CountStars(16) - 147244.35327) < EPS);
    } {
        auto universe_model = UniverseModel<19, 24>();
        assert(abs(universe_model.CountStars(1) - 57905.83579) < EPS);
        assert(abs(universe_model.CountStars(1.1) - 63696.41937) < EPS);
        assert(abs(universe_model.CountStars(10.5) - 608011.2758) < EPS);
        assert(abs(universe_model.CountStars(16) - 926493.37265) < EPS);
    }
}
