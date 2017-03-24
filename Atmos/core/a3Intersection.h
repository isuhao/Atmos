﻿#ifndef A3_INTERSECTION_H
#define A3_INTERSECTION_H

#include <core/a3Settings.h>
#include <t3Math/core/t3Vector3.h>
#include <core/a3Spectrum.h>

class a3Shape;

class a3Intersection
{
public:
    a3Intersection(): shape(NULL), t(FLT_MAX), u(0), v(0), vtu(0), vtv(0), vtw(0) {}

    bool isValid() const;

    t3Vector3f getNormal() const;

    a3Spectrum getColor() const;

    bool isEmitter() const;

    a3Spectrum getEmission(const t3Vector3f& wo);

    // Distance traveled along the ray
    float t;

    // Intersection point's uv coordinate
    float u, v;

    // Intersection point's uvw texture coordinate
    float vtu, vtv, vtw;

    // Pointer to the associated shape
    a3Shape *shape;

    // Intersection point in 3D coordinates
    t3Vector3f p;
};

#endif