#include "sound_manager.h"

using engine::SoundManager;

SoundManager::SoundManager(std::shared_ptr<engine::ResourcePool> resource_pool):
        resource_pool(resource_pool) {}

void SoundManager::play_sound(sound_type_t sound_type, float volume) {
    auto sound = resource_pool->get_sound(sound_to_string.at(sound_type));
    sound->play_sound(0);
    sound->set_volume(volume);
}

void SoundManager::play_infinity(sound_type_t sound_type, float volume) {
    auto sound = resource_pool->get_sound(sound_to_string.at(sound_type));
    sound->play_sound(-1);
    sound->set_volume(volume);
}

SoundManager::~SoundManager() {}
