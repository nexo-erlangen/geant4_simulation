/// \file LXeDetectorConstruction.cc
/// \brief Implementation of the LXeDetectorConstruction class

#include "LXeDetectorConstruction.hh"
#include "LXePrimaryGeneratorAction.hh"
#include "LXeXenonConstructor.hh"
#include "LXeRunControl.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh" 

//hi
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeDetectorConstruction::LXeDetectorConstruction(G4bool useGas)
: G4VUserDetectorConstruction(), // Using wrapper class
fScoringVolume(0),
fPMTSensitiveVolume(0),
logical_CuCylinder(0),
logical_Xe(0),
UseGasInsteadOfLiquid(useGas),
checkOverlaps(false) // DO NEVER SWITCH ON!!!
			// GUI will not start for whatever the reason might be
			//If check is necessare, perform manually for each placement
{Control_Instance = LXeRunControl::GetInstance(); }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeDetectorConstruction::~LXeDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* LXeDetectorConstruction::Construct()
{  

// ---------------------------------------------------- MATERIALS & PROPERTIES ----------------------------------------------------
    
    // Get nist material manager
    
    G4NistManager* nist = G4NistManager::Instance();
    
// 
// World
//
   	G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

//
// Envelope
//
	G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
	//ALTERNATIVELY:
/*	G4double density = 1.05*mg/cm3;
	G4Material* env_mat = nist->BuildMaterialWithNewDensity(
								"Water_1.05",
								"G4_WATER",
								density,
								300*kelvin,
								1.*atmosphere);
*/


//
// Copper cylinder
//
	G4Material* mat_Cu = nist->FindOrBuildMaterial("G4_Cu");
    // ACCORDING TO JASON BRODSKY: DO NOT ASSIGN OPTICAL PROPERTIES TO COPPER!!
	/*const G4int Cu_int =3;
	G4double Cu_Energy[Cu_int] = {0.1*eV, 10*eV, 30*eV};
	G4double Cu_RIND[Cu_int] = {1.57, 1.57, 1.57};
    G4double Cu_ABSL[Cu_int] = {0.01*cm, 0.01*cm, 0.01*cm};
	G4MaterialPropertiesTable* Cu_MPT= new G4MaterialPropertiesTable();
    Cu_MPT -> AddProperty("ABSLENGTH",Cu_Energy, Cu_ABSL,Cu_int);
	Cu_MPT -> AddProperty("RINDEX", Cu_Energy, Cu_RIND, Cu_int);
	mat_Cu->SetMaterialPropertiesTable(Cu_MPT);
*/



//
// SiPM
//
	//G4Material* mat_SiPM = nist->FindOrBuildMaterial("G4_Si");
    
//
// Silicondioxide
//
    
    G4double z_Silicon, z_Oxigen, a_Silicon, a_Oxigen, density;
    G4String name_Oxigen, name_Silicon, symbol_Oxigen, symbol_Silicon;
    G4int ncomponents, natoms;
    
    z_Silicon=14.;
    a_Silicon = 28.085*g/mole;
    G4Element* elS  = new G4Element(name_Silicon="Silicon",symbol_Silicon="Si" , z_Silicon, a_Silicon);
    
    z_Oxigen=8.;
    a_Oxigen = 16.00*g/mole;
    G4Element* elO  = new G4Element(name_Oxigen="Oxygen"  ,symbol_Oxigen="O" , z_Oxigen, a_Oxigen);
    
    density = 2.65*g/cm3;
    G4Material* mat_SiO_2 = new G4Material("SiliconDioxide",density,ncomponents=2);
    mat_SiO_2->AddElement(elS, natoms=1);
    mat_SiO_2->AddElement(elO, natoms=2);
    
//
// PMT and Source holder
//
    G4Material* mat_PMT = nist->FindOrBuildMaterial("G4_Ni");
    G4Material* mat_AlFrame = nist->FindOrBuildMaterial("G4_Al");
    
//
// Teflon Frame
//
    G4Material* mat_Teflon = nist->FindOrBuildMaterial("G4_TEFLON");
    
//
// Am Holder
//
   // G4Material* mat_Am_holder = nist->FindOrBuildMaterial("G4_Al");
    
// ---------------------------------------------------- GEOMETRICAL SHAPES ONLY ----------------------------------------------------

// ================ DIMENSIONS ================
    G4double env_sizeXY = 14*cm, env_sizeZ = 20*cm;	// size of envelope
    G4double CuCylinderRadius = 5.0*cm; // Outer radius of Cu Cylinder
    G4double CuCylinderHeight = 11.3*cm; // TOTAL height of Cu Cylinder
    //G4double CuCylinderHalfHeight = CuCylinderHeight/2; //HALF height of Cu Cylinder
    G4double Cylinder_start = 0*deg, Cylinder_end = 360*deg; //defines full cylinder
    
    G4double PMT_Height_Above_Source = 3.357*cm; //Absolute z-Position above the Source for PMT
    G4double SiPM_Height_Above_Source = 3.965*cm;
  
    G4double SiPM_Frame_xy = 0.62*cm; //total xy-length
    G4double SiPM_Frame_z = 0.10*cm;//total thickness
    
    G4double SiPM_Sensitive_xy = 0.60*cm;
    G4double SiPM_Sensitive_z = 0.08*cm;
    
    // Abmessungen aus Datenblat zu PMT_R8520-406_SEL HAMAMATSU    
    G4double PMT_xy = 2.57*cm;//total values!
    G4double PMT_z = 2.705*cm;//total values! Without glas window which has a thickness of 1.2*cm
    
    G4double AlFrame_z = 0.12*cm;
    G4double AlFrame_xy = PMT_xy;
    
    G4double Silica_Window_xy = 2.4*cm; //total values
    G4double Silica_Window_z = AlFrame_z; //total values
    
    G4double PMT_Sensitive_z = AlFrame_z;
    G4double PMT_Sensitive_xy = 2.05*cm;

// SiPM Board
    G4double SiPM_Board_xy = 3.5*cm;
    G4double SiPM_Board_Thickness = 0.155*cm;// Total values!
   

// Americium Holder consisting of Aluminum
    G4double Am_holder_Radius = 1.5*cm;
    G4double Am_holder_total_thickness = 0.8*cm;
    G4double Am_holder_notch_Radius = 0.5*cm;
    G4double Am_holder_notch_total_thickness = 0.12*cm;//changed this from 0.10*cm
    
// Aluminum Spacer between Teflon Board Holder and SiPM Board itself
    G4double Al_Spacer_Radius = 0.3*cm;
    G4double Al_Spacer_Length = 2.18*cm;
    
//Teflon Holder    
    G4double Teflon_Holder_Thickness = 0.8*cm; // total thickness
   G4double Board_holder_main_x = 1.65*cm;
   G4double Board_holder_main_y = 2.7*cm;
   G4double Board_holder_main_z = Teflon_Holder_Thickness/2;

     G4double Board_holder_trapezoid_big_pX1 = 0.4*cm;
     G4double Board_holder_trapezoid_big_pX2 = 0.4*cm;
     G4double Board_holder_trapezoid_big_pY1 = 2.7*cm;
    G4double Board_holder_trapezoid_big_pY2 = 1.6*cm;
    G4double Board_holder_trapezoid_big_pZ = 1.2*cm;

 G4double Board_holder_trapezoid_small_pX1 = 0.4*cm;
     G4double Board_holder_trapezoid_small_pX2 = 0.4*cm;
     G4double Board_holder_trapezoid_small_pY1 = 2.7*cm;
    G4double Board_holder_trapezoid_small_pY2 = 2.15*cm;
    G4double Board_holder_trapezoid_small_pZ = 0.6*cm;
    
    // ================ POSITION VECTORS ================

		 
	G4ThreeVector XePosition = G4ThreeVector(0,0,1*cm); //Position measured from (0,0,0)
	G4ThreeVector Xenon_Offset_Correction_Vector = -XePosition; 
		//This is necessary, because all G4PVPlacements of parts inside the chamber 
		//are using logical_Xe as mother volume
		//Therefore, they are placed incorrect with an offset of 1*cm 
		//because of "G4ThreeVector XePosition = G4ThreeVector(0,0,1*cm);"
	
	G4ThreeVector Source_Position = Add(Xenon_Offset_Correction_Vector, G4ThreeVector(0,0,-3.75*cm));
	//G4ThreeVector Source_Position = G4ThreeVector(0,0,-3.75*cm);
	//This position is now measured from the origin of the Xenon volume
	//Which globally is at (0,0,1*cm)
	
	G4double PMT_Position_x = -1.90*cm;
	G4double PMT_Position_y = 0*cm;
	G4double PMT_Position_z = (PMT_Height_Above_Source + AlFrame_z+PMT_z/2); //Measured from the source position
	G4ThreeVector Source_to_PMT = G4ThreeVector(PMT_Position_x,PMT_Position_y,PMT_Position_z);
	
	G4double SiPM_Position_x = Control_Instance->getSiPM_xPos()*cm;
	G4double SiPM_Position_y =0.55*cm;
	G4double SiPM_Position_z = (SiPM_Height_Above_Source + SiPM_Frame_z/2);//Measured from the source position
	G4ThreeVector Source_to_SiPM = G4ThreeVector(SiPM_Position_x, SiPM_Position_y, SiPM_Position_z);
	
	G4ThreeVector PMT_Position = Add(Source_Position, Source_to_PMT);//Position measured from Source_Position
	G4ThreeVector SiPM_Position = Add(Source_Position, Source_to_SiPM);
	
	G4ThreeVector PMT_to_AlFrame = G4ThreeVector(0,0,-(PMT_z/2+AlFrame_z/2));
	G4ThreeVector PMT_to_Silica = G4ThreeVector(0,0,-(PMT_z/2+AlFrame_z/2));
	
	G4ThreeVector AlFrame_Position = Add(PMT_Position, PMT_to_AlFrame);//Position measured from PMT_Position
	
	G4ThreeVector Silica_Window_Position =Add(PMT_Position, PMT_to_Silica);//Position measured from PMT_Position
	
	G4ThreeVector PMT_to_PMT_Sensitive = G4ThreeVector(0,0,-(PMT_z/2-PMT_Sensitive_z/2));
	G4ThreeVector PMT_Sensitive_Position = Add(PMT_Position, PMT_to_PMT_Sensitive);
	
	G4ThreeVector SiPM_Frame_to_SiPM_Sensitive = G4ThreeVector(0,0,(-SiPM_Frame_z/2+SiPM_Sensitive_z/2));
	G4ThreeVector SiPM_Sensitive_Position = Add(SiPM_Position, SiPM_Frame_to_SiPM_Sensitive);
	
	G4ThreeVector Source_to_Am_holder = G4ThreeVector(0,0,-0.3*cm);
	G4ThreeVector Am_holder_position = Add(Source_Position, Source_to_Am_holder); // Not bound to other values and lengths fixme
	
	G4double Teflonholder_zPos =  CuCylinderHeight/2-(2.2*cm+Teflon_Holder_Thickness/2);
	G4ThreeVector Teflonholder_Position_global = G4ThreeVector(0.5*cm, 0, Teflonholder_zPos);
	G4ThreeVector Teflonholder_Position = Add(Teflonholder_Position_global, Xenon_Offset_Correction_Vector);
	
	G4double Distance_Teflon_SiPM_Board = Al_Spacer_Length;
	G4double Teflon_to_Board_z = -Teflon_Holder_Thickness/2- Distance_Teflon_SiPM_Board - SiPM_Board_Thickness/2;
	G4double Teflon_to_Board_x = 1.5*cm;
	G4double Teflon_to_Board_y = 0*cm;
	G4ThreeVector Teflon_To_SiPM_Board = G4ThreeVector(Teflon_to_Board_x,Teflon_to_Board_y,Teflon_to_Board_z);
	G4ThreeVector SiPM_Board_Position = Add(Teflonholder_Position,Teflon_To_SiPM_Board);
	
	G4ThreeVector Board_to_AlSpacer_11 = G4ThreeVector(-1.0*cm, +1.0*cm, (Al_Spacer_Length/2+SiPM_Board_Thickness/2)); 
	G4ThreeVector AlSpacer_11_Position = Add(Board_to_AlSpacer_11, SiPM_Board_Position);
	G4ThreeVector AlSpacer_12_Position = Add(AlSpacer_11_Position, G4ThreeVector(2.0*cm, 0,0));
	G4ThreeVector AlSpacer_21_Position = Add(AlSpacer_11_Position, G4ThreeVector(0, -2.0*cm,0));
	G4ThreeVector AlSpacer_22_Position = Add(AlSpacer_11_Position, G4ThreeVector(2.0*cm, -2.0*cm,0));
	
	/* seen from the front: 
	11	back left
	12	back right
	21	front left
	22	front right
	*/
	
    G4RotationMatrix * yRot = new G4RotationMatrix; //cause SubtractionSolid needs a rotation matrix for translation
    yRot->rotateY(0*rad); //rotation set to zero
     
    // ================ SOLID VOLUMES ================   
//
// World
//
    G4double world_sizeXY = 1.2*env_sizeXY;
	G4double world_sizeZ  = 1.2*env_sizeZ;

  
	G4Box* solidWorld =    
	new G4Box("World",                       //its name
			0.5*world_sizeXY, 
			0.5*world_sizeXY, 
			0.5*world_sizeZ);     //its size
    

//
// Envelope
//
		
	G4Box* solidEnv =    
	new G4Box("Envelope",                    //its name
		0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
    

//
// Copper Cylinder
//
    
    G4Tubs* solidCuCylinder =
    new G4Tubs("CuCylinder",
               0*cm, //inner radius
               CuCylinderRadius,
               CuCylinderHeight/2,
               Cylinder_start,
               Cylinder_end);
    

//
// SiPM und Board
//
   G4Box* solidSiPM_Frame_Box =
    new G4Box("SiPM_Frame_Box",
              SiPM_Frame_xy/2,SiPM_Frame_xy/2,SiPM_Frame_z/2);
	
	G4Box* solidSiPM_Sensitive = 
	new G4Box("SiPM_Sensitive",
		SiPM_Sensitive_xy/2 ,SiPM_Sensitive_xy/2 ,SiPM_Sensitive_z/2);
		
	G4SubtractionSolid* solidSiPM_Frame=
	new G4SubtractionSolid("SiPM_Frame",
		solidSiPM_Frame_Box,
		solidSiPM_Sensitive,
		yRot,
		SiPM_Frame_to_SiPM_Sensitive);
//
// PMT and PMT_Window and PMT_Front_Frame
//
    G4Box* solidPMT_Box =
    new G4Box("PMT_Box",
              PMT_xy/2,
              PMT_xy/2,
              PMT_z/2);
	      
	G4Box* solidPMT_Sensitive_Box = // This is only need for G4SubtractionSolid
	new G4Box("PMT_Sensitive",
		PMT_Sensitive_xy/2,		
		PMT_Sensitive_xy/2,
		PMT_Sensitive_z);
	
	G4Box* solidPMT_Sensitive = // Actual solid
	new G4Box("PMT_Sensitive",
		PMT_Sensitive_xy/2,		
		PMT_Sensitive_xy/2,
		PMT_Sensitive_z/2);
		
	G4ThreeVector PMT_to_PMT_Sensitive_for_SubtractionSolid =
		G4ThreeVector(0,0,-PMT_z/2);
		
	G4SubtractionSolid* solid_PMT =
	new G4SubtractionSolid("PMT",
		solidPMT_Box,
		solidPMT_Sensitive_Box,
		yRot,
		PMT_to_PMT_Sensitive_for_SubtractionSolid);
    
   // G4Box* solidPMT_Window =
    new G4Box("PMT_Window", // Silica Window
              Silica_Window_xy/2,
              Silica_Window_xy/2,
              Silica_Window_z/2);
	      
    G4Box* solidPMT_Window_Box =
    new G4Box("PMT_Window", // Silica Window for G4SubtractionSolid
              Silica_Window_xy,
              Silica_Window_xy,
              Silica_Window_z);
    
    G4Box* solidPMT_Front_Frame_Box=
    new G4Box("PMT_Front_Frame", //Al Frame Box
              AlFrame_xy/2,
              AlFrame_xy/2,
              AlFrame_z/2);
    
    G4SubtractionSolid* solidPMT_Front_Frame=
    new G4SubtractionSolid("PMT_Front_Frame_Total", //Al Frame Total
                           solidPMT_Front_Frame_Box,
                           solidPMT_Window_Box,
                           yRot,
                           G4ThreeVector(0,0,0));
    
//
// Teflon frame
//
 /*
    G4Tubs* solidFrame =
    new G4Tubs("Frame",
               0*cm,
               Frame_Radius,
               Frame_Thickness/2,
               Cylinder_start,
               Cylinder_end);
    
    G4SubtractionSolid* solidFrame_Total =
    new G4SubtractionSolid("Frame_Total",
                           solidFrame,
                           solidPMT,
                           yRot,
                           G4ThreeVector(-2*cm, 0*cm, -Relation_Frame_PMT));
*/

//
// Am Holder
//
    G4Tubs * Am_holder_Pt_1 =
    new G4Tubs("Am_holder_Pt1",
               0*cm,
               Am_holder_Radius,
               Am_holder_total_thickness/2,
               Cylinder_start,
               Cylinder_end);
	       
    G4Tubs * Am_holder_Pt_2 =
    new G4Tubs("Am_holder_Pt_2",
               0*cm,
               Am_holder_notch_Radius,
               Am_holder_notch_total_thickness, //Take total thickness for G4SubtractionSolid
               Cylinder_start,
               Cylinder_end);
    
    G4SubtractionSolid *solidAm_holder =
    new G4SubtractionSolid("solidAm_holder",
                           Am_holder_Pt_1,
                           Am_holder_Pt_2,
                           yRot,
                           G4ThreeVector(0,0,0.4*cm));
			   
    G4Tubs* solidAlSpacer =
    new G4Tubs("AlSpacer",
               0*cm, //inner radius
               Al_Spacer_Radius,
               Al_Spacer_Length/2,
               Cylinder_start,
               Cylinder_end);
	       
//
// Teflon  Board  Holder
//
//The Required Rotations:

G4RotationMatrix * Trap_big_1 = new G4RotationMatrix;
    Trap_big_1->rotateY(90*deg); 
    Trap_big_1->rotateZ(0*deg);
    Trap_big_1->rotateX(0*deg);

    G4RotationMatrix * Trap_small_1 = new G4RotationMatrix; 
    Trap_small_1->rotateY(-90*deg);
    Trap_small_1->rotateZ(0*deg);
    Trap_small_1->rotateX(0*deg);

// The Body:
G4Box * Board_holder_main =
new G4Box("Board_holder_main",
                Board_holder_main_x,
                Board_holder_main_y,
                Board_holder_main_z);

G4Trd * Board_holder_trapezoid_big =
new G4Trd("Board_holder_trapezoid_big",
                Board_holder_trapezoid_big_pX1,
                Board_holder_trapezoid_big_pX2,
                Board_holder_trapezoid_big_pY1,
                Board_holder_trapezoid_big_pY2,
                Board_holder_trapezoid_big_pZ);

G4Trap * Board_holder_trapezoid_small =
new G4Trap("Board_holder_trapezoid_small",
                Board_holder_trapezoid_small_pX1,
                Board_holder_trapezoid_small_pX2,
                Board_holder_trapezoid_small_pY1,
                Board_holder_trapezoid_small_pY2,
                Board_holder_trapezoid_small_pZ);

G4UnionSolid *solidBoard_holder_step_1 =
    new G4UnionSolid("solidBoard_holder_step_1",
                        Board_holder_main,
                        Board_holder_trapezoid_big,
                        Trap_big_1,
                        G4ThreeVector(-28.5*mm,0*mm,0));

G4UnionSolid *solidBoard_holder_step_final =
    new G4UnionSolid("solidBoard_holder_step_final",
                        solidBoard_holder_step_1,
                        Board_holder_trapezoid_small,
                        Trap_small_1,
                        G4ThreeVector(22.5*mm,0*mm,0));
//	       
// SiPM Board
//
 G4Box* solidSiPM_Board =    
	new G4Box("SiPM_Board",                       //its name
			0.5*SiPM_Board_xy, 
			0.5*SiPM_Board_xy, 
			0.5*SiPM_Board_Thickness);     //its size	       
	       
// ---------------------------------------------------- VOLUMES (PHYICAL & LOGICAL & POSITION) ----------------------------------------------------

//
// World
//
	G4LogicalVolume* logicWorld =                         
	new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material "G4_AIR"
                        "World");            //its name
                                   
	G4VPhysicalVolume* physWorld = 
	new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
    
//
// Envelope
//
    
    
	G4LogicalVolume* logicEnv =                         
	new G4LogicalVolume(solidEnv,            //its solid
		env_mat,             //its material "G4_AIR"
		"Envelope");         //its name
               
	new G4PVPlacement(0,                       //no rotation
		G4ThreeVector(),         //at (0,0,0)
		logicEnv,                //its logical volume
		"Envelope",              //its name
		logicWorld,              //its mother  volume
		false,                   //no boolean operation
		0,                       //copy number
		checkOverlaps);          //overlaps checking
    
    
//
// Copper Cylinder
//
    
    logical_CuCylinder = //Declared in header
    new G4LogicalVolume(solidCuCylinder,
                        mat_Cu,
                        "CuCylinder");

    G4VPhysicalVolume* phys_CuCylinder =
    new G4PVPlacement(0,
                     G4ThreeVector(0,0,0),
                     logical_CuCylinder,
                     "CuCylinder",
                     logicEnv,
                     false,
                     0,
                     checkOverlaps);
   
    // Instantiation of a set of visualization attributes with red colour
    G4VisAttributes* visAttCuCylinder = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    //visAttCuCylinder->SetForceWireframe(true);
    //visAttCuCylinder->SetForceAuxEdgeVisible(true);
    visAttCuCylinder->SetForceLineSegmentsPerCircle(40);
    // Assignment of the visualization attributes to the logical volume
    logical_CuCylinder->SetVisAttributes(visAttCuCylinder);
   
//
// LXe Total placed inside CuCylinder
//
    
    LXeXenonConstructor* anInstance = new LXeXenonConstructor(UseGasInsteadOfLiquid);
    logical_Xe = anInstance->Construct();
    
    G4VPhysicalVolume* phys_Xe =
    new G4PVPlacement(0, 		//no rotation
                      XePosition,  		//at (0,0,1)
                      logical_Xe,           	//its logical volume
                      "Xenon",            	//its name
                      logical_CuCylinder,   	//its mother  volume
                      false,                    	//no boolean operation
                      0,                        	//copy number
                      checkOverlaps);        //overlaps checking
    

    G4VisAttributes* visAttXe =
    new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.15));
    //visAttXe->SetForceLineSegmentsPerCircle(40); // does not work with polyhedrons according to G4VisSceneHandler
    visAttXe->SetForceAuxEdgeVisible(true);
    logical_Xe->SetVisAttributes(visAttXe);
    // Assignment of the visualization attributes to the logical volume
   // logical_Xe-> SetVisAttributes (G4VisAttributes::GetInvisible()); // Make LXe invisible
    
    
//
// SiPM
//

    G4LogicalVolume* logical_SiPM_Frame =
    new G4LogicalVolume(solidSiPM_Frame,
                        mat_SiO_2,
                        "SiPM_Frame");
    
    G4VPhysicalVolume* phys_SiPM_Frame =
    new G4PVPlacement(0,
                      SiPM_Position,
                      logical_SiPM_Frame,
                      "SiPM_Frame",
                      logical_Xe,
                      false,
                      0,
                      true);

    G4LogicalVolume* logical_SiPM_Sensitive =
    new G4LogicalVolume(solidSiPM_Sensitive,
                        anInstance->GetFinalMaterial(),
                        "SiPM_Sensitive");
    
   // G4VPhysicalVolume* phys_SiPM_Sensitive =
    new G4PVPlacement(0,
                      SiPM_Sensitive_Position,
                      logical_SiPM_Sensitive,
                      "SiPM_Sensitive",
                      logical_Xe,
                      false,
                      0,
                      true);
		      
   // fScoringVolume = logical_SiPM;
     fScoringVolume = logical_SiPM_Sensitive;
    G4VisAttributes* visAttSiPM = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    //visAttSiPM->SetForceAuxEdgeVisible(true);
    logical_SiPM_Frame->SetVisAttributes(visAttSiPM);
  /*  
    G4LogicalVolume* logical_SiPM_Board =
    new G4LogicalVolume(solidSiPM_Board,
                        mat_Teflon,
                        "SiPM_Board");
    new G4PVPlacement(0,
                  SiPM_Board_Pos,
                  logical_SiPM_Board,
                  "SiPM_Board",
                  logical_Xe,
                  false,
                  0,
                  checkOverlaps);
    G4VisAttributes* visAttTeflon = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
    logical_SiPM_Board->SetVisAttributes(visAttTeflon);
    */
    
//
// PMT
//
    G4LogicalVolume* logical_PMT =
    new G4LogicalVolume(solid_PMT,
                        mat_PMT,
                        "PMT");
    G4VPhysicalVolume* phys_PMT =
    new G4PVPlacement(0,
                      PMT_Position,
                      logical_PMT,
                      "PMT",
                      logical_Xe,
                      false,
                      0,
                      checkOverlaps);
    G4VisAttributes* visAttPMT = new G4VisAttributes(G4Colour(1.0,0.0,1.0,0.5));
    logical_PMT->SetVisAttributes(visAttPMT);
    
    G4LogicalVolume* logical_PMT_Sensitive =
    new G4LogicalVolume(solidPMT_Sensitive,
			 anInstance->GetFinalMaterial(),
			"PMT_Sensitive");
			
	fPMTSensitiveVolume = logical_PMT_Sensitive;

    new G4PVPlacement(0,
			PMT_Sensitive_Position,
			logical_PMT_Sensitive,
			"PMT_Sensitive",
			logical_Xe,
			false,
			0,
			true);
    
    /*
    G4LogicalVolume* logical_PMT_Window = // Silica Window
    new G4LogicalVolume(solidPMT_Window,
                        mat_SiO_2,
                        "PMT_Window");
    new G4PVPlacement(0,
                      Silica_Window_Position,
                      logical_PMT_Window,
                      "PMT_Window",
                      logical_Xe,
                      false,
                      0,
                      checkOverlaps);
    logical_PMT_Window->SetVisAttributes(visAttSiPM);
  */  
    G4LogicalVolume* logical_PMT_Front_Frame = // Al Frame
    new G4LogicalVolume(solidPMT_Front_Frame,
                        mat_AlFrame,
                        "PMT_Front_Frame");
    new G4PVPlacement(0,
                      AlFrame_Position,
                      logical_PMT_Front_Frame,
                      "PMT_Front_Frame",
                      logical_Xe,
                      false,
                      0,
                      checkOverlaps);
    logical_PMT_Front_Frame->SetVisAttributes(visAttPMT);
    
//
// Am Holder
//

    G4LogicalVolume* logical_Am_holder =
    new G4LogicalVolume(solidAm_holder,
                        mat_AlFrame,
                        "Am_holder");
			
    G4VPhysicalVolume* phys_Am_holder =
    new G4PVPlacement(0,
                      Am_holder_position,
                      logical_Am_holder,
                      "Am_holder",
                      logical_Xe,
                      false,
                      0,
                      checkOverlaps); //checkOverlaps is turned on here!
    logical_Am_holder->SetVisAttributes(visAttPMT);

//
// Aluminum Spacer for the Board
//
    
  G4LogicalVolume* logical_AlSpacer = 
    new G4LogicalVolume(solidAlSpacer,
                        mat_AlFrame,
                        "AlSpacer");

 //   G4VPhysicalVolume* phys_AlSpacer_11 =
    new G4PVPlacement(0,
                     AlSpacer_11_Position,
                     logical_AlSpacer,
                     "AlSpacer",
                     logical_Xe,
                     false,
                     0,
                     checkOverlaps);

   // G4VPhysicalVolume* phys_AlSpacer_12 =
    new G4PVPlacement(0,
                     AlSpacer_12_Position,
                     logical_AlSpacer,
                     "AlSpacer",
                     logical_Xe,
                     false,
                     0,
                     checkOverlaps);

  //  G4VPhysicalVolume* phys_AlSpacer_21 =
    new G4PVPlacement(0,
                     AlSpacer_21_Position,
                     logical_AlSpacer,
                     "AlSpacer",
                     logical_Xe,
                     false,
                     0,
                     checkOverlaps);

  //  G4VPhysicalVolume* phys_AlSpacer_22 =
    new G4PVPlacement(0,
                     AlSpacer_22_Position,
                     logical_AlSpacer,
                     "AlSpacer",
                     logical_Xe,
                     false,
                     0,
                     checkOverlaps);
   
    logical_AlSpacer->SetVisAttributes(visAttPMT);
    
//
// SiPM Board
// 
     G4LogicalVolume* logical_SiPM_Board = 
    new G4LogicalVolume(solidSiPM_Board,
                        mat_AlFrame,
                        "SiPM_Board");

   // G4VPhysicalVolume* phys_SiPM_Board =
    new G4PVPlacement(0,
                     SiPM_Board_Position,
                     logical_SiPM_Board,
                     "SiPM_Board",
                     logical_Xe,
                     false,
                     0,
                     checkOverlaps);

    
//
// Teflon Board Holder
//
    G4LogicalVolume* logical_Teflon = 
    new G4LogicalVolume(solidBoard_holder_step_final,
			mat_Teflon,
			"Teflon_Holder");
			
	//G4VPhysicalVolume* phys_Teflon = 
	new G4PVPlacement(0,
			Teflonholder_Position,
			logical_Teflon,
			"Teflon_Holder",
			logical_Xe,
			false,
			0,
			checkOverlaps);
			
       /*
    G4Sphere* TestSphere =
    new G4Sphere("TestSphere",//name
                 0*cm, //Rmin
                 0.1*cm, //Rmax
                 0*deg, //pSPhi
                 360*deg, //pDPhi
                 0*deg, //pSTheta
                 180*deg); //pDTheta
		 
	  G4LogicalVolume* logical_TestSphere =
    new G4LogicalVolume(TestSphere, //solid volume
			mat_Cu,
			"Test_Sphere");
    
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,-3.75*cm),       //at (0,0,0)
                      logical_TestSphere,            //its logical volume
                      "Test_Sphere",               //its name
                      logical_Xe,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      false);        //overlaps checking
 */
    
// ---------------------------------------------------- SURFACES & PROPERTIES ----------------------------------------------------
    
// Define Copper-LXe Surface
    
    G4OpticalSurface* optSurface_Cu_LXe = new G4OpticalSurface("optSurface_Cu_LXe");

    optSurface_Cu_LXe->SetType(dielectric_metal);
    optSurface_Cu_LXe->SetFinish(polished); //alternative Option: ground
    optSurface_Cu_LXe->SetModel(glisur); // alternative Option:  glisur
    
    //G4LogicalBorderSurface logSur_LXe_Cu =
    new G4LogicalBorderSurface("optSurface_Cu_LXe",
                               phys_Xe,
                               phys_CuCylinder,
                               optSurface_Cu_LXe);
			       
// Properties of Cu surfaces
    G4double refl = Control_Instance->getCuReflectivity();
    
    G4double pp[2] = {1.0*eV, 30*eV};
    const G4int num = sizeof(pp)/sizeof(G4double);
    G4double reflectivity[2] = {refl, refl};
    assert(sizeof(reflectivity) == sizeof(pp));
    G4double efficiency[2] = {0.0, 0.0};
    assert(sizeof(efficiency) == sizeof(pp));
    
    G4MaterialPropertiesTable* optSurface_Cu_LXe_Properties =
    new G4MaterialPropertiesTable();
    
    optSurface_Cu_LXe_Properties->AddProperty("REFLECTIVITY",pp,reflectivity,num);
    optSurface_Cu_LXe_Properties->AddProperty("EFFICIENCY",pp,efficiency,num);
    
    
    
// Define Aluminum-LXe-Surface

	G4OpticalSurface* optSurface_Al_LXe = new G4OpticalSurface("optSurface_Al_LXe");
	
	 optSurface_Al_LXe->SetType(dielectric_metal);
	 optSurface_Al_LXe->SetFinish(polished);
	 optSurface_Al_LXe->SetModel(glisur);
	 
	 new G4LogicalBorderSurface("optSurface_Al_LXe",
				phys_Xe,
				phys_Am_holder,
				optSurface_Al_LXe);
				
// Properties of Al surfaces
    G4double AlRefl = Control_Instance->getAlReflectivity();
    
    G4double AlReflectivity[2] = {AlRefl, AlRefl};
    assert(sizeof(AlReflectivity) == sizeof(pp));
    G4double AlEfficiency[2] = {0.0, 0.0};
    assert(sizeof(AlEfficiency) == sizeof(pp));
    
    G4MaterialPropertiesTable* optSurface_Al_LXe_Properties = 
    new G4MaterialPropertiesTable();
    
    optSurface_Al_LXe_Properties->AddProperty("REFLECTIVITY",pp,AlReflectivity,num);
    optSurface_Al_LXe_Properties->AddProperty("EFFICIENCY",pp,AlEfficiency,num);
  
// Define LXe-PMT Surface
    
    G4OpticalSurface* optSurface_LXe_PMT = new G4OpticalSurface("optSurface_LXe_PMT");
    
    optSurface_LXe_PMT->SetType(dielectric_metal);
    optSurface_LXe_PMT->SetFinish(polished);
    optSurface_LXe_PMT->SetModel(glisur);
    
    new G4LogicalBorderSurface("optSurface_LXe_PMT",
                             phys_Xe,
                             phys_PMT,
                             optSurface_LXe_PMT);
    
// Define LXe-Silicon Surface
    
    G4OpticalSurface* optSurface_LXe_SiO_2 = new G4OpticalSurface("optSurface_LXe_SiO_2");
    
    optSurface_LXe_SiO_2->SetType(dielectric_dielectric);
    optSurface_LXe_SiO_2->SetFinish(groundfrontpainted);
    optSurface_LXe_SiO_2->SetModel(unified);
    
    new G4LogicalBorderSurface("optSurface_LXe_SiO_2",
                               phys_Xe,
                               phys_SiPM_Frame,
                               optSurface_LXe_SiO_2);
    
// Properties of Silicon surface
    G4double pp2[2] = {1.0*eV, 30*eV};
    G4double reflectivity2[2] = {0.0,0.0};
    G4double efficiency2[2] = {0.0,0.0};
    G4int num2 = sizeof(pp2)/sizeof(G4double);
    
    G4MaterialPropertiesTable* optSurface_LXe_SiO_2_Properties =
    new G4MaterialPropertiesTable();
    
    optSurface_LXe_SiO_2_Properties->AddProperty("REFLECTIVITY",pp2,reflectivity2,num2);
    optSurface_Cu_LXe_Properties->AddProperty("EFFICIENCY",pp2,efficiency2,num2);
    /*
// Define LXe-Teflon Surface
G4OpticalSurface* optSurface_Xe_Teflon = new G4OpticalSurface("optSurface_Xe_Teflon");

G4LogicalBorderSurface* Surface = new
  G4LogicalBorderSurface("optSurface_Xe_Teflon ",phys_Xe, phys_Teflon, optSurface_Xe_Teflon );

G4double sigma_alpha = 0.1;

optSurface_Xe_Teflon -> SetType(dielectric_dielectric);
optSurface_Xe_Teflon -> SetModel(unified);
optSurface_Xe_Teflon -> SetFinish(groundbackpainted);
optSurface_Xe_Teflon -> SetSigmaAlpha(sigma_alpha);

// Properties of Teflon
const G4int NUM_T = 2;

G4double ppT[NUM_T] = {2.038*eV, 4.144*eV};
G4double specularlobe[NUM_T] = {0.3, 0.3};
G4double specularspike[NUM_T] = {0.2, 0.2};
G4double backscatter[NUM_T] = {0.1, 0.1};
G4double rindex_T[NUM_T] = {1.35, 1.40};
G4double reflectivity_T[NUM_T] = {0.3, 0.5};
G4double efficiency_T[NUM_T] = {0.8, 0.1};

G4MaterialPropertiesTable* Teflon_MPT = new G4MaterialPropertiesTable();

Teflon_MPT -> AddProperty("RINDEX",ppT,rindex_T,NUM_T);
Teflon_MPT  -> AddProperty("SPECULARLOBECONSTANT",ppT,specularlobe,NUM_T);
Teflon_MPT  -> AddProperty("SPECULARSPIKECONSTANT",ppT,specularspike,NUM_T);
Teflon_MPT  -> AddProperty("BACKSCATTERCONSTANT",ppT,backscatter,NUM_T);
Teflon_MPT  -> AddProperty("REFLECTIVITY",ppT,reflectivity_T,NUM_T);
Teflon_MPT  -> AddProperty("EFFICIENCY",ppT,efficiency_T,NUM_T);

optSurface_Xe_Teflon  -> SetMaterialPropertiesTable(Teflon_MPT );

*/

    
// Assign to Surface
    optSurface_Cu_LXe->SetMaterialPropertiesTable(optSurface_Cu_LXe_Properties);
    optSurface_Al_LXe->SetMaterialPropertiesTable(optSurface_Al_LXe_Properties);
    optSurface_LXe_SiO_2->SetMaterialPropertiesTable(optSurface_LXe_SiO_2_Properties);
    optSurface_LXe_PMT->SetMaterialPropertiesTable(optSurface_Al_LXe_Properties);
    
    G4cout << "-----------------------Surface Property Tables-----------------------" << G4endl;
    optSurface_Cu_LXe_Properties-> DumpTable();
    optSurface_Al_LXe_Properties->DumpTable();
    optSurface_LXe_SiO_2_Properties->DumpTable();
    G4cout << "-----------------------End of Surface Property Tables-----------------------" << G4endl;
    
return physWorld; //always return the physical World
}

G4ThreeVector LXeDetectorConstruction::Add(G4ThreeVector vec1, G4ThreeVector vec2){ 
	// Needed to rewrite add-method since the one provided by G4ThreeVector wasn't working
	G4double x = vec1.getX() + vec2.getX();
	G4double y = vec1.getY() + vec2.getY();
	G4double z = vec1.getZ() + vec2.getZ();
	G4ThreeVector vector = G4ThreeVector(x,y,z);
	return vector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



