#ifndef BINANCE_LOGGER_H
#define BINANCE_LOGGER_H

// Platform-specific includes
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <windows.h>
#else
#include <fcntl.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#endif

#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

class BinanceCPP_logger
{
  static int         debug_level;
  static std::string debug_log_file;
  static int         debug_log_file_enable;
  static FILE       *log_fp;

  static void open_logfp_if_not_opened();

 public:
  static void write_log(const char *fmt, ...);
  static void write_log_clean(const char *fmt, ...);
  static void set_debug_level(int level) noexcept;
  static void set_debug_logfile(std::string_view pDebug_log_file);
  static void enable_logfile(int pDebug_log_file_enable) noexcept;

  // C++20 format-based logging
  template <typename... Args>
  static void write_log_format(const std::string &fmt, Args &&...args)
  {
    if constexpr (sizeof...(args) > 0)
    {
      auto formatted = std::vformat(fmt, std::make_format_args(args...));
      write_log_clean(formatted.c_str());
    }
    else
    {
      write_log_clean(fmt.c_str());
    }
  }
};

#endif  // BINANCE_LOGGER_H