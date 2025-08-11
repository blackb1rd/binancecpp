
#include <json/json.h>

#include <map>
#include <string>
#include <vector>

#include "binance_cpp.h"
#include "binance_websocket.h"

std::map<long, std::map<std::string, double>> aggTradeCache;

//---------------
void print_aggTradeCache()
{
  std::map<long, std::map<std::string, double>>::iterator it_i;

  std::cout << "==================================" << std::endl;

  for (it_i = aggTradeCache.begin(); it_i != aggTradeCache.end(); it_i++)
  {
    long                          aggTradeId   = (*it_i).first;
    std::map<std::string, double> aggtrade_obj = (*it_i).second;

    std::cout << "AggtradeId:" << aggTradeId << ", ";
    printf("p: %.08f, ", aggtrade_obj["p"]);
    printf("q: %.08f ", aggtrade_obj["q"]);
    std::cout << " " << std::endl;
  }
}

//-----------
int ws_aggTrade_OnData(Json::Value &json_result)
{
  long aggTradeId                = json_result["a"].asInt64();
  aggTradeCache[aggTradeId]["p"] = atof(json_result["p"].asString().c_str());
  aggTradeCache[aggTradeId]["q"] = atof(json_result["q"].asString().c_str());

  print_aggTradeCache();
  return 0;
}

//---------------------------
/*
        To compile, type
        make example_aggTrades
*/

//--------------------------

int main()
{
  Json::Value result;
  long        recvWindow = 10000;

  binance_cpp::core::BinanceAPI::Init();

  //  AggTrades
  binance_cpp::financial_trading::spot_trading::market_data_endpoints::TradeData::GetAggregateTradesList("BNBBTC", 0, 0, 0, 10, result);

  for (int i = 0; i < result.size(); i++)
  {
    long aggTradeId                = result[i]["a"].asInt64();
    aggTradeCache[aggTradeId]["p"] = atof(result[i]["p"].asString().c_str());
    aggTradeCache[aggTradeId]["q"] = atof(result[i]["q"].asString().c_str());
  }
  print_aggTradeCache();

  BinanceCPP_websocket::init();
  BinanceCPP_websocket::connect_endpoint(ws_aggTrade_OnData,
                                         "/ws/bnbbtc@aggTrade");
  BinanceCPP_websocket::enter_event_loop();

  return 0;
}