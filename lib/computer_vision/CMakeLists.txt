# Подключение всех cpp файлов в директории src/
aux_source_directory(src COMPUTER_VISION_SOURCES)

# Задание цели
add_library(computer_vision ${COMPUTER_VISION_SOURCES})

# Покдлючение всех hpp файлов в директории include/
target_include_directories(computer_vision PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)