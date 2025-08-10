
#ifndef BINANCE_WEBSOCKET_H
#define BINANCE_WEBSOCKET_H

// Modern C++20 headers
#include <json/json.h>
#include <libwebsockets.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

constexpr std::string_view BINANCE_WS_HOST = "stream.binance.com";
constexpr int              BINANCE_WS_PORT = 9443;

// Modern C++20 callback type using std::function
using CB = std::function<int(Json::Value &json_value)>;

class BinanceCPP_websocket
{
  static struct lws_context  *context;
  static struct lws_protocols protocols[];

  static std::map<struct lws *, CB> handles;

 public:
  [[nodiscard]] static int event_cb(struct lws               *wsi,
                                    enum lws_callback_reasons reason,
                                    void                     *user,
                                    void                     *in,
                                    size_t                    len);
  static void              connect_endpoint(CB user_cb, std::string_view path);
  static void              init();
  static void              enter_event_loop();
};

#endif  // BINANCE_WEBSOCKET_H