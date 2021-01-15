/*******************************************************************
Code: NuclideFinder

Description: Portable class from which one can obtain the mass of
             a nuclide by specifying its symbol or 'name', e.g
             "4He". The user must choose the mass units from the
             following string options: "MeV/c^2", "u" (unified atomic 
             mass unit) or "micro-u".  Similarly, the mass and atomic
             numbers can be retrieved from the nuclide 'name'.
             
Compile with: 
* Original
g++ -shared -fPIC NuclideFinder.cpp -o NuclideFinder.so
* Better compatibility results (works with CStoSF and SFtoCS)
g++ -c -o NuclideFinder.so NuclideFinder.cpp

Author: Daniel Santiago-Gonzalez
2015-01
 
*******************************************************************/
#ifndef NuclideFinder_hpp_INCLUDED   
#define NuclideFinder_hpp_INCLUDED   

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>      // for std::out_of_range

class NuclideFinder {

public:

  NuclideFinder();
  int GetA(int Index);
  int GetArraySize();
  float GetGSspin(int Index);
  int GetGSparity(int Index);
  double GetMass(int Index, std::string Units);
  double GetMass(int Z, int A, std::string Units);
  double GetMass(std::string Nuclide, std::string Units);
  int GetN(std::string Nuclide);
  std::string GetName(int Index);
  std::string GetName(int Z, int A);
  int GetZ(int Index);
  int GetZ(std::string Nuclide);
  int IsMeasured(int Index);
  int LoadAMEFile(std::string file);
  int LoadNubaseFile(std::string file);

private:
  std::string GetProperName(std::string Nuclide);
  void Init();
  void SetGSProperties();

  int Size;
  int* A;
  int* N;
  int* Z;
  int* Measured;
  std::string* Name;
  double* Mass;  // in micro-u (unified atomic mass unit).
  float* GSspin;
  int* GSparity;


  int nubaseLines;
  // Nubase data structure (from nubase2020.asc file) 
  struct nubaseEntry {
    int massNumber;       // mass number (A)
    int atomicNumber;     // atomic number (Z)
    int stateIndex;       // 0=ground state; 1=1,2,3 ... isomers
    std::string Aelem;    // string containing mass number and element symbol
    char Ssym;            // s in nubase (17)
    double massExcess;    // mass excess in keV
    int massMeas;         // Whether the mass value is measured (1) or not (0=#)
    double massUnc;       // uncertainty of mass excess
    int massUncMeas;      // Whether the mass uncertainty is measured (1) or not (0=#)
    float exc;            // Isomer excitation energy in keV
    int excMeas;          // Whether the excitation energy is measured (1) or not (0=#)
    float excUnc;         // Isomer excitation energy uncertainty in keV
    int excUncMeas;       // Whether the excitation energy uncertainty is measured (1) or not (0=#)
    int uncertIGorder;    // 1 or 0, whether the order of isomer or ground state is uncertain
    float halfLife;       // half-life in 'unitTime'
    int halfLifeMeas;     // Whether the half-life is measured (1) or not (0=#)
    int stable;           // whether the nuclide is "stable" (1) or not (0)
    std::string unitTime; // half-life unit of time
    float halfLifeUnc;    // half-life uncertainty
    int halfLifeUncMeas;  // Whether the half-life uncertainty is measured (1) or not (0=#)
    float twoJ;           // spin times 2
    int spinUnc;          // whether the spin is well established (1) or uncertain (0)
    int parity;           // parity (+1, -1)
    int parityUnc;        // whether the parity is well established (1) or uncertain (0)
    char JPiExtra;        // Whether the spin-parity is measured (*), from systematics (#), or
                          // from isospin (T)
    int yearENSDF;        // ENSDF update year
    int discovery;        // year of discovery
    std::string decayBR;  // the last part of the data entry (char 111:201). Unprocessed
    double mass;          // mass in micro-u (not in nubase original data)
    double timeToSec;     // time conversion factor to seconds
    double halfLifeSec;   // half-life in seconds
  };
  

  // ClassDef(NuclideFinder,1);

};

#endif
