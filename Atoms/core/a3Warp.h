﻿#ifndef A3_WARP_H
#define A3_WARP_H

#include <t3Math/core/t3Vector2.h>
#include <t3Math/core/t3Vector3.h>
#include <core/a3Spectrum.h>

// --!公共函数

// 笛卡尔坐标系转换为极坐标系
t3Vector2f a3SquareToUniformDisk(const float sampleU, const float sampleV);

// 色调映射(需要保证colorList指针已指向线性空间 大小为width * height)
void a3ToneMapping(t3Vector3f* colorList, int width, int height);

// 未启用的Tone Mapping
void a3UncharedTonemap(t3Vector3f& color, float eyeAdaption = 4);

// 伽马矫正(三分量)
void a3GammaCorrection(float& r, float&g, float& b);

// 伽马矫正
void a3GammaCorrection(t3Vector3f& color);

// 球坐标Theta:[0, 2pi]
float a3SphericalTheta(const t3Vector3f &v);

// 球坐标Phi:[-pi, +pi]
float a3SphericalPhi(const t3Vector3f &v);

// 均匀分布半球采样
t3Vector3f a3Hemisphere(float u1, float u2);

// 给定v1坐标轴 与v2v3构建一正交坐标系(返回单位向量)
void a3OrthonomalSystem(const t3Vector3f& v1, t3Vector3f& v2, t3Vector3f& v3);

// 计算判别式求解二次方程f(若有解则t0 <= t1)
bool a3SolveQuadratic(float A, float B, float C, float* t0, float* t1);

// 计算判别式求解二次方程d(若有解则t0 <= t1)
bool a3SolveQuadraticDouble(double A, double B, double C, double* t0, double* t1);

// 多重重要性采样启发算法
float a3PowerHeuristic(int nf, float fPdf, int ng, float gPdf);

// 均匀采样球概率分布
float a3UniformSpherePdf();

// [Tools]转Fov为apretureWidth/Height(度)
float a3FovToApretureSizeDeg(float fov);

// [Tools]转Fov为apretureWidth/Height(弧度)
float a3FovToApretureSizeRad(float fov);

// RGBSpectrum转为亮度/明度
float a3RGB2Luminance(const a3Spectrum& rgb);

// 导体的菲涅尔反射项
float a3FresnelDielectric(float cosi, float cost, const float &etai, const float &etat);

// 绝缘体的菲涅尔反射项
float a3FresnelConductor(float cosi, float cost, const float &etai, const float &etat);
#endif 