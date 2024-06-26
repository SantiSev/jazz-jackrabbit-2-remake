#ifndef TP_FINAL_EDITOR_BUTTON_H
#define TP_FINAL_EDITOR_BUTTON_H

#include <atomic>
#include <memory>

#include "../../common/assets.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"


class EditorButton: public engine::Button {
private:
    std::atomic<bool>& menu_running;
    std::atomic<bool>& editor_running;


public:
    EditorButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                 SDL_Rect& d_rect, std::atomic<bool>& menu_running,
                 std::atomic<bool>& editor_running);

    void on_click() override;

    ~EditorButton() override;
};


#endif  // TP_FINAL_EDITOR_BUTTON_H
