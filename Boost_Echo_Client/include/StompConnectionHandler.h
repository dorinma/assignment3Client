//
// Created by dorin on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPCONNECTIONHANDLER_H
#define BOOST_ECHO_CLIENT_STOMPCONNECTIONHANDLER_H
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "MessageEncoderDecoder.h"
#include "Client.h"
#include "Protocol.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <mutex>

using boost::asio::ip::tcp;

class StompConnectionHandler {

private:
    std::string host_;
    short port_;
    boost::asio::io_service io_service_;   // Provides core I/O functionality
    tcp::socket socket_;
    MessageEncoderDecoder encdec;
    Protocol protocol;
    Client client;
    bool isConnected;
    bool shouldTerminate;
    mutex &_mutexKeyboard;
    mutex &_mutexServer;

public:
    StompConnectionHandler(MessageEncoderDecoder encdec, Protocol protocol, mutex &_mutexKeyboard, mutex &_mutexServer);

    virtual ~StompConnectionHandler();

    bool keyboardRun();

    bool serverRun();

    // Connect to the remote machine
    bool connect();

    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead);

    // Send a fixed number of bytes from the Client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite);

    // Read an ascii line from the server
    // Returns false in case connection closed before a newline can be read.
    bool getLine(std::string& line);

    // Send an ascii line from the server
    // Returns false in case connection closed before all the data is sent.
    bool sendLine(std::string& line);

    // Get Ascii data from the server until the delimiter character
    // Returns false in case connection closed before null can be read.
    bool getFrameAscii(std::string& frame, char delimiter);

    // Send a message to the remote host.
    // Returns false in case connection is closed before all the data is sent.
    bool sendFrameAscii(const std::string& frame, char delimiter);

    // Close down the connection properly.
    void close();

};

#endif //BOOST_ECHO_CLIENT_STOMPCONNECTIONHANDLER_H
