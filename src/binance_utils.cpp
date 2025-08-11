
#include "binance_utils.h"

#include <chrono>

//--------------------------------
void split_string(std::string_view          s,
                  char                      delim,
                  std::vector<std::string>& result)
{
  std::stringstream ss;
  ss.str(std::string(s));
  std::string item;
  while (std::getline(ss, item, delim))
  {
    result.push_back(item);
  }
}

//--------------------------------
int replace_string_once(std::string&     str,
                        std::string_view from,
                        std::string_view to,
                        int              offset)
{
  const size_t start_pos = str.find(from, offset);
  if (start_pos == std::string::npos)
  {
    return 0;
  }
  str.replace(start_pos, from.length(), to);
  return static_cast<int>(start_pos + to.length());
}

//--------------------------------
bool replace_string(std::string&     str,
                    std::string_view from,
                    std::string_view to)
{
  bool   found     = false;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos)
  {
    str.replace(start_pos, from.length(), to);
    found = true;
    start_pos += to.length();
  }
  return found;
}

//-----------------------
void string_toupper(std::string& src)
{
  for (char& c : src)
  {
    c = static_cast<char>(toupper(c));
  }
}

//--------------------------------------
std::string string_toupper(std::string_view cstr)
{
  std::string ret{cstr};
  string_toupper(ret);
  return ret;
}

//--------------------------------------
std::string b2a_hex(char* byte_arr, int n)
{
  constexpr std::string_view HexCodes = "0123456789abcdef";
  std::string                HexString;
  HexString.reserve(n * 2);
  for (int i = 0; i < n; ++i)
  {
    const unsigned char BinValue = static_cast<unsigned char>(byte_arr[i]);
    HexString += HexCodes[(BinValue >> 4) & 0x0F];
    HexString += HexCodes[BinValue & 0x0F];
  }
  return HexString;
}

//---------------------------------
time_t get_current_epoch()
{
  return std::chrono::duration_cast<std::chrono::seconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

//---------------------------------
unsigned long get_current_ms_epoch()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

//---------------------------
std::string hmac_sha256(std::string_view key, std::string_view data)
{
  const unsigned char* digest;
  digest = HMAC(EVP_sha256(),
                key.data(),
                static_cast<int>(key.length()),
                reinterpret_cast<const unsigned char*>(data.data()),
                static_cast<int>(data.length()),
                nullptr,
                nullptr);
  return b2a_hex(const_cast<char*>(reinterpret_cast<const char*>(digest)), 32);
}

//------------------------------
std::string sha256(std::string_view data)
{
  unsigned char digest[32];
  SHA256_CTX    sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data.data(), data.length());
  SHA256_Final(digest, &sha256);
  return b2a_hex(reinterpret_cast<char*>(digest), 32);
}
