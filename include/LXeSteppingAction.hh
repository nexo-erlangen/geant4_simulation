/// \file LXeSteppingAction.hh
/// \brief Implementation of the LXeSteppingAction class

#ifndef LXeSteppingAction_h
#define LXeSteppingAction_h 1

#include "globals.hh"

#include "G4UserSteppingAction.hh"

#include "LXeAnalysis.hh"

class LXeSteppingAction : public G4UserSteppingAction
{
public:
  LXeSteppingAction();
  virtual ~LXeSteppingAction();
  
  virtual void UserSteppingAction(const G4Step*);

private:
};

#endif
