# nanovk library

set(SOURCES
    render.cpp
)

add_library(nanovk STATIC ${SOURCES})
target_include_directories(nanovk PUBLIC
    "include"
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(nanovk PUBLIC glfw)