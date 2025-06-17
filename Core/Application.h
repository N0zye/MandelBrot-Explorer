#ifndef APPLICATION_H
#define APPLICATION_H

#include "..\Rendering\MandelbrotExplorer.h"

class Application {
public:
    int screenWidth = 800;
    int screenHeight = 800;
    MandelbrotExplorer* mandelbrotExplorer;

    Application();
    ~Application();
    void updateDrawFrame() const;
    void run() const;
};

#endif //APPLICATION_H