//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H
#include <string>
#include <vector>
#include "FrameObject.h"
#include "connectionHandler.h"

using namespace std;

class Protocol {
public:
    Protocol();
    void process(vector<std::string> input);
};

#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
