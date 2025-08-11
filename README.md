# Binance C++ API

> **Note:** This is a fork project from [binacpp](https://github.com/binance/binacpp).

## ✨ New in 2025: Reorganized API Structure

This library has been completely reorganized to follow the **official Binance API documentation structure** at [developers.binance.com](https://developers.binance.com/en) and implements **Google C++ Style Guide naming conventions**.

### 🏗️ New API Category Structure

The library now follows this hierarchical structure matching Binance's official documentation:

```cpp
binance_cpp::
├── financial_trading::
│   ├── spot_trading::
│   │   ├── general_endpoints::           // Test connectivity, server time, exchange info
│   │   ├── market_data_endpoints::       // Order book, prices, trades, klines
│   │   ├── account_endpoints::           // Account info, trade history
│   │   ├── spot_trading_endpoints::      // Order management, OCO orders
│   │   └── user_data_stream_endpoints::  // WebSocket user data streams
│   └── margin_trading::                  // Cross & isolated margin trading
├── wallet::                              // Deposit, withdraw, account status
├── investment_service::
│   ├── simple_earn::                     // Staking, savings products
│   └── staking::                         // Dedicated staking endpoints
└── core::                                // Core utilities and HTTP client
```

### 📚 Usage Examples

#### Modern API (Recommended)

```cpp
#include "src/binance_cpp.h"

// Initialize
binance_cpp::core::BinanceAPI::Init(api_key, secret_key);

// Get server time
Json::Value result;
binance_cpp::financial_trading::spot_trading::general_endpoints::ServerTime::GetServerTime(result);

// Get account information
binance_cpp::financial_trading::spot_trading::account_endpoints::AccountInformation::GetAccountInformation(10000, result);

// Get current price
double price = binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetPrice("BTCUSDT");
```

#### Legacy API (Backward Compatible)

```cpp
#include "src/binance_legacy.h"

// Old API still works exactly the same
BinanceCPP::init(api_key, secret_key);
BinanceCPP::get_serverTime(result);
BinanceCPP::get_account(10000, result);
double price = BinanceCPP::get_price("BTCUSDT");
```

---

## Installation

```bash
git clone https://github.com/blackb1rd/binance-cpp
```

For installation and deployment instructions, see [INSTALL.md](INSTALL.md).

## Dependencies

```text
jsoncpp
libcurl
libwebsockets
openssl
```

Dependencies are managed through vcpkg package manager.

### Prerequisites

- CMake 3.20 or higher
- vcpkg package manager
- C++20 compatible compiler

#### Building with CMake and vcpkg

1. **Install vcpkg** (if not already installed):
   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   ./bootstrap-vcpkg.sh  # On Windows: .\bootstrap-vcpkg.bat
   ```

2. **Set VCPKG_ROOT environment variable**:
   ```bash
   export VCPKG_ROOT=/path/to/vcpkg  # On Windows: set VCPKG_ROOT=C:\path\to\vcpkg
   ```

3. **Build using CMake presets** (recommended):
   ```bash
   # List available presets
   cmake --list-presets=all

   # Configure and build (Release)
   cmake --preset=release
   cmake --build --preset=release

   # Or Debug build
   cmake --preset=debug
   cmake --build --preset=debug
   ```

4. **Run examples**:
   ```bash
   cd build/release/example  # or build/debug/example
   ./example
   ```

#### Alternative: Manual CMake configuration

If you prefer not to use presets:
```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

#### Alternative: vcpkg integration

You can also integrate vcpkg globally and then simply use:
```bash
vcpkg integrate install
cmake --preset=default  # Will use integrated vcpkg
cmake --build --preset=default
```

#### Code Quality Tools

This project includes code quality tools to maintain consistency and catch potential issues:

**Available Tools:**
- **clang-format**: Code formatting with Google C++ style
- **cpplint**: Google C++ style checker
- **cppcheck**: Static analysis for bugs and style issues

**Usage:**
```bash
# Format all source files
./scripts/format.sh

# Run all quality checks
./scripts/lint.sh

# Manual commands:
clang-format -i src/*.h src/*.cpp example/*.cpp  # Format code
cpplint src/*.h src/*.cpp                         # Style check
cppcheck --enable=all src/ example/               # Static analysis
```

**Installation (Ubuntu/Debian):**
```bash
sudo apt-get install clang-format cppcheck
pip install cpplint
```

**CI Integration:**
All code quality tools run automatically in GitHub Actions CI on every push and pull request.

---

## 🚀 API Endpoints Status & Roadmap

Based on [Binance API Documentation](https://developers.binance.com/en) (Updated 2025).
Following the new categorized structure.

### ✅ FINANCIAL TRADING - SPOT TRADING

#### General Endpoints (Public)

- [x] `GET /api/v3/ping` - Test connectivity to the API
- [x] `GET /api/v3/time` - Check server time
- [x] `GET /api/v3/exchangeInfo` - Exchange trading rules and symbol information
- [ ] `GET /sapi/v1/system/status` - System status (normal or system maintenance)

#### Market Data Endpoints (Public)

- [x] `GET /api/v3/depth` - Order book
- [ ] `GET /api/v3/trades` - Recent trades list
- [ ] `GET /api/v3/historicalTrades` - Old trade lookup (Historical trades)
- [x] `GET /api/v3/aggTrades` - Compressed/Aggregate trades list
- [x] `GET /api/v3/klines` - Kline/Candlestick data
- [ ] `GET /api/v3/uiKlines` - UIKlines data
- [ ] `GET /api/v3/avgPrice` - Current average price for a symbol
- [x] `GET /api/v3/ticker/24hr` - 24hr ticker price change statistics
- [x] `GET /api/v3/ticker/price` - Symbol price ticker
- [x] `GET /api/v3/ticker/bookTicker` - Symbol order book ticker
- [ ] `GET /api/v3/ticker` - Rolling window price change statistics

#### Account Endpoints (Private - API Key + Signature Required)

- [x] `GET /api/v3/account` - Account information
- [x] `GET /api/v3/myTrades` - Account trade list
- [ ] `GET /api/v3/rateLimit/order` - Query current order count usage
- [ ] `GET /api/v3/myPreventedMatches` - Query prevented matches
- [ ] `GET /api/v3/myAllocations` - Query allocations
- [ ] `GET /api/v3/account/commission` - Query commission rates

#### Spot Trading Endpoints (Private - API Key + Signature Required)

**Order Management:**
- [ ] `POST /api/v3/order/test` - Test new order (Test new order creation and signature/recvWindow long. Creates and validates a new order but does not send it into the matching engine)
- [x] `POST /api/v3/order` - New order (OCO)
- [x] `GET /api/v3/order` - Query order
- [x] `DELETE /api/v3/order` - Cancel order
- [ ] `POST /api/v3/order/cancelReplace` - Cancel and replace order
- [x] `GET /api/v3/openOrders` - Current open orders
- [ ] `DELETE /api/v3/openOrders` - Cancel all open orders on a symbol
- [x] `GET /api/v3/allOrders` - All orders

**OCO (One-Cancels-Other) Orders:**
- [ ] `POST /api/v3/order/oco` - New OCO order
- [ ] `DELETE /api/v3/orderList` - Cancel OCO order
- [ ] `GET /api/v3/orderList` - Query OCO order
- [ ] `GET /api/v3/allOrderList` - Query all OCO orders
- [ ] `GET /api/v3/openOrderList` - Query open OCO orders

**SOR (Smart Order Routing):**
- [ ] `POST /api/v3/sor/order` - New SOR order
- [ ] `POST /api/v3/sor/order/test` - Test new SOR order

#### User Data Stream Endpoints (API Key Required)

- [x] `POST /api/v3/userDataStream` - Start a new user data stream
- [ ] `PUT /api/v3/userDataStream` - Keepalive a user data stream
- [ ] `DELETE /api/v3/userDataStream` - Close out a user data stream

### 🔄 FINANCIAL TRADING - MARGIN TRADING

#### Cross Margin Endpoints (Private)

- [ ] `POST /sapi/v1/margin/transfer` - Cross margin account transfer
- [ ] `POST /sapi/v1/margin/loan` - Margin account borrow
- [ ] `POST /sapi/v1/margin/repay` - Margin account repay
- [ ] `GET /sapi/v1/margin/asset` - Query margin asset
- [ ] `GET /sapi/v1/margin/pair` - Query cross margin pair
- [ ] `GET /sapi/v1/margin/allAssets` - Get all margin assets
- [ ] `GET /sapi/v1/margin/allPairs` - Get all cross margin pairs
- [ ] `GET /sapi/v1/margin/priceIndex` - Query margin price index
- [ ] `POST /sapi/v1/margin/order` - Margin account new order
- [ ] `DELETE /sapi/v1/margin/order` - Margin account cancel order
- [ ] `DELETE /sapi/v1/margin/openOrders` - Margin account cancel all orders
- [ ] `GET /sapi/v1/margin/transfer` - Get cross margin transfer history
- [ ] `GET /sapi/v1/margin/loan` - Query loan record
- [ ] `GET /sapi/v1/margin/repay` - Query repay record
- [ ] `GET /sapi/v1/margin/interestHistory` - Get interest history
- [ ] `GET /sapi/v1/margin/forceLiquidationRec` - Get force liquidation record
- [ ] `GET /sapi/v1/margin/account` - Query cross margin account details
- [ ] `GET /sapi/v1/margin/order` - Query margin account's order
- [ ] `GET /sapi/v1/margin/openOrders` - Query margin account's open orders
- [ ] `GET /sapi/v1/margin/allOrders` - Query margin account's all orders
- [ ] `GET /sapi/v1/margin/myTrades` - Query margin account's trade list
- [ ] `GET /sapi/v1/margin/maxBorrowable` - Query max borrow
- [ ] `GET /sapi/v1/margin/maxTransferable` - Query max transfer-out amount

#### Isolated Margin Endpoints (Private)

- [ ] `POST /sapi/v1/margin/isolated/transfer` - Isolated margin account transfer
- [ ] `GET /sapi/v1/margin/isolated/transfer` - Get isolated margin transfer history
- [ ] `GET /sapi/v1/margin/isolated/account` - Query isolated margin account info
- [ ] `DELETE /sapi/v1/margin/isolated/account` - Disable isolated margin account
- [ ] `POST /sapi/v1/margin/isolated/account` - Enable isolated margin account
- [ ] `GET /sapi/v1/margin/isolated/accountLimit` - Query enabled isolated margin account limit
- [ ] `GET /sapi/v1/margin/isolated/pair` - Query isolated margin symbol
- [ ] `GET /sapi/v1/margin/isolated/allPairs` - Get all isolated margin symbols

### 💰 WALLET ENDPOINTS

#### System & Account Status

- [ ] `GET /sapi/v1/system/status` - System status
- [ ] `GET /sapi/v1/capital/config/getall` - All coins' information
- [ ] `GET /sapi/v1/accountSnapshot` - Daily account snapshot
- [ ] `GET /sapi/v1/account/status` - Account status
- [ ] `GET /sapi/v1/account/apiTradingStatus` - Account API trading status

#### Deposit & Withdraw

- [x] `POST /sapi/v1/capital/withdraw/apply` - Withdraw
- [x] `GET /sapi/v1/capital/deposit/hisrec` - Deposit history (supporting network)
- [x] `GET /sapi/v1/capital/withdraw/history` - Withdraw history (supporting network)
- [x] `GET /sapi/v1/capital/deposit/address` - Deposit address (supporting network)
- [ ] `GET /sapi/v1/capital/deposit/address/list` - Fetch deposit address list with network
- [ ] `GET /sapi/v1/capital/deposit/subAddress` - Fetch sub-account deposit address
- [ ] `GET /sapi/v1/capital/deposit/subHisrec` - Fetch sub-account deposit history

#### Fast Withdraw Switch

- [ ] `POST /sapi/v1/account/disableFastWithdrawSwitch` - Disable fast withdraw switch
- [ ] `POST /sapi/v1/account/enableFastWithdrawSwitch` - Enable fast withdraw switch

#### Dust & Asset Management

- [ ] `GET /sapi/v1/asset/dribblet` - DustLog
- [ ] `GET /sapi/v1/asset/dust-btc` - Get assets that can be converted into BNB
- [ ] `POST /sapi/v1/asset/dust` - Dust transfer
- [ ] `GET /sapi/v1/asset/assetDividend` - Asset dividend record
- [ ] `GET /sapi/v1/asset/assetDetail` - Asset detail
- [ ] `GET /sapi/v1/asset/tradeFee` - Trade fee
- [ ] `GET /sapi/v1/asset/get-funding-asset` - Funding wallet
- [ ] `POST /sapi/v1/asset/get-user-asset` - User universal transfer history
- [ ] `GET /sapi/v1/asset/convert-transfer/queryByPage` - Get convert transfer history

### 📈 INVESTMENT & SERVICE

#### Simple Earn

**Flexible Products:**
- [ ] `GET /sapi/v1/simple-earn/flexible/list` - Get simple earn flexible product list
- [ ] `GET /sapi/v1/simple-earn/flexible/leftDailyPurchaseQuota` - Get left daily purchase quota of flexible product
- [ ] `POST /sapi/v1/simple-earn/flexible/purchase` - Purchase flexible product
- [ ] `GET /sapi/v1/simple-earn/flexible/leftDailyRedemptionQuota` - Get left daily redemption quota of flexible product
- [ ] `POST /sapi/v1/simple-earn/flexible/redeem` - Redeem flexible product
- [ ] `GET /sapi/v1/simple-earn/flexible/position` - Get flexible product position
- [ ] `GET /sapi/v1/simple-earn/flexible/history/subscriptionRecord` - Get flexible subscription record
- [ ] `GET /sapi/v1/simple-earn/flexible/history/redemptionRecord` - Get flexible redemption record
- [ ] `GET /sapi/v1/simple-earn/flexible/history/rewardsRecord` - Get flexible rewards history

**Locked Products:**
- [ ] `GET /sapi/v1/simple-earn/locked/list` - Get simple earn locked product list
- [ ] `POST /sapi/v1/simple-earn/locked/purchase` - Purchase locked product
- [ ] `GET /sapi/v1/simple-earn/locked/position` - Get locked product position
- [ ] `GET /sapi/v1/simple-earn/locked/history/subscriptionRecord` - Get locked subscription record
- [ ] `GET /sapi/v1/simple-earn/locked/history/redemptionRecord` - Get locked redemption record
- [ ] `GET /sapi/v1/simple-earn/locked/history/rewardsRecord` - Get locked rewards history
- [ ] `POST /sapi/v1/simple-earn/locked/setAutoSubscribe` - Set locked product redeem option
- [ ] `GET /sapi/v1/simple-earn/account` - Get simple earn account

#### Staking

- [ ] `GET /sapi/v1/staking/productList` - Get staking product list
- [ ] `POST /sapi/v1/staking/purchase` - Purchase staking product
- [ ] `POST /sapi/v1/staking/redeem` - Redeem staking product
- [ ] `GET /sapi/v1/staking/position` - Get staking product position
- [ ] `GET /sapi/v1/staking/stakingRecord` - Get staking history
- [ ] `POST /sapi/v1/staking/setAutoStaking` - Set auto staking
- [ ] `GET /sapi/v1/staking/personalLeftQuota` - Get personal left quota of staking product

#### Dual Investment

- [ ] `GET /sapi/v1/dci/product/list` - Get dual investment product list
- [ ] `POST /sapi/v1/dci/product/subscribe` - Subscribe dual investment product
- [ ] `GET /sapi/v1/dci/product/positions` - Get dual investment product positions
- [ ] `GET /sapi/v1/dci/product/accounts` - Get dual investment product accounts

### 🤖 ALGO TRADING

- [ ] `POST /sapi/v1/algo/spot/newOrderTwap` - New spot TWAP order
- [ ] `DELETE /sapi/v1/algo/spot/order` - Cancel spot algo order
- [ ] `GET /sapi/v1/algo/spot/openOrders` - Get spot open algo orders
- [ ] `GET /sapi/v1/algo/spot/historicalOrders` - Get spot historical algo orders
- [ ] `GET /sapi/v1/algo/spot/subOrders` - Get spot sub algo orders

### 📱 SUB-ACCOUNT MANAGEMENT

#### Sub-Account Information

- [ ] `GET /sapi/v1/sub-account/list` - Query sub-account list
- [ ] `GET /sapi/v1/sub-account/sub/property` - Query sub-account spot assets summary
- [ ] `GET /sapi/v1/sub-account/universalTransfer` - Query sub-account universal transfer history
- [ ] `GET /sapi/v1/sub-account/assets` - Query sub-account assets
- [ ] `POST /sapi/v1/sub-account/virtualSubAccount` - Create a virtual sub-account
- [ ] `GET /sapi/v1/sub-account/virtualSubAccount/list` - Query virtual sub-account list

#### Sub-Account Trading

- [ ] `POST /sapi/v1/sub-account/margin/enable` - Enable margin for sub-account
- [ ] `GET /sapi/v1/sub-account/margin/account` - Get detail on sub-account's margin account
- [ ] `GET /sapi/v1/sub-account/margin/accountSummary` - Get summary of sub-account's margin account
- [ ] `POST /sapi/v1/sub-account/futures/enable` - Enable futures for sub-account
- [ ] `GET /sapi/v1/sub-account/futures/account` - Get detail on sub-account's futures account
- [ ] `GET /sapi/v1/sub-account/futures/accountSummary` - Get summary of sub-account's futures account

### 🌐 WEBSOCKET STREAMS

#### Market Data Streams

- [ ] `<symbol>@trade` - Trade streams
- [ ] `<symbol>@kline_<interval>` - Kline/Candlestick streams
- [ ] `<symbol>@miniTicker` - Individual symbol mini ticker stream
- [ ] `!miniTicker@arr` - All market mini tickers stream
- [ ] `<symbol>@ticker` - Individual symbol ticker streams
- [ ] `!ticker@arr` - All market tickers stream
- [ ] `<symbol>@bookTicker` - Individual symbol book ticker streams
- [ ] `!bookTicker` - All book tickers stream
- [ ] `<symbol>@depth<levels>` - Partial book depth streams
- [ ] `<symbol>@depth` - Diff. depth stream

#### User Data Streams

- [x] User data stream events for spot account
- [ ] User data stream events for margin account
- [ ] User data stream events for isolated margin account

### 🔧 Missing High-Priority Endpoints

#### Core Trading Features

- [ ] `POST /api/v3/order/test` - Test new order creation
- [ ] `POST /api/v3/order/cancelReplace` - Cancel and replace order (atomically)
- [ ] `DELETE /api/v3/openOrders` - Cancel all open orders on a symbol
- [ ] Complete OCO (One-Cancels-Other) order support
- [ ] SOR (Smart Order Routing) order support

#### Account & Risk Management

- [ ] `GET /api/v3/rateLimit/order` - Query current order count usage
- [ ] `GET /api/v3/myPreventedMatches` - Query prevented matches
- [ ] `GET /api/v3/account/commission` - Query commission rates
- [ ] Complete margin trading support (cross & isolated)

#### Essential Wallet Features

- [ ] `GET /sapi/v1/system/status` - System status
- [ ] `GET /sapi/v1/capital/config/getall` - All coins information
- [ ] Complete dust conversion functionality
- [ ] Asset detail and fee queries

---

## 💻 Coding with binance-cpp

### Headers to include

```cpp
// Modern API
#include "src/binance_cpp.h"
#include "src/binance_websocket.h"
#include <json/json.h>

// OR Legacy API (backward compatible)
#include "src/binance_legacy.h"
#include "src/binance_websocket.h"
#include <json/json.h>
```

### Initialization

```cpp
// Modern API
std::string api_key = API_KEY;
std::string secret_key = SECRET_KEY;
binance_cpp::core::BinanceAPI::Init(api_key, secret_key);

// OR Legacy API
BinanceCPP::init(api_key, secret_key);
```

---

### 📊 Market Data Examples

#### Get Server Time

```cpp
// Modern API
Json::Value result;
binance_cpp::financial_trading::spot_trading::general_endpoints::ServerTime::GetServerTime(result);

// Legacy API
Json::Value result;
BinanceCPP::get_serverTime(result);
```

#### Get Exchange Information

```cpp
// Modern API
Json::Value result;
binance_cpp::financial_trading::spot_trading::general_endpoints::ExchangeInformation::GetExchangeInfo(result);

// Legacy API
Json::Value result;
BinanceCPP::get_exchangeInfo(result);
```

#### Get All Prices

```cpp
// Modern API
Json::Value result;
binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetSymbolPriceTicker(result);

// Legacy API
Json::Value result;
BinanceCPP::get_allPrices(result);
```

#### Get Price of Single Pair (e.g., BNBETH)

```cpp
// Modern API
double bnbeth_price = binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetPrice("BNBETH");

// Legacy API
double bnbeth_price = BinanceCPP::get_price("BNBETH");
```

#### Get All Bid/Ask Prices

```cpp
// Modern API
Json::Value result;
binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetSymbolOrderBookTicker(result);

// Legacy API
Json::Value result;
BinanceCPP::get_allBookTickers(result);
```

#### Get Bid/Ask for Single Pair

```cpp
// Modern API
Json::Value result;
binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetSymbolOrderBookTicker("BNBETH", result);

// Legacy API
Json::Value result;
BinanceCPP::get_bookTicker("bnbeth", result);
```

#### Get Order Book Depth

```cpp
// Modern API
Json::Value result;
binance_cpp::financial_trading::spot_trading::market_data_endpoints::OrderBook::GetOrderBook("ETHBTC", 5, result);

// Legacy API
Json::Value result;
BinanceCPP::get_depth("ETHBTC", 5, result);
```

#### Get 24hr Ticker Statistics

```cpp
// Modern API
Json::Value result;
binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::Get24hrTickerPriceChangeStatistics("ETHBTC", result);

// Legacy API
Json::Value result;
BinanceCPP::get_24hr("ETHBTC", result);
```

---

### 👤 Account & Trading Examples

#### Get Account Information

```cpp
// Modern API
Json::Value result;
long recv_window = 10000;
binance_cpp::financial_trading::spot_trading::account_endpoints::AccountInformation::GetAccountInformation(recv_window, result);

// Legacy API
Json::Value result;
long recv_window = 10000;
BinanceCPP::get_account(recv_window, result);
```

#### Get Account Trade List

```cpp
// Modern API
Json::Value result;
long recv_window = 10000;
binance_cpp::financial_trading::spot_trading::account_endpoints::AccountInformation::GetAccountTradeList("BNBETH", 0, 0, recv_window, result);

// Legacy API
Json::Value result;
long recv_window = 10000;
BinanceCPP::get_myTrades("BNBETH", 0, 0, recv_window, result);
```

---

### 🌐 WebSocket Examples

#### Maintain Market Depth Cache via WebSocket

```cpp
BinanceCPP_websocket::init();
BinanceCPP_websocket::connect_endpoint(ws_depth_onData, "/ws/bnbbtc@depth");
BinanceCPP_websocket::enter_event_loop();
```

#### Kline/Candlestick Cache via WebSocket

```cpp
BinanceCPP_websocket::init();
BinanceCPP_websocket::connect_endpoint(ws_klines_onData, "/ws/bnbbtc@kline_1m");
BinanceCPP_websocket::enter_event_loop();
```

#### Aggregated Trades via WebSocket

```cpp
BinanceCPP_websocket::init();
BinanceCPP_websocket::connect_endpoint(ws_aggTrade_OnData, "/ws/bnbbtc@aggTrade");
BinanceCPP_websocket::enter_event_loop();
```

#### User Stream (Order Updates & Balance) via WebSocket

```cpp
Json::Value result;
BinanceCPP::start_userDataStream(result);
std::string ws_path = "/ws/" + result["listenKey"].asString();

BinanceCPP_websocket::init();
BinanceCPP_websocket::connect_endpoint(ws_userStream_OnData, ws_path.c_str());
BinanceCPP_websocket::enter_event_loop();
```

#### Multiple Streams Subscription

```cpp
Json::Value result;
BinanceCPP::start_userDataStream(result);
std::string ws_path = "/ws/" + result["listenKey"].asString();

BinanceCPP_websocket::init();
BinanceCPP_websocket::connect_endpoint(ws_aggTrade_OnData, "/ws/bnbbtc@aggTrade");
BinanceCPP_websocket::connect_endpoint(ws_userStream_OnData, ws_path.c_str());
BinanceCPP_websocket::connect_endpoint(ws_klines_onData, "/ws/bnbbtc@kline_1m");
BinanceCPP_websocket::connect_endpoint(ws_depth_onData, "/ws/bnbbtc@depth");
BinanceCPP_websocket::enter_event_loop();
```

---

### 🔗 Example Files

For more detailed examples, check out these files:

- [**example_depthCache.cpp**](example/example_depthCache.cpp) - Market depth cache via WebSocket
- [**example_klines.cpp**](example/example_klines.cpp) - Kline/Candlestick cache via WebSocket
- [**example_aggTrades.cpp**](example/example_aggTrades.cpp) - Aggregated trades via WebSocket
- [**example_userStream.cpp**](example/example_userStream.cpp) - User stream for order execution & balance updates
- [**example.cpp**](example/example.cpp) - Multiple streams subscription example

---

### 🆕 Migration Guide: Old API → New API

| **Old API (Legacy)**                          | **New API (Modern)**                                                                    |
|-----------------------------------------------|-----------------------------------------------------------------------------------------|
| `BinanceCPP::init()`                          | `binance_cpp::core::BinanceAPI::Init()`                                               |
| `BinanceCPP::get_serverTime()`                | `binance_cpp::financial_trading::spot_trading::general_endpoints::ServerTime::GetServerTime()` |
| `BinanceCPP::get_exchangeInfo()`              | `binance_cpp::financial_trading::spot_trading::general_endpoints::ExchangeInformation::GetExchangeInfo()` |
| `BinanceCPP::get_allPrices()`                 | `binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetSymbolPriceTicker()` |
| `BinanceCPP::get_price()`                     | `binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetPrice()` |
| `BinanceCPP::get_allBookTickers()`            | `binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetSymbolOrderBookTicker()` |
| `BinanceCPP::get_depth()`                     | `binance_cpp::financial_trading::spot_trading::market_data_endpoints::OrderBook::GetOrderBook()` |
| `BinanceCPP::get_account()`                   | `binance_cpp::financial_trading::spot_trading::account_endpoints::AccountInformation::GetAccountInformation()` |
| `BinanceCPP::get_myTrades()`                  | `binance_cpp::financial_trading::spot_trading::account_endpoints::AccountInformation::GetAccountTradeList()` |

**Note:** Legacy API remains fully functional for backward compatibility. You can migrate gradually or continue using the old interface.



