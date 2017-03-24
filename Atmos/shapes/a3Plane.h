﻿#ifndef A3_PLANE_H
#define A3_PLANE_H

#include <shapes/a3Triangle.h>
#include <t3Math/core/t3Matri4x4.h>

// 单面
class a3Plane:public a3Shape
{
public:
    // world to plane暂时不能包含位移
    a3Plane(const t3Matrix4x4& worldToPlane, const t3Vector3f& p, float width, float height);

    void set(const t3Matrix4x4& worldToPlane, const t3Vector3f& p, float width, float height);

    virtual bool intersect(const a3Ray& ray, float* t, float* u, float* v, float* vtu, float* vtv) const;

    virtual t3Vector3f getNormal(const t3Vector3f& hitPoint, float u, float v) const;

    virtual float area() const;

    virtual t3Vector3f sample(const a3LightSample& sample) const;
 
    // 宽高
    float width, height;

    a3Triangle a, b;

    t3Matrix4x4 worldToPlane;

private:
    void init();

    // --!p为临时分离出的
    t3Vector3f normal, p;
};

#endif