#include "MandelbrotExplorer.h"
#include "rlydesperateattempt.h"
#include <iostream>
#include <fstream>

#if defined(PLATFORM_WEB)
    #define GLSL_VERSION            100
#else
    #define GLSL_VERSION            330
#endif

MandelbrotExplorer::MandelbrotExplorer(int screenWidth, int screenHeight) {
    this->resolution = {(float)screenWidth, (float)screenHeight};
    this->zoom = 1.0;
    this->offset = {0.0, 0.0};
    this->maxIterations = 400;

#if defined(PLATFORM_DESKTOP)
    this->mandelbrotShader = LoadShader(nullptr,TextFormat("resources/shaders/glsl%i/mandelbrot.fs", GLSL_VERSION));
#else
    this->mandelbrotShader = LoadShaderFromMemory(nullptr, fsCode);
#endif
    this->resolutionLoc = GetShaderLocation(mandelbrotShader, "u_resolution");
    this->zoomLoc = GetShaderLocation(mandelbrotShader, "u_zoom");
    this->offsetLoc = GetShaderLocation(mandelbrotShader, "u_offset");
    this->maxIterLoc = GetShaderLocation(mandelbrotShader, "u_maxIterations");

    SetShaderValue(mandelbrotShader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(mandelbrotShader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
    SetShaderValue(mandelbrotShader, offsetLoc, &offset, SHADER_UNIFORM_VEC2);
    SetShaderValue(mandelbrotShader, maxIterLoc, &maxIterations, SHADER_UNIFORM_INT);
}

MandelbrotExplorer::~MandelbrotExplorer() {
    UnloadShader(mandelbrotShader);
}
void MandelbrotExplorer::update() {
    // TODO: maybe mouse panning and zooming with scroll wheel.
    const float delta = 0.01/(0.5*zoom);
    if(IsKeyDown(KEY_Z)) zoom *= 1.01;
    if(IsKeyDown(KEY_X)) zoom /= 1.01;
    if(IsKeyDown(KEY_UP)) offset.y += delta;
    if(IsKeyDown(KEY_DOWN)) offset.y -= delta;
    if(IsKeyDown(KEY_LEFT)) offset.x -= delta;
    if(IsKeyDown(KEY_RIGHT)) offset.x += delta;

    // Update uniforms
    SetShaderValue(mandelbrotShader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
    SetShaderValue(mandelbrotShader, offsetLoc, &offset, SHADER_UNIFORM_VEC2);
    SetShaderValue(mandelbrotShader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(mandelbrotShader, maxIterLoc, &maxIterations, SHADER_UNIFORM_INT);

}

void MandelbrotExplorer::draw() const {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginShaderMode(mandelbrotShader);
    DrawRectangle(0, 0, resolution.x, resolution.y, WHITE);
    EndShaderMode();
    DrawFPS(0, 0);
    EndDrawing();
}

Color MandelbrotExplorer::CalculateColor(std::complex<double> c) const {
    std::complex<double> z(0, 0);
    int i = 0;

    while(abs(z) < 2 && i < maxIterations) {
        z = z * z + c;
        i++;
    }
    if(i == maxIterations) {
        return BLACK;
    }
    return ColorFromHSV((float)i / maxIterations * 360.0, 0.8f, 0.8f);
}