#include "CModel.h"
#include "../RobotWorld.hpp"

CModel::CModel(Model::Robot* pRobot)
{
    std::initializer_list<std::initializer_list<TYPE>> initMean = 
    {
        {pRobot->getPosition().x},
        {pRobot->getPosition().y},
        {pRobot->GetCompassValue()}
    };
    

    std::initializer_list<std::initializer_list<TYPE>> initVar = 
    {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    m_mean = initMean;
    m_variance = initVar;
}

CModel::~CModel()
{
}

Matrix<TYPE, STATES, 1> CModel::GetMean() const
{
    return m_mean;
}

Matrix<TYPE, STATES, STATES> CModel::GetVariance() const
{
    return m_variance;
}

void CModel::SetMean(Matrix<TYPE, STATES, 1> aMean)
{
    m_mean = aMean;
}

void CModel::SetVariance(Matrix<TYPE, STATES, STATES> aVariance)
{
    m_variance = aVariance;
}