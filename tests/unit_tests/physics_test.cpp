//
// Created by santi on 25/05/24.
//
#define CATCH_CONFIG_MAIN
#include <iostream>

#include "../../game_engine/physics_engine/collision_manager.h"
#include "../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../../game_engine/physics_engine/physics_object/static_body.h"
#include "../catch.hpp"

#define PRINT_DEBUG(message)                                                                      \
    std::cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << " (" << __func__ << "): " << message \
              << std::endl


TEST_CASE("ColisionManager with a static body", "[ColisionManager]") {

    CollisionManager collision_manager(100, 100);

    std::shared_ptr<StaticBody> body = std::make_shared<StaticBody>(50, 50, 10, 10);

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

    std::shared_ptr<StaticBody> body = std::make_shared<StaticBody>(50, 50, 10, 10);

    collision_manager.add_object(body);

    collision_manager.remove_object(body);

    // Ensure the object is removed
    for (int x = 50; x < 60; ++x) {
        for (int y = 50; y < 60; ++y) {
            auto obj = collision_manager.get_collision_object_at(x, y);
            REQUIRE(obj == nullptr);  // Assuming get_collision_object_at returns nullptr if no
                                      // object is present
        }
    }
}

TEST_CASE("Check colision everywhere else other than the current place", "[ColisionManager]") {
    CollisionManager collision_manager(100, 100);

    std::shared_ptr<StaticBody> body = std::make_shared<StaticBody>(0, 0, 10, 10);

    collision_manager.add_object(body);  // the CM will now track body

    for (int x = 11; x < 100; ++x) {
        for (int y = 11; y < 100; ++y) {
            auto obj = collision_manager.get_collision_object_at(x, y);
            REQUIRE(obj == nullptr);
        }
    }
}


TEST_CASE("Update object position using move_horizontal", "[DynamicBody]") {

    CollisionManager collision_manager(1000, 1000);

    int expected_position = 50;
    auto body = std::make_shared<DynamicBody>(
            50, 50, 10, 10, Vector2D(1, 1),
            Vector2D(0, 0));  // Create a dynamic body at position 50,50

    collision_manager.add_object(body);  // Add the object to the collision manager

    auto no_body = collision_manager.get_collision_object_at(expected_position + 10, 50);
    REQUIRE(no_body == nullptr);  // currenty there is nothing at (60, 50), our object is at (50,50)

    REQUIRE(body->get_position().get_x() == expected_position);  // now our body is at (50,50)
    body->move_horizontal(
            10);  // Move the object horizontally by 10 unit, now our body should be at (60,50)
    REQUIRE(body->get_position().get_x() ==
            expected_position + 10);  // now our body should be at (60,50)

    collision_manager.update_dynamic_object(body);  // update the object in the collision manager

    auto get_body = collision_manager.get_collision_object_at(
            expected_position + 10, 50);  // get the object at the new position

    REQUIRE(get_body == body);  // make sure that the body i got is the same as my existing body

    REQUIRE(get_body->get_position().get_x() ==
            expected_position + 10);  // make sure that the body i got is at the correct position
}

TEST_CASE("Push Dynamic Object into a wall", "[DynamicBody]") {

    CollisionManager collision_manager(1000, 1000);
    int Y = 10;  // Y axis remains constant because we are only moving horizontally
    int expected_position = 50;
    auto dynamic_body = std::make_shared<DynamicBody>(
            expected_position, Y, 10,
            10);  // Create a dynamic body at position 50,Y and speed of 1
    auto static_body = std::make_shared<StaticBody>(expected_position + 10, Y, 10,
                                                    10);  // Create a static body at position 60,Y

    collision_manager.add_object(dynamic_body);  // Add the object to the collision manager
    collision_manager.add_object(static_body);   // Add the object to the collision manager

    // tracking start!
    // since i want to move the dynamic body into the wall, i need to make sure that if the DO
    // toches the wall then it's position sould be in the left index of the wall

    // iterate move_horizontal 10 times
    for (int i = 0; i < 10; ++i) {
        dynamic_body->move_horizontal(1);  // Move the object horizontally by 1 unit
        collision_manager.update_dynamic_object(
                dynamic_body);  // update the object in the collision manager
    }

    REQUIRE(dynamic_body->get_position().get_x() ==
            expected_position);  // now our body should be at (50,10) since its pushing against a
                                 // wall
}

TEST_CASE("Push Dynamic Object out of bounds", "[CollisionManager]") {

    CollisionManager collision_manager(1000, 1000);
    int Y = 10;                   // Y axis remains constant because we are only moving horizontally
    int expected_position = 990;  // the object is currenty at the right edge of the grid
    auto dynamic_body = std::make_shared<DynamicBody>(
            expected_position, Y, 10,
            10);  // Create a dynamic body at position 990,Y and speed of 1

    collision_manager.add_object(dynamic_body);  // Add the object to the collision manager

    // tracking start!
    // by attempting to push the dynamic body out of bounds, the body should be at the right edge of
    // the grid

    // iterate move_horizontal 10 times
    for (int i = 0; i < 10; ++i) {
        dynamic_body->move_horizontal(1);  // Move the object horizontally by 1 unit
        collision_manager.update_dynamic_object(
                dynamic_body);  // update the object in the collision manager
    }

    REQUIRE(dynamic_body->get_position().get_x() ==
            collision_manager.get_grid_width() -
                    dynamic_body
                            ->get_hitbox_width());  // now our body true position should be still at
                                                    // 990,Y since the objects width is of 10
}

TEST_CASE("Move multiple dynamic objects", "[DynamicBody]") {

    CollisionManager collision_manager(1000, 1000);
    int x_1 = 50;
    int y_1 = 10;
    int x_2 = x_1 + 20;
    int y_2 = 10;

    auto dynamic_body_1 = std::make_shared<DynamicBody>(
            x_1, y_1, 10,
            10);  // Create a dynamic body at position 50,Y and speed of 1

    auto dynamic_body_2 = std::make_shared<DynamicBody>(
            x_2, y_2, 10,
            10);  // Create a dynamic body at position 50,Y and speed of 1


    collision_manager.add_object(dynamic_body_1);  // Add the object to the collision manager
    collision_manager.add_object(dynamic_body_2);  // Add the object to the collision manager

    // tracking start!

    // iterate move_horizontal 10 times
    for (int i = 0; i < 10; ++i) {

        dynamic_body_1->move_horizontal(1);  // Move the object horizontally by 1 unit
        dynamic_body_2->move_vertical(1);    // Move the object horizontally by 1 unit


        collision_manager.update_dynamic_object(
                dynamic_body_1);  // update the object in the collision manager
        collision_manager.update_dynamic_object(
                dynamic_body_2);  // update the object in the collision manager
    }

    REQUIRE(dynamic_body_1->get_position().get_x() == x_1 + 10);
    REQUIRE(dynamic_body_1->get_position().get_y() == y_1);
    REQUIRE(dynamic_body_2->get_position().get_x() == x_2);
    REQUIRE(dynamic_body_2->get_position().get_y() == y_2 + 10);

    auto get_body_1 = collision_manager.get_collision_object_at(x_1 + 10, y_1);
    auto get_body_2 = collision_manager.get_collision_object_at(x_2, y_2 + 10);

    REQUIRE(dynamic_body_1 == get_body_1);
    REQUIRE(dynamic_body_2 == get_body_2);
}

TEST_CASE("Move dynamic from left to right", "[DynamicBody]") {

    CollisionManager collision_manager(1000, 1000);
    int x_1 = 50;
    int y_1 = 10;

    auto dynamic_body = std::make_shared<DynamicBody>(
            x_1, y_1, 10,
            10);  // Create a dynamic body at position 50,Y and speed of 1

    collision_manager.add_object(dynamic_body);  // Add the object to the collision manager

    // tracking start!

    // iterate move_horizontal 10 times
    for (int i = 0; i < 10; ++i) {

        dynamic_body->move_horizontal(1);  // Move the object horizontally to the right by 1 unit

        collision_manager.update_dynamic_object(
                dynamic_body);  // update the object in the collision manager
    }

    auto get_body_moved_right = collision_manager.get_collision_object_at(x_1 + 10, y_1);
    auto get_body_origin_point = collision_manager.get_collision_object_at(x_1, y_1);

    REQUIRE(dynamic_body->get_position().get_x() == x_1 + 10);
    REQUIRE(dynamic_body == get_body_moved_right);
    REQUIRE(get_body_origin_point == nullptr);

    for (int i = 0; i < 20; ++i) {

        dynamic_body->move_horizontal(-1);  // Move the object horizontally to the left by 1 unit

        collision_manager.update_dynamic_object(
                dynamic_body);  // update the object in the collision manager
    }

    auto get_body_moved_left = collision_manager.get_collision_object_at(x_1 - 10, y_1);
    auto get_body_new_origin_point = collision_manager.get_collision_object_at(x_1 + 10, y_1);

    REQUIRE(dynamic_body->get_position().get_x() == x_1 - 10);
    REQUIRE(dynamic_body == get_body_moved_left);
    REQUIRE(get_body_new_origin_point == nullptr);
}

TEST_CASE("Crash Dynamic Objects into each other", "[DynamicBody]") {

    CollisionManager collision_manager(1000, 1000);
    int x_1 = 50;
    int x_2 = 80;
    int Y = 10;

    auto dynamic_body_1 = std::make_shared<DynamicBody>(
            x_1, Y, 10,
            10);  // Create a dynamic body at position 50,Y and speed of 1

    auto dynamic_body_2 = std::make_shared<DynamicBody>(
            x_2, Y, 10,
            10);  // Create a dynamic body at position 50,Y and speed of 1

    collision_manager.add_object(dynamic_body_1);  // Add the object to the collision manager
    collision_manager.add_object(dynamic_body_2);  // Add the object to the collision manager

    // tracking start!

    for (int i = 0; i < 25; ++i) {

        dynamic_body_1->move_horizontal(1);  // Move the object horizontally to the right by 1 unit
        dynamic_body_2->move_horizontal(-1);

        collision_manager.update_dynamic_object(
                dynamic_body_1);  // update the object in the collision manager

        collision_manager.update_dynamic_object(
                dynamic_body_2);  // update the object in the collision manager
    }

    int x_final_1 = dynamic_body_1->get_position().get_x();
    int x_final_2 = dynamic_body_2->get_position().get_x();

    REQUIRE(x_final_1 == 60);
    REQUIRE(x_final_2 == 70);
}
