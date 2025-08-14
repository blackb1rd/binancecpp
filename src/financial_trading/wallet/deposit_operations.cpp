/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Deposit Operations Implementation
        Implementation of deposit operations for wallet functionality
*/

#include "../../binance_cpp.h"
#include "../../binance_logger.h"
#include "../../binance_utils.h"

namespace binance_cpp
{
namespace financial_trading
{
namespace wallet
{
namespace deposit
{

void DepositOperations::GetDepositHistory(std::string_view coin,
                                          int              status,
                                          long             start_time,
                                          long             end_time,
                                          int              offset,
                                          int              limit,
                                          std::string_view tx_id,
                                          long             recv_window,
                                          Json::Value&     json_result)
{
  BinanceCPP_logger::write_log("<DepositOperations::GetDepositHistory>");

  if (core::BinanceAPI::api_key_.empty() ||
      core::BinanceAPI::secret_key_.empty())
  {
    BinanceCPP_logger::write_log(
        "<DepositOperations::GetDepositHistory> API key and secret key "
        "required");
    return;
  }

  std::string url =
      std::string(BINANCE_HOST) + "/sapi/v1/capital/deposit/hisrec";
  std::string querystring = "";

  if (!coin.empty())
  {
    querystring += "coin=" + std::string(coin) + "&";
  }
  if (status >= 0)
  {
    querystring += "status=" + std::to_string(status) + "&";
  }
  if (start_time > 0)
  {
    querystring += "startTime=" + std::to_string(start_time) + "&";
  }
  if (end_time > 0)
  {
    querystring += "endTime=" + std::to_string(end_time) + "&";
  }
  if (offset > 0)
  {
    querystring += "offset=" + std::to_string(offset) + "&";
  }
  if (limit > 0)
  {
    querystring += "limit=" + std::to_string(limit) + "&";
  }
  if (!tx_id.empty())
  {
    querystring += "txId=" + std::string(tx_id) + "&";
  }
  if (recv_window > 0)
  {
    querystring += "recvWindow=" + std::to_string(recv_window) + "&";
  }

  querystring += "timestamp=" + std::to_string(get_current_ms_epoch());

  std::string signature =
      hmac_sha256(core::BinanceAPI::secret_key_, querystring);
  url += "?" + querystring + "&signature=" + signature;

  std::vector<std::string> extra_headers = {"X-MBX-APIKEY: " +
                                            core::BinanceAPI::api_key_};

  std::string result_json;
  std::string post_data = "";
  std::string action    = "GET";

  core::BinanceAPI::CurlAPIWithHeader(
      url, result_json, extra_headers, post_data, action);

  if (!result_json.empty())
  {
    Json::Reader reader;
    reader.parse(result_json, json_result);
    BinanceCPP_logger::write_log(
        "<DepositOperations::GetDepositHistory> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<DepositOperations::GetDepositHistory> Failed to get anything.");
  }
}

void DepositOperations::GetDepositAddress(std::string_view coin,
                                          std::string_view network,
                                          long             recv_window,
                                          Json::Value&     json_result)
{
  BinanceCPP_logger::write_log("<DepositOperations::GetDepositAddress>");

  if (core::BinanceAPI::api_key_.empty() ||
      core::BinanceAPI::secret_key_.empty())
  {
    BinanceCPP_logger::write_log(
        "<DepositOperations::GetDepositAddress> API key and secret key "
        "required");
    return;
  }

  std::string url =
      std::string(BINANCE_HOST) + "/sapi/v1/capital/deposit/address";
  std::string querystring = "";

  if (!coin.empty())
  {
    querystring += "coin=" + std::string(coin) + "&";
  }
  if (!network.empty())
  {
    querystring += "network=" + std::string(network) + "&";
  }
  if (recv_window > 0)
  {
    querystring += "recvWindow=" + std::to_string(recv_window) + "&";
  }

  querystring += "timestamp=" + std::to_string(get_current_ms_epoch());

  std::string signature =
      hmac_sha256(core::BinanceAPI::secret_key_, querystring);
  url += "?" + querystring + "&signature=" + signature;

  std::vector<std::string> extra_headers = {"X-MBX-APIKEY: " +
                                            core::BinanceAPI::api_key_};

  std::string result_json;
  std::string post_data = "";
  std::string action    = "GET";

  core::BinanceAPI::CurlAPIWithHeader(
      url, result_json, extra_headers, post_data, action);

  if (!result_json.empty())
  {
    Json::Reader reader;
    reader.parse(result_json, json_result);
    BinanceCPP_logger::write_log(
        "<DepositOperations::GetDepositAddress> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<DepositOperations::GetDepositAddress> Failed to get anything.");
  }
}

}  // namespace deposit
}  // namespace wallet
}  // namespace financial_trading
}  // namespace binance_cpp
