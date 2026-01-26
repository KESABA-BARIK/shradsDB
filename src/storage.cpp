#include "storage.h"
Storage::Storage(const std::string& filename) {
    logFile.open(filename, std::ios::app);
}

void Storage::appendput(const std::string& key, const std::string& value) {
    if (logFile.is_open()) {
        logFile << "PUT " << key << " " << value << "\n";
        logFile.flush();
    }
}

void Storage::appenddel(const std::string& key) {
    if (logFile.is_open()) {
        logFile << "DEL " << key << "\n";
        logFile.flush();
    }
}