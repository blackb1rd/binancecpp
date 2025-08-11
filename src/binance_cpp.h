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



}  // namespace binance_cpp

#endif  // BINANCE_CPP_H
