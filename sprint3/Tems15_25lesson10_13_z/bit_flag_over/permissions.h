#pragma once

#include <bitset>
#include <iostream>
#include <sstream>

enum class Permissions {
    READ = 0x1,
    WRITE = 0x2,
    EXECUTE  = 0x4
};

class FileAccess {
public:
    FileAccess() : permissions_(0) {}

    // Устанавливает указанный флаг.
    void SetPermission(Permissions perm){
        permissions_ |= static_cast<int>(perm);
    }

    // Проверяет, есть ли указанный флаг.
    bool CheckPermission(Permissions perm){
        return (permissions_ & static_cast<int>(perm))  != 0;
    }

    // Удаляет флаг.
    void RemovePermission(Permissions perm){
        permissions_ &= ~static_cast<int>(perm);
    }

    // Инвертирует флаг.
    void TogglePermission(Permissions perm){
        permissions_ ^= static_cast<int> (perm);
    }

    // Преобразует набор прав в строку вида 0000.
    std::string ToString() {
        std::ostringstream s;
        s << std::bitset<4>(permissions_);
        return s.str();
    }
private:
    int permissions_;
};

