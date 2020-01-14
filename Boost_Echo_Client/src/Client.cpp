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

