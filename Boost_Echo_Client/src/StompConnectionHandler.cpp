//
// Created by dorin on 13/01/2020.
//

//#include <include/StompConnectionHandler.h>
#include "StompConnectionHandler.h"
StompConnectionHandler::StompConnectionHandler(MessageEncoderDecoder encdec, Protocol protocol, mutex &_mutexKeyboard, mutex &_mutexServer) :
                        encdec(encdec), protocol(protocol), host_("0.0.0.0"), port_(7777), io_service_(), socket_(io_service_),
                                _mutexKeyboard(_mutexKeyboard), _mutexServer(_mutexServer){
Client client();
}

StompConnectionHandler::~StompConnectionHandler() {
    //delete(this->encdec.getClient());
    close(); }

bool StompConnectionHandler::keyboardRun() {
    while(!shouldTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        //cout<<"write something:"<<endl;
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        vector<string> expressions;
        boost::split(expressions, line, boost::is_any_of(" "));
        if (!isConnected && expressions[0] == "login") {
            vector<string> hostPort;
            boost::split(hostPort, expressions[1], boost::is_any_of(":"));
            host_ = hostPort[0];
            port_ = boost::lexical_cast<short>(hostPort[1]);
            client.setUserName(expressions[2]);
            client.setPasscode(expressions[3]);
            if (!connect()) {
                //std::cerr << "Cannot connect to " << host_ << ":" << port_ << std::endl;
                //std::cerr << "Cannot connect to server" << std::endl;
                shouldTerminate = true;
            }
        }

        if (isConnected) {
            string stdOut = encdec.kbdToFrame(line).toString();
            //cout<<"------message out------"<<endl;
            //cout<<stdOut<<endl;
            int len = stdOut.length();
            if (!sendLine(stdOut)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                shouldTerminate = true;
                break;
            }
            //std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;
        }
        //cout<<"isConnected" << isConnected << endl;
    }
}

bool StompConnectionHandler::serverRun() {
    while(!shouldTerminate) {
        if (isConnected) {
            string answer;
            //std::cout << "Waiting for message from the server...\n" << std::endl;
            if (!this->getLine(answer)) {
                std::cout << "1server Disconnected. Exiting...\n" << std::endl;
                shouldTerminate = true;
                break;
            }
            //std::cout << "Got new message from the server\n" << std::endl;

            int len = answer.length();
            answer.resize(len - 1);
           // std::cout << "Reply:" << client.getUserName() << "\n" << answer << "\n" << len << " bytes " << std::endl << std::endl;

            FrameObject frameObject = encdec.serverToFrame(answer);
            //protocol.setClient(client);
            FrameObject response = protocol.process(frameObject);

            if (response.getCommand() == "EMPTY") { /*do nothing, no new frame was crated*/ }

            else if (response.getCommand() == "ERROR") {
                std::cout << "Exiting...\n" << std::endl;
                shouldTerminate = true;
            }

            else if(response.getCommand() == "RECEIPT") {
                string tempGenre = response.getHeaders()["destination"];
                for (pair<int, string> element : encdec.getReceipts())
                {
                    if(to_string(element.first) == response.getHeaders()["receipt-id"]) {
                        if (element.second == "SUBSCRIBE")
                            std::cout << "Joined genre " + tempGenre << std::endl;
                        else if (element.second == "UNSUBSCRIBE")
                            std::cout << "Exited genre " + tempGenre << std::endl;
                    }
                }
            }

            else {
                string result = encdec.frameToString(response);
                //cout <<"after toSTring print:::: " + result << endl;
                if(!sendLine(result)) {
                    std::cout << "2server Disconnected. Exiting...\n" << std::endl;
                    shouldTerminate = true;
                    break;
                }
            }
        }
    }
}

bool StompConnectionHandler::connect() {
    //std::cout << "Starting connect to "
    //          << host_ << ":" << port_ << std::endl;
    try {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
        boost::system::error_code error;
        socket_.connect(endpoint, error);
        if (error)
        {
            //cerr<<"---connect error"<< endl;
            std::cerr << "Could not connect to server" << std::endl;
            throw boost::system::system_error(error);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        shouldTerminate = true;
        isConnected = false;
        return isConnected;
    }
    protocol.setClient(&client);
    encdec.setClient(&client);
    isConnected = true;
    return isConnected;
}

bool StompConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
            tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);

        }
        if(error)
        {
            cerr<<"---get bytes error"<< endl;
            throw boost::system::system_error(error);
        }
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool StompConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
    boost::system::error_code error;
    try {
        std::lock_guard<std::mutex> lockGuard(_mutexServer); //syncing writing and sending on the same time
        while (!error && bytesToWrite > tmp ) {
            tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
        if(error)
        {
            cerr<<"---send bytes error"<< endl;
            throw boost::system::system_error(error);
        }
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool StompConnectionHandler::getLine(std::string& line) {
    return getFrameAscii(line, '\0');
}

bool StompConnectionHandler::sendLine(std::string& line) {
    return sendFrameAscii(line, '\0');
}

bool StompConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    //encdec.getFrameAscii(frame, delimiter);
    char ch;
    // Stop when we encounter the null character.
    // Notice that the null character is not appended to the frame string.
    try {
        do{
            if(!getBytes(&ch, 1))
            {
                return false;
            }
            if(ch!='\0')
                frame.append(1, ch);
        }while (delimiter != ch);
    } catch (std::exception& e) {
        std::cerr << "recv failed2 (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool StompConnectionHandler::sendFrameAscii(const std::string& frame, char delimiter) {
    bool result=sendBytes(frame.c_str(),frame.length());
    if(!result) return false;
    return sendBytes(&delimiter,1);
}

// Close down the connection properly.
void StompConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}