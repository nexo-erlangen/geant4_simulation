/// \file LXeEventAction.cc
/// \brief Implementation of the LXeEventAction class

#include "LXeEventAction.hh"

#include "G4Event.hh"
//#include "G4EventManager.hh"
//#include "G4HCofThisEvent.hh"
//#include "G4UImanager.hh"
//#include "G4UnitsTable.hh"

LXeEventAction::LXeEventAction(){}
LXeEventAction::~LXeEventAction(){}

void LXeEventAction::BeginOfEventAction(const G4Event* evt)
{
  LXeAnalysis::GetInstance()->PrepareNewEvent(evt);
}

void LXeEventAction::EndOfEventAction(const G4Event* evt)
{
  LXeAnalysis::GetInstance()->EndOfEventAction(evt);
}
