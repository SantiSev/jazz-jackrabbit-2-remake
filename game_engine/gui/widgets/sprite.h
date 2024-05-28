#ifndef TP_FINAL_SPRITE_H
#define TP_FINAL_SPRITE_H

#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../canvas_object.h"

class Sprite: public CanvasObject {
private:
    SDL_Rect s_rect;
    SDL_Rect d_rect;
    SDL_Surface* surface;

public:
    Sprite(const std::string& file, const SDL_Rect& s_react, const SDL_Rect& d_rect);

    void draw(SDL_Renderer* renderer) override;

    void set_position(int x, int y) override;

    bool is_intersecting(SDL_Point&) override;
    bool is_intersecting(SDL_Rect&) override;

    ~Sprite() override;
};


#endif  // TP_FINAL_SPRITE_H
