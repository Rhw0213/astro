#include "Random.h"
#include "Common.h"
#include "Setting.h"

std::random_device astro::Random::rd;
std::mt19937 astro::Random::gen(astro::Random::rd());
std::uniform_int_distribution<int> astro::Random::randBright(100, 255);
std::uniform_real_distribution<float> astro::Random::randTwinkle(0.5f, 2.f);
std::uniform_real_distribution<float> astro::Random::randSize(1, 2);
std::uniform_int_distribution<int> astro::Random::randColor(0, 6);
std::uniform_int_distribution<int> astro::Random::randAsteroidVertex(6, 12);
std::uniform_real_distribution<float> astro::Random::randZeroToOneFloat(0.f, 1.f);
std::uniform_real_distribution<float> astro::Random::randMinusToPlusFormOneFloat(-1.f, 1.f);
std::uniform_real_distribution<float> astro::Random::randAsteroidSize(5.f, 10.f);
std::uniform_real_distribution<float> astro::Random::randAsteroidSpeed(100.f, 200.f);
std::uniform_real_distribution<float> astro::Random::randScreenX(0, astro::SCREEN_WIDTH);
std::uniform_real_distribution<float> astro::Random::randScreenY(0, astro::SCREEN_HEIGHT);
std::normal_distribution<float> astro::Random::distributionFrameRange(0.f, 10.f);
std::normal_distribution<float> astro::Random::missileRange(0.f, 20.f);