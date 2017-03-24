﻿#ifndef A3_DIELECTRIC_BSDF_H
#define A3_DIELECTRIC_BSDF_H

#include <bsdf/a3BSDF.h>

class a3Dieletric : public a3BSDF
{
public:
    a3Dieletric(a3Spectrum R = a3Spectrum::one());

    virtual a3Spectrum sample(const t3Vector3f& wi, t3Vector3f& wo, float* pdf, const a3Intersection& its) const;

    virtual a3Spectrum eval(const t3Vector3f& wi, const t3Vector3f& wo, const a3Intersection& its) const;

    virtual bool isDiracDistribution() const;

    virtual float pdf(const t3Vector3f& wi, const t3Vector3f& wo, const a3Intersection& its) const override;

    a3Spectrum specularTransmittance, specularReflectance;

private:
    // 反射向量计算
    t3Vector3f reflect(const t3Vector3f& normal, const t3Vector3f& incident) const;

    // 折射向量计算(TIR, total internal relfect)
    t3Vector3f refract(const t3Vector3f& normal, const t3Vector3f& incident, float eta1, float eta2, bool& TIR) const;

    // 考虑全反射的菲涅尔反射计算
    float reflectance(const t3Vector3f& normal, const t3Vector3f& incident, float eta1, float eta2) const;
};

#endif