add_executable(tests test_main.cc
        test_lexer.cc
        test_let_statement.cc)

target_link_libraries(tests gtest_main lexerLib astLib)
target_include_directories(tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ast)

include(GoogleTest)
gtest_discover_tests(tests)
