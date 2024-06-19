#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include <atomic>
#include <list>
#include <memory>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/camera.h"
#include "../editor_objects/editor_controller.h"
#include "../editor_objects/editor_tile.h"
#include "../editor_objects/tile_manager.h"
#include "../event_loop.h"
#include "../hud/editor_hud.h"
#include "../hud/tile.h"
#include "../menu_objects/save_exit_editor_button.h"


class EditorScene {
private:
    engine::Window& window;
    SDL_Renderer* renderer;
    EventLoop* event_loop;
    std::shared_ptr<engine::ResourcePool> resource_pool;

    std::atomic<bool>& menu_running;
    std::atomic<bool>& editor_running;

    std::unique_ptr<engine::Sprite> background;
    std::unordered_map<uint16_t, std::shared_ptr<EditorTile>> tiles;
    TileManager tile_manager;
    EditorHud hud;
    engine::Camera camera;
    EditorController controller;

    void load_background();

public:
    EditorScene(engine::Window& window, EventLoop* event_loop,
                std::shared_ptr<engine::ResourcePool> resource_pool,
                std::atomic<bool>& menu_running, std::atomic<bool>& editor_running,
                ClientMessageHandler& message_handler);

    // cant copy
    EditorScene(const EditorScene&) = delete;
    EditorScene& operator=(const EditorScene&) = delete;

    void start();

    ~EditorScene();
};

#endif  // EDITOR_SCENE_H
