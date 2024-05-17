cmake_minimum_required(VERSION 3.10)

project(tp_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CSTD c17)
set(CXXSTD c++17)

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")

file(GLOB_RECURSE SOURCES_CLIENT "client_src/*.cpp" "client_*.cpp")
file(GLOB_RECURSE SOURCES_SERVER "server_src/*.cpp" "server_*.cpp")
file(GLOB_RECURSE SOURCES_COMMON "common_src/*.cpp" "common_*.cpp")
file(GLOB_RECURSE SOURCES_GAME_ENGINE "game_engine_src/*.cpp" "game_engine_src*.cpp")

file(GLOB_RECURSE HEADERS_CLIENT "client_src/*.h" "client_*.h")
file(GLOB_RECURSE HEADERS_SERVER "server_src/*.h" "server_*.h")
file(GLOB_RECURSE HEADERS_COMMON "common_src/*.h" "common_*.h")
file(GLOB_RECURSE HEADERS_GAME_ENGINE "game_engine_src/*.h" "game_engine_src*.h")


add_executable(client ${SOURCES_COMMON} ${SOURCES_CLIENT} ${HEADERS_CLIENT} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE} )
add_executable(server ${SOURCES_COMMON} ${SOURCES_SERVER} ${HEADERS_SERVER} ${HEADERS_COMMON})


if (DEFINED TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

    add_executable(server-tsan ${SOURCES_SERVER} ${SOURCES_COMMON})
endif()

#add_custom_target(clean COMMAND ${CMAKE_COMMAND} -E rm -f client_src server_src server_src-tsan)
#add_custom_target(zip ALL COMMAND ${CMAKE_COMMAND} -E tar "cvf" "entrega.zip" --format=zip ./common_src ./server_src ./client_src)

if (verbose)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()