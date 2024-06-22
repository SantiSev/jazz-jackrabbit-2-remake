#ifndef TP_FINAL_BUTTON_H
#define TP_FINAL_BUTTON_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../controllers/mouse.h"
#include "../../errors.h"
#include "../canvas_object.h"

#include "label.h"

namespace engine {
class Button: public CanvasObject {
protected:
    std::unique_ptr<Label> label;
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hover_color;
    bool is_hovered_m;

public:
    explicit Button(std::unique_ptr<Label> label, SDL_Rect& rect, const SDL_Color& color,
                    const SDL_Color& hoverColor);

    // Cant copy
    Button(const Button& other) = delete;
    Button& operator=(const Button& other) = delete;

    // Move constructors
    Button(Button&& other) noexcept;
    Button& operator=(Button&& other) noexcept;

    void draw(SDL_Renderer* renderer, int it) override;

    void center_x(int x, int w);
    void center_y(int y, int h);
    void center(int x, int y, int w, int h);

    void on_click() override;
    void is_hovered(bool) override;

    SDL_Rect& get_body() override;
    void set_position(int x, int y) override;

    bool is_intersecting(SDL_Point&) const override;
    bool is_intersecting(SDL_Rect&) const override;

    ~Button() override;
};
}  // namespace engine

#endif  // TP_FINAL_BUTTON_H
