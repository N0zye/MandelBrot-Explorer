#ifndef RLYDESPERATEATTEMPT_H
#define RLYDESPERATEATTEMPT_H

inline const char *fsCode = R"(
#version 100

precision highp float;

// Uniforms provided by the application
uniform vec2 u_resolution;
uniform float u_zoom;
uniform vec2 u_offset;
uniform int u_maxIterations;

// Output color
vec3 hsv2rgb(vec3 hsv) {
    float hh = mod(hsv.x, 360.0) / 60.0;
    int i = int(hh);
    float ff = hh - float(i);

    float p = hsv.z * (1.0 - hsv.y);
    float q = hsv.z * (1.0 - (hsv.y * ff));
    float t = hsv.z * (1.0 - (hsv.y * (1.0 - ff)));

    if (i == 0) return vec3(hsv.z, t, p);
    if (i == 1) return vec3(q, hsv.z, p);
    if (i == 2) return vec3(p, hsv.z, t);
    if (i == 3) return vec3(p, q, hsv.z);
    if (i == 4) return vec3(t, p, hsv.z);
    return vec3(hsv.z, p, q);
}

void main() {
    // Normalize coordinates to [-2, 2] range
    vec2 centered = (gl_FragCoord.xy / u_resolution - 0.5) * 4.0;
    vec2 uv = u_offset + centered / u_zoom;

    vec2 c = uv;
    vec2 z = vec2(0.0);

    int i;
    for (int j = 0; j < 400; j++) {
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = 2.0 * z.x * z.y + c.y;
        z = vec2(x, y);

        if (dot(z, z) > 4.0) {
            break;
        }
        i++;
    }

    if(i == u_maxIterations) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else {
        float hue = float(i) / float(u_maxIterations) * 360.0;
        gl_FragColor = vec4(hsv2rgb(vec3(hue, 0.8, 0.8)), 1.0);
    }
}
)";

#endif //RLYDESPERATEATTEMPT_H
