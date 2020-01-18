//
// Created by hadas on 13/01/2020.
//

#ifndef ASSIGNMENT3CLIENT_BOOK_H
#define ASSIGNMENT3CLIENT_BOOK_H

#include <string>

using namespace std;

class Book {

public:
    Book(string bookName, string genre, string lastOwner, bool exists);

    Book(string bookName, string genre, string lastOwner);

    const string &getNameBook() const;

    const string &getGenre() const;

    const string &getLastOwner() const;

    void setExists(bool exists);

    bool getExists();

    string toString();

private:
    string nameBook;
    string genre;
    string lastOwner;
    bool exists;

};


#endif //ASSIGNMENT3CLIENT_BOOK_H
