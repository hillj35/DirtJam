#version 330 core

in vec3 vertexColor;
in vec3 vertexPosition;
in vec2 outUV;
out vec4 fragColor;

#define PI 3.141592653589793238462

// UE4's PseudoRandom function
// https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Shaders/Private/Random.ush
float pseudo(vec2 v) {
    v = fract(v / 128.) * 128. + vec2(-64.340622, -72.465622);
    return fract(dot(v.xyx * v.xyy, vec3(20.390625, 60.703125, 2.4281209)));
}

// Takes an xz positions and turns them into a random number between 0 and 1 using the above pseudo random function
float HashPosition(vec2 pos) {
    //    return pseudo(pos * vec2(_Seed, _Seed + 4));
    return pseudo(pos * vec2(423487, 423487 + 4));
}

// Generates a random gradient vector for the perlin noise lattice points
vec2 RandVector(float seed) {
    float theta = seed * 360 * 2 - 360;
    //    theta += _GradientRotation;
    theta = theta * PI / 180.0;
    return normalize(vec2(cos(theta), sin(theta)));
}

vec2 quinticInterpolation(vec2 t) {
    return t * t * t * (t * (t * vec2(6) - vec2(15)) + vec2(10));
}

vec2 quinticDerivative(vec2 t) {
    return vec2(30) * t * t * (t * (t - vec2(2)) + vec2(1));
}

vec3 perlin_noise2D(vec2 pos) {
    vec2 latticeMin = floor(pos);
    vec2 latticeMax = ceil(pos);

    vec2 remainder = fract(pos);

    // Lattice Corners
    vec2 c00 = latticeMin;
    vec2 c10 = vec2(latticeMax.x, latticeMin.y);
    vec2 c01 = vec2(latticeMin.x, latticeMax.y);
    vec2 c11 = latticeMax;

    // Gradient Vectors assigned to each corner
    vec2 g00 = RandVector(HashPosition(c00));
    vec2 g10 = RandVector(HashPosition(c10));
    vec2 g01 = RandVector(HashPosition(c01));
    vec2 g11 = RandVector(HashPosition(c11));

    // Directions to position from lattice corners
    vec2 p0 = remainder;
    vec2 p1 = p0 - vec2(1.0);

    vec2 p00 = p0;
    vec2 p10 = vec2(p1.x, p0.y);
    vec2 p01 = vec2(p0.x, p1.y);
    vec2 p11 = p1;

    vec2 u = quinticInterpolation(remainder);
    vec2 du = quinticDerivative(remainder);

    float a = dot(g00, p00);
    float b = dot(g10, p10);
    float c = dot(g01, p01);
    float d = dot(g11, p11);

    // Expanded interpolation freaks of nature from https://iquilezles.org/articles/gradientnoise/
    float noise = a + u.x * (b - a) + u.y * (c - a) + u.x * u.y * (a - b - c + d);

    vec2 gradient = g00 + u.x * (g10 - g00) + u.y * (g01 - g00) + u.x * u.y * (g00 - g10 - g01 + g11) + du * (u.yx * (a - b - c + d) + vec2(b, c) - a);
    return vec3(noise, gradient);
}

void main() {
    vec3 noise_pos = vertexPosition + vec3(4.0, 0, 4.0) / 50000.0f;
    fragColor = vec4(perlin_noise2D(noise_pos.xz).xxx, 1);
}