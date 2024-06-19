#include "editor_hud.h"

#define Y_BUTTON_START 555
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 25

EditorHud::EditorHud(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                     EventLoop* event_loop, TileManager& tile_manager,
                     std::atomic<bool>& menu_running, std::atomic<bool>& editor_running):
        body({0, 544, 800, 56}),
        renderer(renderer),
        event_loop(event_loop),
        resource_pool(resource_pool),
        tile_manager(tile_manager),
        background({0, 0, 0, 128}, body),
        save_and_exit_button(nullptr) {
    create_buttons(menu_running, editor_running);
}

void EditorHud::draw(SDL_Renderer* renderer, int it) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &body);

    for (auto& tile: tiles) {
        tile.draw(renderer, it);
    }

    save_and_exit_button->draw(renderer, it);
}

SDL_Rect& EditorHud::get_body() { return body; }

void EditorHud::create_buttons(std::atomic<bool>& menu_running, std::atomic<bool>& editor_running) {

    // Create save and exit button
    int y_start = Y_BUTTON_START;
    int x_start = 10;
    int w = BUTTON_WIDTH;
    int h = BUTTON_HEIGHT;

    SDL_Rect create_match_button_d_rect = {800 - (w + 10), y_start, w, h};
    save_and_exit_button = std::make_unique<SaveExitEditorButton>(
            renderer, resource_pool, create_match_button_d_rect, menu_running, editor_running,
            tile_manager);
    event_loop->mouse.add_on_click_signal_obj(save_and_exit_button.get());

    // Create selection tiles
    auto texture = resource_pool->get_texture(EDITOR_FILE);
    auto yaml = *resource_pool->get_yaml(EDITOR_FILE);

    for (auto obj: yaml["objects"]) {
        SDL_Rect s_rect = {obj["x"].as<int>(), obj["y"].as<int>(), obj["w"].as<int>(),
                           obj["h"].as<int>()};
        SDL_Rect d_rect = {x_start, y_start, s_rect.w, s_rect.h};
        x_start += s_rect.w + 10;
        tiles.emplace_back(d_rect, s_rect, texture, tile_manager);
        event_loop->mouse.add_on_click_signal_obj(&tiles.back());
    }
}

EditorHud::~EditorHud() {
    event_loop->mouse.remove_on_click_signal_obj(save_and_exit_button.get());
    for (auto& tile: tiles) {
        event_loop->mouse.remove_on_click_signal_obj(&tile);
    }
}
