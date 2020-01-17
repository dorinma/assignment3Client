//
// Created by dorin on 13/01/2020.
//

#include "MessageEncoderDecoder.h"
//#include <include/MessageEncoderDecoder.h>
#include <iostream>

MessageEncoderDecoder::MessageEncoderDecoder() {
    username = "";
    subId = 0;
    receiptId = 0;
    Client client();
}

void MessageEncoderDecoder::setClient(Client *client) {
    this->client = client;
}

string MessageEncoderDecoder::frameToString(FrameObject frameObject) {
    return frameObject.toString();
}

FrameObject MessageEncoderDecoder::kbdToFrame(string input) {
    vector <string> expressions;
    boost::split(expressions, input, boost::is_any_of(" "));
    std::string command;
    std::unordered_map <std::string, std::string> headers;
    std::string body = "";

    if (expressions[0] == "login") {
        command = "CONNECT";
        vector <std::string> hostPort;
        boost::split(hostPort, expressions[1], boost::is_any_of(":"));
        pair<string, string> header1("accept-version", "1.2");
        headers.insert(header1);
        pair<string, string> header2("host", hostPort[0]);
        headers.insert(header2);
        pair<string, string> header3("login", expressions[2]);
        headers.insert(header3);
        pair<string, string> header4("passcode", expressions[3]);
        headers.insert(header4);

        username = expressions[2];

    }
    else if (expressions[0] == "join") {
        command = "SUBSCRIBE";
        headers["destination"] = expressions[1];
        subId++;
        headers["id"] = to_string(subId);
        receiptId++;
        headers["receipt"] = to_string(receiptId);
        receipts[receiptId] = "SUBSCRIBE";
    }
    else if (expressions[0] == "add") {
        command = "SEND";
        headers["destination"] = expressions[1];
        string bookName = expressions[2];
        for (int j = 3; j < expressions.size(); ++j) {
            bookName += " " + expressions[j];
        }
        body = username + " has added the book " + bookName;

    }
    else if (expressions[0] == "borrow") {
        command = "SEND";
        headers["destination"] = expressions[1];
        string bookName = expressions[2];
        for (int j = 3; j < expressions.size(); ++j) {
            bookName += " " + expressions[j];
        }
        body = username + " wish to borrow " + bookName;

    }
    else if (expressions[0] == "return") {

        command = "SEND";
        headers["destination"] = expressions[1];
        string bookName = expressions[2];
        for (int j = 3; j < expressions.size(); ++j) {
            bookName += " " + expressions[j];
        }
        body = "Returning " + bookName + " to " + client->getLastOwner(bookName);
    }
    else if (expressions[0] == "status") {
        command = "SEND";
        headers["destination"] = expressions[1];
        body = "book status";
    }
    else if (expressions[0] == "logout") {
        command = "DISCONNECT";
        receiptId++;
        headers["receipt"] = to_string(receiptId);
        receipts[receiptId] = "DISCONNECT";
    }
    else if (expressions[0] == "exit") {
        command = "UNSUBSCRIBE";
        headers["destination"] = expressions[1];
        //get the wanted subscription id
        string thisSubId = "";
        for (pair<string, string> element : client->getSubId())
        {
            if(element.second == expressions[1])
                thisSubId = element.first;
        }
        headers["id"] = thisSubId;
        client->getSubId().erase(expressions[1]); //delete this genre from user's subscriptions
        //TODO should happen here also? happens in server side already. make sure!
        receiptId++;
        headers["receipt"] = to_string(receiptId);
        receipts[receiptId] = "UNSUBSCRIBE";
    }

    FrameObject frameObject(command, headers, body);
    return frameObject;
}

FrameObject MessageEncoderDecoder::serverToFrame(string input) {
    string command;
    unordered_map <std::string, std::string> headers;
    string body = "";

    vector <string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));

    command = lines[0];

    for(int i = 1; i < lines.size(); i++) {
        if (lines[i].size() > 0 && lines[i].find(":") != string::npos) {
            if(lines[i-1].length() > 0) { //this is an header line
                vector<string> exp;
                boost::split(exp, lines[i], boost::is_any_of(":"));
                pair<string, string> head(exp[0], exp[1]);
                headers.insert(head);
            }
            else //this is the body
                body = lines[i];
        }
        else if(lines[i].size() > 0 && !(lines[i].find('\0') != string::npos)) {
            body = lines[i];
        }
        else if(lines[i].size() > 0 && lines[i].find('\0') != string::npos) {
            body += "\n" + '\0';
        }
    }
    FrameObject frameObject(command, headers, body);
    return frameObject;
}

unordered_map<int, string> MessageEncoderDecoder::getReceipts() { return receipts; }