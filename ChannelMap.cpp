//#include <TROOT.h>
#include <TMath.h>
#include <TRandom3.h>

#include <iostream>
#include <fstream>
#include <string>

#include "ChannelMap.hpp"

using namespace std;

//----------------------------------------------------------------------------------------------------
// Most common constructor.
//----------------------------------------------------------------------------------------------------
ChannelMap::ChannelMap(string MapFile)
{

  rand = new TRandom3();   // Useful random number.

  cout << "> Loading channel map ..." << endl;
  ifstream Read;
  string line;
  int line_counter = 0;
  TotalChannels = 0;
  MaxUnknownChannels = 1000;

  Read.open(MapFile.c_str());
  
  if (!Read.is_open())
    cout << ">\tERROR: The channel map file \"" << MapFile << "\" couldn't be opened." << endl;
  else {
    
    cout << ">\tThe channel map file \"" << MapFile << "\" was opened successfully." << endl;
    
    line_counter = 0;
    do{
      getline(Read, line);
      // Only count non-empty lines.
      if (!line.empty())          
	line_counter++; 
    } while (!Read.eof());
    Read.close();

    TotalChannels = line_counter-1;

    Module = new int[TotalChannels];
    Chan = new int[TotalChannels];
    Det_Type = new string[TotalChannels];
    Det_ID = new int[TotalChannels];
    Det_Ch = new int[TotalChannels];

    Read.open(MapFile.c_str());
    getline(Read, line);    // The 1st line is for column description;
    for (int i=0; i<TotalChannels; i++) {
      Read >> Module[i] >> Chan[i] >> Det_Type[i] >> Det_ID[i] >> Det_Ch[i]; 
      getline(Read, line);  // The last column is for comments
    }
    Read.close();

    cout << ">\t" << TotalChannels << " channels loaded." << endl;
    
    // Arrays for unknown channels.
    TotUnknown = 0;
    UK_Module = new int[MaxUnknownChannels];
    UK_Channel = new int[MaxUnknownChannels];
    UK_Freq = new int[MaxUnknownChannels];
    for (int i=0; i<MaxUnknownChannels; i++) {
      UK_Module[i] = -1;
      UK_Channel[i] = -1;
      UK_Freq[i] = 0;
    }
  }

}


//----------------------------------------------------------------------------------------------------
void ChannelMap::AddUnknownChannel(int Module, int Channel)
{
  bool AlreadySaved = 0;
  for (int i=0; i<TotUnknown; i++)
    if (Module==UK_Module[i] && Channel==UK_Channel[i]) {
      AlreadySaved = 1;
      UK_Freq[i]++;
      break;
    }
  if (!AlreadySaved) {
    UK_Module[TotUnknown] = Module;
    UK_Channel[TotUnknown] = Channel;
    TotUnknown++;
  }
  return;
}


//----------------------------------------------------------------------------------------------------
//Description: From the channel map provided in the constructor this function obtains the
//             detector number and detector channel number for a given module and channel.
bool ChannelMap::Identify(int Module, int Channel, string& Det_Type, int& Det_ID, int& Det_Ch)
{
  bool ChannelIdentified = 0;
  for (int i=0; i<TotalChannels; i++) {
    if (this->Module[i] == Module && Chan[i] == Channel) {
      Det_Type = this->Det_Type[i];
      Det_ID = this->Det_ID[i];
      Det_Ch = this->Det_Ch[i];
      ChannelIdentified = 1;
      break;
    }	 
  }
  if (!ChannelIdentified)
    AddUnknownChannel(Module, Channel);
  return ChannelIdentified;
}


//----------------------------------------------------------------------------------------------------
void ChannelMap::WriteUnknownChannels(string FileName)
{
  ofstream Write;
  if (TotUnknown>0) {
    Write.open(FileName.c_str());
    if (TotUnknown>0) {
      Write << "Unknown channel:\nModule\tChannel\tFreq" << endl;
      for (int i=0; i<TotUnknown; i++)
	Write << UK_Module[i] << "\t" << UK_Channel[i] << "\t" << UK_Freq[i] << endl;
    }
    Write.close();
  }
  return;
}
