add_library(sqlitecache sqlitecache.cpp)

target_link_libraries(sqlitecache sqlite3)