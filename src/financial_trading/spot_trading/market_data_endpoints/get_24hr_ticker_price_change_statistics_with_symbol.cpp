/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Get 24hr Ticker Price Change Statistics
        GET /api/v3/ticker/24hr - 24hr ticker price change statistics (with
   symbol) Following Google C++ Style Guide naming conventions
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

void CurrentPrices::Get24hrTickerPriceChangeStatistics(std::string_view symbol,
                                                       Json::Value& json_result)
{
  BinanceCPP_logger::write_log(
      "<CurrentPrices::Get24hrTickerPriceChangeStatistics>");

  std::string url(BINANCE_HOST);
  url += "/api/v3/ticker/24hr";

  if (!symbol.empty())
  {
    url += "?symbol=";
    url += symbol;
  }

  std::string str_result;
  core::BinanceAPI::CurlAPI(url, str_result);

  if (str_result.size() > 0)
  {
    try
    {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    }
    catch (std::exception& e)
    {
      BinanceCPP_logger::write_log(
          "<CurrentPrices::Get24hrTickerPriceChangeStatistics> Error ! %s",
          e.what());
    }
    BinanceCPP_logger::write_log(
        "<CurrentPrices::Get24hrTickerPriceChangeStatistics> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<CurrentPrices::Get24hrTickerPriceChangeStatistics> Failed to get "
        "anything.");
  }
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
