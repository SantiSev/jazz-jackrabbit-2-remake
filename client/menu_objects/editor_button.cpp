#include "editor_button.h"

EditorButton::EditorButton(SDL_Renderer* renderer,
                           std::shared_ptr<engine::ResourcePool> resource_pool, SDL_Rect& d_rect,
                           std::atomic<bool>& menu_running, std::atomic<bool>& editor_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Map Editor", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        menu_running(menu_running),
        editor_running(editor_running) {}

void EditorButton::on_click() {
#ifdef LOG
    std::cout << "Clicked editor button." << std::endl;
#endif
    editor_running.store(true);
    menu_running.store(false);
}

EditorButton::~EditorButton() = default;
