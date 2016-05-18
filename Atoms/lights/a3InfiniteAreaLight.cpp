﻿#include <lights/a3InfiniteAreaLight.h>
#include <core/a3Warp.h>
#include <core/a3Ray.h>
#include <core/log/a3Log.h>
#include <core/image/a3ImageDecoder.h>
#include <samples/a3LightSample.h>
#include <core/a3Random.h>

a3InfiniteAreaLight::a3InfiniteAreaLight(const std::string& filePath)
:a3Light(t3Matrix4x4::newIdentityMatrix())
{
    image = new a3ImageDecoder(filePath);
}

a3InfiniteAreaLight::~a3InfiniteAreaLight()
{

}

a3Spectrum a3InfiniteAreaLight::le(const a3Ray& ray) const
{
    // 光线方向已归一化 将theta/phi归一化至[0, 1]
    float u = a3SphericalPhi(ray.direction) * T3MATH_INV_TWOPI;
    float v = a3SphericalTheta(ray.direction) * T3MATH_INV_PI;

    return image->lookup(u, v);
}

a3Spectrum a3InfiniteAreaLight::sampleL(t3Vector3f& wo, const t3Vector3f& p, float* pdf, 
                                        const a3LightSample& sample, a3VisibilityTester& vis) const
{
    // 整个球面上随机采样
    float theta = sample.uPos[0] * T3MATH_PI, phi = sample.uPos[1] * T3MATH_PI * 2;

    //wo = -ray.direction;
    t3Vector3f direction(t3Math::sinRad(theta)*t3Math::sinRad(phi), t3Math::cosRad(theta), t3Math::sinRad(theta) * t3Math::cosRad(phi));

    // 光线方向已归一化 将theta/phi归一化至[0, 1]
    float u = a3SphericalPhi(direction) * T3MATH_INV_TWOPI;
    float v = a3SphericalTheta(direction) * T3MATH_INV_PI;

    vis.setRay(p, direction, A3_RAY_BIAS);

    wo = direction;

    *pdf = A3_TOLERANCE_FLOAT;

    return image->lookup(u, v);
}

bool a3InfiniteAreaLight::isDiracDistribution() const
{
    return false;
}

float a3InfiniteAreaLight::pdf(const t3Vector3f&p, const t3Vector3f& wi)
{
    return A3_TOLERANCE_FLOAT;
}

 