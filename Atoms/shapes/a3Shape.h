﻿#ifndef A3_SHAPE_H
#define A3_SHAPE_H

#include <core/a3Spectrum.h>
#include <t3Math/core/t3Vector3.h>
#include <core/a3Settings.h>
#include <core/a3AABB.h>

class a3Ray;
class a3BSDF;

class a3Shape
{
public:
	a3Shape();

    a3Shape(std::string name);

    void setMaterial(const a3Spectrum color, const a3Spectrum emission = a3Spectrum::zero());

    // [u, v]用于三角形插值计算当前相交点的重心坐标系位置; [vtu, vtv]用于相交点的纹理坐标计算
    virtual bool intersect(const a3Ray& ray, float* t, float* u, float* v, float* vtu, float* vtv) const;

    virtual t3Vector3f getNormal(const t3Vector3f& hitPoint, float u, float v) const;

    virtual void print() const;

    bool isEmitter() const;

    // inline
    const a3BSDF* getBSDF() const;

    a3BSDF* getBSDF();

    bool hasBSDF() const;

    void setBSDF(a3BSDF* bsdf);

	// 自发光系数
	t3Vector3f emission;

    // 折射率
    float refractiveIndex;

	// BSDF类型
    a3BSDF* bsdf;

    bool bIsEmitter;

    // 包围盒
    a3AABB aabb;

    // 是否使用单一面片法线
    bool bUseFaceNormal;

    std::string name;
};

#endif 