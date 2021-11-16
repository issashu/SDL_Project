cmake_minimum_required(VERSION 3.10.1)

project(SDL_game LANGUAGES C)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers_c.cmake)

#Remove/Comment before final build or before using Valgrind (CLion specific sanitizer options)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize-address-use-after-scope  -fno-omit-frame-pointer -g")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g")
#Uncomment below line in order to run the Clion profiler:
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

#Uncomment below for Apple Silicon setups
#set(CMAKE_OSX_ARCHITECTURES "arm64")

#Set directories below
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(HEADERS_DIR ${BASE_DIR}/game/include)
set(SOURCES_DIR ${BASE_DIR}/game/src)
set(ASSETS_PATH ${BASE_DIR}/game/assets/)

# This appends a complex path to a variable. Set it as itself and then set the path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

add_executable( ${PROJECT_NAME}
        ${HEADERS_DIR}/main.h
        ${SOURCES_DIR}/main.c
        )

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${BASE_DIR}
        )

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        game_engine
        )

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE
        _DEFAULT_SOURCE=1
        )

add_subdirectory(game_engine)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})