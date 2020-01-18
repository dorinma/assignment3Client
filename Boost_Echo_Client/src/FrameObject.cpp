//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <include/FrameObject.h>
//#include "FrameObject.h"

FrameObject::FrameObject(std::string command, std::unordered_map<std::string, std::string> headers, std::string body) : command(command), headers(headers), body(body) {}

FrameObject::FrameObject() { }

FrameObject::FrameObject(std::string command) : command(command) {}

std::string FrameObject::toString() {
    std::string output = "";
    output += command + "\n";
    for (std::pair<std::string, std::string> element : headers) {
        output += element.first + ":" + element.second + "\n";
    }
    output += "\n" + body;
    output += "\n" + '\0';

    return output;
}

const std::string &FrameObject::getCommand() const {
    return command;
}


std::unordered_map<std::string, std::string> FrameObject::getHeaders() { return headers;}


const std::string &FrameObject::getBody() const {
    return body;
}


