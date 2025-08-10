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

// Note: Function implementations are in separate modular files
// that are compiled separately by CMake and linked together.
// This modular approach allows for easy maintenance and organization.
