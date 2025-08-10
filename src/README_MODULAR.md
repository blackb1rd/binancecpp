# BinanceCPP - Modular Structure

## Overview

The BinanceCPP library has been reorganized into a modular structure for better maintainability and clarity. Each function is now in its own file, organized by API category.

## Author Information

- **Current Maintainer**: blackb1rd (2025+)
- **Original Author**: tensaix2j (2017-2018)

## Folder Structure

```
src/
├── binacpp.h                    # Main header file
├── binacpp.cpp                  # Original single-file implementation
├── binance_modular.cpp          # New modular implementation entry point
├── binance_utils.h/.cpp         # Utility functions
├── binance_logger.h/.cpp        # Logging functions
├── binance_websocket.h/.cpp     # WebSocket functionality
├── initialization/              # Library initialization and cleanup
│   ├── init.cpp                 # Library initialization functions
│   └── cleanup.cpp              # Library cleanup functions
├── market_data/                 # Public market data endpoints
│   ├── get_exchangeInfo.cpp     # Exchange trading rules and symbol info
│   ├── get_serverTime.cpp       # Server time synchronization
│   ├── get_allPrices.cpp        # Latest prices for all symbols
│   ├── get_price.cpp            # Single symbol price lookup
│   ├── get_allBookTickers.cpp   # Order book tickers for all symbols
│   ├── get_bookTicker.cpp       # Order book ticker for specific symbol
│   ├── get_depth.cpp            # Market depth (order book)
│   ├── get_aggTrades.cpp        # Aggregated trades
│   ├── get_24hr.cpp             # 24hr ticker statistics
│   └── get_klines.cpp           # Kline/Candlestick data
├── account/                     # Account information endpoints
│   ├── get_account.cpp          # Account information
│   └── get_myTrades.cpp         # Account trade history
├── trading/                     # Spot trading endpoints
│   ├── get_openOrders.cpp       # Open orders
│   ├── send_order.cpp           # Place new order
│   └── cancel_order.cpp         # Cancel existing order
├── user_stream/                 # User data stream endpoints
│   └── start_userDataStream.cpp # Start user data stream
├── wallet/                      # Wallet/WAPI endpoints
│   └── (wallet functions to be added)
└── utils/                       # Internal utilities
    └── curl_utils.cpp           # HTTP/CURL operations
```

## API Categories

### 1. General Market Data (Public endpoints)
- **No API key required**
- Exchange information, server time, price data
- Order book data, trade data, candlestick data
- 24hr ticker statistics

### 2. Account Information (Private endpoints)
- **API key + signature required**
- Account information and trade history

### 3. Spot Trading (Private endpoints)
- **API key + signature required**
- Order management (create, query, cancel)
- Open orders and order history

### 4. User Data Stream (API key required)
- **API key required**
- Real-time user data streams

### 5. Wallet/WAPI (Private endpoints)
- **API key + signature required**
- Deposit/withdrawal operations
- Transaction history and addresses

### 6. Utility Functions
- Internal HTTP/CURL operations
- Helper functions and utilities

## Building

The library supports both the original single-file structure and the new modular structure:

### Traditional Build (Single File)
```bash
cmake --build build/default
```

### Modular Build
```bash
cmake -DUSE_MODULAR_STRUCTURE=ON -B build/modular
cmake --build build/modular
```

## Usage

The API remains the same regardless of which build approach you use. All functions are still called the same way:

```cpp
#include "binacpp.h"

int main() {
    // Initialize library
    BinanceCPP::init("your_api_key", "your_secret_key");

    // Use any function
    Json::Value result;
    BinanceCPP::get_serverTime(result);

    // Cleanup
    BinanceCPP::cleanup();
    return 0;
}
```

## Benefits of Modular Structure

1. **Better Organization**: Functions are grouped by their API category
2. **Easier Maintenance**: Each function is in its own file
3. **Better Documentation**: Each file contains specific endpoint documentation
4. **Incremental Development**: Easy to add new functions without affecting others
5. **Clear Separation**: Public vs private endpoints are clearly separated
6. **Reduced Conflicts**: Multiple developers can work on different endpoints simultaneously

## Migration

No code changes are required when switching between single-file and modular builds. The API interface remains identical.
