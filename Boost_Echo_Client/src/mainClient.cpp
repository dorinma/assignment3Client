#include <stdlib.h>
#include <connectionHandler.h>
#include <mutex>
#include <thread>
#include <StompConnectionHandler.h>
#include <Protocol.h>

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
    std::mutex _mutexKeyboard;
    std::mutex _mutexSocket;
    MessageEncoderDecoder stompEncoderDecoder;
    Protocol protocol;


    StompConnectionHandler connectionHandler(stompEncoderDecoder,protocol,
                                             _mutexKeyboard,_mutexSocket);
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