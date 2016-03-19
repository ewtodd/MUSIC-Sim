///////////////////////////////////////////////////////////////////////////////////
// Script to compile with ACLiC the HELIOS_Simulator class.  
///////////////////////////////////////////////////////////////////////////////////
{
  // Necessary for OpenMP (parallel processing)
  TString cmd(gSystem->GetMakeSharedLib());
  cmd.ReplaceAll("g++","g++ -fopenmp");
  gSystem->SetMakeSharedLib(cmd);
  // References:
  //  http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=11421
  //  http://root.cern.ch/root/roottalk/roottalk10/1126.html
  //  https://computing.llnl.gov/tutorials/openMP/

  string CodeDir = "~/Dropbox/Codes/HELIOS/Simulator/";
  string IncludePath = "~/Dropbox/DataAnalysisProject/include/MasterVersion/";
  int LibStatus = 0;
  LibStatus += gSystem->Load((IncludePath + "EnergyLoss_cpp.so").c_str());
  LibStatus += gSystem->Load((IncludePath + "FourVector_cpp.so").c_str());
  LibStatus += gSystem->Load((IncludePath + "Particle_cpp.so").c_str());
  LibStatus += gSystem->Load((IncludePath + "SRIM_Table_Maker_cpp.so").c_str());
  LibStatus += gSystem->Load((IncludePath + "VectorField_cpp.so").c_str());
  LibStatus += gSystem->Load("ParticleBranch_cpp.so");
  if (LibStatus==0) 
    gROOT->ProcessLine(Form(".L %sHELIOS_Simulator.cpp++",CodeDir.c_str()));
  
}
