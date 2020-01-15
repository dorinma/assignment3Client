#include <stdlib.h>
#include <mutex>
#include <thread>
#include <iostream>
//#include <include/MessageEncoderDecoder.h>
//#include <include/StompConnectionHandler.h>
//#include <include/Protocol.h>
#include "Protocol.h"
#include "MessageEncoderDecoder.h"
#include "StompConnectionHandler.h"

using namespace std;

/**
* This code assumes that the server replies the exact text the Client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
    /*if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);*/
    mutex _mutexKeyboard;
    mutex _mutexServer;
    MessageEncoderDecoder encdec;
    Protocol protocol;


    StompConnectionHandler connectionHandler(encdec, protocol, _mutexKeyboard ,_mutexServer);
    /*if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }*/

    //From here we will see the rest of the ehco client implementation:
    std::thread th1(&StompConnectionHandler::keyboardRun, &connectionHandler);
    std::thread th2(&StompConnectionHandler::serverRun, &connectionHandler);

    th1.join();
    th2.join();

    return 0;
}