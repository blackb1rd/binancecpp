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
- C++14 compatible compiler

#### Building with CMake and vcpkg

1. **Install vcpkg** (if not already installed):
   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   ./bootstrap-vcpkg.sh  # On Windows: .\bootstrap-vcpkg.bat
   ```

2. **Configure CMake with vcpkg**:
   ```bash
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
   ```

3. **Build the project**:
   ```bash
   cmake --build build
   ```

4. **Run examples**:
   ```bash
   cd build/example
   export SSL_CERT_FILE=./cacert.pem
   ./example
   ```

#### Alternative: vcpkg integration

You can also integrate vcpkg globally and then simply use:
```bash
vcpkg integrate install
cmake -B build -S .
cmake --build build
```

---
## Coding with libBinaCPP

#### Headers to include

	#include "binacpp.h"	
	#include "binacpp_websocket.h"
	#include <json/json.h>


#### Init
	string api_key 		= API_KEY;
	string secret_key = SECRET_KEY;
	BinaCPP::init( api_key , secret_key );

---
#### Example : Get Server Time.
	
	Json::Value result;
	BinaCPP::get_serverTime( result ) ;

#### Example : Get all Prices

	Json::Value result;
	BinaCPP::get_allPrices( result );

#### Example: Get price of single pair. Eg: BNBETH

	double bnbeth_price = BinaCPP::get_price( "BNBETH");

#### Example: Get Account 
	
	Json::Value result;
	long recvWindow = 10000;	
	BinaCPP::get_account( recvWindow , result );

#### Example : Get all bid/ask prices
	
	Json::Value result;
	BinaCPP::get_allBookTickers( result );

#### Example: Get bid/ask for single pair
	
	Json::Value result;
	BinaCPP::get_bookTicker("bnbeth", result );
	
#### Example: Get Depth of single pair
	
	Json::Value result;
	BinaCPP::get_depth( "ETHBTC", 5, result ) ;
	

#### Example: Placing a LIMIT order
	
	long recvWindow = 10000;	
	Json::Value result;
	BinaCPP::send_order( "BNBETH", "BUY", "LIMIT", "GTC", 20 , 0.00380000, "",0,0, recvWindow, result );

#### Example: Placing a MARKET order

	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 20 , 0,   "",0,0, recvWindow, result );

#### Example: Placing an ICEBERG order
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 1 , 0,   "",0,20, recvWindow , result );

#### Example: Check an order's status

	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_order( "BNBETH", 12345678, "", recvWindow, result );

#### Example: Cancel an order

	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::cancel_order("BNBETH", 12345678, "","", recvWindow, result);

#### Example: Getting list of open orders for specific pair
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_openOrders( "BNBETH", recvWindow, result ) ;

#### Example: Get all account orders; active, canceled, or filled.
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_allOrders( "BNBETH", 0,0, recvWindow, result ) 

#### Example : Get all trades history
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_myTrades( "BNBETH", 0,0, recvWindow , result );

#### Example: Getting 24hr ticker price change statistics for a symbol
	
	Json::Value result;
	BinaCPP::get_24hr( "ETHBTC", result ) ;

#### Example: Get Kline/candlestick data for a symbol
	
	Json::Value result;
	BinaCPP::get_klines( "ETHBTC", "1h", 10 , 0, 0, result );

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

	BinaCPP::start_userDataStream(result );
	string ws_path = string("/ws/");
	ws_path.append( result["listenKey"].asString() );


	BinaCPP_websocket::init();
 	
 	BinaCPP_websocket::connect_endpoint( ws_aggTrade_OnData ,"/ws/bnbbtc@aggTrade" ); 
	BinaCPP_websocket::connect_endpoint( ws_userStream_OnData , ws_path.c_str() ); 
	BinaCPP_websocket::connect_endpoint( ws_klines_onData ,"/ws/bnbbtc@kline_1m" ); 
	BinaCPP_websocket::connect_endpoint( ws_depth_onData ,"/ws/bnbbtc@depth" ); 
 		
	BinaCPP_websocket::enter_event_loop(); 

[example.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example.cpp)

	

