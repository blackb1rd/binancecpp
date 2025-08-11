/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Wallet Management Header
        Following Google C++ Style Guide naming conventions
        https://developers.binance.com/docs/wallet
*/

#ifndef BINANCE_CPP_WALLET_H
#define BINANCE_CPP_WALLET_H

#include <json/json.h>
#include <string_view>

namespace binance_cpp {
namespace financial_trading {
namespace wallet {

// System Status
namespace system_status {
class SystemInformation {
 public:
  static void GetSystemStatus(Json::Value& json_result);
  static void GetAllCoinsInformation(long recv_window, Json::Value& json_result);
  static void GetDailyAccountSnapshot(std::string_view type, long start_time, long end_time,
                                     int limit, long recv_window, Json::Value& json_result);
  static void DisableFastWithdrawSwitch(long recv_window, Json::Value& json_result);
  static void EnableFastWithdrawSwitch(long recv_window, Json::Value& json_result);
};
}  // namespace system_status

// Deposit Management
namespace deposit {
class DepositOperations {
 public:
  static void GetDepositHistory(std::string_view coin, int status, long start_time, long end_time,
                               int offset, int limit, std::string_view tx_id, long recv_window, Json::Value& json_result);
  
  static void GetDepositAddress(std::string_view coin, std::string_view network, long recv_window, Json::Value& json_result);
  
  static void GetDepositAddressList(std::string_view coin, std::string_view network, long recv_window, Json::Value& json_result);
};
}  // namespace deposit

// Withdrawal Management
namespace withdraw {
class WithdrawOperations {
 public:
  static void Withdraw(std::string_view coin, std::string_view address, double amount,
                      std::string_view address_tag, std::string_view network, std::string_view name,
                      std::string_view wallet_type, long recv_window, Json::Value& json_result);
  
  static void GetWithdrawHistory(std::string_view coin, std::string_view withdraw_order_id, int status,
                                long start_time, long end_time, int offset, int limit,
                                long recv_window, Json::Value& json_result);
};

class WithdrawSettings {
 public:
  static void GetCapitalConfigGetall(long recv_window, Json::Value& json_result);
  static void GetAccountStatus(long recv_window, Json::Value& json_result);
  static void GetAccountAPITradingStatus(long recv_window, Json::Value& json_result);
  static void GetDustLog(std::string_view account_type, long start_time, long end_time,
                        long recv_window, Json::Value& json_result);
  static void GetAssetsThatCanBeConvertedIntoBNB(std::string_view account_type, long recv_window, Json::Value& json_result);
  static void DustTransfer(std::string_view asset, std::string_view account_type, long recv_window, Json::Value& json_result);
  static void GetAssetDividendRecord(std::string_view asset, long start_time, long end_time, int limit,
                                    long recv_window, Json::Value& json_result);
};
}  // namespace withdraw

// Asset Management
namespace asset_management {
class AssetDetails {
 public:
  static void GetAssetDetail(std::string_view asset, long recv_window, Json::Value& json_result);
  static void GetTradeFee(std::string_view symbol, long recv_window, Json::Value& json_result);
  static void GetUserUniversalTransferHistory(std::string_view type, long start_time, long end_time,
                                             int current, int size, std::string_view from_symbol,
                                             std::string_view to_symbol, long recv_window, Json::Value& json_result);
};

class UniversalTransferOperations {
 public:
  static void UniversalTransfer(std::string_view type, std::string_view asset, double amount,
                               std::string_view from_symbol, std::string_view to_symbol,
                               long recv_window, Json::Value& json_result);
};

class FundingWallet {
 public:
  static void GetFundingWallet(std::string_view asset, std::string_view need_btc_valuation,
                              long recv_window, Json::Value& json_result);
  
  static void GetUserAsset(std::string_view asset, std::string_view need_btc_valuation,
                          long recv_window, Json::Value& json_result);
  
  static void GetBUSDConvertHistory(long start_time, long end_time, int current, int size,
                                   long recv_window, Json::Value& json_result);
  
  static void GetCloudMiningPaymentAndRefundHistory(long start_time, long end_time, int current, int size,
                                                   std::string_view asset, long recv_window, Json::Value& json_result);
};
}  // namespace asset_management

// API Key Management
namespace api_management {
class APIKeyInformation {
 public:
  static void GetAPIKeyPermission(long recv_window, Json::Value& json_result);
};
}  // namespace api_management

// Convert Management
namespace convert {
class ConvertOperations {
 public:
  static void GetConvertTradeHistory(long start_time, long end_time, int limit, long recv_window, Json::Value& json_result);
  static void ConvertExchangeInfo(std::string_view from_asset, std::string_view to_asset, Json::Value& json_result);
  static void ConvertAssetInfo(Json::Value& json_result);
  static void SendQuoteRequest(std::string_view from_asset, std::string_view to_asset, double from_amount,
                              double to_amount, std::string_view wallet_type, std::string_view valid_time,
                              long recv_window, Json::Value& json_result);
  static void AcceptQuoteRequest(std::string_view quote_id, long recv_window, Json::Value& json_result);
  static void GetOrderStatus(std::string_view order_id, std::string_view quote_id, long recv_window, Json::Value& json_result);
};
}  // namespace convert

// Sub-Account Management
namespace sub_account {
class SubAccountOperations {
 public:
  static void CreateVirtualSubAccount(std::string_view sub_account_string, long recv_window, Json::Value& json_result);
  static void GetSubAccountList(std::string_view email, bool is_freeze, int page, int limit,
                               long recv_window, Json::Value& json_result);
  static void GetSubAccountSpotAssetTransferHistory(std::string_view from_email, std::string_view to_email,
                                                   long start_time, long end_time, int page, int limit,
                                                   long recv_window, Json::Value& json_result);
  static void GetSubAccountFuturesAssetTransferHistory(std::string_view email, int futures_type, long start_time,
                                                      long end_time, int page, int limit, long recv_window, Json::Value& json_result);
  static void SubAccountFuturesAssetTransfer(std::string_view from_email, std::string_view to_email,
                                            int futures_type, std::string_view asset, double amount,
                                            long recv_window, Json::Value& json_result);
  static void GetSubAccountAssets(std::string_view email, long recv_window, Json::Value& json_result);
  static void GetSubAccountSpotAssetsSummary(std::string_view email, int page, int size,
                                            long recv_window, Json::Value& json_result);
  static void GetSubAccountDepositAddress(std::string_view email, std::string_view coin, std::string_view network,
                                         long recv_window, Json::Value& json_result);
  static void GetSubAccountDepositHistory(std::string_view email, std::string_view coin, int status,
                                         long start_time, long end_time, int offset, int limit,
                                         std::string_view tx_id, long recv_window, Json::Value& json_result);
  static void GetSubAccountStatus(std::string_view email, long recv_window, Json::Value& json_result);
  static void EnableMarginForSubAccount(std::string_view email, long recv_window, Json::Value& json_result);
  static void GetDetailOnSubAccountMarginAccount(std::string_view email, long recv_window, Json::Value& json_result);
  static void GetSummaryOfSubAccountMarginAccount(long recv_window, Json::Value& json_result);
  static void EnableFuturesForSubAccount(std::string_view email, long recv_window, Json::Value& json_result);
  static void GetDetailOnSubAccountFuturesAccount(std::string_view email, long recv_window, Json::Value& json_result);
  static void GetSummaryOfSubAccountFuturesAccount(long recv_window, Json::Value& json_result);
  static void GetFuturesPositionRiskOfSubAccount(std::string_view email, long recv_window, Json::Value& json_result);
  static void SubAccountSpotAssetTransfer(std::string_view from_email, std::string_view to_email,
                                         std::string_view asset, double amount, long recv_window, Json::Value& json_result);
  static void GetSubAccountTransactionStatistics(std::string_view email, long recv_window, Json::Value& json_result);
  static void SubAccountUniversalTransfer(std::string_view from_email, std::string_view to_email,
                                         std::string_view from_account_type, std::string_view to_account_type,
                                         std::string_view client_tran_id, std::string_view asset, double amount,
                                         long recv_window, Json::Value& json_result);
  static void GetUniversalTransferHistory(std::string_view from_email, std::string_view to_email,
                                         std::string_view client_tran_id, long start_time, long end_time,
                                         int page, int limit, long recv_window, Json::Value& json_result);
  static void GetDetailOnSubAccountFuturesAccountV2(std::string_view email, int futures_type,
                                                    long recv_window, Json::Value& json_result);
  static void GetSummaryOfSubAccountFuturesAccountV2(int futures_type, int page, int limit,
                                                     long recv_window, Json::Value& json_result);
  static void GetFuturesPositionRiskOfSubAccountV2(std::string_view email, int futures_type,
                                                   long recv_window, Json::Value& json_result);
  static void EnableLeverageTokenForSubAccount(std::string_view email, bool enable_blvt,
                                              long recv_window, Json::Value& json_result);
  static void GetIPRestrictionForSubAccountAPIKey(std::string_view email, std::string_view sub_account_api_key,
                                                 long recv_window, Json::Value& json_result);
  static void DeleteIPListForSubAccountAPIKey(std::string_view email, std::string_view sub_account_api_key,
                                             std::string_view ip_address, long recv_window, Json::Value& json_result);
  static void UpdateIPRestrictionForSubAccountAPIKey(std::string_view email, std::string_view sub_account_api_key,
                                                    int status, std::string_view ip_address, long recv_window, Json::Value& json_result);
  static void GetSubAccountAPIKeyList(std::string_view email, long recv_window, Json::Value& json_result);
  static void CreateAPIKeyForSubAccount(std::string_view sub_account, bool can_trade, bool margin_trade,
                                       bool futures_trade, long recv_window, Json::Value& json_result);
  static void DeleteSubAccountAPIKey(std::string_view email, std::string_view sub_account_api_key,
                                    long recv_window, Json::Value& json_result);
};
}  // namespace sub_account

}  // namespace wallet
}  // namespace financial_trading
}  // namespace binance_cpp

#endif  // BINANCE_CPP_WALLET_H
