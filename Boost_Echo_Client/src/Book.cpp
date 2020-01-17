//
// Created by hadas on 13/01/2020.
//

//#include <include/Book.h>
#include "Book.h"

using namespace std;

Book::Book(string bookName, string genre, string lastOwner) : nameBook(bookName), genre(genre), lastOwner(lastOwner){
    exists = true;
}

Book::Book(string bookName, string genre, string lastOwner, bool exists) : nameBook(bookName), genre(genre), lastOwner(lastOwner), exists(exists) {}

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

bool Book::getExists() { return exists; }

void Book::setExists(bool exists) { this->exists = exists; }

string Book::toString() {
    string output = "BOOK: " + this->nameBook+ ",'";
    output += "\tgenre: " + this->genre + ",";
    output += "\tlastOwner: " + this->lastOwner+ ",";
    if(this->exists)
    {
        output += "\texist: true";
    }
    else
    {
        output += "\texist: false";
    }

    return output;
}