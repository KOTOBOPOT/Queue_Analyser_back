cmake_minimum_required(VERSION 3.0.0)
project(queueAnalyser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_subdirectory(lib/server)
add_subdirectory(lib/computer_vision)
add_subdirectory(lib/database_handler)
add_subdirectory(lib/tg_bot)

find_package(Boost REQUIRED)
include_directories(include ${Boost_INCLUDE_DIRS})

find_package(GTest REQUIRED)# Почему-то если добавляю в главный  СMakeLists, то он его не видит
enable_testing()

add_executable(${PROJECT_NAME}  
                    src/main.cpp 
                    src/routes.cpp
                    src/video_processors.cpp
)

target_link_libraries(${PROJECT_NAME} 
                        server 
                        computer_vision 
                        database_handler 
                        tg_bot 
                        ${Boost_LIBRARIES}
)