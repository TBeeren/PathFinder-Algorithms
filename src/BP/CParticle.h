#ifndef CPARTICLE_H
#define CPARTICLE_H

// Includes
#include <memory>
#include <vector>
#include "../Robot.hpp"

class CParticle
{
public:
    CParticle(int X, int Y);
    virtual ~CParticle();

    void DoMovement(int X, int Y);

    // Getters & Setters
    int GetX() const;
    int GetY() const;
    void SetY(int Y);
    void SetWeight(float aWeight);
    float GetWeight() const;
    void SetMeasurements(std::vector<float> aMeasurements);
    std::vector<float> GetMeasurements() const;

    // Opperators
    bool operator==(const CParticle& lhs);

private:
    std::vector<float> m_measurements;
    float m_weight;
    int X;
    int Y;
};

#endif /*CPARTICLE_H*/