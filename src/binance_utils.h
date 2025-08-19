#ifndef BINANCE_UTILS_H
#define BINANCE_UTILS_H

#include <openssl/hmac.h>
#include <openssl/sha.h>

// Cross-platform includes
#ifdef _WIN32
#define NOMINMAX  // Prevent Windows min/max macros from conflicting with std::min/max
#include <io.h>
#include <windows.h>
#define F_OK 0
#define access _access
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <chrono>
#include <concepts>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// C++20 function declarations with modern types
void split_string(std::string_view          s,
                  char                      delim,
                  std::vector<std::string>& result);
bool replace_string(std::string&     str,
                    std::string_view from,
                    std::string_view to);
int  replace_string_once(std::string&     str,
                         std::string_view from,
                         std::string_view to,
                         int              offset);

[[nodiscard]] std::string   b2a_hex(char* byte_arr, int n);
[[nodiscard]] time_t        get_current_epoch();
[[nodiscard]] unsigned long get_current_ms_epoch();

//--------------------
inline bool file_exists(const std::string& name)
{
  return (access(name.c_str(), F_OK) != -1);
}

[[nodiscard]] std::string hmac_sha256(std::string_view key,
                                      std::string_view data);
[[nodiscard]] std::string sha256(std::string_view data);
void                      string_toupper(std::string& src);
[[nodiscard]] std::string string_toupper(std::string_view cstr);

#endif  // BINANCE_UTILS_H