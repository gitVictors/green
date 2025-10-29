#include "common.h"

#include <cctype>
#include <sstream>

const int LETTERS = 26;
const int MAX_POSITION_LENGTH = 17;
const int MAX_POS_LETTER_COUNT = 3;

const Position Position::NONE = {-1, -1};

// Реализуйте методы:
bool Position::operator==(const Position rhs) const {
    return (this->col == rhs.col) && (this->row == rhs.row);
}

bool Position::operator<(const Position rhs) const {
    return (this->col < rhs.col) && (this->row < rhs.row);
}

bool Position::IsValid() const {
    return row >= 0 && col >= 0 && row < MAX_ROWS && col < MAX_COLS;
}



std::string Position::ToString() const {

    if (!IsValid()) {
        return "";
    }

    // Преобразуем номер столбца в буквенное представление
    std::string col_str;
    int col_temp = col;

    do {
        col_str.insert(col_str.begin(), 'A' + (col_temp % LETTERS));
        col_temp = col_temp / LETTERS - 1;
    } while (col_temp >= 0);

    // Преобразуем номер строки (внутренний + 1 = внешний)
    std::string row_str = std::to_string(row + 1);

    return col_str + row_str;
}

Position Position::FromString(std::string_view str) {

    // Пустая строка или слишком длинная — невалидный индекс
    if (str.empty() || str.size() > MAX_POSITION_LENGTH) {
        return Position::NONE;
    }

    // Ищем первую цифру — конец буквенной части
    size_t digit_pos = 0;
    while (digit_pos < str.size() && std::isalpha(static_cast<unsigned char>(str[digit_pos]))) {
        ++digit_pos;
    }

    // Если нет букв или цифр — невалидно
    if (digit_pos == 0 || digit_pos > MAX_POS_LETTER_COUNT || digit_pos == str.size()) {
        return Position::NONE;
    }

    // Разделяем на буквы и цифры
    std::string_view letters_part = str.substr(0, digit_pos);
    std::string_view digits_part = str.substr(digit_pos);

    // Проверяем, что в digits_part только цифры
    for (char c : digits_part) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return Position::NONE;
        }
    }

    //Проверяем, что все буквы в верхнем регистре ===
    for (char ch : letters_part) {
        if (!std::isupper(static_cast<unsigned char>(ch))) {
            return Position::NONE;
        }
    }

    // Правильное преобразование букв в номер столбца ===
    int col = 0;
    for (char ch : letters_part) {
        col = ( col * LETTERS ) + ( ch - 'A' + 1 );
    }
    col--;

    // Преобразуем цифры в номер строки (внутренний = внешний - 1)
    std::string digits_str(digits_part);
    std::stringstream ss(digits_str);
    int row;
    ss >> row;

    // Проверяем успешность преобразования и границы
    if (ss.fail() || !ss.eof() || row < 1) {
        return Position::NONE;
    }
    row--;

    // Проверяем границы
    Position result{row, col};
    if (!result.IsValid()) {
        return Position::NONE;
    }

    return result;
}
