float lerp(float a, float b, float t) {
    return (1.0f - t)*a + b*t;
}

float inv_lerp(float a, float b, float v) {
    return (v - a)/(b - a);
}

float remap(float iMin, float iMax, float oMin, float oMax, float v) {
    float t = inv_lerp(iMin, iMax, v);
    return lerp(oMin, oMax, t);
}
