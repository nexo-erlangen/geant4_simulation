/// \file LXeAnalysis.cc
/// \brief Implementation of the LXeAnalysis class

#include "LXeAnalysis.hh"
#include "LXeMessenger.hh"
#include "G4Track.hh"
#include "LXeDetectorConstruction.hh"
#include "LXeRangeAnalysis.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "LXeScriptWriter.hh"
#include "Randomize.hh"
#include "globals.hh"

extern ofstream data;
extern string VERSION;
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
LXeAnalysis* LXeAnalysis::fInstance = 0;

LXeAnalysis::LXeAnalysis()
{
	NUM_photonsPerEvent = 0;
	largestNUM_photonsPerEvent = 0;
	largestNUM_PhotonsOnSiPMPerEvent = 0;
	largestNUM_PhotonsOnPMTPerEvent = 0;
	NUM_electronsPerEvent = 0;
	NUM_gammasPerEvent = 0;
	NUM_gammasPerRun = 0;
	TrackGammas = LXeRunControl::GetInstance()->TrackGammas();
	total_NUM_events = 1; 
	NUM_photonsInSiPMVolume = 0;
	NUM_photonsInPMTVolume = 0;
	const LXeDetectorConstruction* detectorConstruction =
		static_cast<const LXeDetectorConstruction*>
		(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	fSiPMVolume = detectorConstruction->GetScoringVolume();  
	fPMTVolume = detectorConstruction->GetPMTSensitiveVolume();
	storedTrackID = -1;
	NUM_Test = 0; // Can be used for testing any random stuff
	NUM_Test2 =0;
	UseRunSequence = LXeRunControl::GetInstance()->getUseRunSequence();
	Control_Instance =  LXeRunControl::GetInstance();
	Range_Instance = LXeRangeAnalysis::GetInstance();
	pmt_efficiency = Control_Instance->getPMT_Efficiency();
	sipm_efficiency = Control_Instance->getSiPM_Efficiency();
	AnalyseRange = Control_Instance->getAnalyseRange();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeAnalysis::~LXeAnalysis()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeAnalysis::PrepareNewRun(const G4Run* run){
	if(UseRunSequence) LXeRunControl::GetInstance()->getSequence(run);
	
	Output_FileName = LXeRunControl::GetInstance()->getFileName();
	path = LXeRunControl::GetInstance()->getPath();
	absolutePath = path+Output_FileName;
	
	//tempPath = path+"PhotonEnergy_GXe.txt";
	//tempstream.open(tempPath.c_str()); 
					//This is used to write photon energy of EACH SINGLE photon to file!
					//Poduces ridiculously high amount of data!
					//DO NOT ENABLE IF USING MORE THAN ONE EVENT!
					//Command is written in "LXeAnalysis::PreUserTrackingAction(const G4Track* track)"
	
	data.open(absolutePath.c_str());
	LXeMessenger* Messenger = new LXeMessenger;
	Messenger->CreateHeader();
	//Here: Important information on current run is written to output file
	
// Invoke other analysis classes
	if(AnalyseRange){
		Range_Instance->PrepareNewRun(run);
	}
}

void LXeAnalysis::EndOfRunAction(const G4Run* run){
	
	LXeMessenger* Messenger = new LXeMessenger;	
	Messenger->CreateFooter();
	data.close();
	
	//tempstream.close();
	
	LXeScriptWriter* scriptWriter = new LXeScriptWriter;
	scriptWriter->GNUPLOT_Histo_SiPMHit();
	scriptWriter->GNUPLOT_Histo_PMTHit();
	scriptWriter->GNUPLOT_Scatterplot_SiPM_vs_PMT();
	
	
	largestNUM_photonsPerEvent = 0; // reset for next Run
	largestNUM_PhotonsOnSiPMPerEvent = 0;
	largestNUM_PhotonsOnPMTPerEvent = 0;
	G4cout << "Thank you for using " << VERSION << "!" << G4endl;

	// Invoke other analysis classes
	if(AnalyseRange){
		Range_Instance->EndOfRunAction(run);
	}	

}


void LXeAnalysis::PrepareNewEvent(const G4Event*/*event*/){	
	
	
}

void LXeAnalysis::EndOfEventAction(const G4Event* event){
	if( LXeRunControl::GetInstance()->displayEventResults() ){
		G4cout<< event->GetEventID() << ": Numbers in this event: " << NUM_photonsPerEvent << " photons; "
			<< NUM_electronsPerEvent << " electrons" << "\n"
			<< "NUM Gammas in this event: " << NUM_gammasPerEvent << "\n"
			<< "NUM_photonsInSiPMVolume in this event: " << NUM_photonsInSiPMVolume << "\n" 
			<< "NUM_photonsInPMTVolume in this event: " << NUM_photonsInPMTVolume << "\n" 
			//<< "Number of photon steps that have already been in scoring volume:  " << NUM_Test << "\n"
			//<< "Number of photon steps that have been in scoring volume and LEFT it afterwards again:  " << NUM_Test2
			<< G4endl;
	}
	
	if(TrackGammas){
	data << NUM_photonsPerEvent << "\t" 
			<< NUM_electronsPerEvent << "\t" 
			<< NUM_photonsInSiPMVolume << "\t"
			<< NUM_photonsInPMTVolume << "\t"
			<< NUM_gammasPerEvent << "\t"
			<< LXeRunControl::GetInstance()->getParticleEnergy()
			<< G4endl;
	}else{
	data << NUM_photonsPerEvent << "\t" 
			<< NUM_electronsPerEvent << "\t" 
			<< NUM_photonsInSiPMVolume << "\t"
			<< NUM_photonsInPMTVolume << "\t"
			<< LXeRunControl::GetInstance()->getParticleEnergy()
			<< G4endl;	
	}
	if(NUM_photonsInPMTVolume>largestNUM_PhotonsOnPMTPerEvent){
		largestNUM_PhotonsOnPMTPerEvent = NUM_photonsInPMTVolume;
	}
	
	if(NUM_photonsPerEvent>largestNUM_photonsPerEvent){
		largestNUM_photonsPerEvent = NUM_photonsPerEvent;
	}
	if(NUM_photonsInSiPMVolume>largestNUM_PhotonsOnSiPMPerEvent){
		largestNUM_PhotonsOnSiPMPerEvent = NUM_photonsInSiPMVolume;
	}
	 // reset the counters after each event
	NUM_photonsPerEvent = 0;
	NUM_electronsPerEvent = 0;
	NUM_gammasPerRun += NUM_gammasPerEvent;
	NUM_gammasPerEvent = 0;
	total_NUM_events = (event->GetEventID()+1);
	NUM_photonsInSiPMVolume = 0;
	NUM_photonsInPMTVolume = 0;
	NUM_Test = 0;
	NUM_Test2 = 0;
	//EDep = 0;
	
}	
	
void LXeAnalysis::PreUserTrackingAction(const G4Track* track){
	// G4int trackID = track->GetTrackID();
	
	G4ParticleDefinition* particle = track->GetDefinition();
	
	if (particle->GetParticleName() == "opticalphoton") {
		NUM_photonsPerEvent++;
		/*
		G4double totalEnergy_MeV = (track->GetTotalEnergy())/MeV;
		G4double totalEnergy_nm = (3*4.135*0.0001)/totalEnergy_MeV;
		tempstream << totalEnergy_MeV <<"\t" << "MeV" << "\t" << totalEnergy_nm << "\t" << "nm" << G4endl;
		*/
		// -> DO NOT ENABLE IF USING MORE THAN ONE EVENT!
	}
	else if (particle->GetParticleName() == "e-") {NUM_electronsPerEvent++;}
	else if (particle->GetParticleName() == "alpha") {alphaTrack = track;}
	else if (particle->GetParticleName() == "gamma"){NUM_gammasPerEvent++;}
	// Invoke other stepping actions
	
	if(AnalyseRange){
	Range_Instance->PreUserTrackingAction(track);
	}
}

void LXeAnalysis::PostUserTrackingAction(const G4Track* track){
	// Invoke other stepping actions
	
	if(AnalyseRange){
	Range_Instance->PostUserTrackingAction(track);
	}
}

void LXeAnalysis::SteppingAction(const G4Step* step){
	
	if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "opticalphoton"){
		//Perform for photons only to save time!
		if(step->GetTrack()->GetTrackID() == storedTrackID){
			/*
			NUM_Test ++; // Count Photons that have already been in scoring volume before
			G4cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << G4endl;
			G4cout << "StoredTrackID:  " << storedTrackID << G4endl;
			G4cout << "This Photon has already been in Scoring Volume!" << G4endl;
			G4cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << G4endl;
			
			G4LogicalVolume* volume =
			step->GetPreStepPoint()->GetTouchableHandle()
			->GetVolume()->GetLogicalVolume();
			if(volume != fScoringVolume){
				G4cout << "Photon HAS LEFT scoring volume. " << G4endl;
				NUM_Test2 ++; // Count photons that have hit the scoring volume already and have left it afterwards
			}
			*/
			return;
		}else{
		// get volume of the current step
			G4LogicalVolume* volume =
			step->GetPreStepPoint()->GetTouchableHandle()
			->GetVolume()->GetLogicalVolume();
			
			if(volume == fPMTVolume){
				if(G4UniformRand() <= pmt_efficiency){
					NUM_photonsInPMTVolume ++; 
				}
				storedTrackID = step->GetTrack()->GetTrackID();
			}
			else if(volume == fSiPMVolume){
				if(G4UniformRand() <= sipm_efficiency){
					NUM_photonsInSiPMVolume ++; 
				}
				storedTrackID = step->GetTrack()->GetTrackID();
				//G4cout << "New TrackID:  " << storedTrackID << G4endl;
			}
		}
	
	}else{
		return;
	}
	
	/*
		G4double edep = step->GetTotalEnergyDeposit();
		EDep += edep;
	*/

// Invoke other stepping actions
	
	if(AnalyseRange){
			Range_Instance->SteppingAction(step);
	}
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

