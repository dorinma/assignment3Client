//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H
#include <string>
#include <vector>
#include "FrameObject.h"
#include "Client.h"

using namespace std;

class Protocol {
private:
    Client client;
public:
    Protocol();
    FrameObject process(FrameObject msg);
    void setClient(Client c);
    Client getClient();
};


#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
