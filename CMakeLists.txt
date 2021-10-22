cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set the project name
project(OVR_Controller VERSION 0.0.1)

add_subdirectory(include/third-party)

# add the executable
add_executable(${PROJECT_NAME} main.cpp)

# target_link_libraries(${PROJECT_NAME} OpenVRSDK) 
# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/openvr)