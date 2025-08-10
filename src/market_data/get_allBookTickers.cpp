/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - All Book Tickers
        GET /api/v1/ticker/allBookTickers - Get best price/qty on the order book
   for all symbols
*/
#include "binance.h"
#include "binance_logger.h"

void BinanceCPP::get_allBookTickers(Json::Value &json_result)
{
  BinanceCPP_logger::write_log("<BinanceCPP::get_allBookTickers>");

  std::string url(BINANCE_HOST);
  url += "/api/v1/ticker/allBookTickers";

  std::string str_result;
  curl_api(url, str_result);

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
          "<BinanceCPP::get_allBookTickers> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log("<BinanceCPP::get_allBookTickers> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<BinanceCPP::get_allBookTickers> Failed to get anything.");
  }
}
