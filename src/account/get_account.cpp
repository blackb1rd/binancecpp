/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Account Information
        GET /api/v3/account - Get current account information (SIGNED)
        
        Parameters:
        - recvWindow: LONG (NO)
        - timestamp: LONG (YES)
*/

#include "../binacpp.h"
#include "../binacpp_logger.h"
#include "../binacpp_utils.h"

void BinaCPP::get_account(long recvWindow, Json::Value &json_result) {
  BinaCPP_logger::write_log("<BinaCPP::get_account>");

  if (api_key.size() == 0 || secret_key.size() == 0) {
    BinaCPP_logger::write_log(
        "<BinaCPP::get_account> API Key and Secret Key has not been set.");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/api/v3/account?";
  std::string action = "GET";

  std::string querystring("timestamp=");
  querystring.append(std::to_string(get_current_ms_epoch()));

  if (recvWindow > 0) {
    querystring.append("&recvWindow=");
    querystring.append(std::to_string(recvWindow));
  }

  std::string signature = hmac_sha256(secret_key.c_str(), querystring.c_str());
  querystring.append("&signature=");
  querystring.append(signature);

  url.append(querystring);
  std::vector<std::string> extra_http_header;
  std::string header_chunk("X-MBX-APIKEY: ");
  header_chunk.append(api_key);
  extra_http_header.push_back(header_chunk);

  BinaCPP_logger::write_log("<BinaCPP::get_account> url = |%s|", url.c_str());

  std::string post_data = "";

  std::string str_result;
  curl_api_with_header(url, str_result, extra_http_header, post_data, action);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);

    } catch (std::exception &e) {
      BinaCPP_logger::write_log("<BinaCPP::get_account> Error ! %s", e.what());
    }
    BinaCPP_logger::write_log("<BinaCPP::get_account> Done.");

  } else {
    BinaCPP_logger::write_log("<BinaCPP::get_account> Failed to get anything.");
  }

  BinaCPP_logger::write_log("<BinaCPP::get_account> Done.\n");
}
