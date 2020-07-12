// This file will be automatically read when starting a ROOT session.
{
  // Get rid of the -Wshadow flag for the compiler.
  TString CompilerString = gSystem->GetMakeSharedLib();
  CompilerString.ReplaceAll("-Wshadow", "");
  gSystem->SetMakeSharedLib(CompilerString);

  /////////////////////////////////////////////////////////////////////////////
  // Load the necessary libraries for the script to run.
  /////////////////////////////////////////////////////////////////////////////
  gStyle->SetOptStat("");  
  gROOT->ProcessLine(".L ../../../physics-tools/EnergyLoss.cpp+"); 
  gROOT->ProcessLine(".L ../../../physics-tools/FourVector.cpp+"); 
  gROOT->ProcessLine(".L ../../../physics-tools/Particle.cpp+"); 
  gROOT->ProcessLine(".L ../../../physics-tools/NuclideFinder.cpp+"); 
  gROOT->ProcessLine(".L ../../../physics-tools/SRIM_Table_Maker.cpp+");
  gROOT->ProcessLine(".L ../../MUSIC_Simulator.cpp+");
  
}
