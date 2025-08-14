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

// Windows DLL export/import macros
#ifdef _WIN32
  #ifdef BINANCECPP_EXPORTS
    #define BINANCECPP_API __declspec(dllexport)
  #else
    #define BINANCECPP_API __declspec(dllimport)
  #endif
#else
  #define BINANCECPP_API
#endif

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

class BINANCECPP_API BinanceCPP
{
  static std::string api_key;
  static std::string secret_key;
  static CURL       *curl;

 public:
  static void curl_api(std::string &url, std::string &result_json);
  static void curl_api_with_header(std::string              &url,
                                   std::string              &result_json,
                                   std::vector<std::string> &extra_http_header,
                                   std::string              &post_data,
                                   std::string              &action);
  [[nodiscard]] static size_t curl_cb(void        *content,
                                      size_t       size,
                                      size_t       nmemb,
                                      std::string *buffer);

  static void init();
  static void init(std::string_view api_key, std::string_view secret_key);
  static void cleanup() noexcept;

  // Public API
  static void get_exchangeInfo(Json::Value &json_result);
  static void get_serverTime(Json::Value &json_result);

  static void                 get_allPrices(Json::Value &json_result);
  [[nodiscard]] static double get_price(std::string_view symbol);

  static void get_allBookTickers(Json::Value &json_result);
  static void get_bookTicker(std::string_view symbol, Json::Value &json_result);

  static void get_depth(std::string_view symbol,
                        int              limit,
                        Json::Value     &json_result);
  static void get_aggTrades(std::string_view symbol,
                            int              fromId,
                            time_t           startTime,
                            time_t           endTime,
                            int              limit,
                            Json::Value     &json_result);
  static void get_24hr(std::string_view symbol, Json::Value &json_result);
  static void get_klines(std::string_view symbol,
                         std::string_view interval,
                         int              limit,
                         time_t           startTime,
                         time_t           endTime,
                         Json::Value     &json_result);

  // API + Secret keys required
  static void get_account(long recvWindow, Json::Value &json_result);

  static void get_myTrades(std::string_view symbol,
                           int              limit,
                           long             fromId,
                           long             recvWindow,
                           Json::Value     &json_result);

  static void get_openOrders(std::string_view symbol,
                             long             recvWindow,
                             Json::Value     &json_result);

  static void get_allOrders(std::string_view symbol,
                            long             orderId,
                            int              limit,
                            long             recvWindow,
                            Json::Value     &json_result);

  static void send_order(std::string_view symbol,
                         std::string_view side,
                         std::string_view type,
                         std::string_view timeInForce,
                         double           quantity,
                         double           price,
                         std::string_view newClientOrderId,
                         double           stopPrice,
                         double           icebergQty,
                         long             recvWindow,
                         Json::Value     &json_result);

  static void get_order(std::string_view symbol,
                        long             orderId,
                        std::string_view origClientOrderId,
                        long             recvWindow,
                        Json::Value     &json_result);

  static void cancel_order(std::string_view symbol,
                           long             orderId,
                           std::string_view origClientOrderId,
                           std::string_view newClientOrderId,
                           long             recvWindow,
                           Json::Value     &json_result);

  // API key required
  static void start_userDataStream(Json::Value &json_result);
  static void keep_userDataStream(std::string_view listenKey);
  static void close_userDataStream(std::string_view listenKey);

  // WAPI
  static void withdraw(std::string_view asset,
                       std::string_view address,
                       std::string_view addressTag,
                       double           amount,
                       std::string_view name,
                       long             recvWindow,
                       Json::Value     &json_result);

  static void get_depositHistory(std::string_view asset,
                                 int              status,
                                 long             startTime,
                                 long             endTime,
                                 long             recvWindow,
                                 Json::Value     &json_result);

  static void get_withdrawHistory(std::string_view asset,
                                  int              status,
                                  long             startTime,
                                  long             endTime,
                                  long             recvWindow,
                                  Json::Value     &json_result);

  static void get_depositAddress(std::string_view asset,
                                 long             recvWindow,
                                 Json::Value     &json_result);
};

namespace binance_cpp
{
// Main API namespace bringing together all financial trading modules
// Use the specific namespace modules for organized API access:
//   - financial_trading::spot_trading
//   - financial_trading::derivatives_trading
//   - financial_trading::margin_trading
//   - financial_trading::algo_trading
//   - financial_trading::wallet
//   - financial_trading::copy_trading
}  // namespace binance_cpp

#endif  // BINANCE_CPP_H
