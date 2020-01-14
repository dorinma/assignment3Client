//
// Created by hadas on 13/01/2020.
//

#include "Book.h"

using namespace std;

Book::Book(const string &nameBook, const string &genre, const string &lastOwner) :
nameBook(nameBook), genre(genre), lastOwner(lastOwner){}

const string &Book::getNameBook() const {
    return nameBook;
}

void Book::setNameBook(const string &nameBook) {
    Book::nameBook = nameBook;
}

const string &Book::getGenre() const {
    return genre;
}

void Book::setGenre(const string &genre) {
    Book::genre = genre;
}

const string &Book::getLastOwner() const {
    return lastOwner;
}

void Book::setLastOwner(const string &lastOwner) {
    Book::lastOwner = lastOwner;
}
