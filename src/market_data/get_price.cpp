/*
        Author: blackb1rd
        Date  : 2025/08/07
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Single Price
        Helper function that uses get_allPrices internally to get single pair's
   price
*/
#include "binance.h"
#include "binance_logger.h"
#include "binance_utils.h"

double BinanceCPP::get_price(std::string_view symbol)
{
  BinanceCPP_logger::write_log("<BinanceCPP::get_price>");

  double      ret = 0.0;
  Json::Value alltickers;
  const std::string str_symbol = string_toupper(symbol);
  get_allPrices(alltickers);

  for (const Json::Value &ticker : alltickers)
  {
    if (ticker["symbol"].asString() == str_symbol)
    {
      ret = std::stod(ticker["price"].asString());
      break;
    }
  }
  return ret;
}
