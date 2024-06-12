#ifndef TP_FINAL_ANIMATED_SPRITE_H
#define TP_FINAL_ANIMATED_SPRITE_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <yaml-cpp/yaml.h>

#include "../../errors.h"
#include "../basic/texture.h"
#include "../canvas_object.h"

namespace engine {
class AnimatedSprite: public CanvasObject {
private:
    std::shared_ptr<Texture> texture;
    std::shared_ptr<YAML::Node> animations;
    std::string current_animation;
    int animation_off_x;
    int animation_off_y;

    SDL_Rect s_rect;
    SDL_Rect d_rect;

    int x_start;

    int frames;
    int current_frame;
    int ms_per_frame;
    int elapsed_time;

    short next_frame_offset;
    bool flipped;

    void next_frame();

public:
    explicit AnimatedSprite(std::shared_ptr<Texture> texture,
                            std::shared_ptr<YAML::Node> animations,
                            const std::string& animation_name, int x, int y);
    explicit AnimatedSprite(std::shared_ptr<Texture> texture, SDL_Rect& s_rect, SDL_Rect& d_rect,
                            int frames, int fps);

    // Cant copy
    AnimatedSprite(const AnimatedSprite&) = delete;
    AnimatedSprite& operator=(const AnimatedSprite&) = delete;

    // Can move
    AnimatedSprite(AnimatedSprite&&) noexcept;
    AnimatedSprite& operator=(AnimatedSprite&&) noexcept;

    void draw(SDL_Renderer* renderer) override;
    void update(int delta) override;

    void set_position(int x, int y) override;
    void set_position_with_correction(int x, int y);
    void reverse_animation();
    void flip();
    void set_animation(const std::string& animation_name);

    bool is_intersecting(SDL_Point&) const override;
    bool is_intersecting(SDL_Rect&) const override;

    ~AnimatedSprite() override;
};
}  // namespace engine

#endif  // TP_FINAL_ANIMATED_SPRITE_H
