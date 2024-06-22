file(GLOB SOURCES ./*.cc)

# Add library target
add_library(lexerLib SHARED ${SOURCES})

target_link_libraries(lexerLib PUBLIC pch utilsLib)
target_include_directories(lexerLib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../utils)
