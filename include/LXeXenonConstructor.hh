/// \file LXeXenonConstructor.cc
/// \brief Implementation of the LXeXenonConstructor class
//
//  Created by Reimund Bayerlein on 10/02/16.

#ifndef LXeXenonConstructor_h
#define LXeXenonConstructor_h 1

#include "LXeRunControl.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"


/// Detector construction class to define XENON materials and geometry
/// and to return a logical volume

class G4LogicalVolume;

class LXeXenonConstructor
{
public:
    LXeXenonConstructor(G4bool UseGasInsteadOfLiquid);
    
    virtual ~LXeXenonConstructor();
    
    G4LogicalVolume* Construct();
    G4Material* GetFinalMaterial() const {return FinalMaterial;}
protected:
    G4bool fUseGasInsteadOfLiquid;
    G4double CylinderStart;
    G4double CylinderEnd;

    G4double GasPressure;
    
    G4Material* FinalMaterial;
    
    G4double *photonEnergies;
    G4double *LXeRefractiveIndex;
    G4double *photonWavelengths;
    G4double *LXe_RayL;
    G4double *LXe_ABSL;
    

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif