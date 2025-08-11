/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Copy Trading Header
        Following Google C++ Style Guide naming conventions
        https://developers.binance.com/docs/copy_trading
*/

#ifndef BINANCE_CPP_COPY_TRADING_H
#define BINANCE_CPP_COPY_TRADING_H

#include <json/json.h>
#include <string_view>

namespace binance_cpp {
namespace financial_trading {
namespace copy_trading {

// Lead Trader Management
namespace lead_trader {
class LeadTraderOperations {
 public:
  static void GetLeadTraderList(std::string_view sort_by, std::string_view sort_order, int page, int size,
                               long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderProfile(std::string_view lead_trader_id, long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderPerformance(std::string_view lead_trader_id, std::string_view period,
                                      long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderPositions(std::string_view lead_trader_id, long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderTradeHistory(std::string_view lead_trader_id, long start_time, long end_time,
                                       int page, int size, long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderRanking(std::string_view period, std::string_view sort_by, std::string_view sort_order,
                                  int page, int size, long recv_window, Json::Value& json_result);
};

class LeadTraderSettings {
 public:
  static void ApplyToBecomeLeadTrader(std::string_view nickname, std::string_view description,
                                     long recv_window, Json::Value& json_result);
  
  static void UpdateLeadTraderProfile(std::string_view nickname, std::string_view description,
                                     std::string_view avatar_url, long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderApplicationStatus(long recv_window, Json::Value& json_result);
  
  static void EnableDisableLeadTrader(bool enable, long recv_window, Json::Value& json_result);
};
}  // namespace lead_trader

// Copy Trading Management
namespace copy_management {
class CopyOperations {
 public:
  static void StartCopyTrading(std::string_view lead_trader_id, double copy_amount, std::string_view copy_mode,
                              double max_copy_amount, double stop_loss_percentage, double take_profit_percentage,
                              long recv_window, Json::Value& json_result);
  
  static void StopCopyTrading(std::string_view copy_id, long recv_window, Json::Value& json_result);
  
  static void UpdateCopySettings(std::string_view copy_id, double copy_amount, std::string_view copy_mode,
                                double max_copy_amount, double stop_loss_percentage, double take_profit_percentage,
                                long recv_window, Json::Value& json_result);
  
  static void GetMyCopyTradingList(int page, int size, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingDetails(std::string_view copy_id, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingPerformance(std::string_view copy_id, std::string_view period,
                                       long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingPositions(std::string_view copy_id, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingHistory(std::string_view copy_id, long start_time, long end_time,
                                   int page, int size, long recv_window, Json::Value& json_result);
};

class CopySettings {
 public:
  static void SetCopyTradingRiskManagement(double max_daily_loss, double max_position_size,
                                          double portfolio_allocation, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingRiskSettings(long recv_window, Json::Value& json_result);
  
  static void SetCopyTradingNotifications(bool trade_notifications, bool performance_notifications,
                                         bool risk_notifications, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingNotificationSettings(long recv_window, Json::Value& json_result);
};
}  // namespace copy_management

// Portfolio Management
namespace portfolio_management {
class PortfolioOperations {
 public:
  static void GetCopyTradingPortfolio(long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingBalance(long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingPnL(std::string_view period, long start_time, long end_time,
                               long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingStatistics(std::string_view period, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingAssetAllocation(long recv_window, Json::Value& json_result);
};

class RiskManagement {
 public:
  static void GetCopyTradingRiskMetrics(long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingDrawdownAnalysis(std::string_view period, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingVolatilityAnalysis(std::string_view period, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingCorrelationAnalysis(std::string_view period, long recv_window, Json::Value& json_result);
};
}  // namespace portfolio_management

// Social Trading Features
namespace social_trading {
class SocialOperations {
 public:
  static void FollowLeadTrader(std::string_view lead_trader_id, long recv_window, Json::Value& json_result);
  
  static void UnfollowLeadTrader(std::string_view lead_trader_id, long recv_window, Json::Value& json_result);
  
  static void GetFollowingList(int page, int size, long recv_window, Json::Value& json_result);
  
  static void GetFollowersList(int page, int size, long recv_window, Json::Value& json_result);
  
  static void RateLeadTrader(std::string_view lead_trader_id, int rating, std::string_view comment,
                            long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderReviews(std::string_view lead_trader_id, int page, int size,
                                  long recv_window, Json::Value& json_result);
  
  static void ReportLeadTrader(std::string_view lead_trader_id, std::string_view reason, std::string_view description,
                              long recv_window, Json::Value& json_result);
};

class CommunityFeatures {
 public:
  static void GetTradingSignals(std::string_view lead_trader_id, int page, int size,
                               long recv_window, Json::Value& json_result);
  
  static void GetMarketSentiment(std::string_view symbol, long recv_window, Json::Value& json_result);
  
  static void GetTradingIdeas(std::string_view category, std::string_view sort_by, int page, int size,
                             long recv_window, Json::Value& json_result);
  
  static void PostTradingIdea(std::string_view title, std::string_view content, std::string_view category,
                             std::string_view symbol, long recv_window, Json::Value& json_result);
  
  static void GetTradingCommunityFeed(int page, int size, long recv_window, Json::Value& json_result);
};
}  // namespace social_trading

// Analytics and Reporting
namespace analytics {
class CopyTradingAnalytics {
 public:
  static void GetCopyTradingAnalytics(std::string_view period, long start_time, long end_time,
                                     long recv_window, Json::Value& json_result);
  
  static void GetLeadTraderComparison(std::string_view lead_trader_ids, std::string_view metrics,
                                     std::string_view period, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingBenchmark(std::string_view benchmark_type, std::string_view period,
                                     long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingAttribution(std::string_view copy_id, std::string_view period,
                                       long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingOptimization(std::string_view optimization_type, long recv_window, Json::Value& json_result);
};

class ReportGeneration {
 public:
  static void GenerateCopyTradingReport(std::string_view report_type, std::string_view period,
                                       long start_time, long end_time, std::string_view format,
                                       long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingReportStatus(std::string_view report_id, long recv_window, Json::Value& json_result);
  
  static void DownloadCopyTradingReport(std::string_view report_id, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingReportHistory(int page, int size, long recv_window, Json::Value& json_result);
};
}  // namespace analytics

// Copy Trading API Management
namespace api_management {
class APIOperations {
 public:
  static void GetCopyTradingAPIStatus(long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingAPILimits(long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingAPIUsage(std::string_view period, long recv_window, Json::Value& json_result);
  
  static void SetCopyTradingAPIPermissions(std::string_view permissions, long recv_window, Json::Value& json_result);
  
  static void GetCopyTradingAPIPermissions(long recv_window, Json::Value& json_result);
};
}  // namespace api_management

}  // namespace copy_trading
}  // namespace financial_trading
}  // namespace binance_cpp

#endif  // BINANCE_CPP_COPY_TRADING_H
