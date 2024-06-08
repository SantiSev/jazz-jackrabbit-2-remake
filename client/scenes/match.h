#ifndef TP_FINAL_MATCH_SCENE_H
#define TP_FINAL_MATCH_SCENE_H

#include <atomic>
#include <memory>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../common/common_queue.h"
#include "../../common/protocol/common_dto.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../event_loop.h"
#include "../game_objects/map.h"

class MatchScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    std::atomic<bool>& match_running;
    std::unique_ptr<Map> map;
    Queue<std::shared_ptr<GameStateDTO>>& game_state_q;

    void create_objects();
    void update_objects();

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
