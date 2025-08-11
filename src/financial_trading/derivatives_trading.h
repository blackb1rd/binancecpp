/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Derivatives Trading Header
        Following Google C++ Style Guide naming conventions
        https://developers.binance.com/docs/derivatives
*/

#ifndef BINANCE_CPP_DERIVATIVES_TRADING_H
#define BINANCE_CPP_DERIVATIVES_TRADING_H

#include <json/json.h>
#include <string_view>

namespace binance_cpp {
namespace financial_trading {
namespace derivatives_trading {

// USD-M Futures Endpoints
namespace usd_m_futures {
namespace market_data {
class ExchangeInformation {
 public:
  static void GetExchangeInformation(Json::Value& json_result);
  static void GetOrderBook(std::string_view symbol, int limit, Json::Value& json_result);
  static void GetRecentTradesList(std::string_view symbol, int limit, Json::Value& json_result);
  static void GetOldTradesLookup(std::string_view symbol, int limit, long from_id, Json::Value& json_result);
  static void GetAggregateTradesList(std::string_view symbol, int from_id, long start_time, 
                                    long end_time, int limit, Json::Value& json_result);
  static void GetKlineCandlestickData(std::string_view symbol, std::string_view interval, 
                                     int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetContinuousContractKlineCandlestickData(std::string_view pair, std::string_view contract_type,
                                                       std::string_view interval, int limit, long start_time, 
                                                       long end_time, Json::Value& json_result);
  static void GetIndexPriceKlineCandlestickData(std::string_view pair, std::string_view interval, 
                                               int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetMarkPriceKlineCandlestickData(std::string_view symbol, std::string_view interval, 
                                              int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetPremiumIndexKlineCandlestickData(std::string_view symbol, std::string_view interval, 
                                                 int limit, long start_time, long end_time, Json::Value& json_result);
  static void Get24hrTickerPriceChangeStatistics(std::string_view symbol, Json::Value& json_result);
  static void GetSymbolPriceTicker(std::string_view symbol, Json::Value& json_result);
  static void GetSymbolOrderBookTicker(std::string_view symbol, Json::Value& json_result);
  static void GetOpenInterest(std::string_view symbol, Json::Value& json_result);
  static void GetOpenInterestStatistics(std::string_view symbol, std::string_view period, 
                                        int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetTopLongShortAccountRatio(std::string_view symbol, std::string_view period, 
                                         int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetTopLongShortPositionRatio(std::string_view symbol, std::string_view period, 
                                          int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetLongShortRatio(std::string_view symbol, std::string_view period, 
                               int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetTakerBuySellVolume(std::string_view symbol, std::string_view period, 
                                   int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetCompositeIndexSymbolInformation(std::string_view symbol, Json::Value& json_result);
  static void GetMultiAssetsMode(Json::Value& json_result);
};

class FundingRate {
 public:
  static void GetFundingRateHistory(std::string_view symbol, long start_time, long end_time, 
                                   int limit, Json::Value& json_result);
  static void GetMarkPrice(std::string_view symbol, Json::Value& json_result);
};
}  // namespace market_data

namespace account_trade {
class PositionInformation {
 public:
  static void ChangePositionMode(bool dual_side_position, long recv_window, Json::Value& json_result);
  static void GetCurrentPositionMode(long recv_window, Json::Value& json_result);
  static void ChangeMultiAssetsMode(bool multi_assets_margin, long recv_window, Json::Value& json_result);
  static void GetCurrentMultiAssetsMode(long recv_window, Json::Value& json_result);
};

class OrderManagement {
 public:
  static void NewOrder(std::string_view symbol, std::string_view side, std::string_view type,
                      std::string_view time_in_force, double quantity, double price,
                      std::string_view new_client_order_id, double stop_price, double close_position,
                      double activation_price, double callback_rate, std::string_view working_type,
                      bool price_protect, std::string_view new_order_resp_type, std::string_view side_effect_type,
                      long recv_window, Json::Value& json_result);
  
  static void PlaceMultipleOrders(const std::vector<Json::Value>& batch_orders, long recv_window, Json::Value& json_result);
  
  static void QueryOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                        long recv_window, Json::Value& json_result);
  
  static void CancelOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                         long recv_window, Json::Value& json_result);
  
  static void CancelAllOpenOrders(std::string_view symbol, long recv_window, Json::Value& json_result);
  
  static void CancelMultipleOrders(std::string_view symbol, const std::vector<long>& order_id_list,
                                  const std::vector<std::string>& orig_client_order_id_list,
                                  long recv_window, Json::Value& json_result);
  
  static void AutoCancelAllOpenOrders(std::string_view symbol, long countdown_time, long recv_window, Json::Value& json_result);
  
  static void QueryCurrentOpenOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                                   long recv_window, Json::Value& json_result);
  
  static void GetCurrentOpenOrders(std::string_view symbol, long recv_window, Json::Value& json_result);
  
  static void GetAllOrders(std::string_view symbol, long order_id, long start_time, long end_time,
                          int limit, long recv_window, Json::Value& json_result);
};

class AccountInformation {
 public:
  static void GetFuturesAccountBalance(long recv_window, Json::Value& json_result);
  static void GetAccountInformation(long recv_window, Json::Value& json_result);
  static void ChangeInitialLeverage(std::string_view symbol, int leverage, long recv_window, Json::Value& json_result);
  static void ChangeMarginType(std::string_view symbol, std::string_view margin_type, long recv_window, Json::Value& json_result);
  static void ModifyIsolatedPositionMargin(std::string_view symbol, std::string_view position_side,
                                          double amount, int type, long recv_window, Json::Value& json_result);
  static void GetPositionMarginChangeHistory(std::string_view symbol, int type, long start_time,
                                            long end_time, int limit, long recv_window, Json::Value& json_result);
  static void GetPositionInformation(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetAccountTradeList(std::string_view symbol, long start_time, long end_time,
                                 long from_id, int limit, long recv_window, Json::Value& json_result);
  static void GetIncomeHistory(std::string_view symbol, std::string_view income_type, long start_time,
                              long end_time, int limit, long recv_window, Json::Value& json_result);
  static void GetLeverageBracket(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetPositionsADLQuantileEstimation(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetUserCommissionRate(std::string_view symbol, long recv_window, Json::Value& json_result);
};
}  // namespace account_trade

namespace user_data_stream {
class UserDataStream {
 public:
  static void StartUserDataStream(Json::Value& json_result);
  static void KeepAliveUserDataStream(std::string_view listen_key, Json::Value& json_result);
  static void CloseUserDataStream(std::string_view listen_key, Json::Value& json_result);
};
}  // namespace user_data_stream
}  // namespace usd_m_futures

// COIN-M Futures Endpoints
namespace coin_m_futures {
namespace market_data {
class ExchangeInformation {
 public:
  static void GetExchangeInformation(Json::Value& json_result);
  static void GetOrderBook(std::string_view symbol, int limit, Json::Value& json_result);
  static void GetRecentTradesList(std::string_view symbol, int limit, Json::Value& json_result);
  static void GetOldTradesLookup(std::string_view symbol, int limit, long from_id, Json::Value& json_result);
  static void GetAggregateTradesList(std::string_view symbol, int from_id, long start_time, 
                                    long end_time, int limit, Json::Value& json_result);
  static void GetIndexPriceKlineCandlestickData(std::string_view pair, std::string_view interval, 
                                               int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetKlineCandlestickData(std::string_view symbol, std::string_view interval, 
                                     int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetContinuousContractKlineCandlestickData(std::string_view pair, std::string_view contract_type,
                                                       std::string_view interval, int limit, long start_time, 
                                                       long end_time, Json::Value& json_result);
  static void Get24hrTickerPriceChangeStatistics(std::string_view symbol, std::string_view pair, Json::Value& json_result);
  static void GetSymbolPriceTicker(std::string_view symbol, std::string_view pair, Json::Value& json_result);
  static void GetSymbolOrderBookTicker(std::string_view symbol, std::string_view pair, Json::Value& json_result);
  static void GetOpenInterest(std::string_view symbol, Json::Value& json_result);
  static void GetOpenInterestStatistics(std::string_view symbol, std::string_view period, 
                                        int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetTopLongShortAccountRatio(std::string_view symbol, std::string_view period, 
                                         int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetTopLongShortPositionRatio(std::string_view symbol, std::string_view period, 
                                          int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetLongShortRatio(std::string_view symbol, std::string_view period, 
                               int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetTakerBuySellVolume(std::string_view symbol, std::string_view period, 
                                   int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetBasisData(std::string_view symbol, std::string_view contract_type, std::string_view period, 
                          int limit, long start_time, long end_time, Json::Value& json_result);
};
}  // namespace market_data

namespace account_trade {
class AccountInformation {
 public:
  static void GetFuturesAccountBalance(long recv_window, Json::Value& json_result);
  static void GetAccountInformation(long recv_window, Json::Value& json_result);
  static void ChangeInitialLeverage(std::string_view symbol, int leverage, long recv_window, Json::Value& json_result);
  static void ChangeMarginType(std::string_view symbol, std::string_view margin_type, long recv_window, Json::Value& json_result);
  static void ModifyIsolatedPositionMargin(std::string_view symbol, double amount, int type, long recv_window, Json::Value& json_result);
  static void GetPositionMarginChangeHistory(std::string_view symbol, int type, long start_time,
                                            long end_time, int limit, long recv_window, Json::Value& json_result);
  static void GetPositionInformation(std::string_view symbol, std::string_view pair, long recv_window, Json::Value& json_result);
  static void GetAccountTradeList(std::string_view symbol, std::string_view pair, long start_time, long end_time,
                                 long from_id, int limit, long recv_window, Json::Value& json_result);
  static void GetIncomeHistory(std::string_view symbol, std::string_view income_type, long start_time,
                              long end_time, int limit, long recv_window, Json::Value& json_result);
  static void GetNotionalAndLeverageBrackets(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetPositionsADLQuantileEstimation(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetUserCommissionRate(std::string_view symbol, long recv_window, Json::Value& json_result);
};

class OrderManagement {
 public:
  static void NewOrder(std::string_view symbol, std::string_view side, std::string_view type,
                      std::string_view time_in_force, double quantity, double price,
                      std::string_view new_client_order_id, double stop_price, double close_position,
                      double activation_price, double callback_rate, std::string_view working_type,
                      bool price_protect, std::string_view new_order_resp_type, long recv_window, Json::Value& json_result);
  
  static void PlaceMultipleOrders(const std::vector<Json::Value>& batch_orders, long recv_window, Json::Value& json_result);
  
  static void QueryOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                        long recv_window, Json::Value& json_result);
  
  static void CancelOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                         long recv_window, Json::Value& json_result);
  
  static void CancelAllOpenOrders(std::string_view symbol, long recv_window, Json::Value& json_result);
  
  static void CancelMultipleOrders(std::string_view symbol, const std::vector<long>& order_id_list,
                                  const std::vector<std::string>& orig_client_order_id_list,
                                  long recv_window, Json::Value& json_result);
  
  static void AutoCancelAllOpenOrders(std::string_view symbol, long countdown_time, long recv_window, Json::Value& json_result);
  
  static void QueryCurrentOpenOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                                   long recv_window, Json::Value& json_result);
  
  static void GetCurrentOpenOrders(std::string_view symbol, std::string_view pair, long recv_window, Json::Value& json_result);
  
  static void GetAllOrders(std::string_view symbol, std::string_view pair, long order_id, long start_time, long end_time,
                          int limit, long recv_window, Json::Value& json_result);
};
}  // namespace account_trade

namespace user_data_stream {
class UserDataStream {
 public:
  static void StartUserDataStream(Json::Value& json_result);
  static void KeepAliveUserDataStream(std::string_view listen_key, Json::Value& json_result);
  static void CloseUserDataStream(std::string_view listen_key, Json::Value& json_result);
};
}  // namespace user_data_stream
}  // namespace coin_m_futures

// Options Endpoints
namespace options {
namespace market_data {
class ExchangeInformation {
 public:
  static void GetExchangeInformation(Json::Value& json_result);
  static void GetOptionInfo(std::string_view symbol, Json::Value& json_result);
  static void GetOrderBook(std::string_view symbol, int limit, Json::Value& json_result);
  static void GetRecentTradesList(std::string_view symbol, int limit, Json::Value& json_result);
  static void GetOldTradesLookup(std::string_view symbol, int limit, long from_id, Json::Value& json_result);
  static void GetKlineCandlestickData(std::string_view symbol, std::string_view interval, 
                                     int limit, long start_time, long end_time, Json::Value& json_result);
  static void GetMarkPrice(std::string_view symbol, Json::Value& json_result);
  static void Get24hrTickerPriceChangeStatistics(std::string_view symbol, Json::Value& json_result);
  static void GetSymbolPriceTicker(std::string_view symbol, Json::Value& json_result);
  static void GetSymbolOrderBookTicker(std::string_view symbol, Json::Value& json_result);
  static void GetOpenInterest(std::string_view underlying_asset, std::string_view expiration, Json::Value& json_result);
};
}  // namespace market_data

namespace account_trade {
class AccountInformation {
 public:
  static void GetOptionAccountInformation(long recv_window, Json::Value& json_result);
  static void GetAccountTradeList(std::string_view symbol, long start_time, long end_time,
                                 long from_id, int limit, long recv_window, Json::Value& json_result);
  static void GetPositionInformation(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetUserCommissionRate(Json::Value& json_result);
};

class OrderManagement {
 public:
  static void NewOrder(std::string_view symbol, std::string_view side, std::string_view type,
                      double quantity, double price, std::string_view time_in_force,
                      double reduce_only, std::string_view post_only, std::string_view new_order_resp_type,
                      std::string_view client_order_id, bool is_isolated, long recv_window, Json::Value& json_result);
  
  static void PlaceMultipleOrders(const std::vector<Json::Value>& batch_orders, long recv_window, Json::Value& json_result);
  
  static void QueryOrder(std::string_view symbol, long order_id, std::string_view client_order_id,
                        long recv_window, Json::Value& json_result);
  
  static void CancelOrder(std::string_view symbol, long order_id, std::string_view client_order_id,
                         long recv_window, Json::Value& json_result);
  
  static void CancelAllOpenOrdersBySymbol(std::string_view symbol, long recv_window, Json::Value& json_result);
  
  static void CancelAllOpenOrdersByUnderlying(std::string_view underlying, long recv_window, Json::Value& json_result);
  
  static void CancelMultipleOrders(const std::vector<Json::Value>& orders_to_cancel, long recv_window, Json::Value& json_result);
  
  static void QueryCurrentOpenOrders(std::string_view symbol, long order_id, long start_time,
                                    long end_time, int limit, long recv_window, Json::Value& json_result);
  
  static void QueryOrderHistory(std::string_view symbol, long order_id, long start_time,
                               long end_time, int limit, long recv_window, Json::Value& json_result);
};
}  // namespace account_trade

namespace user_data_stream {
class UserDataStream {
 public:
  static void StartUserDataStream(Json::Value& json_result);
  static void KeepAliveUserDataStream(std::string_view listen_key, Json::Value& json_result);
  static void CloseUserDataStream(std::string_view listen_key, Json::Value& json_result);
};
}  // namespace user_data_stream
}  // namespace options

}  // namespace derivatives_trading
}  // namespace financial_trading
}  // namespace binance_cpp

#endif  // BINANCE_CPP_DERIVATIVES_TRADING_H
