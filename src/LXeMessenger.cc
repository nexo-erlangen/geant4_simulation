/// \file LXeMessenger.cc
/// \brief Implementation of the LXeMessenger class

#include "LXeMessenger.hh"
#include "LXeRunControl.hh"
#include "LXeAnalysis.hh"
#include "globals.hh"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
extern ofstream data;
extern string VERSION;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeMessenger::LXeMessenger(){
	Control_Instance =  LXeRunControl::GetInstance();
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeMessenger::~LXeMessenger(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeMessenger::PrintMainArgError(){
	//G4cout << "An error occured! " << G4endl;
	G4cout 	<< "**************************************************************************" << G4endl;
	G4cout 	<< "ERROR!" << "\n" << "One of the entered agruments is not defined or parameter is missing!" << G4endl; 
	G4cout 	<< "**************************************************************************" << G4endl;
	G4cout 	<< "Find all possible options below." << "\n"
			<< "Only one of the arguments for each option is needed." << G4endl;
	G4cout 	<< "**************************************************************************" << G4endl;
	G4cout 	<< "Option		||	Argument(s)	||	Paramters 	" << "\n"
			<< "--------------------------------------------------------------------------" << "\n"
			<< "Use Liquid	|| -l -L -liquid -Liquid|| 	none		" << "\n"
			<< "Use Gas		|| -g -G -gas -Gas	|| 	none		" << "\n" 
			<< "Set Cuts	|| -cut -cuts -SetCuts	|| 	double [mm]	" << "\n" 
			<< "Single Phase	|| -singlePhase		|| 	none		" << "\n" 
			<< "No Single Phase	|| -nosinglephase	|| 	none		" << "\n" 
			<< "NEST Factor	|| -NEST -nest		|| 	0.0<=double<=1.0	" << "\n" 
			<< "Set output path	|| -path -PATH		|| 	path/	" << "\n" 
			<< "Set file name	|| -data -DATA		|| 	FileName	" << "\n" 
			<< "Particle Type	|| -gamma -alpha -e	|| 	none		" << "\n" 
			<< "Set Energy	|| -energy -setEnergy	|| 	0<double<5.5		" << "\n" 
			<< "Num of Events	|| -numevents		||	0<int<=25000	" << "\n"
			<< "TrackingOutput	|| -tracking		|| 	none	" << "\n" 
			<< "Scint Yield	|| -scintYield		|| 	0.0<double<=1.0	" << "\n" 
			<< "Gamma Tracking	|| -trackGammas		||	none	" << "\n"
			<< "Cu Reflectivity	|| -reflectivity 	||	0.0<=double<=1.0	"<< "\n"
			<< "Al Reflectivity	|| -alrefl		|| 	0.0<=double<=1.0 " << "\n"
			<< "Gas Pressure	|| -pressure 		|| 	0.0< double 	" << "\n"
			<< "Histo/Scatter	|| -SiPMHisto, PMTHisto, -Scatter	" << "\n"
			<< "SiPM x_Pos	|| -SiPM_xPos 		|| 	0<double<=3.0	" << "\n"
			<< "Event Results 	|| -eventResults	|| 	none	" << "\n"
			<< "Other Source	|| -otherSource		||	none 	" << "\n"
			<< "Disable Optics	|| -disableOptics	||	none	" << "\n"
			<< "**************************************************************************" << "\n"
			<< "Please note that all control parameters start with '-' sign!" << "\n"	
			<< "Example: './Simulation -path ~/PathToFile/ -data TestFile -gas -scintYield 1.0' " << "\n"
			<< "Good Luck :)" << "\n"
			<< G4endl;
}
void LXeMessenger::CreateHeader(){
	data	<< "# Output: " << Control_Instance->getPath() << Control_Instance->getFileName() << "\n"
		<< "# Particle Type: " << Control_Instance->getParticleType() << endl;
	if(Control_Instance->getUseAlphaSource()){
	data << "# Alpha Source is used with Pu239 (4.15 MeV), Am241 (4.48 MeV) and Cm244 (4.8 MeV)." << endl;
	}else{
	data << " #Particle Energy: " << Control_Instance->getParticleEnergy() << " MeV" << endl;
	}
	data	<< "# Cut Value: " << Control_Instance->getCutValue() << " mm "<< "\n"
		<< "# NEST_Factor: " << Control_Instance->getNEST_Factor() << "\n"
		<< "# Scintillation Yield: " << Control_Instance->getScintYield() << "\n"
		<< "# Copper Reflectivity: " << Control_Instance->getCuReflectivity() << " Aluminum Reflectivity: " << Control_Instance->getAlReflectivity() <<"\n"
		<< "# Pressure in Gas (if gas was used): " << Control_Instance-> getPressure()
		<< G4endl;
	if(Control_Instance->UseGasInsteadOfLiquid()){
		data << "# Detectormedium: GASEOUS Xenon" << G4endl;
	}else{
		data << "# Detectormedium: LIQUID Xenon" << G4endl;
	}
	data	<< "# SiPM x-Position :" << Control_Instance->getSiPM_xPos() << "\n"
		<< "#SiPM_Efficiency = " << Control_Instance->getSiPM_Efficiency() << " - "
		<< " PMT_Efficiency = " << Control_Instance->getPMT_Efficiency()  << "\n"
		<< "# Photons || Electrons || SiPM Hits || PMT Hits || particleEnergy "<< "\n" << G4endl;
}
void LXeMessenger::CreateFooter(){
	LXeAnalysis* Analysis = LXeAnalysis::GetInstance();
	data	<< "# Total number of processed events: " << Analysis->getTotalNUMEvents() << "\n"
		<< "# Largest number of photons on SiPM per event: " << Analysis->getLargestNUM_PhotonsOnSiPMPerEvent() << "\n"
		<< "# Largest number of photons on PMT per event: " << Analysis->getLargestNUM_PhotonsOnPMTPerEvent() << "\n"
		<< "# Largest number of photons produced per event: " << Analysis->getLargestNUM_photonsPerEvent() << "\n"
		<< G4endl;
	if(Control_Instance->TrackGammas()){
		data << "# NUM Gammas per Run: " << Analysis->getNUM_GammasPerRun() << G4endl;
	}
	data << "# Thank you for using " << VERSION << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......





