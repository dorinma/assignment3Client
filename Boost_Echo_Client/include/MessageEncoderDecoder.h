//
// Created by dorin on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGEENCODERDECODER_H
#define BOOST_ECHO_CLIENT_MESSAGEENCODERDECODER_H
#include "Book.h"
#include "FrameObject.h"
#include "Client.h"
#include <vector>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

class MessageEncoderDecoder {
private:
    int subId;
    int receiptId;
    string username;
    Client *client;
    std::unordered_map<int, string> receipts;
    std::unordered_map<int, string> receiptIdSubscriptions;

public:
    MessageEncoderDecoder();
    FrameObject serverToFrame(string input);
    FrameObject kbdToFrame(string input);
    string frameToString(FrameObject frameObject);
    void setClient(Client *client);
    Client getClient();
    unordered_map<int, string> getReceipts();
    unordered_map<int, string> getReceiptIdSubscriptions();

};

#endif //BOOST_ECHO_CLIENT_MESSAGEENCODERDECODER_H
