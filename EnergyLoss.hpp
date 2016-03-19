/*******************************************************************
Header file: EnergyLoss.hpp

Description: Simple class that calculates the energy loss of an ion
  in a gas target. The input is a three-column text file with the
  energy of the ion and the electrical and nuclear stopping powers
  (dE/dx) of the target for that ion energy. The units are assumed
  to be MeV and MeV/mm for the ion's energy and the stopping powers,
  respectively. This information (E and dE/dx) can be obtained from
  SRIM. Also, it is assumed that the first line are three strings
  describing the columns.

Author: Daniel Santiago-Gonzalez
2012-Sep
*******************************************************************/
#ifndef EnergyLoss_hpp_INCLUDED   
#define EnergyLoss_hpp_INCLUDED   

#include <iostream>
#include <fstream>
#include <string.h>
#include <TGraph.h>

class EnergyLoss{
public:
  EnergyLoss();
  EnergyLoss(string Eloss_file, float IonMass=0);
  void GetBraggCurve(float InitE, int NSteps, float* Dist, float StepSize);
  void GetBraggCurves(int NCurves, float* InitE, int NSteps, float FinalDist);
  void GetBraggCurves(int NCurves, float* InitE, int NSteps, float* Dist, float StepSize);
  void GetBraggCurves(int NCurves, float InitE, int* NSteps, float** Dist, float StepSize);
  void GetEnergyCurve(float InitE, int NSteps, float* Dist, float StepSize);
  void GetEnergyCurves(int NCurves, float* InitE, int NSteps, float* DistArray, float StepSize);
  double GetEnergyLoss(float initial_energy, float distance);
  void GetEvDCurve(float InitEne, float FinalDepth, int steps);
  double GetInitialEnergy(float FinalEnergy/*MeV*/, float PathLength/*cm*/, float StepSize/*cm*/);
  double GetFinalEnergy(float InitialEnergy/*MeV*/, float PathLength/*cm*/, float StepSize/*cm*/);  
  double GetPathLength(float InitialEnergy/*MeV*/, float FinalEnergy/*MeV*/, float DeltaT/*ns*/);
  double GetTimeOfFlight(float InitialEnergy, float PathLength, float StepSize);
  bool LoadSRIMFile(string FileName);
  void SetIonMass(float IonMass);


  bool GoodELossFile;
  TGraph* EvD;
  TGraph** BraggCurve;
  TGraph** EnergyCurve;
  string FileName;

private:
  double c;
  double* IonEnergy;
  double IonMass;
  double* dEdx_e;
  double* dEdx_n;
  int points;
  int last_point;
  bool Energy_in_range;
};


#endif
