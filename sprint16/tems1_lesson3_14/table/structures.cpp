#include "common.h"

#include <cctype>
#include <sstream>

const int LETTERS = 26;
const int MAX_POSITION_LENGTH = 17;
const int MAX_POS_LETTER_COUNT = 3;

const Position Position::NONE = {-1, -1};

// Реализуйте методы:
bool Position::operator==(const Position rhs) const {}

bool Position::operator<(const Position rhs) const {}

bool Position::IsValid() const {}

std::string Position::ToString() const {}

Position Position::FromString(std::string_view str) {}