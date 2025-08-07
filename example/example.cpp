
// Modern C++20 headers
#include <json/json.h>

#include <format>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "binacpp.h"
#include "binacpp_websocket.h"

constexpr auto API_KEY = "api key";
constexpr auto SECRET_KEY = "user key";

// Some code to make terminal to have colors
constexpr auto KGRN = "\033[0;32;32m";
constexpr auto KCYN = "\033[0;36m";
constexpr auto KRED = "\033[0;32;31m";
constexpr auto KYEL = "\033[1;33m";
constexpr auto KBLU = "\033[0;32;34m";
constexpr auto KCYN_L = "\033[1;36m";
constexpr auto KBRN = "\033[0;33m";
constexpr auto RESET = "\033[0m";

// Global data structures using modern initialization
inline std::map<std::string, std::map<double, double>> depthCache{};
inline std::map<long, std::map<std::string, double>> klinesCache{};
inline std::map<long, std::map<std::string, double>> aggTradeCache{};
inline std::map<long, std::map<std::string, double>> userTradeCache{};
inline std::map<std::string, std::map<std::string, double>> userBalance{};

inline int lastUpdateId{0};

//------------------------------
void print_depthCache() {
  for (const auto &[bid_or_ask, price_map] : depthCache) {
    std::cout << bid_or_ask << std::endl;
    std::cout << "Price             Qty" << std::endl;

    // Use reverse iterator with modern auto
    for (auto it = price_map.rbegin(); it != price_map.rend(); ++it) {
      const auto &[price, qty] = *it;
      std::cout << std::format("{:.08f}          {:.08f}\n", price, qty);
    }
  }
}

//------------------
void print_klinesCache() {
  std::cout << "==================================" << std::endl;

  for (const auto &[start_of_candle, candle_obj] : klinesCache) {
    std::cout << std::format("s:{},o:{},h:{},l:{},c:{},v:{} \n",
                             start_of_candle,
                             candle_obj.at("o"),
                             candle_obj.at("h"),
                             candle_obj.at("l"),
                             candle_obj.at("c"),
                             candle_obj.at("v"));
  }
}

//---------------
void print_aggTradeCache() {
  std::map<long, std::map<std::string, double>>::iterator it_i;

  std::cout << "==================================" << std::endl;

  for (it_i = aggTradeCache.begin(); it_i != aggTradeCache.end(); it_i++) {
    long timestamp = (*it_i).first;
    std::map<std::string, double> aggtrade_obj = (*it_i).second;

    std::cout << "T:" << timestamp << ", ";
    printf("p: %.08f, ", aggtrade_obj["p"]);
    printf("q: %.08f ", aggtrade_obj["q"]);
    std::cout << " " << std::endl;
  }
}

//---------------
void print_userBalance() {
  std::map<std::string, std::map<std::string, double>>::iterator it_i;

  std::cout << "==================================" << std::endl;

  for (it_i = userBalance.begin(); it_i != userBalance.end(); it_i++) {
    std::string symbol = (*it_i).first;
    std::map<std::string, double> balance = (*it_i).second;

    std::cout << "Symbol :" << symbol << ", ";
    printf("Free   : %.08f, ", balance["f"]);
    printf("Locked : %.08f ", balance["l"]);
    std::cout << " " << std::endl;
  }
}

//-------------
int ws_depth_onData(Json::Value &json_result) {
  int i;

  int new_updateId = json_result["u"].asInt();

  if (new_updateId > lastUpdateId) {
    for (i = 0; i < json_result["b"].size(); i++) {
      double price = atof(json_result["b"][i][0].asString().c_str());
      double qty = atof(json_result["b"][i][1].asString().c_str());
      if (qty == 0.0) {
        depthCache["bids"].erase(price);
      } else {
        depthCache["bids"][price] = qty;
      }
    }
    for (i = 0; i < json_result["a"].size(); i++) {
      double price = atof(json_result["a"][i][0].asString().c_str());
      double qty = atof(json_result["a"][i][1].asString().c_str());
      if (qty == 0.0) {
        depthCache["asks"].erase(price);
      } else {
        depthCache["asks"][price] = qty;
      }
    }
    lastUpdateId = new_updateId;
  }
  print_depthCache();
  return 0;
}

//-------------
int ws_klines_onData(Json::Value &json_result) {
  long start_of_candle = json_result["k"]["t"].asInt64();
  klinesCache[start_of_candle]["o"] =
      atof(json_result["k"]["o"].asString().c_str());
  klinesCache[start_of_candle]["h"] =
      atof(json_result["k"]["h"].asString().c_str());
  klinesCache[start_of_candle]["l"] =
      atof(json_result["k"]["l"].asString().c_str());
  klinesCache[start_of_candle]["c"] =
      atof(json_result["k"]["c"].asString().c_str());
  klinesCache[start_of_candle]["v"] =
      atof(json_result["k"]["v"].asString().c_str());

  print_klinesCache();
  return 0;
}

//-----------
int ws_aggTrade_OnData(Json::Value &json_result) {
  long timestamp = json_result["T"].asInt64();
  aggTradeCache[timestamp]["p"] = atof(json_result["p"].asString().c_str());
  aggTradeCache[timestamp]["q"] = atof(json_result["q"].asString().c_str());

  print_aggTradeCache();
  return 0;
}

//---------------
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
      return 0;
    }
    printf("%s\n\n%s %s %s %s %s\n\n%s",
           KBLU,
           symbol.c_str(),
           side.c_str(),
           executionType.c_str(),
           orderType.c_str(),
           orderId.c_str(),
           RESET);
  } else if (action == "outboundAccountInfo") {
    // Update user balance
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

//---------------------------
/*
        Examples of how to use BinaCPP Binance API library
        Simply uncomment out the code and compile with :

        make example

        and run with

        ./example.run.sh
*/

//--------------------------

int main() {
  std::string api_key = API_KEY;
  std::string secret_key = SECRET_KEY;
  BinaCPP::init(api_key, secret_key);

  /*
          The Json::value object each element can be access like hash map <>,
          or vector <> if it is Json::array
  */
  Json::Value result;
  long recvWindow = 10000;

  //------------------------------------
  // Example : Get Server Time.
  BinaCPP::get_serverTime(result);
  std::cout << result << std::endl;
  //*/

  /*-------------------------------------------------------------
  // Example : Get all Prices
     BinaCPP::get_allPrices( result );
    cout << result << endl;
  */

  /*-------------------------------------------------------------
  //Example: Get price of single pair. Eg: BNBETH
  double bnbeth_price = BinaCPP::get_price( "BNBETH");
  cout << bnbeth_price << endl;
  //*/

  /*
  // -------------------------------------------------------------
  // Example: Get Account
  BinaCPP::get_account( recvWindow , result );
  cout << result << endl;
  //*/

  /*-------------------------------------------------------------
  // Example : Get all bid/ask prices
  BinaCPP::get_allBookTickers( result );
  cout << result << endl;
  */

  /*-------------------------------------------------------------
  // Example: Get bid/ask for single pair
  /*
  BinaCPP::get_bookTicker("bnbeth", result );
  cout << result << endl;
  */

  /*-------------------------------------------------------------
  // Example: Get Depth of single pair
  BinaCPP::get_depth( "ETHBTC", 5, result ) ;
  cout << result << endl;
  */

  //-------------------------------------------------------------
  // Example: Placing a LIMIT order
  // BinaCPP::send_order( "BNBETH", "BUY", "LIMIT", "GTC", 20 , 0.00380000,
  // "",0,0, recvWindow, result ); cout << result << endl;
  //*/

  /*-------------------------------------------------------------
  // Example: Placing a MARKET order
  BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 20 , 0,   "",0,0,
  recvWindow, result ); cout << result << endl;
  */

  /*-------------------------------------------------------------
  // Example: Placing an ICEBERG order
  //BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 1 , 0,   "",0,20,
  recvWindow , result );
  //cout << result << endl;


  /*-------------------------------------------------------------
  // Example: Check an order's status
  BinaCPP::get_order( "BNBETH", 12345678, "", recvWindow, result );
  cout << result << endl;
  */

  /*-------------------------------------------------------------
  // Example: Cancel an order
  BinaCPP::cancel_order("BNBETH", 12345678, "","", recvWindow, result);
  cout << result << endl;
  */

  /*-------------------------------------------------------------
  // Example: Getting list of open orders for specific pair
  /*
  BinaCPP::get_openOrders( "BNBETH", recvWindow, result ) ;
  cout << result << endl;
  */

  /*-------------------------------------------------------------
  // Example: Get all account orders; active, canceled, or filled.
  BinaCPP::get_allOrders( "BNBETH", 0,0, recvWindow, result )
  cout << result << endl;
  */

  /*-------------------------------------------------------------
  // Example : Get all trades history
  /*
  BinaCPP::get_myTrades( "BNBETH", 0,0, recvWindow , result );
  cout << result << endl;
  */

  /*-------------------------------------------------------------
  /*
  // Example: Getting 24hr ticker price change statistics for a symbol
     BinaCPP::get_24hr( "ETHBTC", result ) ;
     cout << result << endl;
  */

  /*-------------------------------------------------------------
  /*
  // Example: Get Kline/candlestick data for a symbol
    BinaCPP::get_klines( "ETHBTC", "1h", 10 , 0, 0, result );
    cout << result << endl;
  */

  /*-------------------------------------------------------------
  /* Websockets Endpoints */

  // Market Depth
  int i;
  std::string symbol = "BNBBTC";
  BinaCPP::get_depth(symbol.c_str(), 20, result);

  // Initialize the lastUpdateId
  lastUpdateId = result["lastUpdateId"].asInt64();

  for (int i = 0; i < result["asks"].size(); i++) {
    double price = atof(result["asks"][i][0].asString().c_str());
    double qty = atof(result["asks"][i][1].asString().c_str());
    depthCache["asks"][price] = qty;
  }
  for (int i = 0; i < result["bids"].size(); i++) {
    double price = atof(result["bids"][i][0].asString().c_str());
    double qty = atof(result["bids"][i][1].asString().c_str());
    depthCache["bids"][price] = qty;
  }
  print_depthCache();

  // Klines/CandleStick
  BinaCPP::get_klines("ETHBTC", "1h", 10, 0, 0, result);
  for (int i = 0; i < result.size(); i++) {
    long start_of_candle = result[i][0].asInt64();
    klinesCache[start_of_candle]["o"] = atof(result[i][1].asString().c_str());
    klinesCache[start_of_candle]["h"] = atof(result[i][2].asString().c_str());
    klinesCache[start_of_candle]["l"] = atof(result[i][3].asString().c_str());
    klinesCache[start_of_candle]["c"] = atof(result[i][4].asString().c_str());
    klinesCache[start_of_candle]["v"] = atof(result[i][5].asString().c_str());
  }
  print_klinesCache();

  //  AggTrades
  BinaCPP::get_aggTrades("BNBBTC", 0, 0, 0, 10, result);
  for (int i = 0; i < result.size(); i++) {
    long timestamp = result[i]["T"].asInt64();
    aggTradeCache[timestamp]["p"] = atof(result[i]["p"].asString().c_str());
    aggTradeCache[timestamp]["q"] = atof(result[i]["q"].asString().c_str());
  }
  print_aggTradeCache();

  // User Balance
  BinaCPP::get_account(recvWindow, result);
  for (int i = 0; i < result["balances"].size(); i++) {
    std::string symbol = result["balances"][i]["asset"].asString();
    userBalance[symbol]["f"] =
        atof(result["balances"][i]["free"].asString().c_str());
    userBalance[symbol]["l"] =
        atof(result["balances"][i]["locked"].asString().c_str());
  }
  print_userBalance();

  // User data stream
  BinaCPP::start_userDataStream(result);

  std::cout << result << std::endl;

  std::string ws_path = std::string("/ws/");
  ws_path.append(result["listenKey"].asString());

  BinaCPP_websocket::init();

  BinaCPP_websocket::connect_endpoint(ws_aggTrade_OnData,
                                      "/ws/bnbbtc@aggTrade");
  BinaCPP_websocket::connect_endpoint(ws_userStream_OnData, ws_path.c_str());
  BinaCPP_websocket::connect_endpoint(ws_klines_onData, "/ws/bnbbtc@kline_1m");
  BinaCPP_websocket::connect_endpoint(ws_depth_onData, "/ws/bnbbtc@depth");

  BinaCPP_websocket::enter_event_loop();

  return 0;
}