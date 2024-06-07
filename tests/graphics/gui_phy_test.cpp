#include <iostream>

#include "../../game_engine/controllers/keyboard.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/color_rect.h"
#include "../../game_engine/physics_engine/collision_manager.h"
#include "../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../../game_engine/physics_engine/physics_object/static_body.h"

class Player: public DynamicBody, public engine::CanvasObject {
private:
    engine::ColorRect color_rect;
    float base_speed = 10;
    int jump_force = 25;
    int gravity = 1;
    float friction = 0.1f;
    bool on_floor = true;
    bool is_jumping = false;
    int direction = 1;


public:
    // create a method that prints the position of the player and the velocity
    void print_position() {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Position: " << position.x << ", " << position.y << std::endl;
        std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
    }

    void update_color_rect() { color_rect.set_position(position.x, position.y); }

    void update_db() override {

        if (!on_floor) {
            velocity.y += gravity;

        } else {
            velocity.x -= friction * direction;
        }


        position += velocity;

        print_position();
    }


    void handle_colision(CollisionObject& other) override {

        if (is_touching_bool(other)) {
            velocity.y = 10;
            on_floor = true;
        }
    }


    void jump() {
        on_floor = false;
        velocity.y = -jump_force;
    }

    Player(int x, int y, int width, int height, engine::ColorRect& color_rect):
            DynamicBody(x, y, width, height, Vector2D(0, 10)), color_rect(color_rect) {}

    void on_key_press(SDL_Keycode key) override {

        switch (key) {
            case SDLK_a:
                direction = -1;
                velocity.x = -base_speed;
                break;
            case SDLK_d:
                direction = 1;
                velocity.x = base_speed;
                break;
            case SDLK_w:
                if (on_floor)
                    jump();
                break;
            default:
                velocity.x = 0;
                break;
        }
    }

    void draw(SDL_Renderer* renderer) override { color_rect.draw(renderer); }

    void set_position(int x, int y) override {}
    bool is_intersecting(SDL_Point& point) const override { return false; }
    bool is_intersecting(SDL_Rect& rect) const override { return false; }
};

class Platform: public StaticBody, public engine::CanvasObject {
private:
    engine::ColorRect color_rect;

public:
    Platform(int x, int y, int width, int height, engine::ColorRect& color_rect):
            StaticBody(x, y, width, height), color_rect(color_rect) {}

    void draw(SDL_Renderer* renderer) override { color_rect.draw(renderer); }

    void set_position(int x, int y) override {}

    bool is_intersecting(SDL_Point& point) const override { return false; }
    bool is_intersecting(SDL_Rect& rect) const override { return false; }
};

int main() {
    engine::Window window(1600, 800, true, true);
    auto renderer = window.getRenderer();

    CollisionManager collision_manager(1600, 800);

    SDL_Rect rect = {0, 500, 1600, 400};
    engine::ColorRect color_rect({255, 0, 0, 255}, rect);
    auto platform = std::make_shared<Platform>(0, 500, 1600, 400, color_rect);

    SDL_Rect rect_2 = {800, 300, 100, 50};
    engine::ColorRect color_rect_2({0, 255, 0, 255}, rect_2);
    auto platform_2 = std::make_shared<Platform>(800, 300, 100, 50, color_rect_2);

    SDL_Rect rect_3 = {1000, 100, 100, 800};
    engine::ColorRect color_rect_3({0, 255, 255, 255}, rect_3);
    auto platform_3 = std::make_shared<Platform>(1000, 100, 100, 800, color_rect_3);

    SDL_Rect player_cube = {100, 200, 50, 50};
    engine::ColorRect color_player({0, 255, 0, 255}, player_cube);
    auto player = std::make_shared<Player>(100, 200, 50, 50, color_player);

    collision_manager.add_dynamic_body(player);
    collision_manager.add_object(platform);
    collision_manager.add_object(platform_2);
    collision_manager.add_object(platform_3);

    engine::Keyboard keyboard;
    keyboard.add_on_key_down_signal_obj(player.get());

    SDL_Event event;
    bool running = true;

    Uint32 frame_start = 0;
    int frame_time = 0;
    const int frame_delay = 1000 / 60;

    while (running) {
        frame_start = SDL_GetTicks();

        // Updates
        collision_manager.update();
        player->update_color_rect();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            keyboard.update(event);
        }
        window.clear();

        // Draw
        player->draw(renderer);
        platform->draw(renderer);
        platform_2->draw(renderer);
        platform_3->draw(renderer);

        window.render();

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {  // Delay to achieve 60 fps
            SDL_Delay(frame_delay - frame_time);
        }
    }

    return 0;
}
