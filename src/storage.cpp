#include "storage.h"
#include <fstream>
#include <sstream>

Storage::Storage(const std::string& file)
    :filename(file){
        replay();
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

const std::unordered_map<std::string, std::string>& Storage::load() const {
    return kv;
}

void Storage::appendput(const std::string& key, const std::string& value) {
    std::ofstream out(filename, std::ios::app);
    out << "PUT " << key << " " << value << "\n";

}

void Storage::appenddel(const std::string& key) {
    std::ofstream out(filename, std::ios::app);
    out << "DEL " << key << "\n";
}

void Storage::snapshot(const std::unordered_map<std::string, std::string>& data) {
    std::ofstream out("snapshot.tmp");
    for (const auto& [key, value] : data) {
        out << key << " " << value << "\n";
    }
    out.close();
    std::remove("snapshot.db");
    std::rename("snapshot.tmp", "snapshot.db");

    std::ofstream clearLog(filename, std::ios::trunc);
}