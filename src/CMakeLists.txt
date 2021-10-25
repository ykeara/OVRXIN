cmake_minimum_required(VERSION 3.19)
add_subdirectory(include)
# set the project name
project(OVRXIN LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AppManifest.cpp)
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/AppManifest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput_action_set.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput_input_source.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ovrinput/ivrinput_manifest.h)

# add the executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    openvr
    ViGEm)
target_include_directories(${PROJECT_NAME} PRIVATE include
    ovrinput
    ${CMAKE_CURRENT_SOURCE_DIR})
