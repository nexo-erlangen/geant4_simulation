/// \file LXeTrackingAction.cc
/// \brief Implementation of the LXeTrackingAction class

#include "LXeTrackingAction.hh"

LXeTrackingAction::LXeTrackingAction(){}
LXeTrackingAction::~LXeTrackingAction(){}

void LXeTrackingAction::PreUserTrackingAction(const G4Track* track)
{
  LXeAnalysis::GetInstance()->PreUserTrackingAction(track);
}

void LXeTrackingAction::PostUserTrackingAction(const G4Track* track)
{
  LXeAnalysis::GetInstance()->PostUserTrackingAction(track);
}
