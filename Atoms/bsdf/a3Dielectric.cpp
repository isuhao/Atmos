﻿#include <bsdf/a3Dielectric.h>
#include <shapes/a3Shape.h>
#include <core/a3Warp.h>
#include <core/log/a3Log.h>

a3Dieletric::a3Dieletric(a3Spectrum R) :specularTransmittance(0.0f), specularReflectance(1.0f)
{

}

a3Spectrum a3Dieletric::sample(const t3Vector3f& wi, t3Vector3f& wo, float* pdf, const a3Intersection& its) const
{
    static a3Random random;

    t3Vector3f n = its.getNormal();

    // 入射光 / 出射光所在折射率
    float etai = 1.0f, etat = its.shape->refractiveIndex;

    // 光密到光疏
    if(wi.dot(n) > 0)
    {
        t3Math::swap(etai, etat);
        // 翻转法线 保持与入射光线一个平面
        n = -n;
    }

    float eta = etai / etat;

    // 菲涅尔反射(反射的概率)
    //float Fr = a3FresnelDielectric(costhetai, costhetat, etai, etat);
    float Fr = reflectance(n, wi, etai, etat);

    if(random.randomFloat() > Fr)
    {
        bool TIR = false;
        wo = refract(n, wi, etai, etat, TIR);

        *pdf = 1.0f;

        if(!TIR)
        {
            eta = 1 / eta;
            return getColor(its) * specularTransmittance * eta * eta  / t3Math::Abs(wo.dot(n));
        }
        else
        {
            a3Log::error("a3Dieletric::sample() TIR!\n");
            return a3Spectrum(0.0f);
        }
    }
    else
    {
        wo = reflect(n, wi);

        if(Fr == 1.0f)
        {
            *pdf = 1.0f;

            // 全反射
            return getColor(its) / t3Math::Abs(wo.dot(n));
        }
        else
        {
            *pdf = 1.0f;

            // 镜面反射
            return getColor(its) * specularReflectance / t3Math::Abs(wo.dot(n));
        }

    }
}

a3Spectrum a3Dieletric::eval(const t3Vector3f& wi, const t3Vector3f& wo, const a3Intersection& its) const
{
    // delta分布在给定出射方向上几率为0
    return a3Spectrum(0.0f);
}

bool a3Dieletric::isDiracDistribution() const
{
    return true;
}

float a3Dieletric::pdf(const t3Vector3f& wi, const t3Vector3f& wo, const a3Intersection& its) const
{
    return 0.0f;
}

t3Vector3f a3Dieletric::reflect(const t3Vector3f& normal, const t3Vector3f& incident) const
{
    const float costhetai = -normal.dot(incident);
    return incident + 2 * costhetai * normal;
}

t3Vector3f a3Dieletric::refract(const t3Vector3f& normal, const t3Vector3f& incident, float eta1, float eta2, bool& TIR) const
{
    TIR = false;

    const float eta = eta1 / eta2;
    const float costhetai = -normal.dot(incident);
    // sinthetat^2
    const float sinthetat2 = eta * eta * (1.0f - costhetai * costhetai);
    // 全反射
    if(sinthetat2 > 1.0f)
    {
        TIR = true;
        return t3Vector3f::zero();
    }

    const float costhetat = t3Math::sqrt(1.0f - sinthetat2);
    return eta * incident + (eta * costhetai - costhetat) * normal;
}

float a3Dieletric::reflectance(const t3Vector3f& normal, const t3Vector3f& incident, float etai, float etat) const
{
    const float costhetai = -normal.dot(incident);
    const float eta = etai / etat;
    const float sinthetat2 = eta * eta * (1.0f - costhetai * costhetai);
    if(sinthetat2 > 1.0f)
        return 1.0f;

    const float costhetat = t3Math::sqrt(1.0f - sinthetat2);
    return a3FresnelDielectric(costhetai, costhetat, etai, etat);
}
 