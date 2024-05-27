cmake_minimum_required(VERSION 3.10)

project(tp_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# compilation flags
set(CSTD c17)
set(CXXSTD c++17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
#include_directories(${SDL2PP_INCLUDE_DIRS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CSTD} -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CXXSTD} -D _POSIX_C_SOURCE=200809L")

option(math "Use math.h" ON)
option(threads "Use threads" ON)
option(static "Static compilation" OFF)
option(TESTS "Build tests" OFF)


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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")


file(GLOB_RECURSE SOURCES_CLIENT "client/*.cpp" "client_*.cpp")
file(GLOB_RECURSE SOURCES_SERVER "server/*.cpp" "server_*.cpp")
file(GLOB_RECURSE SOURCES_COMMON "common/*.cpp" "common_*.cpp")
file(GLOB_RECURSE SOURCES_GAME_ENGINE "game_engine/*.cpp" "game_engine_*.cpp" "game_engine/**/*.h")

file(GLOB_RECURSE HEADERS_CLIENT "client/*.h" "client_*.h")
file(GLOB_RECURSE HEADERS_SERVER "server/*.h" "server_*.h")
file(GLOB_RECURSE HEADERS_COMMON "common/*.h" "common_*.h")
file(GLOB_RECURSE HEADERS_GAME_ENGINE "game_engine/*.h" "game_engine_*.h" "game_engine/**/*.h")

if (NOT TESTS)
    add_executable(client ${SOURCES_COMMON} ${SOURCES_CLIENT} ${HEADERS_CLIENT} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE})
    add_executable(server ${SOURCES_COMMON} ${SOURCES_SERVER} ${HEADERS_SERVER} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE})

    target_link_libraries(client SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
    target_link_libraries(server SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)

else ()
    # GRAPHICS TEST
    file(GLOB_RECURSE GRAPHIC_TESTS "tests/graphics/*.cpp" "tests/graphics/**/*.cpp")
    foreach(file ${GRAPHIC_TESTS})
        # Extract the file name without extension to use as the target name
        get_filename_component(target_name ${file} NAME_WE)

        add_executable(${target_name} ${file} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE})
        target_link_libraries(${target_name} SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
    endforeach()
endif()

if (DEFINED TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

    add_executable(server-tsan ${SOURCES_SERVER} ${SOURCES_COMMON})
endif()

if (verbose)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()