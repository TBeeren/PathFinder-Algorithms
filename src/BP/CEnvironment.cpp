#include "CEnvironment.h"
#include "CAction.h"
#include "../RobotWorld.hpp"
#include <random>

CEnvironment::CEnvironment(Model::Robot* pRobot)
: At({
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
    })
{
    std::initializer_list<std::initializer_list<TYPE>> initXt = 
    {
        {pRobot->getPosition().x},
        {pRobot->getPosition().y},
        {pRobot->GetCompassValue()}
    };
	Xt = initXt;

    std::initializer_list<std::initializer_list<TYPE>> initEt = 
    {
        {1.0},
        {1.0},
        {0.0}
    };
    Et = initEt;
}

CEnvironment::~CEnvironment()
{
}

Matrix<TYPE, STATES, 1> CEnvironment::getXt()
{
    return Xt;
}

Matrix<TYPE, STATES, 1> CEnvironment::GetOldXt() const
{
    return OldXt;
}

Matrix<TYPE, STATES, STATES> CEnvironment::getAt()
{
    return At;
}

Matrix<TYPE, STATES, 1> CEnvironment::GetEt() const
{
    return Et;
}

Matrix<TYPE, STATES, 1> CEnvironment::GenerateRandomNoise()
{
    static std::random_device random{};
    static std::mt19937 randomGenerator(random());
    std::normal_distribution<TYPE> transNoise{0.0, 1.0};
    std::normal_distribution<TYPE> compassNoise{0.0, 0.0};
    
    return {transNoise(randomGenerator), transNoise(randomGenerator), compassNoise(randomGenerator)};
}

void CEnvironment::calcNewXt(CAction aAction)
{
    OldXt = Xt;
    Matrix<TYPE, STATES, 1> RandomMatrix = GenerateRandomNoise();
    
    Xt = (At * OldXt) + (aAction.GetBt() * aAction.GetUt()) + RandomMatrix;
}
