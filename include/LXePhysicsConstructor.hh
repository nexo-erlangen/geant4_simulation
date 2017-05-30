//
//  LXePhotonPhysicsConstructor.h
//  
//
//  Created by Reimund Bayerlein on 29/01/16.
//
//

#ifndef LXePhotonPhysicsConstructor_h
#define LXePhotonPhysicsConstructor_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class LXePhysicsConstructor : public G4VPhysicsConstructor
{
public:
    LXePhysicsConstructor(G4bool passedBoolean, G4double NestF);
    
    virtual ~LXePhysicsConstructor();
    
    void ConstructProcess();
    void ConstructParticle();

protected:
    void ConstructOptical();
    
private:

    G4bool enableOptics;
    G4bool enableThermalElectrons;
    G4double NESTFactor;
    G4bool SinglePhase;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif