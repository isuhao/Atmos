﻿#include <shapes/a3Disk.h>
#include <core/a3Ray.h>
#include <core/a3Warp.h>
#include <t3Math/core/t3Matri4x4.h>

a3Disk::a3Disk(const t3Vector3f& center, const float radius, const t3Vector3f& normal) :center(center), radius(radius), normal(normal.getNormalized()), a3Shape("a3Disk")
{
    aabb.set(t3Vector3f(center - radius) , t3Vector3f(center + radius));
}

void a3Disk::set(const t3Vector3f& center, const float radius, const t3Vector3f& normal)
{
    this->center = center;
    this->radius = radius;
    this->normal = normal.getNormalized();
    aabb.set(t3Vector3f(center - radius), t3Vector3f(center + radius));
}

bool a3Disk::intersect(const a3Ray& ray, float* t, float* u, float* v, float* vtu, float* vtv) const
{
    t3Vector3d _normal(-normal), direction(ray.direction);

    // 判断圆盘与直线平行关系
    double denominator = _normal.dot(direction), tHit = 0.0f;

    if(denominator > A3_TOLERANCE_DOUBLE)
    {
        t3Vector3d dir(center - ray.origin);

        tHit = dir.dot(_normal) / denominator;

        if(tHit < ray.minT || tHit > ray.maxT)
            return false;

        // 相交点相对于圆心位置
        t3Vector3d p(ray(tHit)), d = p - t3Vector3d(center);

        // 求取平面上相交点p与中心点center距离
        if(d.lengthSquared() <= radius * radius)
        {
            *t = tHit;

            if(bCalTextureCoordinate)
            {
                // 纹理坐标坐标转换
                t3Vector3f v2, v3, dn(d);
                a3OrthonomalSystem(normal, v2, v3);

                // local to world
                t3Matrix4x4 m(v2.x, v2.y, v2.z, 0.0f,
                              v3.x, v3.y, v3.z, 0.0f,
                              normal.x, normal.y, normal.z, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);

                m = m.getInverse();
                dn = dn * m;

                *vtu = (dn.x + radius) / (2.0f * radius);
                *vtv = (dn.y - radius) / (-2.0f * radius);
            }

            return true;
        }
    }

    return false;
}

t3Vector3f a3Disk::getNormal(const t3Vector3f& hitPoint, float u, float v) const
{
    return normal;
}

 