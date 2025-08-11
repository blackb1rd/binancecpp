/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Order Book Implementation
        GET /api/v3/depth - Order book
        Following Google C++ Style Guide naming conventions
*/

#include "binance_cpp.h"
#include "binance_logger.h"

namespace binance_cpp
{
namespace financial_trading
{
namespace spot_trading
{
namespace market_data_endpoints
{

void OrderBook::GetOrderBook(std::string_view symbol,
                             int              limit,
                             Json::Value&     json_result)
{
  BinanceCPP_logger::write_log("<OrderBook::GetOrderBook>");

  if (symbol.empty())
  {
    BinanceCPP_logger::write_log(
        "<OrderBook::GetOrderBook> Symbol cannot be empty");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/api/v3/depth?symbol=";
  url += symbol;

  if (limit > 0)
  {
    url += "&limit=";
    url += std::to_string(limit);
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
      BinanceCPP_logger::write_log("<OrderBook::GetOrderBook> Error ! %s",
                                   e.what());
    }
    BinanceCPP_logger::write_log("<OrderBook::GetOrderBook> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<OrderBook::GetOrderBook> Failed to get anything.");
  }
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
