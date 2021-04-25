#ifndef CENVIRONMENT_H
#define CENVIRONMENT_H

#include <memory>
#include "CMeasurement.h"
#include "Matrix/Matrix.hpp"
#include "../Robot.hpp"

// Forward Declaration
class CAction;

class CEnvironment
{
public:
    explicit CEnvironment(Model::Robot* pRobot);
    virtual ~CEnvironment();

    Matrix<TYPE, STATES, 1> getXt();
    Matrix<TYPE, STATES, 1> GetOldXt() const;
    Matrix<TYPE, STATES, STATES> getAt();
    Matrix<TYPE, STATES, 1> GetEt() const;

    void calcNewXt(CAction action);
    Matrix<TYPE, STATES, 1> GenerateRandomNoise();

private:
    Matrix<TYPE, STATES, 1> Xt;
    Matrix<TYPE, STATES, 1> OldXt;
    Matrix<TYPE, STATES, STATES> At;
    Matrix<TYPE, STATES, 1> Et;
};

#endif /*CENVIRONMENT_H*/