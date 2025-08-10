/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Main Implementation File
        Updated for C++20 support

        This file contains static variable definitions and includes all modular
   function files.

        API Categories based on https://developers.binance.com/docs/:

        1. GENERAL MARKET DATA (Public endpoints - no API key required)
           - Exchange information, Server time, Price information
           - Order book data, Trade data, Kline/Candlestick data
           - 24hr ticker statistics

        2. ACCOUNT INFORMATION (Private endpoints - API key + signature
   required)
           - Account information, Trade history

        3. SPOT TRADING (Private endpoints - API key + signature required)
           - Order management (create, query, cancel)
           - Open orders, All orders history

        4. USER DATA STREAM (API key required)
           - Start, maintain, close user data streams

        5. WALLET/WAPI (Private endpoints - API key + signature required)
           - Deposit/withdrawal operations, Deposit addresses
           - Transaction history

        6. UTILITY FUNCTIONS (Internal HTTP/CURL operations)
           - HTTP request handling and responses
*/

#include "binance.h"

#include "binance_logger.h"
#include "binance_utils.h"

// Static member variable definitions
std::string BinanceCPP::api_key = "";
std::string BinanceCPP::secret_key = "";
CURL *BinanceCPP::curl = nullptr;

// Include all modular function implementations
#include "account/get_account.cpp"
#include "account/get_myTrades.cpp"
#include "initialization/cleanup.cpp"
#include "initialization/init.cpp"
#include "market_data/get_24hr.cpp"
#include "market_data/get_aggTrades.cpp"
#include "market_data/get_allBookTickers.cpp"
#include "market_data/get_allPrices.cpp"
#include "market_data/get_bookTicker.cpp"
#include "market_data/get_depth.cpp"
#include "market_data/get_exchangeInfo.cpp"
#include "market_data/get_klines.cpp"
#include "market_data/get_price.cpp"
#include "market_data/get_serverTime.cpp"
#include "trading/cancel_order.cpp"
#include "trading/get_openOrders.cpp"
#include "trading/send_order.cpp"
#include "user_stream/start_userDataStream.cpp"
#include "utils/curl_utils.cpp"

// Note: Additional function files can be added here as they are created
// This modular approach allows for easy maintenance and organization
