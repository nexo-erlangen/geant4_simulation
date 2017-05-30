/// \file LXeRunControl.cc
/// \brief Implementation of the LXeRunControl class

#include "LXeRunControl.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeRunControl * LXeRunControl::fInstance =0;

LXeRunControl::LXeRunControl()
{	
	fileName = "default.txt";
	nakedFileName = "default.txt";
	path = "/home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/";  
	useGas = true;
	cutValue = 0.001;
	SinglePhaseBoolean = true;
	NEST_Factor = 1.0;
	particleType = "alpha";
	particleEnergy = 4.5; //MeV
	UseCmdLineTrackingOutput = false;
	YieldFactor = 1.0; // 1.0 means full Yield, NO reduction of yield in G4S1Light.cc
	Trackgammas = false;
	CuReflectivity = 0.0;
	AlReflectivity = 0.0;
	Pressure = 1.0; // measured in atm or bar respectively
	CreateScatterPlot = false; // don't create Scatter Plot in Analysis unless set explicitely 
	CreateSiPMHisto = false; // analogous 
	CreatePMTHisto = false; // analogous
	UseRunSequence = false; // Use function getSequence in Analysis
	//SiPM_xPos = 2.655; // Calculated according to measurements from (09.06.16)
	SiPM_xPos = 2.05; // Calculated according to measurements by Tobi (Sep 2016)
	displayEvtRes=false;
	UseAlphaSource = true; //Uses the actual alpha source containing Pu239, Am241 and Cm244
	enableOptics = true;
	PMT_Efficiency  = 1.0;
	SiPM_Efficiency  = 1.0;
	AnalyseRange = false;
	fCherenkov = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
	
LXeRunControl::~LXeRunControl(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4long LXeRunControl::getSeed(){
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	G4long seed = ((now->tm_hour)*(now->tm_min)*(now->tm_sec))*now->tm_mday;
	G4cout << "getSeed() : " << seed << G4endl;
	return seed;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeRunControl::createFileName(){
	 time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	G4int NUM_timeArrayEntries = 5;
	G4int *timeArray;
	timeArray = new G4int[NUM_timeArrayEntries];
	timeArray[0] = now->tm_year + 1900;
	timeArray[1] = now->tm_mon +1;
	timeArray[2] = now->tm_mday;
	timeArray[3] = now->tm_hour;
	timeArray[4] = now->tm_min;
	
	stringstream ss;
	ss << "RawData_";
	for(int i=0; i<NUM_timeArrayEntries-1; i++){
		if(timeArray[i]<10){
			ss << "0" << timeArray[i] << "-";
		}else{
			ss << timeArray[i] <<"-";
		}
	}
	ss << timeArray[NUM_timeArrayEntries-1] << ".txt";
	fileName = ss.str();
	
	// For Naked File Name:
	
	stringstream ss2;
	for(int i=0; i<NUM_timeArrayEntries-1; i++){
		if(timeArray[i]<10){
			ss2 << "0" << timeArray[i] << "-";
		}else{
			ss2 << timeArray[i] <<"-";
		}
	}
	ss2 << timeArray[NUM_timeArrayEntries-1];
	nakedFileName = ss2.str();
	
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void LXeRunControl::setFileName(string name){
	
	string raw = "RawData_";
	string txt = ".txt";
	fileName = raw+name+txt;
	nakedFileName = name;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeRunControl::getSequence(const G4Run* aRun){
	int ID = aRun->GetRunID();
	G4cout << "Sequence Manager for Run ID " << ID << " has been invoked..." << G4endl;
	
	double ALreflectivity = (double)ID/10;
	if(ID<11) setAlReflectivity(ALreflectivity);// No refl higher 1.0 allowed!
	
	char filename[1024];
	sprintf(filename, "%s%d", "AlReflectivity_",ID);
	setFileName(filename);
}
