# Подключение всех cpp файлов в директории src/
aux_source_directory(src SERVER_SOURCES)

# Задание цели
add_library(Server ${SERVER_SOURCES})

# Покдлючение всех hpp файлов в директории include/
target_include_directories(Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)