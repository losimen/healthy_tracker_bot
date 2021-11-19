//
//  HandlerRequest.cpp
//  echobot
//
//  Created by Павло Коваль on 19.11.2021.
//

#include "HandlerRequest.hpp"
#include <unistd.h>

std::string GetToken()
{
    std::ifstream nameFileout;
    nameFileout.open("token.txt");
    
    std::string token;
    std::getline(nameFileout, token);
   
    return token;
}

void HandlerRequest::_comandStart(Bot& bot)
{
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
    {
        std::string years = "NULL", weight;
        Update::Ptr p;
        //check if user exist
        if(!true)
        {
            bot.getApi().sendMessage(message->chat->id, "Welcome back, " + message->chat->firstName + " !");
            //exist move to the profile
            return;
        }
        // if doesn't create profile
        bot.getApi().sendMessage(message->chat->id, "Hi, " + message->chat->firstName + " !");
        
        bot.getApi().sendMessage(message->chat->id, "How old are you?");
        
        
        
    });
    
}

void HandlerRequest::_anyMsg(Bot& bot)
{
    bot.getEvents().onAnyMessage([&bot, this](TgBot::Message::Ptr message) {
        std::cout << "user: " << message->chat->firstName << "| msg: " << message->text << std::endl;
        for(const auto &command : comands)
        {
            if (message->text == "/" + command)
                return;
        }
        
        bot.getApi().sendMessage(message->chat->id, "Не знаю такої дії \xF0\x9F\x98\x94");
    });
}

void HandlerRequest::StartBot()
{
    TgBot::Bot bot(GetToken());

    _comandStart(bot);
    _anyMsg(bot);
    
    try {
        TgLongPoll longPoll(bot);
        while (true)
        {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}
