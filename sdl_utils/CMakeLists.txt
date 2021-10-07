cmake_minimum_required(VERSION 3.10.1)

project(sdl_utils LANGUAGES C)

set(_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${_BASE_DIR}/cmake_helpers/find_modules)

if (UNIX)
    set(SDL_image_name "SDL2_image")
    set(SDL_ttf_name "SDL2_ttf")
    set(SDL_mixer_name "SDL2_mixer")
elseif (WIN32)
    set(SDL_image_name "SDL2_IMAGE")
    set(SDL_ttf_name "SDL2_TTF")
    set(SDL_mixer_name "SDL2_MIXER")
else (MACOS)
    set(SDL_image_name "SDL2_image")
    set(SDL_ttf_name "SDL2_ttf")
    set(SDL_mixer_name "SDL2_mixer")
endif ()

#Find package will generate an include dir and a source dir for each package.

find_package(SDL2 REQUIRED)
find_package(${SDL_image_name} REQUIRED)
find_package(${SDL_ttf_name} REQUIRED)
find_package(${SDL_mixer_name} REQUIRED)
#Add later maybe: find_package(SDL2_gfx REQUIRED)


#We need to include SDL2 includes and libraries below too
target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${_HEADERS_DIR}
        PRIVATE
        ${_SOURCES_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        utils
        PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        )

add_library(${PROJECT_NAME}
        STATIC
        ${_HEADERS_DIR}/sdl_methods.h
        ${_HEADERS_DIR}/event_poll.h

        ${_SOURCES_DIR}/sdl_methods.c
        ${_SOURCES_DIR}/event_poll.c
)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})