#pragma once

#include "handler.hpp"

class GetQueueCountHandler : public Handler, public std::enable_shared_from_this<GetQueueCountHandler> {
public:
    void handle_request(beast::http::request<beast::http::string_body>& request,
                        beast::http::response<beast::http::string_body>& response) override {
        response.result(beast::http::status::ok);
        response.set(beast::http::field::server, "Beast");
        response.set(beast::http::field::content_type, "text/html");
        response.body() = "17";
        response.prepare_payload();
    }
};