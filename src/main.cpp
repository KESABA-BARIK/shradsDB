#include <iostream>
#include "db.h"

int main() {
    DB db;
    std::string command;

    std::cout << "Simple DB CLI. Commands: put <key> <value>, get <key>, del <key>, exit\n";
    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if(command == "put"){ 
            std:: string key, value;
            std::cin >> key >> value;
            db.put(key, value);
            std::cout << "Stored (" << key << ", " << value << ")\n";
            continue;
        }
        else if(command == "get"){
            std:: string key;
            std::cin >> key;
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
            std::cin >> key;
            db.del(key);
            std::cout << "Deleted key: " << key << "\n";
            continue;
        }
        else if(command == "exit"){
            break;
        }
        else{
            std::cout << "Unknown command\n";
        }
    }
    return 0;
}