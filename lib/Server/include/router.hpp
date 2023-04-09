#pragma once

#include <vector>
#include "handler.hpp"

class Router {
public:
    // добавляет обработчик в маршрутизатор.
    void addHandler(Handler* handler);
    // находит обработчик для данного запроса.
    Handler* findHandler(const Request& request) const;

    ~Router();

private:
    std::vector<Handler*> handlers_;
};