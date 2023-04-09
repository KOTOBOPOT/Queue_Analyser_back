#include "response.hpp"

#include <sstream>

Response::Response(int status_code, const std::string& body, const std::map<std::string, std::string>& headers)
    : status_code_(status_code), body_(body), headers_(headers) {}

int Response::status_code() const {
    return status_code_;
}

const std::string& Response::body() const {
    return body_;
}

const std::map<std::string, std::string>& Response::headers() const {
    return headers_;
}

std::string Response::to_string() const {
    std::stringstream ss;
    ss << "HTTP/1.1 " << status_code_ << " " << status_codes_.at(status_code_) << "\r\n";
    for (const auto& header : headers_) {
        ss << header.first << ": " << header.second << "\r\n";
    }
    ss << "\r\n" << body_;
    return ss.str();
}
