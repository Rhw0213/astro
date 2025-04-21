#pragma once
#include <vector>

namespace astro
{
	class PerlinNoise
	{
    public:
        PerlinNoise();
        PerlinNoise(unsigned int seed);

        double noise(double x, double y);
        double octaveNoise(double x, double y, int octaves, double persistence);

    private:
        double fade(double t);
        double lerp(double t, double a, double b);
        double grad(int hash, double x, double y);
    private:
        std::vector<int> p; // ¼ø¿­ º¤ÅÍ
	};
}
