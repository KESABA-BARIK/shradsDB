#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>

class Storage {
public:
    Storage(const std::string& filename);

    void appendput(const std::string& key, const std::string& value);
    void appenddel(const std::string& key);

    void snapshot(const std::map<std::string, std::string>& data);

    const std::map<std::string, std::string>& load() const;
    size_t logSize() const;
    void replaceLog(const std::string& tempFile);

    private:
        std::ofstream logOut;
        std::string filename;
        std::map<std::string, std::string> kv;
        std::string logFilename;

        void replay();
};

#endif // STORAGE_H