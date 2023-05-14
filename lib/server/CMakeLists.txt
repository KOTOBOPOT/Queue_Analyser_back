set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)


find_package(Boost REQUIRED)

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

target_link_libraries(server PUBLIC 
                                database_handler 
                                ${Boost_LIBRARIES}
)
# Покдлючение всех hpp файлов в директории include/
target_include_directories(server PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR}/include 
                                ${Boost_INCLUDE_DIRS} 
)