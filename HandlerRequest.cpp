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
    bot.getEvents().onCommand("start", [&bot, this](TgBot::Message::Ptr message)
    {
        //check if user exist
        if(!true)
        {
            bot.getApi().sendMessage(message->chat->id, "Із поверненням, " + message->chat->firstName + " !");
            //exist move to the profile
            return;
        }
        // if doesn't create profile
        bot.getApi().sendMessage(message->chat->id, "Привіт, " + message->chat->firstName + " !");
        
        flag = setOld;
        bot.getApi().sendMessage(message->chat->id, "Скільки тобі років?");
    });
    
}

void HandlerRequest::_anyMsg(Bot& bot)
{
    bot.getEvents().onAnyMessage([&bot, this](Message::Ptr message) {
        std::cout << "user: " << message->chat->firstName << "| msg: " << message->text << std::endl;
        if (flag == def )
        {
            _f_def(bot, message);
        }else if (flag == setOld)
        {
            _f_setOld(bot, message);
        }else if (flag == setWeight)
        {
            _f_setWeight(bot, message);
        }
        
    });
}

void HandlerRequest::_f_def(Bot& bot, Message::Ptr message)
{

    for(const auto &command : comands)
    {
        if (message->text == "/" + command)
            return;
    }
    
    bot.getApi().sendMessage(message->chat->id, "Не знаю такої дії \xF0\x9F\x98\x94");
}

void HandlerRequest::_f_setOld(Bot& bot, Message::Ptr message)
{
    currentUser.old = message->text;
    flag = setWeight;
    bot.getApi().sendMessage(message->chat->id, "Яка твоя вага? \nНе турбуйся інформація повністю конфідеційна \xF0\x9F\x99\x8A");
}

void HandlerRequest::_f_setWeight(Bot& bot, Message::Ptr message)
{    
    currentUser.weight = message->text;
    flag = def;
    bot.getApi().sendMessage(message->chat->id, "Дякую, реєстрацію завершено \xF0\x9F\x98\xBD \n");
    
    bot.getApi().sendMessage(message->chat->id, "Твої дані: \n\xE2\x9C\x85Кількість років: " + currentUser.old + "\n\xE2\x9C\x85Твоя вага: " + currentUser.weight );
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
