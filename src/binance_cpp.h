/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Main Header
        Following Google C++ Style Guide naming conventions
        Modular design based on official Binance API documentation structure
        https://developers.binance.com/
*/

#ifndef BINANCE_CPP_H
#define BINANCE_CPP_H

#include <curl/curl.h>
#include <json/json.h>

#include <concepts>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#define BINANCE_HOST "https://api.binance.com"

template <typename T>
concept StringLike = std::convertible_to<T, std::string_view>;

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Include all Financial Trading modules following official Binance API
// structure
#include "financial_trading/algo_trading.h"
#include "financial_trading/copy_trading.h"
#include "financial_trading/derivatives_trading.h"
#include "financial_trading/margin_trading.h"
#include "financial_trading/spot_trading.h"
#include "financial_trading/wallet.h"

namespace binance_cpp
{

// Core API functionality
namespace core
{
class BinanceAPI
{
 public:
  static std::string api_key_;
  static std::string secret_key_;
  static CURL*       curl_;

  static void CurlAPI(std::string& url, std::string& result_json);
  static void CurlAPIWithHeader(std::string&              url,
                                std::string&              result_json,
                                std::vector<std::string>& extra_http_header,
                                std::string&              post_data,
                                std::string&              action);
  [[nodiscard]] static size_t CurlCallback(void*        content,
                                           size_t       size,
                                           size_t       nmemb,
                                           std::string* buffer);

  static void Init();
  static void Init(std::string_view api_key, std::string_view secret_key);
  static void Cleanup() noexcept;

  // API key management
  static void SetAPIKey(std::string_view api_key);
  static void SetSecretKey(std::string_view secret_key);
  [[nodiscard]] static const std::string& GetAPIKey() noexcept;
  [[nodiscard]] static const std::string& GetSecretKey() noexcept;
};
}  // namespace core

// Main API namespace bringing together all financial trading modules
// Use the specific namespace modules for organized API access:
//   - financial_trading::spot_trading
//   - financial_trading::derivatives_trading
//   - financial_trading::margin_trading
//   - financial_trading::algo_trading
//   - financial_trading::wallet
//   - financial_trading::copy_trading

// Convenience aliases for commonly used endpoints
namespace api
{
// Quick access aliases for frequently used spot trading functions
using ServerTime =
    financial_trading::spot_trading::general_endpoints::ServerTime;
using ExchangeInfo =
    financial_trading::spot_trading::general_endpoints::ExchangeInformation;
using CurrentPrices =
    financial_trading::spot_trading::market_data_endpoints::CurrentPrices;
using OrderBook =
    financial_trading::spot_trading::market_data_endpoints::OrderBook;
using TradeData =
    financial_trading::spot_trading::market_data_endpoints::TradeData;
using AccountInfo =
    financial_trading::spot_trading::account_endpoints::AccountInformation;
using OrderManagement =
    financial_trading::spot_trading::spot_trading_endpoints::OrderManagement;
using UserDataStream =
    financial_trading::spot_trading::user_data_stream_endpoints::UserDataStream;

// Wallet operations
using DepositOperations = financial_trading::wallet::deposit::DepositOperations;
using WithdrawOperations =
    financial_trading::wallet::withdraw::WithdrawOperations;
}  // namespace api

// Legacy compatibility class for existing examples
class BinanceCPP
{
 public:
  static void init()
  {
    core::BinanceAPI::Init();
  }

  static void init(std::string_view api_key, std::string_view secret_key)
  {
    core::BinanceAPI::Init(api_key, secret_key);
  }

  static void cleanup() noexcept
  {
    core::BinanceAPI::Cleanup();
  }

  // Market data functions - redirect to new API structure
  static void get_serverTime(Json::Value& json_result)
  {
    api::ServerTime::GetServerTime(json_result);
  }

  static void get_exchangeInfo(Json::Value& json_result)
  {
    api::ExchangeInfo::GetExchangeInfo(json_result);
  }

  static void get_allPrices(Json::Value& json_result)
  {
    api::CurrentPrices::GetSymbolPriceTicker(json_result);
  }

  static double get_price(std::string_view symbol)
  {
    return api::CurrentPrices::GetPrice(symbol);
  }

  static void get_depth(std::string_view symbol,
                        int              limit,
                        Json::Value&     json_result)
  {
    api::OrderBook::GetOrderBook(symbol, limit, json_result);
  }

  static void get_aggTrades(std::string_view symbol,
                            int              fromId,
                            time_t           startTime,
                            time_t           endTime,
                            int              limit,
                            Json::Value&     json_result)
  {
    api::TradeData::GetAggregateTradesList(
        symbol, fromId, startTime, endTime, limit, json_result);
  }

  static void get_klines(std::string_view symbol,
                         std::string_view interval,
                         int              limit,
                         time_t           startTime,
                         time_t           endTime,
                         Json::Value&     json_result)
  {
    api::TradeData::GetKlinesCandlestickData(
        symbol, interval, limit, startTime, endTime, json_result);
  }

  static void get_account(long recvWindow, Json::Value& json_result)
  {
    api::AccountInfo::GetAccountInformation(recvWindow, json_result);
  }

  static void start_userDataStream(Json::Value& json_result)
  {
    api::UserDataStream::CreateListenKey(json_result);
  }

  // WAPI functions
  static void withdraw(std::string_view asset,
                       std::string_view address,
                       std::string_view addressTag,
                       double           amount,
                       std::string_view name,
                       long             recvWindow,
                       Json::Value&     json_result)
  {
    api::WithdrawOperations::Withdraw(asset,
                                      address,
                                      amount,
                                      addressTag,
                                      "",
                                      name,
                                      "",
                                      recvWindow,
                                      json_result);
  }

  static void get_depositHistory(std::string_view asset,
                                 int              status,
                                 long             startTime,
                                 long             endTime,
                                 long             recvWindow,
                                 Json::Value&     json_result)
  {
    api::DepositOperations::GetDepositHistory(asset,
                                              status,
                                              startTime,
                                              endTime,
                                              0,
                                              1000,
                                              "",
                                              recvWindow,
                                              json_result);
  }

  static void get_withdrawHistory(std::string_view asset,
                                  int              status,
                                  long             startTime,
                                  long             endTime,
                                  long             recvWindow,
                                  Json::Value&     json_result)
  {
    api::WithdrawOperations::GetWithdrawHistory(asset,
                                                "",
                                                status,
                                                startTime,
                                                endTime,
                                                0,
                                                1000,
                                                recvWindow,
                                                json_result);
  }

  static void get_depositAddress(std::string_view asset,
                                 long             recvWindow,
                                 Json::Value&     json_result)
  {
    api::DepositOperations::GetDepositAddress(
        asset, "", recvWindow, json_result);
  }

  // Core functionality - redirect to new API
  static void curl_api(std::string& url, std::string& result_json)
  {
    core::BinanceAPI::CurlAPI(url, result_json);
  }
};

}  // namespace binance_cpp

// Make BinanceCPP available at global scope for backward compatibility
using BinanceCPP = binance_cpp::BinanceCPP;

#endif  // BINANCE_CPP_H
