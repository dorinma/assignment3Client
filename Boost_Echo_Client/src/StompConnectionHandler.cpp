//
// Created by dorin on 13/01/2020.
//

#include <include/StompConnectionHandler.h>

StompConnectionHandler::StompConnectionHandler(MessageEncoderDecoder encdec, Protocol protocol, mutex &_mutexKeyboard, mutex &_mutexServer) :
                        encdec(encdec), protocol(protocol), host_("0.0.0.0"), port_(7777), io_service_(), socket_(io_service_),
                                _mutexKeyboard(_mutexKeyboard), _mutexServer(_mutexServer){
Client client();
}

StompConnectionHandler::~StompConnectionHandler() { close(); }

bool StompConnectionHandler::keyboardRun() {
    while(!shouldTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        cout<<"write somsing:"<<endl;
        std::cin.getline(buf, bufsize);
        std::string line(buf);

        vector<string> expressions;
        boost::split(expressions, line, boost::is_any_of(" "));
        if (!isConnected && expressions[0] == "login") {
            vector<string> hostPort;
            boost::split(hostPort, expressions[1], boost::is_any_of(":"));
            host_ = hostPort[0];
            port_ = boost::lexical_cast<short>(hostPort[1]);
            encdec.setClient(Client(expressions[2], expressions[3]));
        }
        if (!connect()) {
            std::cerr << "Cannot connect to " << host_ << ":" << port_ << std::endl;
            shouldTerminate = true;
        }
        if (isConnected) {
            string stdOut = encdec.kbdToFrame(line).toString();
            int len = stdOut.length(); //TODO - might need to switch to line.length()
            if (!sendLine(stdOut)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                shouldTerminate = true;
                break;
            }
            std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;
        }
    }
}

bool StompConnectionHandler::serverRun() {
    while(!shouldTerminate) {
        if (isConnected) {
            string answer;
            std::cout << "Waiting for message...\n" << std::endl;
            if (!getLine(answer)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                shouldTerminate = true;
                break;
            }
            std::cout << "Got new message\n" << std::endl;

            int len = answer.length();
            answer.resize(len - 1);
            std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;

            FrameObject frameObject = encdec.serverToFrame(answer);
            FrameObject response = protocol.process(frameObject);

            if (response.getCommand() == "EMPTY") { /*do nothing, no new frame was crated*/ }

            else if (response.getCommand() == "ERROR") {
                std::cout << "Exiting...\n" << std::endl;
                shouldTerminate = true;
            }

            else {
                string result = encdec.frameToString(response);
                if(!sendLine(result)) {
                    std::cout << "Disconnected. Exiting...\n" << std::endl;
                    shouldTerminate = true;
                    break;
                }
            }
        }
    }
}

bool StompConnectionHandler::connect() {
    std::cout << "Starting connect to "
              << host_ << ":" << port_ << std::endl;
    try {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
        boost::system::error_code error;
        socket_.connect(endpoint, error);
        if (error)
            throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        shouldTerminate = true;
        isConnected = false;
        return isConnected;
    }
    protocol.setClient(client);
    encdec.setClient(client);
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
            throw boost::system::system_error(error);
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
        while (!error && bytesToWrite > tmp ) {
            tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
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