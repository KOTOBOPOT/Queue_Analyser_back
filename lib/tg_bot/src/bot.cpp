#include <iostream>

#include "bot.h"

#include <chrono>

int count = 0;

void bot() 
{
    TgBot::Bot bot("6216802370:AAHtsAHiNSVm4PZv2r1YZHdQu5ap63LF8kE");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hello, " + message->from->firstName + "!");

        // Создаем клавиатуру с одной кнопкой
        TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
        TgBot::KeyboardButton::Ptr button(new TgBot::KeyboardButton);
        button->text = "Refresh " + std::to_string(count++);
        std::vector<TgBot::KeyboardButton::Ptr> row;
        row.push_back(button);
        keyboard->keyboard.push_back(row);

        bot.getApi().sendMessage(message->chat->id, "Press the button to refresh", false, 0, keyboard);
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        std::cout << "User wrote " << message->text << std::endl;
    });

    std::cout << "Bot username: " << bot.getApi().getMe()->username << std::endl;

    bot.getApi().deleteWebhook();

    TgBot::TgLongPoll longPoll(bot);
    while (true) {
        longPoll.start();
    }
}