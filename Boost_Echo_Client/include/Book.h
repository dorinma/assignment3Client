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

    void setNameBook(const string &nameBook);

    const string &getGenre() const;

    void setGenre(const string &genre);

    const string &getLastOwner() const;

    void setLastOwner(const string &lastOwner);

    void setExists(bool exists);

    bool getExists();

private:
    string nameBook;
    string genre;
    string lastOwner;
    bool exists;

};


#endif //ASSIGNMENT3CLIENT_BOOK_H
