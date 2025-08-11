/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Get Aggregate Trades List
        GET /api/v3/aggTrades - Compressed/Aggregate trades list
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

void TradeData::GetAggregateTradesList(std::string_view symbol,
                                       int              fromId,
                                       time_t           startTime,
                                       time_t           endTime,
                                       int              limit,
                                       Json::Value&     json_result)
{
  BinanceCPP_logger::write_log("<TradeData::GetAggregateTradesList>");

  std::string url = std::string(BINANCE_HOST) +
                    "/api/v3/aggTrades?symbol=" + std::string(symbol);

  if (fromId > 0)
  {
    url += "&fromId=" + std::to_string(fromId);
  }
  if (startTime > 0)
  {
    url += "&startTime=" + std::to_string(startTime * 1000);
  }
  if (endTime > 0)
  {
    url += "&endTime=" + std::to_string(endTime * 1000);
  }
  if (limit > 0 && limit <= 1000)
  {
    url += "&limit=" + std::to_string(limit);
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
