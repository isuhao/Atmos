#include <shapes/a3Disk.h>
#include <core/a3Ray.h>
#include <core/a3Warp.h>
#include <core/a3Record.h>
#include <core/random/a3Random.h>

a3Disk::a3Disk(const t3Matrix4x4 & objectToWorld, const t3Matrix4x4 & worldToObject, const float radius)
    :radius(radius), a3Shape(objectToWorld, worldToObject)
{
    name = "a3Disk";
}

a3Disk::~a3Disk()
{
}

bool a3Disk::intersect(const a3Ray & _ray, float * t, float * u, float * v) const
{
    a3Ray ray = _ray;
    ray.transform(worldToObject);

    //--!See https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection for detail
    t3Vector3f normal(0, 1, 0);

    // paralle or not
    float denominator = normal.dot(ray.direction), tHit = 0.0f;

    if(t3Math::Abs(denominator) > A3_EPSILON_FLOAT)
    {
        tHit = (-ray.origin).dot(normal) / denominator;

        if(tHit < ray.minT || tHit > ray.maxT)
            return false;

        // distance between hitpoint and disk center
        if(ray(tHit).lengthSquared() <= radius * radius)
        {
            *t = tHit;

            return true;
        }
    }

    return false;
}

void a3Disk::sample(a3ShapeSamplingRecord & sRec) const
{
    static a3Random r;
    // uniform sampling the disk
    t3Vector2f sampledP = a3UniformSampleDisk(r.randomFloat(), r.randomFloat());

    sRec.p = objectToWorld * t3Vector3f(sampledP.x, sampledP.y, 0.0f);
    sRec.pdf = pdf(sRec);
    sRec.normal = getNormal(t3Vector3f::zero(), 0, 0);
}

t3Vector3f a3Disk::getNormal(const t3Vector3f & hitPoint, float u, float v) const
{
    return (objectToWorld * t3Vector3f(0, 1, 0)).getNormalized();
}

float a3Disk::area() const
{
    return T3MATH_PI * radius *radius;
}
