﻿#include <shapes/a3Triangle.h>
#include <core/a3Ray.h>
#include <t3Math/core/t3Math.h>

a3Triangle::a3Triangle() :v0(t3Vector3f::zero()), v1(t3Vector3f::zero()), v2(t3Vector3f::zero()), bEnableBackfaceCulling(false), a3Shape("a3Triangle")
{
    aabb.set(t3Vector3f(t3Math::Min(v0.x, v1.x, v2.x), 
                        t3Math::Min(v0.y, v1.y, v2.y), 
                        t3Math::Min(v0.z, v1.z, v2.z)),
             t3Vector3f(t3Math::Max(v0.x, v1.x, v2.x),
                        t3Math::Max(v0.y, v1.y, v2.y),
                        t3Math::Max(v0.z, v1.z, v2.z)));
}

a3Triangle::a3Triangle(t3Vector3f v0, t3Vector3f v1, t3Vector3f v2) :v0(v0), v1(v1), v2(v2), bEnableBackfaceCulling(false), a3Shape("a3Triangle")
{
    aabb.set(t3Vector3f(t3Math::Min(v0.x, v1.x, v2.x),
                        t3Math::Min(v0.y, v1.y, v2.y),
                        t3Math::Min(v0.z, v1.z, v2.z)),
             t3Vector3f(t3Math::Max(v0.x, v1.x, v2.x),
                        t3Math::Max(v0.y, v1.y, v2.y),
                        t3Math::Max(v0.z, v1.z, v2.z)));
}


void a3Triangle::set(t3Vector3f v0, t3Vector3f v1, t3Vector3f v2)
{
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;

    aabb.set(t3Vector3f(t3Math::Min(v0.x, v1.x, v2.x),
                        t3Math::Min(v0.y, v1.y, v2.y),
                        t3Math::Min(v0.z, v1.z, v2.z)),
             t3Vector3f(t3Math::Max(v0.x, v1.x, v2.x),
                        t3Math::Max(v0.y, v1.y, v2.y),
                        t3Math::Max(v0.z, v1.z, v2.z)));
}

bool a3Triangle::intersect(const a3Ray& ray, float* t, float* _u, float* _v, float* vtu, float* vtv) const
{
    double tHit, u, v;

    t3Vector3d dir(ray.direction);
    t3Vector3d v0v1(v1 - v0);
    t3Vector3d v0v2(v2 - v0);
    t3Vector3d pvec = dir.getCrossed(v0v2);
    double det = v0v1.dot(pvec);

    // 右手坐标系 三角形唯有在行列式>0时才可见
    if(bEnableBackfaceCulling)
        if(det < A3_TOLERANCE_DOUBLE) 
            return false;
    else
        if(t3Math::Abs(det) < A3_TOLERANCE_DOUBLE) 
            return false;

    double invDet = 1.0 / det;

    // 克莱姆法则计算[t, u, v]三分量
    t3Vector3d tvec(ray.origin - v0);
    u = tvec.dot(pvec) * invDet;
    if(u < 0.0 || u > 1.0) return false;

    t3Vector3d qvec = tvec.getCrossed(v0v1);
    v = dir.dot(qvec) * invDet;
    if(v < 0.0 || u + v > 1.0) return false;

    // 可直接返回
    tHit = v0v2.dot(qvec) * invDet;

    if(tHit > ray.minT && tHit < ray.maxT)
    {
        *t = tHit;
        *_u = u;
        *_v = v;

        if(bCalTextureCoordinate)
        {
            // --!纹理坐标
            t3Vector3f vt = (1 - u - v) * vt0 + u * vt1 + v * vt2;
            *vtu = vt.x;
            *vtv = vt.y;
        }

        return true;
    }

    return false;
}

// face normal
t3Vector3f a3Triangle::getNormal(const t3Vector3f& hitPoint, float u, float v) const
{
    t3Vector3f normal;

    if(bUseFaceNormal)
        // 左手坐标系
        normal.set((v1 - v0).getCrossed(v2 - v0).getNormalized());
    else
        normal.set((1 - u - v) * n0 + u * n1 + v * n2);

    return normal;

    // 外部保证hitPoint在三角形内部
    // --!效率低的像狗
    //t3Vector3f pv0 = v0 - hitPoint, pv1 = v1 - hitPoint, pv2 = v2 - hitPoint;
    //float S0 = pv0.getCrossed(pv1).length(), S1 = pv1.getCrossed(pv2).length(), S2 = pv2.getCrossed(pv0).length();
    //float S = S0 + S1 + S2;
    //float u = S1 / S, v = S2 / S;

    //return (u * n0 + (1 - u - v)* n1 + v * n2);

    //return n0;
}
 