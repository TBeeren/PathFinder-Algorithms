#include "CParticle.h"

CParticle::CParticle(int X, int Y)
: X(X)
, Y(Y)
{
}

CParticle::~CParticle()
{
}

int CParticle::GetX() const
{
    return X;
}

int CParticle::GetY() const
{
    return Y;
}

void CParticle::SetMeasurements(std::vector<float> aMeasurements)
{
    m_measurements = aMeasurements;
}

std::vector<float> CParticle::GetMeasurements() const
{
    return m_measurements;
}

void CParticle::DoMovement(int X, int Y)
{
    this->X += X;
    this->Y += Y;
}

void CParticle::SetWeight(float aWeight)
{
    m_weight = aWeight;
}

float CParticle::GetWeight() const
{
    return m_weight;
}

bool CParticle::operator==(const CParticle& lhs)
{
    return this->X == lhs.GetX() && this->Y == lhs.GetY();
}