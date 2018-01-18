﻿#include <core/a3Scene.h>
#include <core/log/a3Log.h>
#include <core/a3Ray.h>
#include <core/random/a3Random.h>
#include <core/a3Record.h>

#include <shapes/a3Shape.h>
#include <lights/a3Light.h>
#include <accelerators/a3PrimitiveSet.h>

a3Scene::a3Scene()
{

}

// free the lights and shape outside
a3Scene::~a3Scene()
{
}

bool a3Scene::addShape(a3Shape* shape)
{
    if(!check()) return false;

    return primitiveSet->addShape(shape);
}

bool a3Scene::addLight(a3Light* light)
{
    if(!light)
    {
        a3Log::error("a3Scene::addLight() not allowed nullptr.\n", light);
        return false;
    }

    lights.push_back(light);
    return true;
}

bool a3Scene::check() const
{
    if(!primitiveSet)
    {
        a3Log::error("Before a3Scene::render() was called, primitiveSet: %d not allocated\n", primitiveSet);
        return false;
    }

    return true;
}

bool a3Scene::intersect(const a3Ray& ray, a3IntersectRecord* intersection) const
{
    return primitiveSet->intersect(ray, intersection);
}

bool a3Scene::intersect(const a3Ray& ray) const
{
    return primitiveSet->intersect(ray);
}

a3Spectrum a3Scene::sampleDirect(a3LightSamplingRecord & dRec) const
{
    if(lights.size() == 0)
        return a3Spectrum();

    int numLights = lights.size();

    // uniform sampling lights
    static a3Random r;
    int index = r.randomFloat() * numLights;
    index = index >= numLights ? numLights - 1 : index;

    a3Spectrum L = lights[index]->sampleDirect(dRec);

    if(dRec.pdf != 0)
    {
        // test visibility
        a3Ray ray(dRec.p, dRec.d, A3_EPSILON, dRec.distance * (1 - A3_EPSILON_SHADOW));

        if(intersect(ray))
            // sth. between sampled point and hitpoint
            return a3Spectrum::zero();
        else
        {
            // lights pdf
            L /= dRec.pdf;

            // sample one light equal to all of it
            return  numLights * L;
        }
    }
    else
        // can't be sampled on the light
        return a3Spectrum::zero();
}

a3Spectrum a3Scene::evalEnvironment(const a3Ray& ray) const
{
    a3Spectrum L;

    // add radiance from environment light
    for(auto l : lights)
        if(l->isEnvironment())
            L += l->evalEnvironment(ray);

    return L;
}




 