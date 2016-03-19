
// Header file for this class
#include "Particle.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////
// Constructor 1 (most common)
///////////////////////////////////////////////////////////////////////////////////
Particle::Particle(string Name, double M, int Q, bool SaveTrajectory)
{
  this->Name = Name;
  this->Q = Q;
  Mass = M;
  A = 0;  // Not used at this moment.
  Z = 0;  // Not used at this moment.
  NEexc = 0;
  this->SaveTrajectory = SaveTrajectory;
  
  // Variables
  AttColor = 1;
  AttStyle = 1;
  AttWidth = 1;
  CurrentExcState = 0;
  NumMedia = 0;
  MaxMedia = 20;
  P.SetName("P_"+Name);
  P.SetCoords(0,0,0,0);
  RI = 0;
  TrPts = 0;
  X.SetName("X_"+Name);
  X.SetCoords(0,0,0,0);
  // Pointers
  Eexc = 0;
  IonInMedium = new EnergyLoss*[MaxMedia];
  for (int m=0; m<MaxMedia; m++) 
    IonInMedium[m] = 0;
  Trajectory = new TEveStraightLineSet();
  TrT = new float[MaxPoints];
  TrX = new float[MaxPoints];
  TrY = new float[MaxPoints];
  TrZ = new float[MaxPoints];
  TrK = new float[MaxPoints];
}


///////////////////////////////////////////////////////////////////////////////////
// Constructor 2
///////////////////////////////////////////////////////////////////////////////////
Particle::Particle(string Name, int A, int Z, int Q, bool SaveTrajectory)
{
  this->Name = Name;
  this->A = A;
  this->Z = Z;
  this->Q = Q;
  this->SaveTrajectory = SaveTrajectory;
  NEexc = 0;

  // Right now the masses are hard coded but they are supposed to be look for
  // in a database.
  double Conv = 931.494061; // from u to MeV/c^2
  if (A==1 && Z==1)
    Mass = Conv*1.0078250321;
  else if (A==4 && Z==2)
    Mass = Conv*4.00260325415;
  else if (A==20 && Z==10)
    Mass = Conv*19.9924401754;
  else if (A==23 && Z==11)
    Mass = Conv*22.9897692809;
  else 
    Mass = 0;
  
  // Variables
  AttColor = 1;
  AttStyle = 1;
  AttWidth = 1;
  CurrentExcState = 0;
  NumMedia = 0;
  MaxMedia = 11;
  P.SetName("P_"+Name);
  P.SetCoords(0,0,0,0);
  RI = 0;
  X.SetName("X_"+Name);
  X.SetCoords(0,0,0,0);
  SaveTrajectory = 0;

  // Pointers
  Eexc = 0;
  IonInMedium = new EnergyLoss*[MaxMedia];
  for (int m=0; m<MaxMedia; m++)
    IonInMedium[m] = 0;
  Trajectory = new TEveStraightLineSet(); 
  TrT = new float[MaxPoints];
  TrX = new float[MaxPoints];
  TrY = new float[MaxPoints];
  TrZ = new float[MaxPoints];
  TrK = new float[MaxPoints];
}


///////////////////////////////////////////////////////////////////////////////////
// Lorentz boost for the position and momentum four-vectors.
///////////////////////////////////////////////////////////////////////////////////
void Particle::Boost(double BetaX, double BetaY, double BetaZ)
{
  X.Boost(BetaX, BetaY, BetaZ);
  P.Boost(BetaX, BetaY, BetaZ);
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// Copy members of another Particle object.  It does not modify Name.
///////////////////////////////////////////////////////////////////////////////////
//Particle& Particle::operator=(const Particle& rhs) {
void Particle::Copy(Particle* rhs) {
  if (this != rhs) {
    // Do the assignment operation.
    A = rhs->A;
    SetExcEnergies(rhs->NEexc, rhs->Eexc);
    Mass = rhs->Mass;
    Q = rhs->Q;
    X = rhs->X;
    P = rhs->P;
  }
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// Copy the trace information to individual arrays.
///////////////////////////////////////////////////////////////////////////////////
void Particle::CopyTrace(int& NumPts, float* t, float* x, float* y, float* z, float* K)
{
  int TotPoints = TrPts;
  if (TrPts>MaxPoints)
    TotPoints = MaxPoints;
  for (int p=0; p<TotPoints; p++) {
    t[p] = TrT[p];
    x[p] = TrX[p];
    y[p] = TrY[p];
    z[p] = TrZ[p];
    K[p] = TrK[p];
  }
  NumPts = TotPoints;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// Get the cartesian components of the velocity in units of c.
///////////////////////////////////////////////////////////////////////////////////
void Particle::GetBeta(double& BetaX, double& BetaY, double& BetaZ)
{
  double E = P.GetX0();
  double px = P.GetX1();
  double py = P.GetX2();
  double pz = P.GetX3();
  BetaX = px/E;
  BetaY = py/E;
  BetaZ = pz/E;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////
int Particle::GetCurrentExcState()
{
  return CurrentExcState;
}


///////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////
double Particle::GetEexc()
{
  double Eexc = 0;
  if (this->Eexc!=0 && CurrentExcState>=0 && CurrentExcState<NEexc)
    Eexc = this->Eexc[CurrentExcState];
  return Eexc;
}

double Particle::GetEexc(int ExcState)
{
  double Eexc = 0;
  if (this->Eexc!=0 && ExcState>=0 && ExcState<NEexc)
    Eexc = this->Eexc[ExcState];
  return Eexc;
}


///////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////
double Particle::GetFinalEnergy(int MediumID, double InitE, double PathLength, double StepSize)
{
  double FinalE = InitE;
  int m = MediumID;
  if (m>=0 && m<NumMedia) {
    FinalE = IonInMedium[m]->GetFinalEnergy(InitE, (float)PathLength, (float)StepSize);
    //    cout << "Using " << IonInMedium[m]->FileName << endl;
    if (FinalE<0)
      FinalE = 0;
  }
  return FinalE;
}



///////////////////////////////////////////////////////////////////////////////////
// Return the kinetic energy (total energy minus mass minus excitation energy).
///////////////////////////////////////////////////////////////////////////////////
double Particle::GetKE()
{
  double KE = P.GetX0() - Mass - GetEexc();
  return KE;
}


///////////////////////////////////////////////////////////////////////////////////
// Return four momentum objects.
///////////////////////////////////////////////////////////////////////////////////
FourVector Particle::GetP()
{
  FourVector P = this->P;
  return P;
}


///////////////////////////////////////////////////////////////////////////////////
// Return coordinates of four momentum.
///////////////////////////////////////////////////////////////////////////////////
void Particle::GetP(double& P0, double& P1, double& P2, double& P3)
{
  P0 = P.GetX0();
  P1 = P.GetX1();
  P2 = P.GetX2();
  P3 = P.GetX3();
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////
double Particle::GetPathLength(int MediumID, double InitE, double FinalE, double DeltaT)
{
  double PL = 0;
  int m = MediumID;
  if (m>=0 && m<NumMedia) 
    PL = IonInMedium[m]->GetPathLength((float)InitE, (float)FinalE, (float)DeltaT);
  return PL;
}


///////////////////////////////////////////////////////////////////////////////////
// Get the azimuthal angle in radians (from 0 to 2*pi).
///////////////////////////////////////////////////////////////////////////////////
double Particle::GetPhi()
{
  double phi = 0;
  double px = P.GetX1();
  double py = P.GetX2();
  double pz = P.GetX3();
  if (px>=0 && py>0) 
    phi = atan(py/px);
  else if (px<0 && py>0)
    phi = pi + atan(py/px);
  else if (px<0 && py<0)
    phi = pi + atan(py/px);
  else if (px>0 && py<0)
    phi = 2*pi + atan(py/px);

  return phi;
}


///////////////////////////////////////////////////////////////////////////////////
// Get the polar angle in radians.
///////////////////////////////////////////////////////////////////////////////////
double Particle::GetTheta()
{
  double theta;
  double px = P.GetX1();
  double py = P.GetX2();
  double pz = P.GetX3();
  theta = atan(sqrt(px*px+py*py)/pz);
  if (pz<0)
    theta += pi;
  return theta;
}


///////////////////////////////////////////////////////////////////////////////////
// Return the trajectory attributes.
///////////////////////////////////////////////////////////////////////////////////
void Particle::GetTrajectoryAtt(short& Color, short& Style, short& Width)
{
  Color = AttColor;
  Style = AttStyle;
  Width = AttWidth;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// Return coordinates of position four vector.
///////////////////////////////////////////////////////////////////////////////////
void Particle::GetX(double& X0, double& X1, double& X2, double& X3)
{
  X0 = X.GetX0();
  X1 = X.GetX1();
  X2 = X.GetX2();
  X3 = X.GetX3();
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// Simple function that prints some variables of this class.
///////////////////////////////////////////////////////////////////////////////////
void Particle::Print()
{
  cout << "== Particle " << Name << " =="<< endl;
  cout << "mass = " << Mass << " MeV/c^2    Charge = " << Q << " e" << endl;
  if (NEexc>0) {
    cout << "Eexc = ";
    for (int n=0; n<NEexc; n++) {
      cout << Eexc[n];
      if (n<NEexc-1)
	cout << ", ";
      else
	cout << "\n";
    }
  }
  X.Print();
  P.Print();
  cout << "Trajectory: " << Trajectory  << " C=" << Trajectory->GetLineColor() 
       << " W=" << Trajectory->GetLineWidth() << " S=" << Trajectory->GetLineStyle() << endl;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////
void Particle::ResetTrace()
{
  int TotPoints = TrPts;
  if (TrPts==0)
    TotPoints = MaxPoints;
  for (int p=0; p<TotPoints; p++) {
    TrT[p] = -1000;
    TrX[p] = 0;
    TrY[p] = 0;
    TrZ[p] = -1000;
    TrK[p] = 0;
  }
  TrPts = 0;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetCurrentExcState(int ExcState)
{
  CurrentExcState = ExcState;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// Set the number of excited states for this particle and obtain their values from 
// the array Eexc[].
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetExcEnergies(int N, double* Eexc)
{
  if (N>0 && Eexc!=0) {
    NEexc = N;
    this->Eexc = new double[N];
    for (int n=0; n<N; n++)
      this->Eexc[n] = Eexc[n];
  }
  return;
}


///////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetMedia(int NumMedia, string* ELossFile)
{
  if (Q>0) {
    if (NumMedia<=MaxMedia) {
      this->NumMedia = NumMedia;
      for (int m=0; m<NumMedia; m++) {
	IonInMedium[m] = new EnergyLoss();
	IonInMedium[m]->LoadSRIMFile(ELossFile[m]);
	IonInMedium[m]->SetIonMass(Mass);
	if (!IonInMedium[m]->GoodELossFile) {
	  delete IonInMedium[m];
	  IonInMedium[m] = 0;
	}
	cout << Name << ": SRIM file " << ELossFile[m] << " loaded." << endl;
      }
    }
    else
      cout << "Warning: Particle \'" << Name << "\' cannot have more than " << MaxMedia 
	   << " energy loss files." << endl;
  }
  else 
    cout << Name << ": SRIM file not loaded for particle with Q=" << Q << endl;

  return;
}

///////////////////////////////////////////////////////////////////////////////////
// Copy just the coordinates of the four vector V to the class member P.
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetP(FourVector V) 
{
  double P0, P1, P2, P3;
  P0 = V.GetX0();
  P1 = V.GetX1();
  P2 = V.GetX2();
  P3 = V.GetX3();
  P.SetCoords(P0, P1, P2, P3);
  return;
}


///////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetP(double P0, double P1, double P2, double P3) 
{
  P.SetCoords(P0, P1, P2, P3);
  return;
}


///////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetReactionIndex(int RI)
{
  this->RI = RI;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetTracePoint(float t, float x, float y, float z, float K)
{
  int p = TrPts;
  if (p<MaxPoints) {
    TrT[p] = t;
    TrX[p] = x;
    TrY[p] = y;
    TrZ[p] = z;
    TrK[p] = K;
  }
  else 
    cout << "Warning: " << Name << " reached maximum number of trace points." << endl;
  TrPts++;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetTrajectoryAtt(short Color, short Style, short Width)
{
  AttColor = Color;
  AttStyle = Style;
  AttWidth = Width;
  return;
}


///////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////
void Particle::SetX(double X0, double X1, double X2, double X3) 
{
  X.SetCoords(X0, X1, X2, X3);
  return;
}
