// Note: Headers are included in binance_modular.cpp

/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Initialization Functions
        Updated for C++20 support
*/

//============================================================================
// INITIALIZATION FUNCTIONS
//============================================================================

void BinanceCPP::init() {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  BinanceCPP::curl = curl_easy_init();
}

void BinanceCPP::init(std::string_view api_key, std::string_view secret_key) {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  BinanceCPP::curl = curl_easy_init();
  BinanceCPP::api_key = api_key;
  BinanceCPP::secret_key = secret_key;
}
