/// \file LXeScriptWriter.hh
/// \brief Definition of the LXeScriptWriter class

#ifndef LXeScriptWriter_h
#define LXeScriptWriter_h 1

#include "LXeRunControl.hh"
#include "LXeAnalysis.hh"
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

/// ScriptWriter class
/// 
using namespace std;

class LXeScriptWriter 
{
  public:
	LXeScriptWriter();
  
	~LXeScriptWriter();
	
	void GNUPLOT_Histo_SiPMHit();
	void GNUPLOT_Histo_PMTHit();
	void GNUPLOT_Scatterplot_SiPM_vs_PMT();
	
	
  private:
	LXeRunControl* Control_Instance;
	LXeAnalysis* Analysis;
	ofstream script_Histo_SiPMHit;
	ofstream script_Histo_PMTHit;
	ofstream script_Scatterplot_SiPMvsPMT;
	string path;
	string txt;
	G4bool useGas;
	string medium;
	string RawData_FileName;
	string RawData_NakedFileName;
	string Histo_SiPMHit_FileName;
	string Histo_PMTHit_FileName;
	string Plot_FileName;
	G4int NUM_Events;
	string particleType;
	G4double particleEnergy;
	G4double Pressure;
	G4bool CreateScatterPlot;
	G4bool CreateSiPMHisto;
	G4bool CreatePMTHisto;
	G4double alRefl;
	G4double cuRefl;
	string Scatterplot_FileName;
  };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif