/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Withdraw Operations Implementation
        Implementation of withdraw operations for wallet functionality
*/

#include "../../binance_cpp.h"
#include "../../binance_logger.h"
#include "../../binance_utils.h"

namespace binance_cpp {
namespace financial_trading {
namespace wallet {
namespace withdraw {

void WithdrawOperations::Withdraw(std::string_view coin, std::string_view address, double amount,
                                 std::string_view address_tag, std::string_view network,
                                 std::string_view name, std::string_view wallet_type,
                                 long recv_window, Json::Value& json_result) {
  BinanceCPP_logger::write_log("<WithdrawOperations::Withdraw>");
  
  if (core::BinanceAPI::api_key_.empty() || core::BinanceAPI::secret_key_.empty()) {
    BinanceCPP_logger::write_log("<WithdrawOperations::Withdraw> API key and secret key required");
    return;
  }

  std::string url = std::string(BINANCE_HOST) + "/sapi/v1/capital/withdraw/apply";
  std::string querystring = "";
  
  if (!coin.empty()) {
    querystring += "coin=" + std::string(coin) + "&";
  }
  if (!address.empty()) {
    querystring += "address=" + std::string(address) + "&";
  }
  if (amount > 0) {
    querystring += "amount=" + std::to_string(amount) + "&";
  }
  if (!address_tag.empty()) {
    querystring += "addressTag=" + std::string(address_tag) + "&";
  }
  if (!network.empty()) {
    querystring += "network=" + std::string(network) + "&";
  }
  if (!name.empty()) {
    querystring += "name=" + std::string(name) + "&";
  }
  if (!wallet_type.empty()) {
    querystring += "walletType=" + std::string(wallet_type) + "&";
  }
  if (recv_window > 0) {
    querystring += "recvWindow=" + std::to_string(recv_window) + "&";
  }
  
  querystring += "timestamp=" + std::to_string(get_current_ms_epoch());
  
  std::string signature = hmac_sha256(core::BinanceAPI::secret_key_, querystring);
  url += "?" + querystring + "&signature=" + signature;
  
  std::vector<std::string> extra_headers = {
    "X-MBX-APIKEY: " + core::BinanceAPI::api_key_
  };
  
  std::string result_json;
  std::string post_data = "";
  std::string action = "POST";
  
  core::BinanceAPI::CurlAPIWithHeader(url, result_json, extra_headers, post_data, action);
  
  if (!result_json.empty()) {
    Json::Reader reader;
    reader.parse(result_json, json_result);
    BinanceCPP_logger::write_log("<WithdrawOperations::Withdraw> Done.");
  } else {
    BinanceCPP_logger::write_log("<WithdrawOperations::Withdraw> Failed to get anything.");
  }
}

void WithdrawOperations::GetWithdrawHistory(std::string_view coin, std::string_view withdraw_order_id,
                                           int status, long start_time, long end_time,
                                           int offset, int limit, long recv_window, Json::Value& json_result) {
  BinanceCPP_logger::write_log("<WithdrawOperations::GetWithdrawHistory>");
  
  if (core::BinanceAPI::api_key_.empty() || core::BinanceAPI::secret_key_.empty()) {
    BinanceCPP_logger::write_log("<WithdrawOperations::GetWithdrawHistory> API key and secret key required");
    return;
  }

  std::string url = std::string(BINANCE_HOST) + "/sapi/v1/capital/withdraw/history";
  std::string querystring = "";
  
  if (!coin.empty()) {
    querystring += "coin=" + std::string(coin) + "&";
  }
  if (!withdraw_order_id.empty()) {
    querystring += "withdrawOrderId=" + std::string(withdraw_order_id) + "&";
  }
  if (status >= 0) {
    querystring += "status=" + std::to_string(status) + "&";
  }
  if (start_time > 0) {
    querystring += "startTime=" + std::to_string(start_time) + "&";
  }
  if (end_time > 0) {
    querystring += "endTime=" + std::to_string(end_time) + "&";
  }
  if (offset > 0) {
    querystring += "offset=" + std::to_string(offset) + "&";
  }
  if (limit > 0) {
    querystring += "limit=" + std::to_string(limit) + "&";
  }
  if (recv_window > 0) {
    querystring += "recvWindow=" + std::to_string(recv_window) + "&";
  }
  
  querystring += "timestamp=" + std::to_string(get_current_ms_epoch());
  
  std::string signature = hmac_sha256(core::BinanceAPI::secret_key_, querystring);
  url += "?" + querystring + "&signature=" + signature;
  
  std::vector<std::string> extra_headers = {
    "X-MBX-APIKEY: " + core::BinanceAPI::api_key_
  };
  
  std::string result_json;
  std::string post_data = "";
  std::string action = "GET";
  
  core::BinanceAPI::CurlAPIWithHeader(url, result_json, extra_headers, post_data, action);
  
  if (!result_json.empty()) {
    Json::Reader reader;
    reader.parse(result_json, json_result);
    BinanceCPP_logger::write_log("<WithdrawOperations::GetWithdrawHistory> Done.");
  } else {
    BinanceCPP_logger::write_log("<WithdrawOperations::GetWithdrawHistory> Failed to get anything.");
  }
}

}  // namespace withdraw
}  // namespace wallet
}  // namespace financial_trading
}  // namespace binance_cpp
