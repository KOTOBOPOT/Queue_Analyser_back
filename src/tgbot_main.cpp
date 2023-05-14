#include "bot.h"

int main(int argc, char **argv)
{
	auto bot = QueueBot::SimpleBot("6216802370:AAHtsAHiNSVm4PZv2r1YZHdQu5ap63LF8kE");
	auto h = QueueBot::SimpleHandler("test");
	bot.addKeyboardButton(h, 1, 1);
	bot.run();
}