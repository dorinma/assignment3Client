//
// Created by dorin on 13/01/2020.
//

#include "MessageEncoderDecoder.h"

MessageEncoderDecoder::MessageEncoderDecoder() {
    username = "";
    subId = 0;
    receiptId = 0;
}

string MessageEncoderDecoder::frameToString(FrameObject frameObject) {
    return frameObject.toString();
}

FrameObject MessageEncoderDecoder::kbdToFrame(string input) {
    //TODO finish method
    vector <string> expressions;
    boost::split(expressions, input, boost::is_any_of(" "));
    std::string command;
    std::unordered_map <std::string, std::string> headers;
    std::string body = "";

    if (expressions[0] == "login") {
        command = "CONNECT";
        vector <std::string> hostPort;
        boost::split(hostPort, expressions[1], boost::is_any_of(":"));
        headers["accept-version"] = "1.2";
        headers["host"] = hostPort[0];
        headers["login"] = expressions[2];
        headers["passcode"] = expressions[3];
        username = expressions[2];
    } else if (expressions[0] == "join") {
        command = "SUBSCRIBE";
        headers["destination"] = expressions[1];
        subId++;
        headers["id"] = subId;
        receiptId++;
        headers["receipt"] = receiptId;
    } else if (expressions[0] == "add") {
        command = "SEND";
        headers["destination"] = expressions[1];
        body = username + " has added the book " + input[2];
    } else if (expressions[0] == "borrow") {
        command = "SEND";
        headers["destination"] = expressions[1];
        body = username + " wish to borrow " + input[2];
    } else if (expressions[0] == "return") {
        command = "SEND";
        headers["destination"] = input[1];
        //string lastOwner = class Book
        body = "Returning " + expressions[1] + " to " /*last owner*/;
    } else if (expressions[0] == "status") {
        command = "SEND";
        headers["destination"] = input[1];
        body = "book status";
    } else if (expressions[0] == "logout") {
        command = "DISCONNECT";
        receiptId++;
        headers["receipt"] = receiptId;
    }

    FrameObject *frameObject = new FrameObject(command, headers, body);
    return *frameObject;
}

FrameObject MessageEncoderDecoder::serverToFrame(string input) {

    string command;
    unordered_map <std::string, std::string> headers;
    string body = "";
    vector <string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));
    command = lines[0];
    for(int i = 1; i < lines.size(); i++) {
        if(lines[i].find(":")) { //header line
            pair<string, string> head;
            boost::split(head, input, boost::is_any_of(":"));
            headers.insert(head);
        }
        else if(lines[i] != "" && !(lines[i].find('\0'))) {
            body = lines[i];
        }
    }

    FrameObject frameObject(command, headers, body);
    return frameObject;
}