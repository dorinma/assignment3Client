//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "client.h"
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
client::client(string username, string passcode) : userName(username), passcode(passcode){
    shouldTerminate = false;
}

short client::getPort() const {
    return port;
}

void client::setPort(short port) {
    client::port = port;
}

bool client::isShouldTerminate() const {
    return shouldTerminate;
}

void client::setShouldTerminate(bool shouldTerminate) {
    client::shouldTerminate = shouldTerminate;
}

const Protocol &client::getProtocol() const {
    return protocol;
}

const string &client::getUserName() const {
    return userName;
}

void client::setUserName(const string &userName) {
    client::userName = userName;
}

const string &client::getPasscode() const {
    return passcode;
}

void client::setPasscode(const string &passcode) {
    client::passcode = passcode;
}

const vector<string> &client::getInventory() const {
    return inventory;
}

void client::setInventory(const vector<string> &inventory) {
    client::inventory = inventory;
}

int client::getSubCount() const {
    return subCount;
}

void client::setSubCount(int subCount) {
    client::subCount = subCount;
}

const unordered_map<int, string> client::getSubId() const {
    return subId;
}

void client::setSubId(const unordered_map<int, string>subId) {
    client::subId = subId;
}

