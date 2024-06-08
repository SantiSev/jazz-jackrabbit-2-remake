#include <iostream>

#include "../../game_engine/controllers/keyboard.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/color_rect.h"
#include "../../game_engine/physics_engine/collision_manager.h"
#include "../../server/game_logic/characters/player.h"
#include "../../server/game_logic/platforms/box_platform.h"

class PlayerTest: public Player, public engine::CanvasObject {

private:
    engine::ColorRect& color_rect;


public:
    PlayerTest(size_t id, std::string name, const uint8_t& character, int x, int y,
               CollisionManager& collision_manager, engine::ColorRect& color_rect):
            Player(id, name, character, x, y, collision_manager), color_rect(color_rect) {}

    void draw(SDL_Renderer* renderer) override { color_rect.draw(renderer); }

    // create a method that prints the position of the player and the velocity
    void print_position() {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Position: " << position.x << ", " << position.y << std::endl;
        std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
    }

    void update_color_rect() { color_rect.set_position(position.x, position.y); }

    void on_key_press(const SDL_Keycode& key) override {

        switch (key) {
            case SDLK_a:
                move_left();
                break;
            case SDLK_d:
                move_right();
                break;
            case SDLK_w:
                jump();
                break;
            default:
                velocity.x = 0;
                break;
        }
    }

    void set_position(int x, int y) override {}
    bool is_intersecting(SDL_Point& point) const override { return false; }
    bool is_intersecting(SDL_Rect& rect) const override { return false; }
};


class PlatformTest: public BoxPlatform, public engine::CanvasObject {
private:
    engine::ColorRect color_rect;

public:
    PlatformTest(int x, int y, int width, int height, engine::ColorRect& color_rect):
            BoxPlatform(x, y, width, height), color_rect(color_rect) {}

    void draw(SDL_Renderer* renderer) override { color_rect.draw(renderer); }

    void set_position(int x, int y) override {}

    bool is_intersecting(SDL_Point& point) const override { return false; }
    bool is_intersecting(SDL_Rect& rect) const override { return false; }
};


int main() {
    engine::Window window(1600, 800, true, true);
    auto renderer = window.get_renderer();

    CollisionManager collision_manager(1600, 800);

    SDL_Rect rect = {0, 500, 1600, 400};
    engine::ColorRect color_rect({255, 0, 0, 255}, rect);
    auto platform = std::make_shared<PlatformTest>(0, 500, 1600, 400, color_rect);

    SDL_Rect rect_2 = {800, 300, 100, 50};
    engine::ColorRect color_rect_2({0, 255, 0, 255}, rect_2);
    auto platform_2 = std::make_shared<PlatformTest>(800, 300, 100, 50, color_rect_2);

    SDL_Rect rect_3 = {1000, 100, 100, 800};
    engine::ColorRect color_rect_3({0, 255, 255, 255}, rect_3);
    auto platform_3 = std::make_shared<PlatformTest>(1000, 100, 100, 800, color_rect_3);

    SDL_Rect player_cube = {100, 200, 50, 50};
    engine::ColorRect color_player({0, 255, 0, 255}, player_cube);
    auto player =
            std::make_shared<PlayerTest>(1, "player", 1, 100, 200, collision_manager, color_player);

    collision_manager.track_dynamic_body(player);
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
