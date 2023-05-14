project(database_tests)

add_executable(db_handler_test src/test_conversions.cpp)
target_link_libraries(db_handler_test database_handler GTest::gtest_main)

add_test(db_handler_test db_handler_test)