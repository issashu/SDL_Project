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


add_library(${PROJECT_NAME}
        STATIC
        # HEADER FILES HERE
        ${_HEADERS_DIR}/Actors/BaseCharacter.h
        ${_HEADERS_DIR}/Actors/PlayerCharacter.h
        ${_HEADERS_DIR}/Actors/EnemyCharacter.h

        ${_HEADERS_DIR}/Core/Camera2D.h
        ${_HEADERS_DIR}/Core/GameEngineCore.h
        ${_HEADERS_DIR}/Core/sdl_default_app_settings.h
        ${_HEADERS_DIR}/Core/sdl_methods.h

        ${_HEADERS_DIR}/Core/GameScenes/DeathScreen.h
        ${_HEADERS_DIR}/Core/GameScenes/MainLevel.h
        ${_HEADERS_DIR}/Core/GameScenes/TitleScreen.h

        ${_HEADERS_DIR}/GameObject/GameObject2D.h
        ${_HEADERS_DIR}/GameObject/ObjectPool.h
        ${_HEADERS_DIR}/GameObject/Transform2D.h
        ${_HEADERS_DIR}/GameObject/Platforms/BasePlatform2D.h

        ${_HEADERS_DIR}/Graphics/DrawParalaxBackgrounds.h
        ${_HEADERS_DIR}/Graphics/GraphicsRenderer2D.h
        ${_HEADERS_DIR}/Graphics/ImageLayers.h

        ${_HEADERS_DIR}/Managers/CharactersEventManager.h
        ${_HEADERS_DIR}/Managers/CollisionManager.h
        ${_HEADERS_DIR}/Managers/GameObjectManager.h
        ${_HEADERS_DIR}/Managers/GameStateManager.h
        ${_HEADERS_DIR}/Managers/NPCManager.h
        ${_HEADERS_DIR}/Managers/TextureManager.h
        ${_HEADERS_DIR}/Managers/WindowManager.h

        ${_HEADERS_DIR}/Physics/RigidBody2D.h
        ${_HEADERS_DIR}/Physics/Vector2D.h

        ${_HEADERS_DIR}/Timers/Timers.h

        ${_HEADERS_DIR}/Utils/include/Log.h
        ${_HEADERS_DIR}/Utils/include/ErrorCodes.h
        ${_HEADERS_DIR}/Utils/include/containers/Vector.h
        ${_HEADERS_DIR}/Utils/include/vfx_tools/shapes.h
        ${_HEADERS_DIR}/Utils/include/Defines.h

        # SOURCE FILES HERE
        ${_SOURCES_DIR}/Actors/BaseCharacter.c
        ${_SOURCES_DIR}/Actors/EnemyCharacter.c
        ${_SOURCES_DIR}/Actors/PlayerCharacter.c

        ${_SOURCES_DIR}/Core/Camera2D.c
        ${_SOURCES_DIR}/Core/GameEngineCore.c
        ${_SOURCES_DIR}/Core/sdl_methods.c

        ${_SOURCES_DIR}/Core/GameScenes/DeathScreen.c
        ${_SOURCES_DIR}/Core/GameScenes/MainLevel.c
        ${_SOURCES_DIR}/Core/sdl_methods.c
        ${_SOURCES_DIR}/Core/GameScenes/TitleScreen.c


        ${_SOURCES_DIR}/GameObject/GameObject2D.c
        ${_SOURCES_DIR}/GameObject/ObjectPool.c
        ${_SOURCES_DIR}/GameObject/Transform2D.c
        ${_SOURCES_DIR}/GameObject/Platforms/BasePlatform2D.c

        ${_SOURCES_DIR}/Graphics/DrawParalaxBackgrounds.c
        ${_SOURCES_DIR}/Graphics/GraphicsRenderer2D.c
        ${_SOURCES_DIR}/Graphics/ImageLayers.c

        ${_SOURCES_DIR}/Managers/CharactersEventManager.c
        ${_SOURCES_DIR}/Managers/CollisionManager.c
        ${_SOURCES_DIR}/Managers/GameObjectManager.c
        ${_SOURCES_DIR}/Managers/GameStateManager.c
        ${_SOURCES_DIR}/Managers/NPCManager.c
        ${_SOURCES_DIR}/Managers/TextureManager.c
        ${_SOURCES_DIR}/Managers/WindowManager.c

        ${_SOURCES_DIR}/Physics/RigidBody2D.c
        ${_SOURCES_DIR}/Physics/Vector2D.c

        ${_SOURCES_DIR}/Timers/Timers.c

        ${_SOURCES_DIR}/Utils/src/containers/Vector.c
        ${_SOURCES_DIR}/Utils/src/vfx_tools/shapes.c
        )

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
        PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        )

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})