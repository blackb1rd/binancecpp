# Binance C++ API

#### Installation
    git clone https://github.com/blackb1rd/binacpp

#### Dependencies

	jsoncpp
	libcurl
	libwebsockets
	openssl

Dependencies are managed through vcpkg package manager.

#### Prerequisites

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

## TODO - Current Binance API Endpoints

This section lists current Binance API endpoints that could be implemented or updated in the library. Based on [Binance API Documentation](https://developers.binance.com/docs/binance-spot-api-docs/web-socket-api) (as of 2025).

### ✅ Implemented Endpoints

#### General/Market Data Endpoints
- [x] `GET /api/v3/ping` - Test connectivity
- [x] `GET /api/v3/time` - Server time
- [x] `GET /api/v3/exchangeInfo` - Exchange information
- [x] `GET /api/v3/ticker/price` - Symbol price ticker
- [x] `GET /api/v3/ticker/bookTicker` - Symbol order book ticker
- [x] `GET /api/v3/ticker/24hr` - 24hr ticker price change statistics
- [x] `GET /api/v3/depth` - Order book
- [x] `GET /api/v3/aggTrades` - Aggregate trades list
- [x] `GET /api/v3/klines` - Kline/Candlestick data

#### Account Endpoints
- [x] `GET /api/v3/account` - Account information
- [x] `GET /api/v3/myTrades` - Account trade list

#### Trading Endpoints
- [x] `POST /api/v3/order` - New order
- [x] `DELETE /api/v3/order` - Cancel order
- [x] `GET /api/v3/openOrders` - Current open orders
- [x] `GET /api/v3/allOrders` - All orders

#### User Data Stream
- [x] `POST /api/v3/userDataStream` - Start user data stream

### 🚧 TODO - Missing/New Endpoints

#### General/Market Data
- [ ] `GET /api/v3/trades` - Recent trades list
- [ ] `GET /api/v3/historicalTrades` - Old trade lookup
- [ ] `GET /api/v3/avgPrice` - Current average price
- [ ] `GET /api/v3/ticker` - Rolling window price change statistics
- [ ] `GET /api/v3/uiKlines` - UIKlines

#### Account Management
- [ ] `GET /api/v3/rateLimit/order` - Query current order count usage
- [ ] `GET /api/v3/myAllocations` - Query allocations
- [ ] `GET /api/v3/account/commission` - Query commission rates

#### Advanced Trading
- [ ] `POST /api/v3/order/oco` - New OCO order
- [ ] `DELETE /api/v3/orderList` - Cancel OCO order
- [ ] `GET /api/v3/orderList` - Query OCO
- [ ] `GET /api/v3/allOrderList` - Query all OCO
- [ ] `GET /api/v3/openOrderList` - Query open OCO
- [ ] `POST /api/v3/order/cancelReplace` - Cancel and replace order
- [ ] `POST /api/v3/sor/order` - New SOR order

#### Margin Trading
- [ ] `POST /api/v3/margin/transfer` - Cross margin account transfer
- [ ] `POST /api/v3/margin/loan` - Margin account borrow
- [ ] `POST /api/v3/margin/repay` - Margin account repay
- [ ] `GET /api/v3/margin/asset` - Query margin asset
- [ ] `GET /api/v3/margin/pair` - Query cross margin pair
- [ ] `GET /api/v3/margin/allAssets` - Get all margin assets
- [ ] `GET /api/v3/margin/allPairs` - Get all cross margin pairs
- [ ] `GET /api/v3/margin/priceIndex` - Query margin price index
- [ ] `POST /api/v3/margin/order` - Margin account new order
- [ ] `DELETE /api/v3/margin/order` - Margin account cancel order
- [ ] `DELETE /api/v3/margin/openOrders` - Margin account cancel all orders
- [ ] `GET /api/v3/margin/transfer` - Get cross margin transfer history
- [ ] `GET /api/v3/margin/loan` - Query loan record
- [ ] `GET /api/v3/margin/repay` - Query repay record
- [ ] `GET /api/v3/margin/interestHistory` - Get interest history
- [ ] `GET /api/v3/margin/forceLiquidationRec` - Get force liquidation record
- [ ] `GET /api/v3/margin/account` - Query cross margin account details
- [ ] `GET /api/v3/margin/order` - Query margin account's order
- [ ] `GET /api/v3/margin/openOrders` - Query margin account's open orders
- [ ] `GET /api/v3/margin/allOrders` - Query margin account's all orders
- [ ] `GET /api/v3/margin/myTrades` - Query margin account's trade list
- [ ] `GET /api/v3/margin/maxBorrowable` - Query max borrow
- [ ] `GET /api/v3/margin/maxTransferable` - Query max transfer-out amount

#### Futures Trading
- [ ] `POST /api/v3/positionSide/dual` - Change position mode
- [ ] `GET /api/v3/positionSide/dual` - Get current position mode
- [ ] `POST /api/v3/multiAssetsMargin` - Change multi-assets mode
- [ ] `GET /api/v3/multiAssetsMargin` - Get current multi-assets mode

#### Wallet Endpoints
- [ ] `GET /sapi/v1/system/status` - System status
- [ ] `GET /sapi/v1/capital/config/getall` - All coins' information
- [ ] `GET /sapi/v1/accountSnapshot` - Daily account snapshot
- [ ] `POST /sapi/v1/account/disableFastWithdrawSwitch` - Disable fast withdraw
- [ ] `POST /sapi/v1/account/enableFastWithdrawSwitch` - Enable fast withdraw
- [ ] `POST /sapi/v1/capital/withdraw/apply` - Withdraw
- [ ] `GET /sapi/v1/capital/deposit/hisrec` - Deposit history
- [ ] `GET /sapi/v1/capital/withdraw/history` - Withdraw history
- [ ] `GET /sapi/v1/capital/deposit/address` - Deposit address
- [ ] `GET /sapi/v1/account/status` - Account status
- [ ] `GET /sapi/v1/account/apiTradingStatus` - Account API trading status
- [ ] `GET /sapi/v1/asset/dribblet` - DustLog
- [ ] `GET /sapi/v1/asset/dust-btc` - Get assets that can be converted to BNB
- [ ] `POST /sapi/v1/asset/dust` - Dust transfer
- [ ] `GET /sapi/v1/asset/assetDividend` - Asset dividend record
- [ ] `GET /sapi/v1/asset/assetDetail` - Asset detail
- [ ] `GET /sapi/v1/asset/tradeFee` - Trade fee

#### Sub-Account Management
- [ ] `GET /sapi/v1/sub-account/list` - Query sub-account list
- [ ] `GET /sapi/v1/sub-account/transfer/subUserHistory` - Query sub-account transfer history
- [ ] `GET /sapi/v1/sub-account/assets` - Query sub-account assets
- [ ] `POST /sapi/v1/sub-account/virtualSubAccount` - Create a virtual sub-account
- [ ] `GET /sapi/v1/sub-account/virtualSubAccount/list` - Query virtual sub-account list

#### Market Data Streams (WebSocket)
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

#### User Data Streams (WebSocket)
- [ ] User data stream events for margin account
- [ ] User data stream events for isolated margin account
- [ ] User data stream events for futures account

### 🔧 Enhancement TODOs

#### Code Quality & Structure
- [ ] Add comprehensive unit tests for all endpoints
- [ ] Implement async/await patterns for better performance
- [ ] Add request rate limiting and retry logic
- [ ] Implement proper error handling and custom exceptions
- [ ] Add logging levels and configurable log output
- [ ] Create comprehensive API documentation with examples

#### Modern C++ Features
- [ ] Utilize C++20 concepts for parameter validation
- [ ] Implement std::optional for optional parameters
- [ ] Add constexpr where applicable
- [ ] Use std::string_view consistently for string parameters
- [ ] Implement RAII patterns for resource management

#### Performance & Reliability
- [ ] Connection pooling for HTTP requests
- [ ] WebSocket connection auto-reconnection
- [ ] Request/response compression support
- [ ] Memory pool allocation for high-frequency trading
- [ ] Metrics and monitoring integration

#### Developer Experience
- [ ] CMake package config for easy integration
- [ ] Conan package manager support
- [ ] Pre-built packages for major platforms
- [ ] Interactive examples and tutorials
- [ ] VS Code extension with IntelliSense support

---

## Coding with libBinanceCPP

#### Headers to include

	#include "src/binacpp.h"
	#include "src/binance_websocket.h"
	#include <json/json.h>


#### Init
	string api_key 		= API_KEY;
	string secret_key = SECRET_KEY;
	BinanceCPP::init( api_key , secret_key );

---
#### Example : Get Server Time.

	Json::Value result;
	BinanceCPP::get_serverTime( result ) ;

#### Example : Get all Prices

	Json::Value result;
	BinanceCPP::get_allPrices( result );

#### Example: Get price of single pair. Eg: BNBETH

	double bnbeth_price = BinanceCPP::get_price( "BNBETH");

#### Example: Get Account

	Json::Value result;
	long recvWindow = 10000;
	BinanceCPP::get_account( recvWindow , result );

#### Example : Get all bid/ask prices

	Json::Value result;
	BinanceCPP::get_allBookTickers( result );

#### Example: Get bid/ask for single pair

	Json::Value result;
	BinanceCPP::get_bookTicker("bnbeth", result );

#### Example: Get Depth of single pair

	Json::Value result;
	BinanceCPP::get_depth( "ETHBTC", 5, result ) ;


#### Example: Placing a LIMIT order

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::send_order( "BNBETH", "BUY", "LIMIT", "GTC", 20 , 0.00380000, "",0,0, recvWindow, result );

#### Example: Placing a MARKET order

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 20 , 0,   "",0,0, recvWindow, result );

#### Example: Placing an ICEBERG order

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 1 , 0,   "",0,20, recvWindow , result );

#### Example: Check an order's status

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::get_order( "BNBETH", 12345678, "", recvWindow, result );

#### Example: Cancel an order

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::cancel_order("BNBETH", 12345678, "","", recvWindow, result);

#### Example: Getting list of open orders for specific pair

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::get_openOrders( "BNBETH", recvWindow, result ) ;

#### Example: Get all account orders; active, canceled, or filled.

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::get_allOrders( "BNBETH", 0,0, recvWindow, result )

#### Example : Get all trades history

	long recvWindow = 10000;
	Json::Value result;
	BinanceCPP::get_myTrades( "BNBETH", 0,0, recvWindow , result );

#### Example: Getting 24hr ticker price change statistics for a symbol

	Json::Value result;
	BinanceCPP::get_24hr( "ETHBTC", result ) ;

#### Example: Get Kline/candlestick data for a symbol

	Json::Value result;
	BinanceCPP::get_klines( "ETHBTC", "1h", 10 , 0, 0, result );

---

### Websocket Endpoints ###


#### Example: Maintain Market Depth Cache Locally via Web Socket


[example_depthCache.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_depthCache.cpp)

#### Example: KLine/Candlestick Cache and update via Web Socket


[example_klines.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_klines.cpp)

#### Example: Aggregated Trades and update via Web Socket

[example_aggTrades.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_aggTrades.cpp)


#### Example: User stream, Order Execution Status and Balance Update via Web Socket

[example_userStream.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_userStream.cpp)


#### Example: To subscribe multiple streams at the same time, do something like this

	BinanceCPP::start_userDataStream(result );
	string ws_path = string("/ws/");
	ws_path.append( result["listenKey"].asString() );


	BinanceCPP_websocket::init();

 	BinanceCPP_websocket::connect_endpoint( ws_aggTrade_OnData ,"/ws/bnbbtc@aggTrade" );
	BinanceCPP_websocket::connect_endpoint( ws_userStream_OnData , ws_path.c_str() );
	BinanceCPP_websocket::connect_endpoint( ws_klines_onData ,"/ws/bnbbtc@kline_1m" );
	BinanceCPP_websocket::connect_endpoint( ws_depth_onData ,"/ws/bnbbtc@depth" );

	BinanceCPP_websocket::enter_event_loop();

[example.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example.cpp)



