/// \file LXeAnalysis.hh
/// \brief Definition of the LXeAnalysis class

#ifndef LXeAnalysis_h
#define LXeAnalysis_h 1

#include "LXeRunControl.hh"
#include "LXeRangeAnalysis.hh"
#include "LXeMessenger.hh"

#include "globals.hh"
#include "G4Track.hh"
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"

#include <string>
#include <iostream>
#include <fstream>

/// Analysis class
/// 
using namespace std;

class LXeAnalysis 
{
  public:
	static LXeAnalysis* GetInstance(){// Returns SINGLETON of LXeAnalysis
								// i.e. it only exists once
		if (LXeAnalysis::fInstance == NULL) {
			LXeAnalysis::fInstance = new LXeAnalysis();
			}
		return fInstance;
	}
	virtual ~LXeAnalysis();
	
	G4int getTotalNUMEvents(){return total_NUM_events;};
	G4int getLargestNUM_photonsPerEvent(){return largestNUM_photonsPerEvent;};
	G4int getLargestNUM_PhotonsOnSiPMPerEvent(){return largestNUM_PhotonsOnSiPMPerEvent;};
	G4int getLargestNUM_PhotonsOnPMTPerEvent(){return largestNUM_PhotonsOnPMTPerEvent;};
	G4int getNUM_GammasPerRun(){return NUM_gammasPerRun;};
	
	void PrepareNewRun(const G4Run* run);
	void EndOfRunAction(const G4Run* run);

	void PrepareNewEvent(const G4Event* event);
	void EndOfEventAction(const G4Event* event);
	
	void PreUserTrackingAction(const G4Track* track);
	void PostUserTrackingAction(const G4Track* track);
	
	void SteppingAction(const G4Step* step);
		
  private:
	LXeAnalysis(); // Private Constructor
  
	static LXeAnalysis * fInstance;
	const G4Track* alphaTrack;
  
	G4int NUM_photonsPerEvent;
	G4int largestNUM_photonsPerEvent;
	G4int largestNUM_PhotonsOnSiPMPerEvent;
	G4int largestNUM_PhotonsOnPMTPerEvent;
	G4int NUM_electronsPerEvent;
	G4int NUM_gammasPerEvent;
	G4int NUM_gammasPerRun;
	G4bool TrackGammas;
	G4int total_NUM_events;
	string Output_FileName;
	string path;
	string absolutePath;
	G4int NUM_photonsInSiPMVolume;
	G4int NUM_photonsInPMTVolume;
	G4LogicalVolume* fSiPMVolume;
	G4LogicalVolume* fPMTVolume;
	G4int storedTrackID;
	G4int NUM_Test;
	G4int NUM_Test2;
	G4bool UseRunSequence;
//	ofstream tempstream;
//	string tempPath; 	
	LXeRunControl* Control_Instance;
	LXeRangeAnalysis* Range_Instance;
	G4double pmt_efficiency;
	G4double sipm_efficiency;
	//LXeMessenger* Messenger;
	G4bool AnalyseRange;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif