cmake_minimum_required(VERSION 3.10.1)

project(game_engine LANGUAGES C)

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
        ${_HEADERS_DIR}/Actors/BaseCharacter.h
        ${_HEADERS_DIR}/Actors/PlayerCharacter.h
        ${_HEADERS_DIR}/Core/Camera2D.h
        ${_HEADERS_DIR}/Core/GameEngineCore.h
        ${_HEADERS_DIR}/Core/MainGameLoop.h
        ${_HEADERS_DIR}/Core/sdl_default_app_settings.h
        ${_HEADERS_DIR}/Core/sdl_methods.h
        ${_HEADERS_DIR}/GameObject/GameObject2D.h
        ${_HEADERS_DIR}/GameObject/ObjectPool.h
        ${_HEADERS_DIR}/GameObject/Transform2D.h
        ${_HEADERS_DIR}/Graphics/DrawParalaxBackgrounds.h
        ${_HEADERS_DIR}/Managers/GameObjectManager.h
        ${_HEADERS_DIR}/Graphics/GraphicsRenderer2D.h
        ${_HEADERS_DIR}/Graphics/ImageLayers.h
        ${_HEADERS_DIR}/Managers/CollisionManager.h
        ${_HEADERS_DIR}/Managers/EventManager.h
        ${_HEADERS_DIR}/Managers/TextureManager.h
        ${_HEADERS_DIR}/Managers/WindowManager.h
        ${_HEADERS_DIR}/Physics/Collider2D.h
        ${_HEADERS_DIR}/Physics/RigidBody2D.h
        ${_HEADERS_DIR}/Physics/Vector2D.h
        ${_HEADERS_DIR}/Timers/Timers.h

        ${_SOURCES_DIR}/sdl_methods.c
        ${_SOURCES_DIR}/GameEngineCore.c
        ${_SOURCES_DIR}/GraphicsRenderer2D.c
        ${_SOURCES_DIR}/Vector2D.c
        ${_SOURCES_DIR}/Transform2D.c
        ${_SOURCES_DIR}/GameObject2D.c
        ${_SOURCES_DIR}/BaseCharacter.c
        ${_SOURCES_DIR}/PlayerCharacter.c
        ${_SOURCES_DIR}/RigidBody2D.c
        ${_SOURCES_DIR}/GameObjectManager.c
        ${_SOURCES_DIR}/WindowManager.c
        ${_SOURCES_DIR}/EventManager.c
        ${_SOURCES_DIR}/TextureManager.c
        ${_SOURCES_DIR}/ObjectPool.c
        ${_SOURCES_DIR}/Timers.c
        ${_SOURCES_DIR}/Collider2D.c
        ${_SOURCES_DIR}/CollisionManager.c
        ${_SOURCES_DIR}/ImageLayers.c
        ${_SOURCES_DIR}/Camera2D.c
        ${_SOURCES_DIR}/MainGameLoop.c
        ${_SOURCES_DIR}/DrawParalaxBackgrounds.c )

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