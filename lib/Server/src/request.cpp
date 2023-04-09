#include "request.hpp"

#include <sstream>

Request::Request(const std::string& method, const std::string& url,
        const std::string& body, const std::map<std::string, std::string>& headers)
    : method_(method), url_(url), body_(body), headers_(headers)
{}

std::string Request::getMethod() const {
    return method_;
}

std::string Request::getUrl() const {
    return url_;
}

std::string Request::getBody() const {
    return body_;
}

std::string Request::getHeader(const std::string& key) const {
    auto iter = headers_.find(key);
    if (iter != headers_.end()) {
        return iter->second;
    }
    return "";
}

Request Request::parse(const std::string& request_string) {
    std::istringstream request_stream(request_string);

    // Разбираем первую строку запроса для получения метода, URL и версии HTTP-протокола
    std::string method, url, version;
    request_stream >> method >> url >> version;

    // Разбираем заголовки запроса
    std::map<std::string, std::string> headers;
    std::string header_line;
    std::getline(request_stream, header_line);
    while (std::getline(request_stream, header_line) && header_line != "\r") {
        // Извлекаем имя и значение заголовка
        std::size_t colon_pos = header_line.find(":");
        if (colon_pos != std::string::npos) {
            std::string header_name = header_line.substr(0, colon_pos);
            std::string header_value = header_line.substr(colon_pos + 1);
            headers[header_name] = header_value;
        }
    }

    // Оставшаяся часть запроса - тело запроса
    std::string body;
    std::getline(request_stream, body, '\0');

    return Request(method, url, body, headers);
}
