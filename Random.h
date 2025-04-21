#pragma once
#include <random>

namespace astro 
{
    struct Random 
    {
        static std::random_device rd;
        static std::mt19937 gen;

        static std::uniform_int_distribution<int> randBright;
        static std::uniform_real_distribution<float> randTwinkle;
        static std::uniform_real_distribution<float> randSize;
        static std::uniform_int_distribution<int> randColor;
        static std::uniform_int_distribution<int> randAsteroidVertex;
        static std::uniform_real_distribution<float> randZeroToOneFloat;
        static std::uniform_real_distribution<float> randMinusToPlusFormOneFloat;
        static std::uniform_real_distribution<float> randAsteroidSize;
        static std::uniform_real_distribution<float> randAsteroidSpeed;
        static std::uniform_real_distribution<float> randScreenX;
        static std::uniform_real_distribution<float> randScreenY;
    };
}
