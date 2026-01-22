#ifndef DB_H
#define DB_H

#include <string>
#include <optional>
#include <unordered_map>


class DB {
    public:
        void put(const std::string& key, const std::string& value);
        std::optional<std::string> get(const std::string& key);
        void del(const std::string& key);

    private:
        std::unordered_map<std::string, std::string> store;
};

#endif // DB_H