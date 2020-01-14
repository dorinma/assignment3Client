//
// Created by hadas on 13/01/2020.
//

#ifndef ASSIGNMENT3CLIENT_BOOK_H
#define ASSIGNMENT3CLIENT_BOOK_H

#include <string>

using namespace std;

class Book {

private:
public:
    Book(const string &nameBook, const string &genre, const string &lastOwner);


private:
public:
    const string &getNameBook() const;

    void setNameBook(const string &nameBook);

    const string &getGenre() const;

    void setGenre(const string &genre);

    const string &getLastOwner() const;

    void setLastOwner(const string &lastOwner);

private:
    string nameBook;
    string genre;
    string lastOwner;

};


#endif //ASSIGNMENT3CLIENT_BOOK_H
