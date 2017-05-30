/// \file LXePrimaryGeneratorAction.hh
/// \brief Definition of the LXePrimaryGeneratorAction class

#ifndef LXePrimaryGeneratorAction_h
#define LXePrimaryGeneratorAction_h 1
#include "LXeRunControl.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include <iostream>
#include <fstream>
using namespace std;
class G4ParticleGun; 	// Forward declaration! 
class G4Event;		// man sagt dem Compiler lediglich,
class G4Box;			// dass es mal so eine Klasse geben wird

/// The primary generator action class with particle gun.

class LXePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    LXePrimaryGeneratorAction(string ptype, double energy);    
     virtual ~LXePrimaryGeneratorAction();	// "virtual" could be removed as well
									// wouldn't change the outcome

    // method from the base class, Mandatory!
    virtual void GeneratePrimaries(G4Event*);// "virtual" could be removed as well
									// wouldn't change the outcome

  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  //  void setParticleGunPosition(G4double value) const;
    
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4Box* fEnvelopeBox;
	ofstream data; // Name the ofstream to write data to file
	string DATA; // declare string for file name
  //  G4double z_position;
  string particleType;
  double particleEnergy;
	    G4double CmEnergy;
	    G4double AmEnergy;
	    G4double PuEnergy;
   LXeRunControl* Control_Instance;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif