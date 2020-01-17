//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

//#include <include/Client.h>
#include <iostream>
#include "Client.h"

using boost::asio::ip::tcp;

Client::Client() {}

Client::Client(string username, string passcode) : userName(username), passcode(passcode) {
    subCount = 0;
}

const string &Client::getUserName() const {
    return userName;
}

void Client::setUserName(const string &userName) {
    Client::userName = userName;
}

string &Client::getPasscode() {
    return passcode;
}

void Client::setPasscode(const string &passcode) {
    Client::passcode = passcode;
}

vector<Book> &Client::getInventory() {
    return inventory;
}

void Client::setInventory(const vector<Book> &inventory) {
    Client::inventory = inventory;
}

int Client::getSubCount(){
    return subCount;
}

void Client::setSubCount(int subCount) {
    Client::subCount = subCount;
}

unordered_map<string, string> Client::getSubId()  {
    return subId;
}

void Client::setSubId(unordered_map<string, string> subId) { this->subId = subId; }

void Client::addBook(string bookName,string genre, string lastOwner) {
    Book book(bookName, genre, lastOwner);
    this->inventory.push_back(book);
}

void Client::addGenre(string subId, string genre) {
    this->getSubId()[subId] = genre;
}

void Client::setWantedBook(string bookName) { this->wantedBook = bookName; }

string Client::getWantedBook() { return wantedBook; }

void Client::removeBook(string bookName) {
//    string test = "------- ";
//    for (Book b : inventory) {
//        test += b.getNameBook() + ", ";
//    }
//    cout<< test << endl;

    int index = 0;
    int count = -1;
    for (Book b : inventory) {
        count++;
        if (b.getNameBook() == bookName)
            index = count;
    }
    inventory.erase(inventory.begin() + index);
//    test = "------- ";
//    for (Book b : inventory) {
//        test += b.getNameBook() + ", ";
//    }
//    cout<< test << endl;
}

bool Client::findBook(string bookName) {
    for(Book b : inventory) {
        if(b.getExists() == 1 & b.getNameBook() == bookName)
            return true;
    }
    return false;
}

//Book* Client::getBook(string bookName) {
//    if(!findBook(bookName))
//        return nullptr;
//    else
//    {
//        for(Book b : inventory) {
//            if (b.getNameBook() == bookName)
//                return new Book(b.getNameBook(), b.getGenre(), b.getLastOwner(), b.getExists());
//        }
//        return nullptr;
//    }
//}

string Client::toString() {

    string output="name: "+this->userName+"\npass: "+ this->passcode+"\n";
                    "MY BOOKS ARE: \n";
    for(Book b : inventory) {
        output = output + b.getNameBook() + ", genre " + b.getGenre() +
                ", exist mode:" ;
                if (b.getExists() == 1)
                    output = output + "true";
                else
                    output = output + "false";
               output = output + ", last owner:" + b.getLastOwner() + "\n";
    }
    output=output+"wantedBookName: "+this->wantedBook+'\n';

    return output;
}

void Client::setExistMode(string bookName, string genre, string owner, bool exist) {
    Book updateBook(bookName, genre, owner);
    updateBook.setExists(exist);
    removeBook(bookName);
    this->inventory.push_back(updateBook);
}

string Client::getLastOwner(string bookName) {
    for(Book b : inventory) {
        if (b.getNameBook() == bookName)
            return b.getLastOwner();
    }
    return "problemmmmmm";
}
