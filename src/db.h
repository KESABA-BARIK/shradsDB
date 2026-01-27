#ifndef DB_H
#define DB_H

#include <string>
#include <optional>
#include <unordered_map>



#include "storage.h"

class DB {
    public:
        
        explicit DB(const std::string& filename) ;
        void put(const std::string& key, const std::string& value);
        std::optional<std::string> get(const std::string& key);
        void del(const std::string& key);
        void snapshot();

    private:
        std::unordered_map<std::string, std::string> store;
        Storage storage;
};

#endif // DB_H