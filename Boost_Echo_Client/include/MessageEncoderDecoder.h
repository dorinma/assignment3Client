//
// Created by dorin on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGEENCODERDECODER_H
#define BOOST_ECHO_CLIENT_MESSAGEENCODERDECODER_H
#include "FrameObject.h"
#include <vector>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

class MessageEncoderDecoder {
public:
    FrameObject serverToFrame(string input);
    FrameObject kbdToFrame(string input);
    string frameToString(FrameObject frameObject);

};

#endif //BOOST_ECHO_CLIENT_MESSAGEENCODERDECODER_H
