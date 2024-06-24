#ifndef TP_FINAL_SCORE_SCENE_H
#define TP_FINAL_SCORE_SCENE_H

#include <algorithm>
#include <cmath>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/sprite.h"
#include "../event_loop.h"
#include "../protocol/client_message_handler.h"
#include "../scoreboard_objects/return_menu_button.h"
#include "../shared/background.h"

class ScoreScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;
    engine::Sprite* background;
    std::shared_ptr<GameStateDTO>& game_state;
    std::list<engine::Button*> buttons;
    std::list<engine::Label*> labels;
    std::atomic<bool>& menu_running;
    std::atomic<bool>& scoreboard_running;
    std::atomic<id_client_t>& my_id_client;

public:
    ScoreScene(engine::Window& window, EventLoop* event_loop,
               const std::shared_ptr<engine::ResourcePool>& resource_pool,
               std::atomic<bool>& menu_running, std::atomic<bool>& scoreboard_running,
               ClientMessageHandler& message_handler,
               std::shared_ptr<GameStateDTO>& last_game_state,
               std::atomic<id_client_t>& my_id_client);

    // cant copy
    ScoreScene(const ScoreScene&) = delete;
    ScoreScene& operator=(const ScoreScene&) = delete;

    void start();

    void create_score_labels();

    SDL_Color select_color_winner(uint16_t id);

    ~ScoreScene();
};


#endif
