#ifndef TP_FINAL_CLIENT_RENDERER_H
#define TP_FINAL_CLIENT_RENDERER_H
#include "../common_src/common_thread.h"

class Renderer: public Thread {
private:
public:
    Renderer();
    ~Renderer() = default;

    void run() override;
    // Kills the running thread
    void stop() override;
};


#endif
