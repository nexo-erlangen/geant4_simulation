/// \file LXeActionInitialization.cc
/// \brief Implementation of the LXeActionInitialization class

#include "LXeActionInitialization.hh"
#include "LXePrimaryGeneratorAction.hh"
#include "LXeRunAction.hh"
#include "LXeEventAction.hh"
#include "LXeSteppingAction.hh"
#include "LXeTrackingAction.hh"
#include <iostream>
#include <string>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeActionInitialization::LXeActionInitialization(string ptype, double energy)
 : G4VUserActionInitialization(),
 particleType(ptype),
 particleEnergy(energy)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeActionInitialization::~LXeActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeActionInitialization::BuildForMaster() const
{
	//SetUserAction(new LXeRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeActionInitialization::Build() const
{
	SetUserAction(new LXePrimaryGeneratorAction(particleType, particleEnergy));
	SetUserAction(new LXeRunAction);
	SetUserAction(new LXeEventAction);
	SetUserAction(new LXeSteppingAction());  
	SetUserAction(new LXeTrackingAction());
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
