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
include_directories(${Boost_INCLUDE_DIRS})
include_directories(include)

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
                        pthread
                        ${Boost_LIBRARIES}
)


# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# target_include_directories(${PROJECT_NAME}
    # PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${CMAKE_CURRENT_SOURCE_DIR}/include/ml
#     ${CMAKE_CURRENT_SOURCE_DIR}/include/server
#     # Добавьте здесь все подключенные заголовочные файлы
# )

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# include(CPack)