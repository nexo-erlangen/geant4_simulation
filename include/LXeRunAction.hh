/// \file LXeRunAction.hh
/// \brief Definition of the LXeRunAction class

#ifndef LXeRunAction_h
#define LXeRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

#include "LXeAnalysis.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4Run;

class LXeRunAction : public G4UserRunAction
{
public:
  LXeRunAction();
  virtual ~LXeRunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

};

#endif