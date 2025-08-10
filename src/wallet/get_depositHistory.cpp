/*
        Author: blackb1rd
        Date  : 2025/08/10
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Wallet Functions
        Updated for C++20 support
*/
#include "binance.h"
#include "binance_logger.h"
#include "binance_utils.h"

//============================================================================
// WAPI - GET DEPOSIT HISTORY
//============================================================================

void BinanceCPP::get_depositHistory(std::string_view asset,
                                    int              status,
                                    long             startTime,
                                    long             endTime,
                                    long             recvWindow,
                                    Json::Value     &json_result)
{
  BinanceCPP_logger::write_log("<BinanceCPP::get_depositHistory>");

  if (api_key.size() == 0 || secret_key.size() == 0)
  {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_depositHistory> API Key and Secret Key has not been "
        "set.");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/wapi/v3/depositHistory.html?";

  std::string querystring;
  if (!asset.empty())
  {
    querystring += "asset=" + std::string(asset);
  }
  if (status >= 0)
  {
    if (!querystring.empty())
      querystring += "&";
    querystring += "status=" + std::to_string(status);
  }
  if (startTime > 0)
  {
    if (!querystring.empty())
      querystring += "&";
    querystring += "startTime=" + std::to_string(startTime);
  }
  if (endTime > 0)
  {
    if (!querystring.empty())
      querystring += "&";
    querystring += "endTime=" + std::to_string(endTime);
  }
  if (recvWindow > 0)
  {
    if (!querystring.empty())
      querystring += "&";
    querystring += "recvWindow=" + std::to_string(recvWindow);
  }
  if (!querystring.empty())
    querystring += "&";
  querystring += "timestamp=" + std::to_string(get_current_ms_epoch());

  std::string signature = hmac_sha256(secret_key, querystring);
  querystring += "&signature=" + signature;

  url += querystring;

  std::vector<std::string> extra_headers;
  extra_headers.emplace_back("X-MBX-APIKEY:" + api_key);

  std::string action    = "GET";
  std::string post_data = "";

  std::string result;
  curl_api_with_header(url, result, extra_headers, action, post_data);

  if (!result.empty())
  {
    try
    {
      Json::Reader reader;
      reader.parse(result, json_result);
    }
    catch (const std::exception &e)
    {
      BinanceCPP_logger::write_log(
          "<BinanceCPP::get_depositHistory> Error parsing JSON: %s", e.what());
    }
  }
}
