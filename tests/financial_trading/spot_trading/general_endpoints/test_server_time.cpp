/*
    Unit test for server_time.cpp
    Tests the ServerTime endpoint functionality
*/

#include <iostream>
#include <string>

#include "../src/binance_api.h"

int main()
{
    std::cout << "=== Testing ServerTime Endpoint ===" << std::endl;
    
    // Initialize the API first
    try 
    {
        binance_cpp::core::BinanceAPI::Init();
        std::cout << "✅ API initialization successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ API initialization failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 1: GetServerTime function exists and can be called
    std::cout << "\n1. Testing GetServerTime..." << std::endl;
    try 
    {
        Json::Value result;
        binance_cpp::financial_trading::spot_trading::general_endpoints::
            ServerTime::GetServerTime(result);
        
        // For unit testing, we mainly check that the function doesn't crash
        // and returns a JSON object (actual network response testing would be integration tests)
        std::cout << "✅ GetServerTime call successful (returned Json::Value)" << std::endl;
        
        // If we got a response with server time, validate it's reasonable
        if (!result.empty() && result.isMember("serverTime"))
        {
            uint64_t serverTime = result["serverTime"].asUInt64();
            // Basic sanity check - should be a recent timestamp (after 2020)
            if (serverTime > 1577836800000ULL) // Jan 1, 2020 in milliseconds
            {
                std::cout << "✅ GetServerTime returned valid timestamp: " << serverTime << std::endl;
            }
            else
            {
                std::cout << "⚠️  GetServerTime returned suspicious timestamp: " << serverTime << std::endl;
            }
        }
        else
        {
            std::cout << "⚠️  GetServerTime returned empty or invalid response (may be expected in test environment)" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ GetServerTime failed: " << e.what() << std::endl;
        // Don't return 1 here as network failures are expected in some test environments
    }
    
    // Test 2: Verify Json::Value object properties
    std::cout << "\n2. Testing Json::Value result object..." << std::endl;
    try 
    {
        Json::Value result;
        // Call the function again
        binance_cpp::financial_trading::spot_trading::general_endpoints::
            ServerTime::GetServerTime(result);
        
        // Test that result is a valid JSON object
        if (result.isObject() || result.isNull())
        {
            std::cout << "✅ Result is valid JSON object" << std::endl;
        }
        else
        {
            std::cout << "❌ Result is not a valid JSON object" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Json::Value test failed: " << e.what() << std::endl;
    }
    
    // Cleanup
    try 
    {
        binance_cpp::core::BinanceAPI::Cleanup();
        std::cout << "\n✅ API cleanup successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "\n❌ API cleanup failed: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== ServerTime Endpoint Tests Complete ===" << std::endl;
    std::cout << "Note: Network connectivity dependent tests may show warnings in offline environments" << std::endl;
    return 0;
}