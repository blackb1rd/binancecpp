

#include <json/json.h>

#include <string>

#include "src/binacpp.h"
#include "src/binacpp_websocket.h"

#define API_KEY "myapikey"
#define SECRET_KEY "mysecretkey"

//-----------------------------
int ws_klines_onData(Json::Value &json_result) {
  std::cout << json_result << std::endl;
  return 0;
}

//-------------------------
int main() {
  std::string api_key = API_KEY;
  std::string secret_key = SECRET_KEY;

  BinaCPP::init(api_key, secret_key);

  BinaCPP_websocket::init();
  BinaCPP_websocket::connect_endpoint(ws_klines_onData, "/ws/bnbbtc@kline_1m");
  BinaCPP_websocket::enter_event_loop();

  return 0;
}
