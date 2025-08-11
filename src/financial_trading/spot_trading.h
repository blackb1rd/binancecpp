/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Spot Trading Header
        Following Google C++ Style Guide naming conventions
        https://developers.binance.com/docs/binance-spot-api-docs
*/

#ifndef BINANCE_CPP_SPOT_TRADING_H
#define BINANCE_CPP_SPOT_TRADING_H

#include <json/json.h>

#include <string_view>

namespace binance_cpp
{
namespace financial_trading
{
namespace spot_trading
{

// General Market Data Endpoints (Public)
namespace general_endpoints
{
class TestConnectivity
{
 public:
  static void Ping(Json::Value& json_result);
};

class ExchangeInformation
{
 public:
  static void GetExchangeInfo(Json::Value& json_result);
  static void GetSystemStatus(Json::Value& json_result);
};

class ServerTime
{
 public:
  static void GetServerTime(Json::Value& json_result);
};
}  // namespace general_endpoints

// Market Data Endpoints (Public)
namespace market_data_endpoints
{
class OrderBook
{
 public:
  static void GetOrderBook(std::string_view symbol,
                           int              limit,
                           Json::Value&     json_result);
};

class RecentTrades
{
 public:
  static void GetRecentTradesList(std::string_view symbol,
                                  int              limit,
                                  Json::Value&     json_result);
  static void GetOldTradeLookup(std::string_view symbol,
                                int              limit,
                                long             from_id,
                                Json::Value&     json_result);
  static void GetAggregateTradesList(std::string_view symbol,
                                     int              from_id,
                                     time_t           start_time,
                                     time_t           end_time,
                                     int              limit,
                                     Json::Value&     json_result);
};

class CurrentPrices
{
 public:
  static void   GetSymbolPriceTicker(std::string_view symbol,
                                     Json::Value&     json_result);
  static void   GetSymbolPriceTicker(Json::Value& json_result);  // All symbols
  static double GetPrice(std::string_view symbol);

  static void GetSymbolOrderBookTicker(std::string_view symbol,
                                       Json::Value&     json_result);
  static void GetSymbolOrderBookTicker(
      Json::Value& json_result);  // All symbols

  static void GetRollingWindowPriceChangeStatistics(std::string_view symbol,
                                                    Json::Value& json_result);
  static void GetRollingWindowPriceChangeStatistics(
      Json::Value& json_result);  // All symbols

  static void Get24hrTickerPriceChangeStatistics(std::string_view symbol,
                                                 Json::Value&     json_result);
  static void Get24hrTickerPriceChangeStatistics(
      Json::Value& json_result);  // All symbols
};

class KlineCandlestickData
{
 public:
  static void GetKlineCandlestickData(std::string_view symbol,
                                      std::string_view interval,
                                      int              limit,
                                      time_t           start_time,
                                      time_t           end_time,
                                      Json::Value&     json_result);
  static void GetUIKlines(std::string_view symbol,
                          std::string_view interval,
                          int              limit,
                          time_t           start_time,
                          time_t           end_time,
                          Json::Value&     json_result);
  static void GetCurrentAveragePrice(std::string_view symbol,
                                     Json::Value&     json_result);
};

class TradeData
{
 public:
  static void GetAggregateTradesList(std::string_view symbol,
                                     int              fromId,
                                     time_t           startTime,
                                     time_t           endTime,
                                     int              limit,
                                     Json::Value&     json_result);
  static void GetKlinesCandlestickData(std::string_view symbol,
                                       std::string_view interval,
                                       int              limit,
                                       time_t           startTime,
                                       time_t           endTime,
                                       Json::Value&     json_result);
};
}  // namespace market_data_endpoints

// Account Endpoints (Private - Requires API Key + Signature)
namespace account_endpoints
{
class AccountInformation
{
 public:
  static void GetAccountInformation(long recv_window, Json::Value& json_result);
  static void GetAccountTradeList(std::string_view symbol,
                                  int              limit,
                                  long             from_id,
                                  long             recv_window,
                                  Json::Value&     json_result);
  static void GetCurrentOrderCountUsage(long         recv_window,
                                        Json::Value& json_result);
  static void GetPreventedMatches(std::string_view symbol,
                                  long             prevented_match_id,
                                  long             order_id,
                                  long             from_prevented_match_id,
                                  int              limit,
                                  long             recv_window,
                                  Json::Value&     json_result);
  static void GetAllocations(std::string_view symbol,
                             long             start_time,
                             long             end_time,
                             long             from_allocation_id,
                             int              limit,
                             long             order_id,
                             long             recv_window,
                             Json::Value&     json_result);
  static void GetCommissionRates(std::string_view symbol,
                                 long             recv_window,
                                 Json::Value&     json_result);
};
}  // namespace account_endpoints

// Spot Trading Endpoints (Private - Requires API Key + Signature)
namespace spot_trading_endpoints
{
class OrderManagement
{
 public:
  // New Order
  static void NewOrder(std::string_view symbol,
                       std::string_view side,
                       std::string_view type,
                       std::string_view time_in_force,
                       double           quantity,
                       double           quote_order_qty,
                       double           price,
                       std::string_view new_client_order_id,
                       double           stop_price,
                       double           trailing_delta,
                       double           iceberg_qty,
                       std::string_view new_order_resp_type,
                       std::string_view strategy_id,
                       int              strategy_type,
                       long             recv_window,
                       Json::Value&     json_result);

  // Test New Order
  static void TestNewOrder(std::string_view symbol,
                           std::string_view side,
                           std::string_view type,
                           std::string_view time_in_force,
                           double           quantity,
                           double           quote_order_qty,
                           double           price,
                           std::string_view new_client_order_id,
                           double           stop_price,
                           double           trailing_delta,
                           double           iceberg_qty,
                           std::string_view new_order_resp_type,
                           std::string_view strategy_id,
                           int              strategy_type,
                           long             recv_window,
                           Json::Value&     json_result);

  // Query Order
  static void QueryOrder(std::string_view symbol,
                         long             order_id,
                         std::string_view orig_client_order_id,
                         long             recv_window,
                         Json::Value&     json_result);

  // Cancel Order
  static void CancelOrder(std::string_view symbol,
                          long             order_id,
                          std::string_view orig_client_order_id,
                          std::string_view new_client_order_id,
                          std::string_view cancel_restrictions,
                          long             recv_window,
                          Json::Value&     json_result);

  // Cancel Replace Order
  static void CancelReplaceOrder(std::string_view symbol,
                                 std::string_view side,
                                 std::string_view type,
                                 std::string_view cancel_replace_mode,
                                 std::string_view time_in_force,
                                 double           quantity,
                                 double           quote_order_qty,
                                 double           price,
                                 std::string_view cancel_new_client_order_id,
                                 std::string_view cancel_orig_client_order_id,
                                 long             cancel_order_id,
                                 std::string_view new_client_order_id,
                                 double           stop_price,
                                 double           trailing_delta,
                                 double           iceberg_qty,
                                 std::string_view new_order_resp_type,
                                 std::string_view strategy_id,
                                 int              strategy_type,
                                 long             recv_window,
                                 Json::Value&     json_result);

  // Current Open Orders
  static void GetCurrentOpenOrders(std::string_view symbol,
                                   long             recv_window,
                                   Json::Value&     json_result);

  // Cancel All Open Orders
  static void CancelAllOpenOrdersOnSymbol(std::string_view symbol,
                                          long             recv_window,
                                          Json::Value&     json_result);

  // All Orders
  static void GetAllOrders(std::string_view symbol,
                           long             order_id,
                           long             start_time,
                           long             end_time,
                           int              limit,
                           long             recv_window,
                           Json::Value&     json_result);

  // New OCO Order
  static void NewOCOOrder(std::string_view symbol,
                          std::string_view list_client_order_id,
                          std::string_view side,
                          double           quantity,
                          std::string_view limit_client_order_id,
                          double           price,
                          double           limit_iceberg_qty,
                          std::string_view stop_client_order_id,
                          double           stop_price,
                          double           stop_limit_price,
                          double           stop_iceberg_qty,
                          std::string_view stop_limit_time_in_force,
                          std::string_view new_order_resp_type,
                          std::string_view self_trade_prevention_mode,
                          long             recv_window,
                          Json::Value&     json_result);

  // Cancel OCO Order
  static void CancelOCOOrder(std::string_view symbol,
                             long             order_list_id,
                             std::string_view list_client_order_id,
                             std::string_view new_client_order_id,
                             long             recv_window,
                             Json::Value&     json_result);

  // Query OCO Order
  static void QueryOCOOrder(long             order_list_id,
                            std::string_view orig_client_order_id,
                            long             recv_window,
                            Json::Value&     json_result);

  // Query All OCO Orders
  static void QueryAllOCOOrders(long         from_id,
                                long         start_time,
                                long         end_time,
                                int          limit,
                                long         recv_window,
                                Json::Value& json_result);

  // Query Open OCO Orders
  static void QueryOpenOCOOrders(long recv_window, Json::Value& json_result);
};

class SOROrders
{
 public:
  static void NewSOROrder(std::string_view symbol,
                          std::string_view side,
                          std::string_view type,
                          std::string_view time_in_force,
                          double           quantity,
                          double           price,
                          std::string_view new_client_order_id,
                          std::string_view strategy_id,
                          int              strategy_type,
                          double           iceberg_qty,
                          std::string_view new_order_resp_type,
                          std::string_view self_trade_prevention_mode,
                          long             recv_window,
                          Json::Value&     json_result);

  static void TestNewSOROrder(std::string_view symbol,
                              std::string_view side,
                              std::string_view type,
                              std::string_view time_in_force,
                              double           quantity,
                              double           price,
                              std::string_view new_client_order_id,
                              std::string_view strategy_id,
                              int              strategy_type,
                              double           iceberg_qty,
                              std::string_view new_order_resp_type,
                              std::string_view self_trade_prevention_mode,
                              long             recv_window,
                              Json::Value&     json_result);
};
}  // namespace spot_trading_endpoints

// User Data Stream Endpoints (Requires API Key)
namespace user_data_stream_endpoints
{
class UserDataStream
{
 public:
  static void CreateListenKey(Json::Value& json_result);
  static void PingExtendListenKey(std::string_view listen_key);
  static void CloseListenKey(std::string_view listen_key);
};
}  // namespace user_data_stream_endpoints

}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp

#endif  // BINANCE_CPP_SPOT_TRADING_H
