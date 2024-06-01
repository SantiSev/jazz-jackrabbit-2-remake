#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture> texture, SDL_Rect& s_rect, SDL_Rect& d_rect,
                               int frames, int fps):
        texture(texture),
        s_rect(s_rect),
        d_rect(d_rect),
        frames(frames),
        current_frame(0),
        elapsed_time(0) {
    if (fps <= 0) {
        throw BadParams("FPS must be greater than 0");
    }
    ms_per_frame = 1000 / fps;
}

void AnimatedSprite::update(int delta) {
    elapsed_time += delta;
    if (elapsed_time >= ms_per_frame) {
        elapsed_time = 0;
        next_frame();
    }
}

void AnimatedSprite::draw(SDL_Renderer* renderer) {
    s_rect.x = current_frame * s_rect.w;
    SDL_RenderCopy(renderer, texture->get_texture(), &s_rect, &d_rect);
}

void AnimatedSprite::next_frame() { current_frame = (current_frame + 1) % frames; }

void AnimatedSprite::set_position(int x, int y) {
    d_rect.x = x;
    d_rect.y = y;
}

bool AnimatedSprite::is_intersecting(SDL_Point& point) const {
    return SDL_PointInRect(&point, &d_rect);
}

bool AnimatedSprite::is_intersecting(SDL_Rect& rect) const {
    return SDL_HasIntersection(&d_rect, &rect);
}

AnimatedSprite::AnimatedSprite(AnimatedSprite&& other) noexcept:
        texture(std::move(other.texture)),
        s_rect(other.s_rect),
        d_rect(other.d_rect),
        frames(other.frames),
        current_frame(other.current_frame),
        ms_per_frame(other.ms_per_frame),
        elapsed_time(other.elapsed_time) {}

AnimatedSprite& AnimatedSprite::operator=(AnimatedSprite&& other) noexcept {
    if (this == &other)
        return *this;

    texture = std::move(other.texture);
    s_rect = other.s_rect;
    d_rect = other.d_rect;
    frames = other.frames;
    current_frame = other.current_frame;
    ms_per_frame = other.ms_per_frame;
    elapsed_time = other.elapsed_time;

    return *this;
}

AnimatedSprite::~AnimatedSprite() = default;
