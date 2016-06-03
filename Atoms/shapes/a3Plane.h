﻿#ifndef A3_PLANE_H
#define A3_PLANE_H

#include <shapes/a3Triangle.h>
#include <t3Math/core/t3Matri4x4.h>

// 单面
class a3Plane:public a3Shape
{
public:
    a3Plane(const t3Vector3f& p, const t3Vector3f& normal, float width, float height);

    void set(const t3Vector3f& p, const t3Vector3f& normal, float width, float height);

    virtual bool intersect(const a3Ray& ray, float* t, float* u, float* v, float* vtu, float* vtv) const;

    virtual t3Vector3f getNormal(const t3Vector3f& hitPoint, float u, float v) const;

    // 平面上一点及其朝向
    t3Vector3f p, normal;

    // 宽高
    float width, height;

    a3Triangle a, b;

    t3Matrix4x4 worldToPlane;

private:
    void init();
};

#endif 