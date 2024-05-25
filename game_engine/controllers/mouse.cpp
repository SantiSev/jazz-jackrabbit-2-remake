#include "mouse.h"

Mouse::Mouse(int x, int y): cursor({x, y}) {}

void Mouse::update(const SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&cursor.x, &cursor.y);
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState(&cursor.x, &cursor.y);
        for (auto handler: signal_handlers) {
            handler(cursor);
        }
    }
}

void Mouse::add_on_click_signal_handler(on_click_signal_handler handler) {
    signal_handlers.push_back(handler);
}

void Mouse::remove_on_click_signal_handler(on_click_signal_handler handler) {
    signal_handlers.remove(handler);
}

Mouse::~Mouse() = default;
