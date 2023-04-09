#pragma once

#include <string>
#include <map>

class Request {
public:
    Request(): method_(""), url_(""), body_(""), headers_(){};
    Request(const std::string& method, const std::string& url,
            const std::string& body = "", const std::map<std::string, std::string>& headers = {});

    std::string getMethod() const;
    std::string getUrl() const;
    std::string getBody() const;
    std::string getHeader(const std::string& key) const;

    static Request parse(const std::string& request_string);    
private:
    std::string method_;
    std::string url_;
    std::string body_;
    std::map<std::string, std::string> headers_;
};
