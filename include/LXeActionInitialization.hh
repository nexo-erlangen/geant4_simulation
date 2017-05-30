/// \file LXeActionInitialization.hh
/// \brief Definition of the LXeActionInitialization class

#ifndef LXeActionInitialization_h				// checks if token "LXeActionInitialization_h" is defined and if not:
#define LXeActionInitialization_h 1				// defines the token

#include "G4VUserActionInitialization.hh"

#include <iostream>
#include <string>
using namespace std;
/// Action initialization class.

class LXeActionInitialization : public G4VUserActionInitialization
{
  public:
    LXeActionInitialization(string ptype, double energy);
    virtual ~LXeActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
  
  private:
  string particleType;
  double particleEnergy;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif									// end of check if token is defined