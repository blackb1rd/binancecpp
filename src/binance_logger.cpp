#include "binance_logger.h"

#include <chrono>

int BinanceCPP_logger::debug_level = 1;
#ifdef _WIN32
std::string BinanceCPP_logger::debug_log_file = "C:\\temp\\binawatch.log";
#else
std::string BinanceCPP_logger::debug_log_file = "/tmp/binawatch.log";
#endif
int   BinanceCPP_logger::debug_log_file_enable = 0;
FILE *BinanceCPP_logger::log_fp                = nullptr;

//-----------------------------------------------
void BinanceCPP_logger::write_log(const char *fmt, ...)
{
  if (debug_level == 0)
  {
    return;
  }
  if (debug_log_file_enable == 1)
  {
    open_logfp_if_not_opened();
  }

  va_list arg;

  char new_fmt[1024];

  // Cross-platform time handling using C++11 chrono
  auto now_time_point = std::chrono::system_clock::now();
  auto time_t_now     = std::chrono::system_clock::to_time_t(now_time_point);
  auto duration_since_epoch = now_time_point.time_since_epoch();
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
                          duration_since_epoch) %
                      1000000;

  const auto *now = localtime(&time_t_now);

  snprintf(new_fmt,
           sizeof(new_fmt),
           "%04d-%02d-%02d %02d:%02d:%02d %06ld :%s\n",
           now->tm_year + 1900,
           now->tm_mon + 1,
           now->tm_mday,
           now->tm_hour,
           now->tm_min,
           now->tm_sec,
           static_cast<long>(microseconds.count()),
           fmt);

  va_start(arg, fmt);

  if (debug_log_file_enable && log_fp)
  {
    vfprintf(log_fp, new_fmt, arg);
    fflush(log_fp);
  }
  else
  {
    vfprintf(stdout, new_fmt, arg);
    fflush(stdout);
  }

  va_end(arg);
}

//-----------------------------------------------
// Write log to channel without any timestamp nor new line
void BinanceCPP_logger::write_log_clean(const char *fmt, ...)
{
  if (debug_level == 0)
  {
    return;
  }
  if (debug_log_file_enable == 1)
  {
    open_logfp_if_not_opened();
  }

  va_list arg;
  va_start(arg, fmt);

  if (debug_log_file_enable && log_fp)
  {
    vfprintf(log_fp, fmt, arg);
    fflush(log_fp);
  }
  else
  {
    vfprintf(stdout, fmt, arg);
    fflush(stdout);
  }
  va_end(arg);
}

//---------------------
void BinanceCPP_logger::open_logfp_if_not_opened()
{
  if (debug_log_file_enable && log_fp == nullptr)
  {
    log_fp = fopen(debug_log_file.c_str(), "a");

    if (log_fp)
    {
      printf("log file in %s\n", debug_log_file.c_str());
    }
    else
    {
      printf("Failed to open log file.\n");
    }
  }
}

//---------------------
void BinanceCPP_logger::set_debug_level(int level) noexcept
{
  debug_level = level;
}

//--------------------
void BinanceCPP_logger::set_debug_logfile(std::string_view pDebug_log_file)
{
  debug_log_file = pDebug_log_file;
}

//--------------------
void BinanceCPP_logger::enable_logfile(int pDebug_log_file_enable) noexcept
{
  debug_log_file_enable = pDebug_log_file_enable;
}
