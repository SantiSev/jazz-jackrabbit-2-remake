#include "sound_effect.h"

using engine::SoundEffect;

SoundEffect::SoundEffect(const std::string& file): sound(nullptr), channel(-1) {
    sound = Mix_LoadWAV(file.c_str());
    if (sound == nullptr) {
        throw SDLError("Error loading sound from file: " + std::string(Mix_GetError()));
    }
}

void SoundEffect::play_sound(int loops) {
    if (sound == nullptr) {
        return;
    }

    this->channel = Mix_PlayChannel(-1, sound, loops);
    if (this->channel < 0) {
        return;
    }
}

void SoundEffect::pause_sound() { Mix_Pause(this->channel); }

void SoundEffect::set_volume(float volume) {
    if (sound != nullptr) {
        Mix_VolumeChunk(sound, MIX_MAX_VOLUME * volume);
    }
}

SoundEffect::SoundEffect(SoundEffect&& other) noexcept: sound(other.sound), channel(other.channel) {
    other.sound = nullptr;
}

SoundEffect& SoundEffect::operator=(SoundEffect&& other) noexcept {
    if (this == &other)
        return *this;

    sound = other.sound;
    other.sound = nullptr;

    return *this;
}

Mix_Chunk* SoundEffect::get_sound() { return sound; }

SoundEffect::~SoundEffect() {
    if (sound != nullptr) {
        Mix_FreeChunk(sound);
    }
}
