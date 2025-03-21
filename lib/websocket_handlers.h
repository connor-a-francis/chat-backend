#include <crow/http_response.h>
#include <crow.h>
#pragma once

namespace ws  {
crow::response open_handler(crow::websocket::connection& conn);

crow::response message_handler(crow::websocket::connection& conn, const std::string& data, bool is_binary);

crow::response close_handler(crow::websocket::connection& conn, const std::string& reason, uint16_t);
}
