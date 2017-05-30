/// \file LXePrimaryGeneratorAction.cc
/// \brief Implementation of the LXePrimaryGeneratorAction class

#include "LXePrimaryGeneratorAction.hh"
#include "LXeRunControl.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"					// For particles
#include "G4ParticleDefinition.hh"				// For particles
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4Alpha.hh"
#include "G4Electron.hh"
#include "G4AntiProton.hh"
#include <boost/random.hpp>
#include <iostream>
#include <fstream>
#include <string>
//#include <boost/math/distributions/poisson.hpp>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePrimaryGeneratorAction::LXePrimaryGeneratorAction(string ptype, double energy)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fEnvelopeBox(0),
  DATA("Primary_Particle_Data.txt"),
  particleType(ptype),
  particleEnergy(energy*MeV),
CmEnergy(5.8214*MeV),
AmEnergy(5.5116*MeV),
PuEnergy(5.1798*MeV)
  /*,
  z_position(0)*/
{
	Control_Instance = LXeRunControl::GetInstance();
	// Define Particle
		
	
	G4ParticleDefinition* particle_defined = G4Alpha::AlphaDefinition(); 
if (particleType!=""){
	if (particleType == "alpha"){
		particle_defined = G4Alpha::AlphaDefinition();
	}
	else if (particleType == "electron"){
		particle_defined = G4Electron::ElectronDefinition();
	}
	else if (particleType == "gamma"){
		particle_defined = G4Gamma::GammaDefinition();
	}
	
}
	//= G4AntiProton::AntiProtonDefinition();
	//
	//= G4Positron::PositronDefinition();
	//= G4Proton::ProtonDefinition();
	// Create and "load" ParticelGun with particle and numberOfParticles
	int numberOfParticles = 1;
	fParticleGun = new G4ParticleGun(particle_defined, numberOfParticles);

//    fParticleGun->SetParticleEnergy(particleEnergy);
	
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePrimaryGeneratorAction::~LXePrimaryGeneratorAction() //Destructor
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event
     
	G4double src_pos_z = -3.75*cm; //Changed this back to -3.75 (-3.70 before)
	G4double src_phi = G4UniformRand()*2*pi;
	G4double src_r = 0.25*sqrt(G4UniformRand())*cm;
	G4double src_pos_x=src_r*cos(src_phi);
	G4double src_pos_y=src_r*sin(src_phi);
    
    G4double phi = G4UniformRand()*2*pi;
    G4double theta = acos(G4UniformRand()*2-1);
    
    G4double x = sin(theta)*cos(phi);
    G4double y = sin(theta)*sin(phi);
    G4double z = cos(theta);
    if(z<0){
	    z=-z;
	    }//Only emit alphas into positive half space
/*
    data.open(DATA.c_str());
    data << x << "\t" << y << "\t" << z << G4endl;
    data.close();
    
    G4cout << "Particle momentum direction is written to file: " << DATA << "\n"
    << "using columns: x, y, z" << G4endl;
	    */
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x,y,z));
//fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
	fParticleGun->SetParticlePosition(G4ThreeVector(src_pos_x,src_pos_y,src_pos_z));
	//fParticleGun->SetParticlePosition(G4ThreeVector(0,0,src_pos_z));
	    

	    
if(!Control_Instance->getUseAlphaSource()){ // Asks if alpha source shall be used like the one in the actual chamber
	fParticleGun->SetParticleEnergy(particleEnergy);    // if false: Use other and get energy
}else{
	G4double percentage = G4UniformRand();
	if(percentage <0.1160){
		G4double RandEnergy_Cm = G4RandGauss::shoot(CmEnergy,0.059*MeV);
		//fParticleGun->SetParticleEnergy(CmEnergy);
		//Control_Instance->setParticleEnergy(CmEnergy);
		fParticleGun->SetParticleEnergy(RandEnergy_Cm);
		Control_Instance->setParticleEnergy(RandEnergy_Cm);
		} // in 11.60% of the cases use Cm244
	else if(percentage > 0.5169){
		G4double RandEnergy_Am = G4RandGauss::shoot(AmEnergy,0.064*MeV);
		fParticleGun->SetParticleEnergy(RandEnergy_Am);
		Control_Instance->setParticleEnergy(RandEnergy_Am);
		//fParticleGun->SetParticleEnergy(AmEnergy);
		//Control_Instance->setParticleEnergy(AmEnergy);
		} // in 48.31 % of the cases use Am241
	else {
		G4double RandEnergy_Pu = G4RandGauss::shoot(PuEnergy,0.063*MeV);
		fParticleGun->SetParticleEnergy(RandEnergy_Pu);
		Control_Instance->setParticleEnergy(RandEnergy_Pu);
		//fParticleGun->SetParticleEnergy(PuEnergy);
		//Control_Instance->setParticleEnergy(PuEnergy);
		} // in 40.28% of the cases use Pu239
}
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......