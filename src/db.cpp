#include "db.h"

#include <fstream>
#include <sstream>

DB::DB(const std::string& filename) : storage(filename) {
    store.reserve(100000);
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
    storage.appendput(key, value);
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
    storage.appenddel(key);
    store.erase(key);
}

void DB::snapshot() {
    storage.snapshot(store);
}