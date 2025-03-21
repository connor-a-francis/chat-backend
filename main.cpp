#include <stdlib.h>
#include <sqlite3.h>
#include <crow.h>
#include <crow/app.h>
#include <crow/http_response.h>
#include "database.h"
#include "lib/app.h"

#define CROW_ENFORCE_WS_SPEC 

int main() {
  auto app = make_app(PROD);
  app.port(8080).run();
}
