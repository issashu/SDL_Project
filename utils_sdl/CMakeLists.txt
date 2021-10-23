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
        ${_HEADERS_DIR}/Core/sdl_methods.h
        ${_HEADERS_DIR}/Core/sdl_event_defines.h
        ${_HEADERS_DIR}/Core/GameEngineCore.h
        ${_HEADERS_DIR}/Graphics/sdl_gfx_renderer.h
        ${_HEADERS_DIR}/Core/sdl_default_app_settings.h
        ${_HEADERS_DIR}/Physics/sdl_vector2D.h
        ${_HEADERS_DIR}/Graphics/sdl_transform2D.h
        ${_HEADERS_DIR}/GameObject/sdl_game_object.h
        ${_HEADERS_DIR}/Actors/sdl_character.h
        ${_HEADERS_DIR}/Physics/sdl_rigidBody2D.h
        ${_HEADERS_DIR}/Managers/GameObjectManager.h
        ${_HEADERS_DIR}/Managers/WindowManager.h
        ${_HEADERS_DIR}/Managers/EventManager.h

        ${_SOURCES_DIR}/sdl_methods.c
        ${_SOURCES_DIR}/GameEngineCore.c
        ${_SOURCES_DIR}/sdl_gfx_renderer.c
        ${_SOURCES_DIR}/sdl_vector2D.c
        ${_SOURCES_DIR}/sdl_transform2D.c
        ${_SOURCES_DIR}/sdl_game_object.c
        ${_SOURCES_DIR}/sdl_character.c
        ${_SOURCES_DIR}/sdl_rigidBody2D.c
        ${_SOURCES_DIR}/GameObjectManager.c
        ${_SOURCES_DIR}/WindowManager.c
        ${_SOURCES_DIR}/EventManager.c)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        ASSETS_PATH="${ASSETS_PATH}"
        )

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

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})