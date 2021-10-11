cmake_minimum_required(VERSION 3.10.1)

project(SDL_game LANGUAGES C)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers_c.cmake)

#_CXX_ for C++
#Remove/Comment before final build
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize-address-use-after-scope -g")

#Uncomment below for Apple Silicon setups
#set(CMAKE_OSX_ARCHITECTURES "arm64")

#Set directories below
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(HEADERS_DIR ${BASE_DIR}/include)
set(SOURCES_DIR ${BASE_DIR}/src)
set(ASSETS_PATH ${BASE_DIR}/assets/)

# This appends a complex path to a variable. Set it as itself and then set the path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

#TODO Check and rearrange all the executables and headers
add_executable(${PROJECT_NAME}
        ${SOURCES_DIR}/main.c
        ${SOURCES_DIR}/gameLoop.c

        ${HEADERS_DIR}/gameLoop.h
        )

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${BASE_DIR}
        )

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        utils_sdl
        )

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE
        _DEFAULT_SOURCE=1
        )

add_subdirectory(utils_sdl)
add_subdirectory(utils)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})