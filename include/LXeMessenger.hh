/// \file LXeMessenger.hh
/// \brief Definition of the LXeMessenger class

#ifndef LXeMessenger_h
#define LXeMessenger_h 1

#include "LXeRunControl.hh"
#include "LXeAnalysis.hh"

#include <string>
#include <fstream>
#include <iostream>

/// Messenger Class
///
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class LXeMessenger
{
	public:
		LXeMessenger();
		virtual ~LXeMessenger();
		
		void PrintMainArgError();
		void CreateHeader();
		void CreateFooter();
	private:
		LXeRunControl* Control_Instance;
		//LXeAnalysis* Analysis;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif