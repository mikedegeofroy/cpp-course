#include "sqlitecache.h"

SQLiteCache::SQLiteCache(const std::string& db_file)  {
  if (sqlite3_open(db_file.c_str(), &db)) {
    throw std::runtime_error("Can't open database: " + std::string(sqlite3_errmsg(db)));
  }
  
  const char* create_table_sql = "CREATE TABLE IF NOT EXISTS cache (key TEXT PRIMARY KEY, value TEXT NOT NULL);";
  if (sqlite3_exec(db, create_table_sql, 0, 0, &err_msg)) {
    throw std::runtime_error("Can't create table: " + std::string(err_msg));
  }
}

void SQLiteCache::put(const std::string& key, const std::string& value)  {
  std::string sql = "INSERT OR REPLACE INTO cache (key, value) VALUES (?, ?);";
  sqlite3_stmt* stmt;
  
  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0)) {
    throw std::runtime_error("Can't prepare statement: " + std::string(sqlite3_errmsg(db)));
  }
  
  sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_TRANSIENT);
  
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    throw std::runtime_error("Can't execute statement: " + std::string(sqlite3_errmsg(db)));
  }
  
  sqlite3_finalize(stmt);
}

std::string SQLiteCache::get(const std::string& key)  {
  std::string sql = "SELECT value FROM cache WHERE key = ?;";
  sqlite3_stmt* stmt;
  
  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0)) {
    throw std::runtime_error("Can't prepare statement: " + std::string(sqlite3_errmsg(db)));
  }
  
  sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
  
  int step = sqlite3_step(stmt);
  std::string value;
  
  if (step == SQLITE_ROW) {
    value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
  } else if (step != SQLITE_DONE) {
    throw std::runtime_error("Can't execute statement: " + std::string(sqlite3_errmsg(db)));
  }
  
  sqlite3_finalize(stmt);
  return value;
}

SQLiteCache::~SQLiteCache() {
  sqlite3_close(db);
}
