//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "FrameObject.h"

FrameObject::FrameObject(std::string command, std::unordered_map<std::string, std::string> headers, std::string body) : command(), headers(), body() {}

std::string FrameObject::toString() {
    std::string output = "";
    output += command + "\n";
    for (std::pair<std::string, std::string> element : headers) {
        output += element.first + ":" + element.second + "\n";
    }
    output += "\n" + body;
    output += "\n" + '\u0000';

    return output;
}

// Getters & setters
const std::string &FrameObject::getCommand() const {
    return command;
}

void FrameObject::setCommand(const std::string &command) { this->command = command; }

const std::unordered_map<std::string, std::string> &FrameObject::getHeaders() const {
    return headers;
}

void FrameObject::setHeaders(const std::unordered_map<std::string, std::string> &headers) {
    this->headers = headers;
}

const std::string &FrameObject::getBody() const {
    return body;
}

void FrameObject::setBody(const std::string &body) {
    this->body = body;
}