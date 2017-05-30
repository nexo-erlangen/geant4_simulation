/// \file LXeXenonConstructor.cc
/// \brief Implementation of the LXeXenonConstructor class
//
//  Created by Reimund Bayerlein on 10/02/16.
//
//This class is meant to create a logical volume for Xenon in a function Construct()
//The constructor must be given a boolean value in order to decide if LXe or GXe should be created
//

#include "LXeXenonConstructor.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeXenonConstructor::LXeXenonConstructor(G4bool UseGasInsteadOfLiquid)
                                         : fUseGasInsteadOfLiquid(UseGasInsteadOfLiquid), // Takes the boolean recieved from Detector Construction
CylinderStart(0*deg),
CylinderEnd(360*deg),
FinalMaterial(0)
{
	GasPressure = LXeRunControl::GetInstance()->getPressure(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeXenonConstructor::~LXeXenonConstructor()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* LXeXenonConstructor::Construct()
{
// ---------------------------------------------------- GEOMETRICAL SHAPES ONLY ----------------------------------------------------

    G4double OuterRadius = 4*cm;
    G4double InnerRadius = 0*cm;

    G4double XeCylinderheight = 9.3*cm;
    G4double XeBottomThickness = 0.8*cm; // if created with that value:
    //makes the bottom cylinder be twice as large as neccessary
    //This is due to the boolean operation of G4UnionSolid
    //-> overlap is needed or prefered
    G4double XeBottomRadius = (3.1/2)*cm;
    G4ThreeVector XeCenterpointSpacer = G4ThreeVector(0,0,-(XeCylinderheight/2));
	
    // LXe Cylinders
    //
    G4Tubs * solidXeCylinderLarge =
    new G4Tubs("XeCylinderLarge",
               InnerRadius,
               OuterRadius,
               XeCylinderheight/2,
               CylinderStart,
               CylinderEnd);
    
    G4Tubs* solidXeCylinderBottom =
    new G4Tubs("XeZylinderBottom",
               0*cm,
               XeBottomRadius,
               XeBottomThickness,
               CylinderStart,
               CylinderEnd);
    
    G4RotationMatrix * yRot = new G4RotationMatrix; //cause UnionSolid needs a rot matrix for translation
    yRot->rotateY(0*rad); //rotation set to zero
    
    G4UnionSolid* solid_Xenon =
    new G4UnionSolid("LXeTotal",
                     solidXeCylinderLarge,
                     solidXeCylinderBottom,
                     yRot,
                     XeCenterpointSpacer);
   /* 
    G4Sphere* TestSphere =
    new G4Sphere("TestSphere",//name
                 0*cm, //Rmin
                 0.5*cm, //Rmax
                 0*deg, //pSPhi
                 360*deg, //pDPhi
                 0*deg, //pSTheta
                 180*deg); //pDTheta
*/
// ---------------------------------------------------- MATERIALS & PROPERTIES ----------------------------------------------------
   // G4NistManager* nist = G4NistManager::Instance();
   // G4Material* mat_Test = nist->FindOrBuildMaterial("G4_Al");
    
//
// LXe Content of Copper Cylinder
//
    G4double Z_Xe, a_Xe;
	a_Xe=131.292*g/mole;
	Z_Xe=54.;
    G4Element* elementXe = new G4Element("Xenon", "Xe", Z_Xe, a_Xe);

	const G4int NUMENTRIES = 22;
	// Photon Energy
	photonEnergies = new G4double[NUMENTRIES]; // Declaration in header file
    photonWavelengths = new G4double[NUMENTRIES];
    photonWavelengths[0] = 144.5;
    photonWavelengths[1] = 175.8641;
    photonWavelengths[2] = 177.6278;
    photonWavelengths[3] = 179.4272;
    photonWavelengths[4] = 193.6;
    photonWavelengths[5] = 250.3;
    photonWavelengths[6] = 303.4;
    photonWavelengths[7] = 340.4;
    photonWavelengths[8] = 410.2;
    photonWavelengths[9] = 467.8;
    photonWavelengths[10] = 508.6;
    photonWavelengths[11] = 546.1;
    photonWavelengths[12] = 627.8;
    photonWavelengths[13] = 706.5;
    photonWavelengths[14] = 766.5;
    photonWavelengths[15] = 844.7;
    photonWavelengths[16] = 1000.0;
    photonWavelengths[17] = 1300.0;
    photonWavelengths[18] = 1529.6;
    photonWavelengths[19] = 1600.0;
    photonWavelengths[20] = 1800.0;
    photonWavelengths[21] = 2058.2;
    for( G4int i=0; i<NUMENTRIES; i++ )
        photonEnergies[NUMENTRIES-1-i] = (4.13566743E-15*299792458/(photonWavelengths[i]*1.E-9))*eV;
    //refractive index values taken from: 'New approach to the calculation
    //of the refractive index of liquid and solid xenon' (some values merely estimated)
    //https://ir.kochi-u.ac.jp/dspace/bitstream/10126/4658/1/Hitachi2005JCP234508.pdf***
    
    
    G4MaterialPropertiesTable* Xe_MPT = new G4MaterialPropertiesTable();
    
    Xe_MPT->AddConstProperty( "ELECTRICFIELD", 0*volt/cm ); //for missed nooks and crannies
    Xe_MPT->AddConstProperty( "ELECTRICFIELDSURFACE", 0*volt/cm );
    Xe_MPT->AddConstProperty( "ELECTRICFIELDGATE", 0*volt/cm );
    Xe_MPT->AddConstProperty( "ELECTRICFIELDCATHODE", 0*volt/cm );
    Xe_MPT->AddConstProperty( "ELECTRICFIELDBOTTOM", 0*volt/cm );
    Xe_MPT->AddConstProperty("TOTALNUM_INT_SITES",-1);
    
    if(fUseGasInsteadOfLiquid==false){
        G4cout << "Detector medium: LIQUID XENON" << G4endl;
        
        G4double d_LXe= 3.*g/cm3;
		G4Material* mat_LXe = new G4Material("liquid Xenon",		 //its name
									d_LXe, 			// its density
									1, 				// number of atoms
									kStateLiquid,		// phase
									163.2*kelvin, 	// temperature
									1.0*atmosphere);	// pressure
	
        mat_LXe->AddElement(elementXe,1);

// Scintillation Properties of LXe 
/// CRUCIAL FOR SCINTILLATION!!

	// Refractive Index
	LXeRefractiveIndex = new G4double[NUMENTRIES]; // Declaration in header file
    LXeRefractiveIndex[21-0] = 1.82;
    LXeRefractiveIndex[21-1] = 1.663;// originally ~1.63 <-> possible shift needed based on temperature?
    LXeRefractiveIndex[21-2] = 1.648;// originally ~1.61
    LXeRefractiveIndex[21-3] = 1.637;// originally ~1.58
    LXeRefractiveIndex[21-4] = 1.576;
    LXeRefractiveIndex[21-5] = 1.468;
    LXeRefractiveIndex[21-6] = 1.429;
    LXeRefractiveIndex[21-7] = 1.415;
    LXeRefractiveIndex[21-8] = 1.404;
    LXeRefractiveIndex[21-9] = 1.3982;
    LXeRefractiveIndex[21-10] = 1.3951;
    LXeRefractiveIndex[21-11] = 1.392;
    LXeRefractiveIndex[21-12] = 1.3879;
    LXeRefractiveIndex[21-13] = 1.3865;
    LXeRefractiveIndex[21-14] = 1.3861;
    LXeRefractiveIndex[21-15] = 1.386;
    LXeRefractiveIndex[21-16] = 1.386;
    LXeRefractiveIndex[21-17] = 1.385;
    LXeRefractiveIndex[21-18] = 1.385;
    LXeRefractiveIndex[21-19] = 1.384;
    LXeRefractiveIndex[21-20] = 1.384;
    LXeRefractiveIndex[21-21] = 1.383;
    
    // Rayleigh Scattering // Rayleighlengthcalculation lXe (evtl auch fuer sXe)
    G4double LXe_RayleighLength = 40*cm;
    LXe_RayL = new G4double[NUMENTRIES]; //Declaration in header
    for (int i=0; i<NUMENTRIES; i++) {
        LXe_RayL[i]=LXe_RayleighLength;
    }
    
    G4double LXe_AbsorptionLength = 20*m; // For_Document: 200*cm
    LXe_ABSL = new G4double[NUMENTRIES]; //Declaration in header
    for (int i=0; i<NUMENTRIES; i++) {
        LXe_ABSL[i]=LXe_AbsorptionLength;
    }
// Further Scintillation values in "Third", but also commented out
		
// Add Properties
	Xe_MPT -> AddProperty("RINDEX", photonEnergies,LXeRefractiveIndex,NUMENTRIES);
	Xe_MPT -> AddProperty("ABSLENGTH",photonEnergies,LXe_ABSL,NUMENTRIES);
    Xe_MPT -> AddProperty("RAYLEIGH", photonEnergies, LXe_RayL, NUMENTRIES);

	mat_LXe -> SetMaterialPropertiesTable(Xe_MPT);
	
	// G4cout << mat_LXe;		// print element "mat_LXe"

    FinalMaterial = mat_LXe;
    }
    
    else{
        G4cout << "Detector medium: GASEOUS XENON" << G4endl;
    
        G4double d_GXe=5.8982E-3*g/cm3; // Wiki
        G4Material* mat_GXe = new G4Material("gaseous Xenon",		 //its name
                                             GasPressure*d_GXe, 			// its density
                                             1, 				// number of atoms
                                             kStateGas,		// phase
                                             173.15*kelvin, 	// temperature
                                             GasPressure*atmosphere);	// pressure
	    G4cout << "Pressure: " << GasPressure << "*atmosphere"  << G4endl;
        
        mat_GXe->AddElement(elementXe,1);
        
        // Scintillation Properties of GXe
        /// CRUCIAL FOR SCINTILLATION!!

        // Refractive Index wave length independent for gas!
        LXeRefractiveIndex = new G4double[NUMENTRIES]; // Declaration in header file
        for (int i=0; i< NUMENTRIES; i++) {
            LXeRefractiveIndex[i]=1.00;  // http://refractiveindex.info/?shelf=main&book=Xe&page=Bideau-Mehu
                                        // exact till 3rd decimal place
        }
        
        // Rayleigh Scattering // Rayleighlengthcalculation lXe (evtl auch fuer sXe)
        G4double LXe_RayleighLength = 40*cm;
        LXe_RayL = new G4double[NUMENTRIES]; //Declaration in header
        for (int i=0; i<NUMENTRIES; i++) {
            LXe_RayL[i]=LXe_RayleighLength;
        }
        
        G4double LXe_AbsorptionLength = 20*m;
        LXe_ABSL = new G4double[NUMENTRIES]; //Declaration in header
        for (int i=0; i<NUMENTRIES; i++) {
            LXe_ABSL[i]=LXe_AbsorptionLength;
        }
        // Further Scintillation values in "Third", but also commented out
        
        // Add Properties
        Xe_MPT -> AddProperty("RINDEX", photonEnergies,LXeRefractiveIndex,NUMENTRIES);
        Xe_MPT -> AddProperty("ABSLENGTH",photonEnergies,LXe_ABSL,NUMENTRIES);
        Xe_MPT -> AddProperty("RAYLEIGH", photonEnergies, LXe_RayL, NUMENTRIES);
        
        mat_GXe -> SetMaterialPropertiesTable(Xe_MPT);
        
        // G4cout << mat_LXe;		// print element "mat_LXe"
        

        FinalMaterial = mat_GXe;
    }

// ---------------------------------------------------- LOGICAL VOLUMES ----------------------------------------------------
    
    G4LogicalVolume* logical_Xe =
    new G4LogicalVolume(solid_Xenon,
                        FinalMaterial,
                        "Xenon");
 /*   G4LogicalVolume* logical_TestSphere =
    new G4LogicalVolume(TestSphere, //solid volume
			FinalMaterial,
			"Test_Sphere");
    
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logical_TestSphere,            //its logical volume
                      "Test_Sphere",               //its name
                      logical_Xe,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      false);        //overlaps checking
 */   
    return logical_Xe;
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......







