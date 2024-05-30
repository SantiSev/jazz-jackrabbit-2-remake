#ifndef TP_FINAL_TEXTURE_H
#define TP_FINAL_TEXTURE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../errors.h"

class Texture {
private:
    SDL_Texture* texture;

public:
    explicit Texture(const std::string& file, SDL_Renderer* renderer);

    SDL_Texture* get_texture();

    ~Texture();
};


#endif  // TP_FINAL_TEXTURE_H
