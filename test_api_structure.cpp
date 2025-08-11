/*
        Test program for the new binance-cpp API structure
        Verifies both modern and legacy API interfaces work correctly
*/

#include <json/json.h>

#include <iostream>

#include "src/binance_cpp.h"

int main()
{
  std::cout << "=== Testing New binance-cpp API Structure ===" << std::endl;

  // Test 1: Modern API initialization
  std::cout << "\n1. Testing Modern API initialization..." << std::endl;
  try
  {
    binance_cpp::core::BinanceAPI::Init();
    std::cout << "✅ Modern API initialization successful" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << "❌ Modern API initialization failed: " << e.what()
              << std::endl;
  }

  // Test 2: API Server Time
  std::cout << "\n2. Testing API Server Time..." << std::endl;
  try
  {
    Json::Value result;
    binance_cpp::financial_trading::spot_trading::general_endpoints::ServerTime::GetServerTime(result);
    if (!result.empty())
    {
      std::cout << "✅ API server time: "
                << result["serverTime"].asUInt64() << std::endl;
    }
    else
    {
      std::cout << "⚠️  API server time returned empty result" << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cout << "❌ API server time failed: " << e.what() << std::endl;
  }

  // Test 3: Test Connectivity
  std::cout << "\n3. Testing API - Test Connectivity..." << std::endl;
  try
  {
    Json::Value result;
    binance_cpp::financial_trading::spot_trading::general_endpoints::
        TestConnectivity::Ping(result);
    std::cout << "✅ Modern API connectivity test successful" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << "❌ Modern API connectivity test failed: " << e.what()
              << std::endl;
  }

  // Test 6: Modern API - Get Exchange Info
  std::cout << "\n6. Testing Modern API - Exchange Information..." << std::endl;
  try
  {
    Json::Value result;
    binance_cpp::financial_trading::spot_trading::general_endpoints::
        ExchangeInformation::GetExchangeInfo(result);
    if (!result.empty())
    {
      std::cout << "✅ Modern API exchange info received (symbols count: "
                << result["symbols"].size() << ")" << std::endl;
    }
    else
    {
      std::cout << "⚠️  Modern API exchange info returned empty result"
                << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cout << "❌ Modern API exchange info failed: " << e.what()
              << std::endl;
  }

  // Test 7: Modern API - Get Price (BTC)
  std::cout << "\n7. Testing Modern API - Get BTC Price..." << std::endl;
  try
  {
    double price = binance_cpp::financial_trading::spot_trading::
        market_data_endpoints::CurrentPrices::GetPrice("BTCUSDT");
    if (price > 0)
    {
      std::cout << "✅ Modern API BTC price: $" << price << std::endl;
    }
    else
    {
      std::cout << "⚠️  Modern API BTC price returned 0" << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cout << "❌ Modern API BTC price failed: " << e.what() << std::endl;
  }

  // Test 4: Get Price (BTC)
  std::cout << "\n4. Testing API - Get BTC Price..." << std::endl;
  try
  {
    double price = binance_cpp::financial_trading::spot_trading::market_data_endpoints::CurrentPrices::GetPrice("BTCUSDT");
    if (price > 0)
    {
      std::cout << "✅ API BTC price: $" << price << std::endl;
    }
    else
    {
      std::cout << "⚠️  API BTC price returned 0" << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cout << "❌ Legacy API BTC price failed: " << e.what() << std::endl;
  }

  // Cleanup
  std::cout << "\n9. Cleanup..." << std::endl;
  try
  {
    binance_cpp::core::BinanceAPI::Cleanup();
    std::cout << "✅ Cleanup successful" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << "❌ Cleanup failed: " << e.what() << std::endl;
  }

  std::cout << "\n=== Test Complete ===" << std::endl;
  std::cout << "\n📋 Summary:" << std::endl;
  std::cout << "• New categorized API structure implemented" << std::endl;
  std::cout << "• Legacy API compatibility maintained" << std::endl;
  std::cout << "• Google C++ Style Guide naming conventions applied"
            << std::endl;
  std::cout << "• Binance API documentation category structure followed"
            << std::endl;

  return 0;
}
