/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Server Time
        GET /api/v1/time - Get server time
*/

// Note: Headers are included in binacpp_modular.cpp

#include "../binacpp.h"
#include "../binacpp_logger.h"

void BinaCPP::get_serverTime(Json::Value &json_result) {
  BinaCPP_logger::write_log("<BinaCPP::get_serverTime>");

  std::string url(BINANCE_HOST);
  url += "/api/v1/time";

  std::string str_result;
  curl_api(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);

    } catch (std::exception &e) {
      BinaCPP_logger::write_log("<BinaCPP::get_serverTime> Error ! %s",
                                e.what());
    }
    BinaCPP_logger::write_log("<BinaCPP::get_serverTime> Done.");

  } else {
    BinaCPP_logger::write_log(
        "<BinaCPP::get_serverTime> Failed to get anything.");
  }
}
