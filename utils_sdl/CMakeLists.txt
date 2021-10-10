cmake_minimum_required(VERSION 3.10.1)

project(utils_sdl LANGUAGES C)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(_HEADERS_DIR ${_BASE_DIR}/include)
set(_SOURCES_DIR ${_BASE_DIR}/src)

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

#We need to include SDL2 includes and libraries below too
add_library(${PROJECT_NAME}
        STATIC
        ${_HEADERS_DIR}/sdl_methods.h
        ${_HEADERS_DIR}/sdl_event_handler.h
        ${_HEADERS_DIR}/sdl_event_defines.h
        ${_HEADERS_DIR}/sdl_command.h
        ${_HEADERS_DIR}/sdl_gfx_renderer.h

        ${_SOURCES_DIR}/sdl_methods.c
        ${_SOURCES_DIR}/sdl_event_handler.c
        ${_SOURCES_DIR}/sdl_command.c
        ${_SOURCES_DIR}/sdl_gfx_renderer.c
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE
        ASSETS_PATH="${ASSETS_PATH}"
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${_HEADERS_DIR}
        PUBLIC
        #TODO Make 'em private
        ${_SOURCES_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        utils
        PUBLIC
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        )