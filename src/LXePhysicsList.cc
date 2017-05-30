/// \file LXePhysicsList.cc
/// \brief Implementation of the LXePhysicsList class

#include "LXePhysicsList.hh"
#include "LXePhysicsConstructor.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicsListHelper.hh"

// For physics process:
#include "G4Scintillation.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
//#include "G4S1Light.hh"
#include "G4Electron.hh"
#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

/*
 #include "G4DataQuestionaire.hh"
 #include "G4VPhysicsConstructor.hh"
 #include "G4EmPenelopePhysics.hh" // Low energy physics
 #include "G4EmLowEPPhysics.hh" // Low energy physics
 #include "G4StoppingPhysics.hh"
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
G4S1Light* LXePhysicsList::GetScintillation(){
    return theScintProcess;
}
*/
LXePhysicsList::LXePhysicsList(G4double passedValue, G4bool passedBoolean, G4double scintFactor):G4VModularPhysicsList(),
cutValue(passedValue),
SinglePhase(passedBoolean),
ScintFactor(scintFactor)
{
    //G4DataQuestionaire it(photon, neutron, no, no, no, neutronxs);
    G4cout << "<<< Geant4 Physics List: LXePhysicsList " <<G4endl;
    
    defaultCutValue = cutValue*mm;  // Sets a threshold below which no secondaries are generated
	
    G4int ver = 1;
   	SetVerboseLevel(ver);
    
    RegisterPhysics(new G4EmStandardPhysics(ver));
    
    RegisterPhysics(new LXePhysicsConstructor(SinglePhase, ScintFactor));
    
 //    RegisterPhysics(new G4OpticalPhysics(ver));
     /*
     RegisterPhysics(new G4DecayPhysics(ver));
     
     RegisterPhysics(new G4RadioactiveDecayPhysics(ver));
     */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePhysicsList::~LXePhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void LXePhysicsList::SetCuts(){
    //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
    //   the default cut value for all particle types
     SetCutsWithDefault();
/*
	SetCutValue(defaultCutValue, "gamma");
	SetCutValue(defaultCutValue, "opticalphoton");
	SetCutValue(defaultCutValue, "e-");
	SetCutValue(defaultCutValue, "alpha");
	*/
}

