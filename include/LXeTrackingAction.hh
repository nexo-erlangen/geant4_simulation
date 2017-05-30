/// \file LXeTrackingAction.hh
/// \brief Definition of the LXeTrackingAction class

#ifndef LXeTrackingAction_h
#define LXeTrackingAction_h 1

#include "globals.hh"

#include "G4Track.hh"
#include "G4UserTrackingAction.hh"

#include "LXeAnalysis.hh"

class LXeTrackingAction : public G4UserTrackingAction
{
public:
  LXeTrackingAction();
  virtual ~LXeTrackingAction();
  
  virtual void PreUserTrackingAction(const G4Track* track);
  virtual void PostUserTrackingAction(const G4Track* track);  

private:
};

#endif
