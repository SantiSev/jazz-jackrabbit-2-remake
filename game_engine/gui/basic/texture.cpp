#include "texture.h"

Texture::Texture(const std::string& file, SDL_Renderer* renderer): texture(nullptr) {
    texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        throw FileDoesNotExist("Could not load texture from file: " + file);
    }
}

Texture::Texture(std::shared_ptr<Font> font, const SDL_Color& color, const std::string& text,
                 SDL_Renderer* renderer):
        texture(nullptr) {
    SDL_Surface* surface = TTF_RenderText_Solid(font->get_font(), text.c_str(), color);
    if (surface == nullptr) {
        throw FileDoesNotExist("Could not render text surface.");
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        throw FileDoesNotExist("Could not create texture from surface.");
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
