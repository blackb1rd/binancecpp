/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Book Ticker
        Helper function that uses get_allBookTickers internally to get book
   ticker for specific symbol
*/
#include "binance.h"
#include "binance_logger.h"
#include "binance_utils.h"

void BinanceCPP::get_bookTicker(std::string_view symbol,
                                Json::Value     &json_result)
{
  BinanceCPP_logger::write_log("<BinanceCPP::get_BookTickers>");

  Json::Value alltickers;
  std::string str_symbol = string_toupper(std::string(symbol));
  get_allBookTickers(alltickers);

  for (int i = 0; i < alltickers.size(); i++)
  {
    if (alltickers[i]["symbol"].asString() == str_symbol)
    {
      json_result = alltickers[i];
      break;
    }
  }
}
