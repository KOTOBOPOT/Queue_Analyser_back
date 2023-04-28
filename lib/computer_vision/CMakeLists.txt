# Подключение всех cpp файлов в директории src/
aux_source_directory(src COMPUTER_VISION_SOURCES)

find_package( OpenCV REQUIRED )

# Задание цели
add_library(computer_vision ${COMPUTER_VISION_SOURCES})

# Покдлючение всех hpp файлов в директории include/
target_link_libraries( computer_vision ${OpenCV_LIBS} )
target_include_directories(computer_vision PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#include_directories( ${OpenCV_INCLUDE_DIRS} )
#include_directories(${PROJECT_SOURCE_DIR}/include)
#add_executable( DisplayImage src/DisplayImage.cpp  src/VideoProcessor.cpp src/CVPicProcessor.cpp)