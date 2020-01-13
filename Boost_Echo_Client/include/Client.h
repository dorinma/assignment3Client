//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H

#include "Protocol.h"
#include "Book.h"
#include <string>
#include <vector>

using namespace std;

class Client {
private:

    string userName;
    string passcode;
    vector<Book> inventory;
    unordered_map<string, string> subId;
    int subCount;

public:
    Client(string username, string passcode);

    const string &getUserName() const;

    void setUserName(const string &userName);

    const string &getPasscode() const;

    void setPasscode(const string &passcode);

    const vector<Book> &getInventory() const;

    void setInventory(const vector<Book> &inventory);

    const unordered_map<string, string>getSubId() const;

    void setSubId(const unordered_map<string string>subId);

    int getSubCount() const;

    void setSubCount(int subCount);

    void addBook(Book book);
};


#endif //BOOST_ECHO_CLIENT_CLIENT_H