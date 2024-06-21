# Assume the source files are in the current directory
file(GLOB SOURCES ./*.cc)

# Add library target
add_library(utilsLib SHARED ${SOURCES})

target_link_libraries(utilsLib PUBLIC pch)
