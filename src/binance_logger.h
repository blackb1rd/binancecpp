#ifndef BINANCE_LOGGER_H
#define BINANCE_LOGGER_H

// Windows DLL export/import macros
#ifdef _WIN32
  #ifdef BINANCECPP_EXPORTS
    #define BINANCECPP_API __declspec(dllexport)
  #else
    #define BINANCECPP_API __declspec(dllimport)
  #endif
#else
  #define BINANCECPP_API
#endif

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
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

// Check for C++20 format support
#if defined(__cpp_lib_format) && __cpp_lib_format >= 201907L
#include <format>
#define HAS_STD_FORMAT 1
#else
#include <sstream>
#define HAS_STD_FORMAT 0
#endif

class BINANCECPP_API BinanceCPP_logger
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

  // C++20 format-based logging with fallback
  template <typename... Args>
  static void write_log_format(const std::string &fmt, Args &&...args)
  {
    if constexpr (sizeof...(args) > 0)
    {
#if HAS_STD_FORMAT
      std::string formatted = std::vformat(fmt, std::make_format_args(args...));
#else
      // Fallback implementation using stringstream
      std::ostringstream oss;
      format_fallback(oss, fmt, std::forward<Args>(args)...);
      std::string formatted = oss.str();
#endif
      write_log_clean(formatted.c_str());
    }
    else
    {
      write_log_clean(fmt.c_str());
    }
  }

 private:
#if !HAS_STD_FORMAT
  // Simple fallback formatting helper for single argument
  template <typename T>
  static void format_fallback(std::ostringstream &oss,
                              const std::string  &fmt,
                              T                 &&value)
  {
    size_t pos = fmt.find("{}");
    if (pos != std::string::npos)
    {
      oss << fmt.substr(0, pos) << std::forward<T>(value)
          << fmt.substr(pos + 2);
    }
    else
    {
      oss << fmt << " " << std::forward<T>(value);
    }
  }

  // Recursive fallback for multiple arguments
  template <typename T, typename... Args>
  static void format_fallback(std::ostringstream &oss,
                              const std::string  &fmt,
                              T                 &&value,
                              Args &&...args)
  {
    size_t pos = fmt.find("{}");
    if (pos != std::string::npos)
    {
      std::string before = fmt.substr(0, pos);
      std::string after  = fmt.substr(pos + 2);
      oss << before << std::forward<T>(value);
      format_fallback(oss, after, std::forward<Args>(args)...);
    }
    else
    {
      oss << fmt << " " << std::forward<T>(value);
      format_fallback_remaining(oss, std::forward<Args>(args)...);
    }
  }

  // Helper to handle remaining arguments when no more {} placeholders
  template <typename T>
  static void format_fallback_remaining(std::ostringstream &oss, T &&value)
  {
    oss << " " << std::forward<T>(value);
  }

  template <typename T, typename... Args>
  static void format_fallback_remaining(std::ostringstream &oss,
                                        T                 &&value,
                                        Args &&...args)
  {
    oss << " " << std::forward<T>(value);
    format_fallback_remaining(oss, std::forward<Args>(args)...);
  }
#endif
};

#endif  // BINANCE_LOGGER_H