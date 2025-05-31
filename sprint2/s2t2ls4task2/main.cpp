#include "tv_control.h"
#include "tv.h"

int main() {
    TV tv;
    const TVControl control{tv};

    while (control.ReadAndApplyCommand()) {
    }
}

