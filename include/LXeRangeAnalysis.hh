/// \file LXeRangeAnalysis.hh
/// \brief Definition of the LXeRangeAnalysis class

#ifndef LXeRangeAnalysis_h
#define LXeRangeAnalysis_h 1

#include "LXeRunControl.hh"
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

/// Range Analysis class
/// 
using namespace std;

class LXeRangeAnalysis 
{
  public:
	static LXeRangeAnalysis* GetInstance(){// Returns SINGLETON of LXeAnalysis
								// i.e. it only exists once
		if (LXeRangeAnalysis::fInstance == NULL) {
			LXeRangeAnalysis::fInstance = new LXeRangeAnalysis();
			}
		return fInstance;
	}
	virtual ~LXeRangeAnalysis();

	void PrepareNewRun(const G4Run* run);
	void EndOfRunAction(const G4Run* run);
	void PreUserTrackingAction(const G4Track* track);
	void PostUserTrackingAction(const G4Track* track);
	void SteppingAction(const G4Step* step);


private:
	LXeRangeAnalysis(); //Constructor	
	static LXeRangeAnalysis* fInstance;
	
	//char fileName[1024];
	string fileName;
	string nakedFileName;
	string path;
	ofstream o;
	G4double totalTrackLength;
	G4int stepCounter;
	G4double MeanTrackLength;
	G4double TrackCounter;
};
#endif