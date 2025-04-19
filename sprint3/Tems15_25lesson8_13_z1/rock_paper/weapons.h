#pragma once

enum class Weapons { ROCK, PAPER, SCISSORS };

// Напишите здесь реализацию перегрузки.

inline bool operator<(Weapons lft, Weapons rgt){
    return (
        (lft == Weapons::ROCK && rgt == Weapons::PAPER) ||
        (lft == Weapons::PAPER && rgt == Weapons::SCISSORS) ||
        (lft == Weapons::SCISSORS && rgt == Weapons::ROCK )
        );
}
