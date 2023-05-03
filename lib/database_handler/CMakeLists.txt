# Подключение всех .cpp файлов в директории src/
aux_source_directory(src DATABASE_HANDLER_SOURCES)

# Задание цели
add_library(database_handler ${DATABASE_HANDLER_SOURCES})

# Find the SQLite3 library
find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
    message(STATUS "SQLite3 found: ${SQLite3_INCLUDE_DIRS}")
    include_directories(${SQLite3_INCLUDE_DIRS})
endif()

# Link the SQLite3 library to your project
target_link_libraries(database_handler ${SQLite3_LIBRARIES})

# Покдлючение всех .h файлов в директории include/
target_include_directories(database_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
