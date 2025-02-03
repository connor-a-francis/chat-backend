#include <crow/http_response.h>
#include <crow.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>


crow::response hello_world(const crow::request& req) {
   return crow::response(req.remote_ip_address);
}

int main() {
  crow::SimpleApp app;
  sqlite3 *db;
  int rc;

  rc = sqlite3_open("./chat.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

  CROW_ROUTE(app, "/")(hello_world);




  app.port(8080).run();
}

