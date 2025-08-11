/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Legacy Compatibility Wrapper
        Provides backward compatibility with the old BinanceCPP class interface
        while internally using the new categorized structure
*/

#include "binance_cpp.h"

// Legacy compatibility class that maintains the old API interface
class BinanceCPP
{
 public:
  // Core methods
  static void init()
  {
    binance_cpp::core::BinanceAPI::Init();
  }

  static void init(std::string_view api_key, std::string_view secret_key)
  {
    binance_cpp::core::BinanceAPI::Init(api_key, secret_key);
  }

  static void cleanup() noexcept
  {
    binance_cpp::core::BinanceAPI::Cleanup();
  }

  // General endpoints
  static void get_serverTime(Json::Value& json_result)
  {
    binance_cpp::financial_trading::spot_trading::general_endpoints::
        ServerTime::GetServerTime(json_result);
  }

  static void get_exchangeInfo(Json::Value& json_result)
  {
    binance_cpp::financial_trading::spot_trading::general_endpoints::
        ExchangeInformation::GetExchangeInfo(json_result);
  }

  // Market data endpoints - legacy naming
  static void get_allPrices(Json::Value& json_result)
  {
    binance_cpp::financial_trading::spot_trading::market_data_endpoints::
        CurrentPrices::GetSymbolPriceTicker(json_result);
  }

  static double get_price(std::string_view symbol)
  {
    return binance_cpp::financial_trading::spot_trading::market_data_endpoints::
        CurrentPrices::GetPrice(symbol);
  }

  static void get_allBookTickers(Json::Value& json_result)
  {
    binance_cpp::financial_trading::spot_trading::market_data_endpoints::
        CurrentPrices::GetSymbolOrderBookTicker(json_result);
  }

  static void get_bookTicker(std::string_view symbol, Json::Value& json_result)
  {
    binance_cpp::financial_trading::spot_trading::market_data_endpoints::
        CurrentPrices::GetSymbolOrderBookTicker(symbol, json_result);
  }

  static void get_24hr(std::string_view symbol, Json::Value& json_result)
  {
    binance_cpp::financial_trading::spot_trading::market_data_endpoints::
        CurrentPrices::Get24hrTickerPriceChangeStatistics(symbol, json_result);
  }

  static void get_depth(std::string_view symbol,
                        int              limit,
                        Json::Value&     json_result)
  {
    binance_cpp::financial_trading::spot_trading::market_data_endpoints::
        OrderBook::GetOrderBook(symbol, limit, json_result);
  }

  // Account endpoints - legacy naming
  static void get_account(long recv_window, Json::Value& json_result)
  {
    binance_cpp::financial_trading::spot_trading::account_endpoints::
        AccountInformation::GetAccountInformation(recv_window, json_result);
  }

  static void get_myTrades(std::string_view symbol,
                           int              limit,
                           long             from_id,
                           long             recv_window,
                           Json::Value&     json_result)
  {
    binance_cpp::financial_trading::spot_trading::account_endpoints::
        AccountInformation::GetAccountTradeList(
            symbol, limit, from_id, recv_window, json_result);
  }

  // Utility methods
  static void curl_api(std::string& url, std::string& result_json)
  {
    binance_cpp::core::BinanceAPI::CurlAPI(url, result_json);
  }

  static void curl_api_with_header(std::string&              url,
                                   std::string&              result_json,
                                   std::vector<std::string>& extra_http_header,
                                   std::string&              post_data,
                                   std::string&              action)
  {
    binance_cpp::core::BinanceAPI::CurlAPIWithHeader(
        url, result_json, extra_http_header, post_data, action);
  }

  static size_t curl_cb(void*        content,
                        size_t       size,
                        size_t       nmemb,
                        std::string* buffer)
  {
    return binance_cpp::core::BinanceAPI::CurlCallback(
        content, size, nmemb, buffer);
  }
};
