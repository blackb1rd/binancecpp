/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Current Prices Implementation
        GET /api/v3/ticker/price - Symbol price ticker
        GET /api/v3/ticker/bookTicker - Symbol order book ticker  
        GET /api/v3/ticker/24hr - 24hr ticker price change statistics
        Following Google C++ Style Guide naming conventions
*/

#include "binance_cpp.h"
#include "binance_logger.h"

namespace binance_cpp {
namespace financial_trading {
namespace spot_trading {
namespace market_data_endpoints {

void CurrentPrices::GetSymbolPriceTicker(std::string_view symbol, Json::Value& json_result) {
  BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolPriceTicker>");

  std::string url(BINANCE_HOST);
  url += "/api/v3/ticker/price";
  
  if (!symbol.empty()) {
    url += "?symbol=";
    url += symbol;
  }

  std::string str_result;
  core::BinanceAPI::CurlAPI(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    } catch (std::exception& e) {
      BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolPriceTicker> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolPriceTicker> Done.");
  } else {
    BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolPriceTicker> Failed to get anything.");
  }
}

void CurrentPrices::GetSymbolPriceTicker(Json::Value& json_result) {
  GetSymbolPriceTicker("", json_result);
}

double CurrentPrices::GetPrice(std::string_view symbol) {
  BinanceCPP_logger::write_log("<CurrentPrices::GetPrice>");

  Json::Value json_result;
  GetSymbolPriceTicker(symbol, json_result);

  if (!json_result.empty() && json_result.isMember("price")) {
    return std::stod(json_result["price"].asString());
  }

  return 0.0;
}

void CurrentPrices::GetSymbolOrderBookTicker(std::string_view symbol, Json::Value& json_result) {
  BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolOrderBookTicker>");

  std::string url(BINANCE_HOST);
  url += "/api/v3/ticker/bookTicker";
  
  if (!symbol.empty()) {
    url += "?symbol=";
    url += symbol;
  }

  std::string str_result;
  core::BinanceAPI::CurlAPI(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    } catch (std::exception& e) {
      BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolOrderBookTicker> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolOrderBookTicker> Done.");
  } else {
    BinanceCPP_logger::write_log("<CurrentPrices::GetSymbolOrderBookTicker> Failed to get anything.");
  }
}

void CurrentPrices::GetSymbolOrderBookTicker(Json::Value& json_result) {
  GetSymbolOrderBookTicker("", json_result);
}

void CurrentPrices::Get24hrTickerPriceChangeStatistics(std::string_view symbol, Json::Value& json_result) {
  BinanceCPP_logger::write_log("<CurrentPrices::Get24hrTickerPriceChangeStatistics>");

  std::string url(BINANCE_HOST);
  url += "/api/v3/ticker/24hr";
  
  if (!symbol.empty()) {
    url += "?symbol=";
    url += symbol;
  }

  std::string str_result;
  core::BinanceAPI::CurlAPI(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    } catch (std::exception& e) {
      BinanceCPP_logger::write_log("<CurrentPrices::Get24hrTickerPriceChangeStatistics> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log("<CurrentPrices::Get24hrTickerPriceChangeStatistics> Done.");
  } else {
    BinanceCPP_logger::write_log("<CurrentPrices::Get24hrTickerPriceChangeStatistics> Failed to get anything.");
  }
}

void CurrentPrices::Get24hrTickerPriceChangeStatistics(Json::Value& json_result) {
  Get24hrTickerPriceChangeStatistics("", json_result);
}

void CurrentPrices::GetRollingWindowPriceChangeStatistics(std::string_view symbol, Json::Value& json_result) {
  BinanceCPP_logger::write_log("<CurrentPrices::GetRollingWindowPriceChangeStatistics>");

  std::string url(BINANCE_HOST);
  url += "/api/v3/ticker";
  
  if (!symbol.empty()) {
    url += "?symbol=";
    url += symbol;
  }

  std::string str_result;
  core::BinanceAPI::CurlAPI(url, str_result);

  if (str_result.size() > 0) {
    try {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    } catch (std::exception& e) {
      BinanceCPP_logger::write_log("<CurrentPrices::GetRollingWindowPriceChangeStatistics> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log("<CurrentPrices::GetRollingWindowPriceChangeStatistics> Done.");
  } else {
    BinanceCPP_logger::write_log("<CurrentPrices::GetRollingWindowPriceChangeStatistics> Failed to get anything.");
  }
}

void CurrentPrices::GetRollingWindowPriceChangeStatistics(Json::Value& json_result) {
  GetRollingWindowPriceChangeStatistics("", json_result);
}

}  // namespace market_data_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
