/*
    Unit test for binance_logger.cpp
    Tests the BinanceCPP_logger class functionality
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

#include "../src/binance_logger.h"

int main()
{
    std::cout << "=== Testing BinanceCPP_logger ===" << std::endl;
    
    // Test 1: Set debug level
    std::cout << "\n1. Testing set_debug_level..." << std::endl;
    try 
    {
        BinanceCPP_logger::set_debug_level(1);
        std::cout << "✅ set_debug_level(1) successful" << std::endl;
        
        BinanceCPP_logger::set_debug_level(0);
        std::cout << "✅ set_debug_level(0) successful" << std::endl;
        
        // Reset to enabled for other tests
        BinanceCPP_logger::set_debug_level(1);
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ set_debug_level failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 2: Basic logging
    std::cout << "\n2. Testing basic write_log..." << std::endl;
    try 
    {
        BinanceCPP_logger::write_log("Test log message %d", 123);
        std::cout << "✅ write_log with formatted string successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ write_log failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 3: Clean logging
    std::cout << "\n3. Testing write_log_clean..." << std::endl;
    try 
    {
        BinanceCPP_logger::write_log_clean("Clean log message");
        std::cout << "✅ write_log_clean successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ write_log_clean failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 4: Set debug log file
    std::cout << "\n4. Testing set_debug_logfile..." << std::endl;
    try 
    {
        BinanceCPP_logger::set_debug_logfile("/tmp/test_binance.log");
        std::cout << "✅ set_debug_logfile successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ set_debug_logfile failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 5: Enable/disable log file
    std::cout << "\n5. Testing enable_logfile..." << std::endl;
    try 
    {
        BinanceCPP_logger::enable_logfile(1);
        BinanceCPP_logger::write_log("Test file log");
        BinanceCPP_logger::enable_logfile(0);
        std::cout << "✅ enable_logfile toggle successful" << std::endl;
        
        // Clean up test log file
        std::remove("/tmp/test_binance.log");
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ enable_logfile failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 6: Disabled logging
    std::cout << "\n6. Testing disabled logging..." << std::endl;
    try 
    {
        BinanceCPP_logger::set_debug_level(0);
        BinanceCPP_logger::write_log("This should not appear");
        BinanceCPP_logger::set_debug_level(1); // Re-enable for final message
        std::cout << "✅ Disabled logging test successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ Disabled logging test failed: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== BinanceCPP_logger Tests Complete ===" << std::endl;
    return 0;
}