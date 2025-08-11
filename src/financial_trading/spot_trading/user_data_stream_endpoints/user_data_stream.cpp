/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - User Data Stream Implementation
        Implementation of user data stream endpoints for Spot Trading
*/

#include "binance_cpp.h"
#include "binance_logger.h"
#include "binance_utils.h"

namespace binance_cpp {
namespace financial_trading {
namespace spot_trading {
namespace user_data_stream_endpoints {

void UserDataStream::CreateListenKey(Json::Value& json_result) {
  BinanceCPP_logger::write_log("<UserDataStream::CreateListenKey>");
  
  if (core::BinanceAPI::api_key_.empty()) {
    BinanceCPP_logger::write_log("<UserDataStream::CreateListenKey> API key is required for user data stream");
    return;
  }

  std::string url = std::string(BINANCE_HOST) + "/api/v3/userDataStream";
  std::string result_json;
  
  std::vector<std::string> extra_http_header = {
    "X-MBX-APIKEY: " + core::BinanceAPI::api_key_
  };
  
  std::string post_data = "";
  std::string action = "POST";
  
  core::BinanceAPI::CurlAPIWithHeader(url, result_json, extra_http_header, post_data, action);
  
  if (!result_json.empty()) {
    Json::Reader reader;
    reader.parse(result_json, json_result);
  }
}

void UserDataStream::PingExtendListenKey(std::string_view listen_key) {
  BinanceCPP_logger::write_log("<UserDataStream::PingExtendListenKey>");
  
  if (core::BinanceAPI::api_key_.empty()) {
    BinanceCPP_logger::write_log("<UserDataStream::PingExtendListenKey> API key is required for user data stream");
    return;
  }

  std::string url = std::string(BINANCE_HOST) + "/api/v3/userDataStream?listenKey=" + std::string(listen_key);
  std::string result_json;
  
  std::vector<std::string> extra_http_header = {
    "X-MBX-APIKEY: " + core::BinanceAPI::api_key_
  };
  
  std::string post_data = "";
  std::string action = "PUT";
  
  core::BinanceAPI::CurlAPIWithHeader(url, result_json, extra_http_header, post_data, action);
}

void UserDataStream::CloseListenKey(std::string_view listen_key) {
  BinanceCPP_logger::write_log("<UserDataStream::CloseListenKey>");
  
  if (core::BinanceAPI::api_key_.empty()) {
    BinanceCPP_logger::write_log("<UserDataStream::CloseListenKey> API key is required for user data stream");
    return;
  }

  std::string url = std::string(BINANCE_HOST) + "/api/v3/userDataStream?listenKey=" + std::string(listen_key);
  std::string result_json;
  
  std::vector<std::string> extra_http_header = {
    "X-MBX-APIKEY: " + core::BinanceAPI::api_key_
  };
  
  std::string post_data = "";
  std::string action = "DELETE";
  
  core::BinanceAPI::CurlAPIWithHeader(url, result_json, extra_http_header, post_data, action);
}

}  // namespace user_data_stream_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
