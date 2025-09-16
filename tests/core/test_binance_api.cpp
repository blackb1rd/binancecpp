/*
    Unit test for binance_api.cpp (core)
    Tests the BinanceAPI core functionality
*/

#include <iostream>
#include <string>

#include "../src/binance_api.h"

int main()
{
    std::cout << "=== Testing BinanceAPI Core ===" << std::endl;
    
    // Test 1: Basic initialization
    std::cout << "\n1. Testing Init..." << std::endl;
    try 
    {
        binance_cpp::core::BinanceAPI::Init();
        std::cout << "✅ Init() successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Init() failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 2: Initialization with API keys
    std::cout << "\n2. Testing Init with API keys..." << std::endl;
    try 
    {
        binance_cpp::core::BinanceAPI::Init("test_api_key", "test_secret_key");
        std::cout << "✅ Init(api_key, secret_key) successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Init(api_key, secret_key) failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 3: API key management
    std::cout << "\n3. Testing API key management..." << std::endl;
    try 
    {
        binance_cpp::core::BinanceAPI::SetAPIKey("new_test_api_key");
        const std::string& api_key = binance_cpp::core::BinanceAPI::GetAPIKey();
        
        if (api_key == "new_test_api_key")
        {
            std::cout << "✅ SetAPIKey/GetAPIKey successful" << std::endl;
        }
        else
        {
            std::cout << "❌ SetAPIKey/GetAPIKey failed: " << api_key << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ API key management failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 4: Secret key management
    std::cout << "\n4. Testing Secret key management..." << std::endl;
    try 
    {
        binance_cpp::core::BinanceAPI::SetSecretKey("new_test_secret_key");
        const std::string& secret_key = binance_cpp::core::BinanceAPI::GetSecretKey();
        
        if (secret_key == "new_test_secret_key")
        {
            std::cout << "✅ SetSecretKey/GetSecretKey successful" << std::endl;
        }
        else
        {
            std::cout << "❌ SetSecretKey/GetSecretKey failed: " << secret_key << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Secret key management failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 5: CurlCallback function
    std::cout << "\n5. Testing CurlCallback..." << std::endl;
    try 
    {
        std::string buffer;
        const char* test_data = "test response data";
        size_t result = binance_cpp::core::BinanceAPI::CurlCallback(
            const_cast<char*>(test_data), 1, strlen(test_data), &buffer);
        
        if (result == strlen(test_data) && buffer == test_data)
        {
            std::cout << "✅ CurlCallback successful" << std::endl;
        }
        else
        {
            std::cout << "❌ CurlCallback failed: " << buffer << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ CurlCallback failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 6: Cleanup
    std::cout << "\n6. Testing Cleanup..." << std::endl;
    try 
    {
        binance_cpp::core::BinanceAPI::Cleanup();
        std::cout << "✅ Cleanup() successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Cleanup() failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 7: Re-initialization after cleanup
    std::cout << "\n7. Testing re-initialization after cleanup..." << std::endl;
    try 
    {
        binance_cpp::core::BinanceAPI::Init("test_api", "test_secret");
        std::cout << "✅ Re-initialization successful" << std::endl;
        
        // Final cleanup
        binance_cpp::core::BinanceAPI::Cleanup();
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Re-initialization failed: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== BinanceAPI Core Tests Complete ===" << std::endl;
    return 0;
}