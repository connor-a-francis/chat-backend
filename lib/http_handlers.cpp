#include "database.h"
#include <crow.h>
#include <crow/http_response.h>

// #define CROW_ENFORCE_WS_SPEC
// Above enforces WS spec to meet WebSocket protocol standards

namespace http {
crow::response ping(const crow::request &req) {
  auto &pool = Pool::getInstance();
  auto *conn = pool.conn();
  return crow::response("Pong!");
}
} 
