#include "app.h"
#include "crow/app.h"
#include "http_handlers.h"
#include "websocket_handlers.h"
#include "database.h"

crow::SimpleApp make_app(const std::string &dbPath) {
  crow::SimpleApp server;

  Pool::setDbPath(dbPath);

  CROW_ROUTE(server, "/ping")(http::ping);

  CROW_WEBSOCKET_ROUTE(server, "/ws")
      .onopen(ws::open_handler)
      .onmessage(ws::message_handler)
      .onclose(ws::close_handler);
  return server;
}
