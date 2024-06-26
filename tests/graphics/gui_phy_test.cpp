// #include <iostream>

// #include "../../game_engine/controllers/keyboard.h"
// #include "../../game_engine/gui/basic/window.h"
// #include "../../game_engine/gui/canvas_object.h"
// #include "../../game_engine/gui/widgets/color_rect.h"
// #include "../../game_engine/physics_engine/collision_manager.h"
// #include "../../server/game_logic/characters/enemy.h"
// #include "../../server/game_logic/characters/player.h"
// #include "../../server/game_logic/collectables/ammo.h"
// #include "../../server/game_logic/collectables/treasure.h"
// #include "../../server/game_logic/platforms/box_platform.h"
// #include "../../server/game_logic/weapons/bullet.h"

// class PlayerTest: public Player, public engine::CanvasObject {

// private:
//     engine::ColorRect color_rect;
//     engine::ColorRect gun_rect;

// public:
//     PlayerTest(size_t id, std::string name, const uint8_t& character, int x, int y,
//                engine::CollisionManager& collision_manager):
//             Player(id, name, JAZZ_CHARACTER, x, y, collision_manager) {

//         SDL_Rect player_cube = {x, y, PLAYER_WIDTH, PLAYER_HEIGHT};
//         SDL_Color color = {0, 255, 0, 255};
//         this->color_rect = engine::ColorRect(color, player_cube);


//         SDL_Rect gun_cube = {x + 50, y + 10, 10, 10};
//         SDL_Color gun_color = {255, 0, 0, 255};
//         this->gun_rect = engine::ColorRect(gun_color, gun_cube);
//     }


//     void draw(SDL_Renderer* renderer, int it) override {
//         color_rect.draw(renderer, it);
//         gun_rect.draw(renderer, it);
//     }

//     void update(int delta) override {
//         color_rect.set_position(position.x, position.y);
//         int gun_dir = position.x;
//         if (direction == 1) {
//             gun_dir += 50;
//         } else {
//             gun_dir -= 10;
//         }

//         gun_rect.set_position(gun_dir, position.y + 10);
//     }

//     void on_key_press(const SDL_Keycode& key) override {

//         switch (key) {
//             case SDLK_a:
//                 move_left();
//                 break;
//             case SDLK_d:
//                 move_right();
//                 break;
//             case SDLK_w:
//                 jump();
//                 break;
//             case SDLK_SPACE:
//                 shoot_selected_weapon();
//                 break;
//             case SDLK_j:
//                 select_next_weapon();
//                 break;
//             default:
//                 velocity.x = 0;
//                 break;
//         }
//     }

//     void set_position(int x, int y) override {}
//     bool is_intersecting(SDL_Point& point) const override { return false; }
//     bool is_intersecting(SDL_Rect& rect) const override { return false; }
// };

// // ----------------------------------------------------------

// class PlatformTest: public BoxPlatform, public engine::CanvasObject {
// private:
//     engine::ColorRect color_rect;

// public:
//     PlatformTest(int x, int y, int width, int height, SDL_Color color_values):
//             BoxPlatform(x, y, width, height) {
//         SDL_Rect platform_cube = {x, y, width, height};
//         this->color_rect = engine::ColorRect(color_values, platform_cube);
//     }

//     void draw(SDL_Renderer* renderer, int it) override { color_rect.draw(renderer, it); }

//     void set_position(int x, int y) override {}

//     bool is_intersecting(SDL_Point& point) const override { return false; }
//     bool is_intersecting(SDL_Rect& rect) const override { return false; }
// };


// class TreasureTest: public Treasure, public engine::CanvasObject {
// private:
//     engine::ColorRect color_rect;

// public:
//     TreasureTest(int x, int y, int width, int height): Treasure(100, x, y, width, height, 100) {
//         SDL_Color color_values = {255, 255, 0, 255};
//         SDL_Rect collectable_cube = {x, y, width, height};
//         this->color_rect = engine::ColorRect(color_values, collectable_cube);
//     }

//     void draw(SDL_Renderer* renderer, int it) override { color_rect.draw(renderer); }

//     void set_position(int x, int y) override {}
//     void update(int delta) override { color_rect.set_position(position.x, position.y); }
//     bool is_intersecting(SDL_Point& point) const override { return false; }
//     bool is_intersecting(SDL_Rect& rect) const override { return false; }
// };

// class AmmoTest: public Ammo, public engine::CanvasObject {
// private:
//     engine::ColorRect color_rect;

// public:
//     AmmoTest(int x, int y, int width, int height): Ammo(1, 50, x, y, width, height, 100) {
//         SDL_Color color_values = {237, 231, 225, 255};
//         SDL_Rect collectable_cube = {x, y, width, height};
//         this->color_rect = engine::ColorRect(color_values, collectable_cube);
//     }

//     void draw(SDL_Renderer* renderer, int it) override { color_rect.draw(renderer); }

//     void set_position(int x, int y) override {}
//     void update(int delta) override { color_rect.set_position(position.x, position.y); }
//     bool is_intersecting(SDL_Point& point) const override { return false; }
//     bool is_intersecting(SDL_Rect& rect) const override { return false; }
// };


// // ----------------------------------------------------------

// class EnemyTest: public Enemy, public engine::CanvasObject {
// private:
//     engine::ColorRect color_rect;

// public:
//     EnemyTest(size_t id, const character_t& character, int attack_damage, int health,
//               int revive_cooldown, int x, int y):
//             Enemy(id, character, attack_damage, health, revive_cooldown, x, y, 50, 50, 1) {
//         SDL_Rect enemy_cube = {x, y, 50, 50};
//         SDL_Color color = {255, 50, 50, 255};
//         this->color_rect = engine::ColorRect(color, enemy_cube);
//     }

//     void update(int delta) override { color_rect.set_position(position.x, position.y); }
//     void set_position(int x, int y) override {}
//     bool is_intersecting(SDL_Point& point) const override { return false; }
//     bool is_intersecting(SDL_Rect& rect) const override { return false; }

//     void draw(SDL_Renderer* renderer, int it) override { color_rect.draw(renderer); }
// };


// // ----------------------------------------------------------


// int main() {
//     engine::Window window(1600, 800, true, true);
//     auto renderer = window.get_renderer();

//     engine::CollisionManager collision_manager(1600, 800);

//     SDL_Color color_1 = {255, 0, 0, 255};
//     auto floor = std::make_shared<PlatformTest>(0, 800 - 32, 1600, 32, color_1);

//     SDL_Color color_roof = {255, 0, 0, 255};
//     auto roof = std::make_shared<PlatformTest>(0, 0, 1600, 32, color_roof);

//     SDL_Color color_2 = {0, 0, 255, 255};
//     auto platform_1 = std::make_shared<PlatformTest>(100, 500, 300, 64, color_2);

//     SDL_Color color_3 = {255, 0, 100, 255};
//     auto platform_2 = std::make_shared<PlatformTest>(500, 300, 300, 64, color_3);

//     SDL_Color color_wall = {200, 210, 255, 255};
//     auto wall_1 = std::make_shared<PlatformTest>(1000, 100, 100, 750, color_wall);

//     auto treasure = std::make_shared<TreasureTest>(700, 800 - 32 - 50, 32, 32);

//     auto ammo = std::make_shared<AmmoTest>(800, 800 - 32 - 50, 32, 32);

//     auto player = std::make_shared<PlayerTest>(1, "JAZZ_CHARACTER", 1, 100, 450,
//     collision_manager);

//     auto enemy = std::make_shared<EnemyTest>(2, JAZZ_CHARACTER, 10, 100, 1000, 500, 800 - 32 -
//     50);

//     collision_manager.track_dynamic_body(player);
//     collision_manager.track_dynamic_body(enemy);
//     collision_manager.track_dynamic_body(treasure);
//     collision_manager.track_dynamic_body(ammo);

//     collision_manager.add_object(floor);
//     collision_manager.add_object(roof);
//     collision_manager.add_object(platform_1);
//     collision_manager.add_object(platform_2);
//     collision_manager.add_object(wall_1);

//     engine::Keyboard keyboard;
//     keyboard.add_on_key_down_signal_obj(player.get());

//     SDL_Event event;
//     bool running = true;

//     Uint32 frame_start = 0;
//     int frame_time = 0;
//     const int frame_delay = 1000 / 60;


//     while (running) {

//         frame_start = SDL_GetTicks();

//         // Updates
//         collision_manager.update();
//         collision_manager.remove_inactive_bodies();

//         // itereate the dynamic bodies and update the color rect

//         collision_manager.iterateDynamicBodies([](std::shared_ptr<engine::DynamicBody>& body) {
//             auto canvasBody = std::dynamic_pointer_cast<engine::CanvasObject>(body);
//             if (canvasBody && body->is_active_object()) {

//                 canvasBody->update(1);
//             }
//         });

//         if (enemy->try_revive()) {
//             enemy->revive(enemy->spawn_position);
//             collision_manager.track_dynamic_body(enemy);
//         }

//         if (player->try_revive()) {
//             player->revive(engine::Vector2D(100, 450));
//             collision_manager.track_dynamic_body(player);
//         }

//         if (ammo->try_respawn()) {
//             ammo->respawn(engine::Vector2D(800, 800 - 32 - 80));
//             collision_manager.track_dynamic_body(ammo);
//         }

//         if (treasure->try_respawn()) {
//             treasure->respawn(engine::Vector2D(700, 800 - 32 - 80));
//             collision_manager.track_dynamic_body(treasure);
//         }


//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = false;
//             }
//             keyboard.update(event);
//         }
//         window.clear();

//         collision_manager.iterateDynamicBodies([renderer](std::shared_ptr<engine::DynamicBody>&
//         body) {
//             auto canvasBody = std::dynamic_pointer_cast<engine::CanvasObject>(body);
//             if (canvasBody && body->is_active_object()) {

//                 canvasBody->draw(renderer);
//             }
//         });

//         floor->draw(renderer);
//         roof->draw(renderer);
//         platform_1->draw(renderer);
//         platform_2->draw(renderer);
//         wall_1->draw(renderer);


//         for (auto& [dynamic_body, position]: collision_manager.dynamic_bodies) {

//             auto bullet = std::dynamic_pointer_cast<Bullet>(dynamic_body);
//             auto ammo = std::dynamic_pointer_cast<AmmoTest>(dynamic_body);
//             auto collectable = std::dynamic_pointer_cast<TreasureTest>(dynamic_body);

//             if (bullet && bullet->is_active_object()) {
//                 bullet->draw(renderer);
//             } else if (ammo && ammo->is_active_object()) {
//                 ammo->draw(renderer);
//             } else if (collectable && collectable->is_active_object()) {
//                 collectable->draw(renderer);
//             } else if (!dynamic_body->is_active_object()) {
//                 collision_manager.remove_object(dynamic_body);
//             }
//         }

//         window.render();

//         frame_time = SDL_GetTicks() - frame_start;
//         if (frame_delay > frame_time) {  // Delay to achieve 60 fps
//             SDL_Delay(frame_delay - frame_time);
//         }

//         player->print_info();
//         enemy->print_info();
//     }
//     std::cout << "Exiting game..." << std::endl;

//     return 0;
// }
