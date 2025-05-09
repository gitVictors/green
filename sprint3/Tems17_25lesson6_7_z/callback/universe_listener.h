#pragma once
#include <iostream>
#include <vector>
#include <functional>

#include "domain.h"

template<UniverseSignalType type>
using Callback = std::function<void (const UniverseSignal<type>& signal)>;

class UniverseListener {
public:
    UniverseListener() {
    }

    // Этот метод предназначен для использования в тестах.
    // Игнорируйте его.
    void Run();

    void SetCallbackUfo(const Callback<UniverseSignalType::UFO>& callback) {
        callback_ufo = callback;
    }
    void SetCallbackSupernova(const Callback<UniverseSignalType::SUPERNOVA>& callback) {
        callback_supernova = callback;
    }
    void SetCallbackDysonSphere(const Callback<UniverseSignalType::DYSON_SPHERE>& callback) {
        callback_dyson_sphere = callback;
    }
    void SetCallbackGravitationalLens(const Callback<UniverseSignalType::GRAVITATIONAL_LENS>& callback) {
        callback_gravitational_lens = callback;
    }

private:
    Callback<UniverseSignalType::UFO> callback_ufo;
    Callback<UniverseSignalType::SUPERNOVA> callback_supernova;
    Callback<UniverseSignalType::DYSON_SPHERE> callback_dyson_sphere;
    Callback<UniverseSignalType::GRAVITATIONAL_LENS> callback_gravitational_lens;
};