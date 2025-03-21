#include "websocket_handlers.h"
#include <crow.h>
#include <crow/http_response.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>

// #define CROW_ENFORCE_WS_SPEC
// Above enforces WS spec to meet WebSocket protocol standards

namespace ws {
crow::response open_handler(crow::websocket::connection &conn) {
  return crow::response(conn.get_remote_ip());
}

crow::response message_handler(crow::websocket::connection &conn,
                               const std::string &data, bool is_binary) {
  return crow::response(conn.get_remote_ip());
}

crow::response close_handler(crow::websocket::connection &conn,
                             const std::string &reason, uint16_t) {
  return crow::response("Closed!");
}
} // namespace ws
