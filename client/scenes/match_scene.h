#ifndef TP_FINAL_MATCH_SCENE_H
#define TP_FINAL_MATCH_SCENE_H

#include <atomic>
#include <cmath>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <SDL2/SDL.h>

// #include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../common/common_constants.h"
#include "../../common/common_queue.h"
#include "../../common/item_enum.h"
#include "../../common/protocol/common_dto.h"
// #include "../../game_engine/gui/basic/resource_pool.h"
// #include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/camera.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "../../game_engine/gui/widgets/sound_manager.h"
// #include "../event_loop.h"
#include "../game_objects/bullet_factory.h"
#include "../game_objects/character_factory.h"
#include "../game_objects/item_factory.h"
#include "../game_objects/map.h"
#include "../game_objects/player_controller.h"
// #include "../hud/ingame_hud.h"

#include "score_scene.h"

class MatchScene {
private:
    std::atomic<id_client_t>& id_client;

    engine::Window& window;
    SDL_Renderer* renderer;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    std::shared_ptr<engine::SoundManager> sound_manager;

    EventLoop* event_loop;
    ClientMessageHandler& message_handler;
    Queue<std::shared_ptr<GameStateDTO>>& game_state_q;
    std::shared_ptr<GameStateDTO> last_game_state;

    std::atomic<bool>& match_running;
    std::atomic<bool>& menu_running;

    std::shared_ptr<Map> map;
    std::unordered_map<uint16_t, std::shared_ptr<engine::AnimatedSprite>> players;
    std::unordered_map<uint16_t, std::shared_ptr<engine::AnimatedSprite>> enemies;
    std::unordered_map<uint16_t, std::shared_ptr<engine::AnimatedSprite>> bullets;
    std::unordered_map<uint16_t, std::shared_ptr<engine::AnimatedSprite>> items;
    // std::unique_ptr<IngameHud> hud;
    engine::Camera camera;

    PlayerController player_controller;

    void destroy_untracked_objects();
    void update_objects();
    void draw_objects(int it);

public:
    MatchScene(engine::Window& window, EventLoop* event_loop,
               const std::shared_ptr<engine::ResourcePool>& resource_pool,
               std::shared_ptr<engine::SoundManager> sound_manager,
               ClientMessageHandler& message_handler, std::atomic<id_client_t>& id_client,
               std::atomic<bool>& match_running, std::atomic<bool>& menu_running, uint16_t map_id);

    // cant copy
    MatchScene(const MatchScene&) = delete;
    MatchScene& operator=(const MatchScene&) = delete;

    void start();

    ~MatchScene();
};

#endif  // TP_FINAL_MATCH_SCENE_H
