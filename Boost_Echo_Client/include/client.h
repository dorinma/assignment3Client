//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H

#include "Protocol.h"
#include <string>
#include <vector>

using namespace std;

class client {
private:
    bool shouldTerminate;
    Protocol protocol;
    string userName;
    string passcode;
    vector<string> inventory;
    unordered_map<int, string> subId;
    int subCount;

public:
    client(string username, string passcode);

    void setProtocol(const Protocol &protocol);

    bool isShouldTerminate() const;

    void setShouldTerminate(bool shouldTerminate);

    const Protocol &getProtocol() const;

    const string &getUserName() const;

    void setUserName(const string &userName);

    const string &getPasscode() const;

    void setPasscode(const string &passcode);

    const vector<string> &getInventory() const;

    void setInventory(const vector<string> &inventory);

    const unordered_map<int, string>getSubId() const;

    void setSubId(const unordered_map<int, string>subId);

    int getSubCount() const;

    void setSubCount(int subCount);
};


#endif //BOOST_ECHO_CLIENT_CLIENT_H