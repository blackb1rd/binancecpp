/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Aggregated Trades
        GET /api/v1/aggTrades - Get aggregated trades list

        Parameters:
        - symbol: STRING (YES)
        - fromId: LONG (NO) - ID to get aggregate trades from INCLUSIVE
        - startTime: LONG (NO) - Timestamp in ms to get aggregate trades from
   INCLUSIVE
        - endTime: LONG (NO) - Timestamp in ms to get aggregate trades until
   INCLUSIVE
        - limit: INT (NO) - Default 500; max 500
*/
#include "binance.h"
#include "binance_logger.h"

void BinanceCPP::get_aggTrades(std::string_view symbol,
                               int              fromId,
                               time_t           startTime,
                               time_t           endTime,
                               int              limit,
                               Json::Value     &json_result)
{
  BinanceCPP_logger::write_log("<BinanceCPP::get_aggTrades>");

  std::string url(BINANCE_HOST);
  url += "/api/v1/aggTrades?";

  std::string querystring("symbol=");
  querystring.append(symbol);

  if (startTime != 0 && endTime != 0)
  {
    querystring.append("&startTime=");
    querystring.append(std::to_string(startTime));

    querystring.append("&endTime=");
    querystring.append(std::to_string(endTime));
  }
  else
  {
    querystring.append("&fromId=");
    querystring.append(std::to_string(fromId));

    querystring.append("&limit=");
    querystring.append(std::to_string(limit));
  }

  url.append(querystring);
  BinanceCPP_logger::write_log("<BinanceCPP::get_aggTrades> url = |%s|",
                               url.c_str());

  std::string str_result;
  curl_api(url, str_result);

  if (str_result.size() > 0)
  {
    try
    {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    }
    catch (std::exception &e)
    {
      BinanceCPP_logger::write_log("<BinanceCPP::get_aggTrades> Error ! %s",
                                   e.what());
    }
    BinanceCPP_logger::write_log("<BinanceCPP::get_aggTrades> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_aggTrades> Failed to get anything.");
  }
}
