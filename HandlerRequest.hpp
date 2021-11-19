//
//  HandlerRequest.hpp
//  echobot
//
//  Created by Павло Коваль on 19.11.2021.
//

#ifndef HandlerRequest_hpp
#define HandlerRequest_hpp

#include <stdio.h>
#include <tgbot/tgbot.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace TgBot;

enum flagTypes
{
    def,
    setOld,
    setWeight
};

struct User2
{
    std::string old;
    std::string weight;
};

class HandlerRequest
{
private:
    User2 currentUser;
    std::vector<std::string> comands {"start", "drink"};
    flagTypes flag;
    
    void _comandStart(Bot& bot);
    void _anyMsg(Bot& bot);
    
    void _f_def(Bot& bot, Message::Ptr message);
    void _f_setOld(Bot& bot, Message::Ptr message);
    void _f_setWeight(Bot& bot, Message::Ptr message);

    
public:
    
    void StartBot();
};

#endif /* HandlerRequest_hpp */
