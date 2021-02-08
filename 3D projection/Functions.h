#ifndef FUNCTIONS
#define FUNCTIONS

#include "Structures.cpp"

void MultiplyMatrixVector(vec3d&, vec3d&, mat4x4&);

vec3d crossProduct(triangle);

vec3d normalize(vec3d);

float dotProduct(vec3d, vec3d);

float mapBetween(float mini, float maxi, float val);

#endif
