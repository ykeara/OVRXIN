cmake_minimum_required(VERSION 3.19)

add_library(openvr INTERFACE)
target_include_directories(openvr INTERFACE openvr/headers)
target_link_libraries(openvr INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/openvr/lib/win64/openvr_api.lib)

add_library(ViGEm INTERFACE)
target_include_directories(ViGEm INTERFACE ViGEm)
target_link_libraries(ViGEm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ViGEm/ViGEm/ViGEmClient.lib)