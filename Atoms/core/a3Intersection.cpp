﻿#include <core/a3Intersection.h>
#include <shapes/a3Shape.h>

bool a3Intersection::isValid() const
{
    return t != FLT_MAX;
}

t3Vector3f a3Intersection::getNormal() const
{
    if(shape)
        return shape->getNormal(p, u, v);
    else
        return t3Vector3f::zero();
}

bool a3Intersection::isEmitter() const
{
    if(shape)
        return shape->isEmitter();
    else
        return false;
}
 