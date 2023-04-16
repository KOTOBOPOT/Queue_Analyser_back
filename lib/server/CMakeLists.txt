# Подключение всех cpp файлов в директории src/
aux_source_directory(src SERVER_SOURCES)

# Задание цели
# add_library(Server ${SERVER_SOURCES})
add_library(server  
                    src/error.cpp                    
                    src/session.cpp                    
                    src/listener.cpp                    
                    src/server.cpp                    
                    # src/router.cpp                    
                    # src/session.cpp                    
                    # src/server.cpp
                    # src/handler.cpp                    
)

# Покдлючение всех hpp файлов в директории include/
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)