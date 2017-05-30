#include "LXeDetectorConstruction.hh"
#include "LXeActionInitialization.hh"	
#include "LXePhysicsList.hh"	
#include "LXeRunControl.hh"
#include "LXeMessenger.hh"

#include "G4RunManager.hh"	
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//#include "G4Scintillation.hh"
#include "G4UnitsTable.hh" 	
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#undef G4VIS_USE
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#undef G4UI_USE
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;
ofstream data;	//extern ofstream -> Used in Messenger and Analysis 
extern const string VERSION = "Simulation - Version 7.3";

int main(int argc,char** argv)
{
	LXeRunControl* Control_Instance = LXeRunControl::GetInstance();
	
	G4cout << "Programme start: " << argv[0] << G4endl;
	G4int NUM_args = argc-1;
	
	// LXeRunControl manages default values in its constructor
	G4bool useGas = Control_Instance->UseGasInsteadOfLiquid();
	string material = "GASEOUS(default)";
	string singlePhase_String = " ";
	G4double cutValue = Control_Instance->getCutValue();
	G4bool singlePhase = Control_Instance->getSinglePhaseBoolean();
	G4long myseed = Control_Instance->getSeed();
	if(singlePhase){singlePhase_String = "ON! - NO";}else{singlePhase_String = "OFF!";}
	G4double NEST_Factor = Control_Instance->getNEST_Factor();
	Control_Instance->createFileName();
	string DATA_output = Control_Instance->getFileName();
	string PATH = Control_Instance->getPath();
	string particleType = Control_Instance->getParticleType();
	G4double particleEnergy = Control_Instance->getParticleEnergy(); // MeV
	G4bool UseCmdLineTrackingOutput = Control_Instance->getTrackingOutputBoolean();
	G4double YieldFactor = Control_Instance->getScintYield(); 	
	G4bool TrackGammas = Control_Instance->TrackGammas();
	string TrackGammas_String = "FALSE"; //default
	G4double CuReflectivity = Control_Instance->getCuReflectivity();
	G4double AlReflectivity = Control_Instance->getAlReflectivity();
	G4double Pressure = Control_Instance->getPressure();
	G4bool CreateScatterPlot = Control_Instance->createScatterPlot();//returns bool
	G4bool CreateSiPMHisto = Control_Instance->createSiPMHisto();//returns bool
	G4bool CreatePMTHisto = Control_Instance->createPMTHisto();//returns bool
	G4bool UseRunSequence = Control_Instance->getUseRunSequence();//returns bool
	G4double SiPM_xPos = Control_Instance->getSiPM_xPos();
	G4bool displayEventResults = Control_Instance->displayEventResults();
	G4int NUM_Events = 10;
	G4bool isErrorThrown = false;
	G4bool UseAlphaSource = Control_Instance->getUseAlphaSource();
	G4bool enableOptics = Control_Instance->getOpticsEnabled();
	G4double PMT_Efficiency = Control_Instance->getPMT_Efficiency();
	G4double SiPM_Efficiency = Control_Instance->getSiPM_Efficiency();
	G4bool AnalyseRange = Control_Instance->getAnalyseRange();
	G4bool fCherenkov = Control_Instance->getCherenkov();
	
	G4cout << "--------------------------------------------------------------------------------------------------------------------------" << G4endl;
	if(argc ==1){
		G4cout << "Number of passed arguments: " << NUM_args << G4endl;
		G4cout << "Default mode - No arguments were passed to main(). Continue..." << G4endl; //Using the default values defined above
	}else{
		G4cout << "Number of passed arguments: " << NUM_args << G4endl;
		G4cout << "Interactive mode using arguments" << G4endl;
		G4int ct =0;
		for(int i = 1; i<argc; i++){
			string tempstring = argv[i];
			if(tempstring == "-l" ||  tempstring == "-L" || tempstring == "-liquid" || tempstring == "-Liquid"){
				Control_Instance->setUseGasBoolean(false);
				useGas = Control_Instance->UseGasInsteadOfLiquid();
				material = "LIQUID";
				ct++;
			}
			else if(tempstring == "-g" ||  tempstring == "-G" || tempstring == "-gas" 
				|| tempstring == "-Gas" || tempstring == "-gaseous" || tempstring == "-Gaseous"){
				Control_Instance->setUseGasBoolean(true);
				useGas = Control_Instance->UseGasInsteadOfLiquid();
				material = "GASEOUS";
				ct++;	
			}
			else if(tempstring == "-SetCuts" || tempstring == "-cutValue" || tempstring == "-cutvalue" || tempstring ==  "-cuts"|| tempstring == "-Cuts" 
				|| tempstring ==  "-cut"|| tempstring == "-Cut"){
				if(argv[i+1]!= NULL){
					G4double tempvalue = atof(argv[i+1]);
					 // atof() converts char to float
					if(tempvalue !=0){ // atof() returns 0, if entered value is not an int or double
						Control_Instance->setCutValue(tempvalue);
						cutValue = Control_Instance->getCutValue();
						ct+=2;
					}else{
						G4cout << "Cut value is missing or is not of correct type (double or int)!" << G4endl;
						}
				}else{
					G4cout << "Cut value missing!" << G4endl;
					}
			}
			else if(tempstring == "-singlePhase" || tempstring == "-singlephase" || tempstring == "-SinglePhase" || tempstring == "-Singlephase"
				|| tempstring == "-sp" || tempstring == "-single" || tempstring == "-Single"){
				Control_Instance->setSinglePhaseBoolean(true);
				singlePhase = Control_Instance->getSinglePhaseBoolean();
				singlePhase_String = "ON! - NO";	
				ct++;
			}
			else if(tempstring == "-nosinglephase" || tempstring == "-noSinglePhase" || tempstring == "-nosinglePhase" || tempstring == "-noSinglephase"
				|| tempstring == "-Nosinglephase" || tempstring == "-NoSinglePhase" || tempstring == "-NosinglePhase" || tempstring == "-NoSinglephase"){
				Control_Instance->setSinglePhaseBoolean(false);
				singlePhase = Control_Instance->getSinglePhaseBoolean();
				singlePhase_String = "OFF! -";
				ct++;
			}
			else if(tempstring == "-NestFactor" || tempstring == "-nestfactor" || tempstring == "-Nestfactor" || tempstring == "-nestFactor" || 
				tempstring == "-NEST_Factor" || tempstring == "-NEST_factor" || tempstring == "-nest" || tempstring == "-NEST" ||  tempstring == "-Nest"){
					if(argv[i+1]!= NULL){
						G4double tempvalue = atof(argv[i+1]);
						if(tempvalue <0 || tempvalue >1.0){
							G4cout << "Invalid Factor for NEST! Value must be type double between 0.0 and 1.0!" << G4endl;	
							
						}
						if(tempvalue ==0){
							Control_Instance->setNEST_Factor(tempvalue);
							NEST_Factor = Control_Instance->getNEST_Factor();
							G4cout << "WARNING: NEST Factor is set to zero! Check if intended!" << G4endl;
							ct+=2;
						}
						else{
							Control_Instance->setNEST_Factor(tempvalue);
							NEST_Factor = Control_Instance->getNEST_Factor();
							G4cout << "NEST Factor is set to " << NEST_Factor << G4endl;
							ct+=2;							
						}
					}
					else{
					G4cout << "NEST Factor missing! Default value " << NEST_Factor << " will be used! " << G4endl;
					ct+=1;
					}
			}
			else if(tempstring == "-data" || tempstring == "-Data" || tempstring == "-DATA" || tempstring == "-output" || tempstring == "-Output" || tempstring == "-DATA_output" 
				|| tempstring == "fileName" || tempstring == "filename" || tempstring == "FileName" || tempstring == "FileName"){
				if(argv[i+1]!=NULL){
					string newTempstring = argv[i+1];
					Control_Instance->setFileName(newTempstring);
					DATA_output = Control_Instance->getFileName();
					ct+=2;
				}else{
					G4cout << "No outputfile entered! Data will be written to default location!" << G4endl;
					G4cout << "In this case: " << DATA_output << G4endl;
					ct+=1;
				}
			}
			else if(tempstring == "-path" || tempstring == "-Path" || tempstring == "-PATH" ) {
				if(argv[i+1]!=NULL){
					string newTempstring = argv[i+1];
					Control_Instance->setPath(newTempstring);
					PATH = Control_Instance->getPath();
					ct+=2;
				}else{
					G4cout << "No path entered! Data will be written to default location!" << G4endl;
					G4cout << "In this case: " << PATH << G4endl;
					ct+=1;
				}
			}
			else if(tempstring == "-alpha" || tempstring == "-a" || tempstring == "-alphaparticle" || tempstring == "-alphaParticle" 
				|| tempstring == "-Alphaparticle" || tempstring == "-AlphaParticle"){
					Control_Instance->setParticleType("alpha");
					particleType = Control_Instance->getParticleType();
					ct++;
			}
			else if (tempstring == "-e" || tempstring == "-e-" || tempstring == "-electron" || tempstring == "-Elelctron"){
					Control_Instance->setParticleType("e-");
					particleType = Control_Instance->getParticleType();
				ct++;
			}
			else if (tempstring == "-gamma" || tempstring == "-Gamma"){
					Control_Instance->setParticleType("gamma");
					particleType = Control_Instance->getParticleType();
				ct++;
			}
			else if (tempstring == "-setEnergy" || tempstring == "-energy" || tempstring == "-setenergy" || tempstring == "-Energy"  ){
				if(argv[i+1]!=NULL){
					G4double tempvalue = atof(argv[i+1]);
					if (tempvalue<= 0)
					{
						G4cout << "No valid energy value entered! 0 < E < 5.5 MeV" << G4endl;
					}else if( tempvalue >= 5.5){
						G4cout << "Energy too high! Must be smaller than 5.5 MeV!" << G4endl;
					}else{
					Control_Instance->setParticleEnergy(tempvalue);
					particleEnergy = Control_Instance->getParticleEnergy();
					ct+=2;
					}
				}
				else{
				G4cout << "Energy value missing! Default value " << particleEnergy << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-tracking" || tempstring == "-Tracking" || tempstring == "-track" ){
				Control_Instance->setCmdLineTrackingOutput(true);
				UseCmdLineTrackingOutput = Control_Instance->getTrackingOutputBoolean();
				ct++;
			}
			else if(tempstring == "-Yield" || tempstring == "-yield" || tempstring == "-yieldFactor" || tempstring == "-YieldFactor" ||  tempstring == "-yieldfactor" ||
				tempstring == "-Yieldfactor" || tempstring == "-scintillationyield" || tempstring == "-scintillationYield" || tempstring == "-ScintillationYield" ||  tempstring == "-Scintillationyield" ||
				tempstring == "-scintYield" || tempstring == "-scintyield" || tempstring == "-Scintyield" || tempstring == "-ScintYield"){
				if(argv[i+1]!= NULL){
						G4double tempvalue = atof(argv[i+1]);
						if(tempvalue <0 || tempvalue >1.0){
							G4cout << "Invalid Scintillation Yield Factor! Value must be type double between 0.0 (excluded) and 1.0 (included)!" << G4endl;
						}
						else if(tempvalue ==0){
							G4cout << "Error: Scintillation Yield Factor was set to zero! Check entered value!" << "\n"
							<<  "Value must be type double between 0.0 (excluded) and 1.0 (included)!" << G4endl;
						}
						else{
							Control_Instance->setScintYield(tempvalue);
							YieldFactor = Control_Instance->getScintYield();
							ct+=2;							
						}
				}
				else{
				G4cout << "Yield Factor missing! Default value " << YieldFactor << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-trackGammas" || tempstring == "-Trackgammas" || tempstring == "-TrackGammas" || tempstring == "-trackgammas"){
				Control_Instance->setTrackGammas(true);
				TrackGammas = Control_Instance->TrackGammas();
				ct++;
			}
			else if(tempstring == "-reflectivity" || tempstring == "-Reflectivity" || tempstring == "-refl"){
				if(argv[i+1]!= NULL){
						G4double tempvalue = atof(argv[i+1]);
						if(tempvalue <0 || tempvalue >1.0){
							G4cout << "Invalid Reflectivity Factor! Value must be type double between 0.0 and 1.0 (both included)!" << G4endl;
						}
						else{
							Control_Instance->setCuReflectivity(tempvalue);
							CuReflectivity = Control_Instance->getCuReflectivity();
							ct+=2;
													
						}
				}
				else{
				G4cout << "Reflectivity Factor missing! Default value " << CuReflectivity << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-Alreflectivity" || tempstring == "-AluminumReflectivity" || tempstring == "-AlRefl" || tempstring == "-alrefl"){
				if(argv[i+1]!= NULL){
						G4double tempvalue = atof(argv[i+1]);
						if(tempvalue <0 || tempvalue >1.0){
							G4cout << "Invalid Aluminum Reflectivity Factor! Value must be type double between 0.0 and 1.0 (both included)!" << G4endl;
						}
						else{
							Control_Instance->setAlReflectivity(tempvalue);
							AlReflectivity = Control_Instance->getAlReflectivity();
							ct+=2;
													
						}
				}
				else{
				G4cout << "Reflectivity Factor missing! Default value " << AlReflectivity << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring =="-pressure" || tempstring == "-setPressure" || tempstring =="-Pressure" || tempstring == "-SetPressure"){
				if(argv[i+1]!= NULL){
						G4double tempvalue = atof(argv[i+1]);
						if(tempvalue <=0){
							G4cout << "Invalid Pressure! Value must be type double and larger that 0!" << G4endl;
						}
						else{
							Control_Instance->setPressure(tempvalue);
							Pressure = Control_Instance->getPressure();
							ct+=2;								
						}
				}
				else{
				G4cout << "Pressure missing! Default value " << Pressure << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-createScatterPlot" || tempstring == "-ScatterPlot" || tempstring == "-scatter" || tempstring == "-Scatter" || tempstring == "-scatterPlot" || tempstring == "-Scatterplot" || tempstring == "-scatterplot"){
				Control_Instance->setScatterPlot(true);
				CreateScatterPlot = Control_Instance->createScatterPlot();
				ct++;
			}
			else if(tempstring == "-SiPMHisto" || tempstring == "-sipmhisto" || tempstring == "-setSiPMHisto" ){
				Control_Instance->setSiPMHisto(true);
				CreateSiPMHisto= Control_Instance->createSiPMHisto();
				ct++;
			}
			else if(tempstring == "-PMTHisto" || tempstring == "-pmthisto" || tempstring == "-setPMTHisto" ){
				Control_Instance->setPMTHisto(true);
				CreatePMTHisto= Control_Instance->createPMTHisto();
				ct++;
			}
			else if(tempstring == "-RunSequence" || tempstring == "-runsequence" || tempstring == "-runseq" ){
				Control_Instance->setUseRunSequence(true);
				UseRunSequence = Control_Instance->getUseRunSequence();
				ct++;
			}
			else if (tempstring == "-SetSiPM_xPos" || tempstring == "-SiPM_xPos" || tempstring == "-xPos" || tempstring == "-setSiPM_xPos"  ){
				if(argv[i+1]!=NULL){
					G4double tempvalue = atof(argv[i+1]);
					if (tempvalue<= 0)
					{
						G4cout << "No valid SiPM x-Position entered! 0 < x <= 3.0*cm" << G4endl;
					}else if( tempvalue > 3.0){
						G4cout << "No valid SiPM x-Position entered! 0 < x <= 3.0*cm" << G4endl;
					}else{
					Control_Instance->setSiPM_xPos(tempvalue);
					SiPM_xPos = Control_Instance->getSiPM_xPos();
					ct+=2;
					}
				}
				else{
				G4cout << "Value for x-Position missing! Default value " << SiPM_xPos << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-eventResults" || tempstring == "-displayEventResults" || tempstring == "-eventRes" ){
				Control_Instance->setdisplayEventResults(true);
				displayEventResults = Control_Instance->displayEventResults();
				ct++;
			}
			// This only works if G4UI_USE is undefined, i.e. in batch mode
			else if(tempstring == "-numevents" || tempstring == "-NUM_Events" || tempstring == "-numEvents" ){
				if(argv[i+1]!=NULL){
					G4double tempvalue = atof(argv[i+1]);
					if (tempvalue<= 0)
					{
						G4cout << "Number of events needs to be larger zero!" << G4endl;
					}else if( tempvalue > 25000){
						G4cout << "Number of events will probably exceed maximum possible run time. Program terminates here!" << G4endl;
					}else{
						NUM_Events = tempvalue;
						G4cout << "Number of Events to be Processed per Run: " << NUM_Events << G4endl;
						ct+=2;
					}
				}
				else{
				G4cout << "No Number of events entered! Default value " << NUM_Events << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-ErrorOnPurpose"){
				isErrorThrown = true;
				ct++;
			}
			else if(tempstring == "-OtherSource" || tempstring == "-Other" || tempstring == "-otherSource" || tempstring == "-other" ){
				Control_Instance->setUseAlphaSource(false);
				UseAlphaSource = Control_Instance->getUseAlphaSource();
				ct++;
			}
			else if(tempstring == "-DisableOptics" || tempstring == "-disableOptics" || tempstring == "-noOptics" || tempstring == "-noPhotons" ){
				Control_Instance->setOpticsEnabled(false);
				enableOptics= Control_Instance->getOpticsEnabled();
				ct++;
			}
			else if(tempstring == "-pmt_efficiency" || tempstring == "-PMT_Efficiency" || tempstring == "-pmt_eff" ){
				if(argv[i+1]!=NULL){
					G4double tempvalue = atof(argv[i+1]);
					if (tempvalue<= 0)
					{
						G4cout << "PMT Efficiency too low! Must be between 0.0 (excluded) and 1.0" << G4endl;
					}else if( tempvalue > 1.0){
						G4cout << "PMT Efficiency too high! Must be between 0.0 (excluded) and 1.0" << G4endl;
					}else{
						Control_Instance->setPMT_Efficiency(tempvalue);
						PMT_Efficiency = Control_Instance->getPMT_Efficiency();
						ct+=2;
					}
				}
				else{
				G4cout << "No PMT Efficiency entered! Default value " << PMT_Efficiency << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-sipm_efficiency" || tempstring == "-SiPM_Efficiency" || tempstring == "-sipm_eff" ){
				if(argv[i+1]!=NULL){
					G4double tempvalue = atof(argv[i+1]);
					if (tempvalue<= 0)
					{
						G4cout << "SiPM Efficiency too low! Must be between 0.0 (excluded) and 1.0" << G4endl;
					}else if( tempvalue > 1.0){
						G4cout << "SiPM Efficiency too high! Must be between 0.0 (excluded) and 1.0" << G4endl;
					}else{
						Control_Instance->setSiPM_Efficiency(tempvalue);
						SiPM_Efficiency = Control_Instance->getSiPM_Efficiency();
						ct+=2;
					}
				}
				else{
				G4cout << "No SiPM Efficiency entered! Default value " << SiPM_Efficiency << " will be used! " << G4endl;
				ct+=1;
				}
			}
			else if(tempstring == "-analyseRange" || tempstring == "-analyserange" || tempstring == "-rangeAnalysis" || tempstring == "-RangeAnalysis" || tempstring == "-range" ){
				Control_Instance->SetAnalyseRange(true);
				AnalyseRange = Control_Instance->getAnalyseRange();
				ct++;
			}
			else if(tempstring == "-cherenkov" || tempstring == "-Cherenkov"){
				Control_Instance->setCherenkov(true);
				fCherenkov = Control_Instance->getCherenkov();
				ct++;
			}
			else if(tempstring == "-nocherenkov" || tempstring == "-noCherenkov" || tempstring == "-NoCherenkov" || tempstring == "-Nocherenkov"){
				Control_Instance->setCherenkov(false);
				fCherenkov = Control_Instance->getCherenkov();
				ct++;
			}
			
			
		}
		if(isErrorThrown) {
			G4cout << "Error was thrown by user on purpose. Program will be closed..." << G4endl;
			return 0;
		}
		if(ct != NUM_args){
			LXeMessenger * messenger = new LXeMessenger();
			messenger->PrintMainArgError();
			return 0;
		}
	}
	if(TrackGammas) TrackGammas_String = "TRUE";
	G4cout << "--------------------------------------------------------------------------------------------------------------------------" << G4endl;
	G4cout << "Simulation of scintillation light in " << material << " Xenon" << G4endl;
	if(UseAlphaSource) {
			G4cout 	<< "Alpha Source is used with Pu239 (4.15 MeV), Am241 (4.48 MeV) and Cm244 (4.8 MeV)." << G4endl;
	}else{
			G4cout 	<< "A different source will be used!" << "\n"
					<< "Not the actual alpha source but as follows:" << "\n"
					<< "Primary Particle: " << particleType << ". Energy: " << particleEnergy << " MeV" << G4endl;
	}
	G4cout << "Single Phase turned " << singlePhase_String << " electron propagation turned on" << G4endl;
	G4cout << "Scintillation Yield Factor is set to " << YieldFactor << G4endl;
	G4cout << "Set cut value to " << cutValue << " mm" << G4endl;
	G4cout << "Gamma Tracking Switched on: " << TrackGammas_String << G4endl;
	G4cout << "Data output: " << PATH << DATA_output << G4endl;
	G4cout << "Copper reflectivity is set to " << CuReflectivity << G4endl;
	G4cout << "Aluminum reflectivity is set to " << AlReflectivity << G4endl;
	G4cout << "In case gas is being used: Pressure = " << Pressure << " bar" << G4endl;
	G4cout << "SiPM x-Position: " << SiPM_xPos << " cm"<< G4endl;
	G4cout << "SiPM Efficiency: " << SiPM_Efficiency  << " and PMT Efficiency: " << PMT_Efficiency << G4endl;
	G4cout << "Range Analyser is switched on:  " << AnalyseRange << " (\"1\" for \"true\" and \"0\" for \"false\")" << G4endl;
	if(UseRunSequence){G4cout << "A Run Sequence Will Be Used Here! " << G4endl;}
	if(!enableOptics){G4cout << "NO PHOTON PRODUCTION!! - Optics is disabled." << endl;}
	if(!fCherenkov){G4cout << "Cherenkov effect is switched off!" << endl;}
	G4cout << "--------------------------------------------------------------------------------------------------------------------------" << G4endl;
	G4cout << "VERSION: " << VERSION << endl;
	G4cout << "--------------------------------------------------------------------------------------------------------------------------" << G4endl;

	// Pass values to RunControl 
	// Choose the Random engine

G4Random::setTheEngine(new CLHEP::RanecuEngine);
G4Random::setTheSeed(myseed);	
G4Random::showEngineStatus();
	
	// Get Run Manager
G4RunManager* runManager = new G4RunManager;
	
	
	// Detector construction
	
runManager->SetUserInitialization(new LXeDetectorConstruction(useGas));
	
	// Physics list
	
G4VModularPhysicsList* physicsList = new LXePhysicsList(cutValue, singlePhase, NEST_Factor);

physicsList->SetVerboseLevel(2);
runManager->SetUserInitialization(physicsList);
  
	// User action initialization
runManager->SetUserInitialization(new LXeActionInitialization(particleType, particleEnergy));

	// Initialize visualization
#ifdef G4VIS_USE
G4VisManager* visManager = new G4VisExecutive("all");

	// G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
	// G4VisManager* visManager = new G4VisExecutive("Quiet");
visManager->Initialize();
#endif
	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	if (UseCmdLineTrackingOutput) {UImanager->ApplyCommand("/tracking/verbose 1");}
	// Command Line tracking Output requires a lot computing power and should only be 
	// enabled if the scintillation yield is low and the event number is limited to 1! In this 
	// case ALL tracking processes are displayed in the terminal or the GUI.
	
#ifdef G4UI_USE
	G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE	  	
	UImanager->ApplyCommand("/control/execute init_vis.mac"); 

	if (ui->IsGUI()) {
	UImanager->ApplyCommand("/control/execute gui.mac");
	}
#else
	UImanager->ApplyCommand("/control/execute init.mac");
#endif    

	ui->SessionStart();
	
	delete ui; 
#else
	G4cout << "No G4UI_USE" << G4endl;
	UImanager->ApplyCommand("/control/execute MAKRO.mac"); 
	
	char command[128];
	sprintf(command, "%s%d", "/run/beamOn ", NUM_Events );
	UImanager->ApplyCommand(command);
#endif
/*	}else{ // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
	}
*/
    
#ifdef G4VIS_USE
delete visManager;
#endif
    // Job Termination - Free storage
delete runManager;
 


return 0;
}
