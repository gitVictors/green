#pragma once
#include "tv.h"

class TVControl {
public:
    // Конструктор TVControl должен принять ссылку
    // на телевизор и сохранить её в поле класса.
    // Определите его с списком инициализации в tv_control.cpp
    TVControl (TV& tv): tv_(tv){

    }

    // Замените метод ReadAndApplyCommand, чтобы он стал нестатическим.
    // bool ReadAndApplyCommand() const;
    bool ReadAndApplyCommand()const;

private:
    /* Приватные методы класса должны стать нестатическими и не принимать ссылку на tv. */
    void Info() const;
    void TurnOn()const;
    void TurnOff()const;
    bool SelectChannel()const;
    //Ссылка на тв
    TV& tv_;
};