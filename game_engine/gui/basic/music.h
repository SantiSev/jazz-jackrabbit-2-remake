#ifndef TP_FINAL_MUSIC_H
#define TP_FINAL_MUSIC_H

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../../errors.h"

#include "sound.h"

namespace engine {
class Music: public Sound {
private:
    Mix_Music* sound;

public:
    explicit Music(const std::string& file);

    void play_sound(int loops) override;

    void pause_sound() override;

    void set_volume(float volume) override;

    // Cant copy
    Music(const Music& other) = delete;
    Music& operator=(const Music& other) = delete;

    // Move constructors
    Music(Music&& other) noexcept;
    Music& operator=(Music&& other) noexcept;

    Mix_Music* get_sound();

    ~Music();
};
}  // namespace engine

#endif  // TP_FINAL_SOUND_H
