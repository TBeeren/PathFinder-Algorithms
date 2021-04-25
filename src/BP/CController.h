#ifndef CCONTORLLER_H
#define CCONTORLLER_H

// Includes
#include <memory>
#include <vector>
#include "../Robot.hpp"
#include "CParticle.h"

// Forward Declarations
class CModel;
class CAction;
class CEnvironment;
class CMeasurement;

class CController
{
    
public:
    explicit CController(Model::Robot* pRobot);
    virtual ~CController();

    void KalmanFilter(CAction aAction, CMeasurement aMeasurement);
    void ParticleFilter(std::vector<float> rRobotLidarValues, Widgets::Point& rMovement);
    int CalcMovementStdDeviation();
    void GenerateRandomParticles(int nParticles);

    // Getters & Setters
    std::shared_ptr<CModel> GetModel() const;
    std::shared_ptr<CEnvironment> GetEnvironment() const;
    CParticle& GetParticleBelief();

private:
    std::shared_ptr<CModel> m_spModel;
    std::shared_ptr<CEnvironment> m_spEnvironment;

    std::vector<CParticle> m_particleVector;
    CParticle m_particleBelief;
    Model::Robot* m_pRobot;
};

#endif /*CCONTORLLER_H*/