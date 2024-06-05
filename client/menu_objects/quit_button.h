#ifndef TP_FINAL_QUITBUTTON_H
#define TP_FINAL_QUITBUTTON_H

#include <memory>
#include <utility>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"
#include "../assets.h"

class QuitButton: public engine::Button {
public:
    QuitButton(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
               SDL_Rect& d_rect);

    void on_click() override;

    ~QuitButton() override;
};


#endif  // TP_FINAL_QUITBUTTON_H
