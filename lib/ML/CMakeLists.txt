# Подключение всех cpp файлов в директории src/
aux_source_directory(src ML_SOURCES)

# Задание цели
add_library(ML ${ML_SOURCES})

# Покдлючение всех hpp файлов в директории include/
target_include_directories(ML PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)