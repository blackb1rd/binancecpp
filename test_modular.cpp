/*
        Test file for modular BinanceCPP structure
        Author: blackb1rd
        Date: 2025/08/07
*/

#include <iostream>

#include "binancecpp.h"

int main() {
  std::cout << "Testing modular BinanceCPP structure..." << std::endl;

  // Initialize library
  BinanceCPP::init();

  // Test a simple market data call
  Json::Value result;
  BinanceCPP::get_serverTime(result);

  if (!result.empty()) {
    std::cout << "✓ Server time function works!" << std::endl;
    std::cout << "Server time: " << result["serverTime"].asString()
              << std::endl;
  } else {
    std::cout << "✗ Server time function failed" << std::endl;
  }

  // Cleanup
  BinanceCPP::cleanup();

  std::cout << "Modular structure test completed." << std::endl;
  return 0;
}
