add_library(tg_bot  
                src/bot.cpp                    
)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ../database_handler)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

target_include_directories(tg_bot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(tg_bot database_handler TgBot ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} Threads::Threads)