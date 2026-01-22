#include "db.h"

void DB::put(const std::string& key, const std::string& value) {
    store[key] = value;
}

std::optional<std::string> DB::get(const std::string& key) {
    auto it = store.find(key);
    if (it != store.end()) {
        return it->second;
    }
    return std::nullopt;
}

void DB::del(const std::string& key) {
    store.erase(key);
}