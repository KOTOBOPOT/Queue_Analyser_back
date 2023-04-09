#include "router.hpp"

void Router::addHandler(Handler* handler) {
    handlers_.push_back(handler);
}

Handler* Router::findHandler(const Request& request) const {
    for (Handler* handler : handlers_) {
        if (handler->canHandle(request)) {
            return handler;
        }
    }
    return nullptr;
}

Router::~Router()
{
    for (auto handler : handlers_) {
        delete handler;
    }
}
