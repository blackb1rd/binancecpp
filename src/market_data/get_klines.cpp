/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Klines/Candlestick Data
        GET /api/v1/klines - Get Klines (Candlestick/OHLC data)

        Parameters:
        - symbol: STRING (YES)
        - interval: ENUM (YES)
        - limit: INT (NO) - Default 500; max 500
        - startTime: LONG (NO)
        - endTime: LONG (NO)
*/
#include "binance.h"
#include "binance_logger.h"

void BinanceCPP::get_klines(std::string_view symbol,
                            std::string_view interval,
                            int              limit,
                            time_t           startTime,
                            time_t           endTime,
                            Json::Value     &json_result) {
  BinanceCPP_logger::write_log("<BinanceCPP::get_klines>");

  std::string url(BINANCE_HOST);
  url += "/api/v1/klines?";

  std::string querystring("symbol=");
  querystring.append(symbol);

  querystring.append("&interval=");
  querystring.append(interval);

  if (startTime > 0 && endTime > 0) {
    querystring.append("&startTime=");
    querystring.append(std::to_string(startTime));

    querystring.append("&endTime=");
    querystring.append(std::to_string(endTime));

  } else if (limit > 0) {
    querystring.append("&limit=");
    querystring.append(std::to_string(limit));
  }

  url.append(querystring);
  BinanceCPP_logger::write_log("<BinanceCPP::get_klines> url = |%s|",
                               url.c_str());

  std::string str_result;
  curl_api(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);

    } catch (std::exception &e) {
      BinanceCPP_logger::write_log("<BinanceCPP::get_klines> Error ! %s",
                                   e.what());
    }
    BinanceCPP_logger::write_log("<BinanceCPP::get_klines> Done.");

  } else {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_klines> Failed to get anything.");
  }
}
