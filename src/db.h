#ifndef DB_H
#define DB_H

#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <shared_mutex>


#include "storage.h"
#include <map>

class DB {
    public:
        
        explicit DB(const std::string& filename) ;
        void put(const std::string& key, const std::string& value);
        std::optional<std::string> get(const std::string& key);
        std::vector<std::pair<std::string, std::string>> getRange(const std::string& start, const std::string& end);
        void del(const std::string& key);
        void compact();
        void snapshot();
        void flushmemtable();

    private:
        std::map<std::string, std::string> store;
        Storage storage;
        std::shared_mutex rwlock;
        std::map<std::string, std::string> memtable;
        size_t memtableSize = 0;
        static constexpr size_t MEMTABLE_LIMIT = 64 * 1024; 
};

#endif // DB_H