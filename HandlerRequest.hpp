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

class HandlerRequest
{
private:
    std::vector<std::string> comands {"start", "drink"};
    
    void _comandStart(TgBot::Bot& bot);
    void _anyMsg(TgBot::Bot& bot);
public:
    
    void StartBot();
};

#endif /* HandlerRequest_hpp */
