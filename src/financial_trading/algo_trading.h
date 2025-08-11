/*
        Author: blackb1rd
        Date  : 2025/08/11

        C++ library for Binance API - Algo Trading Header
        Following Google C++ Style Guide naming conventions
        https://developers.binance.com/docs/algo_trading
*/

#ifndef BINANCE_CPP_ALGO_TRADING_H
#define BINANCE_CPP_ALGO_TRADING_H

#include <json/json.h>

#include <string_view>

namespace binance_cpp
{
namespace financial_trading
{
namespace algo_trading
{

// TWAP (Time Weighted Average Price) Orders
namespace twap_orders
{
class OrderManagement
{
 public:
  static void PlaceTWAPOrder(std::string_view symbol,
                             std::string_view side,
                             double           quantity,
                             std::string_view duration,
                             std::string_view client_algo_id,
                             std::string_view limit_price,
                             long             recv_window,
                             Json::Value&     json_result);

  static void CancelTWAPOrder(long             algo_id,
                              std::string_view client_algo_id,
                              long             recv_window,
                              Json::Value&     json_result);

  static void GetTWAPOrder(long             algo_id,
                           std::string_view client_algo_id,
                           long             recv_window,
                           Json::Value&     json_result);

  static void GetHistoricalTWAPOrders(std::string_view symbol,
                                      std::string_view side,
                                      long             start_time,
                                      long             end_time,
                                      int              page,
                                      int              size,
                                      long             recv_window,
                                      Json::Value&     json_result);

  static void GetTWAPSubOrders(long         algo_id,
                               int          page,
                               int          size,
                               long         recv_window,
                               Json::Value& json_result);
};
}  // namespace twap_orders

// VP (Volume Participation) Orders
namespace vp_orders
{
class OrderManagement
{
 public:
  static void PlaceVPOrder(std::string_view symbol,
                           std::string_view side,
                           double           quantity,
                           std::string_view urgency,
                           std::string_view client_algo_id,
                           std::string_view limit_price,
                           long             recv_window,
                           Json::Value&     json_result);

  static void CancelVPOrder(long             algo_id,
                            std::string_view client_algo_id,
                            long             recv_window,
                            Json::Value&     json_result);

  static void GetVPOrder(long             algo_id,
                         std::string_view client_algo_id,
                         long             recv_window,
                         Json::Value&     json_result);

  static void GetHistoricalVPOrders(std::string_view symbol,
                                    std::string_view side,
                                    long             start_time,
                                    long             end_time,
                                    int              page,
                                    int              size,
                                    long             recv_window,
                                    Json::Value&     json_result);

  static void GetVPSubOrders(long         algo_id,
                             int          page,
                             int          size,
                             long         recv_window,
                             Json::Value& json_result);
};
}  // namespace vp_orders

// Algorithmic Trading Strategies
namespace strategies
{
class GridTrading
{
 public:
  static void PlaceGridOrder(std::string_view symbol,
                             std::string_view side,
                             double           base_quantity,
                             double           upper_price,
                             double           lower_price,
                             int              grid_count,
                             std::string_view client_algo_id,
                             long             recv_window,
                             Json::Value&     json_result);

  static void CancelGridOrder(long             algo_id,
                              std::string_view client_algo_id,
                              long             recv_window,
                              Json::Value&     json_result);

  static void GetGridOrder(long             algo_id,
                           std::string_view client_algo_id,
                           long             recv_window,
                           Json::Value&     json_result);

  static void GetHistoricalGridOrders(std::string_view symbol,
                                      std::string_view side,
                                      long             start_time,
                                      long             end_time,
                                      int              page,
                                      int              size,
                                      long             recv_window,
                                      Json::Value&     json_result);

  static void GetGridSubOrders(long         algo_id,
                               int          page,
                               int          size,
                               long         recv_window,
                               Json::Value& json_result);
};

class IcebergOrders
{
 public:
  static void PlaceIcebergOrder(std::string_view symbol,
                                std::string_view side,
                                double           quantity,
                                double           iceberg_qty,
                                double           price,
                                std::string_view time_in_force,
                                std::string_view client_order_id,
                                long             recv_window,
                                Json::Value&     json_result);
};

class StopLossOrders
{
 public:
  static void PlaceStopLossOrder(std::string_view symbol,
                                 std::string_view side,
                                 double           quantity,
                                 double           stop_price,
                                 double           price,
                                 std::string_view time_in_force,
                                 std::string_view client_order_id,
                                 long             recv_window,
                                 Json::Value&     json_result);
};

class TakeProfitOrders
{
 public:
  static void PlaceTakeProfitOrder(std::string_view symbol,
                                   std::string_view side,
                                   double           quantity,
                                   double           stop_price,
                                   double           price,
                                   std::string_view time_in_force,
                                   std::string_view client_order_id,
                                   long             recv_window,
                                   Json::Value&     json_result);
};

class TrailingStopOrders
{
 public:
  static void PlaceTrailingStopOrder(std::string_view symbol,
                                     std::string_view side,
                                     double           quantity,
                                     double           callback_rate,
                                     std::string_view client_order_id,
                                     long             recv_window,
                                     Json::Value&     json_result);
};
}  // namespace strategies

// Portfolio Optimization
namespace portfolio_optimization
{
class AssetAllocation
{
 public:
  static void GetOptimalAllocation(std::string_view assets,
                                   std::string_view risk_tolerance,
                                   std::string_view investment_horizon,
                                   long             recv_window,
                                   Json::Value&     json_result);

  static void RebalancePortfolio(std::string_view target_allocation,
                                 std::string_view client_id,
                                 long             recv_window,
                                 Json::Value&     json_result);

  static void GetRebalancingHistory(long         start_time,
                                    long         end_time,
                                    int          page,
                                    int          size,
                                    long         recv_window,
                                    Json::Value& json_result);
};

class RiskManagement
{
 public:
  static void SetRiskLimits(std::string_view symbol,
                            double           max_position_size,
                            double           max_drawdown,
                            double           stop_loss_percentage,
                            long             recv_window,
                            Json::Value&     json_result);

  static void GetRiskMetrics(std::string_view symbol,
                             long             start_time,
                             long             end_time,
                             long             recv_window,
                             Json::Value&     json_result);

  static void GetPortfolioRisk(long recv_window, Json::Value& json_result);
};
}  // namespace portfolio_optimization

// Advanced Order Types
namespace advanced_orders
{
class ConditionalOrders
{
 public:
  static void PlaceConditionalOrder(std::string_view symbol,
                                    std::string_view side,
                                    double           quantity,
                                    std::string_view condition_type,
                                    std::string_view condition_value,
                                    std::string_view operator_type,
                                    double           price,
                                    std::string_view client_order_id,
                                    long             recv_window,
                                    Json::Value&     json_result);

  static void CancelConditionalOrder(long             order_id,
                                     std::string_view client_order_id,
                                     long             recv_window,
                                     Json::Value&     json_result);

  static void GetConditionalOrder(long             order_id,
                                  std::string_view client_order_id,
                                  long             recv_window,
                                  Json::Value&     json_result);

  static void GetHistoricalConditionalOrders(std::string_view symbol,
                                             std::string_view side,
                                             long             start_time,
                                             long             end_time,
                                             int              page,
                                             int              size,
                                             long             recv_window,
                                             Json::Value&     json_result);
};

class BracketOrders
{
 public:
  static void PlaceBracketOrder(std::string_view symbol,
                                std::string_view side,
                                double           quantity,
                                double           entry_price,
                                double           stop_loss_price,
                                double           take_profit_price,
                                std::string_view client_order_id,
                                long             recv_window,
                                Json::Value&     json_result);

  static void CancelBracketOrder(long             order_id,
                                 std::string_view client_order_id,
                                 long             recv_window,
                                 Json::Value&     json_result);

  static void GetBracketOrder(long             order_id,
                              std::string_view client_order_id,
                              long             recv_window,
                              Json::Value&     json_result);
};

class OCOOrders
{
 public:
  static void PlaceOCOOrder(std::string_view symbol,
                            std::string_view side,
                            double           quantity,
                            double           price,
                            double           stop_price,
                            double           stop_limit_price,
                            std::string_view stop_limit_time_in_force,
                            std::string_view new_client_order_id,
                            std::string_view list_client_order_id,
                            long             recv_window,
                            Json::Value&     json_result);

  static void CancelOCOOrder(std::string_view symbol,
                             long             order_list_id,
                             std::string_view list_client_order_id,
                             std::string_view new_client_order_id,
                             long             recv_window,
                             Json::Value&     json_result);

  static void GetOCOOrder(long             order_list_id,
                          std::string_view orig_client_order_id,
                          long             recv_window,
                          Json::Value&     json_result);

  static void GetAllOCOOrders(long         from_id,
                              long         start_time,
                              long         end_time,
                              int          limit,
                              long         recv_window,
                              Json::Value& json_result);

  static void GetOpenOCOOrders(long recv_window, Json::Value& json_result);
};
}  // namespace advanced_orders

// Algorithmic Trading Analytics
namespace analytics
{
class PerformanceMetrics
{
 public:
  static void GetAlgoOrderPerformance(long             algo_id,
                                      std::string_view client_algo_id,
                                      long             recv_window,
                                      Json::Value&     json_result);

  static void GetStrategyPerformance(std::string_view strategy_type,
                                     long             start_time,
                                     long             end_time,
                                     long             recv_window,
                                     Json::Value&     json_result);

  static void GetExecutionQuality(long             start_time,
                                  long             end_time,
                                  std::string_view symbol,
                                  long             recv_window,
                                  Json::Value&     json_result);

  static void GetSlippageAnalysis(long             start_time,
                                  long             end_time,
                                  std::string_view symbol,
                                  long             recv_window,
                                  Json::Value&     json_result);
};

class MarketImpactAnalysis
{
 public:
  static void GetMarketImpact(long             start_time,
                              long             end_time,
                              std::string_view symbol,
                              long             recv_window,
                              Json::Value&     json_result);

  static void GetOptimalExecutionAnalysis(std::string_view symbol,
                                          double           quantity,
                                          std::string_view side,
                                          std::string_view urgency,
                                          long             recv_window,
                                          Json::Value&     json_result);
};
}  // namespace analytics

}  // namespace algo_trading
}  // namespace financial_trading
}  // namespace binance_cpp

#endif  // BINANCE_CPP_ALGO_TRADING_H
