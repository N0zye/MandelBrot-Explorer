#ifndef MANDELBROTEXPLORER_H
#define MANDELBROTEXPLORER_H

#include "raylib.h"
#include <complex>

class MandelbrotExplorer {
public:
    Vector2 resolution{};
    float zoom;
    Vector2 offset{};
    int maxIterations;

    MandelbrotExplorer(int screenWidth, int screenHeight);
    ~MandelbrotExplorer();
    void update();
    void draw() const;
private:
    Shader mandelbrotShader{};

    // Shader variables locations
    int resolutionLoc;
    int zoomLoc;
    int offsetLoc;
    int maxIterLoc;

    Color CalculateColor(std::complex<double> c) const;
};

#endif //MANDELBROTEXPLORER_H
