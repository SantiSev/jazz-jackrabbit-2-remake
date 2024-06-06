#ifndef TP_FINAL_MATCH_SCENE_H
#define TP_FINAL_MATCH_SCENE_H

#include <atomic>
#include <memory>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../assets.h"
#include "../event_loop.h"
#include "../game_objects/map.h"

class MatchScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    std::atomic<bool>& match_running;
    Map map;

public:
    MatchScene(engine::Window& window, EventLoop* event_loop,
               std::shared_ptr<engine::ResourcePool> resource_pool,
               std::atomic<bool>& match_running);

    // cant copy
    MatchScene(const MatchScene&) = delete;
    MatchScene& operator=(const MatchScene&) = delete;

    void start();

    ~MatchScene();
};

#endif  // TP_FINAL_MATCH_SCENE_H
