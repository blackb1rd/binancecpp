// Note: Headers are included in binacpp_modular.cpp

/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Cleanup Functions
        Updated for C++20 support
*/


//============================================================================
// CLEANUP FUNCTIONS
//============================================================================

void BinaCPP::cleanup() noexcept {
  if (BinaCPP::curl != nullptr) {
    curl_easy_cleanup(BinaCPP::curl);
    BinaCPP::curl = nullptr;
  }
  curl_global_cleanup();
}
