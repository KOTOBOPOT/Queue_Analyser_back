# Подключение всех cpp файлов в директории src/
aux_source_directory(src SERVER_SOURCES)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)


find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ../database_handler)

# Задание цели
add_library(server
                    src/parse_query_string.cpp                    
                    src/types.cpp                    
                    src/error.cpp                    
                    src/session.cpp                    
                    src/listener.cpp                    
                    src/router.cpp                    
                    src/server.cpp                    
)

# Покдлючение всех hpp файлов в директории include/
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(server database_handler ${Boost_LIBRARIES})