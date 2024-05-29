#ifndef TP_FINAL_ANIMATED_SPRITE_H
#define TP_FINAL_ANIMATED_SPRITE_H

#include <iostream>
#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../errors.h"
#include "../canvas_object.h"

class AnimatedSprite: public CanvasObject {
private:
    std::shared_ptr<SDL_Texture*> texture;
    SDL_Rect s_rect;
    SDL_Rect d_rect;
    int frames;
    int current_frame;
    int ms_per_frame;
    int elapsed_time;

    void next_frame();

public:
    explicit AnimatedSprite(const std::shared_ptr<SDL_Texture*>& texture, SDL_Rect& s_rect,
                            SDL_Rect& d_rect, int frames, int fps);

    void draw(SDL_Renderer* renderer) override;
    void update(int delta) override;

    void set_position(int x, int y) override;

    bool is_intersecting(SDL_Point&) override;
    bool is_intersecting(SDL_Rect&) override;

    ~AnimatedSprite() override;
};


#endif  // TP_FINAL_ANIMATED_SPRITE_H
