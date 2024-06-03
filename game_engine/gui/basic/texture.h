#ifndef TP_FINAL_TEXTURE_H
#define TP_FINAL_TEXTURE_H

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../errors.h"

#include "font.h"

namespace engine {
class Texture {
private:
    SDL_Texture* texture;

public:
    explicit Texture(const std::string& file, SDL_Renderer* renderer);
    explicit Texture(const std::shared_ptr<Font>& font, const SDL_Color& color,
                     const std::string& text, SDL_Renderer* renderer);

    // Cant copy
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    // Move constructors
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    SDL_Texture* get_texture();

    ~Texture();
};
}  // namespace engine

#endif  // TP_FINAL_TEXTURE_H
