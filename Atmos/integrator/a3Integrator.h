﻿#ifndef A3_INTERGRATOR_H
#define A3_INTERGRATOR_H

#include <core/a3Spectrum.h>

class a3Ray;
class a3Scene;

class a3Integrator
{
public:
    a3Integrator() {}

    virtual ~a3Integrator() {}

    // Sample the incident radiance along a ray.
    virtual a3Spectrum Li(const a3Ray& ray, const a3Scene& scene) const = 0;
};

#endif
 