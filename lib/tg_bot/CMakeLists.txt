# Задание цели
add_library(tg_bot  
                src/bot.cpp                    
)

# Покдлючение всех hpp файлов в директории include/
target_include_directories(tg_bot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
