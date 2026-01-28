#include "db.h"

#include <fstream>
#include <sstream>
#include <vector>

DB::DB(const std::string& filename) : storage(filename) {
    store = storage.load();
    std::ifstream infile(filename);
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string cmd, key, value;

        iss >> cmd >> key;

        if (cmd == "PUT") {
            iss >> value;
            store[key] = value;
        } 
        else if (cmd == "DEL") {
            store.erase(key);
        }
    }
}

void DB::put(const std::string& key, const std::string& value) {
    std::shared_lock lock(rwlock);
    storage.appendput(key, value);
    store[key] = value;
}

std::optional<std::string> DB::get(const std::string& key) {
    std::shared_lock shared_lock(rwlock);
    auto it = store.find(key);
    if (it != store.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::vector<std::pair<std::string, std::string>> DB::getRange(const std::string& start, const std::string& end) {
    
    std::shared_lock shared_lock(rwlock);
    std::vector<std::pair<std::string, std::string>> result;

    auto it = store.lower_bound(start);

    while (it != store.end() && it->first <= end) {
        result.push_back(*it);
        ++it;
    }

    return result;
}

void DB::del(const std::string& key) {
    std::shared_lock lock(rwlock);
    storage.appenddel(key);
    store.erase(key);
}

void DB::snapshot() {
    std::shared_lock lock(rwlock);
    storage.snapshot(store);
}