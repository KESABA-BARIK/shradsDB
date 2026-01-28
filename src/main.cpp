#include <iostream>
#include <sstream>
#include "db.h"

int main() {
    DB db("data.log");
    std::string command;

    std::cout << "Simple DB CLI. Commands: put <key> <value>, get <key>, del <key>, range <startKey> <endKey>, exit\n";
    while (true) {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);

        if(line.empty()) continue;

        std::istringstream iss(line);
        iss >> command;

        if(command == "put"){ 
            std:: string key, value;
            iss >> key >> value;
            if(key.empty() || value.empty()){
                std::cout << "Usage: put <key> <value>\n";
                continue;
            }
            db.put(key, value);
            std::cout << "Stored (" << key << ", " << value << ")\n";
            continue;
        }
        else if(command == "get"){
            std:: string key;
            iss >> key;
            if(key.empty()){
                std::cout << "Usage: get <key>\n";
                continue;
            }
            auto result = db.get(key);
            if (result) {
                std::cout << "Value: " << *result << "\n";
            } else {
                std::cout << "Key not found\n";
            }
            continue;
        }
        else if(command == "del"){
            std:: string key;
            iss >> key;
            if(key.empty()){
                std::cout << "Usage: del <key>\n";
                continue;
            }
            db.del(key);
            std::cout << "Deleted key: " << key << "\n";
            continue;
        }
        else if (command == "range") {
            std::string start, end;
            iss >> start >> end;

            if (start.empty() || end.empty()) {
                std::cout << "Usage: range <startKey> <endKey>\n";
                continue;
            }

            auto results = db.getRange(start, end);

            if (results.empty()) {
                std::cout << "No keys in range\n";
            } else {
                for (const auto& [key, value] : results) {
                    std::cout << key << " => " << value << "\n";
                }
            }
            continue;
        }

        else if(command == "exit"){
            db.snapshot();
            break;
        }
        else{
            std::cout << "Unknown command\n";
        }
    }
    return 0;
}