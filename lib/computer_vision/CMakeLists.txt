find_package(OpenCV REQUIRED)

# if(BUILD_TESTS)
find_package(GTest REQUIRED)# Почему-то если добавляю в главный  СMakeLists, то он его не видит
enable_testing()
add_subdirectory(tests)
#endif()

# Задание цели
add_library(computer_vision 
                src/cam_video.cpp
                src/cv_pic_processor.cpp
                src/file_video.cpp
                src/i_video_source.cpp
                src/video_processor.cpp
)

# Покдлючение всех hpp файлов в директории include/
target_include_directories(computer_vision PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR}/include
                                ${GTEST_INCLUDE_DIRS}
                                ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(computer_vision PUBLIC ${OpenCV_LIBS})

