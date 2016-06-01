﻿#include <core/a3Random.h>
#include <random>

class a3Random::a3RandomPrivate
{
public:
    a3RandomPrivate() 
    {
    }

    static float randomFloat()
    {
        return uniformf(mersenneTwister);
    }

    static int randomInt()
    {
        return uniformi(mt);
    }

    static double randomDouble()
    {
        return uniformd(mersenneTwister);
    }

    // 产生随机数种子
    static std::random_device random;
    // mersenne twister engine
    static std::mt19937 mt, mersenneTwister;
    // uniform distribution
    static std::uniform_int_distribution<> uniformi;
    static std::uniform_real_distribution<float> uniformf;
    static std::uniform_real_distribution<double> uniformd;
};

std::random_device a3Random::a3RandomPrivate::random;

std::mt19937 a3Random::a3RandomPrivate::mt(a3Random::a3RandomPrivate::random());

std::mt19937 a3Random::a3RandomPrivate::mersenneTwister(a3Random::a3RandomPrivate::random());

std::uniform_int_distribution<> a3Random::a3RandomPrivate::uniformi(0, 10);

std::uniform_real_distribution<float> a3Random::a3RandomPrivate::uniformf(0.0f, 1.0f);

std::uniform_real_distribution<double> a3Random::a3RandomPrivate::uniformd(0.0, 1.0);

a3Random::a3Random()
{
    //random = new a3RandomPrivate();
}

float a3Random::randomFloat() const
{
    //return rand() / (float) RAND_MAX;
    return a3Random::a3RandomPrivate::randomFloat();
}

unsigned int a3Random::randomInt() const
{
    return a3Random::a3RandomPrivate::randomInt();
}

double a3Random::randomDouble() const
{
    return a3Random::a3RandomPrivate::randomDouble();
}
 