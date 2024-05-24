cmake_minimum_required(VERSION 3.10)

project(tp_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
#set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
#set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
#set(SDL2PP_WITH_IMAGE YES)
#set(SDL2PP_WITH_TTF YES)
#add_subdirectory(extlib/SDL2pp)

# compilation flags
set(CSTD c17)
set(CXXSTD c++17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
#include_directories(${SDL2PP_INCLUDE_DIRS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CSTD} -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CXXSTD} -D _POSIX_C_SOURCE=200809L")

option(math "Usar funciones de math.h" ON)
option(threads "Usar threads" ON)
option(static "Compilar estáticamente" OFF)


if (math)
    set(LDFLAGS "${LDFLAGS} -lm")
endif()

if (threads)
    set(LDFLAGS "${LDFLAGS} -pthread")
endif()

if (static)
    set(LDFLAGS "${LDFLAGS} -static")
endif()

# define targets
#add_executable(client)
#target_link_libraries(client PUBLIC libSDL2pp)
#target_link_libraries(client SDL2pp::SDL2pp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")

file(GLOB_RECURSE SOURCES_CLIENT "client/*.cpp" "client_*.cpp")
file(GLOB_RECURSE SOURCES_SERVER "server/*.cpp" "server_*.cpp")
file(GLOB_RECURSE SOURCES_COMMON "common/*.cpp" "common_*.cpp")
file(GLOB_RECURSE SOURCES_GAME_ENGINE "game_engine/*.cpp" "game_engine_*.cpp")

file(GLOB_RECURSE HEADERS_CLIENT "client/*.h" "client_*.h")
file(GLOB_RECURSE HEADERS_SERVER "server/*.h" "server_*.h")
file(GLOB_RECURSE HEADERS_COMMON "common/*.h" "common_*.h")
file(GLOB_RECURSE HEADERS_GAME_ENGINE "game_engine/*.h" "game_engine_*.h")


add_executable(client ${SOURCES_COMMON} ${SOURCES_CLIENT} ${HEADERS_CLIENT} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE}
        game_engine/physics_engine/physics_engine.cpp
        game_engine/physics_engine/physics_engine.h
        game_engine/math/vector2D.cpp
        game_engine/math/vector2D.h
        game_engine/math/vector2D.h
        game_engine/math/vector2D.cpp
        game_engine/physics_engine/rigid_body/rigid_body.cpp
        game_engine/physics_engine/rigid_body/rigid_body.h
        game_engine/physics_engine/physics_engine.cpp
        game_engine/physics_engine/physics_engine.h
        game_engine/physics_engine/physics_object/physics_object.cpp
        game_engine/physics_engine/physics_object/physics_object.h
        game_engine/physics_engine/static_body/static_body.cpp
        game_engine/game_object.h
        game_engine/colision_object.h
        game_engine/colision_shape.h
        game_engine/physics_engine/physics_object/character_body.cpp
        game_engine/physics_engine/physics_object/character_body.h
        game_engine/physics_engine/physics_object/static_body.cpp
        game_engine/physics_engine/physics_object/static_body.h
        game_engine/physics_engine/physics_object/physics_object.cpp
        game_engine/physics_engine/physics_object/physics_object.h
        game_engine/shapes/square.h
        game_engine/shapes/triangle.h
        game_engine/physics_engine/area_object/item_object.cpp
        game_engine/physics_engine/area_object/item_object.h
)
add_executable(server ${SOURCES_COMMON} ${SOURCES_SERVER} ${HEADERS_SERVER} ${HEADERS_COMMON}
        game_engine/math/vector2D.h
        game_engine/math/vector2D.cpp)


if (DEFINED TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

    add_executable(server-tsan ${SOURCES_SERVER} ${SOURCES_COMMON}
            game_engine/math/vector2D.h
            game_engine/math/vector2D.cpp)
endif()

if (verbose)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()