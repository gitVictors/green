#include <iostream>
#include <cassert>

#include "note_storage.h"


void Test1() {
    // В пустом хранилище все найденные диапазоны должны быть пустыми.
    NoteStorage empty_storage;
    auto empty_range1 = empty_storage.SearchNotes(0, 0);
    assert(empty_range1.first == empty_range1.second);
    auto empty_range2 = empty_storage.SearchNotes(0, 100);
    assert(empty_range2.first == empty_range2.second);
    auto empty_range3 = empty_storage.SearchNotes(100, 200);
    assert(empty_range3.first == empty_range3.second);
}

void Test2() {
    using namespace std::literals;
    // Хранилище с одной заметкой, сделанной на странице 100.
    NoteStorage storage;
    storage.AddNote(100, "Важная формула"s);

    // Диапазоны до и после единственной заметки должны быть пустыми.
    auto empty_range1 = storage.SearchNotes(0, 99);
    assert(empty_range1.first == empty_range1.second);
    auto empty_range2 = storage.SearchNotes(101, 200);
    assert(empty_range2.first == empty_range2.second);

    // Следующие диапазоны должны содержать одну заметку - "Важная формула".
    auto range1 = storage.SearchNotes(100, 100);
    assert(std::distance(range1.first, range1.second) == 1);
    assert(*range1.first == "Важная формула"s);
    auto range2 = storage.SearchNotes(0, 200);
    assert(std::distance(range2.first, range2.second) == 1);
    assert(*range2.first == "Важная формула"s);
    auto range3 = storage.SearchNotes(100, 200);
    assert(std::distance(range3.first, range3.second) == 1);
    assert(*range3.first == "Важная формула"s);
}

void Test3() {
    using namespace std::literals;
    // Хранилище с произвольным набором заметок.
    NoteStorage storage;

    storage.AddNote(1, "Заметка 1"s);
    storage.AddNote(5, "Заметка 2"s);
    storage.AddNote(6, "Заметка 3"s);

    // В данный момент в хранилище три заметки со страницами = {1, 5, 6}
    auto range1 = storage.SearchNotes(0, 100);
    assert(std::distance(range1.first, range1.second) == 3);
    assert(*range1.first == "Заметка 1"s);
    assert(*(range1.first + 2) == "Заметка 3"s);
    auto range2 = storage.SearchNotes(2, 5);
    assert(std::distance(range2.first, range2.second) == 1);
    assert(*range2.first == "Заметка 2"s);
    auto range3 = storage.SearchNotes(1, 4);
    assert(std::distance(range3.first, range3.second) == 1);
    assert(*range3.first == "Заметка 1"s);

    storage.AddNote(7, "Заметка 4"s);
    storage.AddNote(10, "Заметка 5"s);
    storage.AddNote(100, "Заметка 6"s);

    // В данный момент в хранилище шесть заметок со страницами = {1, 5, 6, 7, 10, 100}
    auto range4 = storage.SearchNotes(0, 100);
    assert(std::distance(range4.first, range4.second) == 6);
    assert(*(range4.first + 4) == "Заметка 5"s);
    auto range5 = storage.SearchNotes(2, 11);
    assert(std::distance(range5.first, range5.second) == 4);
    auto range6 = storage.SearchNotes(8, 8);
    assert(std::distance(range6.first, range6.second) == 0);
    auto range7 = storage.SearchNotes(100, 200);
    assert(std::distance(range7.first, range7.second) == 1);
}


int main() {
    Test1();
    Test2();
    Test3();
    std::cout << "All tests passed" << std::endl;
}
