#include "CAction.h"
#include <random>

CAction::CAction(Matrix<TYPE, ACTIONS, 1> aInitialAction)
: Ut(aInitialAction)
, Bt({
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
    })
{
}

CAction::~CAction()
{
}

 Matrix<TYPE, STATES, ACTIONS> CAction::GetBt() const
{
    return Bt;
}

Matrix<TYPE, ACTIONS, 1> CAction::GetUt() const
{
    return Ut;
}

void CAction::SetUt(Matrix<TYPE, ACTIONS, 1> Ut)
{
    this->Ut = Ut;
}