cmake_minimum_required(VERSION 3.10)

project(tp_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# compilation flags
set(CSTD c17)
set(CXXSTD c++17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")

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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")

file(GLOB_RECURSE SOURCES_CLIENT "client/*.cpp")
file(GLOB_RECURSE SOURCES_SERVER "server/*.cpp")
file(GLOB_RECURSE SOURCES_COMMON "common/*.cpp")
file(GLOB_RECURSE SOURCES_GAME_ENGINE "game_engine/*.cpp" "game_engine_*.cpp")

file(GLOB_RECURSE HEADERS_CLIENT "client/*.h" "client_*.h")
file(GLOB_RECURSE HEADERS_SERVER "server/*.h" "server/game_logic/*.h" "server_*.h")
file(GLOB_RECURSE HEADERS_COMMON "common/*.h" "common_*.h")
file(GLOB_RECURSE HEADERS_GAME_ENGINE "game_engine/*.h" "game_engine_*.h")

add_executable(client client/client_main.cpp ${SOURCES_COMMON} ${SOURCES_CLIENT} ${HEADERS_CLIENT} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE} )
add_executable(server server/server_main.cpp ${SOURCES_COMMON} ${SOURCES_SERVER} ${HEADERS_SERVER} ${HEADERS_COMMON})

# COMMUNICATION - TESTS
file(GLOB_RECURSE SOURCES_CLIENT_T "client/protocol/*.cpp")
file(GLOB_RECURSE SOURCES_SERVER_T "server/protocol/*.cpp")

add_executable(client_test_one tests/events/client_to_server/client_main.cpp 
    ${SOURCES_COMMON} 
    ${SOURCES_CLIENT_T} 
    ${HEADERS_CLIENT} 
    ${HEADERS_COMMON}
)
add_executable(server_test_one tests/events/client_to_server/server_main.cpp 
    ${SOURCES_COMMON} 
    ${SOURCES_SERVER_T} 
    ${HEADERS_SERVER} 
    ${HEADERS_COMMON}
)

add_executable(client_test_two tests/events/server_to_client/client_main.cpp 
    ${SOURCES_COMMON} 
    ${SOURCES_CLIENT_T} 
    ${HEADERS_CLIENT} 
    ${HEADERS_COMMON}
)
add_executable(server_test_two tests/events/server_to_client/server_main.cpp 
    ${SOURCES_COMMON} 
    ${SOURCES_SERVER_T} 
    ${HEADERS_SERVER} 
    ${HEADERS_COMMON}
)

add_executable(client ${SOURCES_COMMON} ${SOURCES_CLIENT} ${HEADERS_CLIENT} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE}
        game_engine/physics_engine/colision_object/colision_box.h
        game_engine/physics_engine/colision_object/colision_object.cpp
        game_engine/physics_engine/colision_object/colision_box.cpp
        game_engine/physics_engine/area_object/area_object.cpp
        game_engine/physics_engine/area_object/area_object.h
)

add_executable(server ${SOURCES_COMMON} ${SOURCES_SERVER} ${HEADERS_SERVER} ${HEADERS_COMMON})
target_link_libraries(client SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)

# GRAPHICS TEST
add_executable(graphics_test tests/graphics/graphics_test.cpp)
target_link_libraries(graphics_test SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)

if (DEFINED TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

    add_executable(server-tsan ${SOURCES_SERVER} ${SOURCES_COMMON})
endif()

if (verbose)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

find_package(Catch2 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests ${SOURCES_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_COMMON} ${HEADERS_GAME_ENGINE} ${HEADERS_SERVER} ${HEADERS_CLIENT}
        tests/unit_tests/physics_test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)