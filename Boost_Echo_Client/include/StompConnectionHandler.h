//
// Created by dorin on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPCONNECTIONHANDLER_H
#define BOOST_ECHO_CLIENT_STOMPCONNECTIONHANDLER_H
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "MessageEncoderDecoder.h"

using boost::asio::ip::tcp;

class StompConnectionHandler {

private:
    const std::string host_;
    const short port_;
    boost::asio::io_service io_service_;   // Provides core I/O functionality
    tcp::socket socket_;
    MessageEncoderDecoder encdec;


};

#endif //BOOST_ECHO_CLIENT_STOMPCONNECTIONHANDLER_H
