﻿#ifndef A3_RENDERER_H
#define A3_RENDERER_H

#include <t3Math/core/t3Vector3.h>

class a3Scene;
class a3CameraSample;
class a3Sensor;
class a3Ray;
class a3Intersection;

class a3Renderer
{
public:
	a3Renderer();

	~a3Renderer();

    virtual void render(const a3Scene* scene) = 0;

    virtual void postEffect();

    float progress;
};

#endif 