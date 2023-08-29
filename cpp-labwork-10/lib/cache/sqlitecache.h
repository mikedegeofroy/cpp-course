#include <iostream>
#include <string>
#include <stdexcept>
#include <sqlite3.h>

class SQLiteCache {
    private:
        sqlite3* db;
        char* err_msg;
    public:
        SQLiteCache(const std::string& db_file);
        
        void put(const std::string& key, const std::string& value);
        
        std::string get(const std::string& key);

        ~SQLiteCache();
};
