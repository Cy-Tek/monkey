add_library(pch INTERFACE)
target_precompile_headers(pch INTERFACE common/pch.h)

add_subdirectory(lexer)

add_executable(monkey main.cpp)

target_link_libraries(monkey PRIVATE pch)
target_link_libraries(monkey PUBLIC lexerLib)
