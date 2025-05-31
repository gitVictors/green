#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "book.h"

// Записывает книгу в переданный поток.
void WriteBook(std::ostream& out, const Book& book) {
    out  << book.title << std::endl;
    out  << book.author << std::endl;
    out  << book.publication_year << std::endl;
}

// Считывает книгу из переданного потока.
Book ReadBook(std::istream& in) {
    Book book;
    std::getline(in, book.title);
    std::getline (in, book.author);
    in >> book.publication_year >> std::ws; 
    return book;
}

// Сериализует книгу в строку.
std::string BookToString(const Book& book) {
    std::ostringstream out;
    WriteBook (out, book) ;
    return out.str();
}

// Десериализует книгу из строки.
Book StringToBook(const std::string& str) {
    std::istringstream in;
    in.str(str);
    return ReadBook(in);
}

bool BooksAreEqual(const Book& book1, const Book& book2) {
    return (book1.title == book2.title) && (book1.author == book2.author)
        && (book1.publication_year == book2.publication_year);
}

int main() {
    using namespace std::literals;

    const Book book1{.title = "White Fang"s, .author = "Jack London"s, .publication_year = 1906};
    const Book book2{.title = "Moby-Dick"s, .author = "Herman Melville"s, .publication_year = 1851};

    {
        std::stringstream strm;
        WriteBook(strm, book1);
        WriteBook(strm, book2);

        auto book1_copy = ReadBook(strm);
        auto book2_copy = ReadBook(strm);

        assert(BooksAreEqual(book1_copy, book1));
        assert(BooksAreEqual(book2_copy, book2));
    }

    {
        const std::string serializedBook = BookToString(book1);
        const Book deserializedBook = StringToBook(serializedBook);
        assert(BooksAreEqual(book1, deserializedBook));
    }
}
