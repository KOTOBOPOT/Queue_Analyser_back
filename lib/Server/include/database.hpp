#pragma once

#include <string>
#include <vector>
#include <map>

class Database {
public:
    virtual bool connect(const std::string& url) = 0;
    virtual bool disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual bool insert(const std::string& tableName, const std::map<std::string, std::string>& values) = 0;
    virtual bool update(const std::string& tableName, const std::map<std::string, std::string>& values, const std::string& condition) = 0;
    virtual bool remove(const std::string& tableName, const std::string& condition) = 0;
    virtual std::vector<std::map<std::string, std::string>> select(const std::string& tableName, const std::vector<std::string>& fields, const std::string& condition = "") = 0;
};
