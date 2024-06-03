#include "texture.h"

using engine::Texture;

Texture::Texture(const std::string& file, SDL_Renderer* renderer): texture(nullptr) {
    texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        throw SDLError("Error loading texture from image: " + std::string(SDL_GetError()));
    }
}

Texture::Texture(const std::shared_ptr<Font>& font, const SDL_Color& color, const std::string& text,
                 SDL_Renderer* renderer):
        texture(nullptr) {
    SDL_Surface* surface = TTF_RenderText_Solid(font->get_font(), text.c_str(), color);
    if (surface == nullptr) {
        throw SDLError("Error creating surface from text: " + std::string(TTF_GetError()));
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        throw SDLError("Error creating texture from surface: " + std::string(SDL_GetError()));
    }
}

SDL_Texture* Texture::get_texture() { return texture; }

Texture::Texture(Texture&& other) noexcept: texture(other.texture) { other.texture = nullptr; }

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this == &other)
        return *this;

    texture = other.texture;
    other.texture = nullptr;

    return *this;
}

Texture::~Texture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}
