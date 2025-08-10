/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Cleanup Functions
        Updated for C++20 support
*/
#include "binance.h"

//============================================================================
// CLEANUP FUNCTIONS
//============================================================================

void BinanceCPP::cleanup() noexcept
{
  if (BinanceCPP::curl != nullptr)
  {
    curl_easy_cleanup(BinanceCPP::curl);
    BinanceCPP::curl = nullptr;
  }
  curl_global_cleanup();
}
