#include <crow.h>
#include <crow/http_response.h>
#pragma once

namespace http {
    crow::response ping(const crow::request &req);
}
