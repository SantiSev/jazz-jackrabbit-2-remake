#ifndef TP_FINAL_ANIMATED_SPRITE_H
#define TP_FINAL_ANIMATED_SPRITE_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../errors.h"
#include "../basic/texture.h"
#include "../canvas_object.h"

namespace engine {
class AnimatedSprite: public CanvasObject {
private:
    std::shared_ptr<Texture> texture;
    SDL_Rect s_rect;
    SDL_Rect d_rect;
    int frames;
    int current_frame;
    int ms_per_frame;
    int elapsed_time;

    void next_frame();

public:
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

    bool is_intersecting(SDL_Point&) const override;
    bool is_intersecting(SDL_Rect&) const override;

    ~AnimatedSprite() override;
};
}  // namespace engine

#endif  // TP_FINAL_ANIMATED_SPRITE_H
