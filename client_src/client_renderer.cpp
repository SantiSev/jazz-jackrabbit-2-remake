#include "client_renderer.h"

#include <iostream>

void Renderer::run() { std::cout << "Hello, World!" << std::endl; }

void Renderer::stop() { std::cout << "bye, World!" << std::endl; }

Renderer::Renderer() {}
