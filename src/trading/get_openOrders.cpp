/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Open Orders
        GET /api/v3/openOrders - Get open orders (SIGNED)
        
        Parameters:
        - symbol: STRING (YES)
        - recvWindow: LONG (NO)
        - timestamp: LONG (YES)
*/

#include "../binacpp.h"
#include "../binacpp_logger.h"
#include "../binacpp_utils.h"

void BinaCPP::get_openOrders(std::string_view symbol,
                             long recvWindow,
                             Json::Value &json_result) {
  BinaCPP_logger::write_log("<BinaCPP::get_openOrders>");

  if (api_key.size() == 0 || secret_key.size() == 0) {
    BinaCPP_logger::write_log(
        "<BinaCPP::get_openOrders> API Key and Secret Key has not been set.");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/api/v3/openOrders?";

  std::string querystring("symbol=");
  querystring.append(symbol);

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

  std::string action = "GET";
  std::string post_data = "";

  BinaCPP_logger::write_log("<BinaCPP::get_openOrders> url = |%s|",
                            url.c_str());

  std::string str_result;
  curl_api_with_header(url, str_result, extra_http_header, post_data, action);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);

    } catch (std::exception &e) {
      BinaCPP_logger::write_log("<BinaCPP::get_openOrders> Error ! %s",
                                e.what());
    }
    BinaCPP_logger::write_log("<BinaCPP::get_openOrders> Done.");

  } else {
    BinaCPP_logger::write_log(
        "<BinaCPP::get_openOrders> Failed to get anything.");
  }

  BinaCPP_logger::write_log("<BinaCPP::get_openOrders> Done.\n");
}
