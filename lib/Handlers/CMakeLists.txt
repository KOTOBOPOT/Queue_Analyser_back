# Подключение всех cpp файлов в директории src/
aux_source_directory(src HANDLERS_SOURCES)

# Задание цели
add_library(Handlers ${HANDLERS_SOURCES})

# Покдлючение всех hpp файлов в директории include/
target_include_directories(Handlers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Связываем библиотеку Handlers с библиотекой Server
target_link_libraries(Handlers Server)