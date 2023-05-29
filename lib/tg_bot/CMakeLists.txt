add_library(tg_bot  
                src/tg_bot.cpp
                src/bot_handlers/all_data_handler.cpp
                src/bot_handlers/current_data_handler.cpp
                src/bot_handlers/simple_handler.cpp
                src/handler_creators/all_data_creator.cpp
                src/handler_creators/current_data_creator.cpp
                src/handler_creators/simple_creator.cpp
                src/creator_chouser.cpp
)

find_package(Boost REQUIRED COMPONENTS system)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ../database_handler)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

target_include_directories(tg_bot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_link_libraries(tg_bot database_handler TgBot ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} Threads::Threads)