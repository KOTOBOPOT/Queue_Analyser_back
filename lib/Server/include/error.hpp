#pragma once

#include <string>

class Error {
public:
    Error(int code, const std::string& message) : code_(code), message_(message) {}

    int code() const { return code_; }
    std::string message() const { return message_; }

private:
    int code_;
    std::string message_;
};