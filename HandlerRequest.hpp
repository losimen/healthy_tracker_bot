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

class HandlerRequest
{
private:
    std::vector<std::string> comands {"start", "drink"};
    
    void _comandStart(Bot& bot);
    void _anyMsg(Bot& bot);
public:
    
    void StartBot();
};

#endif /* HandlerRequest_hpp */
