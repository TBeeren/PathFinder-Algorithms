#ifndef CMODEL_H
#define CMODEL_H

#include "Matrix/Matrix.hpp"
#include "../Robot.hpp"

class CModel
{
public:
    CModel(Model::Robot* pRobot);
    virtual ~CModel();

    // Getters & Setters
    Matrix<TYPE, STATES, 1> GetMean() const;
    Matrix<TYPE, STATES, STATES> GetVariance() const;
    void SetMean(Matrix<TYPE, STATES, 1> aMean);
    void SetVariance(Matrix<TYPE, STATES, STATES> aVariance);

private:
    Matrix<TYPE, STATES, 1> m_mean;
    Matrix<TYPE, STATES, STATES> m_variance;
    
};

#endif /*CMODEL_H*/