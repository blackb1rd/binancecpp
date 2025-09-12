/*
    Unit test for binance_utils.cpp
    Tests the utility functions
*/

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "../src/binance_utils.h"

int main()
{
    std::cout << "=== Testing Binance Utils ===" << std::endl;
    
    // Test 1: split_string function
    std::cout << "\n1. Testing split_string..." << std::endl;
    try 
    {
        std::vector<std::string> result;
        split_string("hello,world,test", ',', result);
        
        if (result.size() == 3 && result[0] == "hello" && result[1] == "world" && result[2] == "test")
        {
            std::cout << "✅ split_string successful" << std::endl;
        }
        else
        {
            std::cout << "❌ split_string failed: incorrect result" << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ split_string failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 2: replace_string function
    std::cout << "\n2. Testing replace_string..." << std::endl;
    try 
    {
        std::string test_str = "hello world hello";
        bool result = replace_string(test_str, "hello", "hi");
        
        if (result && test_str == "hi world hi")
        {
            std::cout << "✅ replace_string successful" << std::endl;
        }
        else
        {
            std::cout << "❌ replace_string failed: " << test_str << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ replace_string failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 3: replace_string_once function
    std::cout << "\n3. Testing replace_string_once..." << std::endl;
    try 
    {
        std::string test_str = "hello world hello";
        int result = replace_string_once(test_str, "hello", "hi", 0);
        
        if (result > 0 && test_str == "hi world hello")
        {
            std::cout << "✅ replace_string_once successful" << std::endl;
        }
        else
        {
            std::cout << "❌ replace_string_once failed: " << test_str << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ replace_string_once failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 4: string_toupper function
    std::cout << "\n4. Testing string_toupper..." << std::endl;
    try 
    {
        std::string test_str = "hello world";
        string_toupper(test_str);
        
        if (test_str == "HELLO WORLD")
        {
            std::cout << "✅ string_toupper (in-place) successful" << std::endl;
        }
        else
        {
            std::cout << "❌ string_toupper (in-place) failed: " << test_str << std::endl;
            return 1;
        }
        
        // Test the overload that returns a new string
        std::string result = string_toupper("test string");
        if (result == "TEST STRING")
        {
            std::cout << "✅ string_toupper (return new) successful" << std::endl;
        }
        else
        {
            std::cout << "❌ string_toupper (return new) failed: " << result << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ string_toupper failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 5: b2a_hex function
    std::cout << "\n5. Testing b2a_hex..." << std::endl;
    try 
    {
        char data[] = {0x01, 0x23, 0x45, 0x67};
        std::string result = b2a_hex(data, 4);
        
        if (result == "01234567")
        {
            std::cout << "✅ b2a_hex successful" << std::endl;
        }
        else
        {
            std::cout << "❌ b2a_hex failed: " << result << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ b2a_hex failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 6: get_current_epoch function
    std::cout << "\n6. Testing get_current_epoch..." << std::endl;
    try 
    {
        time_t epoch1 = get_current_epoch();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        time_t epoch2 = get_current_epoch();
        
        if (epoch2 >= epoch1 && epoch1 > 1600000000) // Should be a recent timestamp
        {
            std::cout << "✅ get_current_epoch successful: " << epoch1 << std::endl;
        }
        else
        {
            std::cout << "❌ get_current_epoch failed: " << epoch1 << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ get_current_epoch failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 7: get_current_ms_epoch function
    std::cout << "\n7. Testing get_current_ms_epoch..." << std::endl;
    try 
    {
        unsigned long ms_epoch1 = get_current_ms_epoch();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        unsigned long ms_epoch2 = get_current_ms_epoch();
        
        if (ms_epoch2 > ms_epoch1 && ms_epoch1 > 1600000000000UL) // Should be a recent timestamp in ms
        {
            std::cout << "✅ get_current_ms_epoch successful: " << ms_epoch1 << std::endl;
        }
        else
        {
            std::cout << "❌ get_current_ms_epoch failed: " << ms_epoch1 << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ get_current_ms_epoch failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 8: hmac_sha256 function
    std::cout << "\n8. Testing hmac_sha256..." << std::endl;
    try 
    {
        std::string result = hmac_sha256("key", "test data");
        
        // HMAC-SHA256 should always return a 64-character hex string
        if (result.length() == 64)
        {
            std::cout << "✅ hmac_sha256 successful (length check)" << std::endl;
        }
        else
        {
            std::cout << "❌ hmac_sha256 failed: wrong length " << result.length() << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ hmac_sha256 failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 9: sha256 function
    std::cout << "\n9. Testing sha256..." << std::endl;
    try 
    {
        std::string result = sha256("test data");
        
        // SHA256 should always return a 64-character hex string
        if (result.length() == 64)
        {
            std::cout << "✅ sha256 successful (length check)" << std::endl;
        }
        else
        {
            std::cout << "❌ sha256 failed: wrong length " << result.length() << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ sha256 failed: " << e.what() << std::endl;
        return 1;
    }
    
    // Test 10: file_exists function
    std::cout << "\n10. Testing file_exists..." << std::endl;
    try 
    {
        // Test with a file that should not exist
        bool result1 = file_exists("/this/file/should/not/exist");
        
        // Test with a file that should exist (the test file itself)
        bool result2 = file_exists("/tmp"); // /tmp directory should exist on Unix systems
        
        if (!result1)
        {
            std::cout << "✅ file_exists (non-existent file) successful" << std::endl;
        }
        else
        {
            std::cout << "❌ file_exists (non-existent file) failed" << std::endl;
            return 1;
        }
        
#ifndef _WIN32
        if (result2)
        {
            std::cout << "✅ file_exists (existing directory) successful" << std::endl;
        }
        else
        {
            std::cout << "⚠️  file_exists (existing directory) - /tmp not found (might be Windows)" << std::endl;
        }
#endif
    }
    catch (const std::exception& e)
    {
        std::cout << "❌ file_exists failed: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Binance Utils Tests Complete ===" << std::endl;
    return 0;
}