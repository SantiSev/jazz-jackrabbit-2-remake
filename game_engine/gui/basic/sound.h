#ifndef TP_FINAL_SOUND_H
#define TP_FINAL_SOUND_H

#include <string>

namespace engine {
class Sound {
public:
    Sound() {}

    virtual void play_sound(int loops) = 0;

    virtual void pause_sound() = 0;

    virtual void set_volume(float volume) = 0;

    // Cant copy
    Sound(const Sound& other) = delete;
    Sound& operator=(const Sound& other) = delete;

    // Move constructors
    Sound(Sound&& other) noexcept;
    Sound& operator=(Sound&& other) noexcept;

    ~Sound() {}
};
}  // namespace engine

#endif  // TP_FINAL_SOUND_H
