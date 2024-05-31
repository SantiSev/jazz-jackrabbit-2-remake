//
// Created by santi on 25/05/24.
//
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../game_engine/physics_engine/collision_manager.h"
#include "../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../../game_engine/physics_engine/physics_object/static_body.h"



TEST_CASE("ColisionManager with a static body", "[ColisionManager]") {

    CollisionManager collision_manager(100, 100);

    std::shared_ptr<StaticBody> body = std::make_shared<StaticBody>(50,50,10,10);

    collision_manager.add_object(body);

    for (int x = 50; x < 60; ++x) {
        for (int y = 50; y < 60; ++y) {
            auto obj = collision_manager.get_collision_object_at(x, y);
            REQUIRE(obj == body);
        }
    }
}

// create a test that places a static body in the collision manager and then removes it

TEST_CASE("ColisionManager with a static body, then remove it", "[ColisionManager]") {
    CollisionManager collision_manager(100, 100);

    std::shared_ptr<StaticBody> body = std::make_shared<StaticBody>(50,50,10,10);

    collision_manager.add_object(body);

    collision_manager.remove_object(body);

    // Ensure the object is removed
    for (int x = 50; x < 60; ++x) {
        for (int y = 50; y < 60; ++y) {
            auto obj = collision_manager.get_collision_object_at(x, y);
            REQUIRE(obj == nullptr); // Assuming get_collision_object_at returns nullptr if no object is present
        }
    }
}

TEST_CASE("Check colision everywhere else other than the current place", "[ColisionManager]") {
    CollisionManager collision_manager(100, 100);

    std::shared_ptr<StaticBody> body = std::make_shared<StaticBody>(0,0,10,10);

    collision_manager.add_object(body);

    for (int x = 11; x < 100; ++x) {
        for (int y = 11; y < 100; ++y) {
            auto obj = collision_manager.get_collision_object_at(x, y);
            REQUIRE(obj == nullptr);
        }
    }
}


TEST_CASE("Update object position using move_horizontal", "[DynamicBody]") {

    int game_time = 0; // Assuming the game time is 10 ms
    int expected_position = 51;
    auto body = std::make_shared<DynamicBody>(50, 50, 10, 10, Vector2D(1, 1), Vector2D(0, 0));

    // simulate the game loop
    while (game_time != 10 ) {
        body->move_horizontal(1); // Move the object horizontally by 1 unit
        REQUIRE(body->get_position().get_x() == expected_position); // The object should have moved 10 units to the right
        expected_position += 1;
        game_time += 1;
    }

    REQUIRE(body->get_position().get_x() == 60); // The object should have moved 10 units to the right

}

TEST_CASE("Update object position using move_vertical", "[DynamicBody]") {

    int game_time = 0; // Assuming the game time is 10 ms
    int expected_position = 51;
    auto body = std::make_shared<DynamicBody>(50, 50, 10, 10, Vector2D(1, 1), Vector2D(0, 0));

    // simulate the game loop
    while (game_time != 10 ) {
        body->move_vertical(1); // Move the object vertically by 1 unit
        REQUIRE(body->get_position().get_y() == expected_position); // The object should have moved 1 unit to the vertically
        expected_position += 1;
        game_time += 1;
    }

    REQUIRE(body->get_position().get_y() == 60); // The object should have moved 10 units to the right

}

TEST_CASE("Update object position using parabolic movement", "[DynamicBody]") {

    int game_time = 0; // Assuming the game time is 10 ms
    Vector2D expected_position = Vector2D(50,50);
    auto body = std::make_shared<DynamicBody>(50, 50, 10, 10, Vector2D(1, 1), Vector2D(0, 0));

    // simulate the game loop
    while (game_time != 10 ) {
        body->move_vertical(1); // Move the object vertically by 1 unit
        body->move_horizontal(1); // Move the object horizontally by 1 unit
        expected_position += Vector2D(1,1);
        REQUIRE(body->get_position() == expected_position); // The object should have moved 1 unit to the vertically
        game_time += 1;
    }

    REQUIRE(body->get_position().get_x() == expected_position.get_x());
    REQUIRE(body->get_position().get_y() == expected_position.get_y());
}

TEST_CASE("Update object position and see its values updated in collisionManager", "[CollisionManager]") {

    CollisionManager collision_manager(1000, 1000);

    auto body = std::make_shared<DynamicBody>(50, 50, 10, 10, Vector2D(1, 1), Vector2D(0, 0), collision_manager);

    // add body to collision_manager
    collision_manager.add_object(body);

    // get value and compare positions
    auto get_body = collision_manager.get_collision_object_at(50, 50);

    REQUIRE(body == get_body);

    // update the position of the object
    body->move_horizontal(100); // Move the object horizontally by 1 unit
    //collision_manager.update_object(body);

    // get value and compare positions
    auto should_be_empty_body = collision_manager.get_collision_object_at(50, 50);

    std::cout << should_be_empty_body << std::endl;


}