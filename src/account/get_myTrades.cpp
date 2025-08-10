// Note: Headers are included in binance_modular.cpp

/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - My Trades
        GET /api/v3/myTrades - Get trades for a specific account and symbol
   (SIGNED)

        Parameters:
        - symbol: STRING (YES)
        - limit: INT (NO) - Default 500; max 500
        - fromId: LONG (NO) - TradeId to fetch from. Default gets most recent
   trades
        - recvWindow: LONG (NO)
        - timestamp: LONG (YES)
*/

void BinanceCPP::get_myTrades(std::string_view symbol,
                              int limit,
                              long fromId,
                              long recvWindow,
                              Json::Value &json_result) {
  BinanceCPP_logger::write_log("<BinanceCPP::get_myTrades>");

  if (api_key.size() == 0 || secret_key.size() == 0) {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_myTrades> API Key and Secret Key has not been set.");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/api/v3/myTrades?";

  std::string querystring("symbol=");
  querystring.append(symbol);

  if (limit > 0) {
    querystring.append("&limit=");
    querystring.append(std::to_string(limit));
  }

  if (fromId > 0) {
    querystring.append("&fromId=");
    querystring.append(std::to_string(fromId));
  }

  if (recvWindow > 0) {
    querystring.append("&recvWindow=");
    querystring.append(std::to_string(recvWindow));
  }

  querystring.append("&timestamp=");
  querystring.append(std::to_string(get_current_ms_epoch()));

  std::string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
  querystring.append("&signature=");
  querystring.append(signature);

  url.append(querystring);
  std::vector<std::string> extra_http_header;
  std::string header_chunk("X-MBX-APIKEY: ");
  header_chunk.append(api_key);
  extra_http_header.push_back(header_chunk);

  BinanceCPP_logger::write_log("<BinanceCPP::get_myTrades> url = |%s|",
                               url.c_str());

  std::string action = "GET";
  std::string post_data = "";

  std::string str_result;
  curl_api_with_header(url, str_result, extra_http_header, post_data, action);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);

    } catch (std::exception &e) {
      BinanceCPP_logger::write_log("<BinanceCPP::get_myTrades> Error ! %s",
                                   e.what());
    }
    BinanceCPP_logger::write_log("<BinanceCPP::get_myTrades> Done.");

  } else {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_myTrades> Failed to get anything.");
  }

  BinanceCPP_logger::write_log("<BinanceCPP::get_myTrades> Done.\n");
}
