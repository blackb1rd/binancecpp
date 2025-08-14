/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Get Symbol Price Ticker
        GET /api/v3/ticker/price - Symbol price ticker (all symbols)
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

void CurrentPrices::GetSymbolPriceTicker(Json::Value& json_result)
{
  GetSymbolPriceTicker("", json_result);
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
