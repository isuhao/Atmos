﻿#ifndef A3_BSDF_H
#define A3_BSDF_H

#include <t3Math/core/t3Vector2.h>
#include <core/a3Intersection.h>
#include <core/a3Spectrum.h>
#include <core/a3Random.h>
#include <textures/a3Texture.h>

struct a3BSDFSamplingRecord
{
    a3BSDFSamplingRecord(const a3Intersection &its) 
    :its(its)
    {

    }

    a3BSDFSamplingRecord(const a3Intersection &its, const t3Vector3f &wi, const t3Vector3f &wo)
    :its(its), wi(wi), wo(wo)
    {

    }

    const a3Intersection& its;

    // Normalized incident direction in world coordinates
    t3Vector3f wi;

    // Normalized outgoing direction in world coordinates
    t3Vector3f wo;

    // Relative index of refraction in the sampled direction
    float eta;

    // Generate random number
    a3Random random;
};

class a3BSDF
{
public:
    enum EBSDFType
    {
        // =============================================================
        //                      BSDF lobe types
        // =============================================================

        /// 'null' scattering event, i.e. particles do not undergo deflection
        ENull = 0x00001,
        /// Ideally diffuse reflection
        EDiffuseReflection = 0x00002,
        /// Ideally diffuse transmission
        EDiffuseTransmission = 0x00004,
        /// Glossy reflection
        EGlossyReflection = 0x00008,
        /// Glossy transmission
        EGlossyTransmission = 0x00010,
        /// Reflection into a discrete set of directions
        EDeltaReflection = 0x00020,
        /// Transmission into a discrete set of directions
        EDeltaTransmission = 0x00040,
        /// Reflection into a 1D space of directions
        EDelta1DReflection = 0x00080,
        /// Transmission into a 1D space of directions
        EDelta1DTransmission = 0x00100,

        // =============================================================
        //!                   Other lobe attributes
        // =============================================================
        /// The lobe is not invariant to rotation around the normal
        EAnisotropic = 0x01000,
        /// The BSDF depends on the UV coordinates
        ESpatiallyVarying = 0x02000,
        /// Flags non-symmetry (e.g. transmission in dielectric materials)
        ENonSymmetric = 0x04000,
        /// Supports interactions on the front-facing side
        EFrontSide = 0x08000,
        /// Supports interactions on the back-facing side
        EBackSide = 0x10000,
        /// Uses extra random numbers from the supplied sampler instance
        EUsesSampler = 0x20000
    };

    /// Convenient combinations of flags from \ref EBSDFType
    enum ETypeCombinations
    {
        /// Any reflection component (scattering into discrete, 1D, or 2D set of directions)
        EReflection = EDiffuseReflection | EDeltaReflection
        | EDelta1DReflection | EGlossyReflection,
        /// Any transmission component (scattering into discrete, 1D, or 2D set of directions)
        ETransmission = EDiffuseTransmission | EDeltaTransmission
        | EDelta1DTransmission | EGlossyTransmission | ENull,
        /// Diffuse scattering into a 2D set of directions
        EDiffuse = EDiffuseReflection | EDiffuseTransmission,
        /// Non-diffuse scattering into a 2D set of directions
        EGlossy = EGlossyReflection | EGlossyTransmission,
        /// Scattering into a 2D set of directions
        ESmooth = EDiffuse | EGlossy,
        /// Scattering into a discrete set of directions
        EDelta = ENull | EDeltaReflection | EDeltaTransmission,
        /// Scattering into a 1D space of directions
        EDelta1D = EDelta1DReflection | EDelta1DTransmission,
        /// Any kind of scattering
        EAll = EDiffuse | EGlossy | EDelta | EDelta1D
    };


    // 给定入射光方向，根据相交点信息随机采样生成出射方向
    // 等价于PBRT中的sample_f
    virtual a3Spectrum sample(const t3Vector3f& wi, t3Vector3f& wo, float* pdf, const a3Intersection& its) const = 0;

    // 给定入射出射方向，计算在给定方向对及相交点信息情况下计算bsdf
    // 等价于PBRT中的f
    virtual a3Spectrum eval(const t3Vector3f& wi, const t3Vector3f& wo, const a3Intersection& its) const = 0;

    // Given wi compute the probability of sampling wo
    // --!大胆假设PDF()函数可类似sample()合并为eval()参数之一，未来版本可供参考
    virtual float pdf(const t3Vector3f& wi, const t3Vector3f& wo, const a3Intersection& its) const = 0;

    virtual bool isDiracDistribution() const = 0;

    //virtual bool isReflection() const = 0;

    // Get color from texture
    a3Spectrum getColor(const a3Intersection& its) const;

    // Default Texture 
    a3Texture<a3Spectrum>* texture;
};

#endif
 