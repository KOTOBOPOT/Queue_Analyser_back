#pragma once

#include "request.hpp"
#include "response.hpp"
#include <memory>

class Handler {
public:
    virtual ~Handler() {};
    virtual bool canHandle(const Request& request) const {return false;};
    virtual Response handle(const Request& request) const { return Response(404); };
    virtual std::shared_ptr<Handler> findHandler(const Request& request) { return nullptr; };
};