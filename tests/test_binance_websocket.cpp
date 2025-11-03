/*
    Unit test for binance_websocket.cpp
    Tests the BinanceCPP_websocket class functionality
*/

#include <iostream>
#include <string>

#include "binance_websocket.h"

int main()
{
    std::cout << "=== Testing BinanceCPP_websocket ===" << std::endl;
    
    // Test 1: Basic initialization
    std::cout << "\n1. Testing init..." << std::endl;
    try 
    {
        BinanceCPP_websocket::init();
        std::cout << "✅ init() successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ init() failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 2: Constants and basic setup
    std::cout << "\n2. Testing constants..." << std::endl;
    try 
    {
        // Test that constants are defined correctly
        if (BINANCE_WS_HOST == "stream.binance.com")
        {
            std::cout << "✅ BINANCE_WS_HOST correct: " << BINANCE_WS_HOST << std::endl;
        }
        else
        {
            std::cout << "❌ BINANCE_WS_HOST incorrect: " << BINANCE_WS_HOST << std::endl;
            return 1;
        }
        
        if (BINANCE_WS_PORT == 9443)
        {
            std::cout << "✅ BINANCE_WS_PORT correct: " << BINANCE_WS_PORT << std::endl;
        }
        else
        {
            std::cout << "❌ BINANCE_WS_PORT incorrect: " << BINANCE_WS_PORT << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Constants test failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 3: Callback function type
    std::cout << "\n3. Testing callback function type..." << std::endl;
    try 
    {
        // Test that we can create a callback function
        CB test_callback = [](Json::Value &json_value) -> int {
            // Simple test callback
            return 0;
        };
        
        if (test_callback)
        {
            std::cout << "✅ Callback function type creation successful" << std::endl;
        }
        else
        {
            std::cout << "❌ Callback function type creation failed" << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Callback function test failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 4: Test callback execution
    std::cout << "\n4. Testing callback execution..." << std::endl;
    try 
    {
        bool callback_executed = false;
        CB test_callback = [&callback_executed](Json::Value &json_value) -> int {
            callback_executed = true;
            return 0;
        };
        
        Json::Value test_json;
        test_json["test"] = "value";
        int result = test_callback(test_json);
        
        if (callback_executed && result == 0)
        {
            std::cout << "✅ Callback execution successful" << std::endl;
        }
        else
        {
            std::cout << "❌ Callback execution failed" << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Callback execution test failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Note: We avoid testing connect_endpoint and enter_event_loop as they require
    // an actual network connection and would be integration tests rather than unit tests
    
    std::cout << "\n=== BinanceCPP_websocket Tests Complete ===" << std::endl;
    std::cout << "Note: Network-dependent functions (connect_endpoint, enter_event_loop) not tested in unit tests" << std::endl;
    return 0;
}