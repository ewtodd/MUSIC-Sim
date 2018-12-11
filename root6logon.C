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
  gSystem->Load("/home/dasago/Dropbox/Codes/PhysicsTools/EnergyLoss.so"); 
  gSystem->Load("/home/dasago/Dropbox/Codes/PhysicsTools/FourVector.so"); 
  gSystem->Load("/home/dasago/Dropbox/Codes/PhysicsTools/Particle.so"); 
  gSystem->Load("/home/dasago/Dropbox/Codes/PhysicsTools/NuclideFinder_cpp.so"); 
  // Special lib
  gSystem->Load("/home/dasago/Dropbox/Codes/PhysicsTools/SRIM_Table_Maker_cpp.so");
  gSystem->Load("/home/dasago/Dropbox/Codes/MUSIC/Simulator/MUSIC_Simulator_cpp.so");
}
