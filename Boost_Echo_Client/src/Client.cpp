//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "Client.h"
#include "FrameObject.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "connectionHandler.h"
#include <boost/lexical_cast.hpp>
//#include <stdlib.h>

//using namespace std;
using boost::asio::ip::tcp;


//Constructor

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

void Client::setSubId(const int subId) {}

void Client::addBook(Book book) {
    this->inventory.push_back(book);
}

void Client::addGenre(string subId, string genre) {
    this->getSubId()[subId] = genre;
}

void Client::setWantedBook(string bookName) { this->wantedBook = bookName; }

string Client::getWantedBook() { return wantedBook; }

void Client::removeBook(string bookName) {
    int index = 0;
    int count = -1;
    for (Book b : inventory) {
        count++;
        if (b.getNameBook().compare(bookName))
            index = count;
    }
    inventory.erase(inventory.begin() + index);
}

bool Client::findBook(string bookName) {
    for(Book b : inventory) {
        if(b.getNameBook().compare(bookName))
            return true;
    }
    return false;
}

Book* Client::getBook(string bookName) {
    if(!findBook(bookName))
        return nullptr;
    else
    {
        for(Book b : inventory) {
            if (b.getNameBook().compare(bookName))
                return new Book(b.getNameBook(), b.getGenre(), b.getLastOwner(), b.getExists());
        }
        return nullptr;
    }
}