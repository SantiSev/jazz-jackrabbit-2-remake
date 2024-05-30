#include "texture.h"

Texture::Texture(const std::string& file, SDL_Renderer* renderer): texture(nullptr) {
    texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        throw FileDoesNotExist("Could not load texture from file: " + file);
    }
}

SDL_Texture* Texture::get_texture() { return texture; }

Texture::~Texture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}
