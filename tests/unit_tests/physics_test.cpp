//
// Created by santi on 25/05/24.
//
#define CATCH_CONFIG_MAIN
#include "../../game_engine/physics_engine/physics_object/character_body.h"
#include "../catch.hpp"


TEST_CASE("CharacterBody Initialization", "[CharacterBody]") {
    CharacterBody character(50, 100);

    REQUIRE(character.getWidth() == 50);
    REQUIRE(character.getHeight() == 100);
    REQUIRE(character.get_position() == Vector2D(0, 0));
    REQUIRE(character.getVelocity() == Vector2D(0, 0));
    REQUIRE(character.getAcceleration() == Vector2D(0, 0));
}

TEST_CASE("CharacterBody with default velocity & acceleration values", "[CharacterBody]") {
    CharacterBody character(50, 100, Vector2D(10, 10), Vector2D(20, 20));

    REQUIRE(character.getWidth() == 50);
    REQUIRE(character.getHeight() == 100);
    REQUIRE(character.get_position() == Vector2D(0, 0));
    REQUIRE(character.getVelocity() == Vector2D(10, 10));
    REQUIRE(character.getAcceleration() == Vector2D(20, 20));
}
