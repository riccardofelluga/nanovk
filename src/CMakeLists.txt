# nanovk library

set(SOURCES
    view.cpp
    stream.cpp
    runtime.cpp
    device.cpp
)

add_library(nanovk STATIC ${SOURCES})

target_include_directories(nanovk PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/dependencies"
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(nanovk PUBLIC glfw ${Vulkan_LIBRARIES})