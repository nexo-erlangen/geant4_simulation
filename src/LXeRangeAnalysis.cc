/// \file LXeRangeAnalysis.cc
/// \brief Implementation of the LXerangeAnalysis class

#include "LXeAnalysis.hh"
#include "LXeRangeAnalysis.hh"
#include "LXeRunControl.hh"
#include "LXeMessenger.hh"
#include "G4Track.hh"
#include "LXeDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "LXeScriptWriter.hh"
#include "Randomize.hh"
#include "globals.hh"

extern string VERSION;
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeRangeAnalysis * LXeRangeAnalysis::fInstance =0;

LXeRangeAnalysis::LXeRangeAnalysis()
{	
	path = LXeRunControl::GetInstance()->getPath();
	nakedFileName =LXeRunControl::GetInstance()->getNakedFileName();
	totalTrackLength=0.0;
	stepCounter = 0;
	MeanTrackLength = 0;
	TrackCounter =0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeRangeAnalysis::~LXeRangeAnalysis()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeRangeAnalysis::PrepareNewRun(const G4Run* run){//Das muss in die event Action!
	G4int RunID = run->GetRunID();

	char num[16];
	sprintf(num, "%d", RunID);	
	string range = "Range_";
	string spacer = "_";
	string txt = ".txt";

	fileName=path+range+nakedFileName+spacer+num+txt;
	o.open(fileName.c_str());
	cout << "-------- Range Analyser 1.0 Beta --------" << endl;
	cout << "For Simulation version: " << VERSION << endl;
	o << "#-------- Range Analyser 1.0 Beta --------" << endl;
	o << "#For Simulation version: " << VERSION << endl;
	o << "#Alpha Range" << endl;
}	
	
void LXeRangeAnalysis::EndOfRunAction(const G4Run*/* run*/){
	MeanTrackLength/=TrackCounter;
	o<< "#Mean Track Length:  " << MeanTrackLength<< endl;
o.close();
}

void LXeRangeAnalysis::PreUserTrackingAction(const G4Track* track){

}

void LXeRangeAnalysis::PostUserTrackingAction(const G4Track* track){
	string name = track->GetParticleDefinition()->GetParticleName();
	if(name=="alpha"){
	
	G4double trackLength = track->GetTrackLength();
	MeanTrackLength+=trackLength;
	TrackCounter++;
	o << trackLength << endl;
	}
}

void LXeRangeAnalysis::SteppingAction(const G4Step* step){
	/*
	if(step->GetTrack()->GetParticleDefinition()->GetParticleName() != "opticalphoton"){
	o << step->GetTrack()->GetParticleDefinition()->GetParticleName() << endl;
		if(step->GetTrack()->GetParticleDefinition()->GetParticleName() == "alpha"){
			cout <<" alpha found " << endl;
			o <<" alpha found " << endl;
			stepCounter++;
			G4double stepLength = step->GetStepLength();
			totalTrackLength +=stepLength;
			o << stepCounter << "\t" << stepLength << "\t" << totalTrackLength << endl;
		}
	}
*/
}

	
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
