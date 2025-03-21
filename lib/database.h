#include <sqlite3.h>
#include <stdexcept>
#pragma once

#define IN_MEMORY ":memory:"
#define PROD "./chat_backend.db"

class Pool {
public:
    static Pool& getInstance();
    static void setDbPath(const std::string &dbPath);
    sqlite3* conn() const;
private:
    sqlite3* db_;
    Pool(const std::string& dbPath);
    ~Pool();
};
