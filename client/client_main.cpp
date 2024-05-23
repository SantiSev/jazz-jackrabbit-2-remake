#include <cstdlib>
#include <iostream>
#include <string>

#include "../common/common_thread.h"

#include "client_renderer.h"

//#include <SDL2pp/SDL2pp.hh>
//
// using namespace SDL2pp;

int main(int argc, char* argv[]) {
    try {
        if (argc == 3) {
            const std::string hostname = argv[1];
            const std::string service = argv[2];

            //            SDL sdl(SDL_INIT_VIDEO);


            Renderer renderer;
            renderer.start();
            renderer.stop();
            renderer.join();


        } else {
            std::cout << "Expected: " << argv[0] << " <hostname> <service>\n" << std::endl;
            exit(1);
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
    return 0;
}
