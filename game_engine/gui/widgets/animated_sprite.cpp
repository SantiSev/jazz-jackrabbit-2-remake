#include "animated_sprite.h"

using engine::AnimatedSprite;

AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture> texture, SDL_Rect& s_rect, SDL_Rect& d_rect,
                               int frames, int fps):
        texture(texture),
        animations(nullptr),
        animation_off_x(0),
        animation_off_y(0),
        s_rect(s_rect),
        d_rect(d_rect),
        x_start(s_rect.x),
        frames(frames),
        current_frame(0),
        elapsed_time(0),
        next_frame_offset(1),
        flipped(false),
        fps(fps) {}

AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture> texture,
                               std::shared_ptr<YAML::Node> animations,
                               const std::string& animation_name, int x, int y):
        texture(texture),
        animations(animations),
        animation_off_x(0),
        animation_off_y(0),
        current_frame(0),
        elapsed_time(0),
        next_frame_offset(1),
        flipped(false),
        fps(0) {
    set_animation(animation_name);
    set_position_with_correction(x, y);
}

void AnimatedSprite::draw(SDL_Renderer* renderer, int it) {

    if (it % fps == 0) {
        next_frame();
    }
    s_rect.x = (current_frame * s_rect.w) + x_start;

    int err;
    if (flipped) {
        err = SDL_RenderCopyEx(renderer, texture->get_texture(), &s_rect, &d_rect, 0, nullptr,
                               SDL_FLIP_HORIZONTAL);
    } else {
        err = SDL_RenderCopy(renderer, texture->get_texture(), &s_rect, &d_rect);
    }

    if (err < 0) {
        throw SDLError("Error drawing animation: " + std::string(SDL_GetError()));
    }
}

void AnimatedSprite::next_frame() { current_frame = (current_frame + next_frame_offset) % frames; }

void AnimatedSprite::set_position(int x, int y) {
    // If no animations are set, there's no need to adjust the position
    if (animations == nullptr) {
        d_rect.x = x;
        d_rect.y = y;
        return;
    }
    set_position_with_correction(x, y);
}

void AnimatedSprite::set_position_with_correction(int x, int y) {
    int corrected_x = x + animation_off_x;
    int corrected_y = y + animation_off_y;

    if (corrected_x < 0) {
        corrected_x = 0;
    }

    if (corrected_y < 0) {
        corrected_y = 0;
    }

    d_rect.x = corrected_x;
    d_rect.y = corrected_y;
}

void AnimatedSprite::reverse_animation() { next_frame_offset *= -1; }

void AnimatedSprite::flip() { flipped = !flipped; }

void AnimatedSprite::set_animation(const std::string& animation_name) {
    if (animations == nullptr) {
        throw BadParams("No animations set");
    }

    if (current_animation == animation_name) {
        return;
    }

    current_animation = animation_name;
    YAML::Node yaml = *animations;
    YAML::Node animation = yaml[animation_name];
    if (animation.IsNull()) {
        throw BadParams("Animation not found: " + animation_name);
    }

    s_rect.x = animation["x"].as<int>();
    s_rect.y = animation["y"].as<int>();
    s_rect.w = animation["w"].as<int>();
    s_rect.h = animation["h"].as<int>();

    d_rect.w = animation["w"].as<int>();
    d_rect.h = animation["h"].as<int>();

    animation_off_x = animation["off_x"].as<int>();
    animation_off_y = animation["off_y"].as<int>();

    x_start = s_rect.x;
    frames = animation["frames"].as<int>();
    if (frames <= 0) {
        throw BadParams("Frames must be greater than 0");
    }

    int fps = animation["fps"].as<int>();
    if (fps <= 0) {
        throw BadParams("FPS must be greater than 0");
    }
    this->fps = fps;

    flipped = animation["flipped"].as<bool>();
    current_frame = 0;
}

bool AnimatedSprite::is_intersecting(SDL_Point& point) const {
    return SDL_PointInRect(&point, &d_rect);
}

bool AnimatedSprite::is_intersecting(SDL_Rect& rect) const {
    return SDL_HasIntersection(&d_rect, &rect);
}

AnimatedSprite::AnimatedSprite(AnimatedSprite&& other) noexcept:
        texture(std::move(other.texture)),
        animations(std::move(other.animations)),
        current_animation(other.current_animation),
        animation_off_x(other.animation_off_x),
        animation_off_y(other.animation_off_y),
        s_rect(other.s_rect),
        d_rect(other.d_rect),
        x_start(other.x_start),
        frames(other.frames),
        current_frame(other.current_frame),
        elapsed_time(other.elapsed_time),
        next_frame_offset(other.next_frame_offset),
        flipped(other.flipped),
        fps(other.fps) {}

AnimatedSprite& AnimatedSprite::operator=(AnimatedSprite&& other) noexcept {
    if (this == &other)
        return *this;

    texture = std::move(other.texture);
    animations = std::move(other.animations);
    current_animation = other.current_animation;
    animation_off_x = other.animation_off_x;
    animation_off_y = other.animation_off_y;
    s_rect = other.s_rect;
    d_rect = other.d_rect;
    x_start = other.x_start;
    frames = other.frames;
    current_frame = other.current_frame;
    elapsed_time = other.elapsed_time;
    next_frame_offset = other.next_frame_offset;
    flipped = other.flipped;
    fps = other.fps;

    return *this;
}

AnimatedSprite::~AnimatedSprite() = default;
