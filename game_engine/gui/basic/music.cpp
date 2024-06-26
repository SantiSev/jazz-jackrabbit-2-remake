#include "music.h"

using engine::Music;

Music::Music(const std::string& file): sound(nullptr) {
    sound = Mix_LoadMUS(file.c_str());
    if (sound == nullptr) {
        throw SDLError("Error loading sound from file: " + std::string(Mix_GetError()));
    }
}

void Music::play_sound(int loops) {
    if (sound == nullptr) {
        return;
    }

    if (Mix_PlayMusic(sound, loops) < 0) {
        throw SDLError("Error playing channel (Music): " + std::string(Mix_GetError()));
    }
}

void Music::pause_sound() { Mix_PauseMusic(); }

void Music::set_volume(float volume) {
    if (sound != nullptr) {
        Mix_VolumeMusic(MIX_MAX_VOLUME * volume);
    }
}

Music::Music(Music&& other) noexcept: sound(other.sound) { other.sound = nullptr; }

Music& Music::operator=(Music&& other) noexcept {
    if (this == &other)
        return *this;

    sound = other.sound;
    other.sound = nullptr;

    return *this;
}

Mix_Music* Music::get_sound() { return sound; }

Music::~Music() {
    if (sound != nullptr) {
        Mix_FreeMusic(sound);
    }
}
