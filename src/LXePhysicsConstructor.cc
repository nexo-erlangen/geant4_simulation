//
//  LXePhysicsConstructor.cc
//  
//
//  Created by Reimund Bayerlein on 29/01/16.
//
//

#include "LXePhysicsConstructor.hh"
#include "LXeRunControl.hh"

#include "G4S1Light.hh"
#include "G4ThermalElectron.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"
#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"

#include "G4OpticalPhysics.hh"
#include "G4Cerenkov.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpWLS.hh"
#include "G4EmSaturation.hh"
#include "G4ParticleDefinition.hh"
#include "G4Alpha.hh"
#include "G4OpticalPhoton.hh"
#include "G4Electron.hh"
#include "G4BosonConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePhysicsConstructor::LXePhysicsConstructor(G4bool passedBoolean, G4double NestF):G4VPhysicsConstructor(),
enableThermalElectrons(false),
NESTFactor(NestF),
SinglePhase(passedBoolean)
{
	LXeRunControl* Control_Instance = LXeRunControl::GetInstance();
	enableOptics = Control_Instance->getOpticsEnabled();
	}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePhysicsConstructor::~LXePhysicsConstructor()
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePhysicsConstructor::ConstructParticle()
{
    if (enableThermalElectrons) {
        G4ThermalElectron::ThermalElectronDefinition();
    } 
    G4OpticalPhoton::Definition();
    G4Electron::Definition();
    G4Alpha::Definition();
    //G4BosonConstructor::ConstructParticle();
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePhysicsConstructor::ConstructProcess()
{
    if (enableThermalElectrons) {
        G4cout << "Thermal electrons are enabled." << G4endl;
    }else{
        G4cout << "NO thermal electrons will be produced in this simulation " << G4endl;
    }
    ConstructOptical();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void LXePhysicsConstructor::ConstructOptical()
{
    if (!enableOptics){
        G4cout << "No optical photons will be produced in this simulation " << G4endl;
        return;
    }
      
    //Cerenkov
    G4Cerenkov* theCerenkovProcess = new G4Cerenkov;
    theCerenkovProcess->SetMaxNumPhotonsPerStep(10);
    theCerenkovProcess->SetTrackSecondariesFirst(true);
    
    //Scintillation Process
    G4S1Light* theScintillationProcess = new G4S1Light;
    theScintillationProcess->SetSinglePhaseBoolean(SinglePhase);
    
    LXeRunControl* Control_Instance =  LXeRunControl::GetInstance();
    theScintillationProcess->SetYieldReductionFactor(Control_Instance->getScintYield());
					// Here the scintillation yield is the
					// reduction factor used to reduce the Yield in G4S1Light.cc
    
    if (NESTFactor == 0) {
             theScintillationProcess->SetScintillationYieldFactor(NESTFactor); // NEST: 1. = enabled, 0. = disabled
        G4cout << "NEST is turned OFF! No scintillation takes place! " << G4endl;
        G4cout << "This has no impact on any other optical processes that might occur! " << G4endl;
    }else{
        theScintillationProcess->SetScintillationYieldFactor(NESTFactor); // NEST: 1. = enabled, 0. = disabled
        G4cout << "NEST is turned ON! NEST Factor: " << NESTFactor << G4endl;
        if(theScintillationProcess->GetSinglePhaseBoolean() ){
            G4cout << "Single phase turned ON! Thermal electrons are produced: False" << G4endl;
        }else{
            G4cout << "Single phase turned OFF! Thermal electrons are produced if not disabled." << G4endl;
        }
        
    }
   
    theScintillationProcess->SetTrackSecondariesFirst(true);
    //Absorption Process
    G4OpAbsorption* theAbsorptionProcess     = new G4OpAbsorption();
    //Rayleigh Scattering Process
    G4OpRayleigh* theRayleighScatteringProcess = new G4OpRayleigh();
    //Optical Boundary Process
    G4OpBoundaryProcess* theBoundaryProcess  = new G4OpBoundaryProcess();
    
    
    aParticleIterator->reset();
    while( (*aParticleIterator)() ) {
        
        G4ParticleDefinition* particle = aParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        
        if (theScintillationProcess->IsApplicable(*particle)) {
            pmanager->AddProcess(theScintillationProcess, ordDefault+1, ordInActive, ordDefault+1); //for nest
        }   //int: AtRest, AlongTheStep, PostStep;
            //neg value: Process inactive
if(Control_Instance->getCherenkov()){
        if (theCerenkovProcess->IsApplicable(*particle)) {
            pmanager->AddProcess(theCerenkovProcess);
            pmanager->SetProcessOrdering(theCerenkovProcess, idxPostStep);
        }
}
        if (particleName == "opticalphoton") {             // photons only
            pmanager->AddDiscreteProcess(theAbsorptionProcess);
            pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
            pmanager->AddDiscreteProcess(theBoundaryProcess);
        } // maybe register Processes for electrons in the same way!

    }
}