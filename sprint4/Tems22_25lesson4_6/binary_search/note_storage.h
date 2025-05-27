#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>

using Note = std::string;

class NoteStorage {
public:
    using Iterator = std::vector<Note>::const_iterator;

    NoteStorage() = default;

    void AddNote(const int page, const Note& note) {
        if (!pages_.empty() && page < pages_.back()) {
            // throw std::invalid_argument("Page number must not decrease.");
            return;
        }
        notes_.push_back(note);
        pages_.push_back(page);
    }

    std::pair<Iterator, Iterator> SearchNotes(int page_from, int page_to) const {
        if (notes_.empty() || page_from > page_to) {
            return {notes_.end(), notes_.end()};
        }

        auto lower = std::lower_bound(pages_.begin(), pages_.end(), page_from);
        auto upper = std::upper_bound(lower, pages_.end(), page_to);

        size_t lower_idx = std::distance(pages_.begin(), lower);
        size_t upper_idx = std::distance(pages_.begin(), upper);

        auto notes_begin = notes_.begin();
        auto notes_end = notes_.begin();

        std::advance(notes_begin, lower_idx);
        std::advance(notes_end, upper_idx);

        return {notes_begin, notes_end};
    }

private:
    std::vector<int> pages_;
    std::vector<Note> notes_;
};
