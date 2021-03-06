//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H

#include "Book.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/asio.hpp>

using namespace std;

class Client {
private:
    string userName;
    string passcode;
    vector<Book> inventory;
    unordered_map<string, string> subId;
    int subCount;
    string wantedBook;


public:
    Client();

    ~Client();

    Client(string username, string passcode);

    const string &getUserName() const;

    void setUserName(const string &userName);

    string &getPasscode();

    void setPasscode(const string &passcode);

    vector<Book> &getInventory();

    void setInventory(const vector<Book> &inventory);

    unordered_map<string, string>getSubId();

    void setSubId(unordered_map<string, string> subId);

    int getSubCount();

    void setSubCount(int subCount);

    void addBook(string bookName,string genre, string lastOwner);

    void addGenre(string subId, string genre);

    void removeSubscription(string genreId);

    void removeBook(string bookName);

    void setWantedBook(string bookName);

    string getWantedBook();

    bool findBook(string bookName);

    Book* getBook(string bookName);

    string toString();

    void setExistMode(string bookName, string genre, string owner, bool exist);

    string getLastOwner(string bookName);

};


#endif //BOOST_ECHO_CLIENT_CLIENT_H