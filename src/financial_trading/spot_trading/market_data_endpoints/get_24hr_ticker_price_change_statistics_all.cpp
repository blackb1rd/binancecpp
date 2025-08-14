/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Get 24hr Ticker Price Change Statistics
        GET /api/v3/ticker/24hr - 24hr ticker price change statistics (all
   symbols) Following Google C++ Style Guide naming conventions
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

void CurrentPrices::Get24hrTickerPriceChangeStatistics(Json::Value& json_result)
{
  Get24hrTickerPriceChangeStatistics("", json_result);
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
