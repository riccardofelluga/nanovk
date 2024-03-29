#tell cmake where to put output binaries
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
message(STATUS "Output directory for sample: ${EXECUTABLE_OUTPUT_PATH}")

set(SHADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
file(GLOB SHADERS_LIST "${SHADER_PATH}/*.vert" "${SHADER_PATH}/*.frag")

foreach(SHADER ${SHADERS_LIST})
    get_filename_component(FILENAME ${SHADER} NAME)
    add_dependencies( ${PROJECT_NAME} "compile_${FILENAME}")
	add_custom_target(
		"compile_${FILENAME}"
		COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} -o ${FILENAME}.spv
		WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
		COMMENT "Compiling ${FILENAME}..."
	)
    message(STATUS "Found shader: ${SHADER}")
endforeach()

# add the main executable
add_executable(nanovk_sample main.cpp)
target_link_libraries(nanovk_sample PUBLIC nanovk)
