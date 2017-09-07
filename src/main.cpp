#include <signal.h>
#include <stdio.h>
#include <exception>

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;


void clearString(string &str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (!isalpha(*it)) str.erase(it);
    }
}

bool isPalindrome(string str) {
    std::transform(
        str.begin(), str.end(), str.begin(),
        [](unsigned char c) -> unsigned char { return std::tolower(c); });
    clearString(str);
    for (auto it = str.begin(), it2 = str.end() - 1; it < it2; ++it, --it2) {
        if (*it != *it2) {
            return false;
        }
    }
    return true;
}

int main() {
    Bot bot("API_KEY");
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        string res = "is ";
        printf("User wrote %s\n", message->text.c_str());
        if (!isPalindrome(message->text)) {
            res += "not ";
        }
        bot.getApi().sendMessage(message->chat->id,
                                 "Your message " + res + "a palindrome.");
    });

    signal(SIGINT, [](int s) {
        printf("Got SIGINT, closing.\n");
        exit(1);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

        TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (exception &e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}
