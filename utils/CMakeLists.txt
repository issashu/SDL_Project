cmake_minimum_required(VERSION 3.10.1)

project(utils LANGUAGES C)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(_HEADERS_DIR ${_BASE_DIR}/include)
set(_SOURCES_DIR ${_BASE_DIR}/src)

add_library(
       ${PROJECT_NAME} STATIC
       ${_HEADERS_DIR}/utils/Log.h
       ${_HEADERS_DIR}/utils/ErrorCodes.h
       ${_HEADERS_DIR}/utils/containers/Vector.h

       ${_SOURCES_DIR}/containers/Vector.c
)

target_include_directories(
       ${PROJECT_NAME} PUBLIC
            ${_HEADERS_DIR}
)