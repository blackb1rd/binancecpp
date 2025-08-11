/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Margin Trading Header
        Following Google C++ Style Guide naming conventions
        https://developers.binance.com/docs/margin_trading
*/

#ifndef BINANCE_CPP_MARGIN_TRADING_H
#define BINANCE_CPP_MARGIN_TRADING_H

#include <json/json.h>
#include <string_view>

namespace binance_cpp {
namespace financial_trading {
namespace margin_trading {

// Cross Margin Endpoints
namespace cross_margin {
class AccountTransfer {
 public:
  static void Transfer(std::string_view asset, double amount, int type, long recv_window, Json::Value& json_result);
  static void GetTransferHistory(std::string_view asset, std::string_view type, long start_time,
                                long end_time, int current, int size, long recv_window, Json::Value& json_result);
};

class AccountBorrow {
 public:
  static void Borrow(std::string_view asset, double amount, std::string_view is_isolated,
                    std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetBorrowHistory(std::string_view asset, std::string_view isolated_symbol,
                              std::string_view tx_id, long start_time, long end_time,
                              int current, int size, bool archived, long recv_window, Json::Value& json_result);
  static void GetLoanRecord(std::string_view asset, std::string_view isolated_symbol,
                           std::string_view tx_id, long start_time, long end_time,
                           int current, int size, bool archived, long recv_window, Json::Value& json_result);
};

class AccountRepay {
 public:
  static void Repay(std::string_view asset, double amount, std::string_view is_isolated,
                   std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetRepayHistory(std::string_view asset, std::string_view isolated_symbol,
                             std::string_view tx_id, long start_time, long end_time,
                             int current, int size, bool archived, long recv_window, Json::Value& json_result);
  static void GetRepayRecord(std::string_view asset, std::string_view isolated_symbol,
                            std::string_view tx_id, long start_time, long end_time,
                            int current, int size, bool archived, long recv_window, Json::Value& json_result);
};

class MarginAsset {
 public:
  static void GetAllMarginAssets(Json::Value& json_result);
  static void GetAllCrossMarginPairs(Json::Value& json_result);
  static void GetMarginAsset(std::string_view asset, Json::Value& json_result);
  static void GetCrossMarginPair(std::string_view symbol, Json::Value& json_result);
  static void GetPriceIndex(std::string_view symbol, Json::Value& json_result);
};

class OrderManagement {
 public:
  static void NewMarginOrder(std::string_view symbol, std::string_view side, std::string_view type,
                            std::string_view time_in_force, double quantity, double quote_order_qty,
                            double price, double stop_price, std::string_view new_client_order_id,
                            double iceberg_qty, std::string_view new_order_resp_type,
                            std::string_view side_effect_type, std::string_view auto_repay_at_cancel,
                            std::string_view self_trade_prevention_mode, long recv_window, Json::Value& json_result);
  
  static void CancelMarginOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                               std::string_view new_client_order_id, std::string_view is_isolated,
                               long recv_window, Json::Value& json_result);
  
  static void CancelAllMarginOpenOrders(std::string_view symbol, std::string_view is_isolated,
                                       long recv_window, Json::Value& json_result);
  
  static void GetCrossMarginTransferHistory(std::string_view asset, std::string_view type, long start_time,
                                           long end_time, int current, int size, long recv_window, Json::Value& json_result);
  
  static void GetInterestHistory(std::string_view asset, std::string_view isolated_symbol, long start_time,
                                long end_time, int current, int size, bool archived, long recv_window, Json::Value& json_result);
  
  static void GetForceLiquidationRecord(long start_time, long end_time, std::string_view isolated_symbol,
                                       int current, int size, long recv_window, Json::Value& json_result);
  
  static void GetCrossMarginAccountDetails(long recv_window, Json::Value& json_result);
  
  static void GetMarginAccountOrder(std::string_view symbol, long order_id, std::string_view orig_client_order_id,
                                   std::string_view is_isolated, long recv_window, Json::Value& json_result);
  
  static void GetMarginAccountOpenOrders(std::string_view symbol, std::string_view is_isolated,
                                        long recv_window, Json::Value& json_result);
  
  static void GetMarginAccountAllOrders(std::string_view symbol, std::string_view is_isolated, long order_id,
                                       long start_time, long end_time, int limit, long recv_window, Json::Value& json_result);
  
  static void GetMarginAccountTradeList(std::string_view symbol, std::string_view is_isolated, long order_id,
                                       long start_time, long end_time, long from_id, int limit,
                                       long recv_window, Json::Value& json_result);
  
  static void GetMaxBorrow(std::string_view asset, std::string_view isolated_symbol, long recv_window, Json::Value& json_result);
  
  static void GetMaxTransferOutAmount(std::string_view asset, std::string_view isolated_symbol, long recv_window, Json::Value& json_result);
};

class MarginLevel {
 public:
  static void GetMarginLevelInformation(Json::Value& json_result);
  static void GetCrossMarginFeeData(std::string_view vip_level, std::string_view coin, long recv_window, Json::Value& json_result);
  static void GetIsolatedMarginFeeData(std::string_view vip_level, std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetIsolatedMarginTierData(std::string_view symbol, std::string_view tier, long recv_window, Json::Value& json_result);
  static void GetCurrentMarginOrderCountUsage(std::string_view is_isolated, std::string_view symbol, long recv_window, Json::Value& json_result);
};

class DustLog {
 public:
  static void GetCrossMarginDustLog(long start_time, long end_time, long recv_window, Json::Value& json_result);
};

class BNBBurn {
 public:
  static void GetBNBBurnStatus(long recv_window, Json::Value& json_result);
  static void ToggleBNBBurnOnSpotTradeAndMarginInterest(std::string_view spot_bnb_burn, std::string_view interest_bnb_burn,
                                                        long recv_window, Json::Value& json_result);
};

class MarginInterestRateHistory {
 public:
  static void GetMarginInterestRateHistory(std::string_view asset, std::string_view vip_level, long start_time,
                                          long end_time, int limit, long recv_window, Json::Value& json_result);
};
}  // namespace cross_margin

// Isolated Margin Endpoints
namespace isolated_margin {
class AccountTransfer {
 public:
  static void Transfer(std::string_view asset, std::string_view symbol, std::string_view trans_from,
                      std::string_view trans_to, double amount, long recv_window, Json::Value& json_result);
  static void GetTransferHistory(std::string_view symbol, std::string_view asset, std::string_view trans_from,
                                std::string_view trans_to, long start_time, long end_time, int current,
                                int size, long recv_window, Json::Value& json_result);
};

class AccountInformation {
 public:
  static void GetIsolatedMarginAccountInfo(std::string_view symbols, long recv_window, Json::Value& json_result);
  static void DisableIsolatedMarginAccount(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void EnableIsolatedMarginAccount(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetEnabledIsolatedMarginAccountLimit(long recv_window, Json::Value& json_result);
};

class MarginData {
 public:
  static void GetIsolatedMarginSymbol(std::string_view symbol, Json::Value& json_result);
  static void GetAllIsolatedMarginSymbols(Json::Value& json_result);
};
}  // namespace isolated_margin

// Portfolio Margin Endpoints
namespace portfolio_margin {
class AccountInformation {
 public:
  static void GetPortfolioMarginAccountInfo(long recv_window, Json::Value& json_result);
  static void GetPortfolioMarginCollateralRate(Json::Value& json_result);
  static void GetPortfolioMarginBankruptcyLoanAmount(long recv_window, Json::Value& json_result);
  static void PortfolioMarginBankruptcyLoanRepay(long recv_window, Json::Value& json_result);
};
}  // namespace portfolio_margin

}  // namespace margin_trading
}  // namespace financial_trading
}  // namespace binance_cpp

#endif  // BINANCE_CPP_MARGIN_TRADING_H
