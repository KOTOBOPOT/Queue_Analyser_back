# Подключение всех cpp файлов в директории src/
aux_source_directory(src DATABASE_HANDLER_SOURCES)

# Задание цели
add_library(database_handler ${DATABASE_HANDLER_SOURCES})

# Покдлючение всех hpp файлов в директории include/
target_include_directories(database_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)