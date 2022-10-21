# nanovk library

set(SOURCES
    render.cpp
)

add_library(nanovk STATIC ${SOURCES})

target_link_libraries(nanovk PUBLIC glfw)