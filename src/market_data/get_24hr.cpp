// Note: Headers are included in binacpp_modular.cpp

/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - 24hr Ticker
        GET /api/v1/ticker/24hr - Get 24hr ticker price change statistics
        
        Parameters:
        - symbol: STRING (YES)
*/


void BinaCPP::get_24hr(std::string_view symbol, Json::Value &json_result) {
  BinaCPP_logger::write_log("<BinaCPP::get_24hr>");

  std::string url(BINANCE_HOST);
  url += "/api/v1/ticker/24hr?";

  std::string querystring("symbol=");
  querystring.append(symbol);

  url.append(querystring);
  BinaCPP_logger::write_log("<BinaCPP::get_24hr> url = |%s|", url.c_str());

  std::string str_result;
  curl_api(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);

    } catch (std::exception &e) {
      BinaCPP_logger::write_log("<BinaCPP::get_24hr> Error ! %s", e.what());
    }
    BinaCPP_logger::write_log("<BinaCPP::get_24hr> Done.");

  } else {
    BinaCPP_logger::write_log("<BinaCPP::get_24hr> Failed to get anything.");
  }
}
