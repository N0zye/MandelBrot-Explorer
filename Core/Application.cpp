#include "Application.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


Application::Application() {
    InitWindow(screenWidth, screenHeight, "Mandelbrot Explorer");
    mandelbrotExplorer = new MandelbrotExplorer(screenWidth, screenHeight);
}

Application::~Application() {
    delete mandelbrotExplorer;
    CloseWindow();
}

void Application::updateDrawFrame() const {
    mandelbrotExplorer->update();
    mandelbrotExplorer->draw();
}

void Application::run() const {
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop_arg([](void* arg) {
        static_cast<Application*>(arg)->updateDrawFrame();
    }, (void*)this, 0, 1);
#else
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    while (!WindowShouldClose()) {
        updateDrawFrame();
    }
#endif
}

