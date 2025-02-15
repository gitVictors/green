

int main() {
    TV tv;
    const TVControl control{tv};

    while (control.ReadAndApplyCommand()) {
    }
}

