/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Get Symbol Price Ticker
        GET /api/v3/ticker/price - Symbol price ticker (with symbol parameter)
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

void CurrentPrices::GetSymbolPriceTicker(std::string_view symbol,
                                         Json::Value&     json_result)
{
  BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolPriceTicker>");

  std::string url(BINANCE_HOST);
  url += "/api/v3/ticker/price";

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
          "<CurrentPrices::GetSymbolPriceTicker> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolPriceTicker> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<CurrentPrices::GetSymbolPriceTicker> Failed to get anything.");
  }
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
