#ifndef TP_FINAL_TEXTURE_H
#define TP_FINAL_TEXTURE_H

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../errors.h"

#include "font.h"

class Texture {
private:
    SDL_Texture* texture;

public:
    explicit Texture(const std::string& file, SDL_Renderer* renderer);
    explicit Texture(std::shared_ptr<Font> font, const SDL_Color& color, const std::string& text,
                     SDL_Renderer* renderer);

    // Cant copy
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    // Move constructors
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    SDL_Texture* get_texture();

    ~Texture();
};


#endif  // TP_FINAL_TEXTURE_H
