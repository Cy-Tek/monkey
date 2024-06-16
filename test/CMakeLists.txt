add_executable(tests test_main.cpp
        test_lexer.cc)

target_link_libraries(tests gtest_main lexerLib)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src/lexer)

include(GoogleTest)
gtest_discover_tests(tests)