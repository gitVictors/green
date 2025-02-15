#pragma once
#include "tv.h"

class TVControl {
public:
    // Конструктор TVControl должен принять ссылку
    // на телевизор и сохранить её в поле класса.
    // Определите его с списком инициализации в tv_control.cpp

    // Замените метод ReadAndApplyCommand, чтобы он стал нестатическим.
    // bool ReadAndApplyCommand() const;
    static bool ReadAndApplyCommand(TV& tv);

private:
    /* Приватные методы класса должны стать нестатическими и не принимать ссылку на tv. */
    void Info(const TV& tv);
    void TurnOn(TV& tv);
    void TurnOff(TV& tv);
    bool SelectChannel(TV& tv);
    //Ссылка натв
    TV& tv_;
};