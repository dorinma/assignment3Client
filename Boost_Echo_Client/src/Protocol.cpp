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

FrameObject* Protocol::process(FrameObject msg) {

    string command = msg.getCommand();
    string body = msg.getBody();
    unordered_map<string, string> headers = msg.getHeaders();
    FrameObject* frame = new FrameObject();

    if(command == "MESSAGE")
    {
        string newCommand = "SEND";

        string currUser = body.substr(0, body.find(" "));

        if (body.find("added"))
        {
            vector <string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string bookName = "";
            bookName = exp[5];
            for(int i=6; i<exp.size(); i++)
            {
                bookName = bookName + " " + exp[i];
            }
            string subId = headers.at("subscription");
            string genre = headers.at("destination");
            string lastOwner = "";
            Book book(bookName, genre, lastOwner);

            if (client.getSubId().count(subId) && client.getUserName().compare(currUser))
            {
                if(client.getSubId().at(subId).compare(genre))
                    client.addBook(book);
                else
                    cout<<"genre and subscription id dont match"<<endl;
            }
            else
            {
                client.addGenre(subId, genre);
                client.addBook(book);
            }
            return frame;
        }//end adding book

        else if(body.find("borrow"))
        {
            vector <string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string bookName = exp[4];
            for(int i = 5; i < exp.size(); i++)
            {
                bookName = bookName + " " + exp[i];
            }
            string genre = headers.at("destination");
            for(Book currBook : client.getInventory())
            {
                if(currBook.getExists() && currBook.getNameBook().compare(bookName)) {
                    string newBody = client.getUserName() + " has " + bookName;
                    unordered_map<string, string> newHeaders;
                    newHeaders["destination"] = genre;
                    frame = new FrameObject(newCommand, newHeaders, newBody);
                    currBook.setExists(false);
                    //client.removeBook(bookName);
                    return frame;
                }
            }
        }//end borrowing book

        else if(body.find("has") & !msg.getBody().find("added"))
        {
            vector <string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string lastOwner = exp[0];
            string bookName = exp[2];
            for(int i = 3; i < exp.size() - 2; i++)
            {
                bookName = bookName + " " + exp[i];
            }
            string genre = headers.at("destination");
            if(client.getWantedBook().compare(bookName)) {
                string newBody = "Taking " + bookName + " from " + lastOwner;
                unordered_map<string, string> newHeaders;
                newHeaders["destination"] = genre;
                frame = new FrameObject(newCommand, newHeaders, newBody);
                Book *book = new Book(bookName, genre, lastOwner);
                client.addBook(*book);
                return frame;
            }
        }//end taking book

        else if(body.find("Taking")) { return frame; }

        else if(body.find("Returning")) {
            vector<string> exp;
            boost::split(exp, body, boost::is_any_of(" "));
            string lastOwner = exp[exp.size() - 1];
            string bookName = exp[1];
            string genre = headers.at("destination");
            for (int i = 2; i < exp.size() - 2; i++) {
                bookName = bookName + " " + exp[i];
            }
            //return from
            if(client.findBook(bookName)) {
                //Book* b = client.getBook(bookName);
                //b->setExists(true);
                client.removeBook(bookName);
            }
            //return to
            else if (client.getUserName().compare(lastOwner)) {
                Book* b = client.getBook(bookName);
                b->setExists(true);
                //Book *book = new Book(bookName, genre, lastOwner, true);
                client.addBook(*b);
            }
            return frame;
        }

        else if(body.find("status"))
        {
            string genre = headers.at("destination");
            unordered_map<string, string> newHeaders;
            newHeaders["destination"] = genre;
            string newBody = client.getUserName() + ":";
            for(int i = 0; i < client.getInventory().size(); i++) {
                newBody += client.getInventory()[i].getNameBook();
                if (client.getInventory().size() != 1 & i < client.getInventory().size() - 1)
                    newBody += ",";
            }

            frame = new FrameObject(newCommand, newHeaders, newBody);
            return frame;
        }
        else if(body.find(":"))
        {

        }
        return nullptr;
    }
    else if(command == "ERROR")
        return nullptr;
    else if(command == "CONNECTED") //for debug onlyyyyy
    {
        cout<<""<<endl;
    }
    else if(command == "RECEIPT") //for debug onlyyyyy
    {
        cout<<""<<endl;
    }


}





