#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(const std::string& file, const SDL_Rect& s_rect,
                               const SDL_Rect& d_rect, int frames, int speed):
        s_rect(s_rect),
        d_rect(d_rect),
        frames(frames),
        speed(speed),
        current_frame(0),
        frames_counter(0) {
    surface = IMG_Load(file.c_str());
    if (surface == nullptr) {
        throw std::runtime_error("Error loading image");
    }
}

void AnimatedSprite::draw(SDL_Renderer* renderer) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect current_s_rect = {s_rect.x + s_rect.w * current_frame, s_rect.y, s_rect.w, s_rect.h};
    SDL_RenderCopy(renderer, texture, &current_s_rect, &d_rect);
    SDL_DestroyTexture(texture);

    if (frames_counter == speed) {
        current_frame = (current_frame + 1) % frames;
        frames_counter = 0;
    } else {
        frames_counter++;
    }
}

bool AnimatedSprite::is_intersecting(SDL_Point& point) { return SDL_PointInRect(&point, &d_rect); }

bool AnimatedSprite::is_intersecting(SDL_Rect& rect) { return SDL_HasIntersection(&d_rect, &rect); }

AnimatedSprite::~AnimatedSprite() { SDL_FreeSurface(surface); }
