#include "CMeasurement.h"
#include "CEnvironment.h"
#include <random>

namespace
{
    constexpr const float CHANCE_OF_ODOM = 1.0;
    constexpr const float CHANCE_OF_COMPASS = 2.0;
}

CMeasurement::CMeasurement(std::shared_ptr<CEnvironment> Environment)
: Ct({
    {1.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    })
{
    Dt = GenerateRandomProcessNoise();
}

CMeasurement::~CMeasurement()
{
}

Matrix<TYPE, MEASUREMENTS, STATES> CMeasurement::GetCt()
{
    return Ct;
}

Matrix<TYPE, MEASUREMENTS, 1> CMeasurement::GetDt()
{
    return Dt;
}

Matrix<TYPE, MEASUREMENTS, 1> CMeasurement::GetZt()
{
    return Zt;
}

Matrix<TYPE, MEASUREMENTS, 1> CMeasurement::GenerateRandomProcessNoise()
{
    static std::random_device random{};
    static std::mt19937 randomGenerator(random());
    std::normal_distribution<TYPE> odomNoise{0.0, CHANCE_OF_ODOM};
    std::normal_distribution<TYPE> compassNoise{0.0, CHANCE_OF_COMPASS};
    
    return {odomNoise(randomGenerator), compassNoise(randomGenerator)};
}

void CMeasurement::calcNewZt(CEnvironment aEnvironment)
{
    Zt = (Ct * aEnvironment.getXt()) + Dt;
}