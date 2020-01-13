//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "Protocol.h"
#include "FrameObject.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace std;

Protocol::Protocol(Client &c) : client(c){}

bool Protocol::process(FrameObject msg) {

    string command = msg.getCommand();
    string body = msg.getBody();
    unordered_map<string, string> headers = msg.getHeaders();

    if(msg.getCommand() == "MESSAGE")
    {
        if (msg.getBody().find("added"))
        {
            vector <string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string bookName = "";
            bookName = exp[5];
            for(int i=6; i<exp.size(); i++)
            {
                bookName = bookName + " " +exp[i];
            }
            string subId = msg.getHeaders().at("subscription");
            string genre = client.getSubId().at(subId);
            string lastOwner = "";
            Book* book = new Book(bookName, genre, lastOwner);
            client.
        }
        else if(msg.getBody().find("borrow"))
        {

        }
        else if(msg.getBody().find("has") & !msg.getBody().find("added"))
        {

        }
        else if(msg.getBody().find("Taking"))
        {

        }
        else if(msg.getBody().find("Returning"))
        {

        }
        else if(msg.getBody().find("status"))
        {

        }
        else if(msg.getBody().find(":"))
        {

        }
        return true;
    }
    else if(msg.getCommand() == "ERROR")
        return false;
    else if(msg.getCommand() == "CONNECTED") //for debug onlyyyyy
    {
        cout<<""<<endl;
    }
    else if(msg.getCommand() == "RECEIPT") //for debug onlyyyyy
    {
        cout<<""<<endl;
    }


}





