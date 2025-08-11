/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Create Listen Key
        POST /api/v3/userDataStream - Create a ListenKey
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
namespace user_data_stream_endpoints
{

void UserDataStream::CreateListenKey(Json::Value& json_result)
{
  BinanceCPP_logger::write_log("<UserDataStream::CreateListenKey>");

  if (core::BinanceAPI::api_key_.empty())
  {
    BinanceCPP_logger::write_log(
        "<UserDataStream::CreateListenKey> API key is required for user data "
        "stream");
    return;
  }

  std::string url = std::string(BINANCE_HOST) + "/api/v3/userDataStream";
  std::string result_json;

  std::vector<std::string> extra_http_header = {"X-MBX-APIKEY: " +
                                                core::BinanceAPI::api_key_};

  std::string post_data = "";
  std::string action    = "POST";

  core::BinanceAPI::CurlAPIWithHeader(
      url, result_json, extra_http_header, post_data, action);

  if (!result_json.empty())
  {
    Json::Reader reader;
    reader.parse(result_json, json_result);
  }
}

}  // namespace user_data_stream_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
