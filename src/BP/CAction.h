#ifndef CACTION_H
#define CACTION_H

#include "Matrix/Matrix.hpp"

class CAction
{
public:
    explicit CAction(Matrix<TYPE, ACTIONS, 1> aInitialAction);
    virtual ~CAction();

    //Getters & Setters
    Matrix<TYPE, STATES, ACTIONS> GetBt() const;
    Matrix<TYPE, ACTIONS, 1> GetUt() const;
    void SetUt(Matrix<TYPE, ACTIONS, 1> Ut);

private:
    Matrix<TYPE, STATES, ACTIONS> Bt;
    Matrix<TYPE, ACTIONS, 1> Ut;
};

#endif /*CACTION_H*/