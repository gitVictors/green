#include "tv_control.h"

int main() {
    TV tv;

    while (TVControl::ReadAndApplyCommand(tv)) {
    }
}