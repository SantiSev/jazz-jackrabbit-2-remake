cmake_minimum_required(VERSION 3.10)

project(tp_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# compilation flags
set(CXXSTD c++17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CXXSTD} -D _POSIX_C_SOURCE=200809L")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

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

file(GLOB_RECURSE SOURCES_CLIENT "client/*.cpp" "client/**/*.cpp")
file(GLOB_RECURSE SOURCES_SERVER "server/*.cpp" "sever/**/*.cpp")
file(GLOB_RECURSE SOURCES_COMMON "common/*.cpp" "common/**/*.cpp")
file(GLOB_RECURSE SOURCES_GAME_ENGINE "game_engine/*.cpp" "game_engine/**/*.cpp")

file(GLOB_RECURSE HEADERS_CLIENT "client/*.h" "client/**/*.h")
file(GLOB_RECURSE HEADERS_SERVER "server/*.h" "server/**/*.h")
file(GLOB_RECURSE HEADERS_COMMON "common/*.h" "common/**/*.h")
file(GLOB_RECURSE HEADERS_GAME_ENGINE "game_engine/*.h" "game_engine/**/*.h")

file(GLOB_RECURSE SERVER_WITHOUT_MAIN "server/game_logic/*.cpp" "server/protocol/*.cpp" "server/match.cpp" "server/match.h")
file(GLOB_RECURSE CLIENT_WITHOUT_MAIN "client/protocol/*.cpp" "client/protocol/*.h")

if (NOT TESTS)
    add_executable(client ${SOURCES_COMMON} ${SOURCES_CLIENT} ${HEADERS_CLIENT} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE} ${SERVER_WITHOUT_MAIN})
    add_executable(server ${SOURCES_COMMON} ${SOURCES_SERVER} ${HEADERS_SERVER} ${HEADERS_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE} ${CLIENT_WITHOUT_MAIN})

    target_link_libraries(client 
        SDL2main 
        SDL2::SDL2 
        SDL2_image::SDL2_image 
        SDL2_ttf::SDL2_ttf 
        SDL2_mixer
    )
    target_link_libraries(server 
        SDL2main 
        SDL2::SDL2 
        SDL2_image::SDL2_image 
        SDL2_ttf::SDL2_ttf 
        SDL2_mixer::SDL2_mixer
    )

else ()
    # COMMUNICATION - TESTS
    file(GLOB_RECURSE SOURCES_CLIENT_PROTOCOL "client/protocol/*.cpp")
    file(GLOB_RECURSE SOURCES_SERVER_PROTOCOL "server/protocol/*.cpp")
    file(GLOB_RECURSE SOURCES_SERVER_GAME_LOGIC "server/game_logic/*.cpp")

    add_executable(client_test_one tests/events/client_to_server/client_main.cpp
    ${SOURCES_COMMON}
    ${SOURCES_CLIENT_PROTOCOL}
    ${SOURCES_SERVER_PROTOCOL}
    ${SOURCES_SERVER_GAME_LOGIC}
    ${HEADERS_CLIENT}
    ${HEADERS_SERVER}
    ${HEADERS_COMMON}
    )
    add_executable(server_test_one tests/events/client_to_server/server_main.cpp
    ${SOURCES_COMMON}
    ${SOURCES_CLIENT_PROTOCOL}
    ${SOURCES_SERVER_PROTOCOL}
    ${SOURCES_SERVER_GAME_LOGIC}
    ${HEADERS_CLIENT}
    ${HEADERS_SERVER}
    ${HEADERS_COMMON}
    )

    add_executable(client_test_two tests/events/server_to_client/client_main.cpp
    ${SOURCES_COMMON}
    ${SOURCES_CLIENT_PROTOCOL}
    ${SOURCES_SERVER_PROTOCOL}
    ${SOURCES_SERVER_GAME_LOGIC}
    ${HEADERS_CLIENT}
    ${HEADERS_SERVER}
    ${HEADERS_COMMON}
    )
    add_executable(server_test_two tests/events/server_to_client/server_main.cpp
    ${SOURCES_COMMON}
    ${SOURCES_CLIENT_PROTOCOL}
    ${SOURCES_SERVER_PROTOCOL}
    ${SOURCES_SERVER_GAME_LOGIC}
    ${HEADERS_CLIENT}
    ${HEADERS_SERVER}
    ${HEADERS_COMMON}
    )

    # GRAPHICS TEST
    file(GLOB_RECURSE GRAPHIC_TESTS "tests/graphics/*.cpp" "tests/graphics/**/*.cpp")
    foreach(file ${GRAPHIC_TESTS})
        # Extract the file name without extension to use as the target name
        get_filename_component(target_name ${file} NAME_WE)

        add_executable(${target_name} ${file} ${SOURCES_GAME_ENGINE} ${HEADERS_GAME_ENGINE})
        target_link_libraries(${target_name} SDL2main SDL2 SDL2_image::SDL2_image SDL2_ttf SDL2_mixer)
    endforeach()
endif()

if (DEFINED TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

    add_executable(server-tsan ${SOURCES_SERVER} ${SOURCES_COMMON}
    game_engine/physics_engine/collision_manager.h
    game_engine/physics_engine/colision_object.h)

endif()

if (verbose)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

#find_package(Catch2 REQUIRED)
# These tests can use the Catch2-provided main
#add_executable(tests ${SOURCES_COMMON} ${SOURCES_GAME_ENGINE} ${HEADERS_COMMON} ${HEADERS_GAME_ENGINE} ${HEADERS_SERVER} ${HEADERS_CLIENT}
#        tests/unit_tests/physics_test.cpp)
#target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
