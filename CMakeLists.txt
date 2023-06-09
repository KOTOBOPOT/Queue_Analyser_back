cmake_minimum_required(VERSION 3.0.0)
project(queueAnalyser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

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
                    src/const.cpp
                    src/video_processors.cpp
)

add_executable(start_server
                    src/const.cpp
                    src/routes.cpp
                    src/server_main.cpp
)

add_executable(tgBot
                    src/const.cpp
                    src/tgbot_main.cpp
)

target_link_libraries(start_server server database_handler ${Boost_LIBRARIES})

target_link_libraries(tgBot tg_bot ${Boost_LIBRARIES})


target_link_libraries(${PROJECT_NAME} 
                        computer_vision 
                        database_handler 
)