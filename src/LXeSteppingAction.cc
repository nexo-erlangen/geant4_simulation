/// \file LXeSteppingAction.cc
/// \brief Implementation of the LXeSteppingAction class

#include "LXeSteppingAction.hh"

LXeSteppingAction::LXeSteppingAction(){}
LXeSteppingAction::~LXeSteppingAction(){}

void LXeSteppingAction::UserSteppingAction(const G4Step* step) 
{
  LXeAnalysis::GetInstance()->SteppingAction(step);
}
