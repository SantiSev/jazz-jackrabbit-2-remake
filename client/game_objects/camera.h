#ifndef CAMERA_H
#define CAMERA_H

#include <list>
#include <memory>

#include "../../game_engine/gui/canvas_object.h"

#include "map.h"

namespace engine {
class Camera: public CanvasObject {
private:
    SDL_Rect screen;
    std::list<std::shared_ptr<CanvasObject>> objects;
    std::shared_ptr<Map> map;

public:
    Camera(int x, int y, int w, int h);

    void add_object(std::shared_ptr<CanvasObject> object);
    void remove_object(std::shared_ptr<CanvasObject> object);
    void set_map(std::shared_ptr<Map> map);

    // Recenter the camera on the given body
    void recenter(const SDL_Rect& body);

    void draw(SDL_Renderer* renderer, int it) override;

    SDL_Rect& get_body() override;

    ~Camera() override;
};
}  // namespace engine

#endif  // CAMERA_H
