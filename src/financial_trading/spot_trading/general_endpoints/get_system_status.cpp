/*
        Author: blackb1rd
        Date  : 2025/08/11
        Based on original work by tensaix2j (2017/10/15)

        C++ library for Binance API - Get System Status
        GET /sapi/v1/system/status - System status
        Following Google C++ Style Guide naming conventions
*/

#include "../../../binance_cpp.h"
#include "../../../binance_logger.h"

namespace binance_cpp
{
namespace financial_trading
{
namespace spot_trading
{
namespace general_endpoints
{

void ExchangeInformation::GetSystemStatus(Json::Value& json_result)
{
  BinanceCPP_logger::write_log("<ExchangeInformation::GetSystemStatus>");

  std::string url(BINANCE_HOST);
  url += "/sapi/v1/system/status";

  std::string str_result;
  core::BinanceAPI::CurlAPI(url, str_result);

  if (str_result.size() > 0)
  {
    try
    {
      Json::Reader reader;
      json_result.clear();
      reader.parse(str_result, json_result);
    }
    catch (std::exception& e)
    {
      BinanceCPP_logger::write_log(
          "<ExchangeInformation::GetSystemStatus> Error ! %s", e.what());
    }
    BinanceCPP_logger::write_log(
        "<ExchangeInformation::GetSystemStatus> Done.");
  }
  else
  {
    BinanceCPP_logger::write_log(
        "<ExchangeInformation::GetSystemStatus> Failed to get anything.");
  }
}

}  // namespace general_endpoints
}  // namespace spot_trading
}  // namespace financial_trading
}  // namespace binance_cpp
