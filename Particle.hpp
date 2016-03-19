// May need libroot-math-physics-dev. Install using synaptic package manager.
// http://packages.ubuntu.com/trusty/i386/libroot-math-physics-dev/filelist

#ifndef Particle_hpp_INCLUDED   
#define Particle_hpp_INCLUDED   

// C++ libraries
#include <iostream>
#include <string.h>

// ROOT libraries
#include <TEveStraightLineSet.h>

#include "EnergyLoss.hpp"
#include "FourVector.hpp"
#include "Particle.hpp"

class Particle{
public:
  // Constructors
  Particle(string Name, double M, int Q, bool SaveTrajectory=0);
  Particle(string Name="", int A=0, int Z=0, int Q=0, bool SaveTrajectory=0);

  // Methods
  void Boost(double BetaX, double BetaY, double BetaZ);
  void Copy(Particle* Other);
  void CopyTrace(int& NumPts, float* t, float* x, float* y, float* z, float* K);
  void GetBeta(double& BetaX, double& BetaY, double& BetaZ);
  int GetCurrentExcState();
  double GetEexc();
  double GetEexc(int ExcState);
  double GetFinalEnergy(int MediumID, double InitE, double PathLength, double StepSize);
  double GetKE();
  FourVector GetP();
  void GetP(double& P0, double& P1, double& P2, double& P3);
  double GetPathLength(int MediumID, double InitE, double FinalE, double DeltaT);
  double GetPhi();
  double GetTheta();  
  void GetTrajectoryAtt(short& Color, short& Style, short& Width);
  void GetX(double& X0, double& X1, double& X2, double& X3);
  void Print();
  void ResetTrace();
  void SetCurrentExcState(int ExcState);
  void SetExcEnergies(int N, double* Eexc);
  void SetMedia(int NumMedia, string* ELossFile);
  void SetP(FourVector P);
  void SetP(double P0, double P1, double P2, double P3);
  void SetReactionIndex(int RI);
  void SetTracePoint(float t, float x, float y, float z, float K);
  void SetX(double X0, double X1, double X2, double X3);
  void SetTrajectoryAtt(short Color, short Style=1, short Width=1);

  // Assignment operator 
  //  Particle & operator=(const Particle &rhs);

  // Members
  int A;
  double* Eexc;
  double Mass;
  static const int MaxPoints = 5000;
  string Name;
  int NEexc;
  int Q;
  int RI;
  bool SaveTrajectory;
  TEveStraightLineSet* Trajectory;
  int Z;

private:
  // For the traces (time, space coords and number of points).
  float* TrT;
  float* TrX;
  float* TrY;
  float* TrZ;
  float* TrK;
  int TrPts;

  FourVector P;               // Four-momentum
  FourVector X;               // Four-position

  EnergyLoss** IonInMedium;

  int NumMedia;
  int MaxMedia;
  int CurrentExcState;

  short AttColor;
  short AttStyle;
  short AttWidth;

  static const double pi = 3.14159265359;
  // ClassDef(Particle,1);
};

#endif
