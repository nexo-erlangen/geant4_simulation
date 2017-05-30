/// \file LXeEventAction.hh
/// \brief Implementation of the LXeEventAction class

#ifndef LXeEventAction_h
#define LXeEventAction_h 1

#include "globals.hh"

#include "G4UserEventAction.hh"

#include "LXeAnalysis.hh"

class LXeEventAction : public G4UserEventAction
{
public:
  LXeEventAction();
  virtual ~LXeEventAction();
  
private:
  void BeginOfEventAction(const G4Event* );
  void EndOfEventAction(const G4Event* );

};

#endif
