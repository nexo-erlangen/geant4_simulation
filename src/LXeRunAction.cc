/// \file LXeRunAction.cc
/// \brief Implementation of the LXeRunAction class

#include "LXeRunAction.hh"

#include "G4Run.hh"
//#include "G4UImanager.hh"
//#include "G4VVisManager.hh"

//#include "Randomize.hh"

LXeRunAction::LXeRunAction() 
{
 
}

LXeRunAction::~LXeRunAction()
{

}

void LXeRunAction::BeginOfRunAction(const G4Run* aRun)
{
  
  G4int runN = aRun->GetRunID();
  G4cout << "### Run : " << runN << G4endl;
  LXeAnalysis::GetInstance()->PrepareNewRun(aRun);
 /*   
#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance()) {
     G4UImanager* UI = G4UImanager::GetUIpointer(); 
     UI->ApplyCommand("/vis/clear/view");
     UI->ApplyCommand("/vis/draw/current");
  } 
#endif
  */
}

void LXeRunAction::EndOfRunAction(const G4Run* aRun)
{
  LXeAnalysis::GetInstance()->EndOfRunAction(aRun);
 /*
#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance())
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/show/view");
#endif
*/
	
}
