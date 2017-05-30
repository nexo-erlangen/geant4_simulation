/// \file LXeDetectorConstruction.hh
/// \brief Definition of the LXeDetectorConstruction class

#ifndef LXeDetectorConstruction_h
#define LXeDetectorConstruction_h 1

#include "LXeRunControl.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class LXeDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    LXeDetectorConstruction(G4bool);

    virtual ~LXeDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    G4ThreeVector Add(G4ThreeVector vec1, G4ThreeVector vec2);
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume;} //SiPM Volume is returned here!
    G4LogicalVolume* GetPMTSensitiveVolume() const {return fPMTSensitiveVolume;}
    G4LogicalVolume* GetZylinderVolume() const {return logical_CuCylinder;}
    G4LogicalVolume* GetLogicalXenon() const {return logical_Xe;}
    //G4double GetCylinderHeight() {return Cu_height;}

  protected:
    G4LogicalVolume* fScoringVolume;
    G4LogicalVolume* fPMTSensitiveVolume;
    G4LogicalVolume* logical_CuCylinder; // Cu-Zylinder
    G4LogicalVolume* logical_Xe;
    G4bool UseGasInsteadOfLiquid;
    G4bool checkOverlaps;	// Option to switch on/off checking of volumes overlaps
    G4double CuReflectivity;
    LXeRunControl* Control_Instance;
	
    
 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 