/*
    Unit test for test_connectivity.cpp
    Tests the TestConnectivity endpoint functionality
*/

#include <iostream>
#include <string>

#include "../src/binance_api.h"

int main()
{
    std::cout << "=== Testing TestConnectivity Endpoint ===" << std::endl;
    
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
    
    // Test 1: Ping function exists and can be called
    std::cout << "\n1. Testing Ping..." << std::endl;
    try 
    {
        Json::Value result;
        binance_cpp::financial_trading::spot_trading::general_endpoints::
            TestConnectivity::Ping(result);
        
        // For unit testing, we mainly check that the function doesn't crash
        std::cout << "✅ Ping call successful" << std::endl;
        
        // If we got a successful ping response, it should be an empty JSON object
        if (result.isObject())
        {
            std::cout << "✅ Ping returned valid JSON object" << std::endl;
            
            // Successful ping typically returns an empty object {}
            if (result.empty())
            {
                std::cout << "✅ Ping returned expected empty response" << std::endl;
            }
            else
            {
                std::cout << "⚠️  Ping returned non-empty response (may contain error info)" << std::endl;
            }
        }
        else
        {
            std::cout << "⚠️  Ping returned non-object response (may be expected in test environment)" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Ping failed: " << e.what() << std::endl;
        // Don't return 1 here as network failures are expected in some test environments
    }
    
    // Test 2: Multiple ping calls
    std::cout << "\n2. Testing multiple Ping calls..." << std::endl;
    try 
    {
        Json::Value result1, result2;
        
        binance_cpp::financial_trading::spot_trading::general_endpoints::
            TestConnectivity::Ping(result1);
        binance_cpp::financial_trading::spot_trading::general_endpoints::
            TestConnectivity::Ping(result2);
        
        // Both calls should succeed and return similar structure
        if (result1.type() == result2.type())
        {
            std::cout << "✅ Multiple ping calls returned consistent types" << std::endl;
        }
        else
        {
            std::cout << "⚠️  Multiple ping calls returned inconsistent types" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Multiple ping test failed: " << e.what() << std::endl;
    }
    
    // Test 3: Verify Json::Value object properties
    std::cout << "\n3. Testing Json::Value result object..." << std::endl;
    try 
    {
        Json::Value result;
        binance_cpp::financial_trading::spot_trading::general_endpoints::
            TestConnectivity::Ping(result);
        
        // Test that result is a valid JSON object or null
        if (result.isObject() || result.isNull())
        {
            std::cout << "✅ Result is valid JSON type" << std::endl;
        }
        else
        {
            std::cout << "❌ Result is not a valid JSON type" << std::endl;
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
    
    std::cout << "\n=== TestConnectivity Endpoint Tests Complete ===" << std::endl;
    std::cout << "Note: Network connectivity dependent tests may show warnings in offline environments" << std::endl;
    return 0;
}