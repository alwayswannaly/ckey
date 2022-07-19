#include "cache.hpp"

Cache::Cache(int capacity) {
  this->capacity = capacity;
  this->current_size = 0;
}

// Appends 1 to leftmost position to indicate result was found
std::string Cache::found(const std::string &res) {
  return FOUND_BIT + res;
}

// Appends 0 to leftmost position to indicate result was not found
std::string Cache::not_found(const std::string &res) {
  return NOT_FOUND_BIT + res;
}

bool Cache::safe_to_insert(const std::string &key, const std::string &value) {
  return key.length() < MAX_KEY_LENGTH && value.length() < MAX_VALUE_LENGTH;
}

std::string Cache::get(const std::string &key) {
  if (cache.find(key) == cache.end()) {
    return not_found(EMPTY_STRING_LITERAL);
  }

  return found(cache[key]);
}

void Cache::set(const std::string &key, const std::string &value) {
  if (this->current_size == this->capacity) {
    this->cache.erase(this->cache.last());
  }

  if (safe_to_insert(key, value)) {
    this->cache[key] = value;
  }
}

std::string Cache::dump(bool output_to_console = true) {
  std::string result = EMPTY_STRING_LITERAL;
  std::map<std::string, std::string>::iterator it;

  for (it = cache.begin(); it != cache.end(); it++) {
    result += this->cache.key() + " => " + this->cache.value() + "\n";
  }

  if (output_to_console) {
    std::cout << result;
  }

  return result;
}