#ifndef TP_FINAL_LABEL_H
#define TP_FINAL_LABEL_H

#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../errors.h"
#include "../basic/font.h"
#include "../basic/texture.h"
#include "../canvas_object.h"

namespace engine {
class Label: public CanvasObject {
private:
    std::shared_ptr<Font> font;
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hover_color;
    Texture texture;
    Texture hover_texture;
    std::string text;
    bool is_hovered_m;

public:
    Label(std::shared_ptr<Font> font, SDL_Rect rect, SDL_Color color, SDL_Color hover_color,
          const std::string& text, SDL_Renderer* renderer);

    // Cant copy
    Label(const Label& other) = delete;
    Label& operator=(const Label& other) = delete;

    // Move constructors
    Label(Label&& other) noexcept;
    Label& operator=(Label&& other) noexcept;

    void draw(SDL_Renderer* renderer, int it) override;

    void center_x(int x, int w);
    void center_y(int y, int h);
    void center(int x, int y, int w, int h);

    void is_hovered(bool) override;

    SDL_Rect& get_body() override;
    void set_position(int x, int y) override;

    std::string get_text();
    void set_text(const std::string& new_text, SDL_Renderer* renderer);

    bool is_intersecting(SDL_Point&) const override;
    bool is_intersecting(SDL_Rect&) const override;

    ~Label() override;
};
}  // namespace engine

#endif  // TP_FINAL_LABEL_H
