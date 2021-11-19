//
//  HandlerRequest.cpp
//  echobot
//
//  Created by Павло Коваль on 19.11.2021.
//

#include "HandlerRequest.hpp"

std::string GetToken()
{
    std::ifstream nameFileout;
    nameFileout.open("token.txt");
    
    std::string token;
    std::getline(nameFileout, token);
   
    return token;
}

void HandlerRequest::_comandStart(TgBot::Bot& bot)
{
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "Hi, " + message->chat->firstName + " !");
    });
}

void HandlerRequest::_anyMsg(TgBot::Bot& bot)
{
    bot.getEvents().onAnyMessage([&bot, this](TgBot::Message::Ptr message) {
        std::cout << "user: " << message->chat->firstName << "| msg: " << message->text << std::endl;
        for(const auto &i : comands)
        {
            if (message->text == "/" + i)
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
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}
