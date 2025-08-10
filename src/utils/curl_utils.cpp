/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - CURL Utilities
        Internal HTTP/CURL operations
*/
#include "binance.h"
#include "binance_logger.h"

//============================================================================
// CURL UTILITY FUNCTIONS
//============================================================================

// Curl's callback function
size_t BinanceCPP::curl_cb(void *content,
                           size_t size,
                           size_t nmemb,
                           std::string *buffer) {
  BinanceCPP_logger::write_log("<BinanceCPP::curl_cb> ");

  buffer->append((char *)content, size * nmemb);

  BinanceCPP_logger::write_log("<BinanceCPP::curl_cb> done");
  return size * nmemb;
}

// Simple curl API call without headers
void BinanceCPP::curl_api(std::string &url, std::string &result_json) {
  std::vector<std::string> v;
  std::string action = "GET";
  std::string post_data = "";
  curl_api_with_header(url, result_json, v, post_data, action);
}

// Main curl API function with headers and HTTP methods
// Handles GET, POST, PUT, DELETE requests with authentication headers
void BinanceCPP::curl_api_with_header(
    std::string &url,
    std::string &str_result,
    std::vector<std::string> &extra_http_header,
    std::string &post_data,
    std::string &action) {
  BinanceCPP_logger::write_log("<BinanceCPP::curl_api>");

  CURLcode res;

  if (BinanceCPP::curl) {
    curl_easy_setopt(BinanceCPP::curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(
        BinanceCPP::curl, CURLOPT_WRITEFUNCTION, BinanceCPP::curl_cb);
    curl_easy_setopt(BinanceCPP::curl, CURLOPT_WRITEDATA, &str_result);
    curl_easy_setopt(BinanceCPP::curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(BinanceCPP::curl, CURLOPT_ENCODING, "gzip");

    if (extra_http_header.size() > 0) {
      struct curl_slist *chunk = NULL;
      for (int i = 0; i < extra_http_header.size(); i++) {
        chunk = curl_slist_append(chunk, extra_http_header[i].c_str());
      }
      curl_easy_setopt(BinanceCPP::curl, CURLOPT_HTTPHEADER, chunk);
    }

    if (post_data.size() > 0 || action == "POST" || action == "PUT" ||
        action == "DELETE") {
      if (action == "PUT" || action == "DELETE") {
        curl_easy_setopt(
            BinanceCPP::curl, CURLOPT_CUSTOMREQUEST, action.c_str());
      }
      curl_easy_setopt(BinanceCPP::curl, CURLOPT_POSTFIELDS, post_data.c_str());
    }

    res = curl_easy_perform(BinanceCPP::curl);

    /* Check for errors */
    if (res != CURLE_OK) {
      BinanceCPP_logger::write_log(
          "<BinanceCPP::curl_api> curl_easy_perform() failed: %s",
          curl_easy_strerror(res));
    }
  }

  BinanceCPP_logger::write_log("<BinanceCPP::curl_api> done");
}
