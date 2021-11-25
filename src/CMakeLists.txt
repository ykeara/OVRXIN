cmake_minimum_required(VERSION 3.19)
add_subdirectory(include)
# set the project name

project(OVRXIN LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ../third_party)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/AppManifest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput_action_set.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput_input_source.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput_manifest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/imgui_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UIWrapper.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/backends/imgui_impl_glfw.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/backends/imgui_impl_opengl3.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/glfw/GLFW/glfw3.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/glfw/GLFW/glfw3native.h)


set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AppManifest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UIWrapper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/backends/imgui_impl_glfw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/third_party/imgui/backends/imgui_impl_opengl3.cpp)

# add the executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})


target_link_libraries(${PROJECT_NAME} PRIVATE
    openvr
    ViGEm
    imgui
    GLFW)

target_include_directories(${PROJECT_NAME} PRIVATE include
    ovrinput
    ${CMAKE_CURRENT_SOURCE_DIR})
