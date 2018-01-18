#include <shapes/a3Shape.h>
#include <core/a3Ray.h>
#include <core/log/a3Log.h>
#include <core/a3Utils.h>

a3Shape::a3Shape(const t3Matrix4x4 & objectToWorld, const t3Matrix4x4 & worldToObject)
    :objectToWorld(objectToWorld), worldToObject(worldToObject), name("a3Shape")
{

}

a3Shape::~a3Shape()
{
}

bool a3Shape::intersect(const a3Ray & ray, float * t, float * u, float * v) const
{
    a3FuncNotImplementedError("a3Shape", "intersect");

    return false;
}

float a3Shape::area() const
{
    a3FuncNotImplementedError("a3Shape", "area");

    return 0.0f;
}

void a3Shape::sample(a3ShapeSamplingRecord & sRec) const
{
    a3FuncNotImplementedError("a3Shape", "sample");
}

float a3Shape::pdf(const a3ShapeSamplingRecord & sRec) const
{
    return 1 / area();
}

t3Vector3f a3Shape::getNormal(const t3Vector3f & hitPoint, float u, float v) const
{
    a3FuncNotImplementedError("a3Shape", "getNormal");

    return t3Vector3f::zero();
}

void a3Shape::setBSDF(a3BSDF* bsdf)
{
    this->bsdf = bsdf;
}

a3BSDF* a3Shape::getBSDF() const
{
    return bsdf;
}