#include <gtest/gtest.h>
#include "../lib/app.h"
#include "../lib/database.h"

TEST(API, PING) {
  auto app = make_app(IN_MEMORY);
  app.validate();
  crow::request req;
  crow::response res;
  req.url = "/ping";
  app.handle_full(req, res);
  ASSERT_EQ(res.body, "Pong!");
}
