#include <json/json.h>

#include <map>
#include <string>
#include <vector>

#include "src/binacpp.h"
#include "src/binance_websocket.h"

#define API_KEY "api key"
#define SECRET_KEY "secret_key"
// Some code to make terminal to have colors
#define KGRN "\033[0;32;32m"
#define KCYN "\033[0;36m"
#define KRED "\033[0;32;31m"
#define KYEL "\033[1;33m"
#define KBLU "\033[0;32;34m"
#define KCYN_L "\033[1;36m"
#define KBRN "\033[0;33m"
#define RESET "\033[0m"
std::map<std::string, std::map<std::string, double>> userBalance;

//---------------------------
void print_userBalance() {
  std::map<std::string, std::map<std::string, double>>::iterator it_i;
  std::cout << "==================================" << std::endl;
  for (it_i = userBalance.begin(); it_i != userBalance.end(); it_i++) {
    std::string symbol = (*it_i).first;
    std::map<std::string, double> balance = (*it_i).second;
    std::cout << "Symbol :" << symbol << ", ";
    printf("Free   : %.08f, ", balance["f"]);
    printf("Locked : %.08f\n", balance["l"]);
  }
}

//----------------------------------
int ws_userStream_OnData(Json::Value &json_result) {
  int i;
  std::string action = json_result["e"].asString();
  if (action == "executionReport") {
    std::string executionType = json_result["x"].asString();
    std::string orderStatus = json_result["X"].asString();
    std::string reason = json_result["r"].asString();
    std::string symbol = json_result["s"].asString();
    std::string side = json_result["S"].asString();
    std::string orderType = json_result["o"].asString();
    std::string orderId = json_result["i"].asString();
    std::string price = json_result["p"].asString();
    std::string qty = json_result["q"].asString();

    if (executionType == "NEW") {
      if (orderStatus == "REJECTED") {
        printf("%sOrder Failed! Reason: %s\n%s", KRED, reason.c_str(), RESET);
      }
      printf("%s\n\n%s %s %s %s(%s) %s %s\n\n%s",
             KGRN,
             symbol.c_str(),
             side.c_str(),
             orderType.c_str(),
             orderId.c_str(),
             orderStatus.c_str(),
             price.c_str(),
             qty.c_str(),
             RESET);
    } else {
      printf("%s\n\n%s %s %s %s %s\n\n%s",
             KBLU,
             symbol.c_str(),
             side.c_str(),
             executionType.c_str(),
             orderType.c_str(),
             orderId.c_str(),
             RESET);
    }
  } else if (action == "outboundAccountInfo") {
    for (i = 0; i < json_result["B"].size(); i++) {
      std::string symbol = json_result["B"][i]["a"].asString();
      userBalance[symbol]["f"] =
          atof(json_result["B"][i]["f"].asString().c_str());
      userBalance[symbol]["l"] =
          atof(json_result["B"][i]["f"].asString().c_str());
    }
    print_userBalance();
  }
  return 0;
}

int ws_klines_onData(Json::Value &json_result) {
  printf("Event type:%s symbol:%s\n",
         json_result["e"].asString().c_str(),
         json_result["s"].asString().c_str());
  return 0;
}

int main() {
  std::string api_key = API_KEY;
  std::string secret_key = SECRET_KEY;
  BinanceCPP::init(api_key, secret_key);
  Json::Value result;
  BinanceCPP::get_account(5000, result);
  for (int i = 0; i < result["balances"].size(); i++) {
    std::string symbol = result["balances"][i]["asset"].asString();
    userBalance[symbol]["f"] =
        atof(result["balances"][i]["free"].asString().c_str());
    userBalance[symbol]["l"] =
        atof(result["balances"][i]["locked"].asString().c_str());
  }
  print_userBalance();
  BinanceCPP::start_userDataStream(result);
  std::cout << result << std::endl;
  std::string ws_path = std::string("/ws/");
  ws_path.append(result["listenKey"].asString());
  BinanceCPP_websocket::connect_endpoint(ws_userStream_OnData, ws_path.c_str());
  BinanceCPP_websocket::enter_event_loop();
  return 0;
}
