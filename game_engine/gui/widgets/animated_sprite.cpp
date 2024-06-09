#include "animated_sprite.h"

using engine::AnimatedSprite;

AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture> texture, SDL_Rect& s_rect, SDL_Rect& d_rect,
                               int frames, int fps):
        texture(texture),
        animations(nullptr),
        s_rect(s_rect),
        d_rect(d_rect),
        x_start(s_rect.x),
        frames(frames),
        current_frame(0),
        elapsed_time(0),
        next_frame_offset(1),
        flipped(false) {
    if (fps <= 0) {
        throw BadParams("FPS must be greater than 0");
    }
    ms_per_frame = 1000 / fps;
}

AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture> texture,
                               std::shared_ptr<YAML::Node> animations,
                               const std::string& animation_name, int x, int y):
        texture(texture),
        animations(animations),
        current_frame(0),
        elapsed_time(0),
        next_frame_offset(1),
        flipped(false) {
    d_rect.x = x;
    d_rect.y = y;
    set_animation(animation_name);
}

void AnimatedSprite::update(int delta) {
    elapsed_time += delta;
    if (elapsed_time >= ms_per_frame) {
        elapsed_time = 0;
        next_frame();
    }
}

void AnimatedSprite::draw(SDL_Renderer* renderer) {
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
    d_rect.x = x;
    d_rect.y = y;
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

#ifdef LOG
    std::cout << "Setting animation: " << animation_name << std::endl;
#endif

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

    d_rect.h = yaml["character_height"].as<int>();
    d_rect.w = yaml["character_width"].as<int>();

    x_start = s_rect.x;
    frames = animation["frames"].as<int>();
    if (frames <= 0) {
        throw BadParams("Frames must be greater than 0");
    }

    int fps = animation["fps"].as<int>();
    if (fps <= 0) {
        throw BadParams("FPS must be greater than 0");
    }
    ms_per_frame = 1000 / fps;

    flipped = animation["flipped"].as<bool>();
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
        s_rect(other.s_rect),
        d_rect(other.d_rect),
        x_start(other.x_start),
        frames(other.frames),
        current_frame(other.current_frame),
        ms_per_frame(other.ms_per_frame),
        elapsed_time(other.elapsed_time),
        next_frame_offset(other.next_frame_offset),
        flipped(other.flipped) {}

AnimatedSprite& AnimatedSprite::operator=(AnimatedSprite&& other) noexcept {
    if (this == &other)
        return *this;

    texture = std::move(other.texture);
    animations = std::move(other.animations);
    current_animation = other.current_animation;
    s_rect = other.s_rect;
    d_rect = other.d_rect;
    x_start = other.x_start;
    frames = other.frames;
    current_frame = other.current_frame;
    ms_per_frame = other.ms_per_frame;
    elapsed_time = other.elapsed_time;
    next_frame_offset = other.next_frame_offset;
    flipped = other.flipped;

    return *this;
}

AnimatedSprite::~AnimatedSprite() = default;
