#ifndef TP_FINAL_ANIMATED_SPRITE_H
#define TP_FINAL_ANIMATED_SPRITE_H

#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../canvas_object.h"

class AnimatedSprite: public CanvasObject {
private:
    SDL_Rect s_rect;
    SDL_Rect d_rect;
    SDL_Surface* surface;
    int frames;
    int speed;
    int current_frame;
    int frames_counter;

public:
    AnimatedSprite(const std::string& file, const SDL_Rect& s_rect, const SDL_Rect& d_rect,
                   int frames, int speed);

    void draw(SDL_Renderer* renderer) override;

    bool is_intersecting(SDL_Point&) override;
    bool is_intersecting(SDL_Rect&) override;

    ~AnimatedSprite() override;
};


#endif  // TP_FINAL_ANIMATED_SPRITE_H
