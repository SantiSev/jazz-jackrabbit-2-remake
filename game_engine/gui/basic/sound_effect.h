#ifndef TP_FINAL_SOUND_EFFECT_H
#define TP_FINAL_SOUND_EFFECT_H

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../../errors.h"

#include "sound.h"

namespace engine {
class SoundEffect: public Sound {
private:
    Mix_Chunk* sound;
    int channel;

public:
    explicit SoundEffect(const std::string& file);

    void play_sound(int loops) override;

    void pause_sound() override;

    void set_volume(float volume) override;

    // Cant copy
    SoundEffect(const SoundEffect& other) = delete;
    SoundEffect& operator=(const SoundEffect& other) = delete;

    // Move constructors
    SoundEffect(SoundEffect&& other) noexcept;
    SoundEffect& operator=(SoundEffect&& other) noexcept;

    Mix_Chunk* get_sound();

    ~SoundEffect();
};
}  // namespace engine

#endif  // TP_FINAL_SOUND_EFFECT_H
