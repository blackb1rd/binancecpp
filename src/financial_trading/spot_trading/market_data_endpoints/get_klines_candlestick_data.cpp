/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Get Klines Candlestick Data
        GET /api/v3/klines - Kline/candlestick bars for a symbol
*/

#include "../../../binance_cpp.h"
#include "../../../binance_logger.h"
#include "../../../binance_utils.h"

namespace binance_cpp
{
namespace financial_trading
{
namespace spot_trading
{
namespace market_data_endpoints
{

void TradeData::GetKlinesCandlestickData(std::string_view symbol,
                                         std::string_view interval,
                                         int              limit,
                                         time_t           startTime,
                                         time_t           endTime,
                                         Json::Value&     json_result)
{
  BinanceCPP_logger::write_log("<TradeData::GetKlinesCandlestickData>");

  std::string url = std::string(BINANCE_HOST) +
                    "/api/v3/klines?symbol=" + std::string(symbol) +
                    "&interval=" + std::string(interval);

  if (limit > 0 && limit <= 1000)
  {
    url += "&limit=" + std::to_string(limit);
  }
  if (startTime > 0)
  {
    url += "&startTime=" + std::to_string(startTime * 1000);
  }
  if (endTime > 0)
  {
    url += "&endTime=" + std::to_string(endTime * 1000);
  }

  std::string result_json;
  core::BinanceAPI::CurlAPI(url, result_json);

  if (!result_json.empty())
  {
    Json::Reader reader;
    reader.parse(result_json, json_result);
  }
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
