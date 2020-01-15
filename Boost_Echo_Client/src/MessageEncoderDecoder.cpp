//
// Created by dorin on 13/01/2020.
//

#include <include/MessageEncoderDecoder.h>
#include <iostream>

MessageEncoderDecoder::MessageEncoderDecoder() {
    username = "";
    subId = 0;
    receiptId = 0;
    Client client();
}

void MessageEncoderDecoder::setClient(Client client) {
    this->client = client;
}

Client MessageEncoderDecoder::getClient() { return client; }

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
        username = expressions[2];

    } else if (expressions[0] == "join") {
        command = "SUBSCRIBE";
        headers["destination"] = expressions[1];
        subId++;
        headers["id"] = to_string(subId);
        receiptId++;
        headers["receipt"] = to_string(receiptId);

    } else if (expressions[0] == "add") { //TODO wont get names with more than one word
        command = "SEND";
        headers["destination"] = expressions[1];
        body = username + " has added the book " + expressions[2];

    } else if (expressions[0] == "borrow") {
        command = "SEND";
        headers["destination"] = expressions[1];
        body = username + " wish to borrow " + expressions[2];

    } else if (expressions[0] == "return") {
        command = "SEND";
        headers["destination"] = input[1];
        body = "Returning " + expressions[1] + " to " + client.getBook(expressions[1])->getLastOwner();

    } else if (expressions[0] == "status") {
        command = "SEND";
        headers["destination"] = input[1];
        body = "book status";
    } else if (expressions[0] == "logout") {
        command = "DISCONNECT";
        receiptId++;
        headers["receipt"] = to_string(receiptId);
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
        if (lines[i].size() > 0 && lines[i].find(":") != string::npos) { //header line
            vector<string> exp;
            boost::split(exp, lines[i], boost::is_any_of(":"));
            pair<string, string> head(exp[0], exp[1]);
            headers.insert(head);
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