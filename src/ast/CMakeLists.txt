file(GLOB SOURCES ./*.cc)

# Add library target
add_library(astLib SHARED ${SOURCES})

target_link_libraries(astLib PUBLIC pch utilsLib lexerLib)
target_include_directories(astLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../utils
        ${CMAKE_CURRENT_SOURCE_DIR}/../lexer)
