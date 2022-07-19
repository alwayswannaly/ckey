#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <map>

#define MAX_KEY_LENGTH = 100
#define MAX_VALUE_LENGTH = 1000

#define EMPTY_STRING_LITERAL ""
#define FOUND_BIT "1"
#define NOT_FOUND_BIT "0"

class Cache {
private:
  int capacity;
  int current_size;
  std::map<std::string, std::string> cache;

  bool safe_to_insert(const std::string &key, const std::string &value);
  std::string found(std::string res);
  std::string not_found(std::string res);
public:
  Cache(int capacity);
  ~Cache();

  std::string dump(bool output_to_console);
  std::string get(const std::string &key);
  void set(const std::string &key, const std::string &value);
}

#endif
