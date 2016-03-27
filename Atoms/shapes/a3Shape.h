#ifndef A3_SHAPE_H
#define A3_SHAPE_H

#include <core/a3Settings.h>
#include <t3Math/core/t3Vector3.h>

enum a3MaterialType
{
	A3_MATERIAL_NONE = 0,

	A3_MATERIAL_DIFFUSS = 1,
	A3_MATERIAL_SPECULAR = 2,
	A3_METERIAL_REFRACTION = 3
};

class a3Ray;

class a3Shape
{
public:
	a3Shape();

	virtual float intersect(const a3Ray& ray) const;

    // return normal
    virtual t3Vector3f getNormal(const t3Vector3f& hitPoint) const;

    void setMaterial(const t3Vector3f color, const t3Vector3f emission = t3Vector3f::zero(), int type = A3_MATERIAL_NONE);

    virtual void print() const;

	t3Vector3f color;

	// 自发光系数
	t3Vector3f emission;

    // 折射率
    float refractiveIndex;

	// BSDF类型
	int type;
};

#endif