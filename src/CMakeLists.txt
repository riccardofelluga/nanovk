# nanovk library

set(SOURCES
    view.cpp
   # pipeline.cpp
    device.cpp
)

add_library(nanovk STATIC ${SOURCES})

target_link_libraries(nanovk PUBLIC glfw ${Vulkan_LIBRARIES})