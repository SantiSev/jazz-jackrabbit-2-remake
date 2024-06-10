#ifndef TP_FINAL_MATCH_SCENE_H
#define TP_FINAL_MATCH_SCENE_H

#include <atomic>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/character_enum.h"
#include "../../common/common_constants.h"
#include "../../common/common_queue.h"
#include "../../common/protocol/common_dto.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "../event_loop.h"
#include "../game_objects/character.h"
#include "../game_objects/character_factory.h"
#include "../game_objects/map.h"

class MatchScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    std::shared_ptr<engine::ResourcePool> resource_pool;

    EventLoop* event_loop;
    ClientMessageHandler& message_handler;
    Queue<std::shared_ptr<GameStateDTO>>& game_state_q;

    std::atomic<bool>& match_running;
    std::unique_ptr<Map> map;
    std::map<uint16_t, std::unique_ptr<Character>> characters;

    void init();
    void create_character(uint16_t id, character_t character, uint8_t state, uint16_t x,
                          uint16_t y);
    void update_objects(int delta_time);
    void draw_objects();

public:
    MatchScene(engine::Window& window, EventLoop* event_loop,
               std::shared_ptr<engine::ResourcePool> resource_pool,
               std::atomic<bool>& match_running, ClientMessageHandler& message_handler);

    // cant copy
    MatchScene(const MatchScene&) = delete;
    MatchScene& operator=(const MatchScene&) = delete;

    void start();

    void load_map(const map_list_t& map_enum);

    ~MatchScene();
};

#endif  // TP_FINAL_MATCH_SCENE_H
