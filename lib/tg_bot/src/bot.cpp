#include <iostream>
#include <tgbot/tgbot.h>

void bot(){
    TgBot::Bot bot("6216802370:AAHtsAHiNSVm4PZv2r1YZHdQu5ap63LF8kE");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hello, world!");
    });
     bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        std::cout << "User wrote " << message->text << std::endl;
    });

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}