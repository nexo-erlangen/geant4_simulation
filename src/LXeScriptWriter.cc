/// \file LXeScriptWriter.cc
/// \brief Implementation of the LXeScriptWriter class

#include "LXeScriptWriter.hh"
#include "LXeRunControl.hh"
#include "LXeAnalysis.hh"
#include "globals.hh"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeScriptWriter::LXeScriptWriter(){
	Control_Instance =  LXeRunControl::GetInstance();
	Analysis = LXeAnalysis::GetInstance();
// Write all important information from RunControl in here to have it available for all methods
	
	path = Control_Instance->getPath();
	txt = ".txt";
	useGas = Control_Instance->UseGasInsteadOfLiquid();
	if(useGas){
		medium = "GXe";
	}else{
		medium = "LXe";
	}
	RawData_FileName = Control_Instance->getFileName();// including "RawData_" and ".txt"
	RawData_NakedFileName = Control_Instance->getNakedFileName(); // without ".txt" !!
	
	Plot_FileName = path+"Script_Plot_"+RawData_NakedFileName+txt;

	NUM_Events = Analysis->getTotalNUMEvents();
	particleType = Control_Instance->getParticleType();
	particleEnergy = Control_Instance->getParticleEnergy();
	Pressure = Control_Instance->getPressure();
	CreateScatterPlot = Control_Instance->createScatterPlot();
	CreateSiPMHisto = Control_Instance->createSiPMHisto();
	CreatePMTHisto = Control_Instance->createPMTHisto();
	alRefl = Control_Instance->getAlReflectivity();
	cuRefl = Control_Instance->getCuReflectivity();
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeScriptWriter::~LXeScriptWriter(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeScriptWriter::GNUPLOT_Histo_SiPMHit(){
	if(!CreateSiPMHisto){return;}
	Histo_SiPMHit_FileName = path+"Script_Histo_SiPMHit_"+RawData_NakedFileName+txt;
	//Histo_PMTHit_FileName = path+"Script_Histo_PMTHit_"+RawData_NakedFileName+txt;
	G4cout 	<< "Find awesome gnuplot script for SiPM histogram in: " << "\n"
			<< Histo_SiPMHit_FileName  << "\n"
			<< G4endl;
	
	script_Histo_SiPMHit.open(Histo_SiPMHit_FileName .c_str());

	G4int endXRange = Analysis->getLargestNUM_PhotonsOnSiPMPerEvent();
	G4int binwidth = endXRange/60;
	if (binwidth ==0) binwidth = 1;
	G4cout << "Largest NUM Photons on SiPM: " << endXRange << " Binwidth: " << binwidth << G4endl;
	
	script_Histo_SiPMHit 	<< "reset" << "\n" << endl;
	if(Control_Instance->getUseAlphaSource()){
	script_Histo_SiPMHit	<< "set title 'Histogram SiPM Hit - " << NUM_Events << " events - " 
				<< particleType << " 4.15, 4.48, 4.8 MeV  in " 
				<< medium << " - " << Pressure << " bar - " << "alRefl: "
				<< alRefl << " cuRefl: "<< cuRefl << "'" << endl;
	}else{
	script_Histo_SiPMHit	<< "set title 'Histogram SiPM Hit - " << NUM_Events << " events - " 
				<< particleType << " " << particleEnergy << " MeV  in " 
				<< medium << " - " << Pressure << " bar - " << "alRefl: "
				<< alRefl << " cuRefl: "<< cuRefl << "'" << endl;
	}
		
	script_Histo_SiPMHit	<< "#####Definitions#####" << "\n"
				<< "dataIN = '"<< path << RawData_FileName << "' " << "\n"
				<< "dataOUT = 'Histo_SiPM_" << RawData_NakedFileName << "' " << "\n"
				<< "#####Set Commands#####" << "\n"
				<< "set xlabel 'Number of Hits - Binwidth " <<  binwidth << "'  " << "\n"
				<< "set ylabel 'Number of Events' " << "\n"
				<< G4endl;
	
	script_Histo_SiPMHit << "set xrange [0:" << endXRange << "] " << "\n"
				<< "set ytics nomirror" << "\n"
				<< "set key box top left" << "\n"
				<< G4endl;
	
	script_Histo_SiPMHit << "binwidth=" << binwidth << "\n"
				<< "bin(x,width)=width*floor(x/width)" << "\n"
				<< "####Plot Commands####" << "\n"
				<< "set table 'Data_Histo_SiPM_" << RawData_NakedFileName << ".txt'" << "\n"
				<< "plot " //no new line here!
				<< "dataIN using (bin($3,binwidth)):(1.0) smooth freq w histeps" << "\n"
				<< "unset table" << "\n"
				<< "unset table" << "\n"
				<< "plot " //no new line here!
				<< "dataIN using (bin($3,binwidth)):(1.0) smooth freq w histeps lc 2 title 'Photons on SiPM per event' " << "\n"
				<< "###Output Commands###" << "\n"
				<< "set term pdf font 'Verdana,8' " << "\n"
				<< "set output dataOUT.'.pdf' " << "\n"
				<< "replot" << "\n"
				<< "set term png font 'Verdana,8' " << "\n"
				<< "set output dataOUT.'.png' " << "\n"
				<< "replot" << "\n"
				<< "set term pop "<< "\n"
				<< "replot" << "\n"
				<< G4endl;
				
	script_Histo_SiPMHit.close();
	

}

void LXeScriptWriter::GNUPLOT_Histo_PMTHit(){
	if(!CreatePMTHisto){return;}
	Histo_PMTHit_FileName = path+"Script_Histo_PMTHit_"+RawData_NakedFileName+txt;
	G4cout 	<< "Find awesome gnuplot script for PMT histogram in: " << "\n"
			<< Histo_PMTHit_FileName  << "\n"
			<< G4endl;
	
	script_Histo_PMTHit.open(Histo_PMTHit_FileName .c_str());

	G4int endXRange = Analysis->getLargestNUM_PhotonsOnPMTPerEvent();
	G4int binwidth = endXRange/100;
	G4cout << "Largest NUM Photons on PMT: " << endXRange << " Binwidth: " << binwidth << G4endl;
	
	script_Histo_PMTHit 	<< "reset" << "\n" << endl;
	if(Control_Instance->getUseAlphaSource()){
	script_Histo_SiPMHit	<< "set title 'Histogram PMT Hit - " << NUM_Events << " events - " 
				<< particleType << " 4.15, 4.48, 4.8 MeV  in " 
				<< medium << " - " << Pressure << " bar - " << "alRefl: "
				<< alRefl << " cuRefl: "<< cuRefl << "'" << endl;
	}else{
	script_Histo_SiPMHit	<< "set title 'Histogram PMT Hit - " << NUM_Events << " events - " 
				<< particleType << " " << particleEnergy << " MeV  in " 
				<< medium << " - " << Pressure << " bar - " << "alRefl: "
				<< alRefl << " cuRefl: "<< cuRefl << "'" << endl;
	}
	script_Histo_PMTHit << "#####Definitions#####" << "\n"
				<< "dataIN = '"<< path << RawData_FileName << "' " << "\n"
				<< "dataOUT = 'Histo_PMT_" << RawData_NakedFileName << "' " << "\n"
				<< "#####Set Commands#####" << "\n"
				<< "set xlabel 'Number of Hits - Binwidth " <<  binwidth << "'  " << "\n"
				<< "set ylabel 'Number of Events' " << "\n"
				<< G4endl;
	
	script_Histo_PMTHit << "set xrange [0:" << endXRange << "] " << "\n"
				<< "set ytics nomirror" << "\n"
				<< "set key box top left" << "\n"
				<< G4endl;
	
	script_Histo_PMTHit << "binwidth=" << binwidth << "\n"
				<< "bin(x,width)=width*floor(x/width)" << "\n"
				<< "####Plot Commands####" << "\n"
				<< "set table 'Data_Histo_PMT_" << RawData_NakedFileName << ".txt'" << "\n"
				<< "plot " //no new line here!
				<< "dataIN using (bin($4,binwidth)):(1.0) smooth freq w histeps" << "\n"
				<< "unset table" << "\n"
				<< "unset table" << "\n"
				<< "plot " //no new line here!
				<< "dataIN using (bin($4,binwidth)):(1.0) smooth freq w histeps lc 2 title 'Photons on PMT per event' " << "\n"
				<< "###Output Commands###" << "\n"
				<< "set term pdf font 'Verdana,8' " << "\n"
				<< "set output dataOUT.'.pdf' " << "\n"
				<< "replot" << "\n"
				<< "set term png font 'Verdana,8' " << "\n"
				<< "set output dataOUT.'.png' " << "\n"
				<< "replot" << "\n"
				<< "set term pop "<< "\n"
				<< "replot" << "\n"
				<< G4endl;
				
	script_Histo_PMTHit.close();
	

}


void LXeScriptWriter::GNUPLOT_Scatterplot_SiPM_vs_PMT(){
	if(!CreateScatterPlot){return;}
	Scatterplot_FileName  = path+"Script_Scatterplot_"+RawData_NakedFileName+txt;
	G4cout 	<< "Find even more awesome gnuplot script for scatterplot in: " << "\n"
			<< Scatterplot_FileName  << "\n"
			<< G4endl;
	script_Scatterplot_SiPMvsPMT.open(Scatterplot_FileName.c_str());
	script_Scatterplot_SiPMvsPMT 
				<< "reset" << endl;
	if(Control_Instance->getUseAlphaSource()){
	script_Scatterplot_SiPMvsPMT 
				<< "# SiPM x-Position: " << Control_Instance->getSiPM_xPos() << "\n"
				<< "set title 'SiPM vs PMT - " << NUM_Events << " events - " 
				<< particleType << "  4.15, 4.48, 4.8 MeV  in " 
				<< medium << " - " << Pressure << " bar' "<< endl;
	}	else{
	script_Scatterplot_SiPMvsPMT 
				<< "# SiPM x-Position: " << Control_Instance->getSiPM_xPos() << "\n"
				<< "set title 'SiPM vs PMT - " << NUM_Events << " events - " 
				<< particleType << " " << particleEnergy << " MeV  in " 
				<< medium << " - " << Pressure << " bar' "<< endl;
	}	
	script_Scatterplot_SiPMvsPMT 
				<< "#####Definitions#####" << "\n"
				<< "dataIN = '"<< path << RawData_FileName << "' " << "\n"
				<< "dataOUT = 'Scatterplot_" << RawData_NakedFileName << "' " << "\n"
				<< "#####Set Commands#####" << "\n"
				<< "set xlabel 'Number of Hits on PMT " << "'  " << "\n"
				<< "set ylabel 'Number of Hits on SiPM' " << "\n"
				<< G4endl;
	
	script_Scatterplot_SiPMvsPMT 	
				<< "set ytics nomirror" << "\n"
				<< "set key box top left" << "\n"
				<< G4endl;
	
	script_Scatterplot_SiPMvsPMT 
				<< "####Plot Commands####" << "\n"
				<< "plot " //no new line here!
				<< "dataIN using 4:3 title 'Reflectivity: " << Control_Instance->getCuReflectivity() << "' " << "\n"
				<< "###Output Commands###" << "\n"
				<< "set term pdf font 'Verdana,8' " << "\n"
				<< "set output dataOUT.'.pdf' " << "\n"
				<< "replot" << "\n"
				<< "set term png font 'Verdana,8' " << "\n"
				<< "set output dataOUT.'.png' " << "\n"
				<< "replot" << "\n"
				<< "set term pop "<< "\n"
				<< "replot" << "\n"
				<< G4endl;
				
	script_Scatterplot_SiPMvsPMT.close();
	
}


