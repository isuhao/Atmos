﻿// shape
#include <shapes/a3Sphere.h>
#include <shapes/a3Plane.h>
#include <shapes/a3Disk.h>
#include <shapes/a3Triangle.h>

#include <Common/t3Timer.h>

// light
#include <lights/a3InfiniteAreaLight.h>
#include <lights/a3PointLight.h>
#include <lights/a3SpotLight.h>

// renderer
#include <renderers/a3SamplerRenderer.h>
#include <renderers/a3NormalMapRenderer.h>
#include <renderers/a3SingleRayRenderer.h>

#include <samples/a3RandomSampler.h>
#include <sensors/a3PerspectiveSensor.h>

//integrator
#include <integrator/a3PathIntegrator.h>
#include <integrator/a3DirectLighting.h>

// bsdf
#include <bsdf/a3Diffuse.h>
#include <bsdf/a3Conductor.h>
#include <bsdf/a3Dielectric.h>

// core
#include <core/log/a3Log.h>
#include <core/a3ModelImporter.h>
#include <core/a3Common.h>
#include <core/image/a3NormalMap.h>
#include <core/image/a3Film.h>
#include <core/a3Scene.h>

enum a3MaterialType
{
    A3_MATERIAL_NONE = 0,
    A3_MATERIAL_DIFFUSS = 1,
    A3_MATERIAL_SPECULAR = 2,
    A3_METERIAL_REFRACTION = 3
};

//#define WENDAOQIUER
#define INFINITEAREA_LIGHT
//#define CORNEL_BOX

int main()
{
    a3Film* image = new a3Film(900, 900, "../../../../resources/results/hello", A3_IMAGE_PNG);

    a3NormalMap* normalMap = new a3NormalMap(*image);
    normalMap->setFileName("../../../../resources/results/normalMap");

#ifdef INFINITEAREA_LIGHT
    a3PerspectiveSensor* camera = new a3PerspectiveSensor(t3Vector3f(0, 50, -100), t3Vector3f(0, 0, 20), t3Vector3f(0, 1, 0), 40, 210.0f, 0.0f, image, normalMap);
#endif

#ifdef WENDAOQIUER
    a3PerspectiveSensor* camera = new a3PerspectiveSensor(t3Vector3f(0, -150, -10), t3Vector3f(0, 0, 0), t3Vector3f(0, 0, 1), 55.517f,  210.0f, 0.0f, image, normalMap);
#endif

#ifdef CORNEL_BOX
    a3PerspectiveSensor* camera = new a3PerspectiveSensor(t3Vector3f(50.0f, 52.0f, 295.6f), t3Vector3f(50.0f, 52.0f - 0.042612f, 295.6f - 1.0f), t3Vector3f(0, 1, 0),  40.0f, 210.0f, 0.0f,  image, normalMap);
#endif
    camera->print();

    a3Scene* scene = new a3Scene();

    auto addShape = [&scene](a3Shape* s, a3Spectrum R, a3Spectrum emission, int type)
    {
        s->emission = emission;

        switch(type)
        {
        case A3_MATERIAL_DIFFUSS:
            s->bsdf = new a3Diffuse(R);
            break;
        case A3_MATERIAL_SPECULAR:
            s->bsdf = new a3Conductor(R);
            break;
        case A3_METERIAL_REFRACTION:
            s->bsdf = new a3Dieletric(R);
            break;
        default:
            break;
        }

        scene->addShape(s);
    };

#ifdef INFINITEAREA_LIGHT
    //scene->addLight(new a3InfiniteAreaLight("../../../../resources/images/skylightSurreal.png"));
    scene->addLight(new a3PointLight(t3Vector3f(0, 10, -100), a3Spectrum(500000.0f)));

    a3ModelImporter importer;
    //std::vector<a3Shape*>* shapes = importer.load("../../../../resources/models/spheres.obj");
    std::vector<a3Shape*>* shapes = importer.load("../../../../resources/models/mitsuba.obj");

    if(shapes)
    {
        for(auto s : *shapes)
            addShape(s, t3Vector3f(1, 1, 1), t3Vector3f(0, 0, 0), A3_MATERIAL_SPECULAR);

        //addShape(new a3Sphere(t3Vector3f(-40, -60, 25), 25), t3Vector3f(1.0f, 1.0f, 1.0f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
        //addShape(new a3Sphere(t3Vector3f(40, 30, 25), 25), t3Vector3f(1.0f, 1.0f, 1.0f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);

        //addShape(new a3Plane(t3Vector3f(0, 0, -20), t3Vector3f(0, 0, 1)), t3Vector3f(0.5, 0.5, 0.5), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
        addShape(new a3Disk(t3Vector3f(0, 0, 0), 1000, t3Vector3f(0, 1, 0)), t3Vector3f(0.5, 0.5, 0.5), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
    }

#endif

#ifdef WENDAOQIUER
    scene->addLight(new a3InfiniteAreaLight("../../../resources/images/pisaLatlong.png"));

    addShape(new a3Sphere(t3Vector3f(-30, -8, 0), 37), t3Vector3f(1, 1, 1), t3Vector3f(0, 0, 0), A3_METERIAL_REFRACTION);

    // 无限远平面
    addShape(new a3Plane(t3Vector3f(0, 0, -37), t3Vector3f(0, 0, 1)), t3Vector3f(0.5, 0.5, 0.5), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
#endif

#ifdef CORNEL_BOX
    // Spheres  
    addShape(new a3Sphere(t3Vector3f(73.0f, 16.5f, 47.0f), 16.5f), t3Vector3f(1.0f, 1.0f, 1.0f), t3Vector3f(0.0f, 0.0f, 0.0f), A3_MATERIAL_SPECULAR);
    addShape(new a3Sphere(t3Vector3f(27.0f, 16.5f, 78.0f), 16.5f), t3Vector3f(1.0f, 1.0f, 1.0f), t3Vector3f(0.0f, 0.0f, 0.0f), A3_METERIAL_REFRACTION);

    // Plane
    addShape(new a3Plane(t3Vector3f(1.0f, 40.8f, 81.6f), t3Vector3f(1.0f, 0.0f, 0.0f)), t3Vector3f(0.25f, 0.25f, 0.75f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
    addShape(new a3Plane(t3Vector3f(99.0f, 40.8f, 81.6f), t3Vector3f(-1.0f, 0.0f, 0.0f)), t3Vector3f(0.75f, 0.25f, 0.25f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
    addShape(new a3Plane(t3Vector3f(50.0f, 40.8f, 0.0f), t3Vector3f(0.0f, 0.0f, 1.0f)), t3Vector3f(0.75f, 0.75f, 0.75f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
    //addShape(new a3Plane(t3Vector3f(50.0f, 40.8f, 310.0f), t3Vector3f(0.0f, 0.0f, 1)), t3Vector3f(0.0f, 0.0f, 0.0f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
    addShape(new a3Plane(t3Vector3f(50.0f, 0.0f, 81.6f), t3Vector3f(0.0f, 1.0f, 0.0f)), t3Vector3f(0.75f, 0.75f, 0.75f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);
    addShape(new a3Plane(t3Vector3f(50.0f, 81.6f, 81.6f), t3Vector3f(0.0f, -1.0f, 0.0f)), t3Vector3f(0.75f, 0.75f, 0.75f), t3Vector3f(0, 0, 0), A3_MATERIAL_DIFFUSS);

    // 光源
    //addShape(new a3Sphere(t3Vector3f(50.0f, 681.6f - 0.27f, 81.6f), 600.0f), t3Vector3f(0.0f, 0.0f, 0.0f), t3Vector3f(5000.0f, 5000.0f, 5000.0f), A3_MATERIAL_DIFFUSS);
    //scene->addLight(new a3PointLight(t3Vector3f(50.0f, 81.6f - 0.27f, 81.6f), a3Spectrum(200000.0f)));
    scene->addLight(new a3SpotLight(t3Vector3f(50.0f, 81.6f - 0.27f, 81.6f), t3Vector3f(0.0f, -1.0f, 0.0f), a3Spectrum(1000000.0f), 40, 5));

#endif

    //a3SingleRayRenderer* renderer = new a3SingleRayRenderer(325, 553);
    //a3NormalMapRenderer* renderer = new a3NormalMapRenderer();
    a3SamplerRenderer* renderer = new a3SamplerRenderer(6);
    renderer->sampler = new a3RandomSampler();
    //renderer->integrator = new a3DirectLightingIntegrator();
    renderer->integrator = new a3PathIntegrator(7);
    renderer->camera = camera;

    t3Timer timer;
    timer.start();

    renderer->render(scene);

    timer.end();

    a3Log::info("Cost time: %f sec", timer.difference());

    getchar();
    return 0;
} 