/// \file LXeRunControl.hh
/// \brief Definition of the LXeRunControl class

#ifndef LXeRunControl_h
#define LXeRunControl_h 1

#include "globals.hh"
#include <string>
#include <iostream>
#include "G4Run.hh"

/// RunControl Class
using namespace std;

class LXeRunControl
{
	public:
		static LXeRunControl* GetInstance(){
			if(LXeRunControl::fInstance == NULL) {
				LXeRunControl::fInstance = new LXeRunControl;
			}
			return fInstance;
		}
		
		virtual ~LXeRunControl();
		
		G4long getSeed();
		
		void createFileName();// Also creates naked File Name for Script Writer Class!
		string getNakedFileName(){return nakedFileName;};
		string getFileName(){return fileName;};
		void setFileName(string name);
		
		string getPath(){return path;};
		void setPath(string pathToSet){
			size_t found = pathToSet.rfind("/");
			if(found!=pathToSet.length()-1) pathToSet = pathToSet+"/";
			path=pathToSet;
			};
		
		G4bool UseGasInsteadOfLiquid(){return useGas;};
		void setUseGasBoolean(G4bool passedBoolean){useGas = passedBoolean;};
		
		G4double getCutValue(){return cutValue;};
		void setCutValue(G4double cut){cutValue = cut;};
		
		G4bool getSinglePhaseBoolean(){return SinglePhaseBoolean;};
		void setSinglePhaseBoolean(G4bool passedBoolean){SinglePhaseBoolean = passedBoolean;};
		
		G4double getNEST_Factor(){return NEST_Factor;};
		void setNEST_Factor(G4double factor){NEST_Factor=factor;};
		
		string getParticleType(){return particleType;};
		void setParticleType(string type){particleType = type;};
		
		G4double getParticleEnergy(){return particleEnergy;};
		void setParticleEnergy(G4double energy){particleEnergy = energy;};
		
		G4bool getTrackingOutputBoolean(){return UseCmdLineTrackingOutput;};
		void setCmdLineTrackingOutput(G4bool passedBoolean){UseCmdLineTrackingOutput = passedBoolean;};
		
		G4double getScintYield(){return YieldFactor;};
		void setScintYield(G4double factor){YieldFactor = factor;};
		
		G4bool TrackGammas(){return Trackgammas;};
		void setTrackGammas(G4bool trackG){Trackgammas = trackG;};
		
		G4double getCuReflectivity(){return CuReflectivity;};
		void setCuReflectivity(G4double refl){CuReflectivity = refl;};
		
		G4double getAlReflectivity(){return AlReflectivity;};
		void setAlReflectivity(G4double refl){AlReflectivity = refl;};
		
		G4double getPressure(){return Pressure;};
		void setPressure(G4double pressure){Pressure = pressure;};
		
		G4bool createScatterPlot(){return CreateScatterPlot;};
		void setScatterPlot(G4bool scatter){CreateScatterPlot = scatter;};
		
		G4bool createSiPMHisto(){return CreateSiPMHisto;};
		void setSiPMHisto(G4bool set){CreateSiPMHisto = set;};
		
		G4bool createPMTHisto(){return CreatePMTHisto;};
		void setPMTHisto(G4bool set){CreatePMTHisto = set;};
		
		G4bool getUseRunSequence(){return UseRunSequence;};
		void setUseRunSequence(G4bool yesNo){UseRunSequence = yesNo;};
			
		void getSequence(const G4Run* aRun);
		
		G4double getSiPM_xPos(){return SiPM_xPos;};
		void setSiPM_xPos (G4double value){SiPM_xPos = value;};
		
		G4bool displayEventResults(){return displayEvtRes;};
		void setdisplayEventResults(G4bool boolean){displayEvtRes=boolean;};
		
		G4bool getUseAlphaSource(){return UseAlphaSource;};
		void setUseAlphaSource(G4bool useA){UseAlphaSource = useA;};
		
		G4bool getOpticsEnabled(){return enableOptics;};
		void setOpticsEnabled(G4bool enable){enableOptics = enable;};	
		
		G4double getPMT_Efficiency(){return 
			PMT_Efficiency;
			cout << "LXeRunControl::getPMT_Efficiency = " << PMT_Efficiency << endl;
			};
		void setPMT_Efficiency(G4double eff){PMT_Efficiency = eff;
			cout << "LXeRunControl::setPMT_Efficiency( " << eff << " )" << endl;
			cout << "Now: PMT_Efficiency = " << PMT_Efficiency << endl;
			};
		G4double getSiPM_Efficiency(){return SiPM_Efficiency;
			cout << "LXeRunControl::getSiPM_Efficiency " << SiPM_Efficiency << endl;
			};
		void setSiPM_Efficiency(G4double eff){SiPM_Efficiency = eff;
			cout << "LXeRunControl::setSiPM_Efficiency( " << eff << " )" << endl;
			cout << "Now: SiPM_Efficiency = " << SiPM_Efficiency << endl;
			};
		G4double getAnalyseRange(){return AnalyseRange;};
		void SetAnalyseRange(G4bool analyse){AnalyseRange = analyse;};
		
		G4double getCherenkov(){return fCherenkov;};
		void setCherenkov(G4bool cherenkov){fCherenkov = cherenkov;};
				
		
	private:
		LXeRunControl();
		
		static LXeRunControl* fInstance;
		string fileName;
		string nakedFileName;
		string path;
		G4bool useGas;
		G4double cutValue;
		G4bool SinglePhaseBoolean;
		G4double NEST_Factor;
		string particleType;
		G4double particleEnergy;
		G4bool UseCmdLineTrackingOutput;
		G4double YieldFactor;
		G4bool Trackgammas;
		G4double CuReflectivity;
		G4double AlReflectivity;
		G4double Pressure;
		G4bool CreateScatterPlot;
		G4bool CreateSiPMHisto;
		G4bool CreatePMTHisto;
		G4bool UseRunSequence;
		G4double SiPM_xPos ;
		G4bool displayEvtRes;
		G4bool UseAlphaSource;
		G4bool enableOptics;
		G4double PMT_Efficiency ;
		G4double SiPM_Efficiency ;
		G4bool AnalyseRange;
		G4bool fCherenkov;
	
};

#endif