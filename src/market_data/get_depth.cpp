/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Market Depth
        GET /api/v1/depth - Get market depth (order book)

        Parameters:
        - symbol: STRING (YES)
        - limit: INT (NO) - Default 100; max 100
*/
#include "binance.h"
#include "binance_logger.h"

void BinanceCPP::get_depth(std::string_view symbol,
                           int              limit,
                           Json::Value     &json_result) {
  BinanceCPP_logger::write_log("<BinanceCPP::get_depth>");

  std::string url(BINANCE_HOST);
  url += "/api/v1/depth?";

  std::string querystring("symbol=");
  querystring.append(symbol);
  querystring.append("&limit=");
  querystring.append(std::to_string(limit));

  url.append(querystring);
  BinanceCPP_logger::write_log("<BinanceCPP::get_depth> url = |%s|",
                               url.c_str());

  std::string str_result;
  curl_api(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);

    } catch (std::exception &e) {
      BinanceCPP_logger::write_log("<BinanceCPP::get_depth> Error ! %s",
                                   e.what());
    }
    BinanceCPP_logger::write_log("<BinanceCPP::get_depth> Done.");

  } else {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_depth> Failed to get anything.");
  }
}
