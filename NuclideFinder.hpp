#ifndef NuclideFinder_hpp_INCLUDED   
#define NuclideFinder_hpp_INCLUDED   

#include <iostream>
#include <string>

class NuclideFinder {

public:

  NuclideFinder();
  int GetA(int Index);
  int GetArraySize();
  double GetMass(int Index, string Units);
  double GetMass(int Z, int A, string Units);
  double GetMass(string Nuclide, string Units);
  string GetName(int Index);
  int GetZ(int Index);
  int GetZ(string Nuclide);

private:
  void Init();

  int Size;
  int* A;
  int* N;
  int* Z;
  string* Name;
  double* Mass;  // in micro-u (unified atomic mass unit).
};

#endif
