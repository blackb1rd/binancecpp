
#include <json/json.h>

#include <map>
#include <string>
#include <vector>

#include "binacpp.h"
#include "binacpp_websocket.h"

#define API_KEY "api key"
#define SECRET_KEY "secret key"

//----------------------
int main() {
  std::string api_key = API_KEY;
  std::string secret_key = SECRET_KEY;
  BinaCPP::init(api_key, secret_key);

  Json::Value result;
  long recvWindow = 10000;

  BinaCPP::withdraw("ETH", "0x7bBd854e1CC7A762FFa19DfF07Da7E68D997bFa2", "",
                    10.0, "", recvWindow, result);
  std::cout << result << std::endl;

  BinaCPP::get_depositHistory("ETH", 0, 0, 0, recvWindow, result);
  std::cout << result << std::endl;

  BinaCPP::get_withdrawHistory("ETH", 0, 0, 0, recvWindow, result);
  std::cout << result << std::endl;

  BinaCPP::get_depositAddress("ETH", recvWindow, result);
  std::cout << result << std::endl;

  return 0;
}