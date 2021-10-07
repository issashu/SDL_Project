cmake_minimum_required(VERSION 3.10.1)

project(SDL_game LANGUAGES C)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers_c.cmake)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(_HEADERS_DIR ${_BASE_DIR}/include)
set(_SOURCES_DIR ${_BASE_DIR}/src)
# This appends a complex path to a variable. Set it as itself and then set the path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

#TODO Check and rearrange all the executables and headers
add_executable(${PROJECT_NAME}
        ${_SOURCES_DIR}/main.c
        )

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${_BASE_DIR}
        )

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        utils_sdl
)

add_subdirectory(utils)
add_subdirectory(utils_sdl)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})