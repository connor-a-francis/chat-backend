#include "database.h"
#include <mutex>
#include <sqlite3.h>
#include <stdexcept>

const char *dbPath_;

Pool &Pool::getInstance() {
  static Pool instance(dbPath_);
  return instance;
}

void Pool::setDbPath(const std::string &dbPath) { dbPath_ = dbPath.c_str(); }

sqlite3 *Pool::conn() const { return db_; }

Pool::Pool(const std::string &dbPath) {
  int rc = sqlite3_open(dbPath.c_str(), &db_);
  if (rc != SQLITE_OK) {
    throw std::runtime_error("Failed to open database: " +
                             std::string(sqlite3_errmsg(db_)));
  }
}

Pool::~Pool() {
  if (db_) {
    sqlite3_close(db_);
  }
}
