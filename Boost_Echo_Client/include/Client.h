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

    string &getPasscode();

    void setPasscode(const string &passcode);

    vector<Book> &getInventory();

    void setInventory(const vector<Book> &inventory);

    unordered_map<string, string>getSubId();

    void setSubId(const unordered_map<string string>subId);

    int getSubCount();

    void setSubCount(int subCount);

    void addBook(Book book);

    void addGenre(string subId, string genre);
};


#endif //BOOST_ECHO_CLIENT_CLIENT_H