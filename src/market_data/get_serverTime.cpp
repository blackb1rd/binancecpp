// Note: Headers are included in binance_modular.cpp

/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Server Time
        GET /api/v1/time - Get server time
*/

// Note: Headers are included in binance_modular.cpp

void BinanceCPP::get_serverTime(Json::Value &json_result) {
  BinanceCPP_logger::write_log("<BinanceCPP::get_serverTime>");

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
      BinanceCPP_logger::write_log("<BinanceCPP::get_serverTime> Error ! %s",
                                   e.what());
    }
    BinanceCPP_logger::write_log("<BinanceCPP::get_serverTime> Done.");

  } else {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_serverTime> Failed to get anything.");
  }
}
