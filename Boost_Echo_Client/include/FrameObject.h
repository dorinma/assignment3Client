//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_FRAMEOBJECT_H
#define BOOST_ECHO_CLIENT_FRAMEOBJECT_H
#include <unordered_map>
#include <string>

class FrameObject {
public:
    FrameObject();

    FrameObject(std::string command);

    FrameObject(std::string command, std::unordered_map<std::string, std::string> headers, std::string body);

    const std::string &getCommand() const;
    void setCommand(const std::string &command);
    const std::unordered_map<std::string, std::string> &getHeaders() const;
    void setHeaders(const std::unordered_map<std::string, std::string> &headers);
    const std::string &getBody() const;
    void setBody(const std::string &body);

    std::string toString();

private:
    std::string command;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

};
#endif //BOOST_ECHO_CLIENT_FRAMEOBJECT_H
