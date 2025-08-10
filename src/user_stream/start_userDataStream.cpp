/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Start User Data Stream
        POST /api/v1/userDataStream - Start user data stream (API-KEY)
*/
#include "binance.h"
#include "binance_logger.h"

void BinanceCPP::start_userDataStream(Json::Value &json_result)
{
  BinanceCPP_logger::write_log("<BinanceCPP::start_userDataStream>");

  if (api_key.size() == 0)
  {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::start_userDataStream> API Key has not been set.");
    return;
  }

  std::string url(BINANCE_HOST);
  url += "/api/v1/userDataStream";

  std::vector<std::string> extra_http_header;
  std::string              header_chunk("X-MBX-APIKEY: ");

  header_chunk.append(api_key);
  extra_http_header.push_back(header_chunk);

  BinanceCPP_logger::write_log("<BinanceCPP::start_userDataStream> url = |%s|",
                               url.c_str());

  std::string action    = "POST";
  std::string post_data = "";

  std::string str_result;
  curl_api_with_header(url, str_result, extra_http_header, post_data, action);

  if (str_result.size() > 0)
  {
    try
    {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    }
    catch (std::exception &e)
    {
      BinanceCPP_logger::write_log(
          "<BinanceCPP::start_userDataStream> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log("<BinanceCPP::start_userDataStream> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::start_userDataStream> Failed to get anything.");
  }

  BinanceCPP_logger::write_log("<BinanceCPP::start_userDataStream> Done.\n");
}
