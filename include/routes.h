#ifndef QUEUE_ANALYSER_INCLUDE_ROUTES_H_
#define QUEUE_ANALYSER_INCLUDE_ROUTES_H_
#include <memory>

#include "router.h"

std::unique_ptr<Router> getRouter(const std::string& path_to_db = "../db/db.db");

#endif  // QUEUE_ANALYSER_INCLUDE_ROUTES_H_