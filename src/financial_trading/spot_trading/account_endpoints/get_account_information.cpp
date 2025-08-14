/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Get Account Information
        GET /api/v3/account - Get current account information (SIGNED)
        Following Google C++ Style Guide naming conventions
*/

#include "../../../binance_cpp.h"
#include "../../../binance_logger.h"
#include "../../../binance_utils.h"

namespace binance_cpp
{
namespace financial_trading
{
namespace spot_trading
{
namespace account_endpoints
{

void AccountInformation::GetAccountInformation(long         recv_window,
                                               Json::Value& json_result)
{
  BinanceCPP_logger::write_log("<AccountInformation::GetAccountInformation>");

  if (core::BinanceAPI::api_key_.empty() ||
      core::BinanceAPI::secret_key_.empty())
  {
    BinanceCPP_logger::write_log(
        "<AccountInformation::GetAccountInformation> API key and secret key "
        "required");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/api/v3/account?";

  std::string query_string = "timestamp=";
  query_string += std::to_string(get_current_ms_epoch());

  if (recv_window > 0)
  {
    query_string += "&recvWindow=";
    query_string += std::to_string(recv_window);
  }

  std::string signature =
      hmac_sha256(core::BinanceAPI::secret_key_.c_str(), query_string.c_str());
  query_string += "&signature=";
  query_string += signature;

  url += query_string;

  std::vector<std::string> extra_http_header;
  std::string header_chunk = "X-MBX-APIKEY: " + core::BinanceAPI::api_key_;
  extra_http_header.push_back(header_chunk);

  std::string post_data = "";
  std::string action    = "GET";
  std::string str_result;

  core::BinanceAPI::CurlAPIWithHeader(
      url, str_result, extra_http_header, post_data, action);

  if (str_result.size() > 0)
  {
    try
    {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    }
    catch (std::exception& e)
    {
      BinanceCPP_logger::write_log(
          "<AccountInformation::GetAccountInformation> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log(
        "<AccountInformation::GetAccountInformation> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<AccountInformation::GetAccountInformation> Failed to get anything.");
  }
}

}  // namespace account_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
