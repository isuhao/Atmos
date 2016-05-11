#include <accelerators/a3Exhaustive.h>
#include <core/a3Intersection.h>
#include <shapes/a3Sphere.h>
#include <core/a3Ray.h>

bool a3Exhaustive::intersect(const a3Ray& ray, a3Intersection* intersection) const
{
    float minT = FLT_MAX;
    float t = FLT_MAX;
    float u = 0, v = 0;
    float vtu = 0, vtv = 0;

    for(int i = 0; i < primitives.size(); i++)
    {
        if((primitives[i]->intersect(ray, &t, &u, &v, &vtu, &vtv)) && t > A3_TOLERANCE_FLOAT && t < minT)
        {
            minT = t;

            // 序号代替ID
            intersection->shape = primitives[i];
        }
    }

    if(minT < FLT_MAX && minT > A3_TOLERANCE_FLOAT)
    {
        intersection->t = minT;

        // 接触点初始化
        intersection->p = (ray) (minT);

        // 求交测试若遇到三角形那么[u, v]将被赋值
        intersection->u = u;
        intersection->v = v;

        // 若有纹理存在则纹理坐标将被赋值
        intersection->vtu = vtu;
        intersection->vtv = vtv;

        return true;
    }
    else
    {
        // 用于valid判断
        intersection->t = FLT_MAX;

        return false;
    }
}

bool a3Exhaustive::intersect(const a3Ray& ray) const
{
    float minT = FLT_MAX;
    float t = FLT_MAX;
    float u = 0, v = 0;
    float vtu = 0, vtv = 0;

    for(int i = 0; i<primitives.size(); i++)
    {
        if((primitives[i]->intersect(ray, &t, &u, &v, &vtu, &vtv)) && t > A3_TOLERANCE_FLOAT && t < minT)
            minT = t;
    }

    if(minT < ray.maxT && minT > ray.minT)
        return true;
    else
        return false;
}

