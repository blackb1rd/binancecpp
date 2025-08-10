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
// WAPI - WITHDRAW FUNCTIONS
//============================================================================

void BinanceCPP::withdraw(std::string_view asset,
                          std::string_view address,
                          std::string_view addressTag,
                          double           amount,
                          std::string_view name,
                          long             recvWindow,
                          Json::Value     &json_result)
{
  BinanceCPP_logger::write_log("<BinanceCPP::withdraw>");

  if (api_key.size() == 0 || secret_key.size() == 0)
  {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::withdraw> API Key and Secret Key has not been set.");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/wapi/v3/withdraw.html?";

  std::string querystring;
  querystring += "asset=" + std::string(asset);
  querystring += "&address=" + std::string(address);
  if (!addressTag.empty())
  {
    querystring += "&addressTag=" + std::string(addressTag);
  }
  querystring += "&amount=" + std::to_string(amount);
  if (!name.empty())
  {
    querystring += "&name=" + std::string(name);
  }
  if (recvWindow > 0)
  {
    querystring += "&recvWindow=" + std::to_string(recvWindow);
  }
  querystring += "&timestamp=" + std::to_string(get_current_ms_epoch());

  std::string signature = hmac_sha256(secret_key, querystring);
  querystring += "&signature=" + signature;

  url += querystring;

  std::vector<std::string> extra_headers;
  extra_headers.emplace_back("X-MBX-APIKEY:" + api_key);

  std::string action    = "POST";
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
          "<BinanceCPP::withdraw> Error parsing JSON: %s", e.what());
    }
  }
}
