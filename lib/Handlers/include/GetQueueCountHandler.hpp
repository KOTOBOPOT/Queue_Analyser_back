#pragma once

#include "handler.hpp"

class GetQueueCountHandler : public Handler, public std::enable_shared_from_this<GetQueueCountHandler> {
public:
    bool canHandle(const Request& request) const override;
    Response handle(const Request& request) const override;
    std::shared_ptr<Handler> findHandler(const Request& request) override;
};

