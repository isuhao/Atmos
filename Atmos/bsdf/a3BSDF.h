﻿#pragma once

#include <textures/a3Texture.h>
#include <core/a3Spectrum.h>

class a3BSDFSamplingRecord;
class a3BSDF
{
public:
    a3BSDF();

    a3BSDF(a3Texture<a3Spectrum>* texture);

    virtual ~a3BSDF();

    // evaluate the BSDF f(wi, wo)
    virtual a3Spectrum eval(const a3BSDFSamplingRecord& bRec) const = 0;

    // sample the BSDF and return the importance weight
    // returned value has divided by the probability density of the sample
    virtual a3Spectrum sample(a3BSDFSamplingRecord& bRec) const = 0;

    // compute the probability of sampling wo (given wi, BSDF(wi, wo) * costheta)
    virtual float pdf(const a3BSDFSamplingRecord& bRec) const = 0;

    // if delta distribution
    virtual bool isDeltaDistribution() const = 0;

    std::string name;

    // reflectance on texture
    a3Texture<a3Spectrum>* reflectance;
};
 