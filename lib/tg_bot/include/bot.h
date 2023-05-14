#ifndef QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_H_
#define QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_H_

#include <tgbot/tgbot.h>
#include <string>
#include <vector>
#include <memory>

void bot();

namespace QueueBot
{
	class IBotHandler
	{
	public:
		IBotHandler() {};
		IBotHandler(const IBotHandler& handler) = default;
		virtual ~IBotHandler() = default;

		virtual std::string getHandlerString() = 0;
		virtual bool isHandler(const std::string& token) = 0;
		virtual std::string invoke() = 0;
		
	};

	class SimpleHandler : public IBotHandler
	{
	public:
		SimpleHandler(std::string token) : _value(token) {}
		SimpleHandler(const SimpleHandler& handler) : IBotHandler(handler), _value(handler._value) {}

		std::string getHandlerString() override 
		{ return _value; }
		bool isHandler(const std::string& token) override {return token=="";}
		std::string invoke() override {return _value;}

	private:
		std::string _value;
	};

	class ITgBot
	{
	public:
		ITgBot(std::string token) {};
		virtual ~ITgBot() = default;

		virtual void addMenuButton(IBotHandler& handler) = 0;
		virtual void addKeyboardButton(IBotHandler& handler, size_t row, size_t col) = 0;
		virtual void run() = 0;
	};

	class SimpleBot : public ITgBot
	{
	public:
		SimpleBot(std::string token) : ITgBot(token), _bot(token), _keyboard(std::make_unique<TgBot::ReplyKeyboardMarkup>())
		{
			_keyboard->resizeKeyboard = true;
			_keyboard->oneTimeKeyboard = false;
		}

		void addKeyboardButton(IBotHandler& handler, size_t row, size_t col) override
		{
			TgBot::KeyboardButton::Ptr button(std::make_unique<TgBot::KeyboardButton>());
			button->text = handler.getHandlerString();
			if (_keyboard->keyboard.size() < row)
				_keyboard->keyboard.resize(row);
			
			if (_keyboard->keyboard[row-1].size() < col)
				_keyboard->keyboard[row-1].resize(col);

			_keyboard->keyboard[row-1][col-1] = button;
		}

		void addMenuButton(IBotHandler& handler) override {}

		void run() override
		{
			TgBot::TgLongPoll longPoll(_bot);
		    while (true) {
		        longPoll.start();
		    }
		}

	private:
		TgBot::Bot _bot;
		TgBot::ReplyKeyboardMarkup::Ptr _keyboard;

	};
}

#endif  // QUEUE_ANALYSER_LIB_TG_BOT_INCLUDE_BOT_H_