#include "storage.h"
#include <fstream>
#include <sstream>
#include <filesystem>

Storage::Storage(const std::string& file)
    :filename(file){
        replay();
        logOut.open(filename, std::ios::app);
    }

void Storage::replay() {
    std::ifstream snap("snapshot.db");
    if (snap.is_open()) {
        std::string key, value;
        while (snap >> key >> value) {
            kv[key] = value;
        }
        snap.close();
    }

    std::ifstream in(filename);
    if (!in.is_open()) return;

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);

        std::string cmd, key, value;
        iss >> cmd;

        if (cmd == "PUT") {
            iss >> key >> value;
            kv[key] = value;
        }
        else if (cmd == "DEL") {
            iss >> key;
            kv.erase(key);
        }
    }
}

const std::map<std::string, std::string>& Storage::load() const {
    return kv;
}

void Storage::appendput(const std::string& key, const std::string& value) {
    logOut << "PUT " << key << " " << value << "\n";
    logOut.flush();

}

void Storage::appenddel(const std::string& key) {
    std::ofstream out(filename, std::ios::app);
    out << "DEL " << key << "\n";
}

void Storage::snapshot(const std::map<std::string, std::string>& data) {

    const std::string tmp = "snapshot.tmp";
    const std::string snap = "snapshot.db";
    {
        std::ofstream out(tmp, std::ios::trunc);
        for (const auto& [key, value] : data) {
            out << key << " " << value << "\n";
        }
        out.flush();
    }
    std::remove(snap.c_str());
    std::rename(tmp.c_str(), snap.c_str());

    std::ofstream clear(filename, std::ios::trunc);
}

size_t Storage::logSize() const {
    return std::filesystem::file_size(filename);
}

void Storage::replaceLog(const std::string& tempFile) {
    std::rename(tempFile.c_str(), filename.c_str());
}
