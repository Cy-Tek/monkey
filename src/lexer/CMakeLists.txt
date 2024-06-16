# Assume the source files are in the current directory
file(GLOB SOURCES ./*.cc)

# Add library target
add_library(lexerLib SHARED ${SOURCES})

target_link_libraries(lexerLib PUBLIC pch)