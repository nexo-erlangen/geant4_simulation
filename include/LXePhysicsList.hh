#ifndef LXePhysicsList_h
#define LXePhysicsList_h 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"
#include "LXePhysicsConstructor.hh"

//#include "G4S1Light.hh"

class LXePhysicsList : public G4VModularPhysicsList
{
public:
	LXePhysicsList(G4double passedValue, G4bool passedBoolean, G4double scintFactor);
  //LXePhysicsList(G4int ver = 1, const G4String& type = "LXePhysicsList");


	virtual ~LXePhysicsList();

	virtual void SetCuts();


private:
	G4double cutValue;
	G4bool SinglePhase;
	G4double ScintFactor;
/*
  // copy constructor and hide assignment operator
  LXePhysicsList(LXePhysicsList &);
  LXePhysicsList & operator=(const LXePhysicsList &right);

*/
};

#endif
