#ifndef TP_FINAL_SOUND_MANAGER_H
#define TP_FINAL_SOUND_MANAGER_H

#include <memory>

#include "../../../common/sound_enum.h"
#include "../basic/resource_pool.h"

namespace engine {
class SoundManager {
private:
    std::shared_ptr<engine::ResourcePool> resource_pool;

public:
    explicit SoundManager(std::shared_ptr<engine::ResourcePool> resource_pool);

    void play_sound(sound_type_t sound_type, float volume);

    void play_infinity(sound_type_t sound_type, float volume);

    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager& other) = delete;

    SoundManager(SoundManager&& other) = delete;
    SoundManager& operator=(SoundManager&& other) = delete;

    ~SoundManager();
};
}  // namespace engine

#endif  // TP_FINAL_SOUND_MANAGER_H
