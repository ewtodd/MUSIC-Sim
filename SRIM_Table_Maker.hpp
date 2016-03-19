/***********************************************************************
Header file: SRIM_Table_Maker.hpp

Description: A class that creates input files for SRIM and then runs 
             SRIM (actually, SRModule.exe) via the program 'wine'.  The 
             SRIM outputs are limited to 6 predefined cases: 
             0 - CD2
             1 - CF4 (gas)
             2 - Helium-3 (gas)
             3 - Helium-4 (gas)
             4 - Kapton
             5 - Silicon
             6 - LiF
             7 - Havar
             8 - Oxygen-16 (gas, diatomic molecule)
             9 - Oxygen-18 (gas, diatomic molecule)
            10 - Deuterium (gas, diatomic molecule)

Author: Daniel Santiago-Gonzalez
2014-07
***********************************************************************/
#ifndef SRIM_Table_Maker_hpp_INCLUDED   
#define SRIM_Table_Maker_hpp_INCLUDED   

#include <iostream>
#include <fstream>
#include <string.h>

// To excecute an external program.
#include <unistd.h>
#include <sys/wait.h>

class SRIM_Table_Maker{
public:
  SRIM_Table_Maker(string SRModulePath);
  int GetMaxCases();
  void MakeTable(string SRIM_output, int Case, int Charge, double Mass /*u*/);
  void SetGasDensity(int Case, float Pressure /*Torr*/, float Temperature /*K*/);

private:

  void MakeSRIMInputFile(string SRIM_output, int Case, int Charge, double Mass /*u*/);
  int RunSRModule();

  string SRModulePath;

  int MaxCases, MaxNumElem;
  int* Phase;
  double* Density;
  string* CompCorr;
  int* NumElem;
  string** TgtComp;
  //  pid_t pid;
};

#endif
