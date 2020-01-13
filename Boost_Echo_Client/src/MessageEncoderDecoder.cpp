//
// Created by dorin on 13/01/2020.
//

#include "MessageEncoderDecoder.h"

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
        headers["accept-version"] = "1.2";
        headers["host"] = hostPort[0];
        headers["login"] = expressions[2];
        headers["passcode"] = expressions[3];
    } else if (expressions[0] == "join") {
        command = "SUBSCRIBE";
        headers["destination"] = expressions[1];
        //TODO insert to map id & receipt
        headers["id"] = "";
        headers["receipt"] = "";
    } else if (expressions[0] == "add") {
        command = "SEND";
        headers["destination"] = expressions[1];
        body = /*user name*/ " has added the book " + input[2];
    } else if (expressions[0] == "borrow") {
        command = "SEND";
        headers["destination"] = expressions[1];
        body = /*user name*/ " wish to borrow " + input[2];
    } else if (expressions[0] == "return") {
        command = "SEND";
        headers["destination"] = input[1];
        body = "Returning " + expressions[1] + " to " /*user name*/;
    } else if (expressions[0] == "status") {
        command = "SEND";
        headers["destination"] = input[1];
        body = "book status";
    } else if (expressions[0] == "logout") {
        command = "DISCONNECT";
        //TODO insert receipt id
        headers["receipt"] = input[1];
    }

    FrameObject *frameObject = new FrameObject(command, headers, body);
    return *frameObject;
}

FrameObject MessageEncoderDecoder::serverToFrame(string input) {
    //TODO implement
}