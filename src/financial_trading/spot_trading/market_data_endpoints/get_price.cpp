/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Get Price
        Helper function to get price as double value for a specific symbol
        Following Google C++ Style Guide naming conventions
*/

#include "../../../binance_cpp.h"
#include "../../../binance_logger.h"

namespace binance_cpp
{
namespace financial_trading
{
namespace spot_trading
{
namespace market_data_endpoints
{

double CurrentPrices::GetPrice(std::string_view symbol)
{
  BinanceCPP_logger::write_log("<CurrentPrices::GetPrice>");

  Json::Value json_result;
  GetSymbolPriceTicker(symbol, json_result);

  if (!json_result.empty() && json_result.isMember("price"))
  {
    return std::stod(json_result["price"].asString());
  }

  return 0.0;
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
