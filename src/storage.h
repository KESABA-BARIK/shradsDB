#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <fstream>
#include <unordered_map>

class Storage {
public:
    Storage(const std::string& filename);

    void appendput(const std::string& key, const std::string& value);
    void appenddel(const std::string& key);

    void snapshot(const std::unordered_map<std::string, std::string>& data);

    const std::unordered_map<std::string, std::string>& load() const;

    private:
        std::ofstream logOut;
        std::string filename;
        std::unordered_map<std::string, std::string> kv;

        void replay();
};

#endif // STORAGE_H