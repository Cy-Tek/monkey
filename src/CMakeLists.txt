add_library(pch INTERFACE)
target_precompile_headers(pch INTERFACE common/pch.h)

add_subdirectory(utils)
add_subdirectory(lexer)
add_subdirectory(ast)

add_executable(monkey main.cpp repl.cc)

target_link_libraries(monkey PRIVATE pch)
target_link_libraries(monkey PUBLIC lexerLib)
target_include_directories(monkey PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/lexer
  ${CMAKE_CURRENT_SOURCE_DIR}/utils)
