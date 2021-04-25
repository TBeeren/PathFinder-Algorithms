#ifndef CMEASUREMENT_H
#define CMEASUREMENT_H

#include <iostream>
#include <memory>
#include "Matrix/Matrix.hpp"

// Forward Declarations
class CEnvironment;

class CMeasurement
{
public:
    explicit CMeasurement(std::shared_ptr<CEnvironment> Environment);
    virtual ~CMeasurement();

    Matrix<TYPE, MEASUREMENTS, 1> GenerateRandomProcessNoise();
    void calcNewZt(CEnvironment aEnvironment);

    // Getters & Setters
    Matrix<TYPE, MEASUREMENTS, STATES> GetCt();
    Matrix<TYPE, MEASUREMENTS, 1> GetDt();
    Matrix<TYPE, MEASUREMENTS, 1> GetZt();
    
private:    
    Matrix<TYPE, MEASUREMENTS, STATES> Ct;
    Matrix<TYPE, MEASUREMENTS, 1> Dt;
    Matrix<TYPE, MEASUREMENTS, 1> Zt;

};

#endif /*CMEASUREMENT_H*/