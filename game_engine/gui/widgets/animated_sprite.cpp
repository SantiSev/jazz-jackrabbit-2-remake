#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(const std::string& file, const SDL_Rect& s_rect,
                               const SDL_Rect& d_rect, int frames, int fps, SDL_Renderer* renderer):
        s_rect(s_rect),
        d_rect(d_rect),
        texture(nullptr),
        frames(frames),
        ms_per_frame(1000 / fps),
        current_frame(0),
        elapsed_time(0) {
    texture = IMG_LoadTexture(renderer, file.c_str());
    if (!texture) {
        throw std::runtime_error("Error loading image");
    }
}

void AnimatedSprite::update(int delta) { elapsed_time += delta; }

void AnimatedSprite::draw(SDL_Renderer* renderer) {
    if (elapsed_time >= ms_per_frame) {
        elapsed_time = 0;
        next_frame();
    }

    SDL_Rect current_s_rect = {s_rect.x + s_rect.w * current_frame, s_rect.y, s_rect.w, s_rect.h};
    SDL_RenderCopy(renderer, texture, &current_s_rect, &d_rect);
}

void AnimatedSprite::next_frame() { current_frame = (current_frame + 1) % frames; }

void AnimatedSprite::set_position(int x, int y) {
    d_rect.x = x;
    d_rect.y = y;
}

bool AnimatedSprite::is_intersecting(SDL_Point& point) { return SDL_PointInRect(&point, &d_rect); }

bool AnimatedSprite::is_intersecting(SDL_Rect& rect) { return SDL_HasIntersection(&d_rect, &rect); }

AnimatedSprite::~AnimatedSprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
