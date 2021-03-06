//
// Created by zeirah@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
//#include <include/Protocol.h>
#include "../include/Protocol.h"
using namespace std;

Protocol::Protocol() : client(){
    //Client client();
}


void Protocol::setClient(Client *c) {
    client = c;
}

FrameObject Protocol::process(FrameObject msg) {

    string command = msg.getCommand();
    string body = msg.getBody();
    unordered_map<string, string> headers = msg.getHeaders();
    FrameObject frame("EMPTY");

    if(command == "MESSAGE")
    {
        string newCommand = "SEND";

        if (body.find("added") != string::npos)
        {
            vector <string> exp;
            boost::split(exp, body, boost::is_any_of(" "));

            string bookName = exp[5];
            for(unsigned int i = 6; i < exp.size(); i++)
            {
                bookName = bookName + " " + exp[i];
            }
            string subId = headers.at("subscription");
            string genre = headers.at("destination");
            string lastOwner = "";
            if (client->getSubId().count(subId) == 1 && client->getUserName() == exp[0])
            {
                if(client->getSubId().at(subId) == genre)
                    client->addBook(bookName, genre, lastOwner);
                else
                    std::cout<<"genre and subscription id dont match"<<endl;
            }
            else
            {
                if(client->getUserName() == exp[0])
                {
                    client->addGenre(subId, genre);
                    client->addBook(bookName, genre, lastOwner);
                }
            }
            return frame;
        }//end adding book

        else if(body.find("borrow") != string::npos)
        {
            vector <string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string bookName = exp[4];
            for(unsigned int i = 5; i < exp.size(); i++)
            {
                bookName = bookName + " " + exp[i];
            }

            string genre = headers.at("destination");

            if(exp[0] == client->getUserName())
                this->client->setWantedBook(bookName);

            if(exp[0] != client->getUserName())
            {
                for(Book currBook : client->getInventory())
                {
                    if(currBook.getExists() && currBook.getNameBook() == bookName) {
                        string newBody = client->getUserName() + " has " + bookName;
                        unordered_map<string, string> newHeaders;
                        newHeaders["destination"] = genre;
                        FrameObject newFrame(newCommand, newHeaders, newBody);
                        this->client->setExistMode(bookName, genre, currBook.getLastOwner(), false);
                        return newFrame;
                    }
                }
            }

        }//end borrowing book

        else if((body.find("has") != string::npos) & (msg.getBody().find("added") == string::npos))
        {
            vector <string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string lastOwner = exp[0];
            string bookName = exp[2];
            for(unsigned int i = 3; i < exp.size() - 2; i++)
            {
                bookName = bookName + " " + exp[i];
            }
            string genre = headers.at("destination");
            if(client->getWantedBook() == bookName) {
                string newBody = "Taking " + bookName + " from " + lastOwner;
                unordered_map<string, string> newHeaders;
                newHeaders["destination"] = genre;
                FrameObject newFrame(newCommand, newHeaders, newBody);
                client->addBook(bookName, genre, lastOwner);
                client->setWantedBook("");
                return newFrame;
            }
        }//end taking book

        else if(body.find("Taking") != string::npos) {

            return frame;
        }

        else if(body.find("Returning") != string::npos) {
            vector<string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string lastOwner = exp[exp.size() - 1];
            string bookName = exp[1];
            string genre = headers.at("destination");
            for (unsigned int i = 2; i < exp.size() - 2; i++) {
                bookName = bookName + " " + exp[i];
            }
            //return from
            if(client->findBook(bookName)) {
                client->removeBook(bookName);
            }
            //return to
            else if (client->getUserName() == lastOwner) {
                string owner = client->getLastOwner(bookName);
                //client->removeBook(bookName);
                client->setExistMode(bookName, genre, owner, true);
            }
            return frame;
        }

        else if(body.find("status") != string::npos)
        {
            string genre = headers.at("destination");
            unordered_map<string, string> newHeaders;
            newHeaders["destination"] = genre;
            string newBody = client->getUserName() + ": ";
            for(unsigned int i = 0; i < client->getInventory().size(); i++)
            {
                if((client->getInventory()[i].getGenre() == genre) & (client->getInventory()[i].getExists()))
                {
//                    if(client->getInventory()[i].getExists())
//                    {
                        newBody += client->getInventory()[i].getNameBook() + ", ";
//                    }
//                    else{
//                        newBody += client->getInventory()[i].getNameBook() + "(borrowed), ";
//                    }
                }
            }
            FrameObject newFrame("SEND", newHeaders, newBody);
            //cout<<  " protocol status print " << newBody << endl;
            return newFrame;
        }
        else if(body.find(":") != string::npos){
            return msg;
        }
        return frame;
    }
    else if(command == "ERROR") {
        FrameObject newFrame("ERROR");
        return newFrame;
    }
    else if(command == "CONNECTED") {
        cout<<"Login successful"<<endl;
        return msg;
    }
    else if(command == "RECEIPT"){
        return msg;
    }
    return frame;
}





