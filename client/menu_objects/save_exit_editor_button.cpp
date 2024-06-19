#include "save_exit_editor_button.h"

SaveExitEditorButton::SaveExitEditorButton(SDL_Renderer* renderer,
                                           std::shared_ptr<engine::ResourcePool> resource_pool,
                                           SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                                           std::atomic<bool>& editor_running):
        engine::Button(std::make_unique<engine::Label>(engine::Label(
                               resource_pool->get_font(FONT), d_rect, {255, 255, 255, 255},
                               {0, 0, 0, 255}, "Save and Exit", renderer)),
                       d_rect, {0, 0, 0, 255}, {255, 255, 255, 255}),
        menu_running(menu_running),
        editor_running(editor_running) {}

void SaveExitEditorButton::on_click() {
#ifdef LOG
    std::cout << "Clicked save and exit button." << std::endl;
#endif
    editor_running.store(false);
    menu_running.store(true);
}

SaveExitEditorButton::~SaveExitEditorButton() = default;
