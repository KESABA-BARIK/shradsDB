#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <fstream>

class Storage {
public:
    explicit Storage(const std::string& filename);

    void appendput(const std::string& key, const std::string& value);
    void appenddel(const std::string& key);

    private:
        std::ofstream logFile;
};

#endif // STORAGE_H