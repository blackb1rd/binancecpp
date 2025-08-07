/*
        Test file for modular BinaCPP structure
        Author: blackb1rd
        Date: 2025/08/07
*/

#include "binacpp.h"
#include <iostream>

int main() {
    std::cout << "Testing modular BinaCPP structure..." << std::endl;
    
    // Initialize library
    BinaCPP::init();
    
    // Test a simple market data call
    Json::Value result;
    BinaCPP::get_serverTime(result);
    
    if (!result.empty()) {
        std::cout << "✓ Server time function works!" << std::endl;
        std::cout << "Server time: " << result["serverTime"].asString() << std::endl;
    } else {
        std::cout << "✗ Server time function failed" << std::endl;
    }
    
    // Cleanup
    BinaCPP::cleanup();
    
    std::cout << "Modular structure test completed." << std::endl;
    return 0;
}
