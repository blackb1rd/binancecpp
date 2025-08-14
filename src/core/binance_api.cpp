/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Core Implementation
        Following Google C++ Style Guide naming conventions
*/

#include <openssl/hmac.h>
#include <openssl/sha.h>

#include "../binance_cpp.h"
#include "../binance_logger.h"
#include "../binance_utils.h"

namespace binance_cpp
{
namespace core
{

std::string BinanceAPI::api_key_    = "";
std::string BinanceAPI::secret_key_ = "";
CURL*       BinanceAPI::curl_       = nullptr;

void BinanceAPI::Init()
{
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl_ = curl_easy_init();
}

void BinanceAPI::Init(std::string_view api_key, std::string_view secret_key)
{
  api_key_    = std::string(api_key);
  secret_key_ = std::string(secret_key);
  Init();
}

void BinanceAPI::Cleanup() noexcept
{
  if (curl_)
  {
    curl_easy_cleanup(curl_);
    curl_ = nullptr;
  }
  curl_global_cleanup();
}

size_t BinanceAPI::CurlCallback(void*        content,
                                size_t       size,
                                size_t       nmemb,
                                std::string* buffer)
{
  if (buffer == nullptr)
  {
    return 0;
  }

  size_t real_size = size * nmemb;
  buffer->append(static_cast<char*>(content), real_size);
  return real_size;
}

void BinanceAPI::CurlAPI(std::string& url, std::string& result_json)
{
  std::vector<std::string> extra_headers;
  std::string              post_data;
  std::string              action = "GET";
  CurlAPIWithHeader(url, result_json, extra_headers, post_data, action);
}

void BinanceAPI::CurlAPIWithHeader(std::string&              url,
                                   std::string&              result_json,
                                   std::vector<std::string>& extra_http_header,
                                   std::string&              post_data,
                                   std::string&              action)
{
  BinanceCPP_logger::write_log("<BinanceAPI::CurlAPIWithHeader> url = %s",
                               url.c_str());

  if (!curl_)
  {
    BinanceCPP_logger::write_log(
        "<BinanceAPI::CurlAPIWithHeader> CURL not initialized");
    return;
  }

  result_json.clear();

  curl_easy_reset(curl_);

  curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlCallback);
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &result_json);
  curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl_, CURLOPT_ENCODING, "gzip");

  if (action == "DELETE" || action == "POST" || action == "PUT")
  {
    if (action == "DELETE")
    {
      curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");
    }
    else if (action == "PUT")
    {
      curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PUT");
    }
    else
    {
      curl_easy_setopt(curl_, CURLOPT_POST, 1L);
    }

    if (!post_data.empty())
    {
      curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, post_data.c_str());
    }
  }

  struct curl_slist* chunk = nullptr;
  for (const auto& header : extra_http_header)
  {
    chunk = curl_slist_append(chunk, header.c_str());
  }

  if (chunk)
  {
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);
  }

  CURLcode res = curl_easy_perform(curl_);

  if (chunk)
  {
    curl_slist_free_all(chunk);
  }

  if (res != CURLE_OK)
  {
    BinanceCPP_logger::write_log(
        "<BinanceAPI::CurlAPIWithHeader> curl_easy_perform() failed: %s",
        curl_easy_strerror(res));
  }
}

}  // namespace core
}  // namespace binance_cpp
