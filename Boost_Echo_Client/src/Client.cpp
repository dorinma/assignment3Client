//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

//#include <include/Client.h>
#include <iostream>
#include "../include/Client.h"

using boost::asio::ip::tcp;

Client::Client() : userName(), passcode(), inventory(), subId(), subCount(), wantedBook() {}

Client::Client(string username, string passcode) : userName(username), passcode(passcode), inventory(), subId(), subCount(0), wantedBook() {
   // subCount = 0;
}

Client::~Client() {

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
    this->subId[subId] = genre;
}

void Client::setWantedBook(string bookName) { this->wantedBook = bookName; }

string Client::getWantedBook() { return wantedBook; }

void Client::removeBook(string bookName) {
    int index = 0;
    int count = -1;
    for (Book b : inventory) {
        count++;
        if (b.getNameBook() == bookName)
            index = count;
    }
    inventory.erase(inventory.begin() + index);
}

bool Client::findBook(string bookName) {
    for(Book b : inventory) {
        if((b.getExists() == 1) & (b.getNameBook() == bookName))
            return true;
    }
    return false;
}

string Client::toString() {
    string output = "name: "+this->userName + "\npass: "+ this->passcode+"\n";

    output = output + "MY SUBS ARE: \n";

    for(pair<string, string> element : subId) {
        output += element.second + ", ";
    }

    output = output + "\nMY BOOKS ARE: \n";

    for(Book b : inventory) {
        output = output + b.getNameBook() + ", genre " + b.getGenre() +
                ", exist mode:" ;
                if (b.getExists() == 1)
                    output += "true";
                else
                    output += "false";
               output += ", last owner:" + b.getLastOwner() + "\n";
    }
    output += "wantedBookName: "+this->wantedBook+'\n';

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
    return "problem";
}

void Client::removeSubscription(string genreId) {
    subId.erase(genreId);
}
